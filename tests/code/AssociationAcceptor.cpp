#define BOOST_TEST_MODULE AssociationAcceptor
#include <boost/test/unit_test.hpp>

#include "odil/AssociationAcceptor.h"

BOOST_AUTO_TEST_CASE(AssociationRejected)
{
    odil::AssociationRejected const exception(1, 2, 3, "foo");
    BOOST_REQUIRE_EQUAL(exception.get_result(), 1);
    BOOST_REQUIRE_EQUAL(exception.get_source(), 2);
    BOOST_REQUIRE_EQUAL(exception.get_reason(), 3);
    BOOST_REQUIRE_EQUAL(exception.what(), "foo");
}
