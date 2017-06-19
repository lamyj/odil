#define BOOST_TEST_MODULE QIDORSRequest
#include <boost/test/unit_test.hpp>

#include <set>

#include "odil/json_converter.h"

#include "odil/DataSet.h"
#include "odil/Tag.h"

#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/Utils.h"
#include "odil/webservices/QIDORSRequest.h"
#include "odil/webservices/Selector.h"
#include "odil/webservices/URL.h"

odil::webservices::URL const base_url_http{
    "http", "example.com", "/dicom", "", ""};

odil::webservices::Selector const instance_selector(
    std::map<std::string, std::string>(
        {{"studies", "1.2"},
         {"series", "3.4"},
         {"instances", ""}})
);

odil::webservices::URL const full_url {
    "http", // scheme
    "example.com", // authority
    "/dicom/studies/1.2/instances", // path
    "PatientName=TOTO&"
    "SharedFunctionalGroupsSequence.EffectiveEchoTime=10.5&"
    "includefield=00200020&includefield=52009229.00200035", // query
    ""// fragment
};


BOOST_AUTO_TEST_CASE(ConstructorUrl)
{
    odil::webservices::QIDORSRequest const request(base_url_http);
    BOOST_REQUIRE(request.get_base_url() == base_url_http);
}

BOOST_AUTO_TEST_CASE(BaseUrl)
{
    odil::webservices::HTTPRequest http_request(
                "GET", full_url);
    http_request.set_header("Accept", "application/dicom+json");
    odil::webservices::QIDORSRequest const request(http_request);

    //-------------------- Check for base url
    BOOST_REQUIRE(request.get_base_url() == base_url_http);
}

BOOST_AUTO_TEST_CASE(SetBaseUrl)
{
    odil::webservices::QIDORSRequest request((odil::webservices::URL()));
    request.set_base_url(base_url_http);
    BOOST_REQUIRE(request.get_base_url() == base_url_http);
}

BOOST_AUTO_TEST_CASE(FullUrl)
{
    odil::webservices::HTTPRequest http_request(
                "GET", full_url);
    http_request.set_header("Accept", "application/dicom+json");
    odil::webservices::QIDORSRequest const request(http_request);

    odil::webservices::URL const full_url_alphabetic {
        "http", // scheme
        "example.com", // authority
        "/dicom/studies/1.2/instances", // path
        "PatientName=TOTO&"
        "SharedFunctionalGroupsSequence.EffectiveEchoTime=10.5&"
        "includefield=PatientOrientation&includefield=SharedFunctionalGroupsSequence.ImageOrientation&"
        "fuzzymatching=false", // query
        ""// fragment
    };

    //-------------------- Check for whole url
    BOOST_REQUIRE(request.get_url() == full_url_alphabetic);
}

BOOST_AUTO_TEST_CASE(Selector)
{
    odil::webservices::HTTPRequest http_request(
                "GET", full_url);
    http_request.set_header("Accept", "application/dicom+json");
    odil::webservices::QIDORSRequest const request(http_request);

    //-------------------- Check for selector
    BOOST_REQUIRE_EQUAL(request.get_selector().get_path(false), "/studies/1.2/instances");
}

BOOST_AUTO_TEST_CASE(QueryDataset)
{
    odil::webservices::HTTPRequest http_request(
                "GET", full_url);
    http_request.set_header("Accept", "application/dicom+json");
    odil::webservices::QIDORSRequest const request(http_request);

    //-------------------- Check for dataSet
    odil::DataSet dataset;
    dataset.add(odil::Tag("PatientName"),{"TOTO"});
    odil::DataSet shared;
    shared.add(odil::Tag("EffectiveEchoTime"), {10.5});
    dataset.add(odil::Tag("SharedFunctionalGroupsSequence"), {shared});
    BOOST_REQUIRE(request.get_query_data_set() == dataset);
}

BOOST_AUTO_TEST_CASE(IncludeFields)
{
    odil::webservices::HTTPRequest http_request(
                "GET", full_url);
    http_request.set_header("Accept", "application/dicom+json");
    odil::webservices::QIDORSRequest const request(http_request);

    //-------------------- Check for include_fields
    std::set< std::vector < odil::Tag> > const include_fields{
        {odil::Tag("00200020")},
        {odil::Tag("52009229"), odil::Tag("00200035")}
    };
    BOOST_REQUIRE(request.get_includefields() == include_fields);
}

BOOST_AUTO_TEST_CASE(FuzzyLimitOffset)
{
    odil::webservices::HTTPRequest http_request(
                "GET", full_url);
    http_request.set_header("Accept", "application/dicom+json");
    odil::webservices::QIDORSRequest const request(http_request);

    //-------------------- Check for fuzzymatching
    BOOST_REQUIRE(request.get_fuzzymatching() == false);

    //-------------------- Check for limit - offset
    BOOST_REQUIRE(request.get_limit() == -1);
    BOOST_REQUIRE(request.get_offset() == 0);
}

