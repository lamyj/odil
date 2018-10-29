#define BOOST_TEST_MODULE conversion
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "odil/DataSet.h"
#include "odil/Tag.h"
#include "odil/Value.h"
#include "odil/VR.h"
#include "odil/dcmtk/VRTraits.h"
#include "odil/dcmtk/conversion.h"
#include "odil/dcmtk/ElementAccessor.h"

BOOST_AUTO_TEST_CASE(TagFromDcmtkpp)
{
    odil::Tag const source(0xdead, 0xbeef);
    DcmTagKey const destination = odil::dcmtk::convert(source);

    BOOST_CHECK_EQUAL(destination.getGroup(), 0xdead);
    BOOST_CHECK_EQUAL(destination.getElement(), 0xbeef);
}

BOOST_AUTO_TEST_CASE(TagFromDcmtk)
{
    DcmTagKey const source(0xdead, 0xbeef);
    odil::Tag const destination = odil::dcmtk::convert(source);

    BOOST_CHECK_EQUAL(destination.group, 0xdead);
    BOOST_CHECK_EQUAL(destination.element, 0xbeef);
}

template<typename TValueType>
void compare(TValueType const & t1, TValueType const & t2)
{
    BOOST_CHECK_EQUAL(t1, t2);
}

template<>
void compare<odil::Value::Reals::value_type>(
    odil::Value::Reals::value_type const & t1,
    odil::Value::Reals::value_type const & t2)
{
    BOOST_CHECK_CLOSE(t1, t2, 1e-6);
}

template<odil::VR VVR, DcmEVR VEVR, typename TInputType, typename TOutputType>
void test_element_from_odil(
    TInputType const & source_value,
    TInputType const & (odil::Element::*getter)() const)
{
    odil::Tag const source_tag(0xdead, 0xbeef);
    DcmTagKey const destination_tag = odil::dcmtk::convert(source_tag);

    odil::Element const source(source_value, VVR);

    DcmElement * destination = odil::dcmtk::convert(source_tag, source);
    BOOST_CHECK_NE(destination, (DcmElement const *)(NULL));

    BOOST_CHECK_EQUAL(destination->getVR(), VEVR);
    BOOST_CHECK_NE(
        dynamic_cast<TOutputType *>(destination), (TOutputType *)(NULL));

    BOOST_CHECK_EQUAL(destination->getVM(), source.size());
    for(std::size_t i=0; i<source.size(); ++i)
    {
        typedef typename odil::dcmtk::VRTraits<VEVR>::ValueType ValueType;
        if(typeid(TInputType) == typeid(odil::Value::Reals))
        {
            compare<ValueType>(
                odil::dcmtk::ElementAccessor<ValueType>::element_get(*destination, i),
                (source.*getter)()[i]);
        }
        else
        {
            BOOST_CHECK_EQUAL(
                odil::dcmtk::ElementAccessor<ValueType>::element_get(*destination, i),
                (source.*getter)()[i]);
        }
    }
}

template<odil::VR VVR, DcmEVR VEVR, typename TInputType, typename TElementType>
void test_element_to_odil(
    TInputType const & source_value,
    TInputType const & (odil::Element::*getter)() const)
{
    DcmTag const source_tag(0xdead, 0xbeef, VEVR);
    TElementType source(source_tag);
    if(typeid(TInputType) == typeid(odil::Value::Strings) ||
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
            odil::dcmtk::ElementAccessor<typename odil::dcmtk::VRTraits<VEVR>::ValueType>::element_set(
                source, item, i);
        }
    }

    odil::Element const destination = odil::dcmtk::convert(&source);

    BOOST_CHECK(VVR == destination.vr);
    BOOST_CHECK_EQUAL(source.getVM(), destination.size());
    for(std::size_t i=0; i<destination.size(); ++i)
    {
        typedef typename odil::dcmtk::VRTraits<VEVR>::ValueType ValueType;
        if(typeid(TInputType) == typeid(odil::Value::Reals))
        {
            compare<ValueType>(
                odil::dcmtk::ElementAccessor<ValueType>::element_get(source, i),
                (destination.*getter)()[i]);
        }
        else
        {
            BOOST_CHECK_EQUAL(
                odil::dcmtk::ElementAccessor<ValueType>::element_get(source, i),
                (destination.*getter)()[i]);
        }
    }
}

