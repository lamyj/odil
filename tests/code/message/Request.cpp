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
    auto const command_set = std::make_shared<odil::DataSet>();
    command_set->add("MessageID", {1234});
    auto generic_message = std::make_shared<odil::message::Message const>(
        command_set);

    odil::message::Request const message(generic_message);

    BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
    BOOST_CHECK(!message.has_data_set());
}
