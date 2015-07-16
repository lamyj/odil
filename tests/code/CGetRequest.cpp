#define BOOST_TEST_MODULE CGetRequest
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CGetRequest.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Message.h"
#include "dcmtkpp/registry.h"

#include "../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::CGetRequest>
{
    dcmtkpp::DataSet command_set;
    dcmtkpp::DataSet query;

    Fixture()
    {
        this->command_set.add("CommandField", {dcmtkpp::Message::Command::C_GET_RQ});
        this->command_set.add("MessageID", {1234});
        this->command_set.add("AffectedSOPClassUID",
            {UID_GETPatientRootQueryRetrieveInformationModel});
        this->command_set.add("Priority", {DIMSE_PRIORITY_MEDIUM});

        this->query.add("PatientName", {"Doe^John"});
        this->query.add("StudyDescription", {"Brain"});
        this->query.add("QueryRetrieveLevel", {"STUDY"});
    }

    virtual void check(dcmtkpp::CGetRequest const & message)
    {
        BOOST_CHECK_EQUAL(message.get_command_field(), dcmtkpp::Message::Command::C_GET_RQ);
        BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(),
            UID_GETPatientRootQueryRetrieveInformationModel);
        BOOST_CHECK(message.has_data_set());
        BOOST_CHECK(message.get_data_set() == this->query);
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::CGetRequest const message(
        1234, UID_GETPatientRootQueryRetrieveInformationModel,
        DIMSE_PRIORITY_MEDIUM, this->query);
    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set, this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    this->command_set.as_int("CommandField") = {dcmtkpp::Message::Command::C_ECHO_RQ};
    this->check_message_constructor_throw(this->command_set, this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingAffectSOPClass, Fixture)
{
    this->command_set.remove("AffectedSOPClassUID");
    this->check_message_constructor_throw(this->command_set, this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingPriority, Fixture)
{
    this->command_set.remove("Priority");
    this->check_message_constructor_throw(this->command_set, this->query);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorEmptyQuery, Fixture)
{
    dcmtkpp::DataSet empty;
    this->check_message_constructor_throw(this->command_set, empty);
}
