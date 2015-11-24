#define BOOST_TEST_MODULE Request
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/message/Message.h"
#include "dcmtkpp/message/Request.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::message::Request const message(1234);

    BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
}

BOOST_AUTO_TEST_CASE(MessageConstructor)
{
    dcmtkpp::DataSet command_set;
    command_set.add("MessageID", {1234});
    dcmtkpp::message::Message const generic_message(command_set);

    dcmtkpp::message::Request const message(generic_message);

    BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
    BOOST_CHECK(!message.has_data_set());
}
