#define BOOST_TEST_MODULE PresentationContext
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>
#include <vector>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/pdu/PresentationContext.h"

std::string const rq_data(
    "\x20\x00\x00\x25"
    "\x03\x00\x00\x00"
    "\x30\x00\x00\x0f""abstract_syntax"
    "\x40\x00\x00\x03""ts1"
    "\x40\x00\x00\x03""ts2",
    41
);

std::string const ac_data(
    "\x21\x00\x00\x17"
    "\x03\x00\x01\x00"
    "\x40\x00\x00\x0f""transfer_syntax",
    27
);

BOOST_AUTO_TEST_CASE(RQContext)
{
    dcmtkpp::pdu::PresentationContext const context(
        1, "abstract_syntax", {"ts1", "ts2"});

    BOOST_REQUIRE_EQUAL(context.get_item_type(), 0x20);
    BOOST_REQUIRE_EQUAL(context.get_id(), 1);
    BOOST_REQUIRE_THROW(context.get_result_reason(), dcmtkpp::Exception);
    BOOST_REQUIRE_EQUAL(context.get_abstract_syntax(), "abstract_syntax");
    BOOST_REQUIRE(
        context.get_transfer_syntaxes() ==
            std::vector<std::string>({"ts1", "ts2"}));
    BOOST_REQUIRE_THROW(context.get_transfer_syntax(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ACContext)
{
    dcmtkpp::pdu::PresentationContext const context(1, "transfer_syntax", 2);

    BOOST_REQUIRE_EQUAL(context.get_item_type(), 0x21);
    BOOST_REQUIRE_EQUAL(context.get_id(), 0x1);
    BOOST_REQUIRE_EQUAL(context.get_result_reason(), 0x2);
    BOOST_REQUIRE_THROW(context.get_abstract_syntax(), dcmtkpp::Exception);
    BOOST_REQUIRE_THROW(context.get_transfer_syntaxes(), dcmtkpp::Exception);
    BOOST_REQUIRE_EQUAL(context.get_transfer_syntax(), "transfer_syntax");
}

BOOST_AUTO_TEST_CASE(RQId)
{
    dcmtkpp::pdu::PresentationContext context(
        1, "abstract_syntax", {"ts1", "ts2"});
    context.set_id(123);
    BOOST_REQUIRE_EQUAL(context.get_id(), 123);
}

BOOST_AUTO_TEST_CASE(ACId)
{
    dcmtkpp::pdu::PresentationContext context(1, "transfer_syntax", 1);
    context.set_id(123);
    BOOST_REQUIRE_EQUAL(context.get_id(), 123);
}

BOOST_AUTO_TEST_CASE(RQResultReason)
{
    dcmtkpp::pdu::PresentationContext context(
        1, "abstract_syntax", {"ts1", "ts2"});
    BOOST_REQUIRE_THROW(context.set_result_reason(1), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ACResultReason)
{
    dcmtkpp::pdu::PresentationContext context(1, "transfer_syntax", 1);
    context.set_result_reason(2);
    BOOST_REQUIRE_EQUAL(context.get_result_reason(), 2);
}

BOOST_AUTO_TEST_CASE(RQAbstractSyntax)
{
    dcmtkpp::pdu::PresentationContext context(
        1, "abstract_syntax", {"ts1", "ts2"});
    context.set_abstract_syntax("foo");
    BOOST_REQUIRE_EQUAL(context.get_abstract_syntax(), "foo");
}

BOOST_AUTO_TEST_CASE(ACAbstractSyntax)
{
    dcmtkpp::pdu::PresentationContext context(1, "transfer_syntax", 1);
    BOOST_REQUIRE_THROW(context.set_abstract_syntax("foo"), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(RQTransferSyntaxes)
{
    dcmtkpp::pdu::PresentationContext context(
        1, "abstract_syntax", {"ts1", "ts2"});
    context.set_transfer_syntaxes({"foo", "bar"});
    BOOST_REQUIRE(
        context.get_transfer_syntaxes() ==
            std::vector<std::string>({"foo", "bar"}));
}

BOOST_AUTO_TEST_CASE(ACTransferSyntaxes)
{
    dcmtkpp::pdu::PresentationContext context(1, "transfer_syntax", 1);
    BOOST_REQUIRE_THROW(
        context.set_transfer_syntaxes({"foo", "bar"}), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(RQTransferSyntax)
{
    dcmtkpp::pdu::PresentationContext context(
        1, "abstract_syntax", {"ts1", "ts2"});
    BOOST_REQUIRE_THROW(context.set_transfer_syntax("foo"), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ACTransferSyntax)
{
    dcmtkpp::pdu::PresentationContext context(1, "transfer_syntax", 1);
    context.set_transfer_syntax("foo");
    BOOST_REQUIRE_EQUAL(context.get_transfer_syntax(), "foo");
}

BOOST_AUTO_TEST_CASE(WriteRQ)
{
    dcmtkpp::pdu::PresentationContext context(
        3, "abstract_syntax", {"ts1", "ts2"});

    std::ostringstream stream;
    stream << context;

    BOOST_REQUIRE_EQUAL(stream.str(), rq_data);
}

BOOST_AUTO_TEST_CASE(WriteAC)
{
    dcmtkpp::pdu::PresentationContext context(3, "transfer_syntax", 1);

    std::ostringstream stream;
    stream << context;

    BOOST_REQUIRE_EQUAL(stream.str(), ac_data);
}

BOOST_AUTO_TEST_CASE(ReadRQ)
{
    std::istringstream stream(rq_data);

    dcmtkpp::pdu::PresentationContext const context(stream);

    BOOST_REQUIRE_EQUAL(context.get_item_type(), 0x20);
    BOOST_REQUIRE_EQUAL(context.get_id(), 3);
    BOOST_REQUIRE_THROW(context.get_result_reason(), dcmtkpp::Exception);
    BOOST_REQUIRE_EQUAL(context.get_abstract_syntax(), "abstract_syntax");
    BOOST_REQUIRE(
        context.get_transfer_syntaxes() ==
            std::vector<std::string>({"ts1", "ts2"}));
    BOOST_REQUIRE_THROW(context.get_transfer_syntax(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ReadAC)
{
    std::istringstream stream(ac_data);

    dcmtkpp::pdu::PresentationContext const context(stream);

    BOOST_REQUIRE_EQUAL(context.get_item_type(), 0x21);
    BOOST_REQUIRE_EQUAL(context.get_id(), 3);
    BOOST_REQUIRE_EQUAL(context.get_result_reason(), 1);
    BOOST_REQUIRE_THROW(context.get_abstract_syntax(), dcmtkpp::Exception);
    BOOST_REQUIRE_THROW(context.get_transfer_syntaxes(), dcmtkpp::Exception);
    BOOST_REQUIRE_EQUAL(context.get_transfer_syntax(), "transfer_syntax");
}
