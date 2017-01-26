#define BOOST_TEST_MODULE BasicDirectoryCreator
#include <boost/test/unit_test.hpp>

#include <fstream>

#include "odil/BasicDirectoryCreator.h"
#include "odil/json_converter.h"
#include "odil/Reader.h"
#include "odil/registry.h"
#include "odil/Writer.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    odil::BasicDirectoryCreator const creator;
    BOOST_REQUIRE_EQUAL(creator.root.empty(), true);
    BOOST_REQUIRE_EQUAL(creator.files.empty(), true);
    BOOST_REQUIRE_EQUAL(creator.extra_record_keys.empty(), true);
    BOOST_REQUIRE(
        creator.item_encoding == odil::Writer::ItemEncoding::ExplicitLength);
}

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::BasicDirectoryCreator::RecordKeyMap const extra_records(
        {
            {
                "PATIENT",
                {
                    {odil::registry::PatientBirthDate, 1},
                    {odil::registry::OtherPatientIDs, 3},
                }
            }
        });

    odil::BasicDirectoryCreator const creator(
        "root", {"a.dcm", "b.dcm"}, extra_records,
        odil::Writer::ItemEncoding::UndefinedLength);
    BOOST_REQUIRE_EQUAL(creator.root, "root");
    BOOST_REQUIRE(
        creator.files == std::vector<std::string>({"a.dcm", "b.dcm"}));
    BOOST_REQUIRE(
        creator.extra_record_keys == extra_records);
    BOOST_REQUIRE(
        creator.item_encoding == odil::Writer::ItemEncoding::UndefinedLength);
}

BOOST_AUTO_TEST_CASE(BasicDirectory)
{
    {
        odil::DataSet data_set;
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
        data_set.add("SOPClassUID", {odil::registry::RawDataStorage});

        std::ofstream stream(
            "a.dcm", std::ofstream::out | std::ofstream::binary);
        odil::Writer::write_file(data_set, stream);
    }

    {
        odil::DataSet data_set;
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
        data_set.add("SOPClassUID", {odil::registry::RawDataStorage});

        std::ofstream stream(
            "b.dcm", std::ofstream::out | std::ofstream::binary);
        odil::Writer::write_file(data_set, stream);
    }

    odil::BasicDirectoryCreator::RecordKeyMap const extra_records(
        { { "SERIES", { {odil::registry::SeriesDescription, 1} } } });

    odil::BasicDirectoryCreator const creator(
        ".", {"a.dcm", "b.dcm"}, extra_records);
    creator();

    boost::filesystem::ifstream stream(
        boost::filesystem::path(".")/"DICOMDIR",
        boost::filesystem::ifstream::in | boost::filesystem::ifstream::binary);
    auto const dicomdir_and_header = odil::Reader::read_file(stream);
    stream.close();

    BOOST_REQUIRE(
        dicomdir_and_header.first.as_string("MediaStorageSOPClassUID") ==
            odil::Value::Strings({odil::registry::MediaStorageDirectoryStorage}));
    BOOST_REQUIRE(
        dicomdir_and_header.first.as_string("TransferSyntaxUID") ==
            odil::Value::Strings({odil::registry::ExplicitVRLittleEndian}));

    auto const & records =
        dicomdir_and_header.second.as_data_set("DirectoryRecordSequence");
    BOOST_REQUIRE_EQUAL(records.size(), 5);

    BOOST_REQUIRE(
        records[0].as_string("DirectoryRecordType") ==
            odil::Value::Strings({"PATIENT"}));
    BOOST_REQUIRE(
        records[0].as_string("PatientID") ==
            odil::Value::Strings({"DJ123"}));

    BOOST_REQUIRE(
        records[1].as_string("DirectoryRecordType") ==
            odil::Value::Strings({"STUDY"}));
    BOOST_REQUIRE(
        records[1].as_string("StudyInstanceUID") ==
            odil::Value::Strings({"1.2.3.4"}));
    BOOST_REQUIRE(
        records[1].as_string("StudyDescription") ==
            odil::Value::Strings({"Study"}));

    BOOST_REQUIRE(
        records[2].as_string("DirectoryRecordType") ==
            odil::Value::Strings({"SERIES"}));
    BOOST_REQUIRE(
        records[2].as_string("SeriesInstanceUID") ==
            odil::Value::Strings({"1.2.3.4.1"}));
    BOOST_REQUIRE(
        records[2].as_string("SeriesDescription") ==
            odil::Value::Strings({"Series"}));

    BOOST_REQUIRE(
        records[3].as_string("DirectoryRecordType") ==
            odil::Value::Strings({"IMAGE"}));
    BOOST_REQUIRE(
        records[3].as_int("InstanceNumber") ==
            odil::Value::Integers({1}));

    BOOST_REQUIRE(
        records[4].as_string("DirectoryRecordType") ==
            odil::Value::Strings({"IMAGE"}));
    BOOST_REQUIRE(
        records[4].as_int("InstanceNumber") ==
            odil::Value::Integers({2}));

    boost::filesystem::remove("a.dcm");
    boost::filesystem::remove("b.dcm");
    boost::filesystem::remove("DICOMDIR");
}
