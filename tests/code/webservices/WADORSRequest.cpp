#define BOOST_TEST_MODULE WADORSRequest
#include <boost/test/unit_test.hpp>

#include "odil/registry.h"
#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/URL.h"
#include "odil/webservices/WADORS.h"
#include "odil/webservices/WADORSRequest.h"

odil::webservices::URL const base_url{"", "example.com", "/dicom", "", ""};

odil::webservices::URL const base_url_http{
    "http", "example.com", "/dicom", "", ""};

odil::webservices::WADORSRequest::Selector const instance_selector(
    "1.2", "3.4", "5.6");

odil::webservices::WADORSRequest::Selector const frames_selector(
    "1.2", "3.4", "5.6", {7,8,9});

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::webservices::WADORSRequest const request(
        base_url_http, "1.2.3.4", "latin1", true, true);
    BOOST_REQUIRE(request.get_base_url() == base_url_http);
    BOOST_REQUIRE_EQUAL(request.get_transfer_syntax(), "1.2.3.4");
    BOOST_REQUIRE_EQUAL(request.get_character_set(), "latin1");
    BOOST_REQUIRE(request.get_include_media_type_in_query());
    BOOST_REQUIRE(request.get_include_character_set_in_query());
}

BOOST_AUTO_TEST_CASE(BaseURL)
{
    odil::webservices::WADORSRequest request((odil::webservices::URL()));
    request.set_base_url(base_url_http);
    BOOST_REQUIRE(request.get_base_url() == base_url_http);
}

BOOST_AUTO_TEST_CASE(TransferSyntax)
{
    odil::webservices::WADORSRequest request((odil::webservices::URL()));
    request.set_transfer_syntax("1.2.3.4");
    BOOST_REQUIRE_EQUAL(request.get_transfer_syntax(), "1.2.3.4");
}

BOOST_AUTO_TEST_CASE(CharacterSet)
{
    odil::webservices::WADORSRequest request((odil::webservices::URL()));
    request.set_character_set("latin1");
    BOOST_REQUIRE_EQUAL(request.get_character_set(), "latin1");
}

BOOST_AUTO_TEST_CASE(IncludeMediaTypeInQuery)
{
    odil::webservices::WADORSRequest request((odil::webservices::URL()));
    request.set_include_media_type_in_query(true);
    BOOST_REQUIRE(request.get_include_media_type_in_query());
}

BOOST_AUTO_TEST_CASE(IncludeCharacterSetInQuery)
{
    odil::webservices::WADORSRequest request((odil::webservices::URL()));
    request.set_include_character_set_in_query(true);
    BOOST_REQUIRE(request.get_include_character_set_in_query());
}

BOOST_AUTO_TEST_CASE(RequestDicom)
{
    odil::webservices::WADORSRequest wado_request(base_url_http);
    wado_request.request_dicom(
        odil::webservices::WADORS::Representation::DICOM,
        instance_selector);

    BOOST_REQUIRE(
        wado_request.get_type()
            == odil::webservices::WADORS::Type::DICOM);
    BOOST_REQUIRE(wado_request.get_selector() == instance_selector);
    BOOST_REQUIRE_EQUAL(wado_request.get_media_type(), "application/dicom");
    BOOST_REQUIRE(
        wado_request.get_representation()
            == odil::webservices::WADORS::Representation::DICOM);

    auto const http_request = wado_request.get_http_request();
    BOOST_REQUIRE_EQUAL(http_request.get_method(), "GET");
    BOOST_REQUIRE_EQUAL(
        std::string(http_request.get_target()),
        std::string(base_url_http)+instance_selector.get_path(false));
    BOOST_REQUIRE(
        http_request.get_headers() == odil::webservices::HTTPRequest::Headers({
            { "Accept", "multipart/related;type=application/dicom" }
    }));
    BOOST_REQUIRE(http_request.get_body().empty());
}

