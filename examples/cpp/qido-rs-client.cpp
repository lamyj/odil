#include <string>
#include <sstream>
#include <iostream>

#include <boost/asio.hpp>


#include <odil/DataSet.h>
#include <odil/Tag.h>
#include <odil/webservices/HTTPRequest.h>
#include <odil/webservices/HTTPResponse.h>
#include <odil/webservices/QIDORSRequest.h>
#include <odil/webservices/QIDORSResponse.h>
#include <odil/webservices/Selector.h>
#include <odil/webservices/URL.h>

#include "odil/json_converter.h"

#include "odil/registry.h"
#include "list"
#include <boost/lexical_cast.hpp>
#include "odil/Exception.h"

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

    void operator()(std::shared_ptr<odil::DataSet> const & data_set) const
    {
        for(auto const & item: *data_set)
        {
            this->stream << this->indent << item.first << " " << as_string(item.second.vr) << " ";
            odil::apply_visitor(*this, item.second.get_value());
            this->stream << "\n";
        }
    }
};

int main ()
{
    // orthanc local
//    odil::webservices::URL const root{
//        "http", "localhost", "/dicom-web"};
    // orthanc remote
    odil::webservices::URL const root{
        "http", "demo.orthanc-server.com", "/dicom-web"};


    odil::webservices::QIDORSRequest qido_request(root);

    //-------------------- Query DataSet creation
    auto query_ds = std::make_shared<odil::DataSet>();
    query_ds->add(odil::Tag("PatientName"), {"KNI*"}); // Only to test the regex
    //-------------------- Wanted included fields
    query_ds->add(odil::Tag("00200035"));
    query_ds->add(odil::Tag("00200030"));

    //-------------------- Selector creation
    odil::webservices::Selector selector;
    selector.set_series("");

    qido_request.request_datasets(
        odil::webservices::Representation::DICOM_JSON,
        selector,
        query_ds
        );

    auto http_request = qido_request.get_http_request();
    // Explicitly use HTTP/1.0 to avoid chunked encoding
    http_request.set_http_version("HTTP/1.0");
    http_request.set_header("Host", root.authority);
    http_request.set_header("Connection", "close");

    // orthanc local
//    boost::asio::ip::tcp::iostream stream("localhost", "8042");
    // orthanc remote
    boost::asio::ip::tcp::iostream stream;
    stream.connect(root.authority, root.scheme);
    if(!stream)
    {
        std::cerr << "Error connecting: "
#if BOOST_VERSION >= 104700
            << stream.error().message()
#endif
            << std::endl;

        return 1;
    }

    stream << http_request;
    if(!stream)
    {
        std::cerr << "Error sending: "
#if BOOST_VERSION >= 104700
            << stream.error().message()
#endif
             << std::endl;
        return 1;
    }

    odil::webservices::HTTPResponse http_response;
    stream >> http_response;
    if(!stream)
    {
        std::cerr << "Error receiving: "
#if BOOST_VERSION >= 104700
            << stream.error().message()
#endif
            << std::endl;
        return 1;
    }

    odil::webservices::QIDORSResponse qido_response(http_response);

    std::cout << "Datasets: " << qido_response.get_data_sets().size() << std::endl;

    Printer printer(std::cout);
    for(auto const & data_set: qido_response.get_data_sets())
    {
        printer(data_set);
    }

    return 0;
}
