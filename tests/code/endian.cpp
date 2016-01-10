#define BOOST_TEST_MODULE endian
#include <boost/test/unit_test.hpp>

#include <cstdint>
#include "odil/endian.h"

BOOST_AUTO_TEST_CASE(ToLittleEndian16)
{
    uint16_t const input = 0x1234;
    std::string const expected("\x34\x12");
    BOOST_REQUIRE_EQUAL(
        odil::host_to_little_endian(input),
        *reinterpret_cast<uint16_t const *>(&expected[0])
    );
}

BOOST_AUTO_TEST_CASE(ToLittleEndian32)
{
    uint32_t const input = 0x12345678;
    std::string const expected("\x78\x56\x34\x12");
    BOOST_REQUIRE_EQUAL(
        odil::host_to_little_endian(input),
        *reinterpret_cast<uint32_t const *>(&expected[0])
    );
}

BOOST_AUTO_TEST_CASE(ToBigEndian16)
{
    uint16_t const input = 0x1234;
    std::string const expected("\x12\x34");
    BOOST_REQUIRE_EQUAL(
        odil::host_to_big_endian(input),
        *reinterpret_cast<uint16_t const *>(&expected[0])
    );
}

BOOST_AUTO_TEST_CASE(ToBigEndian32)
{
    uint32_t const input = 0x12345678;
    std::string const expected("\x12\x34\x56\x78");
    BOOST_REQUIRE_EQUAL(
        odil::host_to_big_endian(input),
        *reinterpret_cast<uint32_t const *>(&expected[0])
    );
}

BOOST_AUTO_TEST_CASE(FromLittleEndian16)
{
    std::string const input("\x34\x12");
    uint16_t const expected = 0x1234;
    BOOST_REQUIRE_EQUAL(
        odil::little_endian_to_host(
            *reinterpret_cast<uint16_t const *>(&input[0])),
        expected
    );
}

BOOST_AUTO_TEST_CASE(FromLittleEndian32)
{
    std::string const input("\x78\x56\x34\x12");
    uint32_t const expected = 0x12345678;
    BOOST_REQUIRE_EQUAL(
        odil::little_endian_to_host(
            *reinterpret_cast<uint32_t const *>(&input[0])),
        expected
    );
}

BOOST_AUTO_TEST_CASE(FromBigEndian16)
{
    std::string const input("\x12\x34");
    uint16_t const expected = 0x1234;
    BOOST_REQUIRE_EQUAL(
        odil::big_endian_to_host(
            *reinterpret_cast<uint16_t const *>(&input[0])),
        expected
    );
}

BOOST_AUTO_TEST_CASE(FromBigEndian32)
{
    std::string const input("\x12\x34\x56\x78");
    uint32_t const expected = 0x12345678;
    BOOST_REQUIRE_EQUAL(
        odil::big_endian_to_host(
            *reinterpret_cast<uint32_t const *>(&input[0])),
        expected
    );
}
