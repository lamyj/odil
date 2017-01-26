#define BOOST_TEST_MODULE Value
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/Element.h"
#include "odil/Exception.h"

BOOST_AUTO_TEST_CASE(Empty)
{
    odil::Value const value;

    BOOST_CHECK(value.get_type() == odil::Value::Type::Empty);
    BOOST_CHECK_THROW(value.as_integers(), odil::Exception);
    BOOST_CHECK_THROW(value.as_reals(), odil::Exception);
    BOOST_CHECK_THROW(value.as_strings(), odil::Exception);
    BOOST_CHECK_THROW(value.as_data_sets(), odil::Exception);
}

BOOST_AUTO_TEST_CASE(Integers)
{
    odil::Value const value({1234});

    BOOST_CHECK(value.get_type() == odil::Value::Type::Integers);
    BOOST_CHECK(value.as_integers() == odil::Value::Integers({1234}));

    BOOST_CHECK_THROW(value.as_reals(), odil::Exception);
    BOOST_CHECK_THROW(value.as_strings(), odil::Exception);
    BOOST_CHECK_THROW(value.as_data_sets(), odil::Exception);
}

BOOST_AUTO_TEST_CASE(ModifyIntegers)
{
    odil::Value value({1234});
    value.as_integers().push_back(5678);
    BOOST_CHECK(value.as_integers() == odil::Value::Integers({1234, 5678}));
}

BOOST_AUTO_TEST_CASE(Reals)
{
    odil::Value const value({12.34});

    BOOST_CHECK(value.get_type() == odil::Value::Type::Reals);
    BOOST_CHECK(value.as_reals() == odil::Value::Reals({12.34}));

    BOOST_CHECK_THROW(value.as_integers(), odil::Exception);
    BOOST_CHECK_THROW(value.as_strings(), odil::Exception);
    BOOST_CHECK_THROW(value.as_data_sets(), odil::Exception);
}

BOOST_AUTO_TEST_CASE(ModifyReals)
{
    odil::Value value({12.34});
    value.as_reals().push_back(56.78);
    BOOST_CHECK(value.as_reals() == odil::Value::Reals({12.34, 56.78}));
}

BOOST_AUTO_TEST_CASE(Strings)
{
    odil::Value const value({"foo"});

    BOOST_CHECK(value.get_type() == odil::Value::Type::Strings);
    BOOST_CHECK(value.as_strings() == odil::Value::Strings({"foo"}));

    BOOST_CHECK_THROW(value.as_integers(), odil::Exception);
    BOOST_CHECK_THROW(value.as_reals(), odil::Exception);
    BOOST_CHECK_THROW(value.as_data_sets(), odil::Exception);
}

BOOST_AUTO_TEST_CASE(ModifyStrings)
{
    odil::Value value({"foo"});
    value.as_strings().push_back("bar");
    BOOST_CHECK(value.as_strings() == odil::Value::Strings({"foo", "bar"}));
}

BOOST_AUTO_TEST_CASE(DataSets)
{
    odil::DataSet data_set;
    data_set.add("PatientID", {"DJ1234"});
    odil::Value const value({data_set});

    BOOST_CHECK(value.get_type() == odil::Value::Type::DataSets);
    BOOST_CHECK_EQUAL(value.as_data_sets().size(), 1);
    BOOST_CHECK(value.as_data_sets()[0].has("PatientID"));
    BOOST_CHECK(
        value.as_data_sets()[0].as_string("PatientID") ==
            odil::Value::Strings({"DJ1234"}));

    BOOST_CHECK_THROW(value.as_integers(), odil::Exception);
    BOOST_CHECK_THROW(value.as_strings(), odil::Exception);
    BOOST_CHECK_THROW(value.as_reals(), odil::Exception);
}

BOOST_AUTO_TEST_CASE(ModifyDataSets)
{
    odil::DataSet data_set;
    data_set.add("PatientID");
    data_set.as_string("PatientID").push_back("DJ1234");
    odil::Value value({data_set});

    value.as_data_sets()[0].as_string("PatientID")[0] = "XXX";

    BOOST_CHECK(value.get_type() == odil::Value::Type::DataSets);
    BOOST_CHECK_EQUAL(value.as_data_sets().size(), 1);
    BOOST_CHECK(value.as_data_sets()[0].has("PatientID"));
    BOOST_CHECK(
        value.as_data_sets()[0].as_string("PatientID") ==
            odil::Value::Strings({"XXX"}));
}

BOOST_AUTO_TEST_CASE(EqualityEmpty)
{
    odil::Value const value1;
    odil::Value const value2;
    odil::Value const value3((odil::Value::Integers()));
    BOOST_CHECK(value1 == value2);
    BOOST_CHECK( ! (value1 == value3));
}

BOOST_AUTO_TEST_CASE(EqualityIntegers)
{
    odil::Value const value1({1,2});
    odil::Value const value2({1,2});
    odil::Value const value3({3,4});
    odil::Value const value4({3,4});
    BOOST_CHECK(value1 == value2);
    BOOST_CHECK( ! (value1 == value3));
    BOOST_CHECK( ! (value1 == value4));
}

