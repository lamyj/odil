#define BOOST_TEST_MODULE BasicDirectoryCreator
#include <boost/test/unit_test.hpp>

#include <fstream>

#include "dcmtkpp/BasicDirectoryCreator.h"
#include "dcmtkpp/json_converter.h"
#include "dcmtkpp/Reader.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Writer.h"

#include <boost/filesystem.hpp>
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

BOOST_AUTO_TEST_CASE(BasicDirectory)
{
    std::stringstream stream1;
    stream1 <<  "{";

    {
        dcmtkpp::DataSet data_set;
        data_set.add("PatientID", {"DJ123"});
        data_set.add("StudyDate", {"19100110"});
        data_set.add("StudyTime", {"1234"});
        data_set.add("StudyDescription", {"Study"});
        data_set.add("StudyInstanceUID", {"1.2.3.4"});
        data_set.add("StudyID", {"FOO"});
        data_set.add("Modality", {"OT"});
        data_set.add("SeriesInstanceUID", {"1.2.3.4.1"});
        data_set.add("SeriesNumber", {1});
        data_set.add("SeriesDescription", {"Series"});
        data_set.add("InstanceNumber", {1});
        data_set.add("SOPInstanceUID", {"1.2.3.4.1.1"});
        data_set.add("SOPClassUID", {dcmtkpp::registry::RawDataStorage});

        std::ofstream stream("a.dcm");
        dcmtkpp::Writer::write_file(data_set, stream);
    }

    {
        dcmtkpp::DataSet data_set;
        data_set.add("PatientID", {"DJ123"});
        data_set.add("StudyDate", {"19100110"});
        data_set.add("StudyTime", {"1234"});
        data_set.add("StudyDescription", {"Study"});
        data_set.add("StudyInstanceUID", {"1.2.3.4"});
        data_set.add("StudyID", {"FOO"});
        data_set.add("Modality", {"OT"});
        data_set.add("SeriesInstanceUID", {"1.2.3.4.1"});
        data_set.add("SeriesNumber", {1});
        data_set.add("SeriesDescription", {"Series"});
        data_set.add("InstanceNumber", {2});
        data_set.add("SOPInstanceUID", {"1.2.3.4.1.2"});
        data_set.add("SOPClassUID", {dcmtkpp::registry::RawDataStorage});

        std::ofstream stream("b.dcm");
        dcmtkpp::Writer::write_file(data_set, stream);
    }

    dcmtkpp::BasicDirectoryCreator::RecordKeyMap const extra_records(
        { { "SERIES", { {dcmtkpp::registry::SeriesDescription, 1} } } });

    dcmtkpp::BasicDirectoryCreator const creator(
        ".", {"a.dcm", "b.dcm"}, extra_records);
    creator();

    boost::filesystem::ifstream stream(boost::filesystem::path(".")/"DICOMDIR");
    auto const dicomdir_and_header = dcmtkpp::Reader::read_file(stream);

    BOOST_REQUIRE(
        dicomdir_and_header.first.as_string("MediaStorageSOPClassUID") ==
            dcmtkpp::Value::Strings({dcmtkpp::registry::MediaStorageDirectoryStorage}));
    BOOST_REQUIRE(
        dicomdir_and_header.first.as_string("TransferSyntaxUID") ==
            dcmtkpp::Value::Strings({dcmtkpp::registry::ExplicitVRLittleEndian}));

    auto const & records =
        dicomdir_and_header.second.as_data_set("DirectoryRecordSequence");
    BOOST_REQUIRE_EQUAL(records.size(), 5);

    BOOST_REQUIRE(
        records[0].as_string("DirectoryRecordType") ==
            dcmtkpp::Value::Strings({"PATIENT"}));
    BOOST_REQUIRE(
        records[0].as_string("PatientID") ==
            dcmtkpp::Value::Strings({"DJ123"}));

    BOOST_REQUIRE(
        records[1].as_string("DirectoryRecordType") ==
            dcmtkpp::Value::Strings({"STUDY"}));
    BOOST_REQUIRE(
        records[1].as_string("StudyInstanceUID") ==
            dcmtkpp::Value::Strings({"1.2.3.4"}));
    BOOST_REQUIRE(
        records[1].as_string("StudyDescription") ==
            dcmtkpp::Value::Strings({"Study"}));

    BOOST_REQUIRE(
        records[2].as_string("DirectoryRecordType") ==
            dcmtkpp::Value::Strings({"SERIES"}));
    BOOST_REQUIRE(
        records[2].as_string("SeriesInstanceUID") ==
            dcmtkpp::Value::Strings({"1.2.3.4.1"}));
    BOOST_REQUIRE(
        records[2].as_string("SeriesDescription") ==
            dcmtkpp::Value::Strings({"Series"}));

    BOOST_REQUIRE(
        records[3].as_string("DirectoryRecordType") ==
            dcmtkpp::Value::Strings({"IMAGE"}));
    BOOST_REQUIRE(
        records[3].as_int("InstanceNumber") ==
            dcmtkpp::Value::Integers({1}));

    BOOST_REQUIRE(
        records[4].as_string("DirectoryRecordType") ==
            dcmtkpp::Value::Strings({"IMAGE"}));
    BOOST_REQUIRE(
        records[4].as_int("InstanceNumber") ==
            dcmtkpp::Value::Integers({2}));

    boost::filesystem::remove("a.dcm");
    boost::filesystem::remove("b.dcm");
}