BOOST_AUTO_TEST_CASE(RequestDicomXML)
{
    odil::webservices::WADORSRequest wado_request(base_url_http);
    wado_request.request_dicom(
        odil::webservices::WADORS::Representation::DICOM_XML,
        frames_selector);

    BOOST_REQUIRE(
        wado_request.get_type()
            == odil::webservices::WADORS::Type::DICOM);
    BOOST_REQUIRE(wado_request.get_selector() == frames_selector);
    BOOST_REQUIRE_EQUAL(wado_request.get_media_type(), "application/dicom+xml");
    BOOST_REQUIRE(
        wado_request.get_representation()
            == odil::webservices::WADORS::Representation::DICOM_XML);

    auto const http_request = wado_request.get_http_request();
    BOOST_REQUIRE_EQUAL(http_request.get_method(), "GET");
    BOOST_REQUIRE_EQUAL(
        std::string(http_request.get_target()),
        std::string(base_url_http)+frames_selector.get_path(true)+"/metadata");
    BOOST_REQUIRE(
        http_request.get_headers() == odil::webservices::HTTPRequest::Headers({
            { "Accept", "multipart/related;type=application/dicom+xml" }
    }));
    BOOST_REQUIRE(http_request.get_body().empty());
}

BOOST_AUTO_TEST_CASE(RequestDicomJSON)
{
    odil::webservices::WADORSRequest wado_request(base_url_http);
    wado_request.request_dicom(
        odil::webservices::WADORS::Representation::DICOM_JSON,
        frames_selector);

    BOOST_REQUIRE(
        wado_request.get_type()
            == odil::webservices::WADORS::Type::DICOM);
    BOOST_REQUIRE(wado_request.get_selector() == frames_selector);
    BOOST_REQUIRE_EQUAL(wado_request.get_media_type(), "application/dicom+json");
    BOOST_REQUIRE(
        wado_request.get_representation()
            == odil::webservices::WADORS::Representation::DICOM_JSON);

    auto const http_request = wado_request.get_http_request();
    BOOST_REQUIRE_EQUAL(http_request.get_method(), "GET");
    BOOST_REQUIRE_EQUAL(
        std::string(http_request.get_target()),
        std::string(base_url_http)+frames_selector.get_path(true)+"/metadata");
    BOOST_REQUIRE(
        http_request.get_headers() == odil::webservices::HTTPRequest::Headers({
            { "Accept", "multipart/related;type=application/dicom+json" }
    }));
    BOOST_REQUIRE(http_request.get_body().empty());
}

BOOST_AUTO_TEST_CASE(RequestBulkDataAll)
{
    odil::webservices::WADORSRequest wado_request(base_url_http);
    wado_request.request_bulk_data(frames_selector);

    BOOST_REQUIRE(
        wado_request.get_type()
            == odil::webservices::WADORS::Type::BulkData);
    BOOST_REQUIRE(wado_request.get_selector() == frames_selector);
    BOOST_REQUIRE_EQUAL(wado_request.get_media_type(), "application/octet-stream");

    auto const http_request = wado_request.get_http_request();
    BOOST_REQUIRE_EQUAL(http_request.get_method(), "GET");
    BOOST_REQUIRE_EQUAL(
        std::string(http_request.get_target()),
        std::string(base_url_http)+frames_selector.get_path(true));
    BOOST_REQUIRE(
        http_request.get_headers() == odil::webservices::HTTPRequest::Headers({
            { "Accept", "multipart/related;type=application/octet-stream" }
    }));
    BOOST_REQUIRE(http_request.get_body().empty());
}

