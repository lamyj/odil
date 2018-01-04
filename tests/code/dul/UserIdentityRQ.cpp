#define BOOST_TEST_MODULE UserIdentityRQ
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "odil/Exception.h"
#include "odil/pdu/UserIdentityRQ.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::pdu::UserIdentityRQ const user_identity;
    BOOST_REQUIRE_EQUAL(user_identity.get_type(), 1);
    BOOST_REQUIRE_EQUAL(user_identity.get_positive_response_requested(), false);
    BOOST_REQUIRE_EQUAL(user_identity.get_primary_field(), "");
    BOOST_REQUIRE_EQUAL(user_identity.get_secondary_field(), "");
}

BOOST_AUTO_TEST_CASE(FromStream)
{
    std::string const data(
        "\x58\x00\x00\x0c"
        "\x02\x01"
        "\x00\x03" "foo"
        "\x00\x03" "bar",
        16
    );
    std::istringstream stream(data);

    odil::pdu::UserIdentityRQ const user_identity(stream);

    BOOST_REQUIRE_EQUAL(user_identity.get_type(), 2);
    BOOST_REQUIRE_EQUAL(user_identity.get_positive_response_requested(), true);
    BOOST_REQUIRE_EQUAL(user_identity.get_primary_field(), "foo");
    BOOST_REQUIRE_EQUAL(user_identity.get_secondary_field(), "bar");
}

BOOST_AUTO_TEST_CASE(Type)
{
    odil::pdu::UserIdentityRQ user_identity;
    user_identity.set_type(2);
    BOOST_REQUIRE_EQUAL(user_identity.get_type(), 2);
}

BOOST_AUTO_TEST_CASE(PositiveResponseRequested)
{
    odil::pdu::UserIdentityRQ user_identity;
    user_identity.set_positive_response_requested(true);
    BOOST_REQUIRE_EQUAL(user_identity.get_positive_response_requested(), true);
}

BOOST_AUTO_TEST_CASE(PrimaryField)
{
    odil::pdu::UserIdentityRQ user_identity;
    user_identity.set_primary_field("foo");
    BOOST_REQUIRE_EQUAL(user_identity.get_primary_field(), "foo");
}

BOOST_AUTO_TEST_CASE(SecondaryField)
{
    odil::pdu::UserIdentityRQ user_identity;
    user_identity.set_secondary_field("foo");
    BOOST_REQUIRE_EQUAL(user_identity.get_secondary_field(), "foo");
}

BOOST_AUTO_TEST_CASE(Username)
{
    odil::pdu::UserIdentityRQ user_identity;
    user_identity.set_username("foo");

    BOOST_REQUIRE_EQUAL(user_identity.get_type(), 1);
    BOOST_REQUIRE_EQUAL(user_identity.get_primary_field(), "foo");
    BOOST_REQUIRE_EQUAL(user_identity.get_secondary_field(), "");
}

BOOST_AUTO_TEST_CASE(UsernameAndPasscode)
{
    odil::pdu::UserIdentityRQ user_identity;
    user_identity.set_username_and_passcode("foo", "bar");

    BOOST_REQUIRE_EQUAL(user_identity.get_type(), 2);
    BOOST_REQUIRE_EQUAL(user_identity.get_primary_field(), "foo");
    BOOST_REQUIRE_EQUAL(user_identity.get_secondary_field(), "bar");
}

BOOST_AUTO_TEST_CASE(KerberosTicket)
{
    odil::pdu::UserIdentityRQ user_identity;
    user_identity.set_kerberos_service_ticket("1234");

    BOOST_REQUIRE_EQUAL(user_identity.get_type(), 3);
    BOOST_REQUIRE_EQUAL(user_identity.get_primary_field(), "1234");
    BOOST_REQUIRE_EQUAL(user_identity.get_secondary_field(), "");
}

BOOST_AUTO_TEST_CASE(SAMLAssertion)
{
    odil::pdu::UserIdentityRQ user_identity;
    user_identity.set_saml_assertion("1234");

    BOOST_REQUIRE_EQUAL(user_identity.get_type(), 4);
    BOOST_REQUIRE_EQUAL(user_identity.get_primary_field(), "1234");
    BOOST_REQUIRE_EQUAL(user_identity.get_secondary_field(), "");
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::pdu::UserIdentityRQ user_identity;
    user_identity.set_username_and_passcode("foo", "bar");
    user_identity.set_positive_response_requested(true);

    std::ostringstream data;
    data << user_identity;

    std::string const expected(
        "\x58\x00\x00\x0c"
        "\x02\x01"
        "\x00\x03" "foo"
        "\x00\x03" "bar",
        16
    );

    BOOST_REQUIRE_EQUAL(data.str(), expected);
}
