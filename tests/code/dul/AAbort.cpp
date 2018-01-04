#define BOOST_TEST_MODULE pdu::AAbort
#include <boost/test/unit_test.hpp>

#include <istream>
#include <memory>

#include "odil/dul/AAbort.h"
#include "odil/Exception.h"

std::string const data = {
    0x07, 0x00,
    0x00, 0x00, 0x00, 0x04,
    0x00, 0x00,
    0x01, 0x02
};

BOOST_AUTO_TEST_CASE(ConstructorFields)
{
    odil::dul::AAbort const pdu(1, 2);
    BOOST_REQUIRE_EQUAL(pdu.get_source(), 1);
    BOOST_REQUIRE_EQUAL(pdu.get_reason(), 2);
}

BOOST_AUTO_TEST_CASE(ConstructorStream)
{
    std::istringstream stream(data);
    odil::dul::AAbort const pdu(stream);
    BOOST_REQUIRE_EQUAL(pdu.get_source(), 1);
    BOOST_REQUIRE_EQUAL(pdu.get_reason(), 2);
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::dul::AAbort const pdu(1, 2);
    std::ostringstream stream;
    stream << pdu;

    BOOST_REQUIRE(stream.str() == data);
}

BOOST_AUTO_TEST_CASE(WrongSource)
{
    odil::dul::AAbort pdu(1, 2);
    BOOST_REQUIRE_THROW(pdu.set_source(3), odil::Exception);
}

BOOST_AUTO_TEST_CASE(WrongReason)
{
    odil::dul::AAbort pdu(1, 2);
    BOOST_REQUIRE_THROW(pdu.set_reason(9), odil::Exception);
}
