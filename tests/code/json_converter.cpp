#define BOOST_TEST_MODULE json_converter
#include <boost/test/unit_test.hpp>

#include <set>
#include <string>
#include <vector>

#include <json/json.h>

#include "odil/DataSet.h"
#include "odil/Element.h"
#include "odil/json_converter.h"
#include "odil/Value.h"
#include "odil/VR.h"

BOOST_AUTO_TEST_CASE(AsJSONEmptyDataSet)
{
    odil::DataSet data_set;
    auto const json = odil::as_json(data_set);
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

BOOST_AUTO_TEST_CASE(AsJSONEmptyElement)
{
    odil::DataSet data_set;
    data_set.add(0xdeadbeef, odil::VR::SS);
    auto const json = odil::as_json(data_set);
    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr"});
    check_json_string(json["deadbeef"]["vr"], "SS");
}

BOOST_AUTO_TEST_CASE(AsJSONIntegers)
{
    odil::DataSet data_set;
    data_set.add(0xdeadbeef,
        odil::Element(odil::Value::Integers({1, 2}), odil::VR::SS));
    auto const json = odil::as_json(data_set);
    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["vr"], "SS");
    check_json_array(json["deadbeef"]["Value"],
        &Json::Value::isInt, &Json::Value::asInt, data_set.as_int(0xdeadbeef));
}

BOOST_AUTO_TEST_CASE(AsJSONReals)
{
    odil::DataSet data_set;
    data_set.add(0xdeadbeef,
        odil::Element(odil::Value::Reals({1.2, 3.4}), odil::VR::FL));
    auto const json = odil::as_json(data_set);
    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["vr"], "FL");
    check_json_array(json["deadbeef"]["Value"],
        &Json::Value::isDouble, &Json::Value::asDouble, data_set.as_real(0xdeadbeef));
}

BOOST_AUTO_TEST_CASE(AsJSONStrings)
{
    odil::DataSet data_set;
    data_set.add(0xdeadbeef,
        odil::Element(
            odil::Value::Strings({"FOO", "BAR"}),
            odil::VR::CS));
    auto const json = odil::as_json(data_set);
    check_json_object(json, {"deadbeef"});
    check_json_object(json["deadbeef"], {"vr", "Value"});
    check_json_string(json["deadbeef"]["vr"], "CS");
    check_json_array(json["deadbeef"]["Value"],
        &Json::Value::isString, &Json::Value::asString, data_set.as_string(0xdeadbeef));
}

BOOST_AUTO_TEST_CASE(AsJSONPersonName)
{
    odil::DataSet data_set;
    data_set.add(0xdeadbeef,
        odil::Element(
            odil::Value::Strings({"Alpha^Betic=Ideo^Graphic=Pho^Netic"}),
            odil::VR::PN));
    auto const json = odil::as_json(data_set);
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
    odil::DataSet item;
    item.add(0xbeeff00d,
        odil::Element(odil::Value::Integers({1,2}), odil::VR::SS));
    odil::DataSet data_set;
    data_set.add(0xdeadbeef,
        odil::Element(
            odil::Value::DataSets({item}),
            odil::VR::SQ));

    auto const json = odil::as_json(data_set);

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
    odil::DataSet data_set;
    data_set.add(0xdeadbeef,
        odil::Element(
            odil::Value::Binary({{0x1, 0x2, 0x3, 0x4, 0x5}}),
            odil::VR::OB));

    auto const json = odil::as_json(data_set);

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

    odil::DataSet const data_set = odil::as_dataset(json);
    BOOST_REQUIRE(data_set.empty());
}

BOOST_AUTO_TEST_CASE(AsDataSetIntegers)
{
    std::stringstream data;
    data << "{ \"deadbeef\": { \"vr\": \"SS\", \"Value\": [1, 2] } }";
    Json::Value json;
    data >> json;

    odil::DataSet const data_set = odil::as_dataset(json);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("deadbeef"));
    BOOST_REQUIRE(data_set.get_vr("deadbeef") == odil::VR::SS);
    BOOST_REQUIRE(data_set.is_int("deadbeef"));
    BOOST_REQUIRE(data_set.as_int("deadbeef") == odil::Value::Integers({1, 2}));
}

BOOST_AUTO_TEST_CASE(AsDataSetReals)
{
    std::stringstream data;
    data << "{ \"deadbeef\": { \"vr\": \"FL\", \"Value\": [1.2, 3.4] } }";
    Json::Value json;
    data >> json;

    odil::DataSet const data_set = odil::as_dataset(json);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("deadbeef"));
    BOOST_REQUIRE(data_set.get_vr("deadbeef") == odil::VR::FL);
    BOOST_REQUIRE(data_set.is_real("deadbeef"));
    BOOST_REQUIRE(data_set.as_real("deadbeef") == odil::Value::Reals({1.2, 3.4}));
}

BOOST_AUTO_TEST_CASE(AsDataSetStrings)
{
    std::stringstream data;
    data << "{ \"deadbeef\": { \"vr\": \"CS\", \"Value\": [\"FOO\", \"BAR\"] } }";
    Json::Value json;
    data >> json;

    odil::DataSet const data_set = odil::as_dataset(json);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("deadbeef"));
    BOOST_REQUIRE(data_set.get_vr("deadbeef") == odil::VR::CS);
    BOOST_REQUIRE(data_set.is_string("deadbeef"));
    BOOST_REQUIRE(data_set.as_string("deadbeef") == odil::Value::Strings({"FOO", "BAR"}));
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

    odil::DataSet const data_set = odil::as_dataset(json);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("deadbeef"));
    BOOST_REQUIRE(data_set.get_vr("deadbeef") == odil::VR::PN);
    BOOST_REQUIRE(data_set.is_string("deadbeef"));
    BOOST_REQUIRE(data_set.as_string("deadbeef") == odil::Value::Strings(
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

    odil::DataSet const data_set = odil::as_dataset(json);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("deadbeef"));
    BOOST_REQUIRE(data_set.get_vr("deadbeef") == odil::VR::SQ);
    BOOST_REQUIRE(data_set.is_data_set("deadbeef"));

    odil::DataSet item;
    item.add(0xbeeff00d,
        odil::Element(odil::Value::Integers({1,2}), odil::VR::SS));
    BOOST_REQUIRE(data_set.as_data_set("deadbeef") == odil::Value::DataSets({item}));
}


BOOST_AUTO_TEST_CASE(AsDataSetBinary)
{
    std::stringstream data;
    data << "{ \"deadbeef\": { \"vr\": \"OB\", \"InlineBinary\": \"AQIDBAU=\" } }";
    Json::Value json;
    data >> json;

    odil::DataSet const data_set = odil::as_dataset(json);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("deadbeef"));
    BOOST_REQUIRE(data_set.get_vr("deadbeef") == odil::VR::OB);
    BOOST_REQUIRE(data_set.is_binary("deadbeef"));
    BOOST_REQUIRE(data_set.as_binary("deadbeef") == odil::Value::Binary(
        {{0x1, 0x2, 0x3, 0x4, 0x5}}));
}
