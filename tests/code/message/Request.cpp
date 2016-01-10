#define BOOST_TEST_MODULE Request
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/message/Message.h"
#include "odil/message/Request.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::message::Request const message(1234);

    BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
}

BOOST_AUTO_TEST_CASE(MessageConstructor)
{
    odil::DataSet command_set;
    command_set.add("MessageID", {1234});
    odil::message::Message const generic_message(command_set);

    odil::message::Request const message(generic_message);

    BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
    BOOST_CHECK(!message.has_data_set());
}
