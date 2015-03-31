#define BOOST_TEST_MODULE Response
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/ElementAccessor.h"
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
    DcmDataset command_set;
    dcmtkpp::ElementAccessor<EVR_US>::set(
        command_set, DCM_MessageIDBeingRespondedTo, 1234);
    dcmtkpp::ElementAccessor<EVR_US>::set(
        command_set, DCM_Status, STATUS_Pending);
    dcmtkpp::Message const generic_message(command_set, NULL);

    dcmtkpp::Response const message(generic_message);

    BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
    BOOST_CHECK_EQUAL(message.get_status(), STATUS_Pending);
    BOOST_CHECK_EQUAL(message.get_data_set(), static_cast<DcmDataset *>(NULL));
}
