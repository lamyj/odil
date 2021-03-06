#define BOOST_TEST_MODULE SCU
#include <boost/test/unit_test.hpp>

#include "odil/SCU.h"
#include "odil/registry.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    Fixture()
    : PeerFixtureBase({
        {
            1, odil::registry::Verification,
            {odil::registry::ImplicitVRLittleEndian}, 
            odil::AssociationParameters::PresentationContext::Role::SCU
        }
    })
    {
        // Nothing else
    }
};

BOOST_FIXTURE_TEST_CASE(DefaultConstructor, Fixture)
{
    odil::SCU const scu(this->association);
    BOOST_CHECK_EQUAL(scu.get_affected_sop_class(), "");
}

BOOST_FIXTURE_TEST_CASE(AffectedSOPClassUID, Fixture)
{
    odil::SCU scu(this->association);
    scu.set_affected_sop_class("1.2.3");
    BOOST_CHECK_EQUAL(scu.get_affected_sop_class(), "1.2.3");
}
