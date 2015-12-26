#define BOOST_TEST_MODULE UserInformation
#include <boost/test/unit_test.hpp>

#include <sstream>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/pdu/ImplementationClassUID.h"
#include "dcmtkpp/pdu/ImplementationVersionName.h"
#include "dcmtkpp/pdu/MaximumLength.h"
#include "dcmtkpp/pdu/RoleSelection.h"
#include "dcmtkpp/pdu/UserInformation.h"
#include "dcmtkpp/pdu/UserIdentityAC.h"
#include "dcmtkpp/pdu/UserIdentityRQ.h"

BOOST_AUTO_TEST_CASE(ConstructorDefault)
{
    dcmtkpp::pdu::UserInformation const item;
    BOOST_REQUIRE(item.get_sub_items<dcmtkpp::pdu::MaximumLength>().empty());
    BOOST_REQUIRE(item.get_sub_items<dcmtkpp::pdu::UserIdentityRQ>().empty());
}

BOOST_AUTO_TEST_CASE(ConstructorStreamMaximumLength)
{
    std::string const data(
        "\x50\x00\x00\x08"
        "\x51\x00\x00\x04"
        "\x12\x34\x56\x78",
        12
    );
    std::istringstream stream(data);

    dcmtkpp::pdu::UserInformation const item(stream);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<dcmtkpp::pdu::MaximumLength>().size(), 1);
}

BOOST_AUTO_TEST_CASE(ConstructorStreamImplementationClassUID)
{
    std::string const data(
        "\x50\x00\x00\x07"
        "\x52\x00\x00\x03" "foo",
        11
    );
    std::istringstream stream(data);

    dcmtkpp::pdu::UserInformation const item(stream);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<dcmtkpp::pdu::ImplementationClassUID>().size(), 1);
}

BOOST_AUTO_TEST_CASE(ConstructorStreamRoleSelection)
{
    std::string const data(
        "\x50\x00\x00\x0f"
        "\x54\x00\x00\x0b"
        "\x00\x07" "1.2.3.4"
        "\x01\x01",
        19
    );
    std::istringstream stream(data);

    dcmtkpp::pdu::UserInformation const item(stream);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<dcmtkpp::pdu::RoleSelection>().size(), 1);
}

BOOST_AUTO_TEST_CASE(ConstructorStreamImplementationVersionName)
{
    std::string const data(
        "\x50\x00\x00\x07"
        "\x55\x00\x00\x03" "foo",
        11
    );
    std::istringstream stream(data);

    dcmtkpp::pdu::UserInformation const item(stream);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<dcmtkpp::pdu::ImplementationVersionName>().size(), 1);
}

BOOST_AUTO_TEST_CASE(ConstructorStreamUserIdentityRQ)
{
    std::string const data(
        "\x50\x00\x00\x10"

        "\x58\x00\x00\x0c"
        "\x02\x01"
        "\x00\x03" "foo"
        "\x00\x03" "bar",
        20
    );
    std::istringstream stream(data);

    dcmtkpp::pdu::UserInformation const item(stream);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<dcmtkpp::pdu::UserIdentityRQ>().size(), 1);

}

BOOST_AUTO_TEST_CASE(ConstructorStreamUserIdentityAC)
{
    std::string const data(
        "\x50\x00\x00\x0a"

        "\x59\x00\x00\x06"
        "\x00\x04" "abcd",
        14
    );
    std::istringstream stream(data);

    dcmtkpp::pdu::UserInformation const item(stream);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<dcmtkpp::pdu::UserIdentityAC>().size(), 1);
}

BOOST_AUTO_TEST_CASE(SetSubItems)
{
    dcmtkpp::pdu::UserInformation item;
    BOOST_REQUIRE(item.get_sub_items<dcmtkpp::pdu::MaximumLength>().empty());

    item.set_sub_items<dcmtkpp::pdu::MaximumLength>({{0x12345678}});

    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<dcmtkpp::pdu::MaximumLength>().size(), 1);
}

BOOST_AUTO_TEST_CASE(DeleteSubItems)
{
    dcmtkpp::pdu::UserInformation item;
    BOOST_REQUIRE(item.get_sub_items<dcmtkpp::pdu::MaximumLength>().empty());

    item.set_sub_items<dcmtkpp::pdu::MaximumLength>({{0x12345678}});

    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<dcmtkpp::pdu::MaximumLength>().size(), 1);

    item.delete_sub_items<dcmtkpp::pdu::MaximumLength>();

    BOOST_REQUIRE(item.get_sub_items<dcmtkpp::pdu::MaximumLength>().empty());
}

BOOST_AUTO_TEST_CASE(Write)
{
    dcmtkpp::pdu::UserInformation item;
    item.set_sub_items<dcmtkpp::pdu::MaximumLength>({{0x12345678}});

    std::ostringstream data;
    data << item;

    std::string const expected(
        "\x50\x00\x00\x08"

        "\x51\x00\x00\x04"
        "\x12\x34\x56\x78",
        12
    );

    BOOST_REQUIRE_EQUAL(data.str(), expected);
}

