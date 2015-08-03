#define BOOST_TEST_MODULE Association
#include <boost/test/unit_test.hpp>

#include <ostream>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/registry.h"

#include "../PeerFixtureBase.h"

namespace dcmtkpp
{

std::ostream & operator<<(std::ostream & stream, UserIdentityType const & type)
{
    stream << int(type);
    return stream;
}

}

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::Association association;
    BOOST_CHECK_EQUAL(association.get_own_ae_title(), "");

    BOOST_CHECK_EQUAL(association.get_peer_host_name(), "");
    BOOST_CHECK_EQUAL(association.get_peer_port(), 104);
    BOOST_CHECK_EQUAL(association.get_peer_ae_title(), "");

    BOOST_CHECK_EQUAL(
        association.get_user_identity_type(), dcmtkpp::UserIdentityType::None);
    BOOST_CHECK_EQUAL(association.get_user_identity_primary_field(), "");
    BOOST_CHECK_EQUAL(association.get_user_identity_secondary_field(), "");

    BOOST_CHECK(!association.is_associated());
    BOOST_CHECK_EQUAL(
        association.get_association(), static_cast<T_ASC_Association*>(NULL));
}

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
    dcmtkpp::Association association;
    association.set_own_ae_title("local");

    association.set_peer_host_name("pacs.example.com");
    association.set_peer_port(11112);
    association.set_peer_ae_title("remote");

    association.set_user_identity_to_username_and_password("foo", "bar");

    dcmtkpp::Association const other(association);

    BOOST_CHECK_EQUAL(other.get_own_ae_title(), association.get_own_ae_title());

    BOOST_CHECK_EQUAL(
        other.get_peer_host_name(), association.get_peer_host_name());
    BOOST_CHECK_EQUAL(other.get_peer_port(), association.get_peer_port());
    BOOST_CHECK_EQUAL(
        other.get_peer_ae_title(), association.get_peer_ae_title());

    BOOST_CHECK_EQUAL(
        other.get_user_identity_type(), association.get_user_identity_type());
    BOOST_CHECK_EQUAL(
        other.get_user_identity_primary_field(),
        association.get_user_identity_primary_field());
    BOOST_CHECK_EQUAL(
        other.get_user_identity_secondary_field(),
        association.get_user_identity_secondary_field());
}

BOOST_AUTO_TEST_CASE(Assignment)
{
    dcmtkpp::Association association;
    association.set_own_ae_title("local");

    association.set_peer_host_name("pacs.example.com");
    association.set_peer_port(11112);
    association.set_peer_ae_title("remote");

    association.set_user_identity_to_username_and_password("foo", "bar");

    dcmtkpp::Association other;
    other = association;

    BOOST_CHECK_EQUAL(other.get_own_ae_title(), association.get_own_ae_title());

    BOOST_CHECK_EQUAL(
        other.get_peer_host_name(), association.get_peer_host_name());
    BOOST_CHECK_EQUAL(other.get_peer_port(), association.get_peer_port());
    BOOST_CHECK_EQUAL(
        other.get_peer_ae_title(), association.get_peer_ae_title());

    BOOST_CHECK_EQUAL(
        other.get_user_identity_type(), association.get_user_identity_type());
    BOOST_CHECK_EQUAL(
        other.get_user_identity_primary_field(),
        association.get_user_identity_primary_field());
    BOOST_CHECK_EQUAL(
        other.get_user_identity_secondary_field(),
        association.get_user_identity_secondary_field());
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

BOOST_AUTO_TEST_CASE(UserIdentityNone)
{
    dcmtkpp::Association association;
    association.set_user_identity_to_none();
    BOOST_CHECK_EQUAL(association.get_user_identity_primary_field(), "");
    BOOST_CHECK_EQUAL(association.get_user_identity_secondary_field(), "");
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

BOOST_AUTO_TEST_CASE(Associate)
{
    PeerFixtureBase fixture(NET_REQUESTOR, 0, 10, 
        {
            { dcmtkpp::registry::VerificationSOPClass,
                {dcmtkpp::registry::ImplicitVRLittleEndian}
            }
        });
    BOOST_CHECK_THROW(
        fixture.association.set_own_ae_title("foo"), dcmtkpp::Exception);
    BOOST_CHECK_THROW(
        fixture.association.set_peer_host_name("foo"), dcmtkpp::Exception);
    BOOST_CHECK_THROW(
        fixture.association.set_peer_port(1234), dcmtkpp::Exception);
    BOOST_CHECK_THROW(
        fixture.association.set_peer_ae_title("foo"), dcmtkpp::Exception);
    BOOST_CHECK_THROW(
        fixture.association.add_presentation_context(
                dcmtkpp::registry::PatientRootQueryRetrieveInformationModelGET,
                { dcmtkpp::registry::ImplicitVRLittleEndian }),
        dcmtkpp::Exception);
    BOOST_CHECK_THROW(
        fixture.association.set_user_identity_type(dcmtkpp::UserIdentityType::SAML), 
        dcmtkpp::Exception);
    BOOST_CHECK_THROW(
        fixture.association.set_user_identity_primary_field("foo"), 
        dcmtkpp::Exception);
    BOOST_CHECK_THROW(
        fixture.association.set_user_identity_secondary_field("foo"), 
        dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Release)
{
    dcmtkpp::Association association;
    BOOST_CHECK_THROW(association.release(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Abort)
{
    dcmtkpp::Association association;
    BOOST_CHECK_THROW(association.abort(), dcmtkpp::Exception);
}
