#define BOOST_TEST_MODULE CStoreRequest
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/message/CStoreRequest.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/message/Message.h"
#include "dcmtkpp/registry.h"

#include "../../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::message::CStoreRequest>
{
    dcmtkpp::DataSet command_set;
    dcmtkpp::DataSet data_set;

    Fixture()
    {
        this->command_set.add(
            "CommandField", {dcmtkpp::message::Message::Command::C_STORE_RQ});
        this->command_set.add("MessageID", {1234});
        this->command_set.add(
            "AffectedSOPClassUID", {dcmtkpp::registry::MRImageStorage});
        this->command_set.add("AffectedSOPInstanceUID", {"1.2.3.4"});
        this->command_set.add(
            "Priority", {dcmtkpp::message::Message::Priority::MEDIUM});

        this->command_set.add("MoveOriginatorApplicationEntityTitle", {"origin"});
        this->command_set.add("MoveOriginatorMessageID", {5678});

        this->data_set.add("PatientName", {"Doe^John"});
        this->data_set.add("PatientID", {"DJ123"});
        this->data_set.add("StudyDescription", {"Brain"});
        this->data_set.add("StudyInstanceUID", {"1.2.3"});
    }

    void check(dcmtkpp::message::CStoreRequest const & message)
    {
        BOOST_CHECK_EQUAL(
            message.get_command_field(),
            dcmtkpp::message::Message::Command::C_STORE_RQ);
        BOOST_CHECK_EQUAL(message.get_message_id(), 1234);
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(), dcmtkpp::registry::MRImageStorage);
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_instance_uid(), "1.2.3.4");

        BOOST_CHECK(message.has_move_originator_ae_title());
        BOOST_CHECK_EQUAL(message.get_move_originator_ae_title(), "origin");

        BOOST_CHECK(message.has_move_originator_message_id());
        BOOST_CHECK_EQUAL(message.get_move_originator_message_id(), 5678);

        BOOST_CHECK(message.has_data_set());
        BOOST_CHECK(message.get_data_set() == this->data_set);
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::message::CStoreRequest message(
        1234, dcmtkpp::registry::MRImageStorage, "1.2.3.4",
        dcmtkpp::message::Message::Priority::MEDIUM,
        this->data_set);
    message.set_move_originator_ae_title("origin");
    message.set_move_originator_message_id(5678);

    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set, this->data_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    this->command_set.as_int("CommandField") = {
        dcmtkpp::message::Message::Command::C_ECHO_RSP};
    this->check_message_constructor_throw(this->command_set, this->data_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingAffectSOPClass, Fixture)
{
    this->command_set.remove("AffectedSOPClassUID");
    this->check_message_constructor_throw(this->command_set, this->data_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorMissingAffectSOPInstance, Fixture)
{
    this->command_set.remove("AffectedSOPInstanceUID");
    this->check_message_constructor_throw(this->command_set, this->data_set);
}
