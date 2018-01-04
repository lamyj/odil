#define BOOST_TEST_MODULE UserInformation
#include <boost/test/unit_test.hpp>

#include <sstream>

#include "odil/Exception.h"
#include "odil/dul/ImplementationClassUID.h"
#include "odil/dul/ImplementationVersionName.h"
#include "odil/dul/MaximumLength.h"
#include "odil/dul/RoleSelection.h"
#include "odil/dul/UserInformation.h"
#include "odil/dul/UserIdentityAC.h"
#include "odil/dul/UserIdentityRQ.h"

BOOST_AUTO_TEST_CASE(ConstructorDefault)
{
    odil::dul::UserInformation const item;
    BOOST_REQUIRE(item.get_sub_items<odil::dul::MaximumLength>().empty());
    BOOST_REQUIRE(item.get_sub_items<odil::dul::UserIdentityRQ>().empty());
}

BOOST_AUTO_TEST_CASE(ConstructorStreamMaximumLength)
{
    std::string const data(
        "\x50\x00\x00\x08"
        "\x51\x00\x00\x04"
        "\x12\x34\x56\x78",
        12
    );
    std::istringstream stream(data);

    odil::dul::UserInformation const item(stream);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<odil::dul::MaximumLength>().size(), 1);
}

BOOST_AUTO_TEST_CASE(ConstructorStreamImplementationClassUID)
{
    std::string const data(
        "\x50\x00\x00\x07"
        "\x52\x00\x00\x03" "foo",
        11
    );
    std::istringstream stream(data);

    odil::dul::UserInformation const item(stream);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<odil::dul::ImplementationClassUID>().size(), 1);
}

BOOST_AUTO_TEST_CASE(ConstructorStreamRoleSelection)
{
    std::string const data(
        "\x50\x00\x00\x0f"
        "\x54\x00\x00\x0b"
        "\x00\x07" "1.2.3.4"
        "\x01\x01",
        19
    );
    std::istringstream stream(data);

    odil::dul::UserInformation const item(stream);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<odil::dul::RoleSelection>().size(), 1);
}

BOOST_AUTO_TEST_CASE(ConstructorStreamImplementationVersionName)
{
    std::string const data(
        "\x50\x00\x00\x07"
        "\x55\x00\x00\x03" "foo",
        11
    );
    std::istringstream stream(data);

    odil::dul::UserInformation const item(stream);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<odil::dul::ImplementationVersionName>().size(), 1);
}

BOOST_AUTO_TEST_CASE(ConstructorStreamUserIdentityRQ)
{
    std::string const data(
        "\x50\x00\x00\x10"

        "\x58\x00\x00\x0c"
        "\x02\x01"
        "\x00\x03" "foo"
        "\x00\x03" "bar",
        20
    );
    std::istringstream stream(data);

    odil::dul::UserInformation const item(stream);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<odil::dul::UserIdentityRQ>().size(), 1);

}

BOOST_AUTO_TEST_CASE(ConstructorStreamUserIdentityAC)
{
    std::string const data(
        "\x50\x00\x00\x0a"

        "\x59\x00\x00\x06"
        "\x00\x04" "abcd",
        14
    );
    std::istringstream stream(data);

    odil::dul::UserInformation const item(stream);
    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<odil::dul::UserIdentityAC>().size(), 1);
}

BOOST_AUTO_TEST_CASE(SetSubItems)
{
    odil::dul::UserInformation item;
    BOOST_REQUIRE(item.get_sub_items<odil::dul::MaximumLength>().empty());

    item.set_sub_items<odil::dul::MaximumLength>({{0x12345678}});

    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<odil::dul::MaximumLength>().size(), 1);
}

BOOST_AUTO_TEST_CASE(DeleteSubItems)
{
    odil::dul::UserInformation item;
    BOOST_REQUIRE(item.get_sub_items<odil::dul::MaximumLength>().empty());

    item.set_sub_items<odil::dul::MaximumLength>({{0x12345678}});

    BOOST_REQUIRE_EQUAL(
        item.get_sub_items<odil::dul::MaximumLength>().size(), 1);

    item.delete_sub_items<odil::dul::MaximumLength>();

    BOOST_REQUIRE(item.get_sub_items<odil::dul::MaximumLength>().empty());
}

BOOST_AUTO_TEST_CASE(Write)
{
    odil::dul::UserInformation item;
    item.set_sub_items<odil::dul::MaximumLength>({{0x12345678}});

    std::ostringstream data;
    data << item;

    std::string const expected(
        "\x50\x00\x00\x08"

        "\x51\x00\x00\x04"
        "\x12\x34\x56\x78",
        12
    );

    BOOST_REQUIRE_EQUAL(data.str(), expected);
}

