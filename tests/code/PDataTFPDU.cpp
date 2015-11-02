#define BOOST_TEST_MODULE PDataTFPDU
#include <boost/test/unit_test.hpp>

#include <memory>
#include <vector>

#include "dcmtkpp/PDataTFPDU.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/ProtocolDataUnit.h"

dcmtkpp::ProtocolDataUnit::Data const data = {
    0x04, 0x00,
    0x00, 0x00, 0x00, 0x1c,

    0x00, 0x00, 0x00, 0x0a,
    0x01, 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,

    0x00, 0x00, 0x00, 0x0a,
    0x03, 0x02, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
};

std::vector<dcmtkpp::PDataTFPDU::PresentationDataValueItem> const pdv_items = {
    { 1, { true, false, { 1,2,3,4,5,6,7,8 } } },
    { 3, { false, true, { 9,10,11,12,13,14,15,16 } } },
};

BOOST_AUTO_TEST_CASE(ConstructorPDV)
{
    dcmtkpp::PDataTFPDU const pdu(pdv_items);
    BOOST_REQUIRE_EQUAL(pdu.get_pdu_type(), dcmtkpp::ProtocolDataUnit::P_DATA_TF);
    BOOST_REQUIRE(pdu.get_pdv_items() == pdv_items);
}

BOOST_AUTO_TEST_CASE(ConstructorData)
{
    dcmtkpp::PDataTFPDU const pdu(data);
    BOOST_REQUIRE_EQUAL(pdu.get_pdu_type(), dcmtkpp::ProtocolDataUnit::P_DATA_TF);
    BOOST_REQUIRE(pdu.get_pdv_items() == pdv_items);
}

BOOST_AUTO_TEST_CASE(Factory)
{
    auto const pdu = dcmtkpp::ProtocolDataUnit::factory(data);
    BOOST_REQUIRE_EQUAL(pdu->get_pdu_type(), dcmtkpp::ProtocolDataUnit::P_DATA_TF);
    auto const p_data_tf_pdu = std::dynamic_pointer_cast<dcmtkpp::PDataTFPDU>(pdu);
    BOOST_REQUIRE(p_data_tf_pdu.get() != nullptr);
    BOOST_REQUIRE(p_data_tf_pdu->get_pdv_items() == pdv_items);
}

BOOST_AUTO_TEST_CASE(AsBinary)
{
    dcmtkpp::PDataTFPDU const pdu(pdv_items);
    BOOST_REQUIRE(pdu.as_binary() == data);
}

BOOST_AUTO_TEST_CASE(WrongPresentationContextID)
{
    dcmtkpp::PDataTFPDU::PresentationDataValueItem const pdv_item = {
        2, pdv_items[0].pdv
    };
    BOOST_REQUIRE_THROW(dcmtkpp::PDataTFPDU({pdv_item}), dcmtkpp::Exception);
}
