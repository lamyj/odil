#define BOOST_TEST_MODULE UID
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/uid.h"

BOOST_AUTO_TEST_CASE(generate)
{
    std::string const uid = dcmtkpp::generate_uid();
    BOOST_REQUIRE_LE(uid.size(), 64);
    for(auto const & c: uid)
    {
        BOOST_REQUIRE((c>='0' && c<='9') || c == '.');
    }
}
