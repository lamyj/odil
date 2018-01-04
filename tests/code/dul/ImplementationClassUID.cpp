#define BOOST_TEST_MODULE ImplementationClassUID
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "odil/pdu/ImplementationClassUID.h"

std::string const data(
    "\x52\x00\x00\x03"
    "foo",
    7
);

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::pdu::ImplementationClassUID const item("foo");
    BOOST_REQUIRE_EQUAL(item.get_implementation_class_uid(), "foo");
}

BOOST_AUTO_TEST_CASE(FromStream)
{
    std::istringstream stream(data);
    odil::pdu::ImplementationClassUID const item(stream);

    BOOST_REQUIRE_EQUAL(item.get_implementation_class_uid(), "foo");
}

BOOST_AUTO_TEST_CASE(ImplementationClassUID)
{
    odil::pdu::ImplementationClassUID item("foo");
    item.set_implementation_class_uid("bar");
    BOOST_REQUIRE_EQUAL(item.get_implementation_class_uid(), "bar");
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::pdu::ImplementationClassUID const item("foo");
    std::ostringstream stream;
    stream << item;

    BOOST_REQUIRE_EQUAL(stream.str(), data);
}
