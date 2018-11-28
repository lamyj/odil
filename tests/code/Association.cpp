#define BOOST_TEST_MODULE Association
#include <boost/test/unit_test.hpp>

#include <ostream>

#include "odil/Association.h"
#include "odil/Exception.h"
#include "odil/registry.h"

#include "../PeerFixtureBase.h"

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    odil::Association association;
    BOOST_CHECK_EQUAL(association.get_peer_host(), "");
    BOOST_CHECK_EQUAL(association.get_peer_port(), 104);
    BOOST_CHECK(
        association.get_parameters() ==
            odil::AssociationParameters()
    );

    BOOST_CHECK(!association.is_associated());
}

BOOST_AUTO_TEST_CASE(PeerHostName)
{
    odil::Association association;
    association.set_peer_host("pacs.example.com");
    BOOST_CHECK_EQUAL(association.get_peer_host(), "pacs.example.com");
}

BOOST_AUTO_TEST_CASE(PeerPort)
{
    odil::Association association;
    association.set_peer_port(11112);
    BOOST_CHECK_EQUAL(association.get_peer_port(), 11112);
}

BOOST_AUTO_TEST_CASE(AssociationParameters)
{
    odil::Association association;

    odil::AssociationParameters parameters;
    parameters.set_calling_ae_title("foo");
    association.set_parameters(parameters);

    BOOST_REQUIRE(association.get_parameters() == parameters);
}

BOOST_AUTO_TEST_CASE(Associate)
{
    PeerFixtureBase fixture({
        {
            1, odil::registry::VerificationSOPClass,
            { odil::registry::ImplicitVRLittleEndian }, true, false
        }
    });
    BOOST_CHECK_THROW(
        fixture.association.set_peer_host("foo"), odil::Exception);
    BOOST_CHECK_THROW(
        fixture.association.set_peer_port(1234), odil::Exception);
    BOOST_CHECK_THROW(
        fixture.association.update_parameters().set_maximum_length(123),
        odil::Exception);
}

BOOST_AUTO_TEST_CASE(Release)
{
    odil::Association association;
    BOOST_CHECK_THROW(association.release(), odil::Exception);
}

BOOST_AUTO_TEST_CASE(Abort)
{
    odil::Association association;
    BOOST_CHECK_THROW(association.abort(2, 4), odil::Exception);
}
