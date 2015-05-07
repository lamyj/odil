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
    dcmtkpp::Value const value(dcmtkpp::Value::Integers({1234}));

    BOOST_CHECK(value.get_type() == dcmtkpp::Value::Type::Integers);
    BOOST_CHECK(value.as_integers() == dcmtkpp::Value::Integers({1234}));

    BOOST_CHECK_THROW(value.as_reals(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_strings(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_data_sets(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ModifyIntegers)
{
    dcmtkpp::Value value(dcmtkpp::Value::Integers({1234}));
    value.as_integers().push_back(5678);
    BOOST_CHECK(value.as_integers() == dcmtkpp::Value::Integers({1234, 5678}));
}

BOOST_AUTO_TEST_CASE(Reals)
{
    dcmtkpp::Value const value(dcmtkpp::Value::Reals({12.34}));

    BOOST_CHECK(value.get_type() == dcmtkpp::Value::Type::Reals);
    BOOST_CHECK(value.as_reals() == dcmtkpp::Value::Reals({12.34}));

    BOOST_CHECK_THROW(value.as_integers(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_strings(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_data_sets(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ModifyReals)
{
    dcmtkpp::Value value(dcmtkpp::Value::Reals({12.34}));
    value.as_reals().push_back(56.78);
    BOOST_CHECK(value.as_reals() == dcmtkpp::Value::Reals({12.34, 56.78}));
}

BOOST_AUTO_TEST_CASE(Strings)
{
    dcmtkpp::Value const value(dcmtkpp::Value::Strings({"foo"}));

    BOOST_CHECK(value.get_type() == dcmtkpp::Value::Type::Strings);
    BOOST_CHECK(value.as_strings() == dcmtkpp::Value::Strings({"foo"}));

    BOOST_CHECK_THROW(value.as_integers(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_reals(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(value.as_data_sets(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(ModifyStrings)
{
    dcmtkpp::Value value(dcmtkpp::Value::Strings({"foo"}));
    value.as_strings().push_back("bar");
    BOOST_CHECK(value.as_strings() == dcmtkpp::Value::Strings({"foo", "bar"}));
}

BOOST_AUTO_TEST_CASE(DataSets)
{
    dcmtkpp::DataSet data_set;
    data_set.add("PatientID");
    data_set.as_string("PatientID").push_back("DJ1234");
    dcmtkpp::Value const value(dcmtkpp::Value::DataSets({data_set}));

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
    dcmtkpp::Value value(dcmtkpp::Value::DataSets({data_set}));

    value.as_data_sets()[0].as_string("PatientID")[0] = "XXX";

    BOOST_CHECK(value.get_type() == dcmtkpp::Value::Type::DataSets);
    BOOST_CHECK_EQUAL(value.as_data_sets().size(), 1);
    BOOST_CHECK(value.as_data_sets()[0].has("PatientID"));
    BOOST_CHECK(
        value.as_data_sets()[0].as_string("PatientID") ==
            dcmtkpp::Value::Strings({"XXX"}));
}