BOOST_AUTO_TEST_CASE(RequestBulkDataSingle)
{
    odil::webservices::WADORSRequest wado_request(odil::webservices::URL{});
    wado_request.request_bulk_data({
        "http", "example.com",
        "/dicom"+frames_selector.get_path(true)+"/bulk/7fe00010",
        "", ""});

    BOOST_REQUIRE(
        wado_request.get_type()
            == odil::webservices::WADORS::Type::BulkData);
    BOOST_REQUIRE_EQUAL(wado_request.get_media_type(), "application/octet-stream");

    auto const http_request = wado_request.get_http_request();
    BOOST_REQUIRE_EQUAL(http_request.get_method(), "GET");
    BOOST_REQUIRE_EQUAL(
        std::string(http_request.get_target()),
        std::string(base_url_http)+frames_selector.get_path(true)+"/bulk/7fe00010");
    BOOST_REQUIRE(
        http_request.get_headers() == odil::webservices::HTTPRequest::Headers({
            { "Accept", "multipart/related;type=application/octet-stream" }
    }));
    BOOST_REQUIRE(http_request.get_body().empty());
}

BOOST_AUTO_TEST_CASE(RequestPixelData)
{
    odil::webservices::WADORSRequest wado_request(base_url_http);
    wado_request.request_pixel_data(frames_selector, "image/jpeg");

    BOOST_REQUIRE(
        wado_request.get_type()
            == odil::webservices::WADORS::Type::PixelData);
    BOOST_REQUIRE(wado_request.get_selector() == frames_selector);
    BOOST_REQUIRE_EQUAL(wado_request.get_media_type(), "image/jpeg");

    auto const http_request = wado_request.get_http_request();
    BOOST_REQUIRE_EQUAL(http_request.get_method(), "GET");
    BOOST_REQUIRE_EQUAL(
        std::string(http_request.get_target()),
        std::string(base_url_http)+frames_selector.get_path(true));
    BOOST_REQUIRE(
        http_request.get_headers() == odil::webservices::HTTPRequest::Headers({
            { "Accept", "multipart/related;type=image/jpeg" }
    }));
    BOOST_REQUIRE(http_request.get_body().empty());
}

BOOST_AUTO_TEST_CASE(ParseRequestTransferSyntaxDefault)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", { "", "", "/studies/1.2", "", "" },
        "HTTP/1.1",
        { { "Accept", "multipart/related;type=application/dicom" } },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE_EQUAL(
        wado_request.get_transfer_syntax(),
        odil::registry::ExplicitVRLittleEndian);
    BOOST_REQUIRE(!wado_request.get_include_media_type_in_query());
}

BOOST_AUTO_TEST_CASE(ParseRequestTransferSyntaxHeader)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", { "", "", "/studies/1.2", "", "" },
        "HTTP/1.1",
        { { "Accept", "multipart/related;type=application/dicom;transfer-syntax=3.4" } },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE_EQUAL(wado_request.get_transfer_syntax(), "3.4");
    BOOST_REQUIRE(!wado_request.get_include_media_type_in_query());
}

BOOST_AUTO_TEST_CASE(ParseRequestTransferSyntaxQuery)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", {
            "", "", "/studies/1.2",
            "accept=multipart/related;type=application/dicom;transfer-syntax=3.4",
            "" },
        "HTTP/1.1",
        { { "Accept", "multipart/related;type=application/dicom" } },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE_EQUAL(wado_request.get_transfer_syntax(), "3.4");
    BOOST_REQUIRE(wado_request.get_include_media_type_in_query());
}

BOOST_AUTO_TEST_CASE(ParseRequestTransferSyntaxBoth)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", {
            "", "", "/studies/1.2",
            "accept=multipart/related;type=application/dicom;transfer-syntax=3.4",
            "" },
        "HTTP/1.1",
        { { "Accept", "multipart/related;type=application/dicom;transfer-syntax=5.6" } },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE_EQUAL(wado_request.get_transfer_syntax(), "5.6");
    BOOST_REQUIRE(wado_request.get_include_media_type_in_query());
}

BOOST_AUTO_TEST_CASE(ParseRequestCharacterSetDefault)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", { "", "", "/studies/1.2", "", "" },
        "HTTP/1.1",
        { { "Accept", "multipart/related;type=application/dicom" } },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE_EQUAL(wado_request.get_character_set(), "UTF-8");
    BOOST_REQUIRE(!wado_request.get_include_character_set_in_query());
}

