#define BOOST_TEST_MODULE SOPClassExtendedNegotiation
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "odil/Exception.h"
#include "odil/pdu/SOPClassExtendedNegotiation.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::pdu::SOPClassExtendedNegotiation const item(
        "sop_class", {'\x01', '\x02', '\x03', '\x04'});
    BOOST_REQUIRE_EQUAL(item.get_sop_class_uid(), "sop_class");
    BOOST_REQUIRE(
        item.get_service_class_application_information() ==
            std::vector<uint8_t>({'\x01', '\x02', '\x03', '\x04'}));
}

BOOST_AUTO_TEST_CASE(FromStream)
{
    std::string const data(
        "\x56\x00\x00\x0f"
        "\x00\x09" "sop_class"
        "\x01\x02\x03\x04",
        19
    );
    std::istringstream stream(data);

    odil::pdu::SOPClassExtendedNegotiation const item(stream);

    BOOST_REQUIRE_EQUAL(item.get_sop_class_uid(), "sop_class");
    BOOST_REQUIRE(
        item.get_service_class_application_information() ==
            std::vector<uint8_t>({'\x01', '\x02', '\x03', '\x04'}));
}

BOOST_AUTO_TEST_CASE(SOPClassUID)
{
    odil::pdu::SOPClassExtendedNegotiation item(
        "sop_class", {'\x01', '\x02', '\x03', '\x04'});
    item.set_sop_class_uid("bar");
    BOOST_REQUIRE_EQUAL(item.get_sop_class_uid(), "bar");
}

BOOST_AUTO_TEST_CASE(ServiceClassApplicationInformation)
{
    odil::pdu::SOPClassExtendedNegotiation item(
        "sop_class", {'\x01', '\x02', '\x03', '\x04'});
    item.set_service_class_application_information({'\x05', '\x06'});
    BOOST_REQUIRE(
        item.get_service_class_application_information() ==
            std::vector<uint8_t>({'\x05', '\x06'}));
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::pdu::SOPClassExtendedNegotiation const item(
        "sop_class", {'\x01', '\x02', '\x03', '\x04'});
    std::ostringstream data;
    data << item;

    std::string const expected(
        "\x56\x00\x00\x0f"
        "\x00\x09" "sop_class"
        "\x01\x02\x03\x04",
        19
    );

    BOOST_REQUIRE_EQUAL(data.str(), expected);
}
