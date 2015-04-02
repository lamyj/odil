#define BOOST_TEST_MODULE ElementAccessor
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/ElementAccessor.h"

struct Fixture
{
    DcmDataset dataset;

    Fixture()
    {
        OFCondition condition;
        condition = dataset.putAndInsertOFStringArray(DCM_PatientID, "DJ123");
        if(condition.bad())
        {
            throw dcmtkpp::Exception(condition);
        }

        condition = dataset.putAndInsertUint16(DCM_MessageID, 1234);
        if(condition.bad())
        {
            throw dcmtkpp::Exception(condition);
        }
    }
};

BOOST_FIXTURE_TEST_CASE(GetCorrectVRString, Fixture)
{
    BOOST_CHECK_EQUAL(
        dcmtkpp::ElementAccessor<EVR_LO>::get(this->dataset, DCM_PatientID),
        "DJ123");
}

BOOST_FIXTURE_TEST_CASE(GetCorrectVRNonString, Fixture)
{
    BOOST_CHECK_EQUAL(
        dcmtkpp::ElementAccessor<EVR_US>::get(this->dataset, DCM_MessageID),
        1234);
}

BOOST_FIXTURE_TEST_CASE(GetWrongVRString, Fixture)
{
    BOOST_CHECK_THROW(
        dcmtkpp::ElementAccessor<EVR_PN>::get(this->dataset, DCM_PatientID),
        dcmtkpp::Exception);
}

BOOST_FIXTURE_TEST_CASE(GetWrongVRNonString, Fixture)
{
    BOOST_CHECK_THROW(
        dcmtkpp::ElementAccessor<EVR_FL>::get(this->dataset, DCM_MessageID),
        dcmtkpp::Exception);
}

BOOST_FIXTURE_TEST_CASE(SetEmpty, Fixture)
{
    dcmtkpp::ElementAccessor<EVR_PN>::set(this->dataset, DCM_PatientName, "FOO");
    OFString value;
    OFCondition const condition =
        this->dataset.findAndGetOFString(DCM_PatientName, value);
    BOOST_REQUIRE(condition.good());
    BOOST_CHECK_EQUAL(std::string(value.c_str()), "FOO");
}

BOOST_FIXTURE_TEST_CASE(SetWrongVRString, Fixture)
{
    BOOST_CHECK_THROW(
        dcmtkpp::ElementAccessor<EVR_LO>::set(
            this->dataset, DCM_PatientName, "FOO"),
        dcmtkpp::Exception);
}

BOOST_FIXTURE_TEST_CASE(SetWrongVRNonString, Fixture)
{
    BOOST_CHECK_THROW(
        dcmtkpp::ElementAccessor<EVR_FD>::set(
            this->dataset, DCM_Status, STATUS_Success),
        dcmtkpp::Exception);
}

BOOST_FIXTURE_TEST_CASE(SetExisting, Fixture)
{
    dcmtkpp::ElementAccessor<EVR_LO>::set(this->dataset, DCM_PatientID, "FOO");
    OFString value;
    OFCondition const condition =
        this->dataset.findAndGetOFString(DCM_PatientID, value);
    BOOST_REQUIRE(condition.good());
    BOOST_CHECK_EQUAL(std::string(value.c_str()), "FOO");
}

BOOST_FIXTURE_TEST_CASE(Has, Fixture)
{
    BOOST_CHECK(
        dcmtkpp::ElementAccessor<EVR_LO>::has(this->dataset, DCM_PatientID));
}

BOOST_FIXTURE_TEST_CASE(HasNot, Fixture)
{
    BOOST_CHECK(
        !dcmtkpp::ElementAccessor<EVR_LO>::has(this->dataset, DCM_PatientName));
}
