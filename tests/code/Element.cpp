#define BOOST_TEST_MODULE Element
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/Element.h"
#include "odil/Exception.h"

BOOST_AUTO_TEST_CASE(Empty)
{
    odil::Element element;
    BOOST_CHECK(element.empty());
    BOOST_CHECK_EQUAL(element.size(), 0);
}

BOOST_AUTO_TEST_CASE(Int)
{
    odil::Element const element((odil::Value::Integers()));
    BOOST_CHECK(element.is_int());

    std::vector<int64_t> const & value = element.as_int();
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(ModifyInt)
{
    odil::Element element({0});
    element.as_int().push_back(1);

    BOOST_CHECK(!element.empty());
    BOOST_CHECK_EQUAL(element.size(), 2);

    std::vector<int64_t> const & value = element.as_int();
    BOOST_CHECK(value == odil::Value::Integers({0, 1}));
}

BOOST_AUTO_TEST_CASE(ModifyInt2)
{
    odil::Element element({odil::Value::Integer(0)});
    element.as_int().push_back(1);

    BOOST_CHECK(!element.empty());
    BOOST_CHECK_EQUAL(element.size(), 2);

    std::vector<int64_t> const & value = element.as_int();
    BOOST_CHECK(value == odil::Value::Integers({0, 1}));
}

BOOST_AUTO_TEST_CASE(IntWrong)
{
    odil::Element element((odil::Value::Integers()));
    BOOST_CHECK_THROW(element.as_real(), odil::Exception);
    BOOST_CHECK_THROW(element.as_string(), odil::Exception);
}

BOOST_AUTO_TEST_CASE(Double)
{
    odil::Element const element((odil::Value::Reals()));
    BOOST_CHECK(element.is_real());

    std::vector<double> const & value = element.as_real();
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(ModifyDouble)
{
    odil::Element element({0.});
    element.as_real().push_back(1.5);

    BOOST_CHECK(!element.empty());
    BOOST_CHECK_EQUAL(element.size(), 2);

    std::vector<double> const & value = element.as_real();
    BOOST_CHECK(value == odil::Value::Reals({0., 1.5}));
}

BOOST_AUTO_TEST_CASE(DoubleWrong)
{
    odil::Element element((odil::Value::Reals()));
    BOOST_CHECK_THROW(element.as_int(), odil::Exception);
    BOOST_CHECK_THROW(element.as_string(), odil::Exception);
    BOOST_CHECK_THROW(element.as_data_set(), odil::Exception);
}

BOOST_AUTO_TEST_CASE(String)
{
    odil::Element const element((odil::Value::Strings()));
    BOOST_CHECK(element.is_string());

    std::vector<std::string> const & value = element.as_string();
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(ModifyString)
{
    odil::Element element({""});
    element.as_string().push_back("foo");

    BOOST_CHECK(!element.empty());
    BOOST_CHECK_EQUAL(element.size(), 2);

    std::vector<std::string> const & value = element.as_string();
    BOOST_CHECK(value == odil::Value::Strings({"", "foo"}));
}

BOOST_AUTO_TEST_CASE(StringWrong)
{
    odil::Element element((odil::Value::Strings()));
    BOOST_CHECK_THROW(element.as_int(), odil::Exception);
    BOOST_CHECK_THROW(element.as_real(), odil::Exception);
    BOOST_CHECK_THROW(element.as_data_set(), odil::Exception);
}

BOOST_AUTO_TEST_CASE(DataSet)
{
    odil::Element const element((odil::Value::DataSets()));
    BOOST_CHECK(element.is_data_set());

    odil::Value::DataSets const & value = element.as_data_set();
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(ModifyDataSet)
{
    odil::Element element((odil::Value::DataSets()));

    odil::DataSet data_set;
    data_set.add("PatientID");
    data_set.as_string("PatientID").push_back("DJ1234");
    element.as_data_set().push_back(data_set);

    BOOST_CHECK(!element.empty());
    BOOST_CHECK_EQUAL(element.size(), 1);

    odil::Value::DataSets const & value = element.as_data_set();
    BOOST_CHECK_EQUAL(value.size(), 1);
    BOOST_CHECK_EQUAL(value[0].size(), 1);
    BOOST_CHECK(value[0].has("PatientID"));
    BOOST_CHECK(
        value[0].as_string("PatientID") == odil::Value::Strings({"DJ1234"}));
}

BOOST_AUTO_TEST_CASE(DataSetWrong)
{
    odil::Element element((odil::Value::DataSets()));
    BOOST_CHECK_THROW(element.as_int(), odil::Exception);
    BOOST_CHECK_THROW(element.as_real(), odil::Exception);
    BOOST_CHECK_THROW(element.as_string(), odil::Exception);
}

BOOST_AUTO_TEST_CASE(Equality)
{
    odil::Element const element1({12,34}, odil::VR::US);
    odil::Element const element2({12,34}, odil::VR::US);
    odil::Element const element3({12.,34.}, odil::VR::FL);
    odil::Element const element4({12,34}, odil::VR::UL);

    BOOST_CHECK(element1 == element2);
    BOOST_CHECK(! (element1 == element3));
    BOOST_CHECK(! (element1 == element4));
}

BOOST_AUTO_TEST_CASE(Difference)
{
    odil::Element const element1({12,34}, odil::VR::US);
    odil::Element const element2({12,34}, odil::VR::US);
    odil::Element const element3({12.,34.}, odil::VR::FL);
    odil::Element const element4({12,34}, odil::VR::UL);

    BOOST_CHECK(! (element1 != element2));
    BOOST_CHECK(element1 != element3);
    BOOST_CHECK(element1 != element4);
}

BOOST_AUTO_TEST_CASE(Clear)
{
    odil::Element element({1234});
    element.clear();
    BOOST_CHECK(element.empty());
}
