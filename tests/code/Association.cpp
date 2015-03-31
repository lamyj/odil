#include <ostream>
#include "dcmtkpp/Association.h"

namespace dcmtkpp
{

std::ostream & operator<<(std::ostream & stream, UserIdentityType const & type)
{
    stream << int(type);
    return stream;
}

}

#define BOOST_TEST_MODULE Association
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/Association.h"

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::Association const association;
    BOOST_CHECK_EQUAL(association.get_own_ae_title(), "");

    BOOST_CHECK_EQUAL(association.get_peer_host_name(), "");
    BOOST_CHECK_EQUAL(association.get_peer_port(), 104);
    BOOST_CHECK_EQUAL(association.get_peer_ae_title(), "");

    BOOST_CHECK_EQUAL(
        association.get_user_identity_type(), dcmtkpp::UserIdentityType::None);
    BOOST_CHECK_EQUAL(association.get_user_identity_primary_field(), "");
    BOOST_CHECK_EQUAL(association.get_user_identity_secondary_field(), "");

    BOOST_CHECK(!association.is_associated());
}

BOOST_AUTO_TEST_CASE(OwnAETitle)
{
    dcmtkpp::Association association;
    association.set_own_ae_title("myself");
    BOOST_CHECK_EQUAL(association.get_own_ae_title(), "myself");
}

BOOST_AUTO_TEST_CASE(PeerHostName)
{
    dcmtkpp::Association association;
    association.set_peer_host_name("pacs.example.com");
    BOOST_CHECK_EQUAL(association.get_peer_host_name(), "pacs.example.com");
}

BOOST_AUTO_TEST_CASE(PeerPort)
{
    dcmtkpp::Association association;
    association.set_peer_port(11112);
    BOOST_CHECK_EQUAL(association.get_peer_port(), 11112);
}

BOOST_AUTO_TEST_CASE(PeerAETitle)
{
    dcmtkpp::Association association;
    association.set_peer_ae_title("remote");
    BOOST_CHECK_EQUAL(association.get_peer_ae_title(), "remote");
}

BOOST_AUTO_TEST_CASE(UserIdentityType)
{
    dcmtkpp::Association association;
    association.set_user_identity_type(dcmtkpp::UserIdentityType::Username);
    BOOST_CHECK_EQUAL(
        association.get_user_identity_type(),
        dcmtkpp::UserIdentityType::Username);
}

BOOST_AUTO_TEST_CASE(UserIdentityPrimaryField)
{
    dcmtkpp::Association association;
    association.set_user_identity_primary_field("user");
    BOOST_CHECK_EQUAL(association.get_user_identity_primary_field(), "user");
}

BOOST_AUTO_TEST_CASE(UserIdentitySecondaryField)
{
    dcmtkpp::Association association;
    association.set_user_identity_secondary_field("password");
    BOOST_CHECK_EQUAL(
        association.get_user_identity_secondary_field(), "password");
}

BOOST_AUTO_TEST_CASE(UserIdentityUsername)
{
    dcmtkpp::Association association;
    association.set_user_identity_to_username("user");
    BOOST_CHECK_EQUAL(
        association.get_user_identity_type(),
        dcmtkpp::UserIdentityType::Username);
    BOOST_CHECK_EQUAL(association.get_user_identity_primary_field(), "user");
    BOOST_CHECK_EQUAL(association.get_user_identity_secondary_field(), "");
}

BOOST_AUTO_TEST_CASE(UserIdentityUsernameAndPassword)
{
    dcmtkpp::Association association;
    association.set_user_identity_to_username_and_password("user", "password");
    BOOST_CHECK_EQUAL(
        association.get_user_identity_type(),
        dcmtkpp::UserIdentityType::UsernameAndPassword);
    BOOST_CHECK_EQUAL(association.get_user_identity_primary_field(), "user");
    BOOST_CHECK_EQUAL(
        association.get_user_identity_secondary_field(), "password");
}

BOOST_AUTO_TEST_CASE(UserIdentityKerberos)
{
    dcmtkpp::Association association;
    association.set_user_identity_to_kerberos("ticket");
    BOOST_CHECK_EQUAL(
        association.get_user_identity_type(),
        dcmtkpp::UserIdentityType::Kerberos);
    BOOST_CHECK_EQUAL(association.get_user_identity_primary_field(), "ticket");
    BOOST_CHECK_EQUAL(association.get_user_identity_secondary_field(), "");
}

BOOST_AUTO_TEST_CASE(UserIdentitySAML)
{
    dcmtkpp::Association association;
    association.set_user_identity_to_saml("assertion");
    BOOST_CHECK_EQUAL(
        association.get_user_identity_type(), dcmtkpp::UserIdentityType::SAML);
    BOOST_CHECK_EQUAL(
        association.get_user_identity_primary_field(), "assertion");
    BOOST_CHECK_EQUAL(association.get_user_identity_secondary_field(), "");
}
