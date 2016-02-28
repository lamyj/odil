#define BOOST_TEST_MODULE Base64
#include <boost/test/unit_test.hpp>

#include <iterator>
#include <string>

#include "odil/base64.h"

void test_encode(std::string const & data, std::string const & expected)
{
    std::string encoded;
    encoded.reserve(data.size()*4/3);

    odil::base64::encode(
        data.begin(), data.end(), std::back_inserter(encoded));

    BOOST_REQUIRE_EQUAL(encoded, expected);
}

void test_decode(std::string const & data, std::string const & expected)
{
    std::string decoded;
    decoded.reserve(data.size()*3/4);

    odil::base64::decode(
        data.begin(), data.end(), std::back_inserter(decoded));

    BOOST_REQUIRE_EQUAL(decoded, expected);
}

BOOST_AUTO_TEST_CASE(EncodeEmpty)
{
    test_encode("", "");
}

BOOST_AUTO_TEST_CASE(Encode1)
{
    test_encode(
        "Lorem ipsum dolor sit amet.", "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQu");
}

BOOST_AUTO_TEST_CASE(Encode2)
{
    test_encode(
        "Lorem ipsum dolor sit amet", "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQ=");
}

BOOST_AUTO_TEST_CASE(Encode3)
{
    test_encode(
        "Lorem ipsum dolor sit ame", "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZQ==");
}

BOOST_AUTO_TEST_CASE(DecodeEmpty)
{
    test_decode("", "");
}

BOOST_AUTO_TEST_CASE(Decode1)
{
    test_decode(
        "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQu", "Lorem ipsum dolor sit amet.");
}

BOOST_AUTO_TEST_CASE(Decode2)
{
    test_decode(
        "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQ=", "Lorem ipsum dolor sit amet");
}

BOOST_AUTO_TEST_CASE(Decode3)
{
    test_decode(
        "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZQ==", "Lorem ipsum dolor sit ame");
}

BOOST_AUTO_TEST_CASE(AllStates)
{
    uint8_t data[3];
    uint8_t encoded[4];
    uint8_t decoded[3];

    for(int z=0; z<256; ++z)
    {
        for(int y=0; y<256; ++y)
        {
            for(int x=0; x<256; ++x)
            {
                data[0] = x;
                data[1] = y;
                data[2] = z;

                odil::base64::encode(data, data+3, encoded);
                odil::base64::decode(encoded, encoded+4, decoded);

                BOOST_REQUIRE(std::equal(data, data+3, decoded));
            }
        }
    }
}
