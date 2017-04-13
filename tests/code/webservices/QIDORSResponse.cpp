#define BOOST_TEST_MODULE QIDORSResponse
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <vector>


#include <boost/lexical_cast.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <json/json.h>

#include "odil/DataSet.h"
#include "odil/json_converter.h"
#include "odil/registry.h"
#include "odil/webservices/HTTPResponse.h"
#include "odil/webservices/ItemWithParameters.h"
#include "odil/webservices/multipart_related.h"
#include "odil/webservices/QIDORSResponse.h"
#include "odil/webservices/Utils.h"
#include "odil/xml_converter.h"


struct Fixture
{
    std::vector<odil::DataSet> data_sets;

    Fixture()
    {
        odil::DataSet data_set_1;
        data_set_1.add("SOPClassUID", {odil::registry::RawDataStorage});
        data_set_1.add("SOPInstanceUID", {"1.2.3.4"});
        data_set_1.add("PatientID", {"DJ1234"});
        data_set_1.add("PixelSpacing", {1.5, 2.5});

        odil::DataSet data_set_2;
        data_set_2.add("SOPClassUID", {odil::registry::MRImageStorage});
        data_set_2.add("SOPInstanceUID", {"1.2.3.5"});
        data_set_2.add("PatientName", {"Doe^John"});
        data_set_2.add("PatientAge", {"042Y"});

        this->data_sets = { data_set_1, data_set_2 };
    }
};

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::webservices::QIDORSResponse const response;
    BOOST_REQUIRE(response.get_data_sets().empty());
}

BOOST_FIXTURE_TEST_CASE(DataSets, Fixture)
{
    odil::webservices::QIDORSResponse response;
    response.set_data_sets(data_sets);
    BOOST_REQUIRE(response.get_data_sets() == data_sets);
}

BOOST_FIXTURE_TEST_CASE(RespondDICOMJSON, Fixture)
{
    odil::webservices::QIDORSResponse response;
    response.set_representation(odil::webservices::Representation::DICOM_JSON);
    response.set_data_sets(data_sets);
    BOOST_REQUIRE_EQUAL(response.get_media_type(), "application/dicom+json");
    BOOST_REQUIRE(response.get_representation() == odil::webservices::Representation::DICOM_JSON);

    auto const http = response.get_http_response();
    BOOST_REQUIRE(!odil::webservices::is_multipart_related(http));
    auto const content_type = boost::lexical_cast<
        odil::webservices::ItemWithParameters>(http.get_header("Content-Type"));
    BOOST_REQUIRE_EQUAL(content_type.name, "application/dicom+json");


    std::istringstream stream(http.get_body());
    Json::Value array;
    stream >> array;
    BOOST_REQUIRE(array.isArray());

    std::vector<odil::DataSet> response_data_sets;
    std::transform(
        array.begin(), array.end(), std::back_inserter(response_data_sets),
        static_cast<odil::DataSet (*)(Json::Value const &)>(odil::as_dataset));

    BOOST_REQUIRE(response_data_sets == data_sets);
}

BOOST_FIXTURE_TEST_CASE(RespondDICOMXML, Fixture)
{
    odil::webservices::QIDORSResponse response;
    response.set_representation(odil::webservices::Representation::DICOM_XML);
    response.set_data_sets(data_sets);
    BOOST_REQUIRE_EQUAL(response.get_media_type(), "application/dicom+xml");
    BOOST_REQUIRE(response.get_representation() == odil::webservices::Representation::DICOM_XML);


    auto const http = response.get_http_response();
    BOOST_REQUIRE(odil::webservices::is_multipart_related(http));
    BOOST_REQUIRE_EQUAL(odil::webservices::count_parts(http), data_sets.size());
    auto const content_type = boost::lexical_cast<
        odil::webservices::ItemWithParameters>(http.get_header("Content-Type"));
    BOOST_REQUIRE_EQUAL(
        content_type.name_parameters.at("type"), "application/dicom+xml");

    std::vector<odil::webservices::Message> parts;
    odil::webservices::transform_parts(
        http, std::back_inserter(parts),
        [](odil::webservices::Message const & m) { return m; });

    for(unsigned int i=0; i<data_sets.size(); ++i)
    {
        auto const & data_set = data_sets[i];
        auto const transfer_syntax =
            data_set.get_transfer_syntax().empty()
                ?odil::registry::ExplicitVRLittleEndian
                :data_set.get_transfer_syntax();

        auto const & part = parts[i];
        auto const content_type = boost::lexical_cast<
            odil::webservices::ItemWithParameters>(
                part.get_header("Content-Type"));

        BOOST_REQUIRE_EQUAL(content_type.name, "application/dicom+xml");

        std::stringstream stream(part.get_body());
        boost::property_tree::ptree xml;
        boost::property_tree::read_xml(stream, xml);
        BOOST_REQUIRE(data_set == odil::as_dataset(xml));
    }
}

BOOST_AUTO_TEST_CASE(EmptyResponse)
{
    odil::webservices::QIDORSResponse response;
    auto const http = response.get_http_response();
    BOOST_REQUIRE(http.get_status() == 204);
    BOOST_REQUIRE_EQUAL(http.get_reason(), "No Content");
}
