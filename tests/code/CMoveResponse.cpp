#define BOOST_TEST_MODULE CMoveResponse
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CMoveResponse.h"
#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Message.h"

#include "../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::CMoveResponse>
{
    DcmDataset command_set;
    DcmDataset data_set;

    Fixture()
    {
        dcmtkpp::ElementAccessor<EVR_US>::set(
            this->command_set, DCM_CommandField, DIMSE_C_MOVE_RSP);
        dcmtkpp::ElementAccessor<EVR_US>::set(
            this->command_set, DCM_MessageIDBeingRespondedTo, 1234);
        dcmtkpp::ElementAccessor<EVR_US>::set(
            this->command_set, DCM_Status, STATUS_Success);

        dcmtkpp::ElementAccessor<EVR_US>::set(
            this->command_set, DCM_MessageID, 5678);
        dcmtkpp::ElementAccessor<EVR_UI>::set(
            this->command_set, DCM_AffectedSOPClassUID,
            UID_MOVEStudyRootQueryRetrieveInformationModel);
        dcmtkpp::ElementAccessor<EVR_US>::set(
            this->command_set, DcmTagKey(0x0000, 0x1020), 1);
        dcmtkpp::ElementAccessor<EVR_US>::set(
            this->command_set, DcmTagKey(0x0000, 0x1021), 2);
        dcmtkpp::ElementAccessor<EVR_US>::set(
            this->command_set, DcmTagKey(0x0000, 0x1022), 3);
        dcmtkpp::ElementAccessor<EVR_US>::set(
            this->command_set, DcmTagKey(0x0000, 0x1023), 4);

        dcmtkpp::ElementAccessor<EVR_PN>::set(
            this->data_set, DCM_PatientName, "Doe^John");
        dcmtkpp::ElementAccessor<EVR_LO>::set(
            this->data_set, DCM_PatientID, "DJ123");
        dcmtkpp::ElementAccessor<EVR_LO>::set(
            this->data_set, DCM_StudyDescription, "Brain");
        dcmtkpp::ElementAccessor<EVR_UI>::set(
            this->data_set, DCM_StudyInstanceUID, "1.2.3");
    }

    virtual void check(dcmtkpp::CMoveResponse const & message)
    {
        BOOST_CHECK_EQUAL(message.get_command_field(), DIMSE_C_MOVE_RSP);
        BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
        BOOST_CHECK_EQUAL(message.get_status(), STATUS_Success);

        BOOST_CHECK(message.has_message_id());
        BOOST_CHECK_EQUAL(message.get_message_id(), 5678);

        BOOST_CHECK(message.has_affected_sop_class_uid());
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(),
            UID_MOVEStudyRootQueryRetrieveInformationModel);

        BOOST_CHECK(message.has_number_of_remaining_sub_operations());
        BOOST_CHECK_EQUAL(message.get_number_of_remaining_sub_operations(), 1);

        BOOST_CHECK(message.has_number_of_completed_sub_operations());
        BOOST_CHECK_EQUAL(message.get_number_of_completed_sub_operations(), 2);

        BOOST_CHECK(message.has_number_of_failed_sub_operations());
        BOOST_CHECK_EQUAL(message.get_number_of_failed_sub_operations(), 3);

        BOOST_CHECK(message.has_number_of_warning_sub_operations());
        BOOST_CHECK_EQUAL(message.get_number_of_warning_sub_operations(), 4);

        BOOST_CHECK_EQUAL(message.get_data_set(), &this->data_set);

        BOOST_CHECK_EQUAL(message.get_data_set(), &this->data_set);
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::CMoveResponse message(1234, STATUS_Success, &this->data_set);
    message.set_message_id(5678);
    message.set_affected_sop_class_uid(
        UID_MOVEStudyRootQueryRetrieveInformationModel);
    message.set_number_of_remaining_sub_operations(1);
    message.set_number_of_completed_sub_operations(2);
    message.set_number_of_failed_sub_operations(3);
    message.set_number_of_warning_sub_operations(4);

    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set, &this->data_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    dcmtkpp::ElementAccessor<EVR_US>::set(
        this->command_set, DCM_CommandField, DIMSE_C_ECHO_RQ);
    this->check_message_constructor_throw(this->command_set, &this->data_set);
}
