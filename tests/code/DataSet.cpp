#define BOOST_TEST_MODULE DataSet
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Tag.h"
#include "dcmtkpp/VR.h"

BOOST_AUTO_TEST_CASE(Empty)
{
    dcmtkpp::DataSet dataset;
    BOOST_CHECK(dataset.empty());
    BOOST_CHECK_EQUAL(dataset.size(), 0);
    BOOST_CHECK(!dataset.has(dcmtkpp::Tag("PatientName")));
}

BOOST_AUTO_TEST_CASE(AddExplicitVR)
{
    dcmtkpp::Tag const tag("PatientName");

    dcmtkpp::DataSet dataset;
    dataset.add(tag, dcmtkpp::VR::PN);

    BOOST_CHECK(!dataset.empty());
    BOOST_CHECK_EQUAL(dataset.size(), 1);
    BOOST_CHECK(dataset.has(tag));
    BOOST_CHECK(dataset.get_vr(tag) == dcmtkpp::VR::PN);
}

BOOST_AUTO_TEST_CASE(AddImplicitVR)
{
    dcmtkpp::Tag const tag("PatientName");

    dcmtkpp::DataSet dataset;
    dataset.add(tag);

    BOOST_CHECK(!dataset.empty());
    BOOST_CHECK_EQUAL(dataset.size(), 1);
    BOOST_CHECK(dataset.has(tag));
    BOOST_CHECK(dataset.get_vr(tag) == dcmtkpp::VR::PN);
}

BOOST_AUTO_TEST_CASE(AddValueExplicitVR)
{
    dcmtkpp::Tag const tag("PatientName");

    dcmtkpp::DataSet dataset;
    dataset.add(tag, dcmtkpp::VR::PN, dcmtkpp::Value::Strings({ "Doe^John"}));

    BOOST_CHECK(!dataset.empty());
    BOOST_CHECK_EQUAL(dataset.size(), 1);
    BOOST_CHECK(dataset.has(tag));
    BOOST_CHECK(dataset.get_vr(tag) == dcmtkpp::VR::PN);
    BOOST_CHECK(dataset.as_string(tag) == dcmtkpp::Value::Strings({ "Doe^John" }));
}

BOOST_AUTO_TEST_CASE(AddValueImplicitVR)
{
    dcmtkpp::Tag const tag("PatientName");

    dcmtkpp::DataSet dataset;
    dataset.add(tag, dcmtkpp::Value::Strings({ "Doe^John"}));

    BOOST_CHECK(!dataset.empty());
    BOOST_CHECK_EQUAL(dataset.size(), 1);
    BOOST_CHECK(dataset.has(tag));
    BOOST_CHECK(dataset.get_vr(tag) == dcmtkpp::VR::PN);
    BOOST_CHECK(dataset.as_string(tag) == dcmtkpp::Value::Strings({ "Doe^John" }));
}

