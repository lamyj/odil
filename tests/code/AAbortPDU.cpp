#define BOOST_TEST_MODULE AAbortPDU
#include <boost/test/unit_test.hpp>

#include <memory>

#include "dcmtkpp/AAbortPDU.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/ProtocolDataUnit.h"

dcmtkpp::ProtocolDataUnit::Data const data = {
    0x07, 0x00,
    0x00, 0x00, 0x00, 0x04,
    0x00, 0x00,
    0x01, 0x02
};

BOOST_AUTO_TEST_CASE(ConstructorFields)
{
    dcmtkpp::AAbortPDU const pdu(1, 2);
    BOOST_REQUIRE_EQUAL(pdu.get_pdu_type(), dcmtkpp::ProtocolDataUnit::A_ABORT);
    BOOST_REQUIRE_EQUAL(pdu.get_source(), 1);
    BOOST_REQUIRE_EQUAL(pdu.get_reason(), 2);
}

BOOST_AUTO_TEST_CASE(ConstructorData)
{
    dcmtkpp::AAbortPDU const pdu(data);
    BOOST_REQUIRE_EQUAL(pdu.get_pdu_type(), dcmtkpp::ProtocolDataUnit::A_ABORT);
    BOOST_REQUIRE_EQUAL(pdu.get_source(), 1);
    BOOST_REQUIRE_EQUAL(pdu.get_reason(), 2);
}

BOOST_AUTO_TEST_CASE(Factory)
{
    auto const pdu = dcmtkpp::ProtocolDataUnit::factory(data);
    BOOST_REQUIRE_EQUAL(pdu->get_pdu_type(), dcmtkpp::ProtocolDataUnit::A_ABORT);
    auto const a_abort_pdu = std::dynamic_pointer_cast<dcmtkpp::AAbortPDU>(pdu);
    BOOST_REQUIRE(a_abort_pdu.get() != nullptr);
    BOOST_REQUIRE_EQUAL(a_abort_pdu->get_source(), 1);
    BOOST_REQUIRE_EQUAL(a_abort_pdu->get_reason(), 2);
}

BOOST_AUTO_TEST_CASE(AsBinary)
{
    dcmtkpp::AAbortPDU const pdu(1, 2);
    BOOST_REQUIRE(pdu.as_binary() == data);
}

BOOST_AUTO_TEST_CASE(WrongSource)
{
    dcmtkpp::AAbortPDU pdu(1, 2);
    BOOST_REQUIRE_THROW(pdu.set_source(3), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(WrongReason)
{
    dcmtkpp::AAbortPDU pdu(1, 2);
    BOOST_REQUIRE_THROW(pdu.set_reason(9), dcmtkpp::Exception);
}
