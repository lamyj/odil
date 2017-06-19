#define BOOST_TEST_MODULE STOWRSRequest
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/registry.h"
#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/ItemWithParameters.h"
#include "odil/webservices/multipart_related.h"
#include "odil/webservices/STOWRSRequest.h"
#include "odil/webservices/URL.h"
#include "odil/webservices/Utils.h"

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
        data_set_2.add("Signature", odil::Value::Binary({{0x01, 0x02, 0x03, 0x04}}));

        this->data_sets = { data_set_1, data_set_2 };
    }
};

odil::webservices::URL const base_url_http{
    "http", "example.com", "/dicom", "", ""};

odil::webservices::URL const full_url {
    "http", // scheme
    "example.com", // authority
    "/dicom/studies/1.2", // path
    "", // query
    ""// fragment
};

odil::webservices::Selector const selector(
    std::map<std::string, std::string>({{"studies", "1.2"}}));

BOOST_AUTO_TEST_CASE(Constructor_BaseUrl)
{
    odil::webservices::STOWRSRequest const request(base_url_http);
    BOOST_REQUIRE(request.get_base_url() == base_url_http);
}

BOOST_AUTO_TEST_CASE(Base_Url)
{
    odil::webservices::STOWRSRequest request(base_url_http);
    odil::webservices::URL const base_url_http2{
        "http", "second_example.com", "/dicom", "", ""};
    request.set_base_url(base_url_http2);
    BOOST_REQUIRE(request.get_base_url() == base_url_http2);
}

BOOST_AUTO_TEST_CASE(Constructor_Http)
{
    odil::webservices::HTTPRequest http_request(
                "POST", full_url);
    http_request.set_header("Content-Type", "multipart/related;type=application/dicom");
    odil::webservices::STOWRSRequest const request(http_request);

    //-------------------- Check for full url
    BOOST_REQUIRE(request.get_url() == full_url);

    //-------------------- Check for media_type
    BOOST_REQUIRE(request.get_media_type() == "application/dicom");

    //-------------------- Check for representation
    BOOST_REQUIRE(request.get_representation() == odil::webservices::Representation::DICOM);

    //-------------------- Check for representation
    BOOST_REQUIRE(request.get_selector() == selector);
}

BOOST_FIXTURE_TEST_CASE(DataSets, Fixture)
{
    odil::webservices::STOWRSRequest request(base_url_http);
    request.get_data_sets() = data_sets;

    //-------------------- Check for datasets
    BOOST_REQUIRE(request.get_data_sets() == data_sets);
}

BOOST_FIXTURE_TEST_CASE(FailRequestDataSets, Fixture)
{
    odil::webservices::STOWRSRequest request(base_url_http);
    odil::webservices::Selector invalid_selector(
        std::map<std::string, std::string>(
            {{"studies", "1.2"},
             {"series", "3.4"}})
    );

    //-------------------- Require exception
    BOOST_REQUIRE_THROW(request.request_dicom(data_sets, invalid_selector,
                                              odil::webservices::Representation::DICOM),
                        odil::Exception);
}

BOOST_FIXTURE_TEST_CASE(GetHttpRequest, Fixture)
{
    odil::webservices::STOWRSRequest request(base_url_http);
    request.request_dicom(data_sets, selector, odil::webservices::Representation::DICOM_XML);
    odil::webservices::HTTPRequest http_request = request.get_http_request();
    //-------------------- Check for http request content
    BOOST_REQUIRE(http_request.has_header("Content-Type"));
    BOOST_REQUIRE(http_request.get_method() == "POST");
    BOOST_REQUIRE(http_request.get_http_version() == "HTTP/1.0");
    BOOST_REQUIRE(odil::webservices::count_parts(http_request) == 3);// Two part for dataSets & 1 for binary
    BOOST_REQUIRE(request.get_base_url() == base_url_http);

    request.request_dicom(data_sets, selector, odil::webservices::Representation::DICOM);
    odil::webservices::HTTPRequest http_request_dcm = request.get_http_request();
    BOOST_REQUIRE(odil::webservices::count_parts(http_request_dcm) == 2);// only two parts here
}

BOOST_FIXTURE_TEST_CASE(DataSetsEquality, Fixture)
{
    // We use a getHttpRequest function that can change the dataSet internally, and we check if they remain the sames
    odil::webservices::STOWRSRequest request(base_url_http);
    request.request_dicom({data_sets[1]}, selector, odil::webservices::Representation::DICOM_JSON);
    odil::webservices::HTTPRequest http_request = request.get_http_request();

    BOOST_REQUIRE(request.get_data_sets() == std::vector<odil::DataSet>({data_sets[1]}));
}

BOOST_FIXTURE_TEST_CASE(Equality, Fixture)
{
    odil::webservices::STOWRSRequest request(base_url_http);
    request.request_dicom(data_sets, selector, odil::webservices::Representation::DICOM);
    odil::webservices::HTTPRequest const http_request = request.get_http_request();
    odil::webservices::STOWRSRequest second_request(http_request);

    //-------------------- Check equality
    BOOST_REQUIRE (request == second_request);
}

BOOST_FIXTURE_TEST_CASE(Equality_2, Fixture)
{
    odil::webservices::STOWRSRequest request(base_url_http);
    request.request_dicom(data_sets, selector, odil::webservices::Representation::DICOM_XML);
    odil::webservices::HTTPRequest http_request = request.get_http_request();
    odil::webservices::STOWRSRequest request_copy(http_request);
    BOOST_REQUIRE(request_copy == request);
    BOOST_REQUIRE(data_sets == request_copy.get_data_sets());
}