BOOST_AUTO_TEST_CASE(ParseRequestCharacterSetAcceptCharsetHeader)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", { "", "", "/studies/1.2", "", "" },
        "HTTP/1.1",
        {
            { "Accept", "multipart/related;type=application/dicom" },
            { "AcceptCharset", "ISO-8859-1" }
        },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE_EQUAL(wado_request.get_character_set(), "ISO-8859-1");
    BOOST_REQUIRE(!wado_request.get_include_character_set_in_query());
}

BOOST_AUTO_TEST_CASE(ParseRequestCharacterSetAcceptHeader)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", { "", "", "/studies/1.2", "", "" },
        "HTTP/1.1",
        {
            { "Accept", "multipart/related;type=application/dicom;charset=ISO-8859-1" }
        },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE_EQUAL(wado_request.get_character_set(), "ISO-8859-1");
    BOOST_REQUIRE(!wado_request.get_include_character_set_in_query());
}

BOOST_AUTO_TEST_CASE(ParseRequestCharacterSetQuery)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", { "", "", "/studies/1.2", "charset=ISO-8859-1", "" },
        "HTTP/1.1",
        { { "Accept", "multipart/related;type=application/dicom" } },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE_EQUAL(wado_request.get_character_set(), "ISO-8859-1");
    BOOST_REQUIRE(wado_request.get_include_character_set_in_query());
}

BOOST_AUTO_TEST_CASE(ParseRequestCharacterSetAll)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", { "", "", "/studies/1.2", "charset=ISO-8859-1", "" },
        "HTTP/1.1",
        {
            { "Accept", "multipart/related;type=application/dicom;charset=ISO-8859-2" },
            { "AcceptCharset", "ISO-8859-3" }
        },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE_EQUAL(wado_request.get_character_set(), "ISO-8859-2");
    BOOST_REQUIRE(wado_request.get_include_character_set_in_query());
}

BOOST_AUTO_TEST_CASE(ParseRequestAcceptAndCharacterSetInQuery)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", {
            "", "", "/studies/1.2",
            "charset=ISO-8859-1&"
                "accept=multipart/related;type=application/dicom;transfer-syntax=3.4",
            "" },
        "HTTP/1.1",
        { { "Accept", "multipart/related;type=application/dicom" } },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE_EQUAL(wado_request.get_transfer_syntax(), "3.4");
    BOOST_REQUIRE_EQUAL(wado_request.get_character_set(), "ISO-8859-1");
    BOOST_REQUIRE(wado_request.get_include_media_type_in_query());
    BOOST_REQUIRE(wado_request.get_include_character_set_in_query());
}

BOOST_AUTO_TEST_CASE(ParseRequestDICOM)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", { "", "", "/dicom"+instance_selector.get_path(false), "", "" },
        "HTTP/1.1", {
            { "Host", "example.com" },
            { "Accept", "multipart/related;type=application/dicom" }
        },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE(wado_request.get_base_url() == base_url);
    BOOST_REQUIRE(
        wado_request.get_type()
            == odil::webservices::WADORS::Type::DICOM);
    BOOST_REQUIRE(wado_request.get_selector() == instance_selector);
    BOOST_REQUIRE_EQUAL(wado_request.get_media_type(), "application/dicom");
    BOOST_REQUIRE(
        wado_request.get_representation()
            == odil::webservices::WADORS::Representation::DICOM);
}

BOOST_AUTO_TEST_CASE(ParseRequestDICOM_XML)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", { "", "", "/dicom"+frames_selector.get_path(true), "", "" },
        "HTTP/1.1", {
            { "Host", "example.com" },
            { "Accept", "multipart/related;type=application/dicom+xml" }
        },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE(wado_request.get_base_url() == base_url);
    BOOST_REQUIRE(
        wado_request.get_type()
            == odil::webservices::WADORS::Type::DICOM);
    BOOST_REQUIRE(wado_request.get_selector() == frames_selector);
    BOOST_REQUIRE_EQUAL(wado_request.get_media_type(), "application/dicom+xml");
    BOOST_REQUIRE(
        wado_request.get_representation()
            == odil::webservices::WADORS::Representation::DICOM_XML);
}

