#define BOOST_TEST_MODULE AReleaseRPPDU
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "odil/pdu/AReleaseRP.h"

std::string const data = {
    0x06, 0x00,
    0x00, 0x00, 0x00, 0x04,
    0x00, 0x00,
    0x00, 0x00
};

BOOST_AUTO_TEST_CASE(ConstructorFields)
{
    odil::pdu::AReleaseRP const pdu;
}

BOOST_AUTO_TEST_CASE(ConstructorStream)
{
    std::istringstream stream(data);
    odil::pdu::AReleaseRP const pdu(stream);
}


BOOST_AUTO_TEST_CASE(Write)
{
    odil::pdu::AReleaseRP const pdu;
    std::ostringstream stream;
    stream << pdu;
    BOOST_REQUIRE(stream.str() == data);
}
