#define BOOST_TEST_MODULE AReleaseRPPDU
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "dcmtkpp/pdu/AReleaseRQ.h"

std::string const data = {
    0x05, 0x00,
    0x00, 0x00, 0x00, 0x04,
    0x00, 0x00,
    0x00, 0x00
};

BOOST_AUTO_TEST_CASE(ConstructorFields)
{
    dcmtkpp::pdu::AReleaseRQ const pdu;
}

BOOST_AUTO_TEST_CASE(ConstructorStream)
{
    std::istringstream stream(data);
    dcmtkpp::pdu::AReleaseRQ const pdu(stream);
}


BOOST_AUTO_TEST_CASE(Write)
{
    dcmtkpp::pdu::AReleaseRQ const pdu;
    std::ostringstream stream;
    stream << pdu;
    BOOST_REQUIRE(stream.str() == data);
}
