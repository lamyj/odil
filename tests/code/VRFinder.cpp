#define BOOST_TEST_MODULE VRFinder
#include <boost/test/unit_test.hpp>

#include <string>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Tag.h"
#include "dcmtkpp/VR.h"
#include "dcmtkpp/VRFinder.h"

dcmtkpp::VR
user_defined_finder(
    dcmtkpp::Tag const & tag, dcmtkpp::DataSet const &, std::string const &,
    bool & called)
{
    if(tag == dcmtkpp::Tag(0xeeee, 0xeeee))
    {
        called = true;
        return dcmtkpp::VR::UR;
    }
    else
    {
        throw dcmtkpp::Exception("Not applicable");
    }
}

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::VRFinder finder;
    BOOST_REQUIRE_EQUAL(finder.finders.empty(), true);
}

BOOST_AUTO_TEST_CASE(PublicDictionary)
{
    auto const vr = dcmtkpp::VRFinder::public_dictionary(
        dcmtkpp::Tag(0x0010, 0x0010), dcmtkpp::DataSet(),
        dcmtkpp::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == dcmtkpp::VR::PN);
}

BOOST_AUTO_TEST_CASE(PublicDictionaryNotApplicable)
{
    BOOST_REQUIRE_THROW(
        dcmtkpp::VRFinder::public_dictionary(
            dcmtkpp::Tag(0x0011, 0x0011), dcmtkpp::DataSet(),
            dcmtkpp::registry::ImplicitVRLittleEndian),
        dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(GroupLength)
{
    auto const vr = dcmtkpp::VRFinder::group_length(
        dcmtkpp::Tag(0x0010, 0x0000), dcmtkpp::DataSet(),
        dcmtkpp::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == dcmtkpp::VR::UL);
}

BOOST_AUTO_TEST_CASE(GroupLengthNotApplicable)
{
    BOOST_REQUIRE_THROW(
        dcmtkpp::VRFinder::group_length(
            dcmtkpp::Tag(0x0010, 0x0010), dcmtkpp::DataSet(),
            dcmtkpp::registry::ImplicitVRLittleEndian),
        dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(PrivateTag)
{
    auto const vr = dcmtkpp::VRFinder::private_tag(
        dcmtkpp::Tag(0x0011, 0x0011), dcmtkpp::DataSet(),
        dcmtkpp::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == dcmtkpp::VR::UN);
}

BOOST_AUTO_TEST_CASE(PrivateTagNotApplicable)
{
    BOOST_REQUIRE_THROW(
        dcmtkpp::VRFinder::private_tag(
            dcmtkpp::Tag(0x0010, 0x0010), dcmtkpp::DataSet(),
            dcmtkpp::registry::ImplicitVRLittleEndian),
        dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ImplictiVRLittleEndian)
{
    auto const vr = dcmtkpp::VRFinder::implicit_vr_little_endian(
        dcmtkpp::Tag(0x7fe0, 0x0010), dcmtkpp::DataSet(),
        dcmtkpp::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == dcmtkpp::VR::OW);
}

BOOST_AUTO_TEST_CASE(ImplictiVRLittleEndianNotApplicableTag)
{
    BOOST_REQUIRE_THROW(
        dcmtkpp::VRFinder::implicit_vr_little_endian(
            dcmtkpp::Tag(0x0010, 0x0010), dcmtkpp::DataSet(),
            dcmtkpp::registry::ImplicitVRLittleEndian),
        dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ImplictiVRLittleEndianNotApplicableVR)
{
    BOOST_REQUIRE_THROW(
        dcmtkpp::VRFinder::implicit_vr_little_endian(
            dcmtkpp::Tag(0x7fe0, 0x0010), dcmtkpp::DataSet(),
            dcmtkpp::registry::ExplicitVRLittleEndian),
        dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(PublicElement)
{
    dcmtkpp::VRFinder finder;
    auto const vr = finder(
        dcmtkpp::Tag(0x0010, 0x0010), dcmtkpp::DataSet(),
        dcmtkpp::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == dcmtkpp::VR::PN);
}

BOOST_AUTO_TEST_CASE(GroupLengthElement)
{
    dcmtkpp::VRFinder finder;
    auto const vr = finder(
        dcmtkpp::Tag(0x0010, 0x0000), dcmtkpp::DataSet(),
        dcmtkpp::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == dcmtkpp::VR::UL);
}

BOOST_AUTO_TEST_CASE(PrivateElement)
{
    dcmtkpp::VRFinder finder;
    auto const vr = finder(
        dcmtkpp::Tag(0x0011, 0x0011), dcmtkpp::DataSet(),
        dcmtkpp::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == dcmtkpp::VR::UN);
}

BOOST_AUTO_TEST_CASE(TSDependentElement)
{
    dcmtkpp::VRFinder finder;
    auto const vr = finder(
        dcmtkpp::Tag(0x7fe0, 0x0010), dcmtkpp::DataSet(),
        dcmtkpp::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == dcmtkpp::VR::OW);
}

BOOST_AUTO_TEST_CASE(UserFinder)
{
    bool called = false;
    auto const my_finder_function =
        [&called]
        (
            dcmtkpp::Tag const & tag, dcmtkpp::DataSet const & data_set,
            std::string const & ts
        )
        {
            return user_defined_finder(tag, data_set, ts, called);
        };
    dcmtkpp::VRFinder finder;
    finder.finders.push_back(my_finder_function);
    finder(
        dcmtkpp::Tag(0xeeee, 0xeeee), dcmtkpp::DataSet(),
        dcmtkpp::registry::ImplicitVRLittleEndian
    );
    BOOST_REQUIRE_EQUAL(called, true);
}

BOOST_AUTO_TEST_CASE(NoVRFound)
{
    dcmtkpp::VRFinder finder;
    BOOST_REQUIRE_THROW(
        finder(
            dcmtkpp::Tag(0xcccc, 0xcccc), dcmtkpp::DataSet(),
            dcmtkpp::registry::ImplicitVRLittleEndian
        ), dcmtkpp::Exception);
}
