#define BOOST_TEST_MODULE Element
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Element.h"
#include "dcmtkpp/Exception.h"

BOOST_AUTO_TEST_CASE(Empty)
{
    dcmtkpp::Element element;
    BOOST_CHECK(element.empty());
    BOOST_CHECK_EQUAL(element.size(), 0);
}

BOOST_AUTO_TEST_CASE(Int)
{
    dcmtkpp::Element const element((dcmtkpp::Value::Integers()));
    BOOST_CHECK(element.is_int());

    std::vector<int64_t> const & value = element.as_int();
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(ModifyInt)
{
    dcmtkpp::Element element((dcmtkpp::Value::Integers()));
    element.as_int().push_back(1);

    BOOST_CHECK(!element.empty());
    BOOST_CHECK_EQUAL(element.size(), 1);

    std::vector<int64_t> const & value = element.as_int();
    BOOST_CHECK_EQUAL(value.size(), 1);
    BOOST_CHECK_EQUAL(value[0], 1);
}

BOOST_AUTO_TEST_CASE(IntWrong)
{
    dcmtkpp::Element element((dcmtkpp::Value::Integers()));
    BOOST_CHECK_THROW(element.as_real(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(element.as_string(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Double)
{
    dcmtkpp::Element const element((dcmtkpp::Value::Reals()));
    BOOST_CHECK(element.is_real());

    std::vector<double> const & value = element.as_real();
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(ModifyDouble)
{
    dcmtkpp::Element element((dcmtkpp::Value::Reals()));
    element.as_real().push_back(1.5);

    BOOST_CHECK(!element.empty());
    BOOST_CHECK_EQUAL(element.size(), 1);

    std::vector<double> const & value = element.as_real();
    BOOST_CHECK_EQUAL(value.size(), 1);
    BOOST_CHECK_EQUAL(value[0], 1.5);
}

BOOST_AUTO_TEST_CASE(DoubleWrong)
{
    dcmtkpp::Element element((dcmtkpp::Value::Reals()));
    BOOST_CHECK_THROW(element.as_int(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(element.as_string(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(element.as_data_set(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(String)
{
    dcmtkpp::Element const element((dcmtkpp::Value::Strings()));
    BOOST_CHECK(element.is_string());

    std::vector<std::string> const & value = element.as_string();
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(ModifyString)
{
    dcmtkpp::Element element((dcmtkpp::Value::Strings()));
    element.as_string().push_back("foo");

    BOOST_CHECK(!element.empty());
    BOOST_CHECK_EQUAL(element.size(), 1);

    std::vector<std::string> const & value = element.as_string();
    BOOST_CHECK_EQUAL(value.size(), 1);
    BOOST_CHECK_EQUAL(value[0], "foo");
}

BOOST_AUTO_TEST_CASE(StringWrong)
{
    dcmtkpp::Element element((dcmtkpp::Value::Strings()));
    BOOST_CHECK_THROW(element.as_int(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(element.as_real(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(element.as_data_set(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(DataSet)
{
    dcmtkpp::Element const element((dcmtkpp::Value::DataSets()));
    BOOST_CHECK(element.is_data_set());

    dcmtkpp::Value::DataSets const & value = element.as_data_set();
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(ModifyDataSet)
{
    dcmtkpp::Element element((dcmtkpp::Value::DataSets()));

    dcmtkpp::DataSet data_set;
    data_set.add("PatientID");
    data_set.as_string("PatientID").push_back("DJ1234");
    element.as_data_set().push_back(data_set);

    BOOST_CHECK(!element.empty());
    BOOST_CHECK_EQUAL(element.size(), 1);

    dcmtkpp::Value::DataSets const & value = element.as_data_set();
    BOOST_CHECK_EQUAL(value.size(), 1);
    BOOST_CHECK_EQUAL(value[0].size(), 1);
    BOOST_CHECK(value[0].has("PatientID"));
    BOOST_CHECK(
        value[0].as_string("PatientID") == dcmtkpp::Value::Strings({"DJ1234"}));
}

BOOST_AUTO_TEST_CASE(DataSetWrong)
{
    dcmtkpp::Element element((dcmtkpp::Value::DataSets()));
    BOOST_CHECK_THROW(element.as_int(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(element.as_real(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(element.as_string(), dcmtkpp::Exception);
}
