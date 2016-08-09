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

#include "odil/json_converter.h"

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

template<typename T>
void do_test(odil::Tag const & tag, odil::VR vr, std::initializer_list<T> const & value)
{
    // Empty element
    {
        odil::Element element(odil::Value(), vr);
        odil::DataSet data_set;
        data_set.add(tag, element);
        do_test(data_set);
    }
    // Single value
    {
        odil::Element element({ *value.begin() }, vr);
        odil::DataSet data_set;
        data_set.add(tag, element);
        do_test(data_set);
    }
    // Multiple values
    {
        odil::Element element(value, vr);
        odil::DataSet data_set;
        data_set.add(tag, element);
        do_test(data_set);
    }
}

BOOST_AUTO_TEST_CASE(AE)
{
    do_test(
        odil::registry::SelectorAEValue, odil::VR::AE,
        {std::string("LOCAL"), std::string("REMOTE")});
}

BOOST_AUTO_TEST_CASE(AS)
{
    do_test(
        odil::registry::SelectorASValue, odil::VR::AS,
        {std::string("035Y"), std::string("022W")});
}

BOOST_AUTO_TEST_CASE(AT)
{
    do_test(
        odil::registry::SelectorATValue, odil::VR::AT,
        {std::string("12345678"), std::string("9abcdef0")});
}

BOOST_AUTO_TEST_CASE(CS)
{
    do_test(
        odil::registry::SelectorCSValue, odil::VR::CS,
        {std::string("ABC"), std::string("DEF")});
}

BOOST_AUTO_TEST_CASE(DA)
{
    do_test(
        odil::registry::SelectorDAValue, odil::VR::DA,
        {std::string("20160103"), std::string("19700131")});
}

BOOST_AUTO_TEST_CASE(DS)
{
    do_test(odil::registry::SelectorDSValue, odil::VR::DS, {1.23, -4.56});
}

BOOST_AUTO_TEST_CASE(DT)
{
    do_test(
        odil::registry::SelectorDTValue, odil::VR::DT,
        {std::string("20160103112233"), std::string("19700131001122.123456")});
}

BOOST_AUTO_TEST_CASE(FD)
{
    do_test(odil::registry::SelectorFDValue, odil::VR::FD, {1.23, -4.56});
}

BOOST_AUTO_TEST_CASE(FL)
{
    do_test(odil::registry::SelectorFLValue, odil::VR::FL, {0.5, -0.125});
}

BOOST_AUTO_TEST_CASE(IS)
{
    do_test(odil::registry::SelectorISValue, odil::VR::IS, {123, -456});
}

BOOST_AUTO_TEST_CASE(LO)
{
    do_test(
        odil::registry::SelectorLOValue, odil::VR::LO,
        {std::string("Foo"), std::string("Bar")});
}

BOOST_AUTO_TEST_CASE(LT)
{
    do_test(
        odil::registry::SelectorLTValue, odil::VR::LT,
        {std::string("Foo\\Bar")});
}

BOOST_AUTO_TEST_CASE(OB)
{
    do_test(
        odil::registry::EncapsulatedDocument, odil::VR::OB, {
            odil::Value::Binary::value_type{0x01, 0x02, 0x03, 0x04} });
}

// OD is not in current DCMTK

BOOST_AUTO_TEST_CASE(OF)
{
    do_test(
        odil::registry::VectorGridData, odil::VR::OF, {
            odil::Value::Binary::value_type{
                0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08} });
}

// OL is not in current DCMTK

BOOST_AUTO_TEST_CASE(OW)
{
    do_test(
        odil::registry::RedPaletteColorLookupTableData, odil::VR::OW, {
            odil::Value::Binary::value_type{0x01, 0x02, 0x03, 0x04} });
}

BOOST_AUTO_TEST_CASE(PN)
{
    do_test(
        odil::registry::SelectorPNValue, odil::VR::PN, {
            std::string("Adams^John Robert Quincy^^Rev.^B.A. M.Div."),
            std::string("Morrison-Jones^Susan^^^Ph.D., Chief Executive Officer")
        });
}

BOOST_AUTO_TEST_CASE(SH)
{
    do_test(
        odil::registry::SelectorSHValue, odil::VR::SH,
        {std::string("Foo"), std::string("Bar")});
}

BOOST_AUTO_TEST_CASE(SL)
{
    do_test(odil::registry::SelectorSLValue, odil::VR::SL, {12345678, -8765432});
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

    do_test(odil::registry::FrameExtractionSequence, odil::VR::SQ, {item1, item2});
}

BOOST_AUTO_TEST_CASE(SS)
{
    do_test(odil::registry::SelectorSSValue, odil::VR::SS, {1234, -5678});
}

BOOST_AUTO_TEST_CASE(ST)
{
    do_test(
        odil::registry::SelectorSTValue, odil::VR::ST,
        {std::string("Foo\\Bar")});
}

BOOST_AUTO_TEST_CASE(TM)
{
    do_test(
        odil::registry::SelectorTMValue, odil::VR::TM,
        {std::string("112233"), std::string("001122.123456")});
}

// UC is not in current DCMTK
//{
//    do_test(
//        odil::registry::SelectorUCValue, odil::VR::UC,
//        {std::string("Foo"), std::string("Bar")});
//}

BOOST_AUTO_TEST_CASE(UI)
{
    // SelectorUIValue is not in current DCMTK
    do_test(
        odil::registry::SOPInstanceUID, odil::VR::UI,
        {std::string("1.2"), std::string("3.4")});
}

BOOST_AUTO_TEST_CASE(UL)
{
    do_test(odil::registry::SelectorULValue, odil::VR::UL, {12345678, 8765432});
}

// UR is not in current DCMTK
//{
//    do_test(
//        odil::registry::SelectorURValue, odil::VR::UR,
//        {std::string("https://example.com"), std::string("mailto:me@example.com")});
//}

BOOST_AUTO_TEST_CASE(US)
{
    do_test(odil::registry::SelectorUSValue, odil::VR::US, {1234, 5678});
}

BOOST_AUTO_TEST_CASE(UT)
{
    do_test(
        odil::registry::SelectorUTValue, odil::VR::UT,
        {std::string("Foo\\Bar")});
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
