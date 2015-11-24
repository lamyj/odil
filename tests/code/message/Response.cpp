#define BOOST_TEST_MODULE Response
#include <boost/test/unit_test.hpp>

#include <vector>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/message/Message.h"
#include "dcmtkpp/message/Response.h"
#include "dcmtkpp/Value.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::message::Response const message(
        1234, dcmtkpp::message::Response::Pending);

    BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
    BOOST_CHECK_EQUAL(message.get_status(),
        dcmtkpp::message::Response::Pending);
}

BOOST_AUTO_TEST_CASE(MessageConstructor)
{
    dcmtkpp::DataSet command_set;
    command_set.add("MessageIDBeingRespondedTo", {1234});
    command_set.add("Status", {dcmtkpp::message::Response::Pending});
    dcmtkpp::message::Message const generic_message(command_set);

    dcmtkpp::message::Response const message(generic_message);

    BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
    BOOST_CHECK_EQUAL(
        message.get_status(), dcmtkpp::message::Response::Pending);
    BOOST_CHECK(!message.has_data_set());
}

BOOST_AUTO_TEST_CASE(StatusPending)
{
    std::vector<dcmtkpp::Value::Integer> const statuses = {
        dcmtkpp::message::Response::Pending,
    };

    for(auto const status:statuses)
    {
        BOOST_REQUIRE(dcmtkpp::message::Response::is_pending(status));
        BOOST_REQUIRE(!dcmtkpp::message::Response::is_warning(status));
        BOOST_REQUIRE(!dcmtkpp::message::Response::is_failure(status));

        dcmtkpp::message::Response response(1234, status);
        BOOST_REQUIRE(response.is_pending());
        BOOST_REQUIRE(!response.is_warning());
        BOOST_REQUIRE(!response.is_failure());
    }
}


BOOST_AUTO_TEST_CASE(StatusWarning)
{
    std::vector<dcmtkpp::Value::Integer> const statuses = {
        dcmtkpp::message::Response::AttributeListError,
        dcmtkpp::message::Response::AttributeValueOutOfRange
    };

    for(auto const status:statuses)
    {
        BOOST_REQUIRE(!dcmtkpp::message::Response::is_pending(status));
        BOOST_REQUIRE(dcmtkpp::message::Response::is_warning(status));
        BOOST_REQUIRE(!dcmtkpp::message::Response::is_failure(status));

        dcmtkpp::message::Response response(1234, status);
        BOOST_REQUIRE(!response.is_pending());
        BOOST_REQUIRE(response.is_warning());
        BOOST_REQUIRE(!response.is_failure());
    }
}

BOOST_AUTO_TEST_CASE(StatusFailure)
{
    std::vector<dcmtkpp::Value::Integer> const statuses = {
        dcmtkpp::message::Response::SOPClassNotSupported,
        dcmtkpp::message::Response::ClassInstanceConflict,
        dcmtkpp::message::Response::DuplicateSOPInstance,
        dcmtkpp::message::Response::DuplicateInvocation,
        dcmtkpp::message::Response::InvalidArgumentValue,
        dcmtkpp::message::Response::InvalidAttributeValue,
        dcmtkpp::message::Response::InvalidObjectInstance,
        dcmtkpp::message::Response::MissingAttribute,
        dcmtkpp::message::Response::MissingAttributeValue,
        dcmtkpp::message::Response::MistypedArgument,
        dcmtkpp::message::Response::NoSuchArgument,
        dcmtkpp::message::Response::NoSuchAttribute,
        dcmtkpp::message::Response::NoSuchEventType,
        dcmtkpp::message::Response::NoSuchSOPInstance,
        dcmtkpp::message::Response::NoSuchSOPClass,
        dcmtkpp::message::Response::ProcessingFailure,
        dcmtkpp::message::Response::ResourceLimitation,
        dcmtkpp::message::Response::UnrecognizedOperation,
        dcmtkpp::message::Response::NoSuchActionType,
        dcmtkpp::message::Response::RefusedNotAuthorized
    };

    for(auto const status:statuses)
    {
        BOOST_REQUIRE(!dcmtkpp::message::Response::is_pending(status));
        BOOST_REQUIRE(!dcmtkpp::message::Response::is_warning(status));
        BOOST_REQUIRE(dcmtkpp::message::Response::is_failure(status));

        dcmtkpp::message::Response response(1234, status);
        BOOST_REQUIRE(!response.is_pending());
        BOOST_REQUIRE(!response.is_warning());
        BOOST_REQUIRE(response.is_failure());
    }
}
