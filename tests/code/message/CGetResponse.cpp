#define BOOST_TEST_MODULE CGetResponse
#include <boost/test/unit_test.hpp>

#include "odil/message/CGetResponse.h"
#include "odil/DataSet.h"
#include "odil/message/Message.h"
#include "odil/registry.h"

#include "../../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<odil::message::CGetResponse>
{
    std::shared_ptr<odil::DataSet> command_set;
    std::shared_ptr<odil::DataSet> data_set;

    Fixture()
    : command_set(std::make_shared<odil::DataSet>()),
      data_set(std::make_shared<odil::DataSet>())
    {
        this->command_set->add(
            "CommandField", {odil::message::Message::Command::C_GET_RSP});
        this->command_set->add("MessageIDBeingRespondedTo", {1234});
        this->command_set->add("Status", {odil::message::Response::Success});

        this->command_set->add("MessageID", {5678});
        this->command_set->add("AffectedSOPClassUID",
            {odil::registry::StudyRootQueryRetrieveInformationModelGet});
        this->command_set->add(odil::registry::NumberOfRemainingSuboperations, {1});
        this->command_set->add(odil::registry::NumberOfCompletedSuboperations, {2});
        this->command_set->add(odil::registry::NumberOfFailedSuboperations, {3});
        this->command_set->add(odil::registry::NumberOfWarningSuboperations, {4});

        this->data_set->add("PatientName", {"Doe^John"});
        this->data_set->add("PatientID", {"DJ123"});
        this->data_set->add("StudyDescription", {"Brain"});
        this->data_set->add("StudyInstanceUID", {"1.2.3"});
    }

    virtual void check(odil::message::CGetResponse const & message)
    {
        BOOST_CHECK_EQUAL(
            message.get_command_field(),
            odil::message::Message::Command::C_GET_RSP);
        BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
        BOOST_CHECK_EQUAL(
            message.get_status(), odil::message::Response::Success);

        BOOST_CHECK(message.has_message_id());
        BOOST_CHECK_EQUAL(message.get_message_id(), 5678);

        BOOST_CHECK(message.has_affected_sop_class_uid());
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(),
            odil::registry::StudyRootQueryRetrieveInformationModelGet);

        BOOST_CHECK(message.has_number_of_remaining_sub_operations());
        BOOST_CHECK_EQUAL(message.get_number_of_remaining_sub_operations(), 1);

        BOOST_CHECK(message.has_number_of_completed_sub_operations());
        BOOST_CHECK_EQUAL(message.get_number_of_completed_sub_operations(), 2);

        BOOST_CHECK(message.has_number_of_failed_sub_operations());
        BOOST_CHECK_EQUAL(message.get_number_of_failed_sub_operations(), 3);

        BOOST_CHECK(message.has_number_of_warning_sub_operations());
        BOOST_CHECK_EQUAL(message.get_number_of_warning_sub_operations(), 4);

        BOOST_CHECK(message.has_data_set());
        BOOST_CHECK(*message.get_data_set() == *this->data_set);
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    odil::message::CGetResponse message(
        1234, odil::message::Response::Success, this->data_set);
    message.set_message_id(5678);
    message.set_affected_sop_class_uid(
        odil::registry::StudyRootQueryRetrieveInformationModelGet);
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
    this->command_set->as_int(odil::registry::CommandField) = {
        odil::message::Message::Command::C_ECHO_RQ };
    this->check_message_constructor_throw(this->command_set, this->data_set);
}

BOOST_AUTO_TEST_CASE(StatusWarning)
{
    std::vector<odil::Value::Integer> const statuses = {
        odil::message::CGetResponse::SubOperationsCompleteOneOrMoreFailuresOrWarnings
    };

    for(auto const status:statuses)
    {
        odil::message::CGetResponse response(1234, status);
        BOOST_REQUIRE(!response.is_pending());
        BOOST_REQUIRE(response.is_warning());
        BOOST_REQUIRE(!response.is_failure());
    }
}

BOOST_AUTO_TEST_CASE(StatusFailure)
{
    std::vector<odil::Value::Integer> const statuses = {
        odil::message::CGetResponse::RefusedOutOfResourcesUnableToCalculateNumberOfMatches,
        odil::message::CGetResponse::RefusedOutOfResourcesUnableToPerformSubOperations,
        odil::message::CGetResponse::IdentifierDoesNotMatchSOPClass,
        odil::message::CGetResponse::UnableToProcess
    };

    for(auto const status:statuses)
    {
        odil::message::CGetResponse response(1234, status);
        BOOST_REQUIRE(!response.is_pending());
        BOOST_REQUIRE(!response.is_warning());
        BOOST_REQUIRE(response.is_failure());
    }
}
