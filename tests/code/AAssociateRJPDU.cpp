#define BOOST_TEST_MODULE AAssociateRJPDU
#include <boost/test/unit_test.hpp>

#include <memory>

#include "dcmtkpp/AAssociateRJPDU.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/ProtocolDataUnit.h"

dcmtkpp::ProtocolDataUnit::Data const data = {
    0x03, 0x00,
    0x00, 0x00, 0x00, 0x04,
    0x00, 0x00,
    0x01, 0x02
};

BOOST_AUTO_TEST_CASE(ConstructorFields)
{
    dcmtkpp::AAssociateRJPDU const pdu(1, 2);
    BOOST_REQUIRE_EQUAL(
        pdu.get_pdu_type(), dcmtkpp::ProtocolDataUnit::A_ASSOCIATE_RJ);
    BOOST_REQUIRE_EQUAL(pdu.get_source(), 1);
    BOOST_REQUIRE_EQUAL(pdu.get_reason(), 2);
}

BOOST_AUTO_TEST_CASE(ConstructorData)
{
    dcmtkpp::AAssociateRJPDU const pdu(data);
    BOOST_REQUIRE_EQUAL(
        pdu.get_pdu_type(), dcmtkpp::ProtocolDataUnit::A_ASSOCIATE_RJ);
    BOOST_REQUIRE_EQUAL(pdu.get_source(), 1);
    BOOST_REQUIRE_EQUAL(pdu.get_reason(), 2);
}

BOOST_AUTO_TEST_CASE(Factory)
{
    auto const pdu = dcmtkpp::ProtocolDataUnit::factory(data);
    BOOST_REQUIRE_EQUAL(
        pdu->get_pdu_type(), dcmtkpp::ProtocolDataUnit::A_ASSOCIATE_RJ);
    auto const a_abort_pdu =
        std::dynamic_pointer_cast<dcmtkpp::AAssociateRJPDU>(pdu);
    BOOST_REQUIRE(a_abort_pdu.get() != nullptr);
    BOOST_REQUIRE_EQUAL(a_abort_pdu->get_source(), 1);
    BOOST_REQUIRE_EQUAL(a_abort_pdu->get_reason(), 2);
}

BOOST_AUTO_TEST_CASE(AsBinary)
{
    dcmtkpp::AAssociateRJPDU const pdu(1, 2);
    BOOST_REQUIRE(pdu.as_binary() == data);
}

BOOST_AUTO_TEST_CASE(WrongSource)
{
    dcmtkpp::AAssociateRJPDU pdu(1, 2);
    BOOST_REQUIRE_THROW(pdu.set_source(4), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(WrongReason)
{
    dcmtkpp::AAssociateRJPDU pdu(1, 2);
    BOOST_REQUIRE_THROW(pdu.set_reason(25), dcmtkpp::Exception);
}
