#define BOOST_TEST_MODULE CStoreResponse
#include <boost/test/unit_test.hpp>

#include "odil/message/CStoreResponse.h"
#include "odil/DataSet.h"
#include "odil/message/Message.h"
#include "odil/registry.h"

#include "../../MessageFixtureBase.h"

struct Fixture: public MessageFixtureBase<odil::message::CStoreResponse>
{
    std::shared_ptr<odil::DataSet> command_set;

    Fixture()
    : command_set(std::make_shared<odil::DataSet>())
    {
        this->command_set->add(
            "CommandField", {odil::message::Message::Command::C_STORE_RSP});
        this->command_set->add("MessageIDBeingRespondedTo", {1234});
        this->command_set->add("Status", {odil::message::Response::Success});

        this->command_set->add("MessageID", {5678});
        this->command_set->add(
            "AffectedSOPClassUID", {odil::registry::MRImageStorage});
        this->command_set->add("AffectedSOPInstanceUID", {"1.2.3.4"});
    }

    void check(odil::message::CStoreResponse const & message)
    {
        BOOST_CHECK_EQUAL(
            message.get_command_field(),
            odil::message::Message::Command::C_STORE_RSP);
        BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
        BOOST_CHECK_EQUAL(
            message.get_status(), odil::message::Response::Success);
        BOOST_CHECK(!message.has_data_set());

        BOOST_CHECK(message.has_message_id());
        BOOST_CHECK_EQUAL(message.get_message_id(), 5678);

        BOOST_CHECK(message.has_affected_sop_class_uid());
        BOOST_CHECK_EQUAL(
            message.get_affected_sop_class_uid(), odil::registry::MRImageStorage);

        BOOST_CHECK(message.has_affected_sop_instance_uid());
        BOOST_CHECK_EQUAL(message.get_affected_sop_instance_uid(), "1.2.3.4");
    }
};

BOOST_FIXTURE_TEST_CASE(Constructor, Fixture)
{
    odil::message::CStoreResponse message(
        1234, odil::message::Response::Success);
    message.set_message_id(5678);
    message.set_affected_sop_class_uid(odil::registry::MRImageStorage);
    message.set_affected_sop_instance_uid("1.2.3.4");

    this->check(message);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructor, Fixture)
{
    this->check_message_constructor(this->command_set);
}

BOOST_FIXTURE_TEST_CASE(MessageConstructorWrongCommandField, Fixture)
{
    this->command_set->add(
        "CommandField", {odil::message::Message::Command::C_ECHO_RQ});
    this->check_message_constructor_throw(this->command_set);
}

BOOST_AUTO_TEST_CASE(StatusWarning)
{
    std::vector<odil::Value::Integer> const statuses = {
        odil::message::CStoreResponse::CoercionOfDataElements,
        odil::message::CStoreResponse::DataSetDoesNotMatchSOPClass,
        odil::message::CStoreResponse::ElementsDiscarded
    };

    for(auto const status:statuses)
    {
        odil::message::CStoreResponse response(1234, status);
        BOOST_REQUIRE(!response.is_pending());
        BOOST_REQUIRE(response.is_warning());
        BOOST_REQUIRE(!response.is_failure());
    }
}


BOOST_AUTO_TEST_CASE(StatusFailure)
{
    std::vector<odil::Value::Integer> const statuses = {
        odil::message::CStoreResponse::RefusedOutOfResources,
        odil::message::CStoreResponse::ErrorDataSetDoesNotMatchSOPClass,
        odil::message::CStoreResponse::ErrorCannotUnderstand
    };

    for(auto const status:statuses)
    {
        odil::message::CStoreResponse response(1234, status);
        BOOST_REQUIRE(!response.is_pending());
        BOOST_REQUIRE(!response.is_warning());
        BOOST_REQUIRE(response.is_failure());
    }
}
