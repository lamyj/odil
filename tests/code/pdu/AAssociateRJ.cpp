#define BOOST_TEST_MODULE pdu::AssociateRJ
#include <boost/test/unit_test.hpp>

#include <sstream>

#include "dcmtkpp/pdu/AAssociateRJ.h"
#include "dcmtkpp/Exception.h"

std::string const data = {
    0x03, 0x00,
    0x00, 0x00, 0x00, 0x04,
    0x00, 0x01,
    0x02, 0x03
};

BOOST_AUTO_TEST_CASE(ConstructorFields)
{
    dcmtkpp::pdu::AAssociateRJ const pdu(1, 2, 3);
    BOOST_REQUIRE_EQUAL(pdu.get_result(), 1);
    BOOST_REQUIRE_EQUAL(pdu.get_source(), 2);
    BOOST_REQUIRE_EQUAL(pdu.get_reason(), 3);
}

BOOST_AUTO_TEST_CASE(ConstructorStream)
{
    std::istringstream stream(data);
    dcmtkpp::pdu::AAssociateRJ const pdu(stream);
    BOOST_REQUIRE_EQUAL(pdu.get_result(), 1);
    BOOST_REQUIRE_EQUAL(pdu.get_source(), 2);
    BOOST_REQUIRE_EQUAL(pdu.get_reason(), 3);
}

BOOST_AUTO_TEST_CASE(Write)
{
    dcmtkpp::pdu::AAssociateRJ const pdu(1, 2, 3);
    std::ostringstream stream;
    stream << pdu;

    BOOST_REQUIRE(stream.str() == data);
}

BOOST_AUTO_TEST_CASE(WrongResult)
{
    dcmtkpp::pdu::AAssociateRJ pdu(1, 2, 3);
    BOOST_REQUIRE_THROW(pdu.set_result(4), dcmtkpp::Exception);
}


BOOST_AUTO_TEST_CASE(WrongSource)
{
    dcmtkpp::pdu::AAssociateRJ pdu(1, 2, 3);
    BOOST_REQUIRE_THROW(pdu.set_source(4), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(WrongReason)
{
    dcmtkpp::pdu::AAssociateRJ pdu(1, 2, 3);
    BOOST_REQUIRE_THROW(pdu.set_reason(25), dcmtkpp::Exception);
}