BOOST_AUTO_TEST_CASE(AddInvalidVR)
{
    dcmtkpp::Tag const tag("PatientName");
    dcmtkpp::DataSet dataset;

    BOOST_CHECK_THROW(
        dataset.add(tag, dcmtkpp::VR::INVALID), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(AddInvalidTag)
{
    dcmtkpp::Tag const tag(0xdead, 0xbeef);
    dcmtkpp::DataSet dataset;

    BOOST_CHECK_THROW(dataset.add(tag), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(AddInt)
{
    dcmtkpp::Tag const tag("Rows");

    dcmtkpp::DataSet dataset;
    dataset.add(tag);

    BOOST_CHECK(dataset.is_int(tag));
    BOOST_CHECK(dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 0);

    std::vector<int64_t> const & value = dataset.as_int(tag);
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(AddDouble)
{
    dcmtkpp::Tag const tag("SpacingBetweenSlices");

    dcmtkpp::DataSet dataset;
    dataset.add(tag);

    BOOST_CHECK(dataset.is_real(tag));
    BOOST_CHECK(dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 0);

    std::vector<double> const & value = dataset.as_real(tag);
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(AddString)
{
    dcmtkpp::Tag const tag("PatientID");

    dcmtkpp::DataSet dataset;
    dataset.add(tag);

    BOOST_CHECK(dataset.is_string(tag));
    BOOST_CHECK(dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 0);

    std::vector<std::string> const & value = dataset.as_string(tag);
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(AddDataSet)
{
    dcmtkpp::Tag const tag("ReferencedStudySequence");

    dcmtkpp::DataSet dataset;
    dataset.add(tag);

    BOOST_CHECK(dataset.is_data_set(tag));
    BOOST_CHECK(dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 0);

    dcmtkpp::Value::DataSets const & value = dataset.as_data_set(tag);
    BOOST_CHECK(value.empty());
}

BOOST_AUTO_TEST_CASE(ModifyInt)
{
    dcmtkpp::Tag const tag("Rows");

    dcmtkpp::DataSet dataset;
    dataset.add(tag);
    dataset.as_int(tag).push_back(256);

    BOOST_CHECK(!dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 1);
    BOOST_CHECK_EQUAL(dataset.as_int(tag, 0), 256);
}

BOOST_AUTO_TEST_CASE(ModifyDouble)
{
    dcmtkpp::Tag const tag("SpacingBetweenSlices");

    dcmtkpp::DataSet dataset;
    dataset.add(tag);
    dataset.as_real(tag).push_back(3.14);

    BOOST_CHECK(!dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 1);
    BOOST_CHECK_EQUAL(dataset.as_real(tag, 0), 3.14);
}

BOOST_AUTO_TEST_CASE(ModifyString)
{
    dcmtkpp::Tag const tag("PatientID");

    dcmtkpp::DataSet dataset;
    dataset.add(tag);
    dataset.as_string(tag).push_back("FooBar");

    BOOST_CHECK(!dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 1);
    BOOST_CHECK_EQUAL(dataset.as_string(tag, 0), "FooBar");
}

BOOST_AUTO_TEST_CASE(ModifyDataSet)
{
    dcmtkpp::Tag const tag("ReferencedStudySequence");

    dcmtkpp::DataSet dataset;
    dataset.add(tag);

    dcmtkpp::DataSet item;
    item.add("PatientID");
    item.as_string("PatientID").push_back("DJ1234");
    dataset.as_data_set(tag).push_back(item);

    BOOST_CHECK(!dataset.empty(tag));
    BOOST_CHECK_EQUAL(dataset.size(tag), 1);

    dcmtkpp::Value::DataSets const & value = dataset.as_data_set(tag);
    BOOST_CHECK_EQUAL(value.size(), 1);
    BOOST_CHECK_EQUAL(value.size(), 1);
    BOOST_CHECK_EQUAL(value[0].size(), 1);
    BOOST_CHECK(value[0].has("PatientID"));
    BOOST_CHECK(
        value[0].as_string("PatientID") == dcmtkpp::Value::Strings({"DJ1234"}));
}

BOOST_AUTO_TEST_CASE(GetVRMissing)
{
    dcmtkpp::Tag const tag("PatientID");
    dcmtkpp::DataSet dataset;
    BOOST_CHECK_THROW(dataset.get_vr(tag), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(TestEmptyMissing)
{
    dcmtkpp::Tag const tag("PatientID");
    dcmtkpp::DataSet dataset;
    BOOST_CHECK_THROW(dataset.empty(tag), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(SizeMissing)
{
    dcmtkpp::Tag const tag("PatientID");
    dcmtkpp::DataSet dataset;
    BOOST_CHECK_THROW(dataset.size(tag), dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Remove)
{
    dcmtkpp::Tag const tag("PatientID");
    dcmtkpp::DataSet dataset;
    dataset.add(tag);

    dataset.remove(tag);
    BOOST_CHECK(!dataset.has(tag));
}

BOOST_AUTO_TEST_CASE(RemoveMissing)
{
    dcmtkpp::Tag const tag("PatientID");
    dcmtkpp::DataSet dataset;
    dataset.add(tag);

    dcmtkpp::Tag const other("PatientName");

    BOOST_CHECK_THROW(
        dataset.remove(other),
        dcmtkpp::Exception);
}

BOOST_AUTO_TEST_CASE(Equality)
{
    dcmtkpp::DataSet dataset1;
    dataset1.add("PatientID", dcmtkpp::VR::CS, dcmtkpp::Value::Strings({"DJ1234"}));

    dcmtkpp::DataSet dataset2;
    dataset2.add("PatientID", dcmtkpp::VR::CS, dcmtkpp::Value::Strings({"DJ1234"}));

    dcmtkpp::DataSet dataset3;
    dataset3.add("PatientAge", dcmtkpp::VR::CS, dcmtkpp::Value::Strings({"042Y"}));

    BOOST_CHECK(dataset1 == dataset2);
    BOOST_CHECK(! (dataset1 == dataset3));
}

BOOST_AUTO_TEST_CASE(Difference)
{
    dcmtkpp::DataSet dataset1;
    dataset1.add("PatientID", dcmtkpp::VR::CS, dcmtkpp::Value::Strings({"DJ1234"}));

    dcmtkpp::DataSet dataset2;
    dataset2.add("PatientID", dcmtkpp::VR::CS, dcmtkpp::Value::Strings({"DJ1234"}));

    dcmtkpp::DataSet dataset3;
    dataset3.add("PatientAge", dcmtkpp::VR::CS, dcmtkpp::Value::Strings({"042Y"}));

    BOOST_CHECK(! (dataset1 != dataset2));
    BOOST_CHECK(dataset1 != dataset3);
}
