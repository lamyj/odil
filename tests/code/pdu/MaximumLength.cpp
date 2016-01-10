#define BOOST_TEST_MODULE MaximumLength
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "odil/Exception.h"
#include "odil/pdu/MaximumLength.h"

BOOST_AUTO_TEST_CASE(ConstructorDefault)
{
    odil::pdu::MaximumLength const maximum_length;
    BOOST_REQUIRE_EQUAL(maximum_length.get_maximum_length(), 0);
}

BOOST_AUTO_TEST_CASE(ConstructorInt)
{
    odil::pdu::MaximumLength const maximum_length(123);
    BOOST_REQUIRE_EQUAL(maximum_length.get_maximum_length(), 123);
}

BOOST_AUTO_TEST_CASE(FromStream)
{
    std::string const data(
        "\x51\x00\x00\x04"
        "\x12\x34\x56\x78",
        8
    );
    std::istringstream stream(data);

    odil::pdu::MaximumLength const maximum_length(stream);

    BOOST_REQUIRE_EQUAL(maximum_length.get_maximum_length(), 0x12345678);
}

BOOST_AUTO_TEST_CASE(MaximumLength)
{
    odil::pdu::MaximumLength maximum_length;
    maximum_length.set_maximum_length(123);
    BOOST_REQUIRE_EQUAL(maximum_length.get_maximum_length(), 123);
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::pdu::MaximumLength const maximum_length(0x12345678);
    std::ostringstream data;
    data << maximum_length;

    std::string const expected(
        "\x51\x00\x00\x04"
        "\x12\x34\x56\x78",
        8
    );

    BOOST_REQUIRE_EQUAL(data.str(), expected);
}
