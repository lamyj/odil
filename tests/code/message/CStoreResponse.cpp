#define BOOST_TEST_MODULE CStoreResponse
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/message/CStoreResponse.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/message/Message.h"
#include "dcmtkpp/registry.h"

#include "../../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<dcmtkpp::message::CStoreResponse>
{
    dcmtkpp::DataSet command_set;

    Fixture()
    {
        this->command_set.add(
            "CommandField", {dcmtkpp::message::Message::Command::C_STORE_RSP});
        this->command_set.add("MessageIDBeingRespondedTo", {1234});
        this->command_set.add("Status", {dcmtkpp::message::Response::Success});

        this->command_set.add("MessageID", {5678});
        this->command_set.add(
            "AffectedSOPClassUID", {dcmtkpp::registry::MRImageStorage});
        this->command_set.add("AffectedSOPInstanceUID", {"1.2.3.4"});
    }

    void check(dcmtkpp::message::CStoreResponse const & message)
    {
        BOOST_CHECK_EQUAL(
            message.get_command_field(),
            dcmtkpp::message::Message::Command::C_STORE_RSP);
        BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
        BOOST_CHECK_EQUAL(
            message.get_status(), dcmtkpp::message::Response::Success);
        BOOST_CHECK(!message.has_data_set());

        BOOST_CHECK(message.has_message_id());
        BOOST_CHECK_EQUAL(message.get_message_id(), 5678);

        BOOST_CHECK(message.has_affected_sop_class_uid());
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(), dcmtkpp::registry::MRImageStorage);

        BOOST_CHECK(message.has_affected_sop_instance_uid());
        BOOST_CHECK_EQUAL(message.get_affected_sop_instance_uid(), "1.2.3.4");
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    dcmtkpp::message::CStoreResponse message(
        1234, dcmtkpp::message::Response::Success);
    message.set_message_id(5678);
    message.set_affected_sop_class_uid(dcmtkpp::registry::MRImageStorage);
    message.set_affected_sop_instance_uid("1.2.3.4");

    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    this->command_set.add(
        "CommandField", {dcmtkpp::message::Message::Command::C_ECHO_RQ});
    this->check_message_constructor_throw(this->command_set);
}

BOOST_AUTO_TEST_CASE(StatusWarning)
{
    std::vector<dcmtkpp::Value::Integer> const statuses = {
        dcmtkpp::message::CStoreResponse::CoercionOfDataElements,
        dcmtkpp::message::CStoreResponse::DataSetDoesNotMatchSOPClass,
        dcmtkpp::message::CStoreResponse::ElementsDiscarded
    };

    for(auto const status:statuses)
    {
        dcmtkpp::message::CStoreResponse response(1234, status);
        BOOST_REQUIRE(!response.is_pending());
        BOOST_REQUIRE(response.is_warning());
        BOOST_REQUIRE(!response.is_failure());
    }
}


BOOST_AUTO_TEST_CASE(StatusFailure)
{
    std::vector<dcmtkpp::Value::Integer> const statuses = {
        dcmtkpp::message::CStoreResponse::RefusedOutOfResources,
        dcmtkpp::message::CStoreResponse::ErrorDataSetDoesNotMatchSOPClass,
        dcmtkpp::message::CStoreResponse::ErrorCannotUnderstand
    };

    for(auto const status:statuses)
    {
        dcmtkpp::message::CStoreResponse response(1234, status);
        BOOST_REQUIRE(!response.is_pending());
        BOOST_REQUIRE(!response.is_warning());
        BOOST_REQUIRE(response.is_failure());
    }
}
