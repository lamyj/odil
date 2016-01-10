#define BOOST_TEST_MODULE Tag
#include <boost/test/unit_test.hpp>

#include "odil/Exception.h"
#include "odil/Tag.h"

BOOST_AUTO_TEST_CASE(TwoArgumentsConstructor)
{
    odil::Tag const tag(0xdead, 0xbeef);
    BOOST_CHECK_EQUAL(tag.group, 0xdead);
    BOOST_CHECK_EQUAL(tag.element, 0xbeef);
}

BOOST_AUTO_TEST_CASE(OneArgumentConstructor)
{
    odil::Tag const tag(0xdeadbeef);
    BOOST_CHECK_EQUAL(tag.group, 0xdead);
    BOOST_CHECK_EQUAL(tag.element, 0xbeef);
}

BOOST_AUTO_TEST_CASE(StringConstructor)
{
    odil::Tag const tag(std::string("PixelData"));
    BOOST_CHECK_EQUAL(tag.group, 0x7fe0);
    BOOST_CHECK_EQUAL(tag.element, 0x0010);
}

BOOST_AUTO_TEST_CASE(CharConstructor)
{
    odil::Tag const tag("PixelData");
    BOOST_CHECK_EQUAL(tag.group, 0x7fe0);
    BOOST_CHECK_EQUAL(tag.element, 0x0010);
}

BOOST_AUTO_TEST_CASE(StringConstructorNumeric)
{
    odil::Tag const tag(std::string("7fe00010"));
    BOOST_CHECK_EQUAL(tag.group, 0x7fe0);
    BOOST_CHECK_EQUAL(tag.element, 0x0010);
}

BOOST_AUTO_TEST_CASE(CharConstructorNumeric)
{
    odil::Tag const tag("7fe00010");
    BOOST_CHECK_EQUAL(tag.group, 0x7fe0);
    BOOST_CHECK_EQUAL(tag.element, 0x0010);
}

BOOST_AUTO_TEST_CASE(StringConstructorWrong)
{
    BOOST_CHECK_THROW(odil::Tag(std::string("Foobar")), odil::Exception);
}

BOOST_AUTO_TEST_CASE(CharConstructorWrong)
{
    BOOST_CHECK_THROW(odil::Tag("Foobar"), odil::Exception);
}

BOOST_AUTO_TEST_CASE(StringConstructorNumericWrong)
{
    BOOST_CHECK_THROW(odil::Tag(std::string("XXXXYYYY")), odil::Exception);
}

BOOST_AUTO_TEST_CASE(CharConstructorNumericWrong)
{
    BOOST_CHECK_THROW(odil::Tag("XXXXYYYY"), odil::Exception);
}

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
    odil::Tag const tag(0xdead, 0xbeef);
    odil::Tag const other(tag);
    BOOST_CHECK_EQUAL(other.group, 0xdead);
    BOOST_CHECK_EQUAL(other.element, 0xbeef);
}

BOOST_AUTO_TEST_CASE(IsPrivate)
{
    odil::Tag const tag1(0xdead, 0xbeef);
    odil::Tag const tag2(0x7fe0, 0x0010);

    BOOST_CHECK(tag1.is_private());
    BOOST_CHECK(!tag2.is_private());
}

BOOST_AUTO_TEST_CASE(Name)
{
    odil::Tag const tag(0x7fe0, 0x0010);
    std::string const name = tag.get_name();
    BOOST_CHECK_EQUAL(name, "PixelData");
}

BOOST_AUTO_TEST_CASE(NameWrong)
{
    odil::Tag const tag(0xEEEE, 0xEEEE);
    BOOST_CHECK_THROW(tag.get_name(), odil::Exception);
}

BOOST_AUTO_TEST_CASE(Equality)
{
    odil::Tag const tag1(0xdead, 0xbeef);
    odil::Tag const tag2(0xdead, 0xbeef);
    odil::Tag const tag3(0xbeef, 0xf00d);

    BOOST_CHECK(tag1 == tag2);
    BOOST_CHECK( ! (tag1 == tag3) );
}

BOOST_AUTO_TEST_CASE(Difference)
{
    odil::Tag const tag1(0xdead, 0xbeef);
    odil::Tag const tag2(0xdead, 0xbeef);
    odil::Tag const tag3(0xbeef, 0xf00d);

    BOOST_CHECK( ! (tag1 != tag2) );
    BOOST_CHECK(tag1 != tag3);
}

BOOST_AUTO_TEST_CASE(Inferior)
{
    odil::Tag const tag1(0xdead, 0xbeef);
    odil::Tag const tag2(0xdead, 0xf00d);
    odil::Tag const tag3(0xbeef, 0xf00d);

    BOOST_CHECK(tag1 < tag2);
    BOOST_CHECK(tag3 < tag1);

    BOOST_CHECK( ! (tag2 < tag1) );
    BOOST_CHECK( ! (tag1 < tag3) );
}

BOOST_AUTO_TEST_CASE(Superior)
{
    odil::Tag const tag1(0xdead, 0xbeef);
    odil::Tag const tag2(0xdead, 0xf00d);
    odil::Tag const tag3(0xbeef, 0xf00d);

    BOOST_CHECK(tag2 > tag1);
    BOOST_CHECK(tag1 > tag3);

    BOOST_CHECK( ! (tag1 > tag2) );
    BOOST_CHECK( ! (tag3 > tag1) );
}

BOOST_AUTO_TEST_CASE(InferiorOrEqual)
{
    odil::Tag const tag1(0xdead, 0xbeef);
    odil::Tag const tag2(0xdead, 0xf00d);
    odil::Tag const tag3(0xbeef, 0xf00d);
    odil::Tag const tag4(0xdead, 0xbeef);

    BOOST_CHECK(tag1 <= tag2);
    BOOST_CHECK(tag3 <= tag1);
    BOOST_CHECK(tag1 <= tag4);

    BOOST_CHECK( ! (tag2 <= tag1) );
    BOOST_CHECK( ! (tag1 <= tag3) );
}

BOOST_AUTO_TEST_CASE(SuperiorOrEqual)
{
    odil::Tag const tag1(0xdead, 0xbeef);
    odil::Tag const tag2(0xdead, 0xf00d);
    odil::Tag const tag3(0xbeef, 0xf00d);
    odil::Tag const tag4(0xdead, 0xbeef);

    BOOST_CHECK(tag2 >= tag1);
    BOOST_CHECK(tag1 >= tag3);
    BOOST_CHECK(tag1 >= tag4);

    BOOST_CHECK( ! (tag1 >= tag2) );
    BOOST_CHECK( ! (tag3 >= tag1) );
}

BOOST_AUTO_TEST_CASE(StreamInsertion)
{
    odil::Tag const tag(0xdead, 0xbeef);
    std::ostringstream stream;
    stream << tag;
    BOOST_CHECK_EQUAL(stream.str(), "deadbeef");
}

BOOST_AUTO_TEST_CASE(StringConversion)
{
    odil::Tag const tag(0xdead, 0xbeef);
    BOOST_CHECK_EQUAL(std::string(tag), "deadbeef");
}
