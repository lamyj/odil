#define BOOST_TEST_MODULE registry
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/registry.h"
#include "dcmtkpp/Tag.h"

BOOST_AUTO_TEST_CASE(PublicDictionary)
{
    auto const iterator = dcmtkpp::registry::public_dictionary.find(
        dcmtkpp::registry::PatientName);
    BOOST_REQUIRE(iterator != dcmtkpp::registry::public_dictionary.end());
    auto const & entry = iterator->second;
    BOOST_REQUIRE_EQUAL(entry.name, "Patient's Name");
    BOOST_REQUIRE_EQUAL(entry.keyword, "PatientName");
    BOOST_REQUIRE_EQUAL(entry.vr, "PN");
    BOOST_REQUIRE_EQUAL(entry.vm, "1");
}

BOOST_AUTO_TEST_CASE(UIDsDictionary)
{
    auto const iterator = dcmtkpp::registry::uids_dictionary.find(
        dcmtkpp::registry::MRImageStorage);
    BOOST_REQUIRE(iterator != dcmtkpp::registry::uids_dictionary.end());
    auto const & entry = iterator->second;
    BOOST_REQUIRE_EQUAL(entry.name, "MR Image Storage");
    BOOST_REQUIRE_EQUAL(entry.keyword, "MRImageStorage");
    BOOST_REQUIRE_EQUAL(entry.type, "SOP Class");
}
