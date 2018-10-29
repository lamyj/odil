#define BOOST_TEST_MODULE Cancellation
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/message/Cancellation.h"

#include "../../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<odil::message::Cancellation>
{
    std::shared_ptr<odil::DataSet> command_set;

    Fixture()
    : command_set(std::make_shared<odil::DataSet>())
    {
        this->command_set->add(
            "CommandField", {odil::message::Message::Command::C_CANCEL_RQ});
        this->command_set->add("MessageIDBeingRespondedTo", {1234});
    }

    void check(odil::message::Cancellation const & message)
    {
        BOOST_CHECK_EQUAL(
            message.get_command_field(),
            odil::message::Message::Command::C_CANCEL_RQ);
        BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    odil::message::Cancellation const message(1234);
    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    this->command_set->as_int("CommandField") = {
        odil::message::Message::Command::C_ECHO_RQ};
    this->check_message_constructor_throw(this->command_set);
}
