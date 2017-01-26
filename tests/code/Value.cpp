#define BOOST_TEST_MODULE Value
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/Value.h"

template<typename TContainer>
void test_contents(
    odil::Value const & value,
    TContainer const & contents, odil::Value::Type type,
    TContainer const & (odil::Value::*getter)() const)
{
    BOOST_CHECK(value.get_type() == type);
    BOOST_CHECK_EQUAL(value.empty(), contents.empty());
    BOOST_CHECK_EQUAL(value.size(), contents.size());
    BOOST_CHECK((value.*getter)() == contents);

    if(type != odil::Value::Type::Integers)
    {
        BOOST_CHECK_THROW(value.as_integers(), odil::Exception);
    }
    if(type != odil::Value::Type::Reals)
    {
        BOOST_CHECK_THROW(value.as_reals(), odil::Exception);
    }
    if(type != odil::Value::Type::Strings)
    {
        BOOST_CHECK_THROW(value.as_strings(), odil::Exception);
    }
    if(type != odil::Value::Type::DataSets)
    {
        BOOST_CHECK_THROW(value.as_data_sets(), odil::Exception);
    }
    if(type != odil::Value::Type::Binary)
    {
        BOOST_CHECK_THROW(value.as_binary(), odil::Exception);
    }
}

template<typename TContainer>
void test_container(
    TContainer const & contents, odil::Value::Type type, 
    TContainer const & (odil::Value::*getter)() const)
{
    odil::Value const value(contents);
    test_contents(value, contents, type, getter);
}

template<typename TContainer>
void test_initializer_list(
    std::initializer_list<typename TContainer::value_type> const & contents,
    odil::Value::Type type, 
    TContainer const & (odil::Value::*getter)() const)
{
    odil::Value const value(contents);
    test_contents(value, TContainer(contents), type, getter);
}

template<typename TContainer>
void test_modify(
    TContainer const & contents,
    TContainer const & (odil::Value::*getter)() const,
    TContainer & (odil::Value::*setter)())
{
    odil::Value value(TContainer{{contents[0]}});
    (value.*setter)().push_back(contents[1]);
    BOOST_CHECK((value.*getter)() == contents);
}

template<typename TContainer>
void test_clear(TContainer const & contents, odil::Value::Type type) 
{
    odil::Value value(contents);
    value.clear();
    BOOST_CHECK(value.get_type() == type);
    BOOST_CHECK(value.empty());
}

template<typename TContainer>
void test_equality(
    TContainer const & contents_1, TContainer const & contents_2)
{
    odil::Value const value_1(contents_1);
    odil::Value const value_2(contents_1);
    odil::Value const value_3(contents_2);
    odil::Value const value_4(contents_2);

    BOOST_CHECK(value_1 == value_2);
    BOOST_CHECK( ! (value_1 == value_3));
    BOOST_CHECK( ! (value_1 == value_4));

    BOOST_CHECK(! (value_1 != value_2));
    BOOST_CHECK(value_1 != value_3);
    BOOST_CHECK(value_1 != value_4);
}

struct Visitor
{
    typedef std::string result_type;

    template<typename T>
    result_type operator()(T const & container) const
    {
        return typeid(container).name();
    }
};

template<typename TContainer>
void test_visitor(
    TContainer const & contents)
{
    odil::Value const value(contents);
    BOOST_REQUIRE_EQUAL(
        odil::apply_visitor(Visitor(), value),
        typeid(TContainer).name());
}

template<typename TContainer>
void test(
    std::initializer_list<typename TContainer::value_type> const & contents,
    std::initializer_list<typename TContainer::value_type> const & other_contents,
    odil::Value::Type type, 
    TContainer const & (odil::Value::*getter)() const,
    TContainer & (odil::Value::*setter)())
{
    TContainer const container(contents);
    TContainer const other_container(other_contents);

    test_container(TContainer(), type, getter);
    test_container(container, type, getter);
    test_initializer_list(contents, type, getter);

    test_modify(container, getter, setter);

    test_clear(container, type);

    test_equality(container, other_container);

    test_visitor(container);
}
 
BOOST_AUTO_TEST_CASE(Integers)
{
    test<odil::Value::Integers>(
        {1234, 5678}, {9012, 3456},
        odil::Value::Type::Integers,
        &odil::Value::as_integers, &odil::Value::as_integers);
}

BOOST_AUTO_TEST_CASE(Reals)
{
    test<odil::Value::Reals>(
        {12.34, 56.78}, {1., 2.},
        odil::Value::Type::Reals,
        &odil::Value::as_reals, &odil::Value::as_reals);
}

BOOST_AUTO_TEST_CASE(Strings)
{
    test<odil::Value::Strings>(
        {"foo", "bar"}, {"plip", "plop"},
        odil::Value::Type::Strings,
        &odil::Value::as_strings, &odil::Value::as_strings);
}

BOOST_AUTO_TEST_CASE(DataSets)
{
    odil::DataSet data_set_1;
    data_set_1.add("PatientID", {"DJ1234"});

    odil::DataSet data_set_2;
    data_set_2.add("EchoTime", {100});

    test<odil::Value::DataSets>(
        {data_set_1, data_set_2}, {data_set_2, data_set_1},
        odil::Value::Type::DataSets,
        &odil::Value::as_data_sets, &odil::Value::as_data_sets);
}

BOOST_AUTO_TEST_CASE(Binary)
{
    test<odil::Value::Binary>(
        {{0x1, 0x2}, {0x3}}, {{0x4}, {0x5, 0x6}},
        odil::Value::Type::Binary,
        &odil::Value::as_binary, &odil::Value::as_binary);
}
