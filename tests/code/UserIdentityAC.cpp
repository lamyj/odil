#define BOOST_TEST_MODULE UserIdentityAC
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/UserIdentityAC.h"

BOOST_AUTO_TEST_CASE(ConstructorDefault)
{
    dcmtkpp::UserIdentityAC const user_identity;
    BOOST_REQUIRE_EQUAL(user_identity.get_server_response(), "");
}

BOOST_AUTO_TEST_CASE(ConstructorString)
{
    dcmtkpp::UserIdentityAC const user_identity("foo");
    BOOST_REQUIRE_EQUAL(user_identity.get_server_response(), "foo");
}

BOOST_AUTO_TEST_CASE(FromStream)
{
    std::string const data(
        "\x59\x00\x00\x05"
        "\x00\x03" "foo",
        9
    );
    std::istringstream stream(data);

    dcmtkpp::UserIdentityAC const user_identity(stream);

    BOOST_REQUIRE_EQUAL(user_identity.get_server_response(), "foo");
}

BOOST_AUTO_TEST_CASE(Type)
{
    dcmtkpp::UserIdentityAC user_identity;
    user_identity.set_server_response("foo");
    BOOST_REQUIRE_EQUAL(user_identity.get_server_response(), "foo");
}

BOOST_AUTO_TEST_CASE(Write)
{
    dcmtkpp::UserIdentityAC user_identity;
    user_identity.set_server_response("foo");

    std::ostringstream data;
    data << user_identity;

    std::string const expected(
        "\x59\x00\x00\x05"
        "\x00\x03" "foo",
        9
    );

    BOOST_REQUIRE_EQUAL(data.str(), expected);
}
