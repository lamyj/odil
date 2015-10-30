#define BOOST_TEST_MODULE ProtocolDataUnit
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/ProtocolDataUnit.h"
#include "dcmtkpp/Exception.h"

BOOST_AUTO_TEST_CASE(Factory)
{
    BOOST_REQUIRE_THROW(
        dcmtkpp::ProtocolDataUnit::factory({}),
        dcmtkpp::Exception);
}
