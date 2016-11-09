#define BOOST_TEST_MODULE Message
#include <boost/test/unit_test.hpp>

#include <sstream>

#include <odil/Exception.h>
#include <odil/webservices/HTTPResponse.h>

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    odil::webservices::HTTPResponse const response;
    BOOST_REQUIRE_EQUAL(response.get_http_version(), "");
    BOOST_REQUIRE_EQUAL(response.get_status(), 0);
    BOOST_REQUIRE(response.get_reason().empty());
    BOOST_REQUIRE(response.get_headers().empty());
    BOOST_REQUIRE(response.get_body().empty());
}

BOOST_AUTO_TEST_CASE(OneParameterConstructor)
{
    odil::webservices::HTTPResponse const response("HTTP/1.0");
    BOOST_REQUIRE_EQUAL(response.get_http_version(), "HTTP/1.0");
    BOOST_REQUIRE_EQUAL(response.get_status(), 0);
    BOOST_REQUIRE(response.get_reason().empty());
    BOOST_REQUIRE(response.get_headers().empty());
    BOOST_REQUIRE(response.get_body().empty());
}

BOOST_AUTO_TEST_CASE(TwoParameterConstructor)
{
    odil::webservices::HTTPResponse const response("HTTP/1.0", 200);
    BOOST_REQUIRE_EQUAL(response.get_http_version(), "HTTP/1.0");
    BOOST_REQUIRE_EQUAL(response.get_status(), 200);
    BOOST_REQUIRE(response.get_reason().empty());
    BOOST_REQUIRE(response.get_headers().empty());
    BOOST_REQUIRE(response.get_body().empty());
}

BOOST_AUTO_TEST_CASE(ThreeParameterConstructor)
{
    odil::webservices::HTTPResponse const response("HTTP/1.0", 200, "OK");
    BOOST_REQUIRE_EQUAL(response.get_http_version(), "HTTP/1.0");
    BOOST_REQUIRE_EQUAL(response.get_status(), 200);
    BOOST_REQUIRE_EQUAL(response.get_reason(), "OK");
    BOOST_REQUIRE(response.get_headers().empty());
    BOOST_REQUIRE(response.get_body().empty());
}

BOOST_AUTO_TEST_CASE(FourParameterConstructor)
{
    odil::webservices::HTTPResponse const response(
        "HTTP/1.0", 200, "OK", {{"foo", "bar"}, {"plip", "plop"}});
    BOOST_REQUIRE_EQUAL(response.get_http_version(), "HTTP/1.0");
    BOOST_REQUIRE_EQUAL(response.get_status(), 200);
    BOOST_REQUIRE_EQUAL(response.get_reason(), "OK");
    BOOST_REQUIRE(
        response.get_headers()
            == odil::webservices::Message::Headers(
                {{"foo", "bar"}, {"plip", "plop"}}));
    BOOST_REQUIRE(response.get_body().empty());
}

BOOST_AUTO_TEST_CASE(FiveParametersConstructor)
{
    odil::webservices::HTTPResponse const response(
        "HTTP/1.0", 200, "OK", {{"foo", "bar"}, {"plip", "plop"}}, "body");
    BOOST_REQUIRE_EQUAL(response.get_http_version(), "HTTP/1.0");
    BOOST_REQUIRE_EQUAL(response.get_status(), 200);
    BOOST_REQUIRE_EQUAL(response.get_reason(), "OK");
    BOOST_REQUIRE(
        response.get_headers()
            == odil::webservices::Message::Headers(
                {{"foo", "bar"}, {"plip", "plop"}}));
    BOOST_REQUIRE_EQUAL(response.get_body(), "body");
}

BOOST_AUTO_TEST_CASE(HTTPVersion)
{
    odil::webservices::HTTPResponse response;
    response.set_http_version("HTTP/1.1");
    BOOST_REQUIRE_EQUAL(response.get_http_version(), "HTTP/1.1");
}

BOOST_AUTO_TEST_CASE(Status)
{
    odil::webservices::HTTPResponse response;
    response.set_status(200);
    BOOST_REQUIRE_EQUAL(response.get_status(), 200);
}

BOOST_AUTO_TEST_CASE(Reason)
{
    odil::webservices::HTTPResponse response;
    response.set_reason("OK");
    BOOST_REQUIRE_EQUAL(response.get_reason(), "OK");
}

BOOST_AUTO_TEST_CASE(Headers)
{
    odil::webservices::HTTPResponse response;
    response.set_headers({{"foo", "bar"}, {"plip", "plop"}});

    BOOST_REQUIRE(
        response.get_headers()
            == odil::webservices::Message::Headers(
                {{"foo", "bar"}, {"plip", "plop"}}));

    BOOST_REQUIRE(response.has_header("foo"));
    BOOST_REQUIRE(response.has_header("FoO"));
    BOOST_REQUIRE(!response.has_header("bar"));

    BOOST_REQUIRE_EQUAL(response.get_header("foo"), "bar");
    BOOST_REQUIRE_EQUAL(response.get_header("FoO"), "bar");
    BOOST_REQUIRE_THROW(response.get_header("bar"), odil::Exception);

    response.set_header("foo", "other");
    BOOST_REQUIRE_EQUAL(response.get_header("foo"), "other");
}

BOOST_AUTO_TEST_CASE(Body)
{
    odil::webservices::HTTPResponse response;
    response.set_body("body");
    BOOST_REQUIRE_EQUAL(response.get_body(), "body");
}

BOOST_AUTO_TEST_CASE(Input)
{
    std::stringstream stream(
        "HTTP/1.1 200 OK\r\n"
        "Content-Encoding: utf-8\r\n"
        "Content-Type: application/json\r\n"
        "\r\n"
        "{ }\r\n"
        "\r\n");
    odil::webservices::HTTPResponse response;
    stream >> response;

    BOOST_REQUIRE_EQUAL(response.get_http_version(), "HTTP/1.1");
    BOOST_REQUIRE_EQUAL(response.get_status(), 200);
    BOOST_REQUIRE_EQUAL(response.get_reason(), "OK");
    BOOST_REQUIRE(
        response.get_headers()
            == odil::webservices::Message::Headers({
                {"Content-Encoding", "utf-8"},
                {"Content-Type", "application/json"}
    }));
    BOOST_REQUIRE_EQUAL(response.get_body(), "{ }\r\n\r\n");
}

BOOST_AUTO_TEST_CASE(Output)
{
    odil::webservices::HTTPResponse const response{
        "HTTP/1.1", 200, "OK",
        {
            {"Content-Encoding", "utf-8"},
            {"Content-Type", "application/json"}
        },
        "{ }\r\n\r\n"
    };

    std::stringstream stream;
    stream << response;

    odil::webservices::HTTPResponse result;
    stream >> result;

    BOOST_REQUIRE_EQUAL(response.get_http_version(), result.get_http_version());
    BOOST_REQUIRE_EQUAL(response.get_status(), result.get_status());
    BOOST_REQUIRE_EQUAL(response.get_reason(), result.get_reason());
    BOOST_REQUIRE(response.get_headers() == result.get_headers());
    BOOST_REQUIRE_EQUAL(response.get_body(), result.get_body());
}
