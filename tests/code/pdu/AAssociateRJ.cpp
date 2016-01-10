#define BOOST_TEST_MODULE pdu::AssociateRJ
#include <boost/test/unit_test.hpp>

#include <sstream>

#include "odil/pdu/AAssociateRJ.h"
#include "odil/Exception.h"

std::string const data = {
    0x03, 0x00,
    0x00, 0x00, 0x00, 0x04,
    0x00, 0x01,
    0x02, 0x03
};

BOOST_AUTO_TEST_CASE(ConstructorFields)
{
    odil::pdu::AAssociateRJ const pdu(1, 2, 3);
    BOOST_REQUIRE_EQUAL(pdu.get_result(), 1);
    BOOST_REQUIRE_EQUAL(pdu.get_source(), 2);
    BOOST_REQUIRE_EQUAL(pdu.get_reason(), 3);
}

BOOST_AUTO_TEST_CASE(ConstructorStream)
{
    std::istringstream stream(data);
    odil::pdu::AAssociateRJ const pdu(stream);
    BOOST_REQUIRE_EQUAL(pdu.get_result(), 1);
    BOOST_REQUIRE_EQUAL(pdu.get_source(), 2);
    BOOST_REQUIRE_EQUAL(pdu.get_reason(), 3);
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::pdu::AAssociateRJ const pdu(1, 2, 3);
    std::ostringstream stream;
    stream << pdu;

    BOOST_REQUIRE(stream.str() == data);
}

BOOST_AUTO_TEST_CASE(WrongResult)
{
    odil::pdu::AAssociateRJ pdu(1, 2, 3);
    BOOST_REQUIRE_THROW(pdu.set_result(4), odil::Exception);
}


BOOST_AUTO_TEST_CASE(WrongSource)
{
    odil::pdu::AAssociateRJ pdu(1, 2, 3);
    BOOST_REQUIRE_THROW(pdu.set_source(4), odil::Exception);
}

BOOST_AUTO_TEST_CASE(WrongReason)
{
    odil::pdu::AAssociateRJ pdu(1, 2, 3);
    BOOST_REQUIRE_THROW(pdu.set_reason(25), odil::Exception);
}
