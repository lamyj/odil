#define BOOST_TEST_MODULE StoreSCU
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/StoreSCU.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    dcmtkpp::DataSet dataset;

    Fixture()
    : PeerFixtureBase({
        {
            1, dcmtkpp::registry::RawDataStorage,
            {dcmtkpp::registry::ImplicitVRLittleEndian}, true, false
        }
    })
    {
        this->dataset.add("ImageType", {"ORIGINAL", "PRIMARY", "OTHER"});
        this->dataset.add("PatientID", {"1234"});
        this->dataset.add("StudyInstanceUID", {"2.25.386726390606491051215227596277040710"});
        this->dataset.add("SeriesInstanceUID", {"2.25.235367796740370588607388995952651763168"});
        this->dataset.add("SOPClassUID", {dcmtkpp::registry::RawDataStorage});
        this->dataset.add("SOPInstanceUID", {"2.25.294312554735929033890522327215919068328"});
    }

};

BOOST_FIXTURE_TEST_CASE(AffectedSOPClassUID, Fixture)
{
    dcmtkpp::DataSet dataset;
    dataset.add("SOPClassUID", {dcmtkpp::registry::RawDataStorage});

    dcmtkpp::StoreSCU scu(this->association);
    scu.set_affected_sop_class(dataset);
    BOOST_CHECK_EQUAL(scu.get_affected_sop_class(), dcmtkpp::registry::RawDataStorage);
}

BOOST_FIXTURE_TEST_CASE(AffectedSOPClassUIDNoSOPClassUID, Fixture)
{
    dcmtkpp::DataSet dataset;

    dcmtkpp::StoreSCU scu(this->association);
    BOOST_CHECK_THROW(scu.set_affected_sop_class(dataset), dcmtkpp::Exception);
}

BOOST_FIXTURE_TEST_CASE(AffectedSOPClassUIDUnknownSOPClassUID, Fixture)
{
    dcmtkpp::DataSet dataset;
    dataset.add("SOPClassUID", {"invalid"});

    dcmtkpp::StoreSCU scu(this->association);
    BOOST_CHECK_THROW(scu.set_affected_sop_class(dataset), dcmtkpp::Exception);
}

BOOST_FIXTURE_TEST_CASE(Store, Fixture)
{
    dcmtkpp::StoreSCU scu(this->association);

    scu.set_affected_sop_class(this->dataset);
    scu.store(this->dataset);
}
