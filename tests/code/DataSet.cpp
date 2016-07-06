#define BOOST_TEST_MODULE DataSet
#include <boost/test/unit_test.hpp>

#include "odil/DataSet.h"
#include "odil/Exception.h"
#include "odil/Tag.h"
#include "odil/VR.h"

#include "odil/registry.h"

BOOST_AUTO_TEST_CASE(Empty)
{
    odil::DataSet dataset;
    BOOST_CHECK(dataset.empty());
    BOOST_CHECK_EQUAL(dataset.size(), 0);
    BOOST_CHECK(!dataset.has(odil::Tag("PatientName")));
    BOOST_CHECK(dataset.get_transfer_syntax().empty());
}

BOOST_AUTO_TEST_CASE(TransferSyntaxConstructor)
{
    odil::DataSet dataset(odil::registry::ExplicitVRLittleEndian);
    BOOST_CHECK_EQUAL(
        dataset.get_transfer_syntax(), odil::registry::ExplicitVRLittleEndian);
}

BOOST_AUTO_TEST_CASE(TransferSyntax)
{
    odil::DataSet dataset;
    dataset.set_transfer_syntax(odil::registry::ExplicitVRLittleEndian);
    BOOST_CHECK_EQUAL(
        dataset.get_transfer_syntax(), odil::registry::ExplicitVRLittleEndian);
}

BOOST_AUTO_TEST_CASE(AddExplicitVR)
{
    odil::Tag const tag("PatientName");

    odil::DataSet dataset;
    dataset.add(tag, odil::VR::PN);

    BOOST_CHECK(!dataset.empty());
    BOOST_CHECK_EQUAL(dataset.size(), 1);
    BOOST_CHECK(dataset.has(tag));
    BOOST_CHECK(dataset.get_vr(tag) == odil::VR::PN);
}

BOOST_AUTO_TEST_CASE(AddImplicitVR)
{
    odil::Tag const tag("PatientName");

    odil::DataSet dataset;
    dataset.add(tag);

    BOOST_CHECK(!dataset.empty());
    BOOST_CHECK_EQUAL(dataset.size(), 1);
    BOOST_CHECK(dataset.has(tag));
    BOOST_CHECK(dataset.get_vr(tag) == odil::VR::PN);
}

BOOST_AUTO_TEST_CASE(AddValueExplicitVR)
{
    odil::Tag const tag("PatientName");

    odil::DataSet dataset;
    dataset.add(tag, { "Doe^John"}, odil::VR::PN);

    BOOST_CHECK(!dataset.empty());
    BOOST_CHECK_EQUAL(dataset.size(), 1);
    BOOST_CHECK(dataset.has(tag));
    BOOST_CHECK(dataset.get_vr(tag) == odil::VR::PN);
    BOOST_CHECK(dataset.as_string(tag) == odil::Value::Strings({ "Doe^John" }));
}

BOOST_AUTO_TEST_CASE(AddValueImplicitVR)
{
    odil::Tag const tag("PatientName");

    odil::DataSet dataset;
    dataset.add(tag, { "Doe^John"});

    BOOST_CHECK(!dataset.empty());
    BOOST_CHECK_EQUAL(dataset.size(), 1);
    BOOST_CHECK(dataset.has(tag));
    BOOST_CHECK(dataset.get_vr(tag) == odil::VR::PN);
    BOOST_CHECK(dataset.as_string(tag) == odil::Value::Strings({ "Doe^John" }));
}

BOOST_AUTO_TEST_CASE(AddInvalidTag)
{
    odil::Tag const tag(0xdead, 0xbeef);
    odil::DataSet dataset;

    BOOST_CHECK_THROW(dataset.add(tag), odil::Exception);
}

