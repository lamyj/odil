#define BOOST_TEST_MODULE ImplementationVersionName
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "odil/Exception.h"
#include "odil/pdu/ImplementationVersionName.h"

std::string const data(
    "\x55\x00\x00\x03"
    "foo",
    7
);

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::pdu::ImplementationVersionName const item("foo");
    BOOST_REQUIRE_EQUAL(item.get_implementation_version_name(), "foo");
}

BOOST_AUTO_TEST_CASE(FromStream)
{
    std::istringstream stream(data);
    odil::pdu::ImplementationVersionName const item(stream);

    BOOST_REQUIRE_EQUAL(item.get_implementation_version_name(), "foo");
}

BOOST_AUTO_TEST_CASE(VersionName)
{
    odil::pdu::ImplementationVersionName item("foo");
    item.set_implementation_version_name("bar");
    BOOST_REQUIRE_EQUAL(item.get_implementation_version_name(), "bar");
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::pdu::ImplementationVersionName const item("foo");
    std::ostringstream stream;
    stream << item;

    BOOST_REQUIRE_EQUAL(stream.str(), data);
}

BOOST_AUTO_TEST_CASE(Empty)
{
    odil::pdu::ImplementationVersionName item("foo");
    BOOST_REQUIRE_THROW(
        item.set_implementation_version_name(""), odil::Exception);
}

BOOST_AUTO_TEST_CASE(TooLong)
{
    odil::pdu::ImplementationVersionName item("foo");
    BOOST_REQUIRE_THROW(
        item.set_implementation_version_name("1234567890abcdef01"),
        odil::Exception);
}
