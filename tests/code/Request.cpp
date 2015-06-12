#define BOOST_TEST_MODULE Request
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Message.h"
#include "dcmtkpp/Request.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::Request const message(1234);

    BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
}

BOOST_AUTO_TEST_CASE(MessageConstructor)
{
    dcmtkpp::DataSet command_set;
    command_set.add("MessageID", {1234});
    dcmtkpp::Message const generic_message(command_set);

    dcmtkpp::Request const message(generic_message);

    BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
    BOOST_CHECK(!message.has_data_set());
}
