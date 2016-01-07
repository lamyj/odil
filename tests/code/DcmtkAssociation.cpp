#define BOOST_TEST_MODULE DcmtkAssociation
#include <boost/test/unit_test.hpp>

#include <ostream>

#include "dcmtkpp/dcmtk/Association.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/dcmtk/Exception.h"
#include "dcmtkpp/dcmtk/Network.h"

#include "../PeerFixtureBase.h"

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::dcmtk::Association association;
    BOOST_CHECK_EQUAL(association.get_own_ae_title(), "");

    BOOST_CHECK_EQUAL(association.get_peer_host_name(), "");
    BOOST_CHECK_EQUAL(association.get_peer_port(), 104);
    BOOST_CHECK_EQUAL(association.get_peer_ae_title(), "");

    BOOST_CHECK(
        association.get_user_identity_type() ==
            dcmtkpp::dcmtk::Association::UserIdentityType::None);
    BOOST_CHECK_EQUAL(association.get_user_identity_primary_field(), "");
    BOOST_CHECK_EQUAL(association.get_user_identity_secondary_field(), "");

    BOOST_CHECK(!association.is_associated());
    BOOST_CHECK_EQUAL(
        association.get_association(), static_cast<T_ASC_Association*>(NULL));
}

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
    dcmtkpp::dcmtk::Association association;
    association.set_own_ae_title("local");

    association.set_peer_host_name("pacs.example.com");
    association.set_peer_port(11112);
    association.set_peer_ae_title("remote");

    association.set_user_identity_to_username_and_password("foo", "bar");

    dcmtkpp::dcmtk::Association const other(association);

    BOOST_CHECK_EQUAL(other.get_own_ae_title(), association.get_own_ae_title());

    BOOST_CHECK_EQUAL(
        other.get_peer_host_name(), association.get_peer_host_name());
    BOOST_CHECK_EQUAL(other.get_peer_port(), association.get_peer_port());
    BOOST_CHECK_EQUAL(
        other.get_peer_ae_title(), association.get_peer_ae_title());

    BOOST_CHECK(
        other.get_user_identity_type() == association.get_user_identity_type());
    BOOST_CHECK_EQUAL(
        other.get_user_identity_primary_field(),
        association.get_user_identity_primary_field());
    BOOST_CHECK_EQUAL(
        other.get_user_identity_secondary_field(),
        association.get_user_identity_secondary_field());
}

BOOST_AUTO_TEST_CASE(Assignment)
{
    dcmtkpp::dcmtk::Association association;
    association.set_own_ae_title("local");

    association.set_peer_host_name("pacs.example.com");
    association.set_peer_port(11112);
    association.set_peer_ae_title("remote");

    association.set_user_identity_to_username_and_password("foo", "bar");

    dcmtkpp::dcmtk::Association other;
    other = association;

    BOOST_CHECK_EQUAL(other.get_own_ae_title(), association.get_own_ae_title());

    BOOST_CHECK_EQUAL(
        other.get_peer_host_name(), association.get_peer_host_name());
    BOOST_CHECK_EQUAL(other.get_peer_port(), association.get_peer_port());
    BOOST_CHECK_EQUAL(
        other.get_peer_ae_title(), association.get_peer_ae_title());

    BOOST_CHECK(
        other.get_user_identity_type() == association.get_user_identity_type());
    BOOST_CHECK_EQUAL(
        other.get_user_identity_primary_field(),
        association.get_user_identity_primary_field());
    BOOST_CHECK_EQUAL(
        other.get_user_identity_secondary_field(),
        association.get_user_identity_secondary_field());
}

BOOST_AUTO_TEST_CASE(OwnAETitle)
{
    dcmtkpp::dcmtk::Association association;
    association.set_own_ae_title("myself");
    BOOST_CHECK_EQUAL(association.get_own_ae_title(), "myself");
}

BOOST_AUTO_TEST_CASE(PeerHostName)
{
    dcmtkpp::dcmtk::Association association;
    association.set_peer_host_name("pacs.example.com");
    BOOST_CHECK_EQUAL(association.get_peer_host_name(), "pacs.example.com");
}

BOOST_AUTO_TEST_CASE(PeerPort)
{
    dcmtkpp::dcmtk::Association association;
    association.set_peer_port(11112);
    BOOST_CHECK_EQUAL(association.get_peer_port(), 11112);
}

BOOST_AUTO_TEST_CASE(PeerAETitle)
{
    dcmtkpp::dcmtk::Association association;
    association.set_peer_ae_title("remote");
    BOOST_CHECK_EQUAL(association.get_peer_ae_title(), "remote");
}

BOOST_AUTO_TEST_CASE(UserIdentityType)
{
    dcmtkpp::dcmtk::Association association;
    association.set_user_identity_type(
        dcmtkpp::dcmtk::Association::UserIdentityType::Username);
    BOOST_CHECK(
        association.get_user_identity_type() ==
            dcmtkpp::dcmtk::Association::UserIdentityType::Username);
}

BOOST_AUTO_TEST_CASE(UserIdentityPrimaryField)
{
    dcmtkpp::dcmtk::Association association;
    association.set_user_identity_primary_field("user");
    BOOST_CHECK_EQUAL(association.get_user_identity_primary_field(), "user");
}

BOOST_AUTO_TEST_CASE(UserIdentitySecondaryField)
{
    dcmtkpp::dcmtk::Association association;
    association.set_user_identity_secondary_field("password");
    BOOST_CHECK_EQUAL(
        association.get_user_identity_secondary_field(), "password");
}

