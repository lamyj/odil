#define BOOST_TEST_MODULE ServiceRole
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/ServiceRole.h"

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::ServiceRole const service_role;
    BOOST_CHECK_EQUAL(service_role.get_network(), static_cast<dcmtkpp::Network *>(NULL));
    BOOST_CHECK_EQUAL(service_role.get_association(), static_cast<dcmtkpp::Association *>(NULL));
}
