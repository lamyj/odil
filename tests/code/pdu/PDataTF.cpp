#define BOOST_TEST_MODULE pdu::PDataTF
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>
#include <vector>

#include "odil/Exception.h"
#include "odil/pdu/PDataTF.h"

std::string const data = {
    0x04, 0x00,
    0x00, 0x00, 0x00, 0x1e,

    0x00, 0x00, 0x00, 0x0a,
    0x01, 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,

    0x00, 0x00, 0x00, 0x0c,
    0x03, 0x02, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12
};

std::vector<odil::pdu::PDataTF::PresentationDataValueItem> const pdv_items = {
    { 1, 0x01, "\x01\x02\x03\x04\x05\x06\x07\x08" },
    { 3, 0x02, "\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12" },
};

namespace odil
{

namespace pdu
{

bool operator==(
    PDataTF::PresentationDataValueItem const & lhs,
    PDataTF::PresentationDataValueItem const & rhs)
{
    return (
        lhs.get_presentation_context_id() == rhs.get_presentation_context_id() &&
        lhs.get_control_header() == rhs.get_control_header() &&
        lhs.get_fragment() == rhs.get_fragment());
}

}

}

BOOST_AUTO_TEST_CASE(ConstructorPDV)
{
    odil::pdu::PDataTF const pdu(pdv_items);
    BOOST_REQUIRE(pdu.get_pdv_items() == pdv_items);
}

BOOST_AUTO_TEST_CASE(ConstructorStream)
{
    std::istringstream stream(data);
    odil::pdu::PDataTF const pdu(stream);
    BOOST_REQUIRE(pdu.get_pdv_items() == pdv_items);
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::pdu::PDataTF const pdu(pdv_items);
    std::ostringstream stream;
    stream << pdu;
    BOOST_REQUIRE(stream.str() == data);
}

BOOST_AUTO_TEST_CASE(WrongPresentationContextID)
{
    BOOST_REQUIRE_THROW(
        odil::pdu::PDataTF::PresentationDataValueItem(
            2, pdv_items[0].get_control_header(), pdv_items[0].get_fragment()),
        odil::Exception);
}
