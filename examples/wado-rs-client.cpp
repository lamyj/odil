#include <iostream>
#include <sstream>
#include <string>

#include <boost/asio.hpp>

#include <odil/DataSet.h>
#include <odil/Value.h>
#include <odil/webservices/HTTPRequest.h>
#include <odil/webservices/HTTPResponse.h>
#include <odil/webservices/WADORSRequest.h>
#include <odil/webservices/WADORSResponse.h>

struct Printer
{
    typedef void result_type;

    std::ostream & stream;
    std::string indent;

    Printer(std::ostream & stream, std::string const & indent="")
    : stream(stream), indent(indent)
    {
        // Nothing else
    }

    template<typename T>
    void operator()(T const & value) const
    {
        for(auto const & item: value)
        {
            this->stream << item << " ";
        }
    }

    void operator()(odil::Value::DataSets const & value) const
    {
        this->stream << "\n";

        auto const last_it = --value.end();
        for(auto it=value.begin(); it!= value.end(); ++it)
        {
            Printer const printer(this->stream, this->indent+"  ");
            printer(*it);
            if(it != last_it)
            {
                this->stream << "----\n";
            }
        }
    }

    void operator()(odil::Value::Binary const & value) const
    {
        this->stream << this->indent << "(binary)";
    }

    void operator()(odil::DataSet const & data_set) const
    {
        for(auto const & item: data_set)
        {
            this->stream << this->indent << item.first << " " << as_string(item.second.vr) << " ";
            odil::apply_visitor(*this, item.second.get_value());
            this->stream << "\n";
        }
    }
};

int main()
{
    odil::webservices::URL const root{
        "http", "demo.orthanc-server.com", "/dicom-web"};

    odil::webservices::WADORSRequest wado_request(root);
    odil::webservices::Selector selector(
        std::map<std::string, std::string>(
            {{"studies", "2.16.840.1.113669.632.20.1211.10000357775"},
            {"series", "1.3.46.670589.11.0.0.11.4.2.0.8743.5.5396.2006120114314125550"},
            {"instances", "1.3.46.670589.11.0.0.11.4.2.0.8743.5.5396.2006120114333648576"}})
        );

    wado_request.request_dicom(
        odil::webservices::Representation::DICOM_XML,
        selector
        );

    auto http_request = wado_request.get_http_request();
    // Explicitely use HTTP/1.0 to avoid chunked encoding
    http_request.set_http_version("HTTP/1.0");
    http_request.set_header("Host", wado_request.get_base_url().authority);
    http_request.set_header("Connection", "close");

    boost::asio::ip::tcp::iostream stream;
    stream.connect(root.authority, root.scheme);
    if(!stream)
    {
      std::cerr << "Error connecting: " << stream.error().message() << std::endl;
      return 1;
    }

    stream << http_request;
    if(!stream)
    {
      std::cerr << "Error sending: " << stream.error().message() << std::endl;
      return 1;
    }

    odil::webservices::HTTPResponse http_response;
    stream >> http_response;
    if(!stream)
    {
      std::cerr << "Error receiving: " << stream.error().message() << std::endl;
      return 1;
    }

    odil::webservices::WADORSResponse const wado_response(http_response);
    std::cout
        << "Datasets: " << wado_response.get_data_sets().size() << std::endl;
    std::cout
        << "Bulk data: " << wado_response.get_bulk_data().size() << std::endl;
    std::cout
        << "Partial content: " << std::boolalpha << wado_response.is_partial()
        << std::endl;

    Printer printer(std::cout);
    for(auto const & data_set: wado_response.get_data_sets())
    {
        printer(data_set);
    }

    return 0;
}
