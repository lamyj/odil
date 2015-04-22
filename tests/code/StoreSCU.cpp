#define BOOST_TEST_MODULE StoreSCU
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/StoreSCU.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    static bool called;

    DcmDataset dataset;

    Fixture()
    : PeerFixtureBase(NET_REQUESTOR, 104, 10,
        {
            { UID_RawDataStorage,
                {UID_LittleEndianImplicitTransferSyntax}
            }
        })
    {
        Fixture::called = false;

        dcmtkpp::ElementAccessor<std::string>::set(
            this->dataset, DCM_ImageType, "ORIGINAL\\PRIMARY\\OTHER");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->dataset, DCM_PatientID, "1234");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->dataset, DCM_ImageType, "ORIGINAL\\PRIMARY\\OTHER");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->dataset, DCM_StudyInstanceUID, "2.25.386726390606491051215227596277040710");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->dataset, DCM_SeriesInstanceUID, "2.25.235367796740370588607388995952651763168");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->dataset, DCM_SOPClassUID, UID_RawDataStorage);
        dcmtkpp::ElementAccessor<std::string>::set(
            this->dataset, DCM_SOPInstanceUID, "2.25.294312554735929033890522327215919068328");
    }


    static void callback(void*, unsigned long)
    {
        Fixture::called = true;
    }
};

bool Fixture::called = false;

BOOST_AUTO_TEST_CASE(AffectedSOPClassUID)
{
    DcmDataset dataset;
    dcmtkpp::ElementAccessor<std::string>::set(
        dataset, DCM_SOPClassUID, UID_RawDataStorage);

    dcmtkpp::StoreSCU scu;
    scu.set_affected_sop_class(&dataset);
    BOOST_CHECK_EQUAL(scu.get_affected_sop_class(), UID_RawDataStorage);
}

BOOST_AUTO_TEST_CASE(AffectedSOPClassUIDNoSOPClassUID)
{
    DcmDataset dataset;

    dcmtkpp::StoreSCU scu;
    BOOST_CHECK_THROW(scu.set_affected_sop_class(&dataset), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(AffectedSOPClassUIDUnknownSOPClassUID)
{
    DcmDataset dataset;
    dcmtkpp::ElementAccessor<std::string>::set(dataset, DCM_SOPClassUID, "invalid");

    dcmtkpp::StoreSCU scu;
    BOOST_CHECK_THROW(scu.set_affected_sop_class(&dataset), dcmtkpp::Exception);
}

BOOST_FIXTURE_TEST_CASE(Store, Fixture)
{
    dcmtkpp::StoreSCU scu;
    scu.set_network(&this->network);
    scu.set_association(&this->association);

    scu.set_affected_sop_class(&this->dataset);
    scu.store(&this->dataset, Fixture::callback);
    BOOST_CHECK(this->called);
}
