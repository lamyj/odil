#define BOOST_TEST_MODULE ImplementationClassUID
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "odil/dul/ImplementationClassUID.h"

std::string const data(
    "\x52\x00\x00\x03"
    "foo",
    7
);

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::dul::ImplementationClassUID const item("foo");
    BOOST_REQUIRE_EQUAL(item.get_implementation_class_uid(), "foo");
}

BOOST_AUTO_TEST_CASE(FromStream)
{
    std::istringstream stream(data);
    odil::dul::ImplementationClassUID const item(stream);

    BOOST_REQUIRE_EQUAL(item.get_implementation_class_uid(), "foo");
}

BOOST_AUTO_TEST_CASE(ImplementationClassUID)
{
    odil::dul::ImplementationClassUID item("foo");
    item.set_implementation_class_uid("bar");
    BOOST_REQUIRE_EQUAL(item.get_implementation_class_uid(), "bar");
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::dul::ImplementationClassUID const item("foo");
    std::ostringstream stream;
    stream << item;

    BOOST_REQUIRE_EQUAL(stream.str(), data);
}
