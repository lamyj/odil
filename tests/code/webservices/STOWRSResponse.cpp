#define BOOST_TEST_MODULE STOWRSResponse
#include <boost/test/unit_test.hpp>

#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/version.hpp>

#include <json/json.h>

#include "odil/DataSet.h"
#include "odil/json_converter.h"
#include "odil/registry.h"
#include "odil/webservices/ItemWithParameters.h"
#include "odil/webservices/STOWRSResponse.h"
#include "odil/webservices/multipart_related.h"
#include "odil/webservices/Utils.h"
#include "odil/xml_converter.h"

struct Fixture
{
    odil::DataSet data_set;

    Fixture()
    {
        odil::DataSet data_set_1;
        data_set_1.add("RetrieveURL", {"http://example.com/dicom/studies/7.8.9"});
        data_set_1.add("FailedSOPSequence", {odil::DataSet()}, odil::VR::SQ);
        odil::DataSet referenceSOPSequence;
        odil::DataSet referenceSOPSequence_item1; // first instance that was correctly stored
        referenceSOPSequence_item1.add("ReferencedSOPClassUID", {odil::registry::MRImageStorage});
        referenceSOPSequence_item1.add("ReferencedSOPInstanceUID", {"1.2.3.6.1"});
        referenceSOPSequence_item1.add("RetrieveURL",
            {"http://example.com/dicom/studies/7.8.9/series/4.5/instances/1.2.3.6.1"});
        odil::DataSet referenceSOPSequence_item2; // second instance that was correctly stored
        referenceSOPSequence_item2.add("ReferencedSOPClassUID", {odil::registry::RawDataStorage});
        referenceSOPSequence_item2.add("ReferencedSOPInstanceUID", {"1.2.3.6.2"});
        referenceSOPSequence_item2.add("RetrieveURL",
            {"http://example.com/dicom/studies/7.8.9/series/4.5/instances/1.2.3.6.2"});

        data_set_1.add("ReferencedSOPSequence", {referenceSOPSequence_item1, referenceSOPSequence_item2});

        data_set = data_set_1;
    }
};


BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::webservices::STOWRSResponse const response;
    BOOST_REQUIRE(response.get_store_instance_responses().empty());
}

BOOST_FIXTURE_TEST_CASE(RespondDICOM_XML, Fixture)
{
    odil::webservices::STOWRSResponse response;
    response.set_representation(odil::webservices::Representation::DICOM_XML);
    response.set_store_instance_responses(data_set);
    BOOST_REQUIRE_EQUAL(response.get_media_type(), "application/dicom+xml");
    BOOST_REQUIRE(response.get_representation() == odil::webservices::Representation::DICOM_XML);

    auto const http = response.get_http_response();
    auto const content_type = boost::lexical_cast<
        odil::webservices::ItemWithParameters>(http.get_header("Content-Type"));
    BOOST_REQUIRE_EQUAL(content_type.name, "application/dicom+xml");

    std::stringstream stream(http.get_body());
    boost::property_tree::ptree xml;
    boost::property_tree::read_xml(stream, xml);
    BOOST_REQUIRE(data_set == odil::as_dataset(xml));
}

BOOST_FIXTURE_TEST_CASE(RespondDICOM_JSON, Fixture)
{
    odil::webservices::STOWRSResponse response;
    response.set_representation(odil::webservices::Representation::DICOM_JSON);
    response.set_store_instance_responses(data_set);
    BOOST_REQUIRE_EQUAL(response.get_media_type(), "application/dicom+json");
    BOOST_REQUIRE(response.get_representation() == odil::webservices::Representation::DICOM_JSON);

    auto const http = response.get_http_response();
    auto const content_type = boost::lexical_cast<
        odil::webservices::ItemWithParameters>(http.get_header("Content-Type"));
    BOOST_REQUIRE_EQUAL(content_type.name, "application/dicom+json");

    std::istringstream stream(http.get_body());
    Json::Value array;
    stream >> array;
    BOOST_REQUIRE(array.isArray());

    BOOST_REQUIRE(data_set == odil::as_dataset(array[0]));
}

BOOST_FIXTURE_TEST_CASE(Equality, Fixture)
{
    odil::webservices::HTTPResponse http_response;
    http_response.set_header("Content-Type", "application/dicom+xml");
    http_response.set_status(200);
    http_response.set_reason("OK");
    auto const xml = as_xml(data_set);
    std::ostringstream body;
#if BOOST_VERSION >= 105600
    typedef boost::property_tree::xml_writer_settings<std::string> SettingsType;
#else
    typedef boost::property_tree::xml_writer_settings<char> SettingsType;
#endif
    boost::property_tree::write_xml(body, xml, SettingsType());
    http_response.set_body(body.str());

    odil::webservices::STOWRSResponse response(http_response);

    odil::webservices::STOWRSResponse response_2;
    response_2.set_representation(odil::webservices::Representation::DICOM_XML);
    response_2.set_store_instance_responses(data_set);
    response_2.set_warning(false);
    response_2.set_reason("OK");

    BOOST_REQUIRE(response == response_2);
}

BOOST_FIXTURE_TEST_CASE(Difference, Fixture)
{
    // first http_response
    odil::webservices::HTTPResponse http_response;
    http_response.set_header("Content-Type", "application/dicom+xml");
    http_response.set_status(200);
    http_response.set_reason("OK");
    auto const xml = as_xml(data_set);
    std::ostringstream body;
#if BOOST_VERSION >= 105600
    typedef boost::property_tree::xml_writer_settings<std::string> SettingsType;
#else
    typedef boost::property_tree::xml_writer_settings<char> SettingsType;
#endif
    boost::property_tree::write_xml(body, xml, SettingsType());
    http_response.set_body(body.str());

    odil::webservices::STOWRSResponse response(http_response);

    // second http_response
    odil::webservices::HTTPResponse http_response_2;
    http_response_2.set_header("Content-Type", "application/dicom+xml");
    http_response_2.set_status(400);
    http_response_2.set_reason("Bad Request");
    odil::DataSet ds;
    auto const xml_2 = as_xml(ds);
    std::ostringstream body_2;
#if BOOST_VERSION >= 105600
    typedef boost::property_tree::xml_writer_settings<std::string> SettingsType;
#else
    typedef boost::property_tree::xml_writer_settings<char> SettingsType;
#endif
    boost::property_tree::write_xml(body_2, xml_2, SettingsType());
    http_response_2.set_body(body_2.str());

    odil::webservices::STOWRSResponse response_2(http_response_2);

    BOOST_REQUIRE(response != response_2);
}

BOOST_AUTO_TEST_CASE(Reason)
{
    odil::webservices::STOWRSResponse response;
    response.set_reason("Unauthorized");
    BOOST_REQUIRE_EQUAL(response.get_reason(),"Unauthorized");
}

BOOST_AUTO_TEST_CASE(InvalidReason)
{
    odil::webservices::STOWRSResponse response;
    BOOST_REQUIRE_THROW(response.set_reason("Unrecognize"), odil::Exception);
}

BOOST_AUTO_TEST_CASE(FailureCode)
{
    odil::webservices::STOWRSResponse response;
    response.set_failure_code(503);
    BOOST_REQUIRE_EQUAL(response.get_failure_code(), 503);
}

BOOST_AUTO_TEST_CASE(Representation)
{
    odil::webservices::STOWRSResponse response;
    response.set_representation(odil::webservices::Representation::DICOM_JSON);
    BOOST_REQUIRE(response.get_representation() == odil::webservices::Representation::DICOM_JSON);
}
