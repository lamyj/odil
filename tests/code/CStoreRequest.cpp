#define BOOST_TEST_MODULE CStoreRequest
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CStoreRequest.h"
#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Message.h"

#include "../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::CStoreRequest>
{
    DcmDataset command_set;
    DcmDataset data_set;

    Fixture()
    {
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DCM_CommandField, DIMSE_C_STORE_RQ);
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DCM_MessageID, 1234);
        dcmtkpp::ElementAccessor<std::string>::set(
            this->command_set, DCM_AffectedSOPClassUID, UID_MRImageStorage);
        dcmtkpp::ElementAccessor<std::string>::set(
            this->command_set, DCM_AffectedSOPInstanceUID, "1.2.3.4");
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DCM_Priority, DIMSE_PRIORITY_MEDIUM);

        dcmtkpp::ElementAccessor<std::string>::set(
            this->command_set, DCM_MoveOriginatorApplicationEntityTitle,
            "origin");
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DCM_MoveOriginatorMessageID, 5678);

        dcmtkpp::ElementAccessor<std::string>::set(
            this->data_set, DCM_PatientName, "Doe^John");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->data_set, DCM_PatientID, "DJ123");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->data_set, DCM_StudyDescription, "Brain");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->data_set, DCM_StudyInstanceUID, "1.2.3");
    }

    void check(dcmtkpp::CStoreRequest const & message)
    {
        BOOST_CHECK_EQUAL(message.get_command_field(), DIMSE_C_STORE_RQ);
        BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(), UID_MRImageStorage);
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_instance_uid(), "1.2.3.4");

        BOOST_CHECK(message.has_move_originator_ae_title());
        BOOST_CHECK_EQUAL(message.get_move_originator_ae_title(), "origin");

        BOOST_CHECK(message.has_move_originator_message_id());
        BOOST_CHECK_EQUAL(message.get_move_originator_message_id(), 5678);

        BOOST_CHECK_EQUAL(message.get_data_set(), &this->data_set);
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::CStoreRequest message(
        1234, UID_MRImageStorage, "1.2.3.4", DIMSE_PRIORITY_MEDIUM,
        &this->data_set);
    message.set_move_originator_ae_title("origin");
    message.set_move_originator_message_id(5678);

    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(ConstructorWithoutDataset, Fixture)
{
    BOOST_CHECK_THROW(
        dcmtkpp::CStoreRequest const message(
            1234, UID_MRImageStorage, "1.2.3.4", DIMSE_PRIORITY_MEDIUM, NULL),
        dcmtkpp::Exception);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set, &this->data_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    dcmtkpp::ElementAccessor<Uint16>::set(
        this->command_set, DCM_CommandField, DIMSE_C_ECHO_RSP);
    this->check_message_constructor_throw(this->command_set, &this->data_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingAffectSOPClass, Fixture)
{
    this->command_set.findAndDeleteElement(DCM_AffectedSOPClassUID);
    this->check_message_constructor_throw(this->command_set, &this->data_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingAffectSOPInstance, Fixture)
{
    this->command_set.findAndDeleteElement(DCM_AffectedSOPInstanceUID);
    this->check_message_constructor_throw(this->command_set, &this->data_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingDataset, Fixture)
{
    this->check_message_constructor_throw(this->command_set, NULL);
}