BOOST_AUTO_TEST_CASE(ParseRequestDICOM_JSON)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", { "", "", "/dicom"+frames_selector.get_path(true), "", "" },
        "HTTP/1.1", {
            { "Host", "example.com" },
            { "Accept", "multipart/related;type=application/dicom+json" }
        },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE(wado_request.get_base_url() == base_url);
    BOOST_REQUIRE(
        wado_request.get_type()
            == odil::webservices::WADORS::Type::DICOM);
    BOOST_REQUIRE(wado_request.get_selector() == frames_selector);
    BOOST_REQUIRE_EQUAL(wado_request.get_media_type(), "application/dicom+json");
    BOOST_REQUIRE(
        wado_request.get_representation()
            == odil::webservices::WADORS::Representation::DICOM_JSON);
}

BOOST_AUTO_TEST_CASE(ParseRequestBulkDataSingle)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", {
            "", "", "/dicom"+instance_selector.get_path(false)+"/7fe00010",
            "", "" },
        "HTTP/1.1", {
            { "Host", "example.com" },
            { "Accept", "multipart/related;type=application/octet-stream" }
        },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE(
        wado_request.get_url()
            == odil::webservices::URL({
                "", "example.com",
                "/dicom"+instance_selector.get_path(false)+"/7fe00010",
                "", "" }));
    BOOST_REQUIRE(
        wado_request.get_type()
            == odil::webservices::WADORS::Type::BulkData);
    BOOST_REQUIRE(wado_request.get_selector() == instance_selector);
    BOOST_REQUIRE_EQUAL(wado_request.get_media_type(), "application/octet-stream");
}

BOOST_AUTO_TEST_CASE(ParseRequestBulkDataAll)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", { "", "", "/dicom"+instance_selector.get_path(false), "", "" },
        "HTTP/1.1", {
            { "Host", "example.com" },
            { "Accept", "multipart/related;type=application/octet-stream" }
        },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE(wado_request.get_base_url() == base_url);
    BOOST_REQUIRE(
        wado_request.get_type()
            == odil::webservices::WADORS::Type::BulkData);
    BOOST_REQUIRE(wado_request.get_selector() == instance_selector);
    BOOST_REQUIRE_EQUAL(wado_request.get_media_type(), "application/octet-stream");
}

BOOST_AUTO_TEST_CASE(ParseRequestPixelDataUncompressed)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", { "", "", "/dicom"+frames_selector.get_path(true), "", "" },
        "HTTP/1.1", {
            { "Host", "example.com" },
            { "Accept", "multipart/related;type=application/octet-stream" }
        },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE(wado_request.get_base_url() == base_url);
    BOOST_REQUIRE(
        wado_request.get_type()
            == odil::webservices::WADORS::Type::BulkData);
    BOOST_REQUIRE(wado_request.get_selector() == frames_selector);
    BOOST_REQUIRE_EQUAL(wado_request.get_media_type(), "application/octet-stream");
}

BOOST_AUTO_TEST_CASE(ParseRequestPixelDataCompressed)
{
    odil::webservices::HTTPRequest const http_request(
        "GET", { "", "", "/dicom"+frames_selector.get_path(true), "", "" },
        "HTTP/1.1", {
            { "Host", "example.com" },
            { "Accept", "multipart/related;type=image/jpeg" }
        },
        "");
    odil::webservices::WADORSRequest const wado_request(http_request);

    BOOST_REQUIRE(wado_request.get_base_url() == base_url);
    BOOST_REQUIRE(
        wado_request.get_type()
            == odil::webservices::WADORS::Type::PixelData);
    BOOST_REQUIRE(wado_request.get_selector() == frames_selector);
    BOOST_REQUIRE_EQUAL(wado_request.get_media_type(), "image/jpeg");
}
