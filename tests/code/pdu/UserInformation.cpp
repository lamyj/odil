#define BOOST_TEST_MODULE UserInformation
#include <boost/test/unit_test.hpp>

#include <sstream>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/pdu/MaximumLength.h"
#include "dcmtkpp/pdu/UserInformation.h"
#include "dcmtkpp/pdu/UserIdentityAC.h"
#include "dcmtkpp/pdu/UserIdentityRQ.h"

BOOST_AUTO_TEST_CASE(ConstructorDefault)
{
    dcmtkpp::pdu::UserInformation const item;
    BOOST_REQUIRE(!item.has_sub_item<dcmtkpp::pdu::MaximumLength>());
    BOOST_REQUIRE(!item.has_sub_item<dcmtkpp::pdu::UserIdentityRQ>());
}

BOOST_AUTO_TEST_CASE(ConstructorStreamRQ)
{
    std::string const data(
        "\x50\x00\x00\x18"

        "\x51\x00\x00\x04"
        "\x12\x34\x56\x78"

        "\x58\x00\x00\x0c"
        "\x02\x01"
        "\x00\x03" "foo"
        "\x00\x03" "bar",
        28
    );
    std::istringstream stream(data);

    dcmtkpp::pdu::UserInformation item(stream);

    BOOST_REQUIRE(item.has_sub_item<dcmtkpp::pdu::MaximumLength>());
    BOOST_REQUIRE_EQUAL(
        item.get_sub_item<dcmtkpp::pdu::MaximumLength>().get_maximum_length(),
        0x12345678);

    BOOST_REQUIRE(item.has_sub_item<dcmtkpp::pdu::UserIdentityRQ>());
    BOOST_REQUIRE_EQUAL(
        item.get_sub_item<dcmtkpp::pdu::UserIdentityRQ>().get_type(), 2);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_item<dcmtkpp::pdu::UserIdentityRQ>().get_positive_response_requested(),
        true);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_item<dcmtkpp::pdu::UserIdentityRQ>().get_primary_field(),
        "foo");
    BOOST_REQUIRE_EQUAL(
        item.get_sub_item<dcmtkpp::pdu::UserIdentityRQ>().get_secondary_field(),
        "bar");

    BOOST_REQUIRE(!item.has_sub_item<dcmtkpp::pdu::UserIdentityAC>());
}

BOOST_AUTO_TEST_CASE(ConstructorStreamAC)
{
    std::string const data(
        "\x50\x00\x00\x12"

        "\x51\x00\x00\x04"
        "\x12\x34\x56\x78"

        "\x59\x00\x00\x06"
        "\x00\x04" "abcd",
        22
    );
    std::istringstream stream(data);

    dcmtkpp::pdu::UserInformation item(stream);

    BOOST_REQUIRE(item.has_sub_item<dcmtkpp::pdu::MaximumLength>());
    BOOST_REQUIRE_EQUAL(
        item.get_sub_item<dcmtkpp::pdu::MaximumLength>().get_maximum_length(),
        0x12345678);

    BOOST_REQUIRE(!item.has_sub_item<dcmtkpp::pdu::UserIdentityRQ>());

    BOOST_REQUIRE(item.has_sub_item<dcmtkpp::pdu::UserIdentityAC>());
    BOOST_REQUIRE_EQUAL(
        item.get_sub_item<dcmtkpp::pdu::UserIdentityAC>().get_server_response(),
        "abcd");
}

BOOST_AUTO_TEST_CASE(MaximumLength)
{
    dcmtkpp::pdu::UserInformation item;

    BOOST_REQUIRE(!item.has_sub_item<dcmtkpp::pdu::MaximumLength>());
    BOOST_REQUIRE_THROW(
        item.get_sub_item<dcmtkpp::pdu::MaximumLength>(), dcmtkpp::Exception);

    item.set_sub_item(dcmtkpp::pdu::MaximumLength(0x12345678));

    BOOST_REQUIRE(item.has_sub_item<dcmtkpp::pdu::MaximumLength>());
    BOOST_REQUIRE_EQUAL(
        item.get_sub_item<dcmtkpp::pdu::MaximumLength>().get_maximum_length(),
        0x12345678);

    item.delete_sub_item<dcmtkpp::pdu::MaximumLength>();
    BOOST_REQUIRE(!item.has_sub_item<dcmtkpp::pdu::MaximumLength>());
    BOOST_REQUIRE_THROW(
        item.get_sub_item<dcmtkpp::pdu::MaximumLength>(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(WriteRQ)
{
    dcmtkpp::pdu::UserInformation item;

    dcmtkpp::pdu::UserIdentityRQ user_identity_rq;
    user_identity_rq.set_positive_response_requested(true);
    user_identity_rq.set_username_and_passcode("foo", "bar");
    item.set_sub_item(user_identity_rq);

    dcmtkpp::pdu::MaximumLength const maximum_length(0x12345678);
    item.set_sub_item(maximum_length);

    std::ostringstream data;
    data << item;

    std::string const expected(
        "\x50\x00\x00\x18"

        "\x51\x00\x00\x04"
        "\x12\x34\x56\x78"

        "\x58\x00\x00\x0c"
        "\x02\x01"
        "\x00\x03" "foo"
        "\x00\x03" "bar",
        28
    );

    BOOST_REQUIRE_EQUAL(data.str(), expected);
}

BOOST_AUTO_TEST_CASE(WriteAC)
{
    dcmtkpp::pdu::UserInformation item;

    dcmtkpp::pdu::UserIdentityAC user_identity_ac;
    user_identity_ac.set_server_response("abcd");
    item.set_sub_item(user_identity_ac);

    dcmtkpp::pdu::MaximumLength const maximum_length(0x12345678);
    item.set_sub_item(maximum_length);

    std::ostringstream data;
    data << item;

    std::string const expected(
        "\x50\x00\x00\x12"

        "\x51\x00\x00\x04"
        "\x12\x34\x56\x78"

        "\x59\x00\x00\x06"
        "\x00\x04" "abcd",
        22
    );

    BOOST_REQUIRE_EQUAL(data.str(), expected);
}
