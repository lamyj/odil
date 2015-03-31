#define BOOST_TEST_MODULE Network
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/assoc.h>

#include "dcmtkpp/Network.h"

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::Network const network;

    BOOST_CHECK_EQUAL(network.get_role(), NET_REQUESTOR);
    BOOST_CHECK_EQUAL(network.get_port(), 0);
    BOOST_CHECK_EQUAL(network.get_timeout(), 30);
    BOOST_CHECK_EQUAL(network.get_options(), 0);

    BOOST_CHECK(!network.is_initialized());
}

BOOST_AUTO_TEST_CASE(Role)
{
    dcmtkpp::Network network;
    network.set_role(NET_ACCEPTOR);

    BOOST_CHECK_EQUAL(network.get_role(), NET_ACCEPTOR);
}

BOOST_AUTO_TEST_CASE(Port)
{
    dcmtkpp::Network network;
    network.set_port(1234);

    BOOST_CHECK_EQUAL(network.get_port(), 1234);
}

BOOST_AUTO_TEST_CASE(Timeout)
{
    dcmtkpp::Network network;
    network.set_timeout(10);

    BOOST_CHECK_EQUAL(network.get_timeout(), 10);
}

BOOST_AUTO_TEST_CASE(Options)
{
    dcmtkpp::Network network;
    network.set_options(1);

    BOOST_CHECK_EQUAL(network.get_options(), 1);
}
