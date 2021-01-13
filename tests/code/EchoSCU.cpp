#define BOOST_TEST_MODULE EchoSCU
#include <boost/test/unit_test.hpp>

#include "odil/EchoSCU.h"
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

BOOST_FIXTURE_TEST_CASE(Echo, Fixture)
{
    odil::EchoSCU scu(this->association);
    scu.echo();
}
