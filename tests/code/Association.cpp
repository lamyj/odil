#define BOOST_TEST_MODULE Association
#include <boost/test/unit_test.hpp>

#include <ostream>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/registry.h"

#include "../PeerFixtureBase.h"

namespace dcmtkpp
{

bool
operator==(
    AssociationParameters::PresentationContext const & left,
    AssociationParameters::PresentationContext const & right)
{
    return (
        left.abstract_syntax == right.abstract_syntax &&
        left.transfer_syntaxes == right.transfer_syntaxes &&
        left.scu_role_support == right.scu_role_support &&
        left.scp_role_support == right.scp_role_support
    );
}

bool
operator==(
    AssociationParameters const & left, AssociationParameters const & right)
{
    return (
        left.get_calling_ae_title() == right.get_calling_ae_title() &&
        left.get_called_ae_title() == right.get_called_ae_title() &&

        left.get_presentation_contexts() == right.get_presentation_contexts() &&


        left.get_user_identity().type == right.get_user_identity().type &&
        left.get_user_identity().primary_field == right.get_user_identity().primary_field &&
        left.get_user_identity().secondary_field == right.get_user_identity().secondary_field &&

        left.get_maximum_length() == right.get_maximum_length()
    );
}

}


BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::Association association;
    BOOST_CHECK_EQUAL(association.get_peer_host(), "");
    BOOST_CHECK_EQUAL(association.get_peer_port(), 104);
    BOOST_CHECK(
        association.get_parameters() ==
            dcmtkpp::AssociationParameters()
    );

    BOOST_CHECK(!association.is_associated());
}

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
    dcmtkpp::Association association;
    association.set_peer_host("pacs.example.com");
    association.set_peer_port(11112);
    association.update_parameters()
        .set_called_ae_title("remote")
        .set_user_identity_to_username_and_password("foo", "bar");

    dcmtkpp::Association const other(association);

    BOOST_CHECK_EQUAL(other.get_peer_host(), association.get_peer_host());
    BOOST_CHECK_EQUAL(other.get_peer_port(), association.get_peer_port());
    BOOST_CHECK(
        association.get_parameters() ==
            other.get_parameters()
    );
}

BOOST_AUTO_TEST_CASE(Assignment)
{
    dcmtkpp::Association association;
    association.set_peer_host("pacs.example.com");
    association.set_peer_port(11112);
    association.update_parameters()
        .set_called_ae_title("remote")
        .set_user_identity_to_username_and_password("foo", "bar");

    dcmtkpp::Association other;
    other = association;

    BOOST_CHECK_EQUAL(other.get_peer_host(), association.get_peer_host());
    BOOST_CHECK_EQUAL(other.get_peer_port(), association.get_peer_port());
    BOOST_CHECK(
        association.get_parameters() ==
            other.get_parameters()
    );
}

BOOST_AUTO_TEST_CASE(PeerHostName)
{
    dcmtkpp::Association association;
    association.set_peer_host("pacs.example.com");
    BOOST_CHECK_EQUAL(association.get_peer_host(), "pacs.example.com");
}

BOOST_AUTO_TEST_CASE(PeerPort)
{
    dcmtkpp::Association association;
    association.set_peer_port(11112);
    BOOST_CHECK_EQUAL(association.get_peer_port(), 11112);
}

BOOST_AUTO_TEST_CASE(AssociationParameters)
{
    dcmtkpp::Association association;

    dcmtkpp::AssociationParameters parameters;
    parameters.set_calling_ae_title("foo");
    association.set_parameters(parameters);

    BOOST_REQUIRE(association.get_parameters() == parameters);
}

BOOST_AUTO_TEST_CASE(Associate)
{
    PeerFixtureBase fixture({
        {
            1, dcmtkpp::registry::VerificationSOPClass,
            { dcmtkpp::registry::ImplicitVRLittleEndian }, true, false
        }
    });
    BOOST_CHECK_THROW(
        fixture.association.set_peer_host("foo"), dcmtkpp::Exception);
    BOOST_CHECK_THROW(
        fixture.association.set_peer_port(1234), dcmtkpp::Exception);
    BOOST_CHECK_THROW(
        fixture.association.update_parameters().set_maximum_length(123),
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
    BOOST_CHECK_THROW(association.abort(2, 4), dcmtkpp::Exception);
}
