#define BOOST_TEST_MODULE Response
#include <boost/test/unit_test.hpp>

#include <vector>

#include "odil/DataSet.h"
#include "odil/message/Message.h"
#include "odil/message/Response.h"
#include "odil/Value.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::message::Response const message(
        1234, odil::message::Response::Pending);

    BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
    BOOST_CHECK_EQUAL(message.get_status(),
        odil::message::Response::Pending);
}

BOOST_AUTO_TEST_CASE(MessageConstructor)
{
    odil::DataSet command_set;
    command_set.add("MessageIDBeingRespondedTo", {1234});
    command_set.add("Status", {odil::message::Response::Pending});
    odil::message::Message const generic_message(command_set);

    odil::message::Response const message(generic_message);

    BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
    BOOST_CHECK_EQUAL(
        message.get_status(), odil::message::Response::Pending);
    BOOST_CHECK(!message.has_data_set());
}

BOOST_AUTO_TEST_CASE(StatusPending)
{
    std::vector<odil::Value::Integer> const statuses = {
        odil::message::Response::Pending,
    };

    for(auto const status:statuses)
    {
        BOOST_REQUIRE(odil::message::Response::is_pending(status));
        BOOST_REQUIRE(!odil::message::Response::is_warning(status));
        BOOST_REQUIRE(!odil::message::Response::is_failure(status));

        odil::message::Response response(1234, status);
        BOOST_REQUIRE(response.is_pending());
        BOOST_REQUIRE(!response.is_warning());
        BOOST_REQUIRE(!response.is_failure());
    }
}


BOOST_AUTO_TEST_CASE(StatusWarning)
{
    std::vector<odil::Value::Integer> const statuses = {
        odil::message::Response::AttributeListError,
        odil::message::Response::AttributeValueOutOfRange
    };

    for(auto const status:statuses)
    {
        BOOST_REQUIRE(!odil::message::Response::is_pending(status));
        BOOST_REQUIRE(odil::message::Response::is_warning(status));
        BOOST_REQUIRE(!odil::message::Response::is_failure(status));

        odil::message::Response response(1234, status);
        BOOST_REQUIRE(!response.is_pending());
        BOOST_REQUIRE(response.is_warning());
        BOOST_REQUIRE(!response.is_failure());
    }
}

BOOST_AUTO_TEST_CASE(StatusFailure)
{
    std::vector<odil::Value::Integer> const statuses = {
        odil::message::Response::SOPClassNotSupported,
        odil::message::Response::ClassInstanceConflict,
        odil::message::Response::DuplicateSOPInstance,
        odil::message::Response::DuplicateInvocation,
        odil::message::Response::InvalidArgumentValue,
        odil::message::Response::InvalidAttributeValue,
        odil::message::Response::InvalidObjectInstance,
        odil::message::Response::MissingAttribute,
        odil::message::Response::MissingAttributeValue,
        odil::message::Response::MistypedArgument,
        odil::message::Response::NoSuchArgument,
        odil::message::Response::NoSuchAttribute,
        odil::message::Response::NoSuchEventType,
        odil::message::Response::NoSuchSOPInstance,
        odil::message::Response::NoSuchSOPClass,
        odil::message::Response::ProcessingFailure,
        odil::message::Response::ResourceLimitation,
        odil::message::Response::UnrecognizedOperation,
        odil::message::Response::NoSuchActionType,
        odil::message::Response::RefusedNotAuthorized
    };

    for(auto const status:statuses)
    {
        BOOST_REQUIRE(!odil::message::Response::is_pending(status));
        BOOST_REQUIRE(!odil::message::Response::is_warning(status));
        BOOST_REQUIRE(odil::message::Response::is_failure(status));

        odil::message::Response response(1234, status);
        BOOST_REQUIRE(!response.is_pending());
        BOOST_REQUIRE(!response.is_warning());
        BOOST_REQUIRE(response.is_failure());
    }
}

BOOST_AUTO_TEST_CASE(StatusDetails)
{
    odil::message::Response response(
        1234, odil::message::Response::SOPClassNotSupported);
    odil::DataSet status_details;
    status_details.add(
        odil::registry::ErrorComment, {"This is the error comment"});
    response.set_status_fields(status_details);

    BOOST_REQUIRE(response.has_error_comment());
    BOOST_REQUIRE_EQUAL(
        response.get_error_comment(), "This is the error comment");
}
