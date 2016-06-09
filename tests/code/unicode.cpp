#define BOOST_TEST_MODULE unicode
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/unicode.h"

BOOST_AUTO_TEST_CASE(SCSARAB)
{
    odil::Value::Strings const specific_character_set = { "ISO_IR 127" };
    std::string const source =
        "\xe2\xc8\xc7\xe6\xea" "^" "\xe4\xe6\xd2\xc7\xd1";
    std::string const expected =
        "\xd9\x82\xd8\xa8\xd8\xa7\xd9\x86\xd9\x8a"
        "^"
        "\xd9\x84\xd9\x86\xd8\xb2\xd8\xa7\xd8\xb1";

    std::string const utf8 = odil::as_utf8(
        source, specific_character_set, true);
    BOOST_REQUIRE_EQUAL(utf8, expected);
}

BOOST_AUTO_TEST_CASE(SCSFREN)
{
    odil::Value::Strings const specific_character_set = { "ISO_IR 100" };
    std::string const source = "Buc" "^" "J\xe9r\xf4me";
    std::string const expected =
        "Buc" "^" "J\xc3\xa9r\xc3\xb4me";

    std::string const utf8 = odil::as_utf8(
        source, specific_character_set, true);
    BOOST_REQUIRE_EQUAL(utf8, expected);
}

BOOST_AUTO_TEST_CASE(SCSGERM)
{
    odil::Value::Strings const specific_character_set = { "ISO_IR 100" };
    std::string const source =
        "\xc4neas" "^" "R\xfc" "diger";
    std::string const expected =
        "\xc3\x84neas" "^" "R\xc3\xbc" "diger";

    std::string const utf8 = odil::as_utf8(
        source, specific_character_set, true);
    BOOST_REQUIRE_EQUAL(utf8, expected);
}

BOOST_AUTO_TEST_CASE(SCSGREEK)
{
    odil::Value::Strings const specific_character_set = { "ISO_IR 126" };
    std::string const source = "\xc4\xe9\xef\xed\xf5\xf3\xe9\xef\xf2";
    std::string const expected =
        "\xce\x94\xce\xb9\xce\xbf\xce\xbd\xcf\x85\xcf\x83\xce\xb9\xce\xbf\xcf\x82";

    std::string const utf8 = odil::as_utf8(
        source, specific_character_set, true);
    BOOST_REQUIRE_EQUAL(utf8, expected);
}

BOOST_AUTO_TEST_CASE(SCSH31)
{
    odil::Value::Strings const specific_character_set =
        { "", "ISO 2022 IR 87" };
    std::string const source =
        "Yamada" "^" "Tarou"
        "="
        "\x1b\x24\x42\x3b\x33\x45\x44\x1b\x28\x42"
            "^" "\x1b\x24\x42\x42\x40\x4f\x3a\x1b\x28\x42"
        "="
        "\x1b\x24\x42\x24\x64\x24\x5e\x24\x40\x1b\x28\x42"
            "^" "\x1b\x24\x42\x24\x3f\x24\x6d\x24\x26\x1b\x28\x42";
    std::string const expected =
        "Yamada" "^" "Tarou"
        "="
        "\xe5\xb1\xb1\xe7\x94\xb0" "^" "\xe5\xa4\xaa\xe9\x83\x8e"
        "="
        "\xe3\x82\x84\xe3\x81\xbe\xe3\x81\xa0"
            "^" "\xe3\x81\x9f\xe3\x82\x8d\xe3\x81\x86";

    std::string const utf8 = odil::as_utf8(
        source, specific_character_set, true);
    BOOST_REQUIRE_EQUAL(utf8, expected);
}

BOOST_AUTO_TEST_CASE(SCSH32)
{
    odil::Value::Strings const specific_character_set =
        { "ISO 2022 IR 13", "ISO 2022 IR 87" };
    std::string const source =
        "\xd4\xcf\xc0\xde" "^" "\xc0\xdb\xb3"
        "="
        "\x1b\x24\x42\x3b\x33\x45\x44\x1b\x28\x4a"
            "^" "\x1b\x24\x42\x42\x40\x4f\x3a\x1b\x28\x4a"
        "="
        "\x1b\x24\x42\x24\x64\x24\x5e\x24\x40\x1b\x28\x4a"
            "\x5e\x1b\x24\x42\x24\x3f\x24\x6d\x24\x26\x1b\x28\x4a";
    std::string const expected =
        "\xef\xbe\x94\xef\xbe\x8f\xef\xbe\x80\xef\xbe\x9e"
            "^" "\xef\xbe\x80\xef\xbe\x9b\xef\xbd\xb3"
        "="
        "\xe5\xb1\xb1\xe7\x94\xb0"
            "^" "\xe5\xa4\xaa\xe9\x83\x8e"
        "="
        "\xe3\x82\x84\xe3\x81\xbe\xe3\x81\xa0"
            "^" "\xe3\x81\x9f\xe3\x82\x8d\xe3\x81\x86";

    std::string const utf8 = odil::as_utf8(
        source, specific_character_set, true);
    BOOST_REQUIRE_EQUAL(utf8, expected);
}

