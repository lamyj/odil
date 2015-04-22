#define BOOST_TEST_MODULE CMoveRequest
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CMoveRequest.h"
#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Message.h"

#include "../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::CMoveRequest>
{
    DcmDataset command_set;
    DcmDataset query;

    Fixture()
    {
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DCM_CommandField, DIMSE_C_MOVE_RQ);
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DCM_MessageID, 1234);
        dcmtkpp::ElementAccessor<std::string>::set(
            this->command_set, DCM_AffectedSOPClassUID,
            UID_MOVEPatientRootQueryRetrieveInformationModel);
        dcmtkpp::ElementAccessor<Uint16>::set(
            this->command_set, DCM_Priority, DIMSE_PRIORITY_MEDIUM);
        dcmtkpp::ElementAccessor<std::string>::set(
            this->command_set, DCM_MoveDestination, "destination");

        dcmtkpp::ElementAccessor<std::string>::set(
            this->query, DCM_PatientName, "Doe^John");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->query, DCM_StudyDescription, "Brain");
        dcmtkpp::ElementAccessor<std::string>::set(
            this->query, DCM_QueryRetrieveLevel, "STUDY");
    }

    virtual void check(dcmtkpp::CMoveRequest const & message)
    {
        BOOST_CHECK_EQUAL(message.get_command_field(), DIMSE_C_MOVE_RQ);
        BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(),
            UID_MOVEPatientRootQueryRetrieveInformationModel);
        BOOST_CHECK_EQUAL(message.get_move_destination(), "destination");
        BOOST_CHECK_EQUAL(message.get_data_set(), &this->query);
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::CMoveRequest const message(
        1234, UID_MOVEPatientRootQueryRetrieveInformationModel,
        DIMSE_PRIORITY_MEDIUM, "destination", &this->query);
    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(ConstructorWithoutDataset, Fixture)
{
    BOOST_CHECK_THROW(
        dcmtkpp::CMoveRequest const message(
            1234, UID_MOVEPatientRootQueryRetrieveInformationModel,
            DIMSE_PRIORITY_MEDIUM, "destination", NULL),
        dcmtkpp::Exception);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set, &this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    dcmtkpp::ElementAccessor<Uint16>::set(
        this->command_set, DCM_CommandField, DIMSE_C_ECHO_RQ);
    this->check_message_constructor_throw(this->command_set, &this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingAffectSOPClass, Fixture)
{
    this->command_set.findAndDeleteElement(DCM_AffectedSOPClassUID);
    this->check_message_constructor_throw(this->command_set, &this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingPriority, Fixture)
{
    this->command_set.findAndDeleteElement(DCM_Priority);
    this->check_message_constructor_throw(this->command_set, &this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingQuery, Fixture)
{
    this->check_message_constructor_throw(this->command_set, NULL);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorEmptyQuery, Fixture)
{
    DcmDataset empty;
    this->check_message_constructor_throw(this->command_set, &empty);
}
