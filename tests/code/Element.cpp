#define BOOST_TEST_MODULE Element
#include <boost/test/unit_test.hpp>

#include <string>
#include <utility>

#include "odil/DataSet.h"
#include "odil/Element.h"
#include "odil/Exception.h"

template<typename TContainer>
void test_value(
    odil::Element const & element,
    odil::VR const & vr, TContainer const & contents,
    bool (odil::Element::*type_check)() const,
    TContainer const & (odil::Element::*getter)() const)
{
    BOOST_CHECK((element.*type_check)());
    BOOST_CHECK_EQUAL(element.empty(), contents.empty());
    BOOST_CHECK_EQUAL(element.size(), contents.size());
    BOOST_CHECK((element.*getter)() == contents);
    BOOST_CHECK(element.vr == vr);

    if(!element.is_int())
    {
        BOOST_CHECK_THROW(element.as_int(), odil::Exception);
    }
    if(!element.is_real())
    {
        BOOST_CHECK_THROW(element.as_real(), odil::Exception);
    }
    if(!element.is_string())
    {
        BOOST_CHECK_THROW(element.as_string(), odil::Exception);
    }
    if(!element.is_data_set())
    {
        BOOST_CHECK_THROW(element.as_data_set(), odil::Exception);
    }
    if(!element.is_binary())
    {
        BOOST_CHECK_THROW(element.as_binary(), odil::Exception);
    }
}

template<typename TContainer>
void test_implicit_container(
    odil::VR const & vr,
    bool (odil::Element::*type_check)() const,
    TContainer const & (odil::Element::*getter)() const)
{
    odil::Element const element(vr);
    test_value(element, vr, TContainer(), type_check, getter);
}

template<typename TContainer>
void test_container(
    TContainer const & contents, odil::VR const & vr,
    bool (odil::Element::*type_check)() const,
    TContainer const & (odil::Element::*getter)() const)
{
    odil::Element const element(contents, vr);
    test_value(element, vr, contents, type_check, getter);

    auto contents_copy(contents);
    odil::Element const other_element(std::move(contents_copy));
    BOOST_CHECK(contents_copy.empty());
}

template<typename TContainer>
void test_initializer_list(
    std::initializer_list<typename TContainer::value_type> const & contents,
    bool (odil::Element::*type_check)() const,
    TContainer const & (odil::Element::*getter)() const)
{
    odil::Element const element(contents);
    test_value(element, element.vr, TContainer(contents), type_check, getter);
}

template<typename TContainer>
void test_modify(
    TContainer const & contents,
    TContainer const & (odil::Element::*getter)() const,
    TContainer & (odil::Element::*setter)())
{
    odil::Element value(TContainer{{contents[0]}});
    (value.*setter)().push_back(contents[1]);
    BOOST_CHECK((value.*getter)() == contents);
}

template<typename TContainer>
void test_clear(
    TContainer const & contents, 
    bool (odil::Element::*type_check)() const)
{
    odil::Element element(contents);
    element.clear();
    BOOST_CHECK((element.*type_check)());
    BOOST_CHECK(element.empty());
}

template<typename TContainer>
void test_equality(
    TContainer const & contents_1, TContainer const & contents_2,
    odil::VR const & vr_1, odil::VR const & vr_2)
{
    odil::Element const value_1(contents_1, vr_1);
    odil::Element const value_2(contents_1, vr_1);
    odil::Element const value_3(contents_1, vr_2);
    odil::Element const value_4(contents_2, vr_1);

    BOOST_CHECK(value_1 == value_2);
    BOOST_CHECK( ! (value_1 == value_3));
    BOOST_CHECK( ! (value_1 == value_4));

    BOOST_CHECK(! (value_1 != value_2));
    BOOST_CHECK(value_1 != value_3);
    BOOST_CHECK(value_1 != value_4);
}

struct Visitor
{
    typedef std::pair<std::string, std::string> result_type;

    result_type operator()(odil::VR const & vr) const
    {
        return std::make_pair(odil::as_string(vr), std::string());
    }

    template<typename T>
    result_type operator()(odil::VR const & vr, T const & container) const
    {
        return std::make_pair(odil::as_string(vr), typeid(container).name());
    }
};

template<typename TContainer>
void test_visitor(
    TContainer const & contents, odil::VR const & vr)
{
    odil::Element const element(contents, vr);
    BOOST_REQUIRE(
        odil::apply_visitor(Visitor(), element)
        == std::make_pair(
                odil::as_string(vr), 
                contents.empty()?std::string():typeid(TContainer).name()));
}


template<typename TContainer>
void test(
   std::initializer_list<typename TContainer::value_type> const & contents,
   std::initializer_list<typename TContainer::value_type> const & other_contents,
   odil::VR const & vr, odil::VR const & other_vr,
   bool (odil::Element::*type_check)() const,
   TContainer const & (odil::Element::*getter)() const,
   TContainer & (odil::Element::*setter)())
{
    TContainer const container(contents);
    TContainer const other_container(other_contents);

    test_container(TContainer(), vr, type_check, getter);
    test_container(container, vr, type_check, getter);
    test_initializer_list(contents, type_check, getter); 
    
    test_modify(container, getter, setter);

    test_clear(container, type_check);

    test_equality(container, other_container, vr, other_vr);

    test_visitor(TContainer(), vr);
    test_visitor(container, vr);
}

