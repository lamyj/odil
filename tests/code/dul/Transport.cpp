#define BOOST_TEST_MODULE Transport
#include <boost/test/unit_test.hpp>

#include <chrono>
#include <boost/asio.hpp>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/dul/Transport.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::dul::Transport transport;
    BOOST_REQUIRE(!transport.is_open());
}

BOOST_AUTO_TEST_CASE(Connect)
{
    dcmtkpp::dul::Transport transport;

    boost::asio::ip::tcp::resolver resolver(transport.get_service());
    boost::asio::ip::tcp::resolver::query const query(
        dcmtkpp::dul::Transport::Socket::protocol_type::v4(),
        "www.example.com", "80");
    auto const endpoint_it = resolver.resolve(query);

    transport.connect(*endpoint_it);
    BOOST_REQUIRE(transport.is_open());

    transport.write("HEAD / HTTP/1.1\r\nHost: www.example.com\r\n\r\n");

    auto const response = transport.read(128);
    BOOST_REQUIRE(!response.empty());

    transport.close();
    BOOST_REQUIRE(!transport.is_open());
}

BOOST_AUTO_TEST_CASE(NotConnected)
{
    dcmtkpp::dul::Transport transport;

    BOOST_REQUIRE_THROW(transport.write("..."), dcmtkpp::Exception);
    BOOST_REQUIRE_THROW(transport.read(1), dcmtkpp::Exception);
    BOOST_REQUIRE_THROW(transport.close(), dcmtkpp::Exception);
}
