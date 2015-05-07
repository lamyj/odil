#define BOOST_TEST_MODULE Element
#include <boost/test/unit_test.hpp>

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
    dcmtkpp::Element element((std::vector<int64_t>()));
    BOOST_CHECK(element.is_int());

    std::vector<int64_t> const & value = element.as_int();
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(ModifyInt)
{
    dcmtkpp::Element element((std::vector<int64_t>()));
    element.as_int().push_back(1);

    BOOST_CHECK(!element.empty());
    BOOST_CHECK_EQUAL(element.size(), 1);

    std::vector<int64_t> const & value = element.as_int();
    BOOST_CHECK_EQUAL(value.size(), 1);
    BOOST_CHECK_EQUAL(value[0], 1);
}

BOOST_AUTO_TEST_CASE(IntWrong)
{
    dcmtkpp::Element element((std::vector<int64_t>()));
    BOOST_CHECK_THROW(element.as_real(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(element.as_string(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Double)
{
    dcmtkpp::Element element((std::vector<double>()));
    BOOST_CHECK(element.is_real());

    std::vector<double> const & value = element.as_real();
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(ModifyDouble)
{
    dcmtkpp::Element element((std::vector<double>()));
    element.as_real().push_back(1.5);

    BOOST_CHECK(!element.empty());
    BOOST_CHECK_EQUAL(element.size(), 1);

    std::vector<double> const & value = element.as_real();
    BOOST_CHECK_EQUAL(value.size(), 1);
    BOOST_CHECK_EQUAL(value[0], 1.5);
}

BOOST_AUTO_TEST_CASE(DoubleWrong)
{
    dcmtkpp::Element element((std::vector<double>()));
    BOOST_CHECK_THROW(element.as_int(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(element.as_string(), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(String)
{
    dcmtkpp::Element element((std::vector<std::string>()));
    BOOST_CHECK(element.is_string());

    std::vector<std::string> const & value = element.as_string();
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(ModifyString)
{
    dcmtkpp::Element element((std::vector<std::string>()));
    element.as_string().push_back("foo");

    BOOST_CHECK(!element.empty());
    BOOST_CHECK_EQUAL(element.size(), 1);

    std::vector<std::string> const & value = element.as_string();
    BOOST_CHECK_EQUAL(value.size(), 1);
    BOOST_CHECK_EQUAL(value[0], "foo");
}

BOOST_AUTO_TEST_CASE(StringWrong)
{
    dcmtkpp::Element element((std::vector<std::string>()));
    BOOST_CHECK_THROW(element.as_int(), dcmtkpp::Exception);
    BOOST_CHECK_THROW(element.as_real(), dcmtkpp::Exception);
}
