#define BOOST_TEST_MODULE Response
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Message.h"
#include "dcmtkpp/Response.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::Response const message(1234, STATUS_Pending);

    BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
    BOOST_CHECK_EQUAL(message.get_status(), STATUS_Pending);
}

BOOST_AUTO_TEST_CASE(MessageConstructor)
{
    dcmtkpp::DataSet command_set;
    command_set.add("MessageIDBeingRespondedTo", {1234});
    command_set.add("Status", {STATUS_Pending});
    dcmtkpp::Message const generic_message(command_set);

    dcmtkpp::Response const message(generic_message);

    BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
    BOOST_CHECK_EQUAL(message.get_status(), STATUS_Pending);
    BOOST_CHECK(!message.has_data_set());
}
