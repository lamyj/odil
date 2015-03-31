#define BOOST_TEST_MODULE Request
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>

#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Message.h"
#include "dcmtkpp/Request.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::Request const message(1234);

    BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
}

BOOST_AUTO_TEST_CASE(MessageConstructor)
{
    DcmDataset command_set;
    dcmtkpp::ElementAccessor<EVR_US>::set(command_set, DCM_MessageID, 1234);
    dcmtkpp::Message const generic_message(command_set, NULL);

    dcmtkpp::Request const message(generic_message);

    BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
    BOOST_CHECK_EQUAL(message.get_data_set(), static_cast<DcmDataset *>(NULL));
}
