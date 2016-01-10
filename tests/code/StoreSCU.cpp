#define BOOST_TEST_MODULE StoreSCU
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/registry.h"
#include "odil/StoreSCU.h"

#include "../PeerFixtureBase.h"

struct Fixture: public PeerFixtureBase
{
    odil::DataSet dataset;

    Fixture()
    : PeerFixtureBase({
        {
            1, odil::registry::RawDataStorage,
            {odil::registry::ImplicitVRLittleEndian}, true, false
        }
    })
    {
        this->dataset.add("ImageType", {"ORIGINAL", "PRIMARY", "OTHER"});
        this->dataset.add("PatientID", {"1234"});
        this->dataset.add("StudyInstanceUID", {"2.25.386726390606491051215227596277040710"});
        this->dataset.add("SeriesInstanceUID", {"2.25.235367796740370588607388995952651763168"});
        this->dataset.add("SOPClassUID", {odil::registry::RawDataStorage});
        this->dataset.add("SOPInstanceUID", {"2.25.294312554735929033890522327215919068328"});
    }

};

BOOST_FIXTURE_TEST_CASE(AffectedSOPClassUID, Fixture)
{
    odil::DataSet dataset;
    dataset.add("SOPClassUID", {odil::registry::RawDataStorage});

    odil::StoreSCU scu(this->association);
    scu.set_affected_sop_class(dataset);
    BOOST_CHECK_EQUAL(scu.get_affected_sop_class(), odil::registry::RawDataStorage);
}

BOOST_FIXTURE_TEST_CASE(AffectedSOPClassUIDNoSOPClassUID, Fixture)
{
    odil::DataSet dataset;

    odil::StoreSCU scu(this->association);
    BOOST_CHECK_THROW(scu.set_affected_sop_class(dataset), odil::Exception);
}

BOOST_FIXTURE_TEST_CASE(AffectedSOPClassUIDUnknownSOPClassUID, Fixture)
{
    odil::DataSet dataset;
    dataset.add("SOPClassUID", {"invalid"});

    odil::StoreSCU scu(this->association);
    BOOST_CHECK_THROW(scu.set_affected_sop_class(dataset), odil::Exception);
}

BOOST_FIXTURE_TEST_CASE(Store, Fixture)
{
    odil::StoreSCU scu(this->association);

    scu.set_affected_sop_class(this->dataset);
    scu.store(this->dataset);
}
