#define BOOST_TEST_MODULE FindSCU
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/FindSCU.h"
#include "dcmtkpp/registry.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    static bool called;

    dcmtkpp::DataSet query;

    Fixture()
    : PeerFixtureBase(NET_REQUESTOR, 104, 10,
        {
            {
                dcmtkpp::registry::PatientRootQueryRetrieveInformationModelFIND,
                { dcmtkpp::registry::ImplicitVRLittleEndian }
            }
        })
    {
        Fixture::called = false;

        this->query.add("QueryRetrieveLevel", {"PATIENT"});
        this->query.add("PatientName", {"Doe^John"});
        this->query.add("PatientID");
    }


    static void callback(dcmtkpp::DataSet const &)
    {
        Fixture::called = true;
    }
};

bool Fixture::called = false;

BOOST_FIXTURE_TEST_CASE(Find, Fixture)
{
    dcmtkpp::FindSCU scu;
    scu.set_network(&this->network);
    scu.set_association(&this->association);

    scu.set_affected_sop_class(dcmtkpp::registry::PatientRootQueryRetrieveInformationModelFIND);
    auto const results = scu.find(this->query);

    BOOST_REQUIRE_EQUAL(results.size(), 1);
    BOOST_CHECK(
        results[0].as_string("PatientID") ==
            dcmtkpp::Value::Strings({"DJ001"}));
}

BOOST_FIXTURE_TEST_CASE(FindCallback, Fixture)
{
    dcmtkpp::FindSCU scu;
    scu.set_network(&this->network);
    scu.set_association(&this->association);

    scu.set_affected_sop_class(dcmtkpp::registry::PatientRootQueryRetrieveInformationModelFIND);
    scu.find(this->query, Fixture::callback);

    BOOST_CHECK(Fixture::called);
}
