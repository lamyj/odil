#define BOOST_TEST_MODULE ServiceRole
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/Network.h"
#include "dcmtkpp/ServiceRole.h"

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::ServiceRole const role;
    BOOST_CHECK_EQUAL(
        role.get_network(), static_cast<dcmtkpp::Network *>(NULL));
    BOOST_CHECK_EQUAL(
        role.get_association(), static_cast<dcmtkpp::Association *>(NULL));
}

BOOST_AUTO_TEST_CASE(Network)
{
    dcmtkpp::ServiceRole role;

    dcmtkpp::Network network;
    role.set_network(&network);

    BOOST_CHECK_EQUAL(role.get_network(), &network);
}

BOOST_AUTO_TEST_CASE(Association)
{
    dcmtkpp::ServiceRole role;

    dcmtkpp::Association association;
    role.set_association(&association);

    BOOST_CHECK_EQUAL(role.get_association(), &association);
}

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
    dcmtkpp::Network network;
    dcmtkpp::Association association;
    dcmtkpp::ServiceRole role;
    role.set_network(&network);
    role.set_association(&association);

    dcmtkpp::ServiceRole const other(role);
    BOOST_CHECK_EQUAL(other.get_network(), role.get_network());
    BOOST_CHECK_EQUAL(other.get_association(), role.get_association());
}

BOOST_AUTO_TEST_CASE(Assignement)
{
    dcmtkpp::Network network;
    dcmtkpp::Association association;
    dcmtkpp::ServiceRole role;
    role.set_network(&network);
    role.set_association(&association);

    dcmtkpp::ServiceRole other;
    other = role;
    BOOST_CHECK_EQUAL(other.get_network(), role.get_network());
    BOOST_CHECK_EQUAL(other.get_association(), role.get_association());
}
