#define BOOST_TEST_MODULE Value
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Element.h"
#include "dcmtkpp/Exception.h"

BOOST_AUTO_TEST_CASE(Empty)
{
    dcmtkpp::Value const value;

    BOOST_CHECK(value.get_type() == dcmtkpp::Value::Type::Empty);
    BOOST_CHECK_THROW(value.as_integers(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_reals(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_strings(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_data_sets(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Integers)
{
    dcmtkpp::Value const value({1234});

    BOOST_CHECK(value.get_type() == dcmtkpp::Value::Type::Integers);
    BOOST_CHECK(value.as_integers() == dcmtkpp::Value::Integers({1234}));

    BOOST_CHECK_THROW(value.as_reals(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_strings(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_data_sets(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ModifyIntegers)
{
    dcmtkpp::Value value({1234});
    value.as_integers().push_back(5678);
    BOOST_CHECK(value.as_integers() == dcmtkpp::Value::Integers({1234, 5678}));
}

BOOST_AUTO_TEST_CASE(Reals)
{
    dcmtkpp::Value const value({12.34});

    BOOST_CHECK(value.get_type() == dcmtkpp::Value::Type::Reals);
    BOOST_CHECK(value.as_reals() == dcmtkpp::Value::Reals({12.34}));

    BOOST_CHECK_THROW(value.as_integers(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_strings(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_data_sets(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ModifyReals)
{
    dcmtkpp::Value value({12.34});
    value.as_reals().push_back(56.78);
    BOOST_CHECK(value.as_reals() == dcmtkpp::Value::Reals({12.34, 56.78}));
}

BOOST_AUTO_TEST_CASE(Strings)
{
    dcmtkpp::Value const value({"foo"});

    BOOST_CHECK(value.get_type() == dcmtkpp::Value::Type::Strings);
    BOOST_CHECK(value.as_strings() == dcmtkpp::Value::Strings({"foo"}));

    BOOST_CHECK_THROW(value.as_integers(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_reals(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_data_sets(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ModifyStrings)
{
    dcmtkpp::Value value({"foo"});
    value.as_strings().push_back("bar");
    BOOST_CHECK(value.as_strings() == dcmtkpp::Value::Strings({"foo", "bar"}));
}

BOOST_AUTO_TEST_CASE(DataSets)
{
    dcmtkpp::DataSet data_set;
    data_set.add("PatientID", {"DJ1234"});
    dcmtkpp::Value const value({data_set});

    BOOST_CHECK(value.get_type() == dcmtkpp::Value::Type::DataSets);
    BOOST_CHECK_EQUAL(value.as_data_sets().size(), 1);
    BOOST_CHECK(value.as_data_sets()[0].has("PatientID"));
    BOOST_CHECK(
        value.as_data_sets()[0].as_string("PatientID") ==
            dcmtkpp::Value::Strings({"DJ1234"}));

    BOOST_CHECK_THROW(value.as_integers(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_strings(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_reals(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ModifyDataSets)
{
    dcmtkpp::DataSet data_set;
    data_set.add("PatientID");
    data_set.as_string("PatientID").push_back("DJ1234");
    dcmtkpp::Value value({data_set});

    value.as_data_sets()[0].as_string("PatientID")[0] = "XXX";

    BOOST_CHECK(value.get_type() == dcmtkpp::Value::Type::DataSets);
    BOOST_CHECK_EQUAL(value.as_data_sets().size(), 1);
    BOOST_CHECK(value.as_data_sets()[0].has("PatientID"));
    BOOST_CHECK(
        value.as_data_sets()[0].as_string("PatientID") ==
            dcmtkpp::Value::Strings({"XXX"}));
}

BOOST_AUTO_TEST_CASE(EqualityEmpty)
{
    dcmtkpp::Value const value1;
    dcmtkpp::Value const value2;
    dcmtkpp::Value const value3((dcmtkpp::Value::Integers()));
    BOOST_CHECK(value1 == value2);
    BOOST_CHECK( ! (value1 == value3));
}

BOOST_AUTO_TEST_CASE(EqualityIntegers)
{
    dcmtkpp::Value const value1({1,2});
    dcmtkpp::Value const value2({1,2});
    dcmtkpp::Value const value3({3,4});
    dcmtkpp::Value const value4({3,4});
    BOOST_CHECK(value1 == value2);
    BOOST_CHECK( ! (value1 == value3));
    BOOST_CHECK( ! (value1 == value4));
}

BOOST_AUTO_TEST_CASE(EqualityReals)
{
    dcmtkpp::Value const value1({1,2});
    dcmtkpp::Value const value2({1,2});
    dcmtkpp::Value const value3({3,4});
    dcmtkpp::Value const value4({3,4});
    BOOST_CHECK(value1 == value2);
    BOOST_CHECK( ! (value1 == value3));
    BOOST_CHECK( ! (value1 == value4));
}

BOOST_AUTO_TEST_CASE(EqualityStrings)
{
    dcmtkpp::Value const value1({"1","2"});
    dcmtkpp::Value const value2({"1","2"});
    dcmtkpp::Value const value3({"3","4"});
    dcmtkpp::Value const value4({3,4});
    BOOST_CHECK(value1 == value2);
    BOOST_CHECK( ! (value1 == value3));
    BOOST_CHECK( ! (value1 == value4));
}

BOOST_AUTO_TEST_CASE(EqualityDataSets)
{
    dcmtkpp::DataSet dataset1;
    dataset1.add("PatientID", {"DJ1234"});
    dataset1.add("PixelSpacing", {1.5, 2.5});

    dcmtkpp::DataSet dataset2;
    dataset1.add("PatientName", {"Doe^John"});
    dataset1.add("PatientAge", {"042Y"});

    dcmtkpp::Value const value1({dataset1});
    dcmtkpp::Value const value2({dataset1});
    dcmtkpp::Value const value3({dataset2});
    dcmtkpp::Value const value4({3,4});
    BOOST_CHECK(value1 == value2);
    BOOST_CHECK( ! (value1 == value3));
    BOOST_CHECK( ! (value1 == value4));
}

BOOST_AUTO_TEST_CASE(DifferenceEmpty)
{
    dcmtkpp::Value const value1;
    dcmtkpp::Value const value2;
    dcmtkpp::Value const value3((dcmtkpp::Value::Integers()));
    BOOST_CHECK(! (value1 != value2));
    BOOST_CHECK(value1 != value3);
}

BOOST_AUTO_TEST_CASE(DifferenceIntegers)
{
    dcmtkpp::Value const value1({1,2});
    dcmtkpp::Value const value2({1,2});
    dcmtkpp::Value const value3({3,4});
    dcmtkpp::Value const value4({3,4});
    BOOST_CHECK(! (value1 != value2));
    BOOST_CHECK(value1 != value3);
    BOOST_CHECK(value1 != value4);
}

BOOST_AUTO_TEST_CASE(DifferenceReals)
{
    dcmtkpp::Value const value1({1.,2.});
    dcmtkpp::Value const value2({1.,2.});
    dcmtkpp::Value const value3({3.,4.});
    dcmtkpp::Value const value4({3,4});
    BOOST_CHECK(! (value1 != value2));
    BOOST_CHECK(value1 != value3);
    BOOST_CHECK(value1 != value4);
}

BOOST_AUTO_TEST_CASE(DifferenceStrings)
{
    dcmtkpp::Value const value1({"1","2"});
    dcmtkpp::Value const value2({"1","2"});
    dcmtkpp::Value const value3({"3","4"});
    dcmtkpp::Value const value4({3,4});
    BOOST_CHECK(! (value1 != value2));
    BOOST_CHECK(value1 != value3);
    BOOST_CHECK(value1 != value4);
}

BOOST_AUTO_TEST_CASE(DifferenceDataSets)
{
    dcmtkpp::DataSet dataset1;
    dataset1.add("PatientID", {"DJ1234"});
    dataset1.add("PixelSpacing", {1.5, 2.5});

    dcmtkpp::DataSet dataset2;
    dataset1.add("PatientName", {"Doe^John"});
    dataset1.add("PatientAge", {"042Y"});

    dcmtkpp::Value const value1({dataset1});
    dcmtkpp::Value const value2({dataset1});
    dcmtkpp::Value const value3({dataset2});
    dcmtkpp::Value const value4({3,4});
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
    dcmtkpp::Value const value;
    BOOST_CHECK_THROW(
        dcmtkpp::apply_visitor(Visitor(), value),
        dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(VisitorIntegers)
{
    dcmtkpp::Value const value({1234});
    BOOST_REQUIRE_EQUAL(
        dcmtkpp::apply_visitor(Visitor(), value),
        typeid(dcmtkpp::Value::Integers).name());
}

BOOST_AUTO_TEST_CASE(VisitorReals)
{
    dcmtkpp::Value const value({12.34});
    BOOST_REQUIRE_EQUAL(
        dcmtkpp::apply_visitor(Visitor(), value),
        typeid(dcmtkpp::Value::Reals).name());
}

BOOST_AUTO_TEST_CASE(VisitorStrings)
{
    dcmtkpp::Value const value({"foo"});
    BOOST_REQUIRE_EQUAL(
        dcmtkpp::apply_visitor(Visitor(), value),
        typeid(dcmtkpp::Value::Strings).name());
}

BOOST_AUTO_TEST_CASE(VisitorDataSets)
{
    dcmtkpp::Value const value({dcmtkpp::DataSet()});
    BOOST_REQUIRE_EQUAL(
        dcmtkpp::apply_visitor(Visitor(), value),
        typeid(dcmtkpp::Value::DataSets).name());
}

BOOST_AUTO_TEST_CASE(VisitorBinary)
{
    dcmtkpp::Value const value((dcmtkpp::Value::Binary()));
    BOOST_REQUIRE_EQUAL(
        dcmtkpp::apply_visitor(Visitor(), value),
        typeid(dcmtkpp::Value::Binary).name());
}
