#define BOOST_TEST_MODULE json_converter
#include <boost/test/unit_test.hpp>

#include <set>
#include <string>
#include <vector>

#include <jsoncpp/json/json.h>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Element.h"
#include "dcmtkpp/json_converter.h"
#include "dcmtkpp/Value.h"
#include "dcmtkpp/VR.h"

BOOST_AUTO_TEST_CASE(Empty)
{
    dcmtkpp::DataSet data_set;
    auto const json = dcmtkpp::to_json(data_set);
    BOOST_REQUIRE(json.empty());
}

template<typename TChecker, typename TValue>
void check_json_array(Json::Value const & object, TChecker checker, TValue const & expected)
{
    BOOST_REQUIRE(object.isArray());
    BOOST_REQUIRE_EQUAL(object.size(), expected.size());
    for(Json::ArrayIndex i=0; i<object.size(); ++i)
    {
        BOOST_REQUIRE((object[i].*checker)());
        BOOST_REQUIRE_EQUAL(object[i], expected[i]);
    }
}

void check_json_object(Json::Value const & object,
    std::set<std::string> const & expected_members)
{
    BOOST_REQUIRE(object.isObject());
    auto const members = object.getMemberNames();
    BOOST_REQUIRE(
        std::set<std::string>(members.begin(), members.end()) == expected_members);
}

void check_json_string(Json::Value const & object, std::string const & expected_value)
{
    BOOST_REQUIRE(object.isString());
    BOOST_REQUIRE_EQUAL(object.asString(), expected_value);
}

BOOST_AUTO_TEST_CASE(Integers)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0xdeadbeef,
        dcmtkpp::Element(dcmtkpp::Value::Integers({1, 2}), dcmtkpp::VR::SS));
    auto const json = dcmtkpp::to_json(data_set);
    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["vr"], "SS");
    check_json_array(json["deadbeef"]["Value"],
        &Json::Value::isInt, data_set.as_int(0xdeadbeef));
}

BOOST_AUTO_TEST_CASE(Reals)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0xdeadbeef,
        dcmtkpp::Element(dcmtkpp::Value::Reals({1.2, 3.4}), dcmtkpp::VR::FL));
    auto const json = dcmtkpp::to_json(data_set);
    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["vr"], "FL");
    check_json_array(json["deadbeef"]["Value"],
        &Json::Value::isDouble, data_set.as_real(0xdeadbeef));
}

BOOST_AUTO_TEST_CASE(Strings)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0xdeadbeef,
        dcmtkpp::Element(
            dcmtkpp::Value::Strings({"FOO", "BAR"}),
            dcmtkpp::VR::CS));
    auto const json = dcmtkpp::to_json(data_set);
    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["vr"], "CS");
    check_json_array(json["deadbeef"]["Value"],
        &Json::Value::isString, data_set.as_string(0xdeadbeef));
}

BOOST_AUTO_TEST_CASE(PersonName)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0xdeadbeef,
        dcmtkpp::Element(
            dcmtkpp::Value::Strings({"Alpha^Betic=Ideo^Graphic=Pho^Netic"}),
            dcmtkpp::VR::PN));
    auto const json = dcmtkpp::to_json(data_set);
    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["vr"], "PN");

    BOOST_REQUIRE(json["deadbeef"]["Value"].isArray());
    BOOST_REQUIRE_EQUAL(json["deadbeef"]["Value"].size(), 1);
    check_json_object(
        json["deadbeef"]["Value"][0], {"Alphabetic", "Ideographic", "Phonetic"});
    check_json_string(json["deadbeef"]["Value"][0]["Alphabetic"], {"Alpha^Betic"});
    check_json_string(json["deadbeef"]["Value"][0]["Ideographic"], {"Ideo^Graphic"});
    check_json_string(json["deadbeef"]["Value"][0]["Phonetic"], {"Pho^Netic"});
}

BOOST_AUTO_TEST_CASE(DataSets)
{
    dcmtkpp::DataSet item;
    item.add(0xbeeff00d,
        dcmtkpp::Element(dcmtkpp::Value::Integers({1,2}), dcmtkpp::VR::SS));
    dcmtkpp::DataSet data_set;
    data_set.add(0xdeadbeef,
        dcmtkpp::Element(
            dcmtkpp::Value::DataSets({item}),
            dcmtkpp::VR::SQ));

    auto const json = dcmtkpp::to_json(data_set);

    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["vr"], "SQ");

    BOOST_REQUIRE(json["deadbeef"]["Value"].isArray());
    BOOST_REQUIRE_EQUAL(json["deadbeef"]["Value"].size(), 1);
    check_json_object(json["deadbeef"]["Value"][0], {"beeff00d"});

    check_json_object(json["deadbeef"]["Value"][0]["beeff00d"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["Value"][0]["beeff00d"]["vr"], "SS");
    check_json_array(json["deadbeef"]["Value"][0]["beeff00d"]["Value"],
        &Json::Value::isInt, item.as_int(0xbeeff00d));
}

BOOST_AUTO_TEST_CASE(Binary)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0xdeadbeef,
        dcmtkpp::Element(
            dcmtkpp::Value::Binary({0x1, 0x2, 0x3, 0x4, 0x5}),
            dcmtkpp::VR::OB));

    auto const json = dcmtkpp::to_json(data_set);

    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "InlineBinary"});
    check_json_string(json["deadbeef"]["vr"], "OB");
    check_json_string(json["deadbeef"]["InlineBinary"], "AQIDBAU=");
}
