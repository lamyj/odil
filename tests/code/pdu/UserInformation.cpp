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
    BOOST_REQUIRE_EQUAL(item.has_maximum_length(), false);
    BOOST_REQUIRE_EQUAL(item.has_user_identity_rq(), false);
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

    BOOST_REQUIRE(item.has_maximum_length());
    BOOST_REQUIRE_EQUAL(
        item.get_maximum_length().get_maximum_length(), 0x12345678);

    BOOST_REQUIRE(item.has_user_identity_rq());
    BOOST_REQUIRE_EQUAL(item.get_user_identity_rq().get_type(), 2);
    BOOST_REQUIRE_EQUAL(
        item.get_user_identity_rq().get_positive_response_requested(), true);
    BOOST_REQUIRE_EQUAL(item.get_user_identity_rq().get_primary_field(), "foo");
    BOOST_REQUIRE_EQUAL(
        item.get_user_identity_rq().get_secondary_field(), "bar");

    BOOST_REQUIRE(!item.has_user_identity_ac());
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

    BOOST_REQUIRE(item.has_maximum_length());
    BOOST_REQUIRE_EQUAL(
        item.get_maximum_length().get_maximum_length(), 0x12345678);

    BOOST_REQUIRE(!item.has_user_identity_rq());

    BOOST_REQUIRE(item.has_user_identity_ac());
    BOOST_REQUIRE_EQUAL(
        item.get_user_identity_ac().get_server_response(), "abcd");
}

BOOST_AUTO_TEST_CASE(MaximumLength)
{
    dcmtkpp::pdu::UserInformation item;

    BOOST_REQUIRE(!item.has_maximum_length());
    BOOST_REQUIRE_THROW(item.get_maximum_length(), dcmtkpp::Exception);

    item.set_maximum_length(dcmtkpp::pdu::MaximumLength(0x12345678));

    BOOST_REQUIRE(item.has_maximum_length());
    BOOST_REQUIRE_EQUAL(
        item.get_maximum_length().get_maximum_length(), 0x12345678);

    item.delete_maximum_length();
    BOOST_REQUIRE(!item.has_maximum_length());
    BOOST_REQUIRE_THROW(item.get_maximum_length(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(UserIdentityRQ)
{
    dcmtkpp::pdu::UserInformation item;

    BOOST_REQUIRE(!item.has_user_identity_rq());
    BOOST_REQUIRE_THROW(item.get_user_identity_rq(), dcmtkpp::Exception);

    dcmtkpp::pdu::UserIdentityRQ user_identity;
    user_identity.set_positive_response_requested(true);
    user_identity.set_username_and_passcode("foo", "bar");
    item.set_user_identity_rq(user_identity);

    BOOST_REQUIRE(item.has_user_identity_rq());
    BOOST_REQUIRE_EQUAL(item.get_user_identity_rq().get_type(), 2);
    BOOST_REQUIRE_EQUAL(
        item.get_user_identity_rq().get_positive_response_requested(), true);
    BOOST_REQUIRE_EQUAL(item.get_user_identity_rq().get_primary_field(), "foo");
    BOOST_REQUIRE_EQUAL(
        item.get_user_identity_rq().get_secondary_field(), "bar");

    item.delete_user_identity_rq();
    BOOST_REQUIRE(!item.has_user_identity_rq());
    BOOST_REQUIRE_THROW(item.get_user_identity_rq(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(UserIdentityAC)
{
    dcmtkpp::pdu::UserInformation item;

    BOOST_REQUIRE(!item.has_user_identity_ac());
    BOOST_REQUIRE_THROW(item.get_user_identity_ac(), dcmtkpp::Exception);

    dcmtkpp::pdu::UserIdentityAC user_identity;
    user_identity.set_server_response("abcd");
    item.set_user_identity_ac(user_identity);

    BOOST_REQUIRE(item.has_user_identity_ac());
    BOOST_REQUIRE_EQUAL(
        item.get_user_identity_ac().get_server_response(), "abcd");

    item.delete_user_identity_ac();
    BOOST_REQUIRE(!item.has_user_identity_ac());
    BOOST_REQUIRE_THROW(item.get_user_identity_ac(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(UserIdentityBoth1)
{
    dcmtkpp::pdu::UserInformation item;

    dcmtkpp::pdu::UserIdentityRQ user_identity_rq;
    user_identity_rq.set_positive_response_requested(true);
    user_identity_rq.set_username_and_passcode("foo", "bar");
    item.set_user_identity_rq(user_identity_rq);

    dcmtkpp::pdu::UserIdentityAC user_identity_ac;
    user_identity_ac.set_server_response("abcd");
    BOOST_REQUIRE_THROW(
        item.set_user_identity_ac(user_identity_ac), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(UserIdentityBoth2)
{
    dcmtkpp::pdu::UserInformation item;

    dcmtkpp::pdu::UserIdentityAC user_identity_ac;
    user_identity_ac.set_server_response("abcd");
    item.set_user_identity_ac(user_identity_ac);

    dcmtkpp::pdu::UserIdentityRQ user_identity_rq;
    user_identity_rq.set_positive_response_requested(true);
    user_identity_rq.set_username_and_passcode("foo", "bar");
    BOOST_REQUIRE_THROW(
        item.set_user_identity_rq(user_identity_rq), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(WriteRQ)
{
    dcmtkpp::pdu::UserInformation item;

    dcmtkpp::pdu::UserIdentityRQ user_identity_rq;
    user_identity_rq.set_positive_response_requested(true);
    user_identity_rq.set_username_and_passcode("foo", "bar");
    item.set_user_identity_rq(user_identity_rq);

    dcmtkpp::pdu::MaximumLength const maximum_length(0x12345678);
    item.set_maximum_length(maximum_length);

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
    item.set_user_identity_ac(user_identity_ac);

    dcmtkpp::pdu::MaximumLength const maximum_length(0x12345678);
    item.set_maximum_length(maximum_length);

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
