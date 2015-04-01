#define BOOST_TEST_MODULE CEchoResponse
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CEchoResponse.h"
#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Message.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::CEchoResponse const message(
        1234, STATUS_Success, UID_VerificationSOPClass);

    BOOST_CHECK_EQUAL(message.get_command_field(), DIMSE_C_ECHO_RSP);

    BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);

    BOOST_CHECK_EQUAL(message.get_status(), STATUS_Success);

    BOOST_CHECK_EQUAL(
        message.get_affected_sop_class_uid(), UID_VerificationSOPClass);

    BOOST_CHECK_EQUAL(
        message.get_data_set(), static_cast<DcmDataset const *>(NULL));
}

BOOST_AUTO_TEST_CASE(MessageConstructor)
{
    DcmDataset command_set;
    dcmtkpp::ElementAccessor<EVR_US>::set(
        command_set, DCM_CommandField, DIMSE_C_ECHO_RSP);
    dcmtkpp::ElementAccessor<EVR_US>::set(
        command_set, DCM_MessageIDBeingRespondedTo, 1234);
    dcmtkpp::ElementAccessor<EVR_US>::set(
        command_set, DCM_Status, STATUS_Success);
    dcmtkpp::ElementAccessor<EVR_UI>::set(
        command_set, DCM_AffectedSOPClassUID, UID_VerificationSOPClass);

    dcmtkpp::Message const generic_message(command_set, NULL);

    dcmtkpp::CEchoResponse const message(generic_message);

    BOOST_CHECK_EQUAL(message.get_command_field(), DIMSE_C_ECHO_RSP);

    BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);

    BOOST_CHECK_EQUAL(message.get_status(), STATUS_Success);

    BOOST_CHECK_EQUAL(
        message.get_affected_sop_class_uid(), UID_VerificationSOPClass);

    BOOST_CHECK_EQUAL(
        message.get_data_set(), static_cast<DcmDataset const *>(NULL));
}
