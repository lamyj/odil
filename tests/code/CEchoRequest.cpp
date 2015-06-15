#define BOOST_TEST_MODULE CEchoRequest
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/CEchoRequest.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Message.h"

#include "../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::CEchoRequest>
{
    dcmtkpp::DataSet command_set;

    Fixture()
    {
        this->command_set.add("CommandField", {dcmtkpp::Message::Command::C_ECHO_RQ});
        this->command_set.add("MessageID", {1234});
        this->command_set.add("AffectedSOPClassUID", {UID_VerificationSOPClass});
    }

    void check(dcmtkpp::CEchoRequest const & message)
    {
        BOOST_CHECK_EQUAL(message.get_command_field(), dcmtkpp::Message::Command::C_ECHO_RQ);
        BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(), UID_VerificationSOPClass);
        BOOST_CHECK(!message.has_data_set());
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::CEchoRequest const message(1234, UID_VerificationSOPClass);
    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    this->command_set.as_int("CommandField") = {dcmtkpp::Message::Command::C_ECHO_RSP};
    this->check_message_constructor_throw(this->command_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingAffectSOPClass, Fixture)
{
    this->command_set.remove("AffectedSOPClassUID");
    this->check_message_constructor_throw(this->command_set);
}
