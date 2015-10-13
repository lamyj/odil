#define BOOST_TEST_MODULE Reader
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <tuple>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmdata/dcostrmb.h>

#include "dcmtkpp/endian.h"
#include "dcmtkpp/conversion.h"
#include "dcmtkpp/Element.h"
#include "dcmtkpp/registry.h"
#include "dcmtkpp/Reader.h"
#include "dcmtkpp/VR.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    std::istringstream stream;
    dcmtkpp::Reader const reader(stream, dcmtkpp::registry::ExplicitVRBigEndian_Retired);
    BOOST_REQUIRE(reader.byte_ordering == BIG_ENDIAN);
    BOOST_REQUIRE(reader.explicit_vr == true);
}

void do_test(
    dcmtkpp::DataSet const & dcmtkpp_data_set, std::string transfer_syntax,
    E_EncodingType item_encoding, E_GrpLenEncoding group_length_encoding)
{
    // Write input data set
    auto const dcmtk_data_set = dynamic_cast<DcmDataset*>(dcmtkpp::convert(dcmtkpp_data_set));
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
    dcmtkpp::Reader reader(stream, transfer_syntax);
    auto const other_dcmtkpp_data_set = reader.read_data_set();

    BOOST_REQUIRE(other_dcmtkpp_data_set == dcmtkpp_data_set);
}

void do_test(dcmtkpp::DataSet const & dcmtkpp_data_set)
{
    std::vector<std::string> const transfer_syntaxes =
        {
            dcmtkpp::registry::ImplicitVRLittleEndian,
            dcmtkpp::registry::ExplicitVRLittleEndian,
            dcmtkpp::registry::ExplicitVRBigEndian_Retired
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
                    dcmtkpp_data_set, transfer_syntax,
                    item_encoding, use_group_length);
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(AT)
{
    dcmtkpp::Element dcmtkpp_element({"12345678", "9abcdef0"}, dcmtkpp::VR::AT);
    dcmtkpp::DataSet dcmtkpp_data_set;
    dcmtkpp_data_set.add(dcmtkpp::registry::SelectorATValue, dcmtkpp_element);

    do_test(dcmtkpp_data_set);
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
    E_EncodingType item_encoding, E_GrpLenEncoding group_length_encoding)
{
    // Write input data set
    auto const dcmtk_data_set = dynamic_cast<DcmDataset*>(dcmtkpp::convert(dcmtkpp_data_set));

    DcmFileFormat file_format(dcmtk_data_set);
    file_format.getMetaInfo()->putAndInsertString(
        DCM_TransferSyntaxUID, transfer_syntax.c_str());
    file_format.getMetaInfo()->putAndInsertString(
        DCM_MediaStorageSOPClassUID,
        dcmtkpp_data_set.as_string(dcmtkpp::registry::SOPClassUID)[0].c_str());
    file_format.getMetaInfo()->putAndInsertString(
        DCM_MediaStorageSOPInstanceUID,
        dcmtkpp_data_set.as_string(dcmtkpp::registry::SOPInstanceUID)[0].c_str());

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
    dcmtkpp::DataSet meta_information, other_dcmtkpp_data_set;
    std::tie(meta_information, other_dcmtkpp_data_set) = dcmtkpp::Reader::read_file(stream);

    BOOST_REQUIRE(other_dcmtkpp_data_set == dcmtkpp_data_set);

    BOOST_REQUIRE(
        meta_information.as_string(dcmtkpp::registry::TransferSyntaxUID) ==
        dcmtkpp::Value::Strings({transfer_syntax}));
    BOOST_REQUIRE(
        meta_information.as_string(dcmtkpp::registry::MediaStorageSOPClassUID) ==
        other_dcmtkpp_data_set.as_string(dcmtkpp::registry::SOPClassUID));
    BOOST_REQUIRE(
        meta_information.as_string(dcmtkpp::registry::MediaStorageSOPInstanceUID) ==
        other_dcmtkpp_data_set.as_string(dcmtkpp::registry::SOPInstanceUID));
}

void do_file_test(dcmtkpp::DataSet const & dcmtkpp_data_set)
{
    std::vector<std::string> const transfer_syntaxes =
        {
            dcmtkpp::registry::ImplicitVRLittleEndian,
            dcmtkpp::registry::ExplicitVRLittleEndian,
            dcmtkpp::registry::ExplicitVRBigEndian_Retired
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