BOOST_AUTO_TEST_CASE(EqualityReals)
{
    odil::Value const value1({1,2});
    odil::Value const value2({1,2});
    odil::Value const value3({3,4});
    odil::Value const value4({3,4});
    BOOST_CHECK(value1 == value2);
    BOOST_CHECK( ! (value1 == value3));
    BOOST_CHECK( ! (value1 == value4));
}

BOOST_AUTO_TEST_CASE(EqualityStrings)
{
    odil::Value const value1({"1","2"});
    odil::Value const value2({"1","2"});
    odil::Value const value3({"3","4"});
    odil::Value const value4({3,4});
    BOOST_CHECK(value1 == value2);
    BOOST_CHECK( ! (value1 == value3));
    BOOST_CHECK( ! (value1 == value4));
}

BOOST_AUTO_TEST_CASE(EqualityDataSets)
{
    odil::DataSet dataset1;
    dataset1.add("PatientID", {"DJ1234"});
    dataset1.add("PixelSpacing", {1.5, 2.5});

    odil::DataSet dataset2;
    dataset1.add("PatientName", {"Doe^John"});
    dataset1.add("PatientAge", {"042Y"});

    odil::Value const value1({dataset1});
    odil::Value const value2({dataset1});
    odil::Value const value3({dataset2});
    odil::Value const value4({3,4});
    BOOST_CHECK(value1 == value2);
    BOOST_CHECK( ! (value1 == value3));
    BOOST_CHECK( ! (value1 == value4));
}

BOOST_AUTO_TEST_CASE(DifferenceEmpty)
{
    odil::Value const value1;
    odil::Value const value2;
    odil::Value const value3((odil::Value::Integers()));
    BOOST_CHECK(! (value1 != value2));
    BOOST_CHECK(value1 != value3);
}

BOOST_AUTO_TEST_CASE(DifferenceIntegers)
{
    odil::Value const value1({1,2});
    odil::Value const value2({1,2});
    odil::Value const value3({3,4});
    odil::Value const value4({3,4});
    BOOST_CHECK(! (value1 != value2));
    BOOST_CHECK(value1 != value3);
    BOOST_CHECK(value1 != value4);
}

BOOST_AUTO_TEST_CASE(DifferenceReals)
{
    odil::Value const value1({1.,2.});
    odil::Value const value2({1.,2.});
    odil::Value const value3({3.,4.});
    odil::Value const value4({3,4});
    BOOST_CHECK(! (value1 != value2));
    BOOST_CHECK(value1 != value3);
    BOOST_CHECK(value1 != value4);
}

BOOST_AUTO_TEST_CASE(DifferenceStrings)
{
    odil::Value const value1({"1","2"});
    odil::Value const value2({"1","2"});
    odil::Value const value3({"3","4"});
    odil::Value const value4({3,4});
    BOOST_CHECK(! (value1 != value2));
    BOOST_CHECK(value1 != value3);
    BOOST_CHECK(value1 != value4);
}

BOOST_AUTO_TEST_CASE(DifferenceDataSets)
{
    odil::DataSet dataset1;
    dataset1.add("PatientID", {"DJ1234"});
    dataset1.add("PixelSpacing", {1.5, 2.5});

    odil::DataSet dataset2;
    dataset2.add("PatientName", {"Doe^John"});
    dataset2.add("PatientAge", {"042Y"});

    odil::Value const value1({dataset1});
    odil::Value const value2({dataset1});
    odil::Value const value3({dataset2});
    odil::Value const value4({3,4});
    BOOST_CHECK(! (value1 != value2));
    BOOST_CHECK(value1 != value3);
    BOOST_CHECK(value1 != value4);
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

BOOST_AUTO_TEST_CASE(VisitorEmpty)
{
    odil::Value const value;
    BOOST_CHECK_THROW(
        odil::apply_visitor(Visitor(), value),
        odil::Exception);
}

BOOST_AUTO_TEST_CASE(VisitorIntegers)
{
    odil::Value const value({1234});
    BOOST_REQUIRE_EQUAL(
        odil::apply_visitor(Visitor(), value),
        typeid(odil::Value::Integers).name());
}

BOOST_AUTO_TEST_CASE(VisitorReals)
{
    odil::Value const value({12.34});
    BOOST_REQUIRE_EQUAL(
        odil::apply_visitor(Visitor(), value),
        typeid(odil::Value::Reals).name());
}

BOOST_AUTO_TEST_CASE(VisitorStrings)
{
    odil::Value const value({"foo"});
    BOOST_REQUIRE_EQUAL(
        odil::apply_visitor(Visitor(), value),
        typeid(odil::Value::Strings).name());
}

BOOST_AUTO_TEST_CASE(VisitorDataSets)
{
    odil::Value const value({odil::DataSet()});
    BOOST_REQUIRE_EQUAL(
        odil::apply_visitor(Visitor(), value),
        typeid(odil::Value::DataSets).name());
}

BOOST_AUTO_TEST_CASE(VisitorBinary)
{
    odil::Value const value((odil::Value::Binary()));
    BOOST_REQUIRE_EQUAL(
        odil::apply_visitor(Visitor(), value),
        typeid(odil::Value::Binary).name());
}
