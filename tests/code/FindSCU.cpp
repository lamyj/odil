#define BOOST_TEST_MODULE FindSCU
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/FindSCU.h"
#include "odil/registry.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    static bool called;

    std::shared_ptr<odil::DataSet> query;

    Fixture()
    : PeerFixtureBase({
            {
                1, odil::registry::PatientRootQueryRetrieveInformationModelFind,
                { odil::registry::ImplicitVRLittleEndian }, 
                odil::AssociationParameters::PresentationContext::Role::SCU
            }
        }),
      query(std::make_shared<odil::DataSet>())
    {
        Fixture::called = false;

        this->query->add("QueryRetrieveLevel", {"PATIENT"});
        this->query->add("PatientName", {"Doe^John"});
        this->query->add("PatientID");
    }


    static void callback(std::shared_ptr<odil::DataSet const>)
    {
        Fixture::called = true;
    }
};

bool Fixture::called = false;

BOOST_FIXTURE_TEST_CASE(Find, Fixture)
{
    odil::FindSCU scu(this->association);

    scu.set_affected_sop_class(odil::registry::PatientRootQueryRetrieveInformationModelFind);
    auto const results = scu.find(this->query);
    BOOST_REQUIRE(!this->query->empty());

    BOOST_REQUIRE_EQUAL(results.size(), 1);
    BOOST_CHECK(
        results[0]->as_string("PatientID") ==
            odil::Value::Strings({"DJ001"}));
}

BOOST_FIXTURE_TEST_CASE(FindCallback, Fixture)
{
    odil::FindSCU scu(this->association);

    scu.set_affected_sop_class(odil::registry::PatientRootQueryRetrieveInformationModelFind);
    scu.find(this->query, Fixture::callback);
    BOOST_REQUIRE(!this->query->empty());

    BOOST_CHECK(Fixture::called);
}
