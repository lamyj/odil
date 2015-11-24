#define BOOST_TEST_MODULE CEchoResponse
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/message/CEchoResponse.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/message/Message.h"
#include "dcmtkpp/registry.h"

#include "../../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::message::CEchoResponse>
{
    dcmtkpp::DataSet command_set;

    Fixture()
    {
        this->command_set.add(
            "CommandField", {dcmtkpp::message::Message::Command::C_ECHO_RSP});
        this->command_set.add("MessageIDBeingRespondedTo", {1234});
        this->command_set.add("Status", {dcmtkpp::message::Response::Success});
        this->command_set.add(
            "AffectedSOPClassUID", {dcmtkpp::registry::VerificationSOPClass});
    }

    void check(dcmtkpp::message::CEchoResponse const & message)
    {
        BOOST_CHECK_EQUAL(
            message.get_command_field(),
            dcmtkpp::message::Message::Command::C_ECHO_RSP);
        BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
        BOOST_CHECK_EQUAL(
            message.get_status(), dcmtkpp::message::Response::Success);
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(),
            dcmtkpp::registry::VerificationSOPClass);
        BOOST_CHECK(!message.has_data_set());
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::message::CEchoResponse const message(
        1234, dcmtkpp::message::Response::Success,
        dcmtkpp::registry::VerificationSOPClass);
    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    this->command_set.as_int("CommandField") = {
        dcmtkpp::message::Message::Command::C_ECHO_RQ};
    this->check_message_constructor_throw(this->command_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingAffectSOPClass, Fixture)
{
    this->command_set.remove("AffectedSOPClassUID");
    this->check_message_constructor_throw(this->command_set);
}