BOOST_AUTO_TEST_CASE(AddIntEmpty)
{
    odil::Tag const tag("Rows");

    odil::DataSet dataset;
    dataset.add(tag);

    BOOST_CHECK(dataset.is_int(tag));
    BOOST_CHECK(dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 0);

    std::vector<int64_t> const & value = dataset.as_int(tag);
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(AddDoubleEmpty)
{
    odil::Tag const tag("SpacingBetweenSlices");

    odil::DataSet dataset;
    dataset.add(tag);

    BOOST_CHECK(dataset.is_real(tag));
    BOOST_CHECK(dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 0);

    std::vector<double> const & value = dataset.as_real(tag);
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(AddStringEmpty)
{
    odil::Tag const tag("PatientID");

    odil::DataSet dataset;
    dataset.add(tag);

    BOOST_CHECK(dataset.is_string(tag));
    BOOST_CHECK(dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 0);

    std::vector<std::string> const & value = dataset.as_string(tag);
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(AddDataSetEmpty)
{
    odil::Tag const tag("ReferencedStudySequence");

    odil::DataSet dataset;
    dataset.add(tag);

    BOOST_CHECK(dataset.is_data_set(tag));
    BOOST_CHECK(dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 0);

    odil::Value::DataSets const & value = dataset.as_data_set(tag);
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(AddBinaryEmpty)
{
    odil::Tag const tag("BadPixelImage");

    odil::DataSet dataset;
    dataset.add(tag);

    BOOST_CHECK(dataset.is_binary(tag));
    BOOST_CHECK(dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 0);

    auto const & value = dataset.as_binary(tag);
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(AddInt)
{
    odil::Tag const tag("Rows");

    odil::DataSet dataset;
    dataset.add(tag, odil::Value::Integers({123}));

    BOOST_CHECK(dataset.is_int(tag));
    BOOST_REQUIRE_EQUAL(dataset.size(tag), 1);
    BOOST_REQUIRE(dataset.as_int(tag) == odil::Value::Integers({123}));
}

BOOST_AUTO_TEST_CASE(AddDouble)
{
    odil::Tag const tag("SpacingBetweenSlices");

    odil::DataSet dataset;
    dataset.add(tag, odil::Value::Reals({123.456}));

    BOOST_CHECK(dataset.is_real(tag));
    BOOST_REQUIRE_EQUAL(dataset.size(tag), 1);
    BOOST_REQUIRE(dataset.as_real(tag) == odil::Value::Reals({123.456}));
}

BOOST_AUTO_TEST_CASE(AddString)
{
    odil::Tag const tag("PatientID");

    odil::DataSet dataset;
    dataset.add(tag, odil::Value::Strings({"DJ123"}));

    BOOST_CHECK(dataset.is_string(tag));
    BOOST_REQUIRE_EQUAL(dataset.size(tag), 1);
    BOOST_REQUIRE(dataset.as_string(tag) == odil::Value::Strings({"DJ123"}));
}

BOOST_AUTO_TEST_CASE(AddDataSet)
{
    odil::Tag const tag("ReferencedStudySequence");
    odil::DataSet item;
    item.add(odil::registry::StudyInstanceUID, {"1.2.3"});

    odil::DataSet dataset;
    dataset.add(tag, odil::Value::DataSets({item}));

    BOOST_CHECK(dataset.is_data_set(tag));
    BOOST_REQUIRE_EQUAL(dataset.size(tag), 1);
    BOOST_REQUIRE(dataset.as_data_set(tag, 0) == item);
}

BOOST_AUTO_TEST_CASE(AddIntInitializer1)
{
    odil::Tag const tag("Rows");

    odil::DataSet dataset;
    dataset.add(tag, {123});

    BOOST_CHECK(dataset.is_int(tag));
    BOOST_REQUIRE_EQUAL(dataset.size(tag), 1);
    BOOST_REQUIRE(dataset.as_int(tag) == odil::Value::Integers({123}));
}

BOOST_AUTO_TEST_CASE(AddIntInitializer2)
{
    odil::Tag const tag("Rows");

    odil::DataSet dataset;
    dataset.add(tag, {odil::Value::Integer(123)});

    BOOST_CHECK(dataset.is_int(tag));
    BOOST_REQUIRE_EQUAL(dataset.size(tag), 1);
    BOOST_REQUIRE(dataset.as_int(tag) == odil::Value::Integers({123}));
}


BOOST_AUTO_TEST_CASE(AddDoubleInitializer)
{
    odil::Tag const tag("SpacingBetweenSlices");

    odil::DataSet dataset;
    dataset.add(tag, {123.456});

    BOOST_CHECK(dataset.is_real(tag));
    BOOST_REQUIRE_EQUAL(dataset.size(tag), 1);
    BOOST_REQUIRE(dataset.as_real(tag) == odil::Value::Reals({123.456}));
}

BOOST_AUTO_TEST_CASE(AddStringInitializer)
{
    odil::Tag const tag("PatientID");

    odil::DataSet dataset;
    dataset.add(tag, {"DJ123"});

    BOOST_CHECK(dataset.is_string(tag));
    BOOST_REQUIRE_EQUAL(dataset.size(tag), 1);
    BOOST_REQUIRE(dataset.as_string(tag) == odil::Value::Strings({"DJ123"}));
}

BOOST_AUTO_TEST_CASE(AddDataSetInitializer)
{
    odil::Tag const tag("ReferencedStudySequence");
    odil::DataSet item;
    item.add(odil::registry::StudyInstanceUID, {"1.2.3"});

    odil::DataSet dataset;
    dataset.add(tag, {item});

    BOOST_CHECK(dataset.is_data_set(tag));
    BOOST_REQUIRE_EQUAL(dataset.size(tag), 1);
    BOOST_REQUIRE(dataset.as_data_set(tag, 0) == item);
}

BOOST_AUTO_TEST_CASE(AddBinary)
{
    odil::Tag const tag("BadPixelImage");

    odil::DataSet dataset;
    dataset.add(tag, odil::Value::Binary({{0x01, 0x02}}));

    BOOST_CHECK(dataset.is_binary(tag));
    BOOST_REQUIRE(
        dataset.as_binary(tag) == odil::Value::Binary({{ 0x01, 0x02 }}));
}

BOOST_AUTO_TEST_CASE(ModifyInt)
{
    odil::Tag const tag("Rows");

    odil::DataSet dataset;
    dataset.add(tag);
    dataset.as_int(tag).push_back(256);

    BOOST_CHECK(!dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 1);
    BOOST_CHECK_EQUAL(dataset.as_int(tag, 0), 256);
}

BOOST_AUTO_TEST_CASE(ModifyDouble)
{
    odil::Tag const tag("SpacingBetweenSlices");

    odil::DataSet dataset;
    dataset.add(tag);
    dataset.as_real(tag).push_back(3.14);

    BOOST_CHECK(!dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 1);
    BOOST_CHECK_EQUAL(dataset.as_real(tag, 0), 3.14);
}

BOOST_AUTO_TEST_CASE(ModifyString)
{
    odil::Tag const tag("PatientID");

    odil::DataSet dataset;
    dataset.add(tag);
    dataset.as_string(tag).push_back("FooBar");

    BOOST_CHECK(!dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 1);
    BOOST_CHECK_EQUAL(dataset.as_string(tag, 0), "FooBar");
}

BOOST_AUTO_TEST_CASE(ModifyDataSet)
{
    odil::Tag const tag("ReferencedStudySequence");

    odil::DataSet dataset;
    dataset.add(tag);

    odil::DataSet item;
    item.add("PatientID", {"DJ1234"});
    dataset.as_data_set(tag).push_back(item);

    BOOST_CHECK(!dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 1);

    odil::Value::DataSets const & value = dataset.as_data_set(tag);
    BOOST_CHECK_EQUAL(value.size(), 1);
    BOOST_CHECK_EQUAL(value.size(), 1);
    BOOST_CHECK_EQUAL(value[0].size(), 1);
    BOOST_CHECK(value[0].has("PatientID"));
    BOOST_CHECK(
        value[0].as_string("PatientID") == odil::Value::Strings({"DJ1234"}));
}

BOOST_AUTO_TEST_CASE(ElementAccessor)
{
    odil::Tag const tag("PatientID");

    odil::DataSet dataset;
    dataset.add(tag, {"Foo^Bar"});
    BOOST_REQUIRE(
        dataset[tag].as_string() == odil::Value::Strings({"Foo^Bar"}));
    BOOST_REQUIRE_THROW(
        dataset[odil::registry::PatientName], odil::Exception);
}

BOOST_AUTO_TEST_CASE(GetVRMissing)
{
    odil::Tag const tag("PatientID");
    odil::DataSet dataset;
    BOOST_CHECK_THROW(dataset.get_vr(tag), odil::Exception);
}

BOOST_AUTO_TEST_CASE(TestEmptyMissing)
{
    odil::Tag const tag("PatientID");
    odil::DataSet dataset;
    BOOST_CHECK_THROW(dataset.empty(tag), odil::Exception);
}

BOOST_AUTO_TEST_CASE(SizeMissing)
{
    odil::Tag const tag("PatientID");
    odil::DataSet dataset;
    BOOST_CHECK_THROW(dataset.size(tag), odil::Exception);
}

BOOST_AUTO_TEST_CASE(Remove)
{
    odil::Tag const tag("PatientID");
    odil::DataSet dataset;
    dataset.add(tag);

    dataset.remove(tag);
    BOOST_CHECK(!dataset.has(tag));
}

BOOST_AUTO_TEST_CASE(RemoveMissing)
{
    odil::Tag const tag("PatientID");
    odil::DataSet dataset;
    dataset.add(tag);

    odil::Tag const other("PatientName");

    BOOST_CHECK_THROW(
        dataset.remove(other),
        odil::Exception);
}

BOOST_AUTO_TEST_CASE(Equality)
{
    odil::DataSet dataset1;
    dataset1.add("PatientID", {"DJ1234"});

    odil::DataSet dataset2;
    dataset2.add("PatientID", {"DJ1234"});

    odil::DataSet dataset3;
    dataset3.add("PatientAge", {"042Y"});

    BOOST_CHECK(dataset1 == dataset2);
    BOOST_CHECK(! (dataset1 == dataset3));
}

BOOST_AUTO_TEST_CASE(Difference)
{
    odil::DataSet dataset1;
    dataset1.add("PatientID", {"DJ1234"});

    odil::DataSet dataset2;
    dataset2.add("PatientID", {"DJ1234"});

    odil::DataSet dataset3;
    dataset3.add("PatientAge", {"042Y"});

    BOOST_CHECK(! (dataset1 != dataset2));
    BOOST_CHECK(dataset1 != dataset3);
}
