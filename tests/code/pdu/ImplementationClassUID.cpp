#define BOOST_TEST_MODULE ImplementationClassUID
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/pdu/ImplementationClassUID.h"

std::string const data(
    "\x52\x00\x00\x03"
    "foo",
    7
);

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::pdu::ImplementationClassUID const item("foo");
    BOOST_REQUIRE_EQUAL(item.get_implementation_class_uid(), "foo");
}

BOOST_AUTO_TEST_CASE(FromStream)
{
    std::istringstream stream(data);
    dcmtkpp::pdu::ImplementationClassUID const item(stream);

    BOOST_REQUIRE_EQUAL(item.get_implementation_class_uid(), "foo");
}

BOOST_AUTO_TEST_CASE(MaximumLength)
{
    dcmtkpp::pdu::ImplementationClassUID item("foo");
    item.set_implementation_class_uid("bar");
    BOOST_REQUIRE_EQUAL(item.get_implementation_class_uid(), "bar");
}

BOOST_AUTO_TEST_CASE(Write)
{
    dcmtkpp::pdu::ImplementationClassUID const item("foo");
    std::ostringstream stream;
    stream << item;

    BOOST_REQUIRE_EQUAL(stream.str(), data);
}
