#define BOOST_TEST_MODULE Message
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/message/Message.h"

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::message::Message const message;

    // Command Set might not be empty (Command Group Length, Data Set Type)
    BOOST_CHECK(!message.has_data_set());
}

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::DataSet command_set;
    command_set.add(
        "CommandField", {dcmtkpp::message::Message::Command::C_ECHO_RQ});

    dcmtkpp::DataSet data_set;

    dcmtkpp::message::Message const message(command_set, data_set);

    BOOST_CHECK_EQUAL(
        message.get_command_set().as_int("CommandField", 0),
        dcmtkpp::message::Message::Command::C_ECHO_RQ);

    BOOST_CHECK(message.has_data_set());
    BOOST_CHECK(message.get_data_set().empty());

    BOOST_CHECK_EQUAL(
        message.get_command_field(),
        dcmtkpp::message::Message::Command::C_ECHO_RQ);
}

BOOST_AUTO_TEST_CASE(CommandField)
{
    dcmtkpp::message::Message message;
    message.set_command_field(dcmtkpp::message::Message::Command::C_FIND_RSP);

    BOOST_CHECK(
        message.get_command_set().as_int("CommandField") ==
            dcmtkpp::Value::Integers(
                {dcmtkpp::message::Message::Command::C_FIND_RSP}));
    BOOST_CHECK_EQUAL(
        message.get_command_field(),
        dcmtkpp::message::Message::Command::C_FIND_RSP);
}

BOOST_AUTO_TEST_CASE(DeleteDataSet)
{
    dcmtkpp::DataSet command_set;
    dcmtkpp::DataSet data_set;

    dcmtkpp::message::Message message(command_set, data_set);

    BOOST_CHECK(message.has_data_set());

    message.delete_data_set();

    BOOST_CHECK(!message.has_data_set());
}