BOOST_AUTO_TEST_CASE(UserIdentityNone)
{
    dcmtkpp::dcmtk::Association association;
    association.set_user_identity_to_none();
    BOOST_CHECK_EQUAL(association.get_user_identity_primary_field(), "");
    BOOST_CHECK_EQUAL(association.get_user_identity_secondary_field(), "");
}

BOOST_AUTO_TEST_CASE(UserIdentityUsername)
{
    dcmtkpp::dcmtk::Association association;
    association.set_user_identity_to_username("user");
    BOOST_CHECK(
        association.get_user_identity_type() ==
            dcmtkpp::dcmtk::Association::UserIdentityType::Username);
    BOOST_CHECK_EQUAL(association.get_user_identity_primary_field(), "user");
    BOOST_CHECK_EQUAL(association.get_user_identity_secondary_field(), "");
}

BOOST_AUTO_TEST_CASE(UserIdentityUsernameAndPassword)
{
    dcmtkpp::dcmtk::Association association;
    association.set_user_identity_to_username_and_password("user", "password");
    BOOST_CHECK(
        association.get_user_identity_type() ==
            dcmtkpp::dcmtk::Association::UserIdentityType::UsernameAndPassword);
    BOOST_CHECK_EQUAL(association.get_user_identity_primary_field(), "user");
    BOOST_CHECK_EQUAL(
        association.get_user_identity_secondary_field(), "password");
}

BOOST_AUTO_TEST_CASE(UserIdentityKerberos)
{
    dcmtkpp::dcmtk::Association association;
    association.set_user_identity_to_kerberos("ticket");
    BOOST_CHECK(
        association.get_user_identity_type() ==
            dcmtkpp::dcmtk::Association::UserIdentityType::Kerberos);
    BOOST_CHECK_EQUAL(association.get_user_identity_primary_field(), "ticket");
    BOOST_CHECK_EQUAL(association.get_user_identity_secondary_field(), "");
}

BOOST_AUTO_TEST_CASE(UserIdentitySAML)
{
    dcmtkpp::dcmtk::Association association;
    association.set_user_identity_to_saml("assertion");
    BOOST_CHECK(
        association.get_user_identity_type() ==
            dcmtkpp::dcmtk::Association::UserIdentityType::SAML);
    BOOST_CHECK_EQUAL(
        association.get_user_identity_primary_field(), "assertion");
    BOOST_CHECK_EQUAL(association.get_user_identity_secondary_field(), "");
}

BOOST_AUTO_TEST_CASE(Associate)
{
    dcmtkpp::dcmtk::Network network(NET_REQUESTOR, 0, 10);
    network.initialize();

    dcmtkpp::dcmtk::Association dcmtk_association;
    dcmtk_association.set_own_ae_title(
        PeerFixtureBase::get_environment_variable("DCMTKPP_OWN_AET"));
    dcmtk_association.set_peer_host_name(
        PeerFixtureBase::get_environment_variable("DCMTKPP_PEER_HOST_NAME"));
    dcmtk_association.set_peer_port(
        PeerFixtureBase::get_environment_variable<uint16_t>("DCMTKPP_PEER_PORT"));
    dcmtk_association.set_peer_ae_title(
        PeerFixtureBase::get_environment_variable("DCMTKPP_PEER_AET"));
    dcmtk_association.set_presentation_contexts({
        {
            dcmtkpp::registry::VerificationSOPClass,
            {dcmtkpp::registry::ImplicitVRLittleEndian}
        }
    });
    dcmtk_association.associate(network);

    BOOST_CHECK_THROW(dcmtk_association.set_own_ae_title("foo"), dcmtkpp::Exception);
    BOOST_CHECK_THROW(dcmtk_association.set_peer_host_name("foo"), dcmtkpp::Exception);
    BOOST_CHECK_THROW(dcmtk_association.set_peer_port(1234), dcmtkpp::Exception);
    BOOST_CHECK_THROW(dcmtk_association.set_peer_ae_title("foo"), dcmtkpp::Exception);

    std::vector<dcmtkpp::dcmtk::Association::PresentationContext>
        presentation_contexts;
    presentation_contexts.push_back(
        {
            dcmtkpp::registry::PatientRootQueryRetrieveInformationModelGET,
            { dcmtkpp::registry::ImplicitVRLittleEndian }
        });
    BOOST_CHECK_THROW(
        dcmtk_association.set_presentation_contexts(presentation_contexts),
        dcmtkpp::Exception);

    BOOST_CHECK_THROW(
        dcmtk_association.set_user_identity_type(
            dcmtkpp::dcmtk::Association::UserIdentityType::SAML),
        dcmtkpp::Exception);
    BOOST_CHECK_THROW(
        dcmtk_association.set_user_identity_primary_field("foo"),
        dcmtkpp::Exception);
    BOOST_CHECK_THROW(
        dcmtk_association.set_user_identity_secondary_field("foo"),
        dcmtkpp::Exception);

    network.drop();
}

BOOST_AUTO_TEST_CASE(Release)
{
    dcmtkpp::dcmtk::Association association;
    BOOST_CHECK_THROW(association.release(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Abort)
{
    dcmtkpp::dcmtk::Association association;
    BOOST_CHECK_THROW(association.abort(), dcmtkpp::Exception);
}
