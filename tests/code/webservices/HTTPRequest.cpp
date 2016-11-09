#define BOOST_TEST_MODULE Message
#include <boost/test/unit_test.hpp>

#include <sstream>

#include <odil/Exception.h>
#include <odil/webservices/HTTPRequest.h>

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    odil::webservices::HTTPRequest const request;
    BOOST_REQUIRE(request.get_method().empty());
    BOOST_REQUIRE(request.get_target().empty());
    BOOST_REQUIRE_EQUAL(request.get_http_version(), "HTTP/1.0");
    BOOST_REQUIRE(request.get_headers().empty());
    BOOST_REQUIRE(request.get_body().empty());
}

BOOST_AUTO_TEST_CASE(OneParameterConstructor)
{
    odil::webservices::HTTPRequest const request("GET");
    BOOST_REQUIRE_EQUAL(request.get_method(), "GET");
    BOOST_REQUIRE(request.get_target().empty());
    BOOST_REQUIRE_EQUAL(request.get_http_version(), "HTTP/1.0");
    BOOST_REQUIRE(request.get_headers().empty());
    BOOST_REQUIRE(request.get_body().empty());
}

BOOST_AUTO_TEST_CASE(TwoParameterConstructor)
{
    odil::webservices::HTTPRequest const request("GET", "/foo");
    BOOST_REQUIRE_EQUAL(request.get_method(), "GET");
    BOOST_REQUIRE_EQUAL(request.get_target(), "/foo");
    BOOST_REQUIRE_EQUAL(request.get_http_version(), "HTTP/1.0");
    BOOST_REQUIRE(request.get_headers().empty());
    BOOST_REQUIRE(request.get_body().empty());
}

BOOST_AUTO_TEST_CASE(ThreeParameterConstructor)
{
    odil::webservices::HTTPRequest const request("GET", "/foo", "HTTP/1.1");
    BOOST_REQUIRE_EQUAL(request.get_method(), "GET");
    BOOST_REQUIRE_EQUAL(request.get_target(), "/foo");
    BOOST_REQUIRE_EQUAL(request.get_http_version(), "HTTP/1.1");
    BOOST_REQUIRE(request.get_headers().empty());
    BOOST_REQUIRE(request.get_body().empty());
}

BOOST_AUTO_TEST_CASE(FourParameterConstructor)
{
    odil::webservices::HTTPRequest const request(
        "GET", "/foo", "HTTP/1.1", {{"foo", "bar"}, {"plip", "plop"}});
    BOOST_REQUIRE_EQUAL(request.get_method(), "GET");
    BOOST_REQUIRE_EQUAL(request.get_target(), "/foo");
    BOOST_REQUIRE_EQUAL(request.get_http_version(), "HTTP/1.1");
    BOOST_REQUIRE(
        request.get_headers()
            == odil::webservices::Message::Headers(
                {{"foo", "bar"}, {"plip", "plop"}}));
    BOOST_REQUIRE(request.get_body().empty());
}

BOOST_AUTO_TEST_CASE(FiveParametersConstructor)
{
    odil::webservices::HTTPRequest const request(
        "GET", "/foo", "HTTP/1.1", {{"foo", "bar"}, {"plip", "plop"}}, "body");
    BOOST_REQUIRE_EQUAL(request.get_method(), "GET");
    BOOST_REQUIRE_EQUAL(request.get_target(), "/foo");
    BOOST_REQUIRE_EQUAL(request.get_http_version(), "HTTP/1.1");
    BOOST_REQUIRE(
        request.get_headers()
            == odil::webservices::Message::Headers(
                {{"foo", "bar"}, {"plip", "plop"}}));
    BOOST_REQUIRE_EQUAL(request.get_body(), "body");
}

BOOST_AUTO_TEST_CASE(Method)
{
    odil::webservices::HTTPRequest request;
    request.set_method("GET");
    BOOST_REQUIRE_EQUAL(request.get_method(), "GET");
}

BOOST_AUTO_TEST_CASE(Target)
{
    odil::webservices::HTTPRequest request;
    request.set_target("/foo");
    BOOST_REQUIRE_EQUAL(request.get_target(), "/foo");
}

BOOST_AUTO_TEST_CASE(HTTPVersion)
{
    odil::webservices::HTTPRequest request;
    request.set_http_version("HTTP/1.1");
    BOOST_REQUIRE_EQUAL(request.get_http_version(), "HTTP/1.1");
}

BOOST_AUTO_TEST_CASE(Headers)
{
    odil::webservices::HTTPRequest request;
    request.set_headers({{"foo", "bar"}, {"plip", "plop"}});

    BOOST_REQUIRE(
        request.get_headers()
            == odil::webservices::Message::Headers(
                {{"foo", "bar"}, {"plip", "plop"}}));

    BOOST_REQUIRE(request.has_header("foo"));
    BOOST_REQUIRE(request.has_header("FoO"));
    BOOST_REQUIRE(!request.has_header("bar"));

    BOOST_REQUIRE_EQUAL(request.get_header("foo"), "bar");
    BOOST_REQUIRE_EQUAL(request.get_header("FoO"), "bar");
    BOOST_REQUIRE_THROW(request.get_header("bar"), odil::Exception);

    request.set_header("foo", "other");
    BOOST_REQUIRE_EQUAL(request.get_header("foo"), "other");
}

BOOST_AUTO_TEST_CASE(Body)
{
    odil::webservices::HTTPRequest request;
    request.set_body("body");
    BOOST_REQUIRE_EQUAL(request.get_body(), "body");
}

BOOST_AUTO_TEST_CASE(Input)
{
    std::stringstream stream(
        "POST /foo HTTP/1.1\r\n"
        "Host: www.example.com\r\n"
        "Content-Type: application/json\r\n"
        "\r\n"
        "{ }\r\n"
        "\r\n");
    odil::webservices::HTTPRequest request;
    stream >> request;

    BOOST_REQUIRE_EQUAL(request.get_method(), "POST");
    BOOST_REQUIRE_EQUAL(request.get_target(), "/foo");
    BOOST_REQUIRE_EQUAL(request.get_http_version(), "HTTP/1.1");
    BOOST_REQUIRE(
        request.get_headers()
            == odil::webservices::Message::Headers({
                {"Host", "www.example.com"},
                {"Content-Type", "application/json"}
    }));
    BOOST_REQUIRE_EQUAL(request.get_body(), "{ }\r\n\r\n");
}

BOOST_AUTO_TEST_CASE(Output)
{
    odil::webservices::HTTPRequest const request{
        "POST", "/foo", "HTTP/1.1",
        {
            {"Host", "www.example.com"},
            {"Content-Type", "application/json"}
        },
        "{ }\r\n\r\n"
    };

    std::stringstream stream;
    stream << request;

    odil::webservices::HTTPRequest result;
    stream >> result;

    BOOST_REQUIRE_EQUAL(request.get_method(), result.get_method());
    BOOST_REQUIRE_EQUAL(request.get_target(), result.get_target());
    BOOST_REQUIRE_EQUAL(request.get_http_version(), result.get_http_version());
    BOOST_REQUIRE(request.get_headers() == result.get_headers());
    BOOST_REQUIRE_EQUAL(request.get_body(), result.get_body());
}
