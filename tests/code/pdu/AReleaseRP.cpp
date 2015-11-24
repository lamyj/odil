#define BOOST_TEST_MODULE AReleaseRPPDU
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "dcmtkpp/pdu/AReleaseRP.h"
#include "dcmtkpp/ProtocolDataUnit.h"

std::string const data = {
    0x06, 0x00,
    0x00, 0x00, 0x00, 0x04,
    0x00, 0x00,
    0x00, 0x00
};

BOOST_AUTO_TEST_CASE(ConstructorFields)
{
    dcmtkpp::pdu::AReleaseRP const pdu;
}

BOOST_AUTO_TEST_CASE(ConstructorStream)
{
    std::istringstream stream(data);
    dcmtkpp::pdu::AReleaseRP const pdu(stream);
}


BOOST_AUTO_TEST_CASE(Write)
{
    dcmtkpp::pdu::AReleaseRP const pdu;
    std::ostringstream stream;
    stream << pdu;
    BOOST_REQUIRE(stream.str() == data);
}
