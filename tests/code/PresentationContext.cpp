#define BOOST_TEST_MODULE PresentationContext
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>
#include <vector>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/PresentationContext.h"

BOOST_AUTO_TEST_CASE(RQContext)
{
    dcmtkpp::PresentationContext const context("abstract_syntax", {"ts1", "ts2"});

    BOOST_REQUIRE_EQUAL(context.get_item_type(), 0x20);
    BOOST_REQUIRE_EQUAL(context.get_id(), 0x0);
    BOOST_REQUIRE_THROW(context.get_result_reason(), dcmtkpp::Exception);
    BOOST_REQUIRE_EQUAL(context.get_abstract_syntax(), "abstract_syntax");
    BOOST_REQUIRE(
        context.get_transfer_syntaxes() ==
            std::vector<std::string>({"ts1", "ts2"}));
    BOOST_REQUIRE_THROW(context.get_transfer_syntax(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ACContext)
{
    dcmtkpp::PresentationContext const context("transfer_syntax");

    BOOST_REQUIRE_EQUAL(context.get_item_type(), 0x21);
    BOOST_REQUIRE_EQUAL(context.get_id(), 0x0);
    BOOST_REQUIRE_EQUAL(context.get_result_reason(), 0x0);
    BOOST_REQUIRE_THROW(context.get_abstract_syntax(), dcmtkpp::Exception);
    BOOST_REQUIRE_THROW(context.get_transfer_syntaxes(), dcmtkpp::Exception);
    BOOST_REQUIRE_EQUAL(context.get_transfer_syntax(), "transfer_syntax");
}

BOOST_AUTO_TEST_CASE(RQId)
{
    dcmtkpp::PresentationContext context("abstract_syntax", {"ts1", "ts2"});
    context.set_id(123);
    BOOST_REQUIRE_EQUAL(context.get_id(), 123);
}

BOOST_AUTO_TEST_CASE(ACId)
{
    dcmtkpp::PresentationContext context("transfer_syntax");
    context.set_id(123);
    BOOST_REQUIRE_EQUAL(context.get_id(), 123);
}

BOOST_AUTO_TEST_CASE(RQResultReason)
{
    dcmtkpp::PresentationContext context("abstract_syntax", {"ts1", "ts2"});
    BOOST_REQUIRE_THROW(context.set_result_reason(1), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ACResultReason)
{
    dcmtkpp::PresentationContext context("transfer_syntax");
    context.set_result_reason(1);
    BOOST_REQUIRE_EQUAL(context.get_result_reason(), 1);
}

BOOST_AUTO_TEST_CASE(RQAbstractSyntax)
{
    dcmtkpp::PresentationContext context("abstract_syntax", {"ts1", "ts2"});
    context.set_abstract_syntax("foo");
    BOOST_REQUIRE_EQUAL(context.get_abstract_syntax(), "foo");
}

BOOST_AUTO_TEST_CASE(ACAbstractSyntax)
{
    dcmtkpp::PresentationContext context("transfer_syntax");
    BOOST_REQUIRE_THROW(context.set_abstract_syntax("foo"), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(RQTransferSyntaxes)
{
    dcmtkpp::PresentationContext context("abstract_syntax", {"ts1", "ts2"});
    context.set_transfer_syntaxes({"foo", "bar"});
    BOOST_REQUIRE(
        context.get_transfer_syntaxes() ==
            std::vector<std::string>({"foo", "bar"}));
}

BOOST_AUTO_TEST_CASE(ACTransferSyntaxes)
{
    dcmtkpp::PresentationContext context("transfer_syntax");
    BOOST_REQUIRE_THROW(
        context.set_transfer_syntaxes({"foo", "bar"}), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(RQTransferSyntax)
{
    dcmtkpp::PresentationContext context("abstract_syntax", {"ts1", "ts2"});
    BOOST_REQUIRE_THROW(context.set_transfer_syntax("foo"), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ACTransferSyntax)
{
    dcmtkpp::PresentationContext context("transfer_syntax");
    context.set_transfer_syntax("foo");
    BOOST_REQUIRE_EQUAL(context.get_transfer_syntax(), "foo");
}

BOOST_AUTO_TEST_CASE(WriteRQ)
{
    dcmtkpp::PresentationContext context("abstract_syntax", {"ts1", "ts2"});
    context.set_id(3);

    std::ostringstream stream;
    stream << context;

    std::string const expected(
        "\x20\x00\x00\x28"
        "\x03\x00\x00\x00"
        "\x30\x00\x00\x10""abstract_syntax\x00"
        "\x40\x00\x00\x4""ts1\x00"
        "\x40\x00\x00\x4""ts2\x00",
        44
    );

    BOOST_REQUIRE_EQUAL(stream.str(), expected);
}

BOOST_AUTO_TEST_CASE(WriteAC)
{
    dcmtkpp::PresentationContext context("transfer_syntax");
    context.set_id(3);
    context.set_result_reason(1);

    std::ostringstream stream;
    stream << context;

    std::string const expected(
        "\x21\x00\x00\x18"
        "\x03\x00\x01\x00"
        "\x40\x00\x00\x10""transfer_syntax\x00",
        28
    );

    BOOST_REQUIRE_EQUAL(stream.str(), expected);
}
