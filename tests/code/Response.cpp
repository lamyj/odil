#define BOOST_TEST_MODULE Response
#include <boost/test/unit_test.hpp>

#include <vector>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Message.h"
#include "dcmtkpp/Response.h"
#include "dcmtkpp/Value.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::Response const message(1234, dcmtkpp::Response::Pending);

    BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
    BOOST_CHECK_EQUAL(message.get_status(), dcmtkpp::Response::Pending);
}

BOOST_AUTO_TEST_CASE(MessageConstructor)
{
    dcmtkpp::DataSet command_set;
    command_set.add("MessageIDBeingRespondedTo", {1234});
    command_set.add("Status", {dcmtkpp::Response::Pending});
    dcmtkpp::Message const generic_message(command_set);

    dcmtkpp::Response const message(generic_message);

    BOOST_CHECK_EQUAL(message.get_message_id_being_responded_to(), 1234);
    BOOST_CHECK_EQUAL(message.get_status(), dcmtkpp::Response::Pending);
    BOOST_CHECK(!message.has_data_set());
}

BOOST_AUTO_TEST_CASE(StatusPending)
{
    std::vector<dcmtkpp::Value::Integer> const statuses = {
        dcmtkpp::Response::Pending,
    };

    for(auto const status:statuses)
    {
        dcmtkpp::Response response(1234, status);
        BOOST_REQUIRE(response.is_pending());
        BOOST_REQUIRE(!response.is_warning());
        BOOST_REQUIRE(!response.is_failure());
    }
}


BOOST_AUTO_TEST_CASE(StatusWarning)
{
    std::vector<dcmtkpp::Value::Integer> const statuses = {
        dcmtkpp::Response::AttributeListError,
        dcmtkpp::Response::AttributeValueOutOfRange
    };

    for(auto const status:statuses)
    {
        dcmtkpp::Response response(1234, status);
        BOOST_REQUIRE(!response.is_pending());
        BOOST_REQUIRE(response.is_warning());
        BOOST_REQUIRE(!response.is_failure());
    }
}

BOOST_AUTO_TEST_CASE(StatusFailure)
{
    std::vector<dcmtkpp::Value::Integer> const statuses = {
        dcmtkpp::Response::SOPClassNotSupported,
        dcmtkpp::Response::ClassInstanceConflict,
        dcmtkpp::Response::DuplicateSOPInstance,
        dcmtkpp::Response::DuplicateInvocation,
        dcmtkpp::Response::InvalidArgumentValue,
        dcmtkpp::Response::InvalidAttributeValue,
        dcmtkpp::Response::InvalidObjectInstance,
        dcmtkpp::Response::MissingAttribute,
        dcmtkpp::Response::MissingAttributeValue,
        dcmtkpp::Response::MistypedArgument,
        dcmtkpp::Response::NoSuchArgument,
        dcmtkpp::Response::NoSuchAttribute,
        dcmtkpp::Response::NoSuchEventType,
        dcmtkpp::Response::NoSuchSOPInstance,
        dcmtkpp::Response::NoSuchSOPClass,
        dcmtkpp::Response::ProcessingFailure,
        dcmtkpp::Response::ResourceLimitation,
        dcmtkpp::Response::UnrecognizedOperation,
        dcmtkpp::Response::NoSuchActionType,
        dcmtkpp::Response::RefusedNotAuthorized
    };

    for(auto const status:statuses)
    {
        dcmtkpp::Response response(1234, status);
        BOOST_REQUIRE(!response.is_pending());
        BOOST_REQUIRE(!response.is_warning());
        BOOST_REQUIRE(response.is_failure());
    }
}
