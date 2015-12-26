#define BOOST_TEST_MODULE SCU
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/SCU.h"
#include "dcmtkpp/registry.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    Fixture()
    : PeerFixtureBase({
        { dcmtkpp::registry::VerificationSOPClass,
          {dcmtkpp::registry::ImplicitVRLittleEndian}
        }
    })
    {
        // Nothing else
    }
};

BOOST_FIXTURE_TEST_CASE(DefaultConstructor, Fixture)
{
    dcmtkpp::SCU const scu(this->association);
    BOOST_CHECK_EQUAL(scu.get_affected_sop_class(), "");
}

BOOST_FIXTURE_TEST_CASE(AffectedSOPClassUID, Fixture)
{
    dcmtkpp::SCU scu(this->association);
    scu.set_affected_sop_class("1.2.3");
    BOOST_CHECK_EQUAL(scu.get_affected_sop_class(), "1.2.3");
}

BOOST_FIXTURE_TEST_CASE(Echo, Fixture)
{
    dcmtkpp::SCU scu(this->association);
    scu.echo();
}
