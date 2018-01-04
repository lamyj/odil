#define BOOST_TEST_MODULE ApplicationContext
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "odil/Exception.h"
#include "odil/dul/ApplicationContext.h"

std::string const data(
    "\x10\x00\x00\x03"
    "foo",
    7
);

BOOST_AUTO_TEST_CASE(FromString)
{
    odil::dul::ApplicationContext const context("foo");
    BOOST_REQUIRE_EQUAL(context.get_name(), "foo");
}

BOOST_AUTO_TEST_CASE(FromStream)
{
    std::istringstream stream(data);

    odil::dul::ApplicationContext const context(stream);
    BOOST_REQUIRE_EQUAL(context.get_name(), "foo");
}

BOOST_AUTO_TEST_CASE(Name)
{
    odil::dul::ApplicationContext context("foo");
    context.set_name("other");
    BOOST_REQUIRE_EQUAL(context.get_name(), "other");
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::dul::ApplicationContext const context("foo");
    std::ostringstream stream;
    stream << context;

    BOOST_REQUIRE_EQUAL(stream.str(), data);
}
