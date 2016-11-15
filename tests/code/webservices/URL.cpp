#define BOOST_TEST_MODULE URL
#include <boost/test/unit_test.hpp>

#include "odil/webservices/URL.h"

BOOST_AUTO_TEST_CASE(Parse)
{
    auto const url = odil::webservices::URL::parse(
        "foo://example.com:8042/over/there?name=ferret#nose");
    BOOST_REQUIRE_EQUAL(url.scheme, "foo");
    BOOST_REQUIRE_EQUAL(url.authority, "example.com:8042");
    BOOST_REQUIRE_EQUAL(url.path, "/over/there");
    BOOST_REQUIRE_EQUAL(url.query, "name=ferret");
    BOOST_REQUIRE_EQUAL(url.fragment, "nose");
}

BOOST_AUTO_TEST_CASE(Recompose)
{
    odil::webservices::URL const url{
        "foo", "example.com:8042", "/over/there", "name=ferret", "nose"};
    std::string const string(url);
    BOOST_REQUIRE_EQUAL(
        string, "foo://example.com:8042/over/there?name=ferret#nose");
}
