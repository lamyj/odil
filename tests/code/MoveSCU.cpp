#define BOOST_TEST_MODULE MoveSCU
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/MoveSCU.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    static bool called;

    DcmDataset query;

    Fixture()
    : PeerFixtureBase(NET_ACCEPTORREQUESTOR, 11113, 10,
        {
            {
                UID_MOVEPatientRootQueryRetrieveInformationModel,
                { UID_LittleEndianImplicitTransferSyntax }
            },
            {
                UID_RawDataStorage, { UID_LittleEndianImplicitTransferSyntax },
                ASC_SC_ROLE_SCP
            }
        })
    {
        Fixture::called = false;

        dcmtkpp::ElementAccessor<EVR_CS>::set(this->query,
            DCM_QueryRetrieveLevel, "PATIENT");
        dcmtkpp::ElementAccessor<EVR_PN>::set(
            this->query, DCM_PatientName, "Doe^John");
    }

    static void callback(DcmDataset const *)
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

    scu.set_affected_sop_class(UID_MOVEPatientRootQueryRetrieveInformationModel);
    auto const results = scu.move(&this->query);

    BOOST_REQUIRE_EQUAL(results.size(), 1);
    BOOST_CHECK_EQUAL(
        dcmtkpp::ElementAccessor<EVR_UI>::get(*results[0], DCM_SOPInstanceUID),
        "2.25.95090344942250266709587559073467305647");

    delete results[0];
}

BOOST_FIXTURE_TEST_CASE(MoveCallback, Fixture)
{
    dcmtkpp::MoveSCU scu;
    scu.set_network(&this->network);
    scu.set_association(&this->association);
    scu.set_move_destination("LOCAL");

    scu.set_affected_sop_class(UID_MOVEPatientRootQueryRetrieveInformationModel);
    scu.move(&this->query, Fixture::callback);

    BOOST_CHECK(Fixture::called);
}
