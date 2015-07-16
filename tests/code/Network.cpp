#define BOOST_TEST_MODULE Network
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/assoc.h>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Network.h"

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::Network network;

    BOOST_CHECK_EQUAL(network.get_role(), NET_REQUESTOR);
    BOOST_CHECK_EQUAL(network.get_port(), 0);
    BOOST_CHECK_EQUAL(network.get_timeout(), 30);
    BOOST_CHECK_EQUAL(network.get_options(), 0);

    BOOST_CHECK(!network.is_initialized());
    BOOST_CHECK_EQUAL(network.get_network(), static_cast<T_ASC_Network*>(NULL));
}

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::Network network(NET_ACCEPTOR, 11112, 10, 1);

    BOOST_CHECK_EQUAL(network.get_role(), NET_ACCEPTOR);
    BOOST_CHECK_EQUAL(network.get_port(), 11112);
    BOOST_CHECK_EQUAL(network.get_timeout(), 10);
    BOOST_CHECK_EQUAL(network.get_options(), 1);

    BOOST_CHECK(!network.is_initialized());
    BOOST_CHECK_EQUAL(network.get_network(), static_cast<T_ASC_Network*>(NULL));
}

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
    dcmtkpp::Network network(NET_ACCEPTOR, 11112, 10, 1);
    dcmtkpp::Network other(network);

    BOOST_CHECK_EQUAL(other.get_role(), network.get_role());
    BOOST_CHECK_EQUAL(other.get_port(), network.get_port());
    BOOST_CHECK_EQUAL(other.get_timeout(), network.get_timeout());
    BOOST_CHECK_EQUAL(other.get_options(), network.get_options());
    BOOST_CHECK_EQUAL(other.is_initialized(), network.is_initialized());
    BOOST_CHECK_EQUAL(other.get_network(), network.get_network());
}

BOOST_AUTO_TEST_CASE(Assignment)
{
    dcmtkpp::Network network(NET_ACCEPTOR, 11112, 10, 1);
    dcmtkpp::Network other(NET_REQUESTOR, 112, 30, 0);
    other = network;

    BOOST_CHECK_EQUAL(other.get_role(), network.get_role());
    BOOST_CHECK_EQUAL(other.get_port(), network.get_port());
    BOOST_CHECK_EQUAL(other.get_timeout(), network.get_timeout());
    BOOST_CHECK_EQUAL(other.get_options(), network.get_options());
    BOOST_CHECK_EQUAL(other.is_initialized(), network.is_initialized());
    BOOST_CHECK_EQUAL(other.get_network(), network.get_network());
}

BOOST_AUTO_TEST_CASE(Role)
{
    dcmtkpp::Network network;
    network.set_role(NET_ACCEPTOR);

    BOOST_CHECK_EQUAL(network.get_role(), NET_ACCEPTOR);
}

BOOST_AUTO_TEST_CASE(RoleAssociated)
{
    dcmtkpp::Network network;
    network.initialize();

    BOOST_CHECK_THROW(network.set_role(NET_ACCEPTOR), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Port)
{
    dcmtkpp::Network network;
    network.set_port(1234);

    BOOST_CHECK_EQUAL(network.get_port(), 1234);
}

BOOST_AUTO_TEST_CASE(PortAssociated)
{
    dcmtkpp::Network network;
    network.initialize();

    BOOST_CHECK_THROW(network.set_port(1234), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Timeout)
{
    dcmtkpp::Network network;
    network.set_timeout(10);

    BOOST_CHECK_EQUAL(network.get_timeout(), 10);
}

BOOST_AUTO_TEST_CASE(TimeoutAssociated)
{
    dcmtkpp::Network network;
    network.initialize();

    BOOST_CHECK_THROW(network.set_timeout(10), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Options)
{
    dcmtkpp::Network network;
    network.set_options(1);

    BOOST_CHECK_EQUAL(network.get_options(), 1);
}

BOOST_AUTO_TEST_CASE(OptionsAssociated)
{
    dcmtkpp::Network network;
    network.initialize();

    BOOST_CHECK_THROW(network.set_options(1), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Initialize)
{
    dcmtkpp::Network network(NET_REQUESTOR, 11112, 1, 0);
    network.initialize();

    BOOST_CHECK(network.is_initialized());
    BOOST_CHECK_NE(network.get_network(),  static_cast<T_ASC_Network*>(NULL));
}

BOOST_AUTO_TEST_CASE(Drop)
{
    dcmtkpp::Network network(NET_REQUESTOR, 11112, 1, 0);
    network.initialize();
    network.drop();
    BOOST_CHECK(!network.is_initialized());
    BOOST_CHECK_EQUAL(network.get_network(),  static_cast<T_ASC_Network*>(NULL));
}

BOOST_AUTO_TEST_CASE(InitializeTwice)
{
    dcmtkpp::Network network(NET_REQUESTOR, 11112, 1, 0);
    network.initialize();
    BOOST_REQUIRE_THROW(network.initialize(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(DropNotInitialized)
{
    dcmtkpp::Network network;
    BOOST_REQUIRE_THROW(network.drop(), dcmtkpp::Exception);
}
