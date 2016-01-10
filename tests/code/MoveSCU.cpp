#define BOOST_TEST_MODULE MoveSCU
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/MoveSCU.h"
#include "odil/registry.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    static bool called;

    odil::DataSet query;

    Fixture()
    : PeerFixtureBase({
            {
                1, odil::registry::PatientRootQueryRetrieveInformationModelMOVE,
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

BOOST_FIXTURE_TEST_CASE(DefaultConstructor, Fixture)
{
    odil::MoveSCU const scu(this->association);
    BOOST_CHECK_EQUAL(scu.get_move_destination(), "");
}

BOOST_FIXTURE_TEST_CASE(MoveDestination, Fixture)
{
    odil::MoveSCU scu(this->association);
    scu.set_move_destination("remote");
    BOOST_CHECK_EQUAL(scu.get_move_destination(), "remote");
}

BOOST_FIXTURE_TEST_CASE(Move, Fixture)
{
    odil::MoveSCU scu(this->association);
    scu.set_move_destination("LOCAL");

    scu.set_affected_sop_class(
        odil::registry::PatientRootQueryRetrieveInformationModelMOVE);
    auto const results = scu.move(this->query);

    BOOST_REQUIRE_EQUAL(results.size(), 1);
    BOOST_CHECK(
        results[0].as_string("SOPInstanceUID") ==
            odil::Value::Strings{"2.25.95090344942250266709587559073467305647"});
}

BOOST_FIXTURE_TEST_CASE(MoveCallback, Fixture)
{
    odil::MoveSCU scu(this->association);
    scu.set_move_destination("LOCAL");

    scu.set_affected_sop_class(
        odil::registry::PatientRootQueryRetrieveInformationModelMOVE);
    scu.move(this->query, Fixture::callback);

    BOOST_CHECK(Fixture::called);
}
