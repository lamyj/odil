#define BOOST_TEST_MODULE Message
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/message/Message.h"

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    odil::message::Message const message;

    // Command Set might not be empty (Command Group Length, Data Set Type)
    BOOST_CHECK(!message.has_data_set());
}

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::DataSet command_set;
    command_set.add(
        "CommandField", {odil::message::Message::Command::C_ECHO_RQ});

    odil::DataSet data_set;

    odil::message::Message const message(command_set, data_set);

    BOOST_CHECK_EQUAL(
        message.get_command_set().as_int("CommandField", 0),
        odil::message::Message::Command::C_ECHO_RQ);

    BOOST_CHECK(message.has_data_set());
    BOOST_CHECK(message.get_data_set().empty());

    BOOST_CHECK_EQUAL(
        message.get_command_field(),
        odil::message::Message::Command::C_ECHO_RQ);
}

BOOST_AUTO_TEST_CASE(CommandField)
{
    odil::message::Message message;
    message.set_command_field(odil::message::Message::Command::C_FIND_RSP);

    BOOST_CHECK(
        message.get_command_set().as_int("CommandField") ==
            odil::Value::Integers(
                {odil::message::Message::Command::C_FIND_RSP}));
    BOOST_CHECK_EQUAL(
        message.get_command_field(),
        odil::message::Message::Command::C_FIND_RSP);
}

BOOST_AUTO_TEST_CASE(DeleteDataSet)
{
    odil::DataSet command_set;
    odil::DataSet data_set;

    odil::message::Message message(command_set, data_set);

    BOOST_CHECK(message.has_data_set());

    message.delete_data_set();

    BOOST_CHECK(!message.has_data_set());
}
