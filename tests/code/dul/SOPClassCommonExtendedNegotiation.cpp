#define BOOST_TEST_MODULE SOPClassCommonExtendedNegotiation
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "odil/Exception.h"
#include "odil/dul/SOPClassCommonExtendedNegotiation.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::dul::SOPClassCommonExtendedNegotiation const item(
        "sop_class", "service_class", {"foo", "bar"});
    BOOST_REQUIRE_EQUAL(item.get_sop_class_uid(), "sop_class");
    BOOST_REQUIRE_EQUAL(item.get_service_class_uid(), "service_class");
    BOOST_REQUIRE(
        item.get_related_general_sop_class_uids() ==
            std::vector<std::string>({"foo", "bar"}));
}

BOOST_AUTO_TEST_CASE(FromStream)
{
    std::string const data(
        "\x57\x00\x00\x26"
        "\x00\x09" "sop_class"
        "\x00\x0d" "service_class"
        "\x00\x0a"
            "\x00\x03" "foo"
            "\x00\x03" "bar",
        42
    );
    std::istringstream stream(data);

    odil::dul::SOPClassCommonExtendedNegotiation const item(stream);

    BOOST_REQUIRE_EQUAL(item.get_sop_class_uid(), "sop_class");
    BOOST_REQUIRE_EQUAL(item.get_service_class_uid(), "service_class");
    BOOST_REQUIRE(
        item.get_related_general_sop_class_uids() ==
            std::vector<std::string>({"foo", "bar"}));
}

BOOST_AUTO_TEST_CASE(SOPClassUID)
{
    odil::dul::SOPClassCommonExtendedNegotiation item(
        "sop_class", "service_class", {"foo", "bar"});
    item.set_sop_class_uid("bar");
    BOOST_REQUIRE_EQUAL(item.get_sop_class_uid(), "bar");
}

BOOST_AUTO_TEST_CASE(ServiceClassUID)
{
    odil::dul::SOPClassCommonExtendedNegotiation item(
        "sop_class", "service_class", {"foo", "bar"});
    item.set_service_class_uid("bar");
    BOOST_REQUIRE_EQUAL(item.get_service_class_uid(), "bar");
}

BOOST_AUTO_TEST_CASE(RelatedClasses)
{
    odil::dul::SOPClassCommonExtendedNegotiation item(
        "sop_class", "service_class", {"foo", "bar"});
    item.set_related_general_sop_class_uids({"plip", "plop", "plup"});
    BOOST_REQUIRE(
        item.get_related_general_sop_class_uids() ==
            std::vector<std::string>({"plip", "plop", "plup"}));
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::dul::SOPClassCommonExtendedNegotiation const item(
        "sop_class", "service_class", {"foo", "bar"});
    std::ostringstream data;
    data << item;

    std::string const expected(
        "\x57\x00\x00\x26"
        "\x00\x09" "sop_class"
        "\x00\x0d" "service_class"
        "\x00\x0a"
            "\x00\x03" "foo"
            "\x00\x03" "bar",
        42
    );

    BOOST_REQUIRE_EQUAL(data.str(), expected);
}
