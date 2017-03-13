#define BOOST_TEST_MODULE ItemWithParameters
#include <boost/test/unit_test.hpp>

#include <sstream>

#include "odil/webservices/ItemWithParameters.h"

BOOST_AUTO_TEST_CASE(NoParameter)
{
    std::stringstream stream("text/plain");
    odil::webservices::ItemWithParameters item;
    stream >> item;

    BOOST_REQUIRE_EQUAL(item.name, "text/plain");
    BOOST_REQUIRE(item.name_parameters.empty());
    BOOST_REQUIRE(item.extension_parameters.empty());
}

BOOST_AUTO_TEST_CASE(NameParametersOnly)
{
    std::stringstream stream(
        "text/plain; charset=\"iso-8859-1\"; format=\"flowed\"");
    odil::webservices::ItemWithParameters item;
    stream >> item;

    typedef std::map<std::string, std::string> Map;

    BOOST_REQUIRE_EQUAL(item.name, "text/plain");
    BOOST_REQUIRE(
        item.name_parameters == Map({
            { "charset", "\"iso-8859-1\""},
            { "format", "\"flowed\""}
    }));
    BOOST_REQUIRE(item.extension_parameters.empty());
}

BOOST_AUTO_TEST_CASE(ExtensionParametersOnly)
{
    std::stringstream stream("text/plain; q=0.8;foo=bar");
    odil::webservices::ItemWithParameters item;
    stream >> item;

    typedef std::map<std::string, std::string> Map;

    BOOST_REQUIRE_EQUAL(item.name, "text/plain");
    BOOST_REQUIRE(item.name_parameters.empty());
    BOOST_REQUIRE(
        item.extension_parameters == Map({ { "q", "0.8"}, { "foo", "bar"} }));

}

BOOST_AUTO_TEST_CASE(BothParameters)
{
    std::stringstream stream(
        "text/plain; charset=\"iso-8859-1\"; format=\"flowed\"; q=0.8;foo=bar");
    odil::webservices::ItemWithParameters item;
    stream >> item;

    typedef std::map<std::string, std::string> Map;

    BOOST_REQUIRE_EQUAL(item.name, "text/plain");
    BOOST_REQUIRE(
        item.name_parameters == Map({
            { "charset", "\"iso-8859-1\""},
            { "format", "\"flowed\""}
    }));
    BOOST_REQUIRE(
        item.extension_parameters == Map({ { "q", "0.8"}, { "foo", "bar"} }));

}
