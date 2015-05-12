#define BOOST_TEST_MODULE conversion
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dcmtkpp/conversion.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/ElementAccessor.h"
#include "dcmtkpp/Tag.h"
#include "dcmtkpp/Value.h"
#include "dcmtkpp/VR.h"
#include "dcmtkpp/VRTraits.h"

BOOST_AUTO_TEST_CASE(TagFromDcmtkpp)
{
    dcmtkpp::Tag const source(0xdead, 0xbeef);
    DcmTagKey const destination = dcmtkpp::convert(source);

    BOOST_CHECK_EQUAL(destination.getGroup(), 0xdead);
    BOOST_CHECK_EQUAL(destination.getElement(), 0xbeef);
}

BOOST_AUTO_TEST_CASE(TagFromDcmtk)
{
    DcmTagKey const source(0xdead, 0xbeef);
    dcmtkpp::Tag const destination = dcmtkpp::convert(source);

    BOOST_CHECK_EQUAL(destination.group, 0xdead);
    BOOST_CHECK_EQUAL(destination.element, 0xbeef);
}

template<typename TValueType>
void compare(TValueType const & t1, TValueType const & t2)
{
    BOOST_CHECK_EQUAL(t1, t2);
}

template<>
void compare<dcmtkpp::Value::Reals::value_type>(
    dcmtkpp::Value::Reals::value_type const & t1,
    dcmtkpp::Value::Reals::value_type const & t2)
{
    BOOST_CHECK_CLOSE(t1, t2, 1e-6);
}

template<dcmtkpp::VR VVR, DcmEVR VEVR, typename TInputType, typename TOutputType>
void test_element_from_dcmtkpp(
    TInputType const & source_value,
    TInputType const & (dcmtkpp::Element::*getter)() const)
{
    dcmtkpp::Tag const source_tag(0xdead, 0xbeef);
    DcmTagKey const destination_tag = dcmtkpp::convert(source_tag);

    dcmtkpp::Element const source(source_value, VVR);

    DcmElement * destination = dcmtkpp::convert(source_tag, source);
    BOOST_CHECK_NE(destination, (DcmElement const *)(NULL));

    BOOST_CHECK_EQUAL(destination->getVR(), VEVR);
    BOOST_CHECK_NE(
        dynamic_cast<TOutputType *>(destination), (TOutputType *)(NULL));

    BOOST_CHECK_EQUAL(destination->getVM(), source.size());
    for(std::size_t i=0; i<source.size(); ++i)
    {
        typedef typename dcmtkpp::VRTraits<VEVR>::ValueType ValueType;
        if(typeid(TInputType) == typeid(dcmtkpp::Value::Reals))
        {
            compare<ValueType>(
                dcmtkpp::ElementAccessor<ValueType>::element_get(*destination, i),
                (source.*getter)()[i]);
        }
        else
        {
            BOOST_CHECK_EQUAL(
                dcmtkpp::ElementAccessor<ValueType>::element_get(*destination, i),
                (source.*getter)()[i]);
        }
    }
}

template<dcmtkpp::VR VVR, DcmEVR VEVR, typename TInputType, typename TElementType>
void test_element_to_dcmtkpp(
    TInputType const & source_value,
    TInputType const & (dcmtkpp::Element::*getter)() const)
{
    DcmTag const source_tag(0xdead, 0xbeef, VEVR);
    TElementType source(source_tag);
    if(typeid(TInputType) == typeid(dcmtkpp::Value::Strings) ||
        VEVR == EVR_IS || VEVR == EVR_DS)
    {
        OFString value;

        if(!source_value.empty())
        {
            auto const last_it = --source_value.end();
            auto it = source_value.begin();
            while(it != last_it)
            {
                std::ostringstream stream;
                stream << *it;
                value += stream.str().c_str();
                value += "\\";
                ++it;
            }

            std::ostringstream stream;
            stream << *last_it;
            value += stream.str().c_str();
        }

        source.putOFStringArray(value);
    }
    else
    {
        for(unsigned int i=0; i<source_value.size(); ++i)
        {
            auto const & item = source_value[i];
            dcmtkpp::ElementAccessor<typename dcmtkpp::VRTraits<VEVR>::ValueType>::element_set(
                source, item, i);
        }
    }

    dcmtkpp::Element const destination = dcmtkpp::convert(&source);

    BOOST_CHECK(VVR == destination.vr);
    BOOST_CHECK_EQUAL(source.getVM(), destination.size());
    for(std::size_t i=0; i<destination.size(); ++i)
    {
        typedef typename dcmtkpp::VRTraits<VEVR>::ValueType ValueType;
        if(typeid(TInputType) == typeid(dcmtkpp::Value::Reals))
        {
            compare<ValueType>(
                dcmtkpp::ElementAccessor<ValueType>::element_get(source, i),
                (destination.*getter)()[i]);
        }
        else
        {
            BOOST_CHECK_EQUAL(
                dcmtkpp::ElementAccessor<ValueType>::element_get(source, i),
                (destination.*getter)()[i]);
        }
    }
}

