#include "odil/webservices/STOWRSRequest.h"
#include "odil/webservices/STOWRSResponse.h"

#include <string>
#include <sstream>
#include <iostream>

#include <boost/asio.hpp>

#include "odil/VR.h"

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "json/json.h"

#include "odil/Reader.h"
#include "odil/DataSet.h"
#include "odil/registry.h"
#include "odil/Tag.h"
#include <odil/webservices/HTTPRequest.h>
#include <odil/webservices/HTTPResponse.h>
#include "odil/webservices/URL.h"
#include "odil/webservices/Selector.h"


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
            printer(std::const_pointer_cast<odil::DataSet const>(*it));
            if(it != last_it)
            {
                this->stream << "----\n";
            }
        }
    }

    void operator()(odil::Value::Binary const &) const
    {
        this->stream << this->indent << "(binary)";
    }

    void operator()(std::shared_ptr<odil::DataSet const> const & data_set) const
    {
        for(auto const & item: *data_set)
        {
            this->stream << this->indent << item.first << " " << as_string(item.second.vr) << " ";
            odil::apply_visitor(*this, item.second.get_value());
            this->stream << "\n";
        }
    }
};

struct Data
{
    odil::Value::DataSets data_sets;


    Data()
    {
        //-------------------- DataSets Creation
        auto ds = std::make_shared<odil::DataSet>();
        ds->add(odil::Tag("PatientName"), {"TOTO"});
        ds->add(odil::Tag("PatientID"), {"TOTO"});
        ds->add(odil::Tag("SOPClassUID"), {odil::registry::MRImageStorage});
        ds->add(odil::Tag("SOPInstanceUID"), {"1.2.3.5"});
        ds->add(odil::Tag("StudyInstanceUID"), {"1.3.46.670589.11.38235.5.0.4644.2013061709032540000"});
        ds->add(odil::Tag("SeriesInstanceUID"), {"1.3.46.670589.11.38235.5.0.5964.2013061710064254405"});
        ds->add(odil::Tag("Signature"), odil::Value::Binary({{0x01, 0x02}}));
        ds->add(odil::Tag("TransferSyntaxUID"), {odil::registry::ExplicitVRLittleEndian});

        auto ds_2 = std::make_shared<odil::DataSet>();
        ds_2->add(odil::Tag("PatientName"), {"JP"});
        ds_2->add(odil::Tag("PatientID"), {"TUTU"});
        ds_2->add(odil::Tag("SOPClassUID"), {odil::registry::MRImageStorage});
        ds_2->add(odil::Tag("SOPInstanceUID"), {"1.2.3.6"});
        ds_2->add(odil::Tag("StudyInstanceUID"), {"1.3.46.670589.11.38235.5.0.4644.2013061709032540000"});
        ds_2->add(odil::Tag("SeriesInstanceUID"), {"1.3.46.670589.11.38235.5.0.5964.31"});
        ds_2->add(odil::Tag("TransferSyntaxUID"), {odil::registry::ExplicitVRLittleEndian});
        this->data_sets = {ds, ds_2};
    }
};

int main()
{
    // Uncomment to test it locally (need to have orthanc installed)
//    odil::webservices::URL const root{
//        "http", "localhost", "/dicom-web"};
    // Uncomment to test it on a remote server (dicomserver.co.uk)
    odil::webservices::URL const root{
        "http", "dicomserver.co.uk", "/stow"};
    // Uncomment to test it on a remote server (demo.orthanc-server.com)
//    odil::webservices::URL const root{
//        "http", "demo.orthanc-server.com", "/dicom-web"};

    odil::webservices::STOWRSRequest stow_request(root);
    Data d;

    //-------------------- Selector creation
    odil::webservices::Selector selector;
    selector.set_study("1.3.46.670589.11.38235.5.0.4644.2013061709032540000");

     stow_request.request_dicom(d.data_sets, selector, odil::webservices::Representation::DICOM_JSON);

    auto http_request = stow_request.get_http_request();
    // Explicitly use HTTP/1.0 to avoid chunked encoding
    http_request.set_http_version("HTTP/1.0");
    http_request.set_header("Host", root.authority);
    http_request.set_header("Content-Length", std::to_string(http_request.get_body().size()));
    http_request.set_header("Transfer-Encoding", "identity");
    http_request.set_header("Accept", "application/dicom+xml");
    http_request.set_header("Connection", "close");

    // Dicomserver.co (seems to not support the XML or JSON format)
    boost::asio::ip::tcp::iostream stream("dicomserver.co.uk", "81");
    // Uncomment to test it locally (need to have orthanc installed)
//    boost::asio::ip::tcp::iostream stream("localhost", "8042");
    // Uncomment the two following lines to test on demo.orthanc-server.com
//    boost::asio::ip::tcp::iostream stream;
//    stream.connect(root.authority, root.scheme);
    if(!stream)
    {
        std::cerr << "Error connecting: "
#if BOOST_VERSION >= 104700
            << stream.error().message()
#endif
            << std::endl;
        return 1;
    }

    for (auto const header: http_request.get_headers())
    {
        std::cout << header.first << " : " << header.second << std::endl;
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

    if (!stream)
    {
        std::cerr << "Error receiving : "
#if BOOST_VERSION >= 104700
            << stream.error().message()
#endif
            << std::endl;
        return 1;
    }

    odil::webservices::STOWRSResponse stow_response(http_response);

    auto const data_set = stow_response.get_store_instance_responses();

    Printer printer(std::cout);
    printer(data_set);

    return 0;
}

