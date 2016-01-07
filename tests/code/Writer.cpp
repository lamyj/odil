#define BOOST_TEST_MODULE Writer
#include <boost/test/unit_test.hpp>

#include <sstream>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmdata/dcistrmb.h>

#include "dcmtkpp/endian.h"
#include "dcmtkpp/Element.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Writer.h"
#include "dcmtkpp/VR.h"
#include "dcmtkpp/dcmtk/conversion.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    std::ostringstream stream;
    dcmtkpp::Writer const writer(stream, dcmtkpp::ByteOrdering::BigEndian, true);
    BOOST_REQUIRE(writer.byte_ordering == dcmtkpp::ByteOrdering::BigEndian);
    BOOST_REQUIRE(writer.explicit_vr == true);
}

BOOST_AUTO_TEST_CASE(ConstructorTransferSyntax)
{
    std::ostringstream stream;
    dcmtkpp::Writer const writer(stream, dcmtkpp::registry::ExplicitVRBigEndian_Retired);
    BOOST_REQUIRE(writer.byte_ordering == dcmtkpp::ByteOrdering::BigEndian);
    BOOST_REQUIRE(writer.explicit_vr == true);
}

void do_test(
    dcmtkpp::DataSet const & dcmtkpp_data_set, std::string transfer_syntax,
    dcmtkpp::Writer::ItemEncoding item_encoding, bool use_group_length)
{
    // Write input data set
    std::stringstream stream;
    dcmtkpp::Writer const writer(
        stream, transfer_syntax, item_encoding, use_group_length);
    writer.write_data_set(dcmtkpp_data_set);

    // Store data in a DCMTK stream
    std::string const data = stream.str();
    DcmInputBufferStream dcmtk_stream;
    dcmtk_stream.setBuffer(&data[0], data.size());

    // Read output data set
    DcmDataset dcmtk_data_set;
    dcmtk_data_set.transferInit();
    OFCondition const condition = dcmtk_data_set.read(
        dcmtk_stream, DcmXfer(transfer_syntax.c_str()).getXfer());
    BOOST_REQUIRE(condition == EC_Normal || condition == EC_StreamNotifyClient);
    BOOST_REQUIRE_EQUAL(dcmtk_stream.avail(), 0);
    dcmtk_data_set.transferEnd();

    auto const other_dcmtkpp_dataset = dcmtkpp::dcmtk::convert(&dcmtk_data_set);
    BOOST_REQUIRE(dcmtkpp_data_set == other_dcmtkpp_dataset);
}

