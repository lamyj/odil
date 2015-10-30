#define BOOST_TEST_MODULE AReleaseRPPDU
#include <boost/test/unit_test.hpp>

#include <memory>

#include "dcmtkpp/AReleaseRPPDU.h"
#include "dcmtkpp/ProtocolDataUnit.h"

dcmtkpp::ProtocolDataUnit::Data const data = {
    0x06, 0x00,
    0x04, 0x00, 0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00
};

BOOST_AUTO_TEST_CASE(ConstructorFields)
{
    dcmtkpp::AReleaseRPPDU const pdu;
    BOOST_REQUIRE_EQUAL(pdu.get_pdu_type(), dcmtkpp::ProtocolDataUnit::A_RELEASE_RP);
}

BOOST_AUTO_TEST_CASE(ConstructorData)
{
    dcmtkpp::AReleaseRPPDU const pdu(data);
    BOOST_REQUIRE_EQUAL(pdu.get_pdu_type(), dcmtkpp::ProtocolDataUnit::A_RELEASE_RP);
}

BOOST_AUTO_TEST_CASE(Factory)
{
    auto const pdu = dcmtkpp::ProtocolDataUnit::factory(data);
    BOOST_REQUIRE_EQUAL(pdu->get_pdu_type(), dcmtkpp::ProtocolDataUnit::A_RELEASE_RP);
    auto const a_release_rp_pdu = std::dynamic_pointer_cast<dcmtkpp::AReleaseRPPDU>(pdu);
    BOOST_REQUIRE(a_release_rp_pdu.get() != nullptr);
}

BOOST_AUTO_TEST_CASE(AsBinary)
{
    dcmtkpp::AReleaseRPPDU const pdu;
    BOOST_REQUIRE(pdu.as_binary() == data);
}
