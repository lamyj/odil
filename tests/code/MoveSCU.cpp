#define BOOST_TEST_MODULE MoveSCU
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/MoveSCU.h"

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::MoveSCU const scu;
    BOOST_CHECK_EQUAL(scu.get_move_destination(), "");
}

BOOST_AUTO_TEST_CASE(MoveDestination)
{
    dcmtkpp::MoveSCU scu;
    scu.set_move_destination("remote");
    BOOST_CHECK_EQUAL(scu.get_move_destination(), "remote");
}
