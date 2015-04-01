#define BOOST_TEST_MODULE CFindRequest
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CFindRequest.h"
#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Message.h"

struct Fixture
{
    DcmDataset query;

    Fixture()
    {
        dcmtkpp::ElementAccessor<EVR_PN>::set(
            query, DCM_PatientName, "Doe^John");
        dcmtkpp::ElementAccessor<EVR_LO>::set(
            query, DCM_StudyDescription, "Brain");
        dcmtkpp::ElementAccessor<EVR_CS>::set(
            query, DCM_QueryRetrieveLevel, "STUDY");
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::CFindRequest const message(
        1234, UID_FINDPatientRootQueryRetrieveInformationModel,
        DIMSE_PRIORITY_MEDIUM, &this->query);

    BOOST_CHECK_EQUAL(message.get_command_field(), DIMSE_C_FIND_RQ);

    BOOST_CHECK_EQUAL(message.get_message_id(), 1234);

    BOOST_CHECK_EQUAL(
        message.get_affected_sop_class_uid(),
        UID_FINDPatientRootQueryRetrieveInformationModel);

    BOOST_CHECK_EQUAL(message.get_data_set(), &this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    DcmDataset command_set;
    dcmtkpp::ElementAccessor<EVR_US>::set(
        command_set, DCM_CommandField, DIMSE_C_FIND_RQ);
    dcmtkpp::ElementAccessor<EVR_US>::set(command_set, DCM_MessageID, 1234);
    dcmtkpp::ElementAccessor<EVR_UI>::set(
        command_set, DCM_AffectedSOPClassUID,
        UID_FINDPatientRootQueryRetrieveInformationModel);
    dcmtkpp::ElementAccessor<EVR_US>::set(
        command_set, DCM_Priority, DIMSE_PRIORITY_MEDIUM);


    dcmtkpp::Message const generic_message(command_set, &this->query);

    dcmtkpp::CFindRequest const message(generic_message);

    BOOST_CHECK_EQUAL(message.get_command_field(), DIMSE_C_FIND_RQ);

    BOOST_CHECK_EQUAL(message.get_message_id(), 1234);

    BOOST_CHECK_EQUAL(
        message.get_affected_sop_class_uid(),
        UID_FINDPatientRootQueryRetrieveInformationModel);

    BOOST_CHECK_EQUAL(message.get_data_set(), &this->query);
}
