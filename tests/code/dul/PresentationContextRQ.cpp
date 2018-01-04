#define BOOST_TEST_MODULE PresentationContextRQ
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>
#include <vector>

#include "odil/Exception.h"
#include "odil/dul/PresentationContextRQ.h"

std::string const data(
    "\x20\x00\x00\x25"
    "\x03\x00\x00\x00"
    "\x30\x00\x00\x0f""abstract_syntax"
    "\x40\x00\x00\x03""ts1"
    "\x40\x00\x00\x03""ts2",
    41
);

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::dul::PresentationContextRQ const context(
        1, "abstract_syntax", {"ts1", "ts2"});

    BOOST_REQUIRE_EQUAL(context.get_item_type(), 0x20);
    BOOST_REQUIRE_EQUAL(context.get_id(), 1);
    BOOST_REQUIRE_EQUAL(context.get_abstract_syntax(), "abstract_syntax");
    BOOST_REQUIRE(
        context.get_transfer_syntaxes() ==
            std::vector<std::string>({"ts1", "ts2"}));
}

BOOST_AUTO_TEST_CASE(Id)
{
    odil::dul::PresentationContextRQ context(
        1, "abstract_syntax", {"ts1", "ts2"});
    context.set_id(123);
    BOOST_REQUIRE_EQUAL(context.get_id(), 123);
}

BOOST_AUTO_TEST_CASE(AbstractSyntax)
{
    odil::dul::PresentationContextRQ context(
        1, "abstract_syntax", {"ts1", "ts2"});
    context.set_abstract_syntax("foo");
    BOOST_REQUIRE_EQUAL(context.get_abstract_syntax(), "foo");
}

BOOST_AUTO_TEST_CASE(TransferSyntaxes)
{
    odil::dul::PresentationContextRQ context(
        1, "abstract_syntax", {"ts1", "ts2"});
    context.set_transfer_syntaxes({"foo", "bar"});
    BOOST_REQUIRE(
        context.get_transfer_syntaxes() ==
            std::vector<std::string>({"foo", "bar"}));
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::dul::PresentationContextRQ context(
        3, "abstract_syntax", {"ts1", "ts2"});

    std::ostringstream stream;
    stream << context;

    BOOST_REQUIRE_EQUAL(stream.str(), data);
}

BOOST_AUTO_TEST_CASE(Read)
{
    std::istringstream stream(data);

    odil::dul::PresentationContextRQ const context(stream);

    BOOST_REQUIRE_EQUAL(context.get_item_type(), 0x20);
    BOOST_REQUIRE_EQUAL(context.get_id(), 3);
    BOOST_REQUIRE_EQUAL(context.get_abstract_syntax(), "abstract_syntax");
    BOOST_REQUIRE(
        context.get_transfer_syntaxes() ==
            std::vector<std::string>({"ts1", "ts2"}));
}
