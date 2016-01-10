#define BOOST_TEST_MODULE Writer
#include <boost/test/unit_test.hpp>

#include <sstream>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmdata/dcistrmb.h>

#include "odil/endian.h"
#include "odil/Element.h"
#include "odil/registry.h"
#include "odil/Writer.h"
#include "odil/VR.h"
#include "odil/dcmtk/conversion.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    std::ostringstream stream;
    odil::Writer const writer(stream, odil::ByteOrdering::BigEndian, true);
    BOOST_REQUIRE(writer.byte_ordering == odil::ByteOrdering::BigEndian);
    BOOST_REQUIRE(writer.explicit_vr == true);
}

BOOST_AUTO_TEST_CASE(ConstructorTransferSyntax)
{
    std::ostringstream stream;
    odil::Writer const writer(stream, odil::registry::ExplicitVRBigEndian_Retired);
    BOOST_REQUIRE(writer.byte_ordering == odil::ByteOrdering::BigEndian);
    BOOST_REQUIRE(writer.explicit_vr == true);
}

void do_test(
    odil::DataSet const & odil_data_set, std::string transfer_syntax,
    odil::Writer::ItemEncoding item_encoding, bool use_group_length)
{
    // Write input data set
    std::stringstream stream;
    odil::Writer const writer(
        stream, transfer_syntax, item_encoding, use_group_length);
    writer.write_data_set(odil_data_set);

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

    auto const other_odil_dataset = odil::dcmtk::convert(&dcmtk_data_set);
    BOOST_REQUIRE(odil_data_set == other_odil_dataset);
}

