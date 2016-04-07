#define BOOST_TEST_MODULE Reader
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <tuple>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmdata/dcostrmb.h>

#include "odil/endian.h"
#include "odil/Element.h"
#include "odil/registry.h"
#include "odil/Reader.h"
#include "odil/VR.h"
#include "odil/dcmtk/conversion.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    std::istringstream stream;
    odil::Reader const reader(stream, odil::registry::ExplicitVRBigEndian_Retired);
    BOOST_REQUIRE(reader.byte_ordering == odil::ByteOrdering::BigEndian);
    BOOST_REQUIRE(reader.explicit_vr == true);
}

void do_test(
    odil::DataSet const & odil_data_set, std::string transfer_syntax,
    E_EncodingType item_encoding, E_GrpLenEncoding group_length_encoding)
{
    // Write input data set
    auto const dcmtk_data_set =
        dynamic_cast<DcmDataset*>(odil::dcmtk::convert(odil_data_set));
    std::string data(1000000, '\0');
    DcmOutputBufferStream dcmtk_stream(&data[0], data.size());
    dcmtk_data_set->transferInit();
    OFCondition const condition = dcmtk_data_set->write(
        dcmtk_stream, DcmXfer(transfer_syntax.c_str()).getXfer(),
        item_encoding, NULL, group_length_encoding);
    BOOST_REQUIRE(condition == EC_Normal);
    dcmtk_data_set->transferEnd();

    // Store data in a stream
    data = data.substr(0, dcmtk_stream.tell());
    std::istringstream stream(data);

    // Read output data set
    odil::Reader reader(stream, transfer_syntax);
    auto const other_odil_data_set = reader.read_data_set();

    BOOST_REQUIRE(other_odil_data_set == odil_data_set);
}

void do_test(odil::DataSet const & odil_data_set)
{
    std::vector<std::string> const transfer_syntaxes =
        {
            odil::registry::ImplicitVRLittleEndian,
            odil::registry::ExplicitVRLittleEndian,
            odil::registry::ExplicitVRBigEndian_Retired
        };
    std::vector<E_EncodingType> item_encodings =
        { EET_ExplicitLength, EET_UndefinedLength };
    std::vector<E_GrpLenEncoding> use_group_length_values =
        { EGL_withoutGL, EGL_withGL };

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
    odil::Element odil_element({"12345678", "9abcdef0"}, odil::VR::AT);
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
        odil::Value::Binary({{0x01, 0x02, 0x03, 0x04}}),
        odil::VR::OB);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::EncapsulatedDocument, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(OF)
{
    odil::Element odil_element(
        odil::Value::Binary({{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}}),
        odil::VR::OF);
    odil::DataSet odil_data_set;
    odil_data_set.add(odil::registry::VectorGridData, odil_element);

    do_test(odil_data_set);
}

BOOST_AUTO_TEST_CASE(OW)
{
    odil::Element odil_element(
        odil::Value::Binary({{0x01, 0x02, 0x03, 0x04}}),
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
    E_EncodingType item_encoding, E_GrpLenEncoding group_length_encoding)
{
    // Write input data set
    auto const dcmtk_data_set =
        dynamic_cast<DcmDataset*>(odil::dcmtk::convert(odil_data_set));

    DcmFileFormat file_format(dcmtk_data_set);
    file_format.getMetaInfo()->putAndInsertString(
        DCM_TransferSyntaxUID, transfer_syntax.c_str());
    file_format.getMetaInfo()->putAndInsertString(
        DCM_MediaStorageSOPClassUID,
        odil_data_set.as_string(odil::registry::SOPClassUID)[0].c_str());
    file_format.getMetaInfo()->putAndInsertString(
        DCM_MediaStorageSOPInstanceUID,
        odil_data_set.as_string(odil::registry::SOPInstanceUID)[0].c_str());

    std::string data(1000000, '\0');
    DcmOutputBufferStream dcmtk_stream(&data[0], data.size());

    file_format.transferInit();
    OFCondition const condition = file_format.write(
        dcmtk_stream, DcmXfer(transfer_syntax.c_str()).getXfer(),
        item_encoding, NULL, group_length_encoding);
    BOOST_REQUIRE(condition == EC_Normal);
    file_format.transferEnd();

    // Store data in a stream
    data = data.substr(0, dcmtk_stream.tell());
    std::istringstream stream(data);

    // Read output data set
    odil::DataSet meta_information, other_odil_data_set;
    std::tie(meta_information, other_odil_data_set) = odil::Reader::read_file(stream);

    BOOST_REQUIRE(other_odil_data_set == odil_data_set);

    BOOST_REQUIRE(
        meta_information.as_string(odil::registry::TransferSyntaxUID) ==
        odil::Value::Strings({transfer_syntax}));
    BOOST_REQUIRE(
        meta_information.as_string(odil::registry::MediaStorageSOPClassUID) ==
        other_odil_data_set.as_string(odil::registry::SOPClassUID));
    BOOST_REQUIRE(
        meta_information.as_string(odil::registry::MediaStorageSOPInstanceUID) ==
        other_odil_data_set.as_string(odil::registry::SOPInstanceUID));
}

void do_file_test(odil::DataSet const & odil_data_set)
{
    std::vector<std::string> const transfer_syntaxes =
        {
            odil::registry::ImplicitVRLittleEndian,
            odil::registry::ExplicitVRLittleEndian,
            odil::registry::ExplicitVRBigEndian_Retired
        };
    std::vector<E_EncodingType> item_encodings =
        { EET_ExplicitLength, EET_UndefinedLength };
    std::vector<E_GrpLenEncoding> use_group_length_values =
        { EGL_withoutGL, EGL_withGL };

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
