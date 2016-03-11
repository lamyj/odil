#define BOOST_TEST_MODULE registry
#include <boost/test/unit_test.hpp>

#include "odil/registry.h"
#include "odil/Tag.h"

BOOST_AUTO_TEST_CASE(PublicDictionary)
{
    auto const iterator = odil::registry::public_dictionary.find(
        odil::registry::PatientName);
    BOOST_REQUIRE(iterator != odil::registry::public_dictionary.end());
    auto const & entry = iterator->second;
    BOOST_REQUIRE_EQUAL(entry.name, "Patient's Name");
    BOOST_REQUIRE_EQUAL(entry.keyword, "PatientName");
    BOOST_REQUIRE_EQUAL(entry.vr, "PN");
    BOOST_REQUIRE_EQUAL(entry.vm, "1");
}

BOOST_AUTO_TEST_CASE(PublicDictionaryRepeatingGroup)
{
    auto const iterator = odil::registry::public_dictionary.find(
        std::string("60xx0010"));
    BOOST_REQUIRE(iterator != odil::registry::public_dictionary.end());
    auto const & entry = iterator->second;
    BOOST_REQUIRE_EQUAL(entry.name, "Overlay Rows");
    BOOST_REQUIRE_EQUAL(entry.keyword, "OverlayRows");
    BOOST_REQUIRE_EQUAL(entry.vr, "US");
    BOOST_REQUIRE_EQUAL(entry.vm, "1");
}

BOOST_AUTO_TEST_CASE(UIDsDictionary)
{
    auto const iterator = odil::registry::uids_dictionary.find(
        odil::registry::MRImageStorage);
    BOOST_REQUIRE(iterator != odil::registry::uids_dictionary.end());
    auto const & entry = iterator->second;
    BOOST_REQUIRE_EQUAL(entry.name, "MR Image Storage");
    BOOST_REQUIRE_EQUAL(entry.keyword, "MRImageStorage");
    BOOST_REQUIRE_EQUAL(entry.type, "SOP Class");
}
