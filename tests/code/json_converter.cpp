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

BOOST_AUTO_TEST_CASE(AsJSONEmpty)
{
    dcmtkpp::DataSet data_set;
    auto const json = dcmtkpp::as_json(data_set);
    BOOST_REQUIRE(json.empty());
}

template<typename TChecker, typename TGetter, typename TValue>
void check_json_array(
    Json::Value const & object, TChecker checker, TGetter getter,
    TValue const & expected)
{
    BOOST_REQUIRE(object.isArray());
    BOOST_REQUIRE_EQUAL(object.size(), expected.size());
    for(Json::ArrayIndex i=0; i<object.size(); ++i)
    {
        BOOST_REQUIRE((object[i].*checker)());
        BOOST_REQUIRE_EQUAL((object[i].*getter)(), expected[i]);
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

BOOST_AUTO_TEST_CASE(AsJSONIntegers)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0xdeadbeef,
        dcmtkpp::Element(dcmtkpp::Value::Integers({1, 2}), dcmtkpp::VR::SS));
    auto const json = dcmtkpp::as_json(data_set);
    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["vr"], "SS");
    check_json_array(json["deadbeef"]["Value"],
        &Json::Value::isInt, &Json::Value::asInt, data_set.as_int(0xdeadbeef));
}

BOOST_AUTO_TEST_CASE(AsJSONReals)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0xdeadbeef,
        dcmtkpp::Element(dcmtkpp::Value::Reals({1.2, 3.4}), dcmtkpp::VR::FL));
    auto const json = dcmtkpp::as_json(data_set);
    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["vr"], "FL");
    check_json_array(json["deadbeef"]["Value"],
        &Json::Value::isDouble, &Json::Value::asDouble, data_set.as_real(0xdeadbeef));
}

BOOST_AUTO_TEST_CASE(AsJSONStrings)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0xdeadbeef,
        dcmtkpp::Element(
            dcmtkpp::Value::Strings({"FOO", "BAR"}),
            dcmtkpp::VR::CS));
    auto const json = dcmtkpp::as_json(data_set);
    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["vr"], "CS");
    check_json_array(json["deadbeef"]["Value"],
        &Json::Value::isString, &Json::Value::asString, data_set.as_string(0xdeadbeef));
}

BOOST_AUTO_TEST_CASE(AsJSONPersonName)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0xdeadbeef,
        dcmtkpp::Element(
            dcmtkpp::Value::Strings({"Alpha^Betic=Ideo^Graphic=Pho^Netic"}),
            dcmtkpp::VR::PN));
    auto const json = dcmtkpp::as_json(data_set);
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

BOOST_AUTO_TEST_CASE(AsJSONDataSets)
{
    dcmtkpp::DataSet item;
    item.add(0xbeeff00d,
        dcmtkpp::Element(dcmtkpp::Value::Integers({1,2}), dcmtkpp::VR::SS));
    dcmtkpp::DataSet data_set;
    data_set.add(0xdeadbeef,
        dcmtkpp::Element(
            dcmtkpp::Value::DataSets({item}),
            dcmtkpp::VR::SQ));

    auto const json = dcmtkpp::as_json(data_set);

    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["vr"], "SQ");

    BOOST_REQUIRE(json["deadbeef"]["Value"].isArray());
    BOOST_REQUIRE_EQUAL(json["deadbeef"]["Value"].size(), 1);
    check_json_object(json["deadbeef"]["Value"][0], {"beeff00d"});

    check_json_object(json["deadbeef"]["Value"][0]["beeff00d"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["Value"][0]["beeff00d"]["vr"], "SS");
    check_json_array(json["deadbeef"]["Value"][0]["beeff00d"]["Value"],
        &Json::Value::isInt, &Json::Value::asInt, item.as_int(0xbeeff00d));
}

BOOST_AUTO_TEST_CASE(AsJSONBinary)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0xdeadbeef,
        dcmtkpp::Element(
            dcmtkpp::Value::Binary({0x1, 0x2, 0x3, 0x4, 0x5}),
            dcmtkpp::VR::OB));

    auto const json = dcmtkpp::as_json(data_set);

    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "InlineBinary"});
    check_json_string(json["deadbeef"]["vr"], "OB");
    check_json_string(json["deadbeef"]["InlineBinary"], "AQIDBAU=");
}

BOOST_AUTO_TEST_CASE(AsDataSetEmpty)
{
    std::stringstream data;
    data << "{ }";
    Json::Value json;
    data >> json;

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(json);
    BOOST_REQUIRE(data_set.empty());
}