#define ElementTest(vr, InputType, ElementType, value, getter) \
BOOST_AUTO_TEST_CASE(vr##FromDcmtkpp) \
{ \
    test_element_from_dcmtkpp< \
        dcmtkpp::VR::vr, EVR_##vr, InputType, ElementType>(value, getter); \
} \
BOOST_AUTO_TEST_CASE(vr##ToDcmtkpp) \
{ \
    test_element_to_dcmtkpp< \
        dcmtkpp::VR::vr, EVR_##vr, InputType, ElementType>(value, getter); \
}

ElementTest(
    AE, dcmtkpp::Value::Strings, DcmApplicationEntity,
    dcmtkpp::Value::Strings({"foo", "bar"}), &dcmtkpp::Element::as_string);

ElementTest(
    AS, dcmtkpp::Value::Strings, DcmAgeString,
    dcmtkpp::Value::Strings({"012Y", "345D"}), &dcmtkpp::Element::as_string);

// AT

ElementTest(
    CS, dcmtkpp::Value::Strings, DcmCodeString,
    dcmtkpp::Value::Strings({"foo", "bar"}), &dcmtkpp::Element::as_string);

ElementTest(
    DA, dcmtkpp::Value::Strings, DcmDate,
    dcmtkpp::Value::Strings({"19000101", "20131215"}),
    &dcmtkpp::Element::as_string);

ElementTest(
    DS, dcmtkpp::Value::Reals, DcmDecimalString,
    dcmtkpp::Value::Reals({12.34, 56.78}), &dcmtkpp::Element::as_real);

ElementTest(
    DT, dcmtkpp::Value::Strings, DcmDateTime,
    dcmtkpp::Value::Strings({"19000101123456", "201312150123"}),
    &dcmtkpp::Element::as_string);

ElementTest(
    FL, dcmtkpp::Value::Reals, DcmFloatingPointSingle,
    dcmtkpp::Value::Reals({12.34, 56.78}), &dcmtkpp::Element::as_real);

ElementTest(
    FD, dcmtkpp::Value::Reals, DcmFloatingPointDouble,
    dcmtkpp::Value::Reals({12.34, 56.78}), &dcmtkpp::Element::as_real);

ElementTest(
    IS, dcmtkpp::Value::Integers, DcmIntegerString,
    dcmtkpp::Value::Integers({34567, -67890}), &dcmtkpp::Element::as_int);

ElementTest(
    LO, dcmtkpp::Value::Strings, DcmLongString,
    dcmtkpp::Value::Strings({"foo bar", "something else"}),
    &dcmtkpp::Element::as_string);

ElementTest(
    LT, dcmtkpp::Value::Strings, DcmLongText,
    dcmtkpp::Value::Strings({"foo\nbar\\something else"}),
    &dcmtkpp::Element::as_string);

// OB
// OF
// OW

ElementTest(
    PN, dcmtkpp::Value::Strings, DcmPersonName,
    dcmtkpp::Value::Strings({"Doe^John", "^Bob^Dr."}),
    &dcmtkpp::Element::as_string);

ElementTest(
    SH, dcmtkpp::Value::Strings, DcmShortString,
    dcmtkpp::Value::Strings({"foo", "bar"}), &dcmtkpp::Element::as_string);

ElementTest(
    SL, dcmtkpp::Value::Integers, DcmSignedLong,
    dcmtkpp::Value::Integers({34567, -56789}), &dcmtkpp::Element::as_int);

ElementTest(
    SS, dcmtkpp::Value::Integers, DcmSignedShort,
    dcmtkpp::Value::Integers({1234, -5678}), &dcmtkpp::Element::as_int);

ElementTest(
    ST, dcmtkpp::Value::Strings, DcmShortText,
    dcmtkpp::Value::Strings({"foo\nbar\\something else"}),
    &dcmtkpp::Element::as_string);

ElementTest(
    TM, dcmtkpp::Value::Strings, DcmTime,
    dcmtkpp::Value::Strings({"123456", "0123"}),
    &dcmtkpp::Element::as_string);

ElementTest(
    UI, dcmtkpp::Value::Strings, DcmUniqueIdentifier,
    dcmtkpp::Value::Strings(
        {"1.2.840.10008.5.1.4.1.1.4", "1.2.840.10008.5.1.4.1.1.4.1"}),
        &dcmtkpp::Element::as_string);

ElementTest(
    UL, dcmtkpp::Value::Integers, DcmUnsignedLong,
    dcmtkpp::Value::Integers({123456, 789012}), &dcmtkpp::Element::as_int);

// UN

ElementTest(
    US, dcmtkpp::Value::Integers, DcmUnsignedShort,
    dcmtkpp::Value::Integers({12345, 6789}), &dcmtkpp::Element::as_int);

ElementTest(
    UT, dcmtkpp::Value::Strings, DcmUnlimitedText,
    dcmtkpp::Value::Strings({"foo\nbar\\something else"}),
    &dcmtkpp::Element::as_string);

BOOST_AUTO_TEST_CASE(SQFromDcmtkpp)
{
    dcmtkpp::DataSet item;
    item.add("PatientID");
    item.as_string("PatientID").push_back("DJ1234");

    dcmtkpp::Element const source(
        dcmtkpp::Value::DataSets({item}), dcmtkpp::VR::SQ);

    dcmtkpp::Tag const source_tag(0xdead, 0xbeef);

    DcmElement * destination = dcmtkpp::convert(source_tag, source);

    BOOST_CHECK_NE(destination, (DcmElement const *)(NULL));

    BOOST_CHECK_EQUAL(destination->getVR(), dcmtkpp::convert(source.vr));
    BOOST_CHECK_NE(
        dynamic_cast<DcmSequenceOfItems *>(destination),
        (DcmSequenceOfItems *)(NULL));

    BOOST_CHECK_EQUAL(destination->getVM(), source.size());
    for(std::size_t i=0; i<source.size(); ++i)
    {
        dcmtkpp::DataSet const & source_item = source.as_data_set()[i];
        DcmItem * item = dynamic_cast<DcmSequenceOfItems *>(destination)->getItem(i);
        DcmDataset * destination_item = dynamic_cast<DcmDataset *>(item);
        BOOST_CHECK(source_item == dcmtkpp::convert(*destination_item));
    }
}

BOOST_AUTO_TEST_CASE(SQToDcmtkpp)
{
    DcmDataset * item = new DcmDataset;
    item->putAndInsertOFStringArray(DCM_PatientID, "DJ1234");

    DcmSequenceOfItems source(DcmTag(0xdead, 0xbeef, EVR_SQ));
    source.append(item);

    dcmtkpp::Element const destination = dcmtkpp::convert(&source);

    BOOST_CHECK(destination.vr == dcmtkpp::convert(source.getVR()));
    BOOST_CHECK_EQUAL(source.getVM(), destination.size());
    for(std::size_t i=0; i<destination.size(); ++i)
    {
        DcmItem * item = source.getItem(i);
        DcmDataset * source_item = dynamic_cast<DcmDataset *>(item);
        BOOST_REQUIRE(source_item != NULL);

        dcmtkpp::DataSet const & destination_item = destination.as_data_set()[i];
        BOOST_CHECK(dcmtkpp::convert(*source_item) == destination_item);
    }
}

BOOST_AUTO_TEST_CASE(EmptyDataSetFromDcmtkpp)
{
    dcmtkpp::DataSet const empty;
    DcmDataset const result = dcmtkpp::convert(empty);
    BOOST_CHECK_EQUAL(result.card(), 0);
}

BOOST_AUTO_TEST_CASE(EmptyDataSetFromDcmtk)
{
    DcmDataset const empty;
    dcmtkpp::DataSet const result = dcmtkpp::convert(empty);
    BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(DataSetFromDcmtkpp)
{
    dcmtkpp::Element const patient_id_source(
        dcmtkpp::Value::Strings({"DJ1234"}), dcmtkpp::VR::CS);
    dcmtkpp::Element const pixel_spacing_source(
        dcmtkpp::Value::Reals({1.23, 4.56}), dcmtkpp::VR::DS);

    dcmtkpp::DataSet source;
    source.add(dcmtkpp::Tag("PatientID"), patient_id_source);
    source.add(dcmtkpp::Tag("PixelSpacing"), pixel_spacing_source);

    DcmDataset result = dcmtkpp::convert(source);
    BOOST_CHECK_EQUAL(result.card(), 2);

    DcmElement * patient_id;
    OFCondition const patient_id_ok =
        result.findAndGetElement(DCM_PatientID, patient_id);
    BOOST_CHECK(patient_id_ok.good());
    BOOST_CHECK(
        dcmtkpp::convert(patient_id).as_string() ==
            patient_id_source.as_string());

    DcmElement * pixel_spacing;
    OFCondition const pixel_spacing_ok =
        result.findAndGetElement(DCM_PixelSpacing, pixel_spacing);
    BOOST_CHECK(pixel_spacing_ok.good());
    BOOST_CHECK(
        dcmtkpp::convert(pixel_spacing).as_real() ==
            pixel_spacing_source.as_real());
}

BOOST_AUTO_TEST_CASE(DataSetFromDcmtk)
{
    dcmtkpp::Element const patient_id_source(
        dcmtkpp::Value::Strings({"DJ1234"}), dcmtkpp::VR::CS);
    dcmtkpp::Element const pixel_spacing_source(
        dcmtkpp::Value::Reals({1.23, 4.56}), dcmtkpp::VR::DS);

    DcmDataset source;
    source.insert(dcmtkpp::convert(dcmtkpp::Tag("PatientID"), patient_id_source));
    source.insert(dcmtkpp::convert(dcmtkpp::Tag("PixelSpacing"), pixel_spacing_source));

    dcmtkpp::DataSet const result = dcmtkpp::convert(source);
    BOOST_CHECK_EQUAL(result.size(), 2);
    BOOST_CHECK(
        result.as_string(dcmtkpp::Tag("PatientID")) ==
            patient_id_source.as_string());
    BOOST_CHECK(
        result.as_real(dcmtkpp::Tag("PixelSpacing")) ==
            pixel_spacing_source.as_real());
}
