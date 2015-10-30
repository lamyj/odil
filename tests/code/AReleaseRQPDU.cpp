#define BOOST_TEST_MODULE AReleaseRQPDU
#include <boost/test/unit_test.hpp>

#include <memory>

#include "dcmtkpp/AReleaseRQPDU.h"
#include "dcmtkpp/ProtocolDataUnit.h"

dcmtkpp::ProtocolDataUnit::Data const data = {
    0x05, 0x00,
    0x00, 0x00, 0x00, 0x04,
    0x00, 0x00,
    0x00, 0x00
};

BOOST_AUTO_TEST_CASE(ConstructorFields)
{
    dcmtkpp::AReleaseRQPDU const pdu;
    BOOST_REQUIRE_EQUAL(pdu.get_pdu_type(), dcmtkpp::ProtocolDataUnit::A_RELEASE_RQ);
}

BOOST_AUTO_TEST_CASE(ConstructorData)
{
    dcmtkpp::AReleaseRQPDU const pdu(data);
    BOOST_REQUIRE_EQUAL(pdu.get_pdu_type(), dcmtkpp::ProtocolDataUnit::A_RELEASE_RQ);
}

BOOST_AUTO_TEST_CASE(Factory)
{
    auto const pdu = dcmtkpp::ProtocolDataUnit::factory(data);
    BOOST_REQUIRE_EQUAL(pdu->get_pdu_type(), dcmtkpp::ProtocolDataUnit::A_RELEASE_RQ);
    auto const a_release_rq_pdu = std::dynamic_pointer_cast<dcmtkpp::AReleaseRQPDU>(pdu);
    BOOST_REQUIRE(a_release_rq_pdu.get() != nullptr);
}

BOOST_AUTO_TEST_CASE(AsBinary)
{
    dcmtkpp::AReleaseRQPDU const pdu;
    BOOST_REQUIRE(pdu.as_binary() == data);
}