BOOST_AUTO_TEST_CASE(AsDataSetIntegers)
{
    std::stringstream data;
    data << "{ \"deadbeef\": { \"vr\": \"SS\", \"Value\": [1, 2] } }";
    Json::Value json;
    data >> json;

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(json);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("deadbeef"));
    BOOST_REQUIRE(data_set.get_vr("deadbeef") == dcmtkpp::VR::SS);
    BOOST_REQUIRE(data_set.is_int("deadbeef"));
    BOOST_REQUIRE(data_set.as_int("deadbeef") == dcmtkpp::Value::Integers({1, 2}));
}

BOOST_AUTO_TEST_CASE(AsDataSetReals)
{
    std::stringstream data;
    data << "{ \"deadbeef\": { \"vr\": \"FL\", \"Value\": [1.2, 3.4] } }";
    Json::Value json;
    data >> json;

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(json);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("deadbeef"));
    BOOST_REQUIRE(data_set.get_vr("deadbeef") == dcmtkpp::VR::FL);
    BOOST_REQUIRE(data_set.is_real("deadbeef"));
    BOOST_REQUIRE(data_set.as_real("deadbeef") == dcmtkpp::Value::Reals({1.2, 3.4}));
}

BOOST_AUTO_TEST_CASE(AsDataSetStrings)
{
    std::stringstream data;
    data << "{ \"deadbeef\": { \"vr\": \"CS\", \"Value\": [\"FOO\", \"BAR\"] } }";
    Json::Value json;
    data >> json;

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(json);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("deadbeef"));
    BOOST_REQUIRE(data_set.get_vr("deadbeef") == dcmtkpp::VR::CS);
    BOOST_REQUIRE(data_set.is_string("deadbeef"));
    BOOST_REQUIRE(data_set.as_string("deadbeef") == dcmtkpp::Value::Strings({"FOO", "BAR"}));
}

BOOST_AUTO_TEST_CASE(AsDataSetPersonName)
{
    std::stringstream data;
    data << "{ \"deadbeef\": { \"vr\": \"PN\", \"Value\": [ ";
    data << "{ \"Alphabetic\": \"Alpha^Betic\" , ";
    data << "\"Ideographic\": \"Ideo^Graphic\" , ";
    data << "\"Phonetic\": \"Pho^Netic\" } ";
    data << " ] } }";
    Json::Value json;
    data >> json;

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(json);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("deadbeef"));
    BOOST_REQUIRE(data_set.get_vr("deadbeef") == dcmtkpp::VR::PN);
    BOOST_REQUIRE(data_set.is_string("deadbeef"));
    BOOST_REQUIRE(data_set.as_string("deadbeef") == dcmtkpp::Value::Strings(
        {"Alpha^Betic=Ideo^Graphic=Pho^Netic"}));
}

BOOST_AUTO_TEST_CASE(AsDataSetDataSets)
{
    std::stringstream data;
    data << "{ \"deadbeef\": { \"vr\": \"SQ\", \"Value\": [ ";
    data << "{ \"beeff00d\": { \"vr\": \"SS\", \"Value\": [1, 2] } }";
    data << " ] } }";
    Json::Value json;
    data >> json;

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(json);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("deadbeef"));
    BOOST_REQUIRE(data_set.get_vr("deadbeef") == dcmtkpp::VR::SQ);
    BOOST_REQUIRE(data_set.is_data_set("deadbeef"));

    dcmtkpp::DataSet item;
    item.add(0xbeeff00d,
        dcmtkpp::Element(dcmtkpp::Value::Integers({1,2}), dcmtkpp::VR::SS));
    BOOST_REQUIRE(data_set.as_data_set("deadbeef") == dcmtkpp::Value::DataSets({item}));
}


BOOST_AUTO_TEST_CASE(AsDataSetBinary)
{
    std::stringstream data;
    data << "{ \"deadbeef\": { \"vr\": \"OB\", \"InlineBinary\": \"AQIDBAU=\" } }";
    Json::Value json;
    data >> json;

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(json);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("deadbeef"));
    BOOST_REQUIRE(data_set.get_vr("deadbeef") == dcmtkpp::VR::OB);
    BOOST_REQUIRE(data_set.is_binary("deadbeef"));
    BOOST_REQUIRE(data_set.as_binary("deadbeef") == dcmtkpp::Value::Binary(
        {0x1, 0x2, 0x3, 0x4, 0x5}));
}
