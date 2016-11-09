#define BOOST_TEST_MODULE Message
#include <boost/test/unit_test.hpp>

#include <sstream>

#include <odil/Exception.h>
#include <odil/webservices/Message.h>

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    odil::webservices::Message const message;
    BOOST_REQUIRE(message.get_headers().empty());
    BOOST_REQUIRE(message.get_body().empty());
}

BOOST_AUTO_TEST_CASE(OneParameterConstructor)
{
    odil::webservices::Message const message(
        odil::webservices::Message::Headers{{"foo", "bar"}, {"plip", "plop"}});
    BOOST_REQUIRE(
        message.get_headers()
            == odil::webservices::Message::Headers(
                {{"foo", "bar"}, {"plip", "plop"}}));
    BOOST_REQUIRE(message.get_body().empty());
}

BOOST_AUTO_TEST_CASE(TwoParametersConstructor)
{
    odil::webservices::Message const message(
        odil::webservices::Message::Headers{{"foo", "bar"}, {"plip", "plop"}},
        "body");
    BOOST_REQUIRE(
        message.get_headers()
            == odil::webservices::Message::Headers(
                {{"foo", "bar"}, {"plip", "plop"}}));
    BOOST_REQUIRE_EQUAL(message.get_body(), "body");
}

BOOST_AUTO_TEST_CASE(Headers)
{
    odil::webservices::Message message;
    message.set_headers({{"foo", "bar"}, {"plip", "plop"}});

    BOOST_REQUIRE(
        message.get_headers()
            == odil::webservices::Message::Headers(
                {{"foo", "bar"}, {"plip", "plop"}}));

    BOOST_REQUIRE(message.has_header("foo"));
    BOOST_REQUIRE(message.has_header("FoO"));
    BOOST_REQUIRE(!message.has_header("bar"));

    BOOST_REQUIRE_EQUAL(message.get_header("foo"), "bar");
    BOOST_REQUIRE_EQUAL(message.get_header("FoO"), "bar");
    BOOST_REQUIRE_THROW(message.get_header("bar"), odil::Exception);

    message.set_header("foo", "other");
    BOOST_REQUIRE_EQUAL(message.get_header("foo"), "other");
}

BOOST_AUTO_TEST_CASE(Body)
{
    odil::webservices::Message message;
    message.set_body("body");
    BOOST_REQUIRE_EQUAL(message.get_body(), "body");
}

BOOST_AUTO_TEST_CASE(Input)
{
    std::stringstream stream(
        "From: John Doe <jdoe@machine.example>\r\n"
        "To: Mary Smith <mary@example.net>\r\n"
        "Subject: Saying Hello\r\n"
        "Date: Fri, 21 Nov 1997 09:55:06 -0600\r\n"
        "Message-ID: <1234@local.machine.example>\r\n"
        "\r\n"
        "This is a message just to say hello.\r\n"
        "So, \"Hello\".\r\n");
    odil::webservices::Message message;
    stream >> message;

    BOOST_REQUIRE(
        message.get_headers()
            == odil::webservices::Message::Headers({
                {"From", "John Doe <jdoe@machine.example>"},
                {"To", "Mary Smith <mary@example.net>"},
                {"Subject", "Saying Hello"},
                {"Date", "Fri, 21 Nov 1997 09:55:06 -0600"},
                {"Message-ID", "<1234@local.machine.example>"}
    }));
    BOOST_REQUIRE_EQUAL(
        message.get_body(),
        "This is a message just to say hello.\r\n"
        "So, \"Hello\".\r\n");
}

BOOST_AUTO_TEST_CASE(Output)
{
    odil::webservices::Message const message{
        {
            {"From", "John Doe <jdoe@machine.example>"},
            {"To", "Mary Smith <mary@example.net>"},
            {"Subject", "Saying Hello"},
            {"Date", "Fri, 21 Nov 1997 09:55:06 -0600"},
            {"Message-ID", "<1234@local.machine.example>"}
        },
        "This is a message just to say hello.\r\n"
        "So, \"Hello\".\r\n"
    };

    std::stringstream stream;
    stream << message;

    odil::webservices::Message result;
    stream >> result;

    BOOST_REQUIRE(message.get_headers() == result.get_headers());
    BOOST_REQUIRE_EQUAL(message.get_body(), result.get_body());
}
