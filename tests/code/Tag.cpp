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

BOOST_AUTO_TEST_CASE(StringConstructorNumeric)
{
    dcmtkpp::Tag const tag(std::string("7fe00010"));
    BOOST_CHECK_EQUAL(tag.group, 0x7fe0);
    BOOST_CHECK_EQUAL(tag.element, 0x0010);
}

BOOST_AUTO_TEST_CASE(CharConstructorNumeric)
{
    dcmtkpp::Tag const tag("7fe00010");
    BOOST_CHECK_EQUAL(tag.group, 0x7fe0);
    BOOST_CHECK_EQUAL(tag.element, 0x0010);
}

BOOST_AUTO_TEST_CASE(StringConstructorWrong)
{
    BOOST_CHECK_THROW(dcmtkpp::Tag(std::string("Foobar")), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(CharConstructorWrong)
{
    BOOST_CHECK_THROW(dcmtkpp::Tag("Foobar"), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(StringConstructorNumericWrong)
{
    BOOST_CHECK_THROW(dcmtkpp::Tag(std::string("XXXXYYYY")), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(CharConstructorNumericWrong)
{
    BOOST_CHECK_THROW(dcmtkpp::Tag("XXXXYYYY"), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
    dcmtkpp::Tag const tag(0xdead, 0xbeef);
    dcmtkpp::Tag const other(tag);
    BOOST_CHECK_EQUAL(other.group, 0xdead);
    BOOST_CHECK_EQUAL(other.element, 0xbeef);
}

BOOST_AUTO_TEST_CASE(IsPrivate)
{
    dcmtkpp::Tag const tag1(0xdead, 0xbeef);
    dcmtkpp::Tag const tag2(0x7fe0, 0x0010);

    BOOST_CHECK(tag1.is_private());
    BOOST_CHECK(!tag2.is_private());
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

BOOST_AUTO_TEST_CASE(Equality)
{
    dcmtkpp::Tag const tag1(0xdead, 0xbeef);
    dcmtkpp::Tag const tag2(0xdead, 0xbeef);
    dcmtkpp::Tag const tag3(0xbeef, 0xf00d);

    BOOST_CHECK(tag1 == tag2);
    BOOST_CHECK( ! (tag1 == tag3) );
}

BOOST_AUTO_TEST_CASE(Difference)
{
    dcmtkpp::Tag const tag1(0xdead, 0xbeef);
    dcmtkpp::Tag const tag2(0xdead, 0xbeef);
    dcmtkpp::Tag const tag3(0xbeef, 0xf00d);

    BOOST_CHECK( ! (tag1 != tag2) );
    BOOST_CHECK(tag1 != tag3);
}

BOOST_AUTO_TEST_CASE(Inferior)
{
    dcmtkpp::Tag const tag1(0xdead, 0xbeef);
    dcmtkpp::Tag const tag2(0xdead, 0xf00d);
    dcmtkpp::Tag const tag3(0xbeef, 0xf00d);

    BOOST_CHECK(tag1 < tag2);
    BOOST_CHECK(tag3 < tag1);

    BOOST_CHECK( ! (tag2 < tag1) );
    BOOST_CHECK( ! (tag1 < tag3) );
}

BOOST_AUTO_TEST_CASE(Superior)
{
    dcmtkpp::Tag const tag1(0xdead, 0xbeef);
    dcmtkpp::Tag const tag2(0xdead, 0xf00d);
    dcmtkpp::Tag const tag3(0xbeef, 0xf00d);

    BOOST_CHECK(tag2 > tag1);
    BOOST_CHECK(tag1 > tag3);

    BOOST_CHECK( ! (tag1 > tag2) );
    BOOST_CHECK( ! (tag3 > tag1) );
}

BOOST_AUTO_TEST_CASE(InferiorOrEqual)
{
    dcmtkpp::Tag const tag1(0xdead, 0xbeef);
    dcmtkpp::Tag const tag2(0xdead, 0xf00d);
    dcmtkpp::Tag const tag3(0xbeef, 0xf00d);
    dcmtkpp::Tag const tag4(0xdead, 0xbeef);

    BOOST_CHECK(tag1 <= tag2);
    BOOST_CHECK(tag3 <= tag1);
    BOOST_CHECK(tag1 <= tag4);

    BOOST_CHECK( ! (tag2 <= tag1) );
    BOOST_CHECK( ! (tag1 <= tag3) );
}

BOOST_AUTO_TEST_CASE(SuperiorOrEqual)
{
    dcmtkpp::Tag const tag1(0xdead, 0xbeef);
    dcmtkpp::Tag const tag2(0xdead, 0xf00d);
    dcmtkpp::Tag const tag3(0xbeef, 0xf00d);
    dcmtkpp::Tag const tag4(0xdead, 0xbeef);

    BOOST_CHECK(tag2 >= tag1);
    BOOST_CHECK(tag1 >= tag3);
    BOOST_CHECK(tag1 >= tag4);

    BOOST_CHECK( ! (tag1 >= tag2) );
    BOOST_CHECK( ! (tag3 >= tag1) );
}

BOOST_AUTO_TEST_CASE(StreamInsertion)
{
    dcmtkpp::Tag const tag(0xdead, 0xbeef);
    std::ostringstream stream;
    stream << tag;
    BOOST_CHECK_EQUAL(stream.str(), "deadbeef");
}

BOOST_AUTO_TEST_CASE(StringConversion)
{
    dcmtkpp::Tag const tag(0xdead, 0xbeef);
    BOOST_CHECK_EQUAL(std::string(tag), "deadbeef");
}
