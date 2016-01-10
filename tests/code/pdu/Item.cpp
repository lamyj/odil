#define BOOST_TEST_MODULE pdu::Item
#include <boost/test/unit_test.hpp>

#include <cstdint>

#include "odil/pdu/Item.h"
#include "odil/Exception.h"

BOOST_AUTO_TEST_CASE(FieldUInt8)
{
    odil::pdu::Item::Field const field(uint8_t(123));

    BOOST_REQUIRE(
        field.get_type() == odil::pdu::Item::Field::Type::unsigned_int_8);
    BOOST_REQUIRE_EQUAL(field.as_unsigned_int_8(), 123);
}

BOOST_AUTO_TEST_CASE(FieldUInt16)
{
    odil::pdu::Item::Field const field(uint16_t(1234));

    BOOST_REQUIRE(
        field.get_type() == odil::pdu::Item::Field::Type::unsigned_int_16);
    BOOST_REQUIRE_EQUAL(field.as_unsigned_int_16(), 1234);
}

BOOST_AUTO_TEST_CASE(FieldUInt32)
{
    odil::pdu::Item::Field const field(uint32_t(123456));

    BOOST_REQUIRE(
        field.get_type() == odil::pdu::Item::Field::Type::unsigned_int_32);
    BOOST_REQUIRE_EQUAL(field.as_unsigned_int_32(), 123456);
}

BOOST_AUTO_TEST_CASE(FieldString)
{
    odil::pdu::Item::Field const field("abcdef");

    BOOST_REQUIRE(field.get_type() == odil::pdu::Item::Field::Type::string);
    BOOST_REQUIRE_EQUAL(field.as_string(), "abcdef");
}

BOOST_AUTO_TEST_CASE(FieldItems)
{
    odil::pdu::Item const item_1({{"foo", uint8_t(123)}});
    odil::pdu::Item const item_2({{"bar", std::string("abcdef")}});
    odil::pdu::Item::Field const field(
        std::vector<odil::pdu::Item>({item_1, item_2}));

    BOOST_REQUIRE(field.get_type() == odil::pdu::Item::Field::Type::items);
    BOOST_REQUIRE_EQUAL(field.as_items().size(), 2);
}

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    odil::pdu::Item const item;
    BOOST_REQUIRE(item.empty());
    BOOST_REQUIRE_EQUAL(item.size(), 0);
}

BOOST_AUTO_TEST_CASE(FieldsConstructor)
{
    odil::pdu::Item const item({
        {std::string("foo"), uint8_t(123)},
        {std::string("bar"), std::string("abcd")}
    });
    BOOST_REQUIRE_EQUAL(item.size(), 2);
    BOOST_REQUIRE_EQUAL(item.as_unsigned_int_8("foo"), 123);
    BOOST_REQUIRE_EQUAL(item.as_string("bar"), "abcd");
}

BOOST_AUTO_TEST_CASE(UInt8)
{
    odil::pdu::Item item;
    item.add("foo", uint8_t(123));
    BOOST_REQUIRE_EQUAL(item.size(), 1);
    BOOST_REQUIRE_EQUAL(item.has_field("foo"), true);
    BOOST_REQUIRE_EQUAL(item.as_unsigned_int_8("foo"), 123);
    BOOST_REQUIRE_THROW(item.as_unsigned_int_16("foo"), odil::Exception);
}

BOOST_AUTO_TEST_CASE(UInt16)
{
    odil::pdu::Item item;
    item.add("foo", uint16_t(1234));
    BOOST_REQUIRE_EQUAL(item.size(), 1);
    BOOST_REQUIRE_EQUAL(item.as_unsigned_int_16("foo"), 1234);
    BOOST_REQUIRE_THROW(item.as_unsigned_int_32("foo"), odil::Exception);
}

BOOST_AUTO_TEST_CASE(UInt32)
{
    odil::pdu::Item item;
    item.add("foo", uint32_t(123456));
    BOOST_REQUIRE_EQUAL(item.size(), 1);
    BOOST_REQUIRE_EQUAL(item.as_unsigned_int_32("foo"), 123456);
    BOOST_REQUIRE_THROW(item.as_string("foo"), odil::Exception);
}

BOOST_AUTO_TEST_CASE(String)
{
    odil::pdu::Item item;
    item.add("foo", std::string("abcd"));
    BOOST_REQUIRE_EQUAL(item.size(), 1);
    BOOST_REQUIRE_EQUAL(item.as_string("foo"), "abcd");
    BOOST_REQUIRE_THROW(item.as_items("foo"), odil::Exception);
}

BOOST_AUTO_TEST_CASE(Items)
{
    odil::pdu::Item const sub_item(
        {{"bar", std::string("abcdef")}});
    odil::pdu::Item item;
    item.add("foo", std::vector<odil::pdu::Item>({sub_item}));
    BOOST_REQUIRE_EQUAL(item.size(), 1);
    BOOST_REQUIRE_EQUAL(item.as_items("foo").size(), 1);
    BOOST_REQUIRE_THROW(item.as_unsigned_int_8("foo"), odil::Exception);
}

BOOST_AUTO_TEST_CASE(FieldAccessor)
{
    odil::pdu::Item item;
    item.add("foo", std::string("abcd"));
    BOOST_REQUIRE_NO_THROW(item["foo"]);
    BOOST_REQUIRE_THROW(item["bar"], odil::Exception);

}