BOOST_AUTO_TEST_CASE(SCSHBRW)
{
    odil::Value::Strings const specific_character_set = { "ISO_IR 138" };
    std::string const source = "\xf9\xf8\xe5\xef" "^" "\xe3\xe1\xe5\xf8\xe4";
    std::string const expected =
        "\xd7\xa9\xd7\xa8\xd7\x95\xd7\x9f"
            "^" "\xd7\x93\xd7\x91\xd7\x95\xd7\xa8\xd7\x94";

    std::string const utf8 = odil::as_utf8(
        source, specific_character_set, true);
    BOOST_REQUIRE_EQUAL(utf8, expected);
}

BOOST_AUTO_TEST_CASE(SCSI2)
{
    odil::Value::Strings const specific_character_set =
        { "", "ISO 2022 IR 149" };

    std::string const source =
        "\x48\x6f\x6e\x67" "^" "\x47\x69\x6c\x64\x6f\x6e\x67"
        "="
        "\x1b\x24\x29\x43\xfb\xf3" "^" "\x1b\x24\x29\x43\xd1\xce\xd4\xd7"
        "="
        "\x1b\x24\x29\x43\xc8\xab" "^" "\x1b\x24\x29\x43\xb1\xe6\xb5\xbf";
    std::string const expected =
        "\x48\x6f\x6e\x67" "^" "\x47\x69\x6c\x64\x6f\x6e\x67"
        "="
        "\xe6\xb4\xaa" "^" "\xe5\x90\x89\xe6\xb4\x9e"
        "="
        "\xed\x99\x8d" "^" "\xea\xb8\xb8\xeb\x8f\x99";

    std::string const utf8 = odil::as_utf8(
        source, specific_character_set, true);
    BOOST_REQUIRE_EQUAL(utf8, expected);
}

BOOST_AUTO_TEST_CASE(SCSRUSS)
{
    odil::Value::Strings const specific_character_set = { "ISO_IR 144" };
    std::string const source = "\xbb\xee\xda\x63\x65\xdc\xd1\x79\x70\xd3";
    std::string const expected =
        "\xd0\x9b\xd1\x8e\xd0\xba\x63\x65\xd0\xbc\xd0\xb1\x79\x70\xd0\xb3";

    std::string const utf8 = odil::as_utf8(
        source, specific_character_set, true);
    BOOST_REQUIRE_EQUAL(utf8, expected);
}

BOOST_AUTO_TEST_CASE(SCSX1)
{
    odil::Value::Strings const specific_character_set = { "ISO_IR 192" };
    std::string const source =
        "Wang" "^" "XiaoDong"
        "="
        "\xe7\x8e\x8b" "^" "\xe5\xb0\x8f\xe6\x9d\xb1"
        "=";
    std::string const expected =
        "Wang" "^" "XiaoDong"
        "\x3d\xe7\x8e\x8b" "^" "\xe5\xb0\x8f\xe6\x9d\xb1"
        "=";

    std::string const utf8 = odil::as_utf8(
        source, specific_character_set, true);
    BOOST_REQUIRE_EQUAL(utf8, expected);
}

BOOST_AUTO_TEST_CASE(SCSX2)
{
    odil::Value::Strings const specific_character_set = { "GB18030" };
    std::string const source =
        "Wang" "^" "XiaoDong"
        "=" ""
        "\xcd\xf5" "^" "\xd0\xa1\xb6\xab"
        "=";
    std::string const expected =
        "Wang" "^" "XiaoDong"
        "="
        "\xe7\x8e\x8b" "^" "\xe5\xb0\x8f\xe4\xb8\x9c"
        "=";

    std::string const utf8 = odil::as_utf8(
        source, specific_character_set, true);
    BOOST_REQUIRE_EQUAL(utf8, expected);
}
