#define BOOST_TEST_MODULE CFindResponse
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CFindResponse.h"
#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Message.h"

struct Fixture
{
    DcmDataset query;

    Fixture()
    {
        dcmtkpp::ElementAccessor<EVR_PN>::set(
            query, DCM_PatientName, "Doe^John");
        dcmtkpp::ElementAccessor<EVR_LO>::set(query, DCM_PatientID, "DJ123");
        dcmtkpp::ElementAccessor<EVR_LO>::set(
            query, DCM_StudyDescription, "Brain");
        dcmtkpp::ElementAccessor<EVR_UI>::set(
            query, DCM_StudyInstanceUID, "1.2.3");
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::CFindResponse message(1234, STATUS_Success, &this->query);
    message.set_affected_sop_class_uid(
        UID_FINDStudyRootQueryRetrieveInformationModel);

    BOOST_CHECK_EQUAL(message.get_command_field(), DIMSE_C_FIND_RSP);

    BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);

    BOOST_CHECK_EQUAL(message.get_status(), STATUS_Success);

    BOOST_CHECK(message.has_affected_sop_class_uid());
    BOOST_CHECK_EQUAL(
        message.get_affected_sop_class_uid(),
        UID_FINDStudyRootQueryRetrieveInformationModel);

    BOOST_CHECK_EQUAL(message.get_data_set(), &this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    DcmDataset command_set;
    dcmtkpp::ElementAccessor<EVR_US>::set(
        command_set, DCM_CommandField, DIMSE_C_FIND_RSP);
    dcmtkpp::ElementAccessor<EVR_US>::set(
        command_set, DCM_MessageIDBeingRespondedTo, 1234);
    dcmtkpp::ElementAccessor<EVR_US>::set(
        command_set, DCM_Status, STATUS_Success);
    dcmtkpp::ElementAccessor<EVR_UI>::set(
        command_set, DCM_AffectedSOPClassUID,
        UID_FINDStudyRootQueryRetrieveInformationModel);

    dcmtkpp::Message const generic_message(command_set, &this->query);

    dcmtkpp::CFindResponse const message(generic_message);

    BOOST_CHECK_EQUAL(message.get_command_field(), DIMSE_C_FIND_RSP);

    BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);

    BOOST_CHECK_EQUAL(message.get_status(), STATUS_Success);

    BOOST_CHECK(message.has_affected_sop_class_uid());
    BOOST_CHECK_EQUAL(
        message.get_affected_sop_class_uid(),
        UID_FINDStudyRootQueryRetrieveInformationModel);

    BOOST_CHECK_EQUAL(message.get_data_set(), &this->query);
}
