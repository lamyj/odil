#define BOOST_TEST_MODULE ApplicationContext
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/pdu/ApplicationContext.h"

BOOST_AUTO_TEST_CASE(FromString)
{
    dcmtkpp::pdu::ApplicationContext const context("foo");
    BOOST_REQUIRE_EQUAL(context.get_name(), "foo");
}

BOOST_AUTO_TEST_CASE(FromStream)
{
    std::string const data(
        "\x10\x00\x00\x04"
        "foo\0",
        8
    );
    std::istringstream stream(data);

    dcmtkpp::pdu::ApplicationContext const context(stream);
    BOOST_REQUIRE_EQUAL(context.get_name(), "foo");
}

BOOST_AUTO_TEST_CASE(Name)
{
    dcmtkpp::pdu::ApplicationContext context("foo");
    context.set_name("other");
    BOOST_REQUIRE_EQUAL(context.get_name(), "other");
}

BOOST_AUTO_TEST_CASE(Write)
{
    dcmtkpp::pdu::ApplicationContext const context("foo");
    std::ostringstream data;
    data << context;

    std::string const expected(
        "\x10\x00\x00\x04"
        "foo\0",
        8
    );

    BOOST_REQUIRE_EQUAL(data.str(), expected);
}