void do_test(odil::DataSet const & odil_data_set)
{
    std::vector<std::string> const transfer_syntaxes =
        {
            odil::registry::ImplicitVRLittleEndian,
            odil::registry::ExplicitVRLittleEndian,
            odil::registry::ExplicitVRBigEndian_Retired
        };
    std::vector<odil::Writer::ItemEncoding> item_encodings =
        {
            odil::Writer::ItemEncoding::ExplicitLength,
            odil::Writer::ItemEncoding::UndefinedLength
        };
    std::vector<bool> use_group_length_values = {/*true, */false};

    for(auto const & transfer_syntax: transfer_syntaxes)
    {
        for(auto const & item_encoding: item_encodings)
        {
            for(auto const & use_group_length: use_group_length_values)
            {
                do_test(
                    odil_data_set, transfer_syntax,
                    item_encoding, use_group_length);
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(AT)
{
    odil::Element odil_element({"00100020", "0008103e"}, odil::VR::AT);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::SelectorATValue, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(CS)
{
    odil::Element odil_element({"ABC", "DEF"}, odil::VR::CS);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::SelectorCSValue, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(DS)
{
    odil::Element odil_element({1.23, -4.56}, odil::VR::DS);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::SelectorDSValue, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(FD)
{
    odil::Element odil_element({1.23, -4.56}, odil::VR::FD);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::SelectorFDValue, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(FL)
{
    odil::Element odil_element({0.5, -0.125}, odil::VR::FL);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::SelectorFLValue, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(IS)
{
    odil::Element odil_element({123, -456}, odil::VR::IS);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::SelectorISValue, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(OB)
{
    odil::Element odil_element(
        std::vector<uint8_t>({0x01, 0x02, 0x03, 0x04}),
        odil::VR::OB);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::EncapsulatedDocument, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(OF)
{
    odil::Element odil_element(
        std::vector<uint8_t>({0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}),
        odil::VR::OF);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::VectorGridData, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(OW)
{
    odil::Element odil_element(
        std::vector<uint8_t>({0x01, 0x02, 0x03, 0x04}),
        odil::VR::OW);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::RedPaletteColorLookupTableData, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(SL)
{
    odil::Element odil_element({12345678, -8765432}, odil::VR::SL);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::SelectorSLValue, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(SQ)
{
    odil::DataSet item1;
    item1.add(
        odil::registry::SelectorSLValue,
        odil::Element({12345678, -8765432}, odil::VR::SL));
    odil::DataSet item2;
    item2.add(
        odil::registry::SelectorFDValue,
        odil::Element({1.23, -4.56}, odil::VR::FD));

    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::FrameExtractionSequence,
        odil::Element({item1, item2}, odil::VR::SQ));

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(SS)
{
    odil::Element odil_element({1234, -5678}, odil::VR::SS);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::SelectorSSValue, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(UI)
{
    odil::Element odil_element({"1.2", "3.4"}, odil::VR::UI);
    odil::DataSet odil_data_set;
    // SelectorUIValue is not in current DCMTK
    odil_data_set.add(odil::registry::SOPInstanceUID, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(UL)
{
    odil::Element odil_element({12345678, 8765432}, odil::VR::UL);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::SelectorULValue, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(US)
{
    odil::Element odil_element({1234, 5678}, odil::VR::US);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::SelectorUSValue, odil_element);

    do_test(odil_data_set);
}

void do_file_test(
    odil::DataSet const & odil_data_set, std::string transfer_syntax,
    odil::Writer::ItemEncoding item_encoding, bool use_group_length)
{
    // Write input data set
    std::stringstream stream;

    odil::Writer::write_file(
        odil_data_set, stream, odil::DataSet(), transfer_syntax,
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
    auto const odil_meta_information =
        odil::dcmtk::convert(dcmtk_meta_information);
    BOOST_REQUIRE(
        odil_meta_information.as_string(odil::registry::TransferSyntaxUID) ==
            odil::Value::Strings({ transfer_syntax }));

    DcmDataset * dcmtk_data_set = format.getDataset();
    auto const other_odil_dataset = odil::dcmtk::convert(dcmtk_data_set);
    BOOST_REQUIRE(odil_data_set == other_odil_dataset);

    BOOST_REQUIRE(
        odil_meta_information.as_string(odil::registry::MediaStorageSOPClassUID) ==
            other_odil_dataset.as_string(odil::registry::SOPClassUID));
    BOOST_REQUIRE(
        odil_meta_information.as_string(odil::registry::MediaStorageSOPInstanceUID) ==
            other_odil_dataset.as_string(odil::registry::SOPInstanceUID));
}

void do_file_test(odil::DataSet const & odil_data_set)
{
    std::vector<std::string> const transfer_syntaxes =
        {
            odil::registry::ImplicitVRLittleEndian,
            odil::registry::ExplicitVRLittleEndian,
            odil::registry::ExplicitVRBigEndian_Retired
        };
    std::vector<odil::Writer::ItemEncoding> item_encodings =
        {
            odil::Writer::ItemEncoding::ExplicitLength,
            odil::Writer::ItemEncoding::UndefinedLength
        };
    std::vector<bool> use_group_length_values = {/*true, */false};

    for(auto const & transfer_syntax: transfer_syntaxes)
    {
        for(auto const & item_encoding: item_encodings)
        {
            for(auto const & use_group_length: use_group_length_values)
            {
                do_file_test(
                    odil_data_set, transfer_syntax,
                    item_encoding, use_group_length);
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(File)
{
    odil::DataSet item1;
    item1.add(
        odil::registry::SelectorSLValue,
        odil::Element({12345678, -8765432}, odil::VR::SL));
    odil::DataSet item2;
    item2.add(
        odil::registry::SelectorFDValue,
        odil::Element({1.23, -4.56}, odil::VR::FD));

    odil::DataSet odil_data_set;
    odil_data_set.add(
        odil::registry::SOPClassUID,
        {odil::registry::RawDataStorage}, odil::VR::UI);
    odil_data_set.add(
        odil::registry::SOPInstanceUID,
        {"1.2.3.4"}, odil::VR::UI);
    odil_data_set.add(
        odil::registry::FrameExtractionSequence,
        odil::Element({item1, item2}, odil::VR::SQ));

    do_file_test(odil_data_set);
}
