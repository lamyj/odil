#define BOOST_TEST_MODULE Network
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/assoc.h>

#include "dcmtkpp/dcmtk/Exception.h"
#include "dcmtkpp/dcmtk/Network.h"

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::dcmtk::Network network;

    BOOST_CHECK_EQUAL(network.get_role(), NET_REQUESTOR);
    BOOST_CHECK_EQUAL(network.get_port(), 0);
    BOOST_CHECK_EQUAL(network.get_timeout(), 30);
    BOOST_CHECK_EQUAL(network.get_options(), 0);

    BOOST_CHECK(!network.is_initialized());
    BOOST_CHECK_EQUAL(network.get_network(), static_cast<T_ASC_Network*>(NULL));
}

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::dcmtk::Network network(NET_ACCEPTOR, 11112, 10, 1);

    BOOST_CHECK_EQUAL(network.get_role(), NET_ACCEPTOR);
    BOOST_CHECK_EQUAL(network.get_port(), 11112);
    BOOST_CHECK_EQUAL(network.get_timeout(), 10);
    BOOST_CHECK_EQUAL(network.get_options(), 1);

    BOOST_CHECK(!network.is_initialized());
    BOOST_CHECK_EQUAL(network.get_network(), static_cast<T_ASC_Network*>(NULL));
}

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
    dcmtkpp::dcmtk::Network network(NET_ACCEPTOR, 11112, 10, 1);
    dcmtkpp::dcmtk::Network other(network);

    BOOST_CHECK_EQUAL(other.get_role(), network.get_role());
    BOOST_CHECK_EQUAL(other.get_port(), network.get_port());
    BOOST_CHECK_EQUAL(other.get_timeout(), network.get_timeout());
    BOOST_CHECK_EQUAL(other.get_options(), network.get_options());
    BOOST_CHECK_EQUAL(other.is_initialized(), network.is_initialized());
    BOOST_CHECK_EQUAL(other.get_network(), network.get_network());
}

BOOST_AUTO_TEST_CASE(Assignment)
{
    dcmtkpp::dcmtk::Network network(NET_ACCEPTOR, 11112, 10, 1);
    dcmtkpp::dcmtk::Network other(NET_REQUESTOR, 112, 30, 0);
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
    dcmtkpp::dcmtk::Network network;
    network.set_role(NET_ACCEPTOR);

    BOOST_CHECK_EQUAL(network.get_role(), NET_ACCEPTOR);
}

BOOST_AUTO_TEST_CASE(RoleAssociated)
{
    dcmtkpp::dcmtk::Network network;
    network.initialize();

    BOOST_CHECK_THROW(network.set_role(NET_ACCEPTOR), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Port)
{
    dcmtkpp::dcmtk::Network network;
    network.set_port(1234);

    BOOST_CHECK_EQUAL(network.get_port(), 1234);
}

BOOST_AUTO_TEST_CASE(PortAssociated)
{
    dcmtkpp::dcmtk::Network network;
    network.initialize();

    BOOST_CHECK_THROW(network.set_port(1234), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Timeout)
{
    dcmtkpp::dcmtk::Network network;
    network.set_timeout(10);

    BOOST_CHECK_EQUAL(network.get_timeout(), 10);
}

BOOST_AUTO_TEST_CASE(TimeoutAssociated)
{
    dcmtkpp::dcmtk::Network network;
    network.initialize();

    BOOST_CHECK_THROW(network.set_timeout(10), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Options)
{
    dcmtkpp::dcmtk::Network network;
    network.set_options(1);

    BOOST_CHECK_EQUAL(network.get_options(), 1);
}

BOOST_AUTO_TEST_CASE(OptionsAssociated)
{
    dcmtkpp::dcmtk::Network network;
    network.initialize();

    BOOST_CHECK_THROW(network.set_options(1), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Initialize)
{
    dcmtkpp::dcmtk::Network network(NET_REQUESTOR, 11112, 1, 0);
    network.initialize();

    BOOST_CHECK(network.is_initialized());
    BOOST_CHECK_NE(network.get_network(),  static_cast<T_ASC_Network*>(NULL));
}

BOOST_AUTO_TEST_CASE(Drop)
{
    dcmtkpp::dcmtk::Network network(NET_REQUESTOR, 11112, 1, 0);
    network.initialize();
    network.drop();
    BOOST_CHECK(!network.is_initialized());
    BOOST_CHECK_EQUAL(network.get_network(),  static_cast<T_ASC_Network*>(NULL));
}

BOOST_AUTO_TEST_CASE(InitializeTwice)
{
    dcmtkpp::dcmtk::Network network(NET_REQUESTOR, 11112, 1, 0);
    network.initialize();
    BOOST_REQUIRE_THROW(network.initialize(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(DropNotInitialized)
{
    dcmtkpp::dcmtk::Network network;
    BOOST_REQUIRE_THROW(network.drop(), dcmtkpp::Exception);
}
