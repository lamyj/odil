#define BOOST_TEST_MODULE RoleSelection
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "odil/pdu/RoleSelection.h"

#include <iostream>

std::string const data(
    "\x54\x00\x00\x0b"
    "\x00\x07" "1.2.3.4"
    "\x01\x01",
    15
);

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    odil::pdu::RoleSelection const item;
    BOOST_REQUIRE_EQUAL(item.get_sop_class_uid(), "");
    BOOST_REQUIRE_EQUAL(item.get_scu_role_support(), false);
    BOOST_REQUIRE_EQUAL(item.get_scp_role_support(), false);
}

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::pdu::RoleSelection const item("1.2.3.4", true, true);
    BOOST_REQUIRE_EQUAL(item.get_sop_class_uid(), "1.2.3.4");
    BOOST_REQUIRE_EQUAL(item.get_scu_role_support(), true);
    BOOST_REQUIRE_EQUAL(item.get_scp_role_support(), true);
}

BOOST_AUTO_TEST_CASE(FromStream)
{
    std::istringstream stream(data);
    odil::pdu::RoleSelection const item(stream);

    BOOST_REQUIRE_EQUAL(item.get_sop_class_uid(), "1.2.3.4");
    BOOST_REQUIRE_EQUAL(item.get_scu_role_support(), true);
    BOOST_REQUIRE_EQUAL(item.get_scp_role_support(), true);
}

BOOST_AUTO_TEST_CASE(SOPClassUID)
{
    odil::pdu::RoleSelection item;
    item.set_sop_class_uid("1.2.3.4");
    BOOST_REQUIRE_EQUAL(item.get_sop_class_uid(), "1.2.3.4");
}

BOOST_AUTO_TEST_CASE(SCURoleSupport)
{
    odil::pdu::RoleSelection item;
    item.set_scu_role_support(true);
    BOOST_REQUIRE_EQUAL(item.get_scu_role_support(), true);
}

BOOST_AUTO_TEST_CASE(SCPRoleSupport)
{
    odil::pdu::RoleSelection item;
    item.set_scp_role_support(true);
    BOOST_REQUIRE_EQUAL(item.get_scp_role_support(), true);
}


BOOST_AUTO_TEST_CASE(Write)
{
    odil::pdu::RoleSelection item("1.2.3.4", true, true);

    std::ostringstream stream;
    stream << item;

    BOOST_REQUIRE_EQUAL(stream.str(), data);
}