void do_test(dcmtkpp::DataSet const & dcmtkpp_data_set)
{
    std::vector<std::string> const transfer_syntaxes =
        {
            dcmtkpp::registry::ImplicitVRLittleEndian,
            dcmtkpp::registry::ExplicitVRLittleEndian,
            dcmtkpp::registry::ExplicitVRBigEndian_Retired
        };
    std::vector<dcmtkpp::Writer::ItemEncoding> item_encodings =
        {
            dcmtkpp::Writer::ItemEncoding::ExplicitLength,
            dcmtkpp::Writer::ItemEncoding::UndefinedLength
        };
    std::vector<bool> use_group_length_values = {/*true, */false};

    for(auto const & transfer_syntax: transfer_syntaxes)
    {
        for(auto const & item_encoding: item_encodings)
        {
            for(auto const & use_group_length: use_group_length_values)
            {
                do_test(
                    dcmtkpp_data_set, transfer_syntax,
                    item_encoding, use_group_length);
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(CS)
{
    dcmtkpp::Element dcmtkpp_element({"ABC", "DEF"}, dcmtkpp::VR::CS);
    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::SelectorCSValue, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
}

BOOST_AUTO_TEST_CASE(DS)
{
    dcmtkpp::Element dcmtkpp_element({1.23, -4.56}, dcmtkpp::VR::DS);
    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::SelectorDSValue, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
}

BOOST_AUTO_TEST_CASE(FD)
{
    dcmtkpp::Element dcmtkpp_element({1.23, -4.56}, dcmtkpp::VR::FD);
    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::SelectorFDValue, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
}

BOOST_AUTO_TEST_CASE(FL)
{
    dcmtkpp::Element dcmtkpp_element({0.5, -0.125}, dcmtkpp::VR::FL);
    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::SelectorFLValue, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
}

BOOST_AUTO_TEST_CASE(IS)
{
    dcmtkpp::Element dcmtkpp_element({123, -456}, dcmtkpp::VR::IS);
    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::SelectorISValue, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
}

BOOST_AUTO_TEST_CASE(OB)
{
    dcmtkpp::Element dcmtkpp_element(
        std::vector<uint8_t>({0x01, 0x02, 0x03, 0x04}),
        dcmtkpp::VR::OB);
    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::EncapsulatedDocument, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
}

BOOST_AUTO_TEST_CASE(OF)
{
    dcmtkpp::Element dcmtkpp_element(
        std::vector<uint8_t>({0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}),
        dcmtkpp::VR::OF);
    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::VectorGridData, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
}

BOOST_AUTO_TEST_CASE(OW)
{
    dcmtkpp::Element dcmtkpp_element(
        std::vector<uint8_t>({0x01, 0x02, 0x03, 0x04}),
        dcmtkpp::VR::OW);
    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::RedPaletteColorLookupTableData, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
}

BOOST_AUTO_TEST_CASE(SL)
{
    dcmtkpp::Element dcmtkpp_element({12345678, -8765432}, dcmtkpp::VR::SL);
    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::SelectorSLValue, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
}

BOOST_AUTO_TEST_CASE(SQ)
{
    dcmtkpp::DataSet item1;
    item1.add(
        dcmtkpp::registry::SelectorSLValue,
        dcmtkpp::Element({12345678, -8765432}, dcmtkpp::VR::SL));
    dcmtkpp::DataSet item2;
    item2.add(
        dcmtkpp::registry::SelectorFDValue,
        dcmtkpp::Element({1.23, -4.56}, dcmtkpp::VR::FD));

    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::FrameExtractionSequence,
        dcmtkpp::Element({item1, item2}, dcmtkpp::VR::SQ));

    do_test(dcmtkpp_data_set);
}

BOOST_AUTO_TEST_CASE(SS)
{
    dcmtkpp::Element dcmtkpp_element({1234, -5678}, dcmtkpp::VR::SS);
    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::SelectorSSValue, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
}

BOOST_AUTO_TEST_CASE(UI)
{
    dcmtkpp::Element dcmtkpp_element({"1.2", "3.4"}, dcmtkpp::VR::UI);
    dcmtkpp::DataSet dcmtkpp_data_set;
    // SelectorUIValue is not in current DCMTK
    dcmtkpp_data_set.add(dcmtkpp::registry::SOPInstanceUID, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
}

BOOST_AUTO_TEST_CASE(UL)
{
    dcmtkpp::Element dcmtkpp_element({12345678, 8765432}, dcmtkpp::VR::UL);
    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::SelectorULValue, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
}

BOOST_AUTO_TEST_CASE(US)
{
    dcmtkpp::Element dcmtkpp_element({1234, 5678}, dcmtkpp::VR::US);
    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::SelectorUSValue, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
}

void do_file_test(
    dcmtkpp::DataSet const & dcmtkpp_data_set, std::string transfer_syntax,
    dcmtkpp::Writer::ItemEncoding item_encoding, bool use_group_length)
{
    // Write input data set
    std::stringstream stream;

    dcmtkpp::Writer::write_file(
        dcmtkpp_data_set, stream, dcmtkpp::DataSet(), transfer_syntax,
        item_encoding, use_group_length);

    // Store data in a DCMTK stream
    std::string const data = stream.str();
    DcmInputBufferStream dcmtk_stream;
    dcmtk_stream.setBuffer(&data[0], data.size());

    // Read output data set
    DcmFileFormat format;

    format.transferInit();
    OFCondition const condition = format.read(dcmtk_stream);
    BOOST_REQUIRE(condition == EC_Normal || condition == EC_StreamNotifyClient);
    BOOST_REQUIRE_EQUAL(dcmtk_stream.avail(), 0);
    format.transferEnd();

    DcmMetaInfo * dcmtk_meta_information = format.getMetaInfo();
    auto const dcmtkpp_meta_information =
        dcmtkpp::dcmtk::convert(dcmtk_meta_information);
    BOOST_REQUIRE(
        dcmtkpp_meta_information.as_string(dcmtkpp::registry::TransferSyntaxUID) ==
            dcmtkpp::Value::Strings({ transfer_syntax }));

    DcmDataset * dcmtk_data_set = format.getDataset();
    auto const other_dcmtkpp_dataset = dcmtkpp::dcmtk::convert(dcmtk_data_set);
    BOOST_REQUIRE(dcmtkpp_data_set == other_dcmtkpp_dataset);

    BOOST_REQUIRE(
        dcmtkpp_meta_information.as_string(dcmtkpp::registry::MediaStorageSOPClassUID) ==
            other_dcmtkpp_dataset.as_string(dcmtkpp::registry::SOPClassUID));
    BOOST_REQUIRE(
        dcmtkpp_meta_information.as_string(dcmtkpp::registry::MediaStorageSOPInstanceUID) ==
            other_dcmtkpp_dataset.as_string(dcmtkpp::registry::SOPInstanceUID));
}

void do_file_test(dcmtkpp::DataSet const & dcmtkpp_data_set)
{
    std::vector<std::string> const transfer_syntaxes =
        {
            dcmtkpp::registry::ImplicitVRLittleEndian,
            dcmtkpp::registry::ExplicitVRLittleEndian,
            dcmtkpp::registry::ExplicitVRBigEndian_Retired
        };
    std::vector<dcmtkpp::Writer::ItemEncoding> item_encodings =
        {
            dcmtkpp::Writer::ItemEncoding::ExplicitLength,
            dcmtkpp::Writer::ItemEncoding::UndefinedLength
        };
    std::vector<bool> use_group_length_values = {/*true, */false};

    for(auto const & transfer_syntax: transfer_syntaxes)
    {
        for(auto const & item_encoding: item_encodings)
        {
            for(auto const & use_group_length: use_group_length_values)
            {
                do_file_test(
                    dcmtkpp_data_set, transfer_syntax,
                    item_encoding, use_group_length);
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(File)
{
    dcmtkpp::DataSet item1;
    item1.add(
        dcmtkpp::registry::SelectorSLValue,
        dcmtkpp::Element({12345678, -8765432}, dcmtkpp::VR::SL));
    dcmtkpp::DataSet item2;
    item2.add(
        dcmtkpp::registry::SelectorFDValue,
        dcmtkpp::Element({1.23, -4.56}, dcmtkpp::VR::FD));

    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(
        dcmtkpp::registry::SOPClassUID,
        {dcmtkpp::registry::RawDataStorage}, dcmtkpp::VR::UI);
    dcmtkpp_data_set.add(
        dcmtkpp::registry::SOPInstanceUID,
        {"1.2.3.4"}, dcmtkpp::VR::UI);
    dcmtkpp_data_set.add(
        dcmtkpp::registry::FrameExtractionSequence,
        dcmtkpp::Element({item1, item2}, dcmtkpp::VR::SQ));

    do_file_test(dcmtkpp_data_set);
}
