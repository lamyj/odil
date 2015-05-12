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

BOOST_AUTO_TEST_CASE(EmptyFromDcmtkpp)
{
    dcmtkpp::DataSet const empty;
    DcmDataset const result = dcmtkpp::convert(empty);
    BOOST_CHECK_EQUAL(result.card(), 0);
}

BOOST_AUTO_TEST_CASE(EmptyFromDcmtk)
{
    DcmDataset const empty;
    dcmtkpp::DataSet const result = dcmtkpp::convert(empty);
    BOOST_CHECK(result.empty());
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

BOOST_AUTO_TEST_CASE(AEFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::AE, EVR_AE, dcmtkpp::Value::Strings, DcmApplicationEntity
    >({"foo", "bar"}, &dcmtkpp::Element::as_string);
}

BOOST_AUTO_TEST_CASE(ASFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::AS, EVR_AS, dcmtkpp::Value::Strings, DcmAgeString
    >({"012Y", "345D"}, &dcmtkpp::Element::as_string);
}

// AT

BOOST_AUTO_TEST_CASE(CSFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::CS, EVR_CS, dcmtkpp::Value::Strings, DcmCodeString
    >({"foo", "bar"}, &dcmtkpp::Element::as_string);
}

BOOST_AUTO_TEST_CASE(DAFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::DA, EVR_DA, dcmtkpp::Value::Strings, DcmDate
    >({"19000101", "20131215"}, &dcmtkpp::Element::as_string);
}

BOOST_AUTO_TEST_CASE(DSFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::DS, EVR_DS, dcmtkpp::Value::Reals, DcmDecimalString
    >({12.34, 56.78}, &dcmtkpp::Element::as_real);
}

BOOST_AUTO_TEST_CASE(DTFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::DT, EVR_DT, dcmtkpp::Value::Strings, DcmDateTime
    >({"19000101123456", "201312150123"}, &dcmtkpp::Element::as_string);
}

BOOST_AUTO_TEST_CASE(FLFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::FL, EVR_FL, dcmtkpp::Value::Reals, DcmFloatingPointSingle
    >({12.34, 56.78}, &dcmtkpp::Element::as_real);
}

BOOST_AUTO_TEST_CASE(FDFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::FD, EVR_FD, dcmtkpp::Value::Reals, DcmFloatingPointDouble
    >({12.34, 56.78}, &dcmtkpp::Element::as_real);
}

BOOST_AUTO_TEST_CASE(ISFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::IS, EVR_IS, dcmtkpp::Value::Integers, DcmIntegerString
    >({34567, -67890}, &dcmtkpp::Element::as_int);
}

BOOST_AUTO_TEST_CASE(LOFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::LO, EVR_LO, dcmtkpp::Value::Strings, DcmLongString
    >({"foo bar", "something else"}, &dcmtkpp::Element::as_string);
}

BOOST_AUTO_TEST_CASE(LTFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::LT, EVR_LT, dcmtkpp::Value::Strings, DcmLongText
    >({"foo\nbar\\something else"}, &dcmtkpp::Element::as_string);
}

// OB
// OF
// OW

BOOST_AUTO_TEST_CASE(PNFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::PN, EVR_PN, dcmtkpp::Value::Strings, DcmPersonName
    >({"Doe^John", "^Bob^Dr."}, &dcmtkpp::Element::as_string);
}

BOOST_AUTO_TEST_CASE(SHFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::SH, EVR_SH, dcmtkpp::Value::Strings, DcmShortString
    >({"foo", "bar"}, &dcmtkpp::Element::as_string);
}

BOOST_AUTO_TEST_CASE(SLFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::SL, EVR_SL, dcmtkpp::Value::Integers, DcmSignedLong
    >({34567, -56789}, &dcmtkpp::Element::as_int);
}

// SQ

BOOST_AUTO_TEST_CASE(SSFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::SS, EVR_SS, dcmtkpp::Value::Integers, DcmSignedShort
    >({1234, -5678}, &dcmtkpp::Element::as_int);
}

BOOST_AUTO_TEST_CASE(STFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::ST, EVR_ST, dcmtkpp::Value::Strings, DcmShortText
    >({"foo\nbar\\something else"}, &dcmtkpp::Element::as_string);
}

BOOST_AUTO_TEST_CASE(TMFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::TM, EVR_TM, dcmtkpp::Value::Strings, DcmTime
    >({"123456", "0123"}, &dcmtkpp::Element::as_string);
}

BOOST_AUTO_TEST_CASE(UIFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::UI, EVR_UI, dcmtkpp::Value::Strings, DcmUniqueIdentifier
    >(
        {"1.2.840.10008.5.1.4.1.1.4", "1.2.840.10008.5.1.4.1.1.4.1"},
        &dcmtkpp::Element::as_string);
}

BOOST_AUTO_TEST_CASE(ULFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::UL, EVR_UL, dcmtkpp::Value::Integers, DcmUnsignedLong
    >({123456, 789012}, &dcmtkpp::Element::as_int);
}

// UN

BOOST_AUTO_TEST_CASE(USFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::US, EVR_US, dcmtkpp::Value::Integers, DcmUnsignedShort
    >({12345, 6789}, &dcmtkpp::Element::as_int);
}

BOOST_AUTO_TEST_CASE(UTFromDcmtkpp)
{
    test_element_from_dcmtkpp<
        dcmtkpp::VR::UT, EVR_UT, dcmtkpp::Value::Strings, DcmUnlimitedText
    >({"foo\nbar\\something else"}, &dcmtkpp::Element::as_string);
}
