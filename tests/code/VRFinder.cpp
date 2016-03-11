#define BOOST_TEST_MODULE VRFinder
#include <boost/test/unit_test.hpp>

#include <string>

#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/registry.h"
#include "odil/Tag.h"
#include "odil/VR.h"
#include "odil/VRFinder.h"

odil::VR
user_defined_finder(
    odil::Tag const & tag, odil::DataSet const &, std::string const &,
    bool & called)
{
    if(tag == odil::Tag(0xeeee, 0xeeee))
    {
        called = true;
        return odil::VR::UR;
    }
    else
    {
        throw odil::Exception("Not applicable");
    }
}

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    odil::VRFinder finder;
    BOOST_REQUIRE_EQUAL(finder.finders.empty(), true);
}

BOOST_AUTO_TEST_CASE(PublicDictionary)
{
    auto const vr = odil::VRFinder::public_dictionary(
        odil::Tag(0x0010, 0x0010), odil::DataSet(),
        odil::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == odil::VR::PN);
}

BOOST_AUTO_TEST_CASE(PublicDictionaryRepeatingGroup)
{
    auto const vr = odil::VRFinder::public_dictionary(
        odil::Tag(0x6012, 0x0010), odil::DataSet(),
        odil::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == odil::VR::US);
}

BOOST_AUTO_TEST_CASE(PublicDictionaryNotApplicable)
{
    BOOST_REQUIRE_THROW(
        odil::VRFinder::public_dictionary(
            odil::Tag(0x0011, 0x0011), odil::DataSet(),
            odil::registry::ImplicitVRLittleEndian),
        odil::Exception);
}

BOOST_AUTO_TEST_CASE(GroupLength)
{
    auto const vr = odil::VRFinder::group_length(
        odil::Tag(0x0010, 0x0000), odil::DataSet(),
        odil::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == odil::VR::UL);
}

BOOST_AUTO_TEST_CASE(GroupLengthNotApplicable)
{
    BOOST_REQUIRE_THROW(
        odil::VRFinder::group_length(
            odil::Tag(0x0010, 0x0010), odil::DataSet(),
            odil::registry::ImplicitVRLittleEndian),
        odil::Exception);
}

BOOST_AUTO_TEST_CASE(PrivateTag)
{
    auto const vr = odil::VRFinder::private_tag(
        odil::Tag(0x0011, 0x0011), odil::DataSet(),
        odil::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == odil::VR::UN);
}

BOOST_AUTO_TEST_CASE(PrivateTagNotApplicable)
{
    BOOST_REQUIRE_THROW(
        odil::VRFinder::private_tag(
            odil::Tag(0x0010, 0x0010), odil::DataSet(),
            odil::registry::ImplicitVRLittleEndian),
        odil::Exception);
}

BOOST_AUTO_TEST_CASE(ImplictiVRLittleEndian)
{
    auto const vr = odil::VRFinder::implicit_vr_little_endian(
        odil::Tag(0x7fe0, 0x0010), odil::DataSet(),
        odil::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == odil::VR::OW);
}

BOOST_AUTO_TEST_CASE(ImplictiVRLittleEndianNotApplicableTag)
{
    BOOST_REQUIRE_THROW(
        odil::VRFinder::implicit_vr_little_endian(
            odil::Tag(0x0010, 0x0010), odil::DataSet(),
            odil::registry::ImplicitVRLittleEndian),
        odil::Exception);
}

BOOST_AUTO_TEST_CASE(ImplictiVRLittleEndianNotApplicableVR)
{
    BOOST_REQUIRE_THROW(
        odil::VRFinder::implicit_vr_little_endian(
            odil::Tag(0x7fe0, 0x0010), odil::DataSet(),
            odil::registry::ExplicitVRLittleEndian),
        odil::Exception);
}

BOOST_AUTO_TEST_CASE(PublicElement)
{
    odil::VRFinder finder;
    auto const vr = finder(
        odil::Tag(0x0010, 0x0010), odil::DataSet(),
        odil::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == odil::VR::PN);
}

BOOST_AUTO_TEST_CASE(GroupLengthElement)
{
    odil::VRFinder finder;
    auto const vr = finder(
        odil::Tag(0x0010, 0x0000), odil::DataSet(),
        odil::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == odil::VR::UL);
}

BOOST_AUTO_TEST_CASE(PrivateElement)
{
    odil::VRFinder finder;
    auto const vr = finder(
        odil::Tag(0x0011, 0x0011), odil::DataSet(),
        odil::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == odil::VR::UN);
}

BOOST_AUTO_TEST_CASE(TSDependentElement)
{
    odil::VRFinder finder;
    auto const vr = finder(
        odil::Tag(0x7fe0, 0x0010), odil::DataSet(),
        odil::registry::ImplicitVRLittleEndian);
    BOOST_REQUIRE(vr == odil::VR::OW);
}

BOOST_AUTO_TEST_CASE(UserFinder)
{
    bool called = false;
    auto const my_finder_function =
        [&called]
        (
            odil::Tag const & tag, odil::DataSet const & data_set,
            std::string const & ts
        )
        {
            return user_defined_finder(tag, data_set, ts, called);
        };
    odil::VRFinder finder;
    finder.finders.push_back(my_finder_function);
    finder(
        odil::Tag(0xeeee, 0xeeee), odil::DataSet(),
        odil::registry::ImplicitVRLittleEndian
    );
    BOOST_REQUIRE_EQUAL(called, true);
}

BOOST_AUTO_TEST_CASE(NoVRFound)
{
    odil::VRFinder finder;
    BOOST_REQUIRE_THROW(
        finder(
            odil::Tag(0xcccc, 0xcccc), odil::DataSet(),
            odil::registry::ImplicitVRLittleEndian
        ), odil::Exception);
}
