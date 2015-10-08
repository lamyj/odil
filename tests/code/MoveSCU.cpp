#define BOOST_TEST_MODULE MoveSCU
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/MoveSCU.h"
#include "dcmtkpp/registry.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    static bool called;

    dcmtkpp::DataSet query;

    Fixture()
    : PeerFixtureBase(NET_ACCEPTORREQUESTOR, 11113, 10,
        {
            {
                dcmtkpp::registry::PatientRootQueryRetrieveInformationModelMOVE,
                { dcmtkpp::registry::ImplicitVRLittleEndian }
            },
            {
                dcmtkpp::registry::RawDataStorage, { dcmtkpp::registry::ImplicitVRLittleEndian },
                ASC_SC_ROLE_SCP
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

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::MoveSCU const scu;
    BOOST_CHECK_EQUAL(scu.get_move_destination(), "");
}

BOOST_AUTO_TEST_CASE(MoveDestination)
{
    dcmtkpp::MoveSCU scu;
    scu.set_move_destination("remote");
    BOOST_CHECK_EQUAL(scu.get_move_destination(), "remote");
}

BOOST_FIXTURE_TEST_CASE(Move, Fixture)
{
    dcmtkpp::MoveSCU scu;
    scu.set_network(&this->network);
    scu.set_association(&this->association);
    scu.set_move_destination("LOCAL");

    scu.set_affected_sop_class(dcmtkpp::registry::PatientRootQueryRetrieveInformationModelMOVE);
    auto const results = scu.move(this->query);

    BOOST_REQUIRE_EQUAL(results.size(), 1);
    BOOST_CHECK(
        results[0].as_string("SOPInstanceUID") ==
            dcmtkpp::Value::Strings{"2.25.95090344942250266709587559073467305647"});
}

BOOST_FIXTURE_TEST_CASE(MoveCallback, Fixture)
{
    dcmtkpp::MoveSCU scu;
    scu.set_network(&this->network);
    scu.set_association(&this->association);
    scu.set_move_destination("LOCAL");

    scu.set_affected_sop_class(dcmtkpp::registry::PatientRootQueryRetrieveInformationModelMOVE);
    scu.move(this->query, Fixture::callback);

    BOOST_CHECK(Fixture::called);
}
