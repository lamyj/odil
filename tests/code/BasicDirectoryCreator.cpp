#define BOOST_TEST_MODULE BasicDirectoryCreator
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/BasicDirectoryCreator.h"
#include "dcmtkpp/Reader.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Writer.h"

#include <boost/filesystem/fstream.hpp>

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dcmtkpp::BasicDirectoryCreator const creator;
    BOOST_REQUIRE_EQUAL(creator.root.empty(), true);
    BOOST_REQUIRE_EQUAL(creator.files.empty(), true);
    BOOST_REQUIRE_EQUAL(creator.extra_record_keys.empty(), true);
    BOOST_REQUIRE(
        creator.item_encoding == dcmtkpp::Writer::ItemEncoding::ExplicitLength);
}

BOOST_AUTO_TEST_CASE(Constructor)
{
    dcmtkpp::BasicDirectoryCreator::RecordKeyMap const extra_records(
        {
            {
                "PATIENT",
                {
                    {dcmtkpp::registry::PatientBirthDate, 1},
                    {dcmtkpp::registry::OtherPatientIDs, 3},
                }
            }
        });

    dcmtkpp::BasicDirectoryCreator const creator(
        "root", {"a.dcm", "b.dcm"}, extra_records,
        dcmtkpp::Writer::ItemEncoding::UndefinedLength);
    BOOST_REQUIRE_EQUAL(creator.root, "root");
    BOOST_REQUIRE(
        creator.files == std::vector<std::string>({"a.dcm", "b.dcm"}));
    BOOST_REQUIRE(
        creator.extra_record_keys == extra_records);
    BOOST_REQUIRE(
        creator.item_encoding == dcmtkpp::Writer::ItemEncoding::UndefinedLength);
}
