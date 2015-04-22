#define BOOST_TEST_MODULE GetSCU
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/GetSCU.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    static bool called;

    DcmDataset query;

    Fixture()
    : PeerFixtureBase(NET_REQUESTOR, 104, 10,
        {
            {
                UID_GETPatientRootQueryRetrieveInformationModel,
                { UID_LittleEndianImplicitTransferSyntax }
            },
            {
                UID_RawDataStorage, { UID_LittleEndianImplicitTransferSyntax },
                ASC_SC_ROLE_SCP
            }
        })
    {
        Fixture::called = false;

        dcmtkpp::ElementAccessor<std::string>::set(this->query,
            DCM_QueryRetrieveLevel, "PATIENT");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->query, DCM_PatientName, "Doe^John");
    }


    static void callback(DcmDataset const *)
    {
        Fixture::called = true;
    }
};

bool Fixture::called = false;

BOOST_FIXTURE_TEST_CASE(Get, Fixture)
{
    dcmtkpp::GetSCU scu;
    scu.set_network(&this->network);
    scu.set_association(&this->association);

    scu.set_affected_sop_class(UID_GETPatientRootQueryRetrieveInformationModel);
    auto const results = scu.get(&this->query);

    BOOST_REQUIRE_EQUAL(results.size(), 1);
    BOOST_CHECK_EQUAL(
        dcmtkpp::ElementAccessor<std::string>::get(*results[0], DCM_SOPInstanceUID),
        "2.25.95090344942250266709587559073467305647");

    delete results[0];
}

BOOST_FIXTURE_TEST_CASE(GetCallback, Fixture)
{
    dcmtkpp::GetSCU scu;
    scu.set_network(&this->network);
    scu.set_association(&this->association);

    scu.set_affected_sop_class(UID_GETPatientRootQueryRetrieveInformationModel);
    scu.get(&this->query, Fixture::callback);

    BOOST_CHECK(Fixture::called);
}