BOOST_AUTO_TEST_CASE(ImplicitType)
{
    test_implicit_container<odil::Value::Strings>(
        odil::VR::AE, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::AS, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::AT, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::CS, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::DA, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Reals>(
        odil::VR::DS, &odil::Element::is_real, &odil::Element::as_real);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::DT, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Reals>(
        odil::VR::FL, &odil::Element::is_real, &odil::Element::as_real);
    test_implicit_container<odil::Value::Reals>(
        odil::VR::FD, &odil::Element::is_real, &odil::Element::as_real);
    test_implicit_container<odil::Value::Integers>(
        odil::VR::IS, &odil::Element::is_int, &odil::Element::as_int);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::LO, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::LT, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Binary>(
        odil::VR::OB, &odil::Element::is_binary, &odil::Element::as_binary);
    test_implicit_container<odil::Value::Binary>(
        odil::VR::OD, &odil::Element::is_binary, &odil::Element::as_binary);
    test_implicit_container<odil::Value::Binary>(
        odil::VR::OF, &odil::Element::is_binary, &odil::Element::as_binary);
    test_implicit_container<odil::Value::Binary>(
        odil::VR::OL, &odil::Element::is_binary, &odil::Element::as_binary);
    test_implicit_container<odil::Value::Binary>(
        odil::VR::OW, &odil::Element::is_binary, &odil::Element::as_binary);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::PN, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::SH, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Integers>(
        odil::VR::SL, &odil::Element::is_int, &odil::Element::as_int);
    test_implicit_container<odil::Value::DataSets>(
        odil::VR::SQ, &odil::Element::is_data_set, &odil::Element::as_data_set);
    test_implicit_container<odil::Value::Integers>(
        odil::VR::SS, &odil::Element::is_int, &odil::Element::as_int);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::ST, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::TM, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::UC, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::UI, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Integers>(
        odil::VR::UL, &odil::Element::is_int, &odil::Element::as_int);
    test_implicit_container<odil::Value::Binary>(
        odil::VR::UN, &odil::Element::is_binary, &odil::Element::as_binary);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::UR, &odil::Element::is_string, &odil::Element::as_string);
    test_implicit_container<odil::Value::Integers>(
        odil::VR::US, &odil::Element::is_int, &odil::Element::as_int);
    test_implicit_container<odil::Value::Strings>(
        odil::VR::UT, &odil::Element::is_string, &odil::Element::as_string);
}

BOOST_AUTO_TEST_CASE(Int)
{
    BOOST_CHECK(odil::Element({1234, 5678}).is_int());
    test<odil::Value::Integers>(
        {1234, 5678}, {9012, 3456}, odil::VR::US, odil::VR::UL, 
        &odil::Element::is_int,
        &odil::Element::as_int, &odil::Element::as_int);
}

BOOST_AUTO_TEST_CASE(Real)
{
    BOOST_CHECK(odil::Element({12.34, 56.78}).is_real());
    test<odil::Value::Reals>(
        {12.34, 56.78}, {1., 2.}, odil::VR::FD, odil::VR::DS, 
        &odil::Element::is_real,
        &odil::Element::as_real, &odil::Element::as_real);
}

BOOST_AUTO_TEST_CASE(String)
{
    BOOST_CHECK(odil::Element({"foo", "bar"}).is_string());
    test<odil::Value::Strings>(
        {"foo", "bar"}, {"plip", "plop"}, odil::VR::CS, odil::VR::UT, 
        &odil::Element::is_string,
        &odil::Element::as_string, &odil::Element::as_string);
}

BOOST_AUTO_TEST_CASE(DataSets)
{
    odil::DataSet data_set_1;
    data_set_1.add("PatientID", {"DJ1234"});

    odil::DataSet data_set_2;
    data_set_2.add("EchoTime", {100});

    BOOST_CHECK(odil::Element({data_set_1, data_set_2}).is_data_set());
    test<odil::Value::DataSets>(
        {data_set_1, data_set_2}, {data_set_2, data_set_1}, 
        odil::VR::SQ, odil::VR::UN,
        &odil::Element::is_data_set,
        &odil::Element::as_data_set, &odil::Element::as_data_set);
}

BOOST_AUTO_TEST_CASE(Binary)
{
    BOOST_CHECK(odil::Element({{0x1, 0x2}, {0x3}}).is_binary());
    test<odil::Value::Binary>(
        {{0x1, 0x2}, {0x3}}, {{0x4}, {0x5, 0x6}},
        odil::VR::OB, odil::VR::OW,
        &odil::Element::is_binary,
        &odil::Element::as_binary, &odil::Element::as_binary);
}