#define ElementTest(vr, InputType, ElementType, value, getter) \
BOOST_AUTO_TEST_CASE(vr##FromOdil) \
{ \
    test_element_from_odil< \
        odil::VR::vr, EVR_##vr, InputType, ElementType>(value, getter); \
} \
BOOST_AUTO_TEST_CASE(vr##ToOdil) \
{ \
    test_element_to_odil< \
        odil::VR::vr, EVR_##vr, InputType, ElementType>(value, getter); \
}

ElementTest(
    AE, odil::Value::Strings, DcmApplicationEntity,
    odil::Value::Strings({"foo", "bar"}), &odil::Element::as_string);

ElementTest(
    AS, odil::Value::Strings, DcmAgeString,
    odil::Value::Strings({"012Y", "345D"}), &odil::Element::as_string);

ElementTest(
    CS, odil::Value::Strings, DcmCodeString,
    odil::Value::Strings({"foo", "bar"}), &odil::Element::as_string);

ElementTest(
    DA, odil::Value::Strings, DcmDate,
    odil::Value::Strings({"19000101", "20131215"}),
    &odil::Element::as_string);

ElementTest(
    DS, odil::Value::Reals, DcmDecimalString,
    odil::Value::Reals({12.34, 56.78}), &odil::Element::as_real);

ElementTest(
    DT, odil::Value::Strings, DcmDateTime,
    odil::Value::Strings({"19000101123456", "201312150123"}),
    &odil::Element::as_string);

ElementTest(
    FL, odil::Value::Reals, DcmFloatingPointSingle,
    odil::Value::Reals({12.34, 56.78}), &odil::Element::as_real);

ElementTest(
    FD, odil::Value::Reals, DcmFloatingPointDouble,
    odil::Value::Reals({12.34, 56.78}), &odil::Element::as_real);

ElementTest(
    IS, odil::Value::Integers, DcmIntegerString,
    odil::Value::Integers({34567, -67890}), &odil::Element::as_int);

ElementTest(
    LO, odil::Value::Strings, DcmLongString,
    odil::Value::Strings({"foo bar", "something else"}),
    &odil::Element::as_string);

ElementTest(
    LT, odil::Value::Strings, DcmLongText,
    odil::Value::Strings({"foo\nbar\\something else"}),
    &odil::Element::as_string);

// OB
// OF
// OW

ElementTest(
    PN, odil::Value::Strings, DcmPersonName,
    odil::Value::Strings({"Doe^John", "^Bob^Dr."}),
    &odil::Element::as_string);

ElementTest(
    SH, odil::Value::Strings, DcmShortString,
    odil::Value::Strings({"foo", "bar"}), &odil::Element::as_string);

ElementTest(
    SL, odil::Value::Integers, DcmSignedLong,
    odil::Value::Integers({34567, -56789}), &odil::Element::as_int);

ElementTest(
    SS, odil::Value::Integers, DcmSignedShort,
    odil::Value::Integers({1234, -5678}), &odil::Element::as_int);

ElementTest(
    ST, odil::Value::Strings, DcmShortText,
    odil::Value::Strings({"foo\nbar\\something else"}),
    &odil::Element::as_string);

ElementTest(
    TM, odil::Value::Strings, DcmTime,
    odil::Value::Strings({"123456", "0123"}),
    &odil::Element::as_string);

ElementTest(
    UI, odil::Value::Strings, DcmUniqueIdentifier,
    odil::Value::Strings(
        {"1.2.840.10008.5.1.4.1.1.4", "1.2.840.10008.5.1.4.1.1.4.1"}),
        &odil::Element::as_string);

ElementTest(
    UL, odil::Value::Integers, DcmUnsignedLong,
    odil::Value::Integers({123456, 789012}), &odil::Element::as_int);

// UN

ElementTest(
    US, odil::Value::Integers, DcmUnsignedShort,
    odil::Value::Integers({12345, 6789}), &odil::Element::as_int);

ElementTest(
    UT, odil::Value::Strings, DcmUnlimitedText,
    odil::Value::Strings({"foo\nbar\\something else"}),
    &odil::Element::as_string);

BOOST_AUTO_TEST_CASE(ATFromDcmtkpp)
{
    odil::Element const source(
        odil::Value::Strings({"deadbeef", "beeff00d"}), odil::VR::AT);

    DcmElement * destination = odil::dcmtk::convert(
        odil::Tag(0x1234, 0x5678), source);

    BOOST_CHECK_NE(destination, (DcmElement const *)(NULL));

    BOOST_CHECK_EQUAL(destination->getVR(), odil::dcmtk::convert(source.vr));
    BOOST_CHECK_NE(
        dynamic_cast<DcmAttributeTag *>(destination),
        (DcmAttributeTag *)(NULL));

    BOOST_CHECK_EQUAL(destination->getVM(), source.size());
    for(std::size_t i=0; i<source.size(); ++i)
    {
        odil::Tag const & source_tag = source.as_string()[i];

        DcmTagKey destination_tag;
        OFCondition const condition = destination->getTagVal(destination_tag, i);
        BOOST_CHECK(condition.good());

        BOOST_CHECK(source_tag == odil::dcmtk::convert(destination_tag));
    }
}

BOOST_AUTO_TEST_CASE(ATToDcmtkpp)
{
    DcmAttributeTag source(DcmTag(0x1234, 0x5678, EVR_AT));
    source.putTagVal(DcmTagKey(0xdead, 0xbeef), 0);
    source.putTagVal(DcmTagKey(0xbeef, 0xf00d), 1);

    odil::Element const destination = odil::dcmtk::convert(&source);

    BOOST_CHECK(destination.vr == odil::dcmtk::convert(source.getVR()));
    BOOST_CHECK_EQUAL(source.getVM(), destination.size());
    for(std::size_t i=0; i<destination.size(); ++i)
    {
        DcmTagKey source_tag;
        source.getTagVal(source_tag, i);

        odil::Tag const & destination_tag = destination.as_string()[i];
        BOOST_CHECK(odil::dcmtk::convert(source_tag) == destination_tag);
    }
}

BOOST_AUTO_TEST_CASE(SQFromDcmtkpp)
{
    auto item = std::make_shared<odil::DataSet>();
    item->add("PatientID");
    item->as_string("PatientID").push_back("DJ1234");

    odil::Element const source(
        odil::Value::DataSets({item}), odil::VR::SQ);

    odil::Tag const source_tag(0xdead, 0xbeef);

    DcmElement * destination = odil::dcmtk::convert(source_tag, source);

    BOOST_CHECK_NE(destination, (DcmElement const *)(NULL));

    BOOST_CHECK_EQUAL(destination->getVR(), odil::dcmtk::convert(source.vr));
    BOOST_CHECK_NE(
        dynamic_cast<DcmSequenceOfItems *>(destination),
        (DcmSequenceOfItems *)(NULL));

    BOOST_CHECK_EQUAL(destination->getVM(), source.size());
    for(std::size_t i=0; i<source.size(); ++i)
    {
        auto const & source_item = source.as_data_set()[i];
        DcmItem * destination_item = dynamic_cast<DcmSequenceOfItems *>(destination)->getItem(i);
        BOOST_CHECK(*source_item == *odil::dcmtk::convert(destination_item));
    }
}

BOOST_AUTO_TEST_CASE(SQToDcmtkpp)
{
    DcmDataset * item = new DcmDataset;
    item->putAndInsertOFStringArray(DCM_PatientID, "DJ1234");

    DcmSequenceOfItems source(DcmTag(0xdead, 0xbeef, EVR_SQ));
    source.append(item);

    odil::Element const destination = odil::dcmtk::convert(&source);

    BOOST_CHECK(destination.vr == odil::dcmtk::convert(source.getVR()));
    BOOST_CHECK_EQUAL(source.getVM(), destination.size());
    for(std::size_t i=0; i<destination.size(); ++i)
    {
        DcmItem * item = source.getItem(i);
        DcmDataset * source_item = dynamic_cast<DcmDataset *>(item);
        BOOST_REQUIRE(source_item != NULL);

        auto const & destination_item = destination.as_data_set()[i];
        BOOST_CHECK(*odil::dcmtk::convert(source_item) == *destination_item);
    }
}

BOOST_AUTO_TEST_CASE(EmptyDataSetFromDcmtkpp)
{
    auto empty = std::make_shared<odil::DataSet>();
    DcmItem * result = odil::dcmtk::convert(empty);
    BOOST_CHECK_EQUAL(result->card(), 0);
}

BOOST_AUTO_TEST_CASE(EmptyDataSetFromDcmtk)
{
    DcmDataset empty;
    auto const result = odil::dcmtk::convert(&empty);
    BOOST_CHECK(result->empty());
}

BOOST_AUTO_TEST_CASE(DataSetFromDcmtkpp)
{
    odil::Element const patient_id_source(
        odil::Value::Strings({"DJ1234"}), odil::VR::CS);
    odil::Element const pixel_spacing_source(
        odil::Value::Reals({1.23, 4.56}), odil::VR::DS);

    auto source = std::make_shared<odil::DataSet>();
    source->add(odil::Tag("PatientID"), patient_id_source);
    source->add(odil::Tag("PixelSpacing"), pixel_spacing_source);

    DcmItem * result = odil::dcmtk::convert(source);
    BOOST_CHECK_EQUAL(result->card(), 2);

    DcmElement * patient_id;
    OFCondition const patient_id_ok =
        result->findAndGetElement(DCM_PatientID, patient_id);
    BOOST_CHECK(patient_id_ok.good());
    BOOST_CHECK(
        odil::dcmtk::convert(patient_id).as_string() ==
            patient_id_source.as_string());

    DcmElement * pixel_spacing;
    OFCondition const pixel_spacing_ok =
        result->findAndGetElement(DCM_PixelSpacing, pixel_spacing);
    BOOST_CHECK(pixel_spacing_ok.good());
    BOOST_CHECK(
        odil::dcmtk::convert(pixel_spacing).as_real() ==
            pixel_spacing_source.as_real());
}

BOOST_AUTO_TEST_CASE(DataSetFromDcmtk)
{
    odil::Element const patient_id_source(
        odil::Value::Strings({"DJ1234"}), odil::VR::CS);
    odil::Element const pixel_spacing_source(
        odil::Value::Reals({1.23, 4.56}), odil::VR::DS);

    DcmDataset source;
    source.insert(odil::dcmtk::convert(odil::Tag("PatientID"), patient_id_source));
    source.insert(odil::dcmtk::convert(odil::Tag("PixelSpacing"), pixel_spacing_source));

    auto const result = odil::dcmtk::convert(&source);
    BOOST_CHECK_EQUAL(result->size(), 2);
    BOOST_CHECK(
        result->as_string(odil::Tag("PatientID")) ==
            patient_id_source.as_string());
    BOOST_CHECK(
        result->as_real(odil::Tag("PixelSpacing")) ==
            pixel_spacing_source.as_real());
}
