#define BOOST_TEST_MODULE WADORSResponse
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <json/json.h>

#include "odil/DataSet.h"
#include "odil/json_converter.h"
#include "odil/registry.h"
#include "odil/webservices/BulkData.h"
#include "odil/webservices/ItemWithParameters.h"
#include "odil/webservices/multipart_related.h"
#include "odil/webservices/Utils.h"
#include "odil/webservices/WADORSResponse.h"
#include "odil/Writer.h"
#include "odil/xml_converter.h"

struct Fixture
{
    std::vector<odil::DataSet> data_sets;
    std::vector<odil::webservices::BulkData> bulk_data;

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

        this->bulk_data = {
            {{'\x01', '\x02'}, "foo/bar", "here"},
            {{'\x03', '\x04'}, "plip/plop", "not/here"}};
    }
};

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::webservices::WADORSResponse const response;

    BOOST_REQUIRE(response.get_data_sets().empty());
    BOOST_REQUIRE(response.get_bulk_data().empty());
    BOOST_REQUIRE(!response.is_partial());
    BOOST_REQUIRE(response.get_type() == odil::webservices::Type::None);
}

BOOST_FIXTURE_TEST_CASE(DataSets, Fixture)
{
    odil::webservices::WADORSResponse response;
    response.set_data_sets(data_sets);
    BOOST_REQUIRE(response.get_data_sets() == data_sets);
}

BOOST_FIXTURE_TEST_CASE(BulkData, Fixture)
{
    odil::webservices::WADORSResponse response;
    response.set_bulk_data(bulk_data);
    BOOST_REQUIRE(
        std::equal(
            response.get_bulk_data().begin(), response.get_bulk_data().end(),
            bulk_data.begin(),
            [](odil::webservices::BulkData const & b1, odil::webservices::BulkData const & b2)
            {
                return (
                    b1.data == b2.data
                    && b1.type == b2.type && b1.location == b2.location);
            }));
}

BOOST_AUTO_TEST_CASE(Partial)
{
    odil::webservices::WADORSResponse response;
    response.set_partial(true);
    BOOST_REQUIRE(response.is_partial());
}

BOOST_FIXTURE_TEST_CASE(RespondFull, Fixture)
{
    odil::webservices::WADORSResponse wado;
    wado.set_data_sets(data_sets);
    wado.set_partial(false);

    wado.respond_dicom(odil::webservices::Representation::DICOM);

    auto const http = wado.get_http_response();
    BOOST_REQUIRE_EQUAL(http.get_status(), 200);
    BOOST_REQUIRE_EQUAL(http.get_reason(), "OK");
}

BOOST_FIXTURE_TEST_CASE(RespondPartial, Fixture)
{
    odil::webservices::WADORSResponse wado;
    wado.set_data_sets(data_sets);
    wado.set_partial(true);

    wado.respond_dicom(odil::webservices::Representation::DICOM);

    auto const http = wado.get_http_response();
    BOOST_REQUIRE_EQUAL(http.get_status(), 206);
    BOOST_REQUIRE_EQUAL(http.get_reason(), "Partial Content");
}

BOOST_FIXTURE_TEST_CASE(RespondDICOM, Fixture)
{
    odil::webservices::WADORSResponse wado;
    data_sets[0].set_transfer_syntax(odil::registry::ImplicitVRLittleEndian);
    wado.set_data_sets(data_sets);

    wado.respond_dicom(odil::webservices::Representation::DICOM);

    BOOST_REQUIRE(wado.get_type() == odil::webservices::Type::DICOM);
    BOOST_REQUIRE(
        wado.get_representation()
            == odil::webservices::Representation::DICOM);

    auto const http = wado.get_http_response();
    BOOST_REQUIRE(odil::webservices::is_multipart_related(http));
    BOOST_REQUIRE_EQUAL(odil::webservices::count_parts(http), data_sets.size());
    auto const content_type = boost::lexical_cast<
        odil::webservices::ItemWithParameters>(http.get_header("Content-Type"));
    BOOST_REQUIRE_EQUAL(
        content_type.name_parameters.at("type"), "application/dicom");

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

        BOOST_REQUIRE_EQUAL(content_type.name, "application/dicom");
        if(
            content_type.name_parameters.find("transfer-syntax")
                == content_type.name_parameters.end())
        {
            BOOST_REQUIRE(
                transfer_syntax == odil::registry::ExplicitVRLittleEndian);
        }
        else
        {
            BOOST_REQUIRE_EQUAL(
                transfer_syntax,
                content_type.name_parameters.at("transfer-syntax"));
        }

        std::ostringstream stream(std::ios_base::out | std::ios_base::binary);
        odil::Writer::write_file(
            data_set, stream, odil::DataSet(), transfer_syntax);
        BOOST_REQUIRE(stream.str() == part.get_body());
    }
}

