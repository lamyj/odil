#define BOOST_TEST_MODULE FindSCU
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/FindSCU.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    static bool called;

    DcmDataset query;

    Fixture()
    : PeerFixtureBase(NET_REQUESTOR, 104, 10,
        {
            {
                UID_FINDPatientRootQueryRetrieveInformationModel,
                { UID_LittleEndianImplicitTransferSyntax }
            }
        })
    {
        Fixture::called = false;

        dcmtkpp::ElementAccessor<EVR_CS>::set(this->query,
            DCM_QueryRetrieveLevel, "PATIENT");
        dcmtkpp::ElementAccessor<EVR_PN>::set(
            this->query, DCM_PatientName, "Doe^John");
        this->query.insertEmptyElement(DCM_SOPInstanceUID);
    }


    static void callback(DcmDataset const *)
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

    scu.set_affected_sop_class(UID_FINDPatientRootQueryRetrieveInformationModel);
    auto const results = scu.find(&this->query);

    BOOST_REQUIRE_EQUAL(results.size(), 1);
    BOOST_CHECK_EQUAL(
        dcmtkpp::ElementAccessor<EVR_UI>::get(*results[0], DCM_SOPInstanceUID),
        "2.25.95090344942250266709587559073467305647");

    delete results[0];
}

BOOST_FIXTURE_TEST_CASE(FindCallback, Fixture)
{
    dcmtkpp::FindSCU scu;
    scu.set_network(&this->network);
    scu.set_association(&this->association);

    scu.set_affected_sop_class(UID_FINDPatientRootQueryRetrieveInformationModel);
    scu.find(&this->query, Fixture::callback);

    BOOST_CHECK(Fixture::called);
}
