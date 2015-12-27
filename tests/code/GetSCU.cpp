#define BOOST_TEST_MODULE GetSCU
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/GetSCU.h"
#include "dcmtkpp/registry.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    static bool called;

    dcmtkpp::DataSet query;

    Fixture()
    : PeerFixtureBase({
            {
                1, dcmtkpp::registry::PatientRootQueryRetrieveInformationModelGET,
                { dcmtkpp::registry::ImplicitVRLittleEndian }, true, false
            },
            {
                3, dcmtkpp::registry::RawDataStorage,
                { dcmtkpp::registry::ImplicitVRLittleEndian }, false, true
            }
        })
    {
        Fixture::called = false;

        this->query.add("QueryRetrieveLevel", {"PATIENT"});
        this->query.add("PatientName", {"Doe^John"});
    }


    static void callback(dcmtkpp::DataSet const &)
    {
        Fixture::called = true;
    }
};

bool Fixture::called = false;

BOOST_FIXTURE_TEST_CASE(Get, Fixture)
{
    dcmtkpp::GetSCU scu(this->association);

    scu.set_affected_sop_class(
        dcmtkpp::registry::PatientRootQueryRetrieveInformationModelGET);
    auto const results = scu.get(this->query);

    BOOST_REQUIRE_EQUAL(results.size(), 1);
    BOOST_CHECK(
        results[0].as_string("SOPInstanceUID") ==
            dcmtkpp::Value::Strings(
                {"2.25.95090344942250266709587559073467305647"}));
}

BOOST_FIXTURE_TEST_CASE(GetCallback, Fixture)
{
    dcmtkpp::GetSCU scu(this->association);

    scu.set_affected_sop_class(
        dcmtkpp::registry::PatientRootQueryRetrieveInformationModelGET);
    scu.get(this->query, Fixture::callback);

    BOOST_CHECK(Fixture::called);
}

