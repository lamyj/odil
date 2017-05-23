#define BOOST_TEST_MODULE MoveSCU
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/MoveSCU.h"
#include "odil/registry.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    static bool store_callback_called;
    static bool move_callback_called;

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
        Fixture::store_callback_called = false;
        Fixture::move_callback_called = false;

        this->query.add("QueryRetrieveLevel", {"PATIENT"});
        this->query.add("PatientName", {"Doe^John"});
    }

    static void store_callback(odil::DataSet const &)
    {
        Fixture::store_callback_called = true;
    }

    static void move_callback(odil::message::CMoveResponse const &)
    {
        Fixture::move_callback_called = true;
    }
};

bool Fixture::store_callback_called = false;
bool Fixture::move_callback_called = false;

BOOST_FIXTURE_TEST_CASE(DefaultConstructor, Fixture)
{
    odil::MoveSCU const scu(this->association);
    BOOST_CHECK_EQUAL(scu.get_move_destination(), "");
    BOOST_CHECK_EQUAL(scu.get_incoming_port(), 0);
}

BOOST_FIXTURE_TEST_CASE(MoveDestination, Fixture)
{
    odil::MoveSCU scu(this->association);
    scu.set_move_destination("remote");
    BOOST_CHECK_EQUAL(scu.get_move_destination(), "remote");
}

BOOST_FIXTURE_TEST_CASE(IncomingPort, Fixture)
{
    odil::MoveSCU scu(this->association);
    scu.set_incoming_port(11113);
    BOOST_CHECK_EQUAL(scu.get_incoming_port(), 11113);
}

BOOST_FIXTURE_TEST_CASE(Move, Fixture)
{
    odil::MoveSCU scu(this->association);
    scu.set_move_destination("LOCAL");
    scu.set_incoming_port(11113);

    scu.set_affected_sop_class(
        odil::registry::PatientRootQueryRetrieveInformationModelMOVE);
    auto const results = scu.move(this->query);

    BOOST_REQUIRE_EQUAL(results.size(), 1);
    BOOST_CHECK(
        results[0].as_string("SOPInstanceUID") ==
            odil::Value::Strings{"2.25.95090344942250266709587559073467305647"});
}

BOOST_FIXTURE_TEST_CASE(MoveMove, Fixture)
{
    odil::MoveSCU scu(this->association);
    scu.set_move_destination("LOCAL");
    scu.set_incoming_port(11113);

    scu.set_affected_sop_class(
        odil::registry::PatientRootQueryRetrieveInformationModelMOVE);
    auto const results = scu.move(std::move(this->query));

    BOOST_REQUIRE_EQUAL(results.size(), 1);
    BOOST_CHECK(
        results[0].as_string("SOPInstanceUID") ==
            odil::Value::Strings{"2.25.95090344942250266709587559073467305647"});
}

BOOST_FIXTURE_TEST_CASE(MoveBothCallback, Fixture)
{
    odil::MoveSCU scu(this->association);
    scu.set_move_destination("LOCAL");
    scu.set_incoming_port(11113);

    scu.set_affected_sop_class(
        odil::registry::PatientRootQueryRetrieveInformationModelMOVE);
    scu.move(this->query, Fixture::store_callback, Fixture::move_callback);

    BOOST_CHECK(Fixture::store_callback_called);
    BOOST_CHECK(Fixture::move_callback_called);
}

BOOST_FIXTURE_TEST_CASE(MoveBothCallbackMove, Fixture)
{
    odil::MoveSCU scu(this->association);
    scu.set_move_destination("LOCAL");
    scu.set_incoming_port(11113);

    scu.set_affected_sop_class(
        odil::registry::PatientRootQueryRetrieveInformationModelMOVE);
    scu.move(
        std::move(this->query), Fixture::store_callback,
        Fixture::move_callback);

    BOOST_CHECK(Fixture::store_callback_called);
    BOOST_CHECK(Fixture::move_callback_called);
}

BOOST_FIXTURE_TEST_CASE(MoveOnlyStoreCallback, Fixture)
{
    odil::MoveSCU scu(this->association);
    scu.set_move_destination("LOCAL");
    scu.set_incoming_port(11113);

    scu.set_affected_sop_class(
        odil::registry::PatientRootQueryRetrieveInformationModelMOVE);
    scu.move(
        this->query, Fixture::store_callback, odil::MoveSCU::MoveCallback());

    BOOST_CHECK(Fixture::store_callback_called);
    BOOST_CHECK(!Fixture::move_callback_called);
}

BOOST_FIXTURE_TEST_CASE(MoveOnlyStoreCallbackMove, Fixture)
{
    odil::MoveSCU scu(this->association);
    scu.set_move_destination("LOCAL");
    scu.set_incoming_port(11113);

    scu.set_affected_sop_class(
        odil::registry::PatientRootQueryRetrieveInformationModelMOVE);
    scu.move(
        std::move(this->query), Fixture::store_callback,
        odil::MoveSCU::MoveCallback());

    BOOST_CHECK(Fixture::store_callback_called);
    BOOST_CHECK(!Fixture::move_callback_called);
}