BOOST_FIXTURE_TEST_CASE(RespondDICOMXML, Fixture)
{
    odil::webservices::WADORSResponse wado;
    wado.set_data_sets(data_sets);

    wado.respond_dicom(odil::webservices::Representation::DICOM_XML);

    BOOST_REQUIRE(wado.get_type() == odil::webservices::Type::DICOM);
    BOOST_REQUIRE(
        wado.get_representation()
            == odil::webservices::Representation::DICOM_XML);

    auto const http = wado.get_http_response();
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

BOOST_FIXTURE_TEST_CASE(RespondDICOMJSON, Fixture)
{
    odil::webservices::WADORSResponse wado;
    wado.set_data_sets(data_sets);

    wado.respond_dicom(odil::webservices::Representation::DICOM_JSON);

    BOOST_REQUIRE(wado.get_type() == odil::webservices::Type::DICOM);
    BOOST_REQUIRE(
        wado.get_representation()
            == odil::webservices::Representation::DICOM_JSON);

    auto const http = wado.get_http_response();
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

BOOST_FIXTURE_TEST_CASE(RespondBulkData, Fixture)
{
    odil::webservices::WADORSResponse wado;
    wado.set_bulk_data(bulk_data);

    wado.respond_bulk_data();

    BOOST_REQUIRE(wado.get_type() == odil::webservices::Type::BulkData);

    auto const http = wado.get_http_response();
    BOOST_REQUIRE(odil::webservices::is_multipart_related(http));
    BOOST_REQUIRE_EQUAL(odil::webservices::count_parts(http), bulk_data.size());
    auto const content_type = boost::lexical_cast<
        odil::webservices::ItemWithParameters>(http.get_header("Content-Type"));
    BOOST_REQUIRE_EQUAL(
        content_type.name_parameters.at("type"), "application/octet-stream");

    std::vector<odil::webservices::Message> parts;
    odil::webservices::transform_parts(
        http, std::back_inserter(parts),
        [](odil::webservices::Message const & m) { return m; });

    for(unsigned int i=0; i<bulk_data.size(); ++i)
    {
        auto const & part = parts[i];
        BOOST_REQUIRE_EQUAL(part.get_header("Content-Type"), bulk_data[i].type);
        BOOST_REQUIRE_EQUAL(
            part.get_header("Content-Location"), bulk_data[i].location);

        std::vector<uint8_t> data;
        std::copy(
            part.get_body().begin(), part.get_body().end(),
            std::back_inserter(data));
        BOOST_REQUIRE(data == bulk_data[i].data);
    }
}

BOOST_FIXTURE_TEST_CASE(RespondPixelData, Fixture)
{
    odil::webservices::WADORSResponse wado;
    wado.set_bulk_data(bulk_data);

    wado.respond_pixel_data("image/jpeg");

    BOOST_REQUIRE(wado.get_type() == odil::webservices::Type::PixelData);

    auto const http = wado.get_http_response();
    BOOST_REQUIRE(odil::webservices::is_multipart_related(http));
    BOOST_REQUIRE_EQUAL(odil::webservices::count_parts(http), bulk_data.size());
    auto const content_type = boost::lexical_cast<
        odil::webservices::ItemWithParameters>(http.get_header("Content-Type"));
    BOOST_REQUIRE_EQUAL(content_type.name_parameters.at("type"), "image/jpeg");

    std::vector<odil::webservices::Message> parts;
    odil::webservices::transform_parts(
        http, std::back_inserter(parts),
        [](odil::webservices::Message const & m) { return m; });

    for(unsigned int i=0; i<bulk_data.size(); ++i)
    {
        auto const & part = parts[i];
        BOOST_REQUIRE_EQUAL(part.get_header("Content-Type"), bulk_data[i].type);
        BOOST_REQUIRE_EQUAL(
            part.get_header("Content-Location"), bulk_data[i].location);

        std::vector<uint8_t> data;
        std::copy(
            part.get_body().begin(), part.get_body().end(),
            std::back_inserter(data));
        BOOST_REQUIRE(data == bulk_data[i].data);
    }
}
