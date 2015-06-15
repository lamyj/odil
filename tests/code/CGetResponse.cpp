#define BOOST_TEST_MODULE CGetResponse
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CGetResponse.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Message.h"
#include "dcmtkpp/registry.h"

#include "../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::CGetResponse>
{
    dcmtkpp::DataSet command_set;
    dcmtkpp::DataSet data_set;

    Fixture()
    {
        this->command_set.add("CommandField", {dcmtkpp::Message::Command::C_GET_RSP});
        this->command_set.add("MessageIDBeingRespondedTo", {1234});
        this->command_set.add("Status", {STATUS_Success});

        this->command_set.add("MessageID", {5678});
        this->command_set.add("AffectedSOPClassUID",
            {UID_GETStudyRootQueryRetrieveInformationModel});
        this->command_set.add(dcmtkpp::registry::NumberOfRemainingSuboperations, {1});
        this->command_set.add(dcmtkpp::registry::NumberOfCompletedSuboperations, {2});
        this->command_set.add(dcmtkpp::registry::NumberOfFailedSuboperations, {3});
        this->command_set.add(dcmtkpp::registry::NumberOfWarningSuboperations, {4});

        this->data_set.add("PatientName", {"Doe^John"});
        this->data_set.add("PatientID", {"DJ123"});
        this->data_set.add("StudyDescription", {"Brain"});
        this->data_set.add("StudyInstanceUID", {"1.2.3"});
    }

    virtual void check(dcmtkpp::CGetResponse const & message)
    {
        BOOST_CHECK_EQUAL(message.get_command_field(), dcmtkpp::Message::Command::C_GET_RSP);
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

        BOOST_CHECK(message.has_data_set());
        BOOST_CHECK(message.get_data_set() == this->data_set);
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::CGetResponse message(1234, STATUS_Success, this->data_set);
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
    this->check_message_constructor(this->command_set, this->data_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    this->command_set.as_int(dcmtkpp::registry::CommandField) = { dcmtkpp::Message::Command::C_ECHO_RQ };
    this->check_message_constructor_throw(this->command_set, this->data_set);
}
