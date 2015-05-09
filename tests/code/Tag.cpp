#define BOOST_TEST_MODULE Tag
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Tag.h"

BOOST_AUTO_TEST_CASE(TwoArgumentsConstructor)
{
    dcmtkpp::Tag const tag(0xdead, 0xbeef);
    BOOST_CHECK_EQUAL(tag.group, 0xdead);
    BOOST_CHECK_EQUAL(tag.element, 0xbeef);
}

BOOST_AUTO_TEST_CASE(OneArgumentConstructor)
{
    dcmtkpp::Tag const tag(0xdeadbeef);
    BOOST_CHECK_EQUAL(tag.group, 0xdead);
    BOOST_CHECK_EQUAL(tag.element, 0xbeef);
}

BOOST_AUTO_TEST_CASE(StringConstructor)
{
    dcmtkpp::Tag const tag(std::string("PixelData"));
    BOOST_CHECK_EQUAL(tag.group, 0x7fe0);
    BOOST_CHECK_EQUAL(tag.element, 0x0010);
}

BOOST_AUTO_TEST_CASE(CharConstructor)
{
    dcmtkpp::Tag const tag("PixelData");
    BOOST_CHECK_EQUAL(tag.group, 0x7fe0);
    BOOST_CHECK_EQUAL(tag.element, 0x0010);
}

BOOST_AUTO_TEST_CASE(StringConstructorWrong)
{
    BOOST_CHECK_THROW(dcmtkpp::Tag("Foobar"), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
    dcmtkpp::Tag const tag(0xdead, 0xbeef);
    dcmtkpp::Tag const other(tag);
    BOOST_CHECK_EQUAL(other.group, 0xdead);
    BOOST_CHECK_EQUAL(other.element, 0xbeef);
}

BOOST_AUTO_TEST_CASE(Assignment)
{
    dcmtkpp::Tag const tag(0xdead, 0xbeef);

    dcmtkpp::Tag other(0xfedc, 0xba98);
    other = tag;
    BOOST_CHECK_EQUAL(other.group, 0xdead);
    BOOST_CHECK_EQUAL(other.element, 0xbeef);
}

BOOST_AUTO_TEST_CASE(Name)
{
    dcmtkpp::Tag const tag(0x7fe0, 0x0010);
    std::string const name = tag.get_name();
    BOOST_CHECK_EQUAL(name, "PixelData");
}

BOOST_AUTO_TEST_CASE(NameWrong)
{
    dcmtkpp::Tag const tag(0xEEEE, 0xEEEE);
    BOOST_CHECK_THROW(tag.get_name(), dcmtkpp::Exception);
}
