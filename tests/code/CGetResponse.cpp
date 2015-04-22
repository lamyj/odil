#define BOOST_TEST_MODULE CGetResponse
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CGetResponse.h"
#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Message.h"

#include "../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::CGetResponse>
{
    DcmDataset command_set;
    DcmDataset data_set;

    Fixture()
    {
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DCM_CommandField, DIMSE_C_GET_RSP);
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DCM_MessageIDBeingRespondedTo, 1234);
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DCM_Status, STATUS_Success);

        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DCM_MessageID, 5678);
        dcmtkpp::ElementAccessor<std::string>::set(
            this->command_set, DCM_AffectedSOPClassUID,
            UID_GETStudyRootQueryRetrieveInformationModel);
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DcmTagKey(0x0000, 0x1020), 1);
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DcmTagKey(0x0000, 0x1021), 2);
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DcmTagKey(0x0000, 0x1022), 3);
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DcmTagKey(0x0000, 0x1023), 4);

        dcmtkpp::ElementAccessor<std::string>::set(
            this->data_set, DCM_PatientName, "Doe^John");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->data_set, DCM_PatientID, "DJ123");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->data_set, DCM_StudyDescription, "Brain");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->data_set, DCM_StudyInstanceUID, "1.2.3");
    }

    virtual void check(dcmtkpp::CGetResponse const & message)
    {
        BOOST_CHECK_EQUAL(message.get_command_field(), DIMSE_C_GET_RSP);
        BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
        BOOST_CHECK_EQUAL(message.get_status(), STATUS_Success);

        BOOST_CHECK(message.has_message_id());
        BOOST_CHECK_EQUAL(message.get_message_id(), 5678);

        BOOST_CHECK(message.has_affected_sop_class_uid());
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(),
            UID_GETStudyRootQueryRetrieveInformationModel);

        BOOST_CHECK(message.has_number_of_remaining_sub_operations());
        BOOST_CHECK_EQUAL(message.get_number_of_remaining_sub_operations(), 1);

        BOOST_CHECK(message.has_number_of_completed_sub_operations());
        BOOST_CHECK_EQUAL(message.get_number_of_completed_sub_operations(), 2);

        BOOST_CHECK(message.has_number_of_failed_sub_operations());
        BOOST_CHECK_EQUAL(message.get_number_of_failed_sub_operations(), 3);

        BOOST_CHECK(message.has_number_of_warning_sub_operations());
        BOOST_CHECK_EQUAL(message.get_number_of_warning_sub_operations(), 4);

        BOOST_CHECK_EQUAL(message.get_data_set(), &this->data_set);
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::CGetResponse message(1234, STATUS_Success, &this->data_set);
    message.set_message_id(5678);
    message.set_affected_sop_class_uid(
        UID_GETStudyRootQueryRetrieveInformationModel);
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
    dcmtkpp::ElementAccessor<Uint16>::set(
        this->command_set, DCM_CommandField, DIMSE_C_ECHO_RQ);
    this->check_message_constructor_throw(this->command_set, &this->data_set);
}