BOOST_AUTO_TEST_CASE(MediaTypeJson)
{
    odil::webservices::HTTPRequest http_request(
                "GET", full_url);
    http_request.set_header("Accept", "application/dicom+json");
    odil::webservices::QIDORSRequest const request(http_request);
    BOOST_REQUIRE_EQUAL(request.get_media_type(), "application/dicom+json");
    BOOST_REQUIRE(request.get_representation() == odil::webservices::Representation::DICOM_JSON);
}

BOOST_AUTO_TEST_CASE(MediaTypeXml)
{
    odil::webservices::HTTPRequest http_request(
                "GET", full_url);
    http_request.set_header("Accept", "multipart/related;type=application/dicom+xml");
    odil::webservices::QIDORSRequest const request(http_request);
    BOOST_REQUIRE_EQUAL(request.get_media_type(), "application/dicom+xml");
    BOOST_REQUIRE(request.get_representation() == odil::webservices::Representation::DICOM_XML);
}

BOOST_AUTO_TEST_CASE(MediaTypeUnrecognized)
{
    odil::webservices::HTTPRequest http_request(
                "GET", full_url);
    http_request.set_header("Accept", "multipart/related;type=application/dicom+json");
    BOOST_REQUIRE_THROW(odil::webservices::QIDORSRequest const request(http_request),
                        odil::Exception);
}

BOOST_AUTO_TEST_CASE(RequestDataset)
{
    //-------------------- Selector
    odil::webservices::Selector selector;
    selector.set_study("1.2").set_instance("");

    //-------------------- Query Dataset
    odil::DataSet dataset;
    dataset.add(odil::Tag("PatientName"), {"TOTO"});
    odil::DataSet shared;
    shared.add(odil::Tag("StudyDate"), {20130509});
    dataset.add(odil::Tag("SharedFunctionalGroupsSequence"), {shared});

    //-------------------- IncludeFields
    std::set< std::vector < odil::Tag> > include_fields{
        {odil::Tag("00200020")},
        {odil::Tag("52009229"), odil::Tag("00200035")}
    };

    odil::webservices::QIDORSRequest request(base_url_http);
    request.request_datasets(
        odil::webservices::Representation::DICOM_XML,
        selector,
        dataset,
        include_fields
    );

    odil::webservices::URL const full_url_alphabetic_tags {
        "http", // scheme
        "example.com", // authority
        "/dicom/studies/1.2/instances", // path
        "PatientName=TOTO&"
        "SharedFunctionalGroupsSequence.StudyDate=20130509&"
        "includefield=PatientOrientation&includefield=SharedFunctionalGroupsSequence.ImageOrientation&"
        "fuzzymatching=false", // query
        ""// fragment
    };

    BOOST_REQUIRE(request.get_http_request().get_target() == full_url_alphabetic_tags);
    BOOST_REQUIRE_EQUAL(request.get_http_request().get_method(), "GET");
}

BOOST_AUTO_TEST_CASE(Equality)
{
    odil::webservices::URL const full_url_cpy {
        "http", // scheme
        "example.com", // authority
        "/dicom/studies/1.2/instances", // path
        "SharedFunctionalGroupsSequence.EffectiveEchoTime=10.5&"
        "includefield=00200020&includefield=52009229.00200035&" // query
        "PatientName=TOTO"
        ""// fragment
    };

    // The element's order within query should not be important,
    // this url and full_url must lead to the same QIDORSRequest

    odil::webservices::HTTPRequest http_request_base(
                "GET", full_url);
    http_request_base.set_header("Accept", "application/dicom+json");
    odil::webservices::QIDORSRequest const request(http_request_base);
    odil::webservices::HTTPRequest http_request_cpy(
                "GET", full_url_cpy);
    http_request_cpy.set_header("Accept", "application/dicom+json");
    odil::webservices::QIDORSRequest const request_cpy(http_request_cpy);

    BOOST_REQUIRE(request == request_cpy);
}

BOOST_AUTO_TEST_CASE(Difference)
{
    odil::webservices::URL const full_url_cpy {
        "http", // scheme
        "example.com", // authority
        "/dicom/studies/1.2/instances", // path
        "SharedFunctionalGroupsSequence.EffectiveEchoTime=10.5&"
        "includefield=00200020&includefield=52009229.00200035&" // query
        "PatientName=TUTU"
        ""// fragment
    };

    odil::webservices::HTTPRequest http_request_base(
                "GET", full_url);
    http_request_base.set_header("Accept", "application/dicom+json");
    odil::webservices::QIDORSRequest const request(http_request_base);
    odil::webservices::HTTPRequest http_request_cpy(
                "GET", full_url_cpy);
    http_request_cpy.set_header("Accept", "application/dicom+json");
    odil::webservices::QIDORSRequest const request_cpy(http_request_cpy);

    BOOST_REQUIRE(request != request_cpy);
}
