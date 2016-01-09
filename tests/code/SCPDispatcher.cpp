#define BOOST_TEST_MODULE SCPDispatcher
#include <boost/test/unit_test.hpp>

#include <memory>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/EchoSCP.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/SCPDispatcher.h"
#include "dcmtkpp/message/Message.h"

BOOST_AUTO_TEST_CASE(Empty)
{
    dcmtkpp::Association association;
    dcmtkpp::SCPDispatcher dispatcher(association);
    BOOST_REQUIRE_EQUAL(
        dispatcher.has_scp(dcmtkpp::message::Message::Command::C_ECHO_RQ),
        false);
    BOOST_REQUIRE_THROW(
        dispatcher.get_scp(dcmtkpp::message::Message::Command::C_ECHO_RQ),
        dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(SCP)
{
    dcmtkpp::Association association;
    dcmtkpp::SCPDispatcher dispatcher(association);

    auto scp = std::make_shared<dcmtkpp::EchoSCP>(association);
    dispatcher.set_scp(
        dcmtkpp::message::Message::Command::C_ECHO_RQ,
        scp);

    BOOST_REQUIRE_NO_THROW(
        dispatcher.get_scp(dcmtkpp::message::Message::Command::C_ECHO_RQ));
}
