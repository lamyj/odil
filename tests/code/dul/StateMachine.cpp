#define BOOST_TEST_MODULE StateMachine
#include <boost/test/unit_test.hpp>

#include "odil/Exception.h"
#include "odil/dul/EventData.h"
#include "odil/dul/StateMachine.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::dul::StateMachine state_machine;
    BOOST_REQUIRE(
        state_machine.get_state() == odil::dul::StateMachine::State::Sta1);
}

BOOST_AUTO_TEST_CASE(WrongTransition)
{
    odil::dul::StateMachine state_machine;
    odil::dul::EventData data;
    BOOST_REQUIRE_THROW(
        state_machine.transition(odil::dul::StateMachine::Event::None, data),
        odil::Exception);
}
