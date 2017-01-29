#include <iostream>
#include <string>

#include <boost/asio.hpp>

#include <odil/webservices/WADORSRequest.h>
#include <odil/webservices/WADORSResponse.h>

int main()
{
    odil::webservices::URL const root{
        "http", "demo.orthanc-server.com", "/dicom-web"};

    odil::webservices::WADORSRequest wado_request(root);
    wado_request.request_dicom(
        odil::webservices::WADORS::Representation::DICOM_XML,
        {
            "2.16.840.1.113669.632.20.1211.10000357775",
            "1.3.46.670589.11.0.0.11.4.2.0.8743.5.5396.2006120114314125550",
            "1.3.46.670589.11.0.0.11.4.2.0.8743.5.5396.2006120114333648576"});

    auto http_request = wado_request.get_http_request();
    // Mark as 1.0 to avoid chunked encoding
    http_request.set_http_version("HTTP/1.0");
    http_request.set_header("Host", wado_request.get_base_url().authority);
    http_request.set_header("Connection", "close");

    boost::asio::ip::tcp::iostream stream;
    stream.connect(root.authority, root.scheme);
    stream << http_request;

    odil::webservices::HTTPResponse http_response;
    stream >> http_response;
    odil::webservices::WADORSResponse const wado_response(http_response);
    std::cout
        << "Datasets: " << wado_response.get_data_sets().size() << std::endl;
    std::cout
        << "Bulk data: " << wado_response.get_bulk_data().size() << std::endl;
    std::cout
        << "Partial content: " << std::boolalpha << wado_response.is_partial()
        << std::endl;

    return 0;
}
