#define BOOST_TEST_MODULE GetSCU
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/GetSCU.h"
#include "odil/registry.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    static bool called;

    odil::DataSet query;

    Fixture()
    : PeerFixtureBase({
            {
                1, odil::registry::PatientRootQueryRetrieveInformationModelGET,
                { odil::registry::ImplicitVRLittleEndian }, true, false
            },
            {
                3, odil::registry::RawDataStorage,
                { odil::registry::ImplicitVRLittleEndian }, false, true
            }
        })
    {
        Fixture::called = false;

        this->query.add("QueryRetrieveLevel", {"PATIENT"});
        this->query.add("PatientName", {"Doe^John"});
    }


    static void callback(odil::DataSet const &)
    {
        Fixture::called = true;
    }
};

bool Fixture::called = false;

BOOST_FIXTURE_TEST_CASE(Get, Fixture)
{
    odil::GetSCU scu(this->association);

    scu.set_affected_sop_class(
        odil::registry::PatientRootQueryRetrieveInformationModelGET);
    auto const results = scu.get(this->query);

    BOOST_REQUIRE_EQUAL(results.size(), 1);
    BOOST_CHECK(
        results[0].as_string("SOPInstanceUID") ==
            odil::Value::Strings(
                {"2.25.95090344942250266709587559073467305647"}));
}

BOOST_FIXTURE_TEST_CASE(GetCallback, Fixture)
{
    odil::GetSCU scu(this->association);

    scu.set_affected_sop_class(
        odil::registry::PatientRootQueryRetrieveInformationModelGET);
    scu.get(this->query, Fixture::callback);

    BOOST_CHECK(Fixture::called);
}

