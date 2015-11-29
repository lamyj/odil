#define BOOST_TEST_MODULE StateMachine
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/dul/EventData.h"
#include "dcmtkpp/dul/StateMachine.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::dul::StateMachine state_machine;
    BOOST_REQUIRE(
        state_machine.get_state() == dcmtkpp::dul::StateMachine::State::Sta1);
}

BOOST_AUTO_TEST_CASE(WrongTransition)
{
    dcmtkpp::dul::StateMachine state_machine;
    dcmtkpp::dul::EventData data;
    BOOST_REQUIRE_THROW(
        state_machine.transition(dcmtkpp::dul::StateMachine::Event::None, data),
        dcmtkpp::Exception);
}
