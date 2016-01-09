#define BOOST_TEST_MODULE Exception
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/Exception.h"

BOOST_AUTO_TEST_CASE(Exception)
{
    dcmtkpp::Exception const exception("foo");
    BOOST_REQUIRE_EQUAL(exception.what(), "foo");
}
