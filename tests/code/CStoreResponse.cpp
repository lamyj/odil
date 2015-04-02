#define BOOST_TEST_MODULE CStoreResponse
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CStoreResponse.h"
#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Message.h"

#include "../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::CStoreResponse>
{
    DcmDataset command_set;

    Fixture()
    {
        dcmtkpp::ElementAccessor<EVR_US>::set(
            this->command_set, DCM_CommandField, DIMSE_C_STORE_RSP);
        dcmtkpp::ElementAccessor<EVR_US>::set(
            this->command_set, DCM_MessageIDBeingRespondedTo, 1234);
        dcmtkpp::ElementAccessor<EVR_US>::set(
            this->command_set, DCM_Status, STATUS_Success);

        dcmtkpp::ElementAccessor<EVR_US>::set(
            this->command_set, DCM_MessageID, 5678);
        dcmtkpp::ElementAccessor<EVR_UI>::set(
            this->command_set, DCM_AffectedSOPClassUID, UID_MRImageStorage);
        dcmtkpp::ElementAccessor<EVR_UI>::set(
            this->command_set, DCM_AffectedSOPInstanceUID, "1.2.3.4");
    }

    void check(dcmtkpp::CStoreResponse const & message)
    {
        BOOST_CHECK_EQUAL(message.get_command_field(), DIMSE_C_STORE_RSP);
        BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
        BOOST_CHECK_EQUAL(message.get_status(), STATUS_Success);
        BOOST_CHECK_EQUAL(message.get_data_set(), static_cast<DcmDataset const *>(NULL));

        BOOST_CHECK(message.has_message_id());
        BOOST_CHECK_EQUAL(message.get_message_id(), 5678);

        BOOST_CHECK(message.has_affected_sop_class_uid());
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(), UID_MRImageStorage);

        BOOST_CHECK(message.has_affected_sop_instance_uid());
        BOOST_CHECK_EQUAL(message.get_affected_sop_instance_uid(), "1.2.3.4");
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::CStoreResponse message(1234, STATUS_Success);
    message.set_message_id(5678);
    message.set_affected_sop_class_uid(UID_MRImageStorage);
    message.set_affected_sop_instance_uid("1.2.3.4");

    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set, NULL);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    dcmtkpp::ElementAccessor<EVR_US>::set(
        this->command_set, DCM_CommandField, DIMSE_C_ECHO_RQ);
    this->check_message_constructor_throw(this->command_set, NULL);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWithDataSet, Fixture)
{
    DcmDataset dataset;
    dcmtkpp::ElementAccessor<EVR_PN>::set(dataset, DCM_PatientName, "Foo");
    this->check_message_constructor_throw(this->command_set, &dataset);
}
