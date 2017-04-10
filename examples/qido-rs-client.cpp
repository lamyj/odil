#include <string>
#include <sstream>
#include <iostream>

#include <boost/asio.hpp>


#include <odil/DataSet.h>
#include <odil/Tag.h>
#include <odil/webservices/HTTPRequest.h>
#include <odil/webservices/QIDORSRequest.h>
#include <odil/webservices/Selector.h>
#include <odil/webservices/URL.h>

int main ()
{
    odil::webservices::URL const root{
        "http", "demo.orthanc-server.com", "/dicom-web"};

    odil::webservices::QIDORSRequest qido_request(root);

    //-------------------- Query DataSet creation
    odil::DataSet query_ds;
    query_ds.add(odil::Tag("PatientName"), {"KNIX"});

    //-------------------- Selector creation
    odil::webservices::Selector selector;
    selector.set_series("");

    //-------------------- Wanted included fields
    std::set< std::vector< odil::Tag > > includefields;
    includefields.insert({odil::Tag("00200035")});
    includefields.insert({odil::Tag("00200030")});


    qido_request.request_datasets(
        odil::webservices::Representation::DICOM_XML,
        selector,
        query_ds,
        includefields // WARNING : the server specified here doesn't handle <includefield> field
                      // the option includefield=all is understand as <DicomTag>=<Value> so it leads to an error
        );

    auto http_request = qido_request.get_http_request();
    // Explicitely use HTTP/1.0 to avoid chunked encoding
    http_request.set_http_version("HTTP/1.0");
    http_request.set_header("Host", root.authority);
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

    std::cout << stream.rdbuf() << std::endl;
    return 0;
}
