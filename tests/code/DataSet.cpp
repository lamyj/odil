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

template<typename TContainer>
void test_element_value(
    odil::DataSet const & data_set, odil::Tag const & tag,
    TContainer const & contents,
    bool (odil::DataSet::*type_check)(odil::Tag const &) const,
    TContainer const & (odil::DataSet::*getter)(odil::Tag const &) const,
    typename TContainer::value_type const & (odil::DataSet::*getter_pos)(odil::Tag const &, unsigned int) const)
{
    BOOST_CHECK(data_set.has(tag));
    BOOST_CHECK_EQUAL(data_set.empty(tag), contents.empty());
    BOOST_CHECK_EQUAL(data_set.size(tag), contents.size());
    BOOST_CHECK((data_set.*type_check)(tag));
    BOOST_CHECK((data_set.*getter)(tag) == contents);

    for(int i=0; i<contents.size(); ++i)
    {
        BOOST_CHECK((data_set.*getter_pos)(tag, i) == contents[i]);
    }
    BOOST_CHECK_THROW((data_set.*getter_pos)(tag, contents.size()), odil::Exception);

    if(!data_set.is_int(tag))
    {
        BOOST_CHECK_THROW(data_set.as_int(tag), odil::Exception);
    }
    if(!data_set.is_real(tag))
    {
        BOOST_CHECK_THROW(data_set.as_real(tag), odil::Exception);
    }
    if(!data_set.is_string(tag))
    {
        BOOST_CHECK_THROW(data_set.as_string(tag), odil::Exception);
    }
    if(!data_set.is_data_set(tag))
    {
        BOOST_CHECK_THROW(data_set.as_data_set(tag), odil::Exception);
    }
    if(!data_set.is_binary(tag))
    {
        BOOST_CHECK_THROW(data_set.as_binary(tag), odil::Exception);
    }
}

template<typename TContainer>
void test_implicit_container(
    odil::Tag const & tag, 
    bool (odil::DataSet::*type_check)(odil::Tag const &) const,
    TContainer const & (odil::DataSet::*getter)(odil::Tag const &) const,
    typename TContainer::value_type const & (odil::DataSet::*getter_pos)(odil::Tag const &, unsigned int) const)
{
    odil::DataSet data_set;
    data_set.add(tag);
    test_element_value(data_set, tag, TContainer(), type_check, getter, getter_pos);
}

template<typename TContainer>
void test_implicit_container(
    odil::Tag const & tag, odil::VR const & vr,
    bool (odil::DataSet::*type_check)(odil::Tag const &) const,
    TContainer const & (odil::DataSet::*getter)(odil::Tag const &) const,
    typename TContainer::value_type const & (odil::DataSet::*getter_pos)(odil::Tag const &, unsigned int) const)
{
    odil::DataSet data_set;
    data_set.add(tag, vr);
    test_element_value(data_set, tag, TContainer(), type_check, getter, getter_pos);
}

template<typename TContainer>
void test_container(
    odil::Tag const & tag, TContainer const & contents,
    bool (odil::DataSet::*type_check)(odil::Tag const &) const,
    TContainer const & (odil::DataSet::*getter)(odil::Tag const &) const,
    typename TContainer::value_type const & (odil::DataSet::*getter_pos)(odil::Tag const &, unsigned int) const)
{
    odil::DataSet data_set;
    data_set.add(tag, contents);
    test_element_value(data_set, tag, contents, type_check, getter, getter_pos);

    auto contents_copy(contents);
    odil::DataSet other_data_set;
    other_data_set.add(tag, std::move(contents_copy));
    BOOST_CHECK(contents_copy.empty());
}

template<typename TContainer>
void test_container(
    odil::Tag const & tag, TContainer const & contents, odil::VR const & vr,
    bool (odil::DataSet::*type_check)(odil::Tag const &) const,
    TContainer const & (odil::DataSet::*getter)(odil::Tag const &) const,
    typename TContainer::value_type const & (odil::DataSet::*getter_pos)(odil::Tag const &, unsigned int) const)
{
    odil::DataSet data_set;
    data_set.add(tag, contents, vr);
    test_element_value(data_set, tag, contents, type_check, getter, getter_pos);

    auto contents_copy(contents);
    odil::DataSet other_data_set;
    other_data_set.add(tag, std::move(contents_copy));
    BOOST_CHECK(contents_copy.empty());
}

template<typename TContainer>
void test_initializer_list(
    odil::Tag const & tag, 
    std::initializer_list<typename TContainer::value_type> const & contents,
    bool (odil::DataSet::*type_check)(odil::Tag const &) const, 
    TContainer const & (odil::DataSet::*getter)(odil::Tag const &) const,
    typename TContainer::value_type const & (odil::DataSet::*getter_pos)(odil::Tag const &, unsigned int) const)
{
    odil::DataSet data_set;
    data_set.add(tag, contents);
    test_element_value(data_set, tag, TContainer(contents), type_check, getter, getter_pos);
}

template<typename TContainer>
void test_initializer_list(
    odil::Tag const & tag, 
    std::initializer_list<typename TContainer::value_type> const & contents,
    odil::VR const & vr,
    bool (odil::DataSet::*type_check)(odil::Tag const &) const, 
    TContainer const & (odil::DataSet::*getter)(odil::Tag const &) const,
    typename TContainer::value_type const & (odil::DataSet::*getter_pos)(odil::Tag const &, unsigned int) const)
{
    odil::DataSet data_set;
    data_set.add(tag, contents, vr);
    test_element_value(data_set, tag, TContainer(contents), type_check, getter, getter_pos);
}

template<typename TContainer>
void test_modify(
    odil::Tag const & tag, TContainer const & contents,
    TContainer const & (odil::DataSet::*getter)(odil::Tag const &) const,
    TContainer & (odil::DataSet::*setter)(odil::Tag const &))
{
    odil::DataSet data_set;
    data_set.add(tag, {contents[0]});
    (data_set.*setter)(tag).push_back(contents[1]);
    BOOST_CHECK((data_set.*getter)(tag) == contents);
}

template<typename TContainer>
void test_clear(
    odil::Tag const & tag, TContainer const & contents,
    bool (odil::DataSet::*type_check)(odil::Tag const &) const)
{
    odil::DataSet data_set;
    data_set.add(tag, contents);
    data_set.clear(tag);
    BOOST_CHECK((data_set.*type_check)(tag));
    BOOST_CHECK(data_set.empty(tag));
}

template<typename TContainer>
void test_element(
    odil::Tag const & tag, 
    std::initializer_list<typename TContainer::value_type> const & contents,
    odil::VR const & vr, 
    bool (odil::DataSet::*type_check)(odil::Tag const &) const,
    TContainer const & (odil::DataSet::*getter)(odil::Tag const &) const,
    typename TContainer::value_type const & (odil::DataSet::*getter_pos)(odil::Tag const &, unsigned int) const,
    TContainer & (odil::DataSet::*setter)(odil::Tag const &))
{
    test_implicit_container(tag, type_check, getter, getter_pos);
    test_implicit_container(tag, vr, type_check, getter, getter_pos);

    TContainer const container(contents);

    test_container(tag, container, type_check, getter, getter_pos);
    test_container(tag, container, vr, type_check, getter, getter_pos);

    test_initializer_list(tag, contents, type_check, getter, getter_pos);
    test_initializer_list(tag, contents, vr, type_check, getter, getter_pos);

    test_modify(tag, container, getter, setter);

    test_clear(tag, container, type_check);
}

BOOST_AUTO_TEST_CASE(Int)
{
    odil::DataSet data_set;
    data_set.add(odil::registry::Rows, {1234, 5678});
    data_set.is_int(odil::registry::Rows);

    test_element<odil::Value::Integers>(
        odil::registry::Rows, {1234, 5678}, odil::VR::US,
        &odil::DataSet::is_int, 
        &odil::DataSet::as_int, &odil::DataSet::as_int, &odil::DataSet::as_int);
}

BOOST_AUTO_TEST_CASE(Real)
{
    odil::DataSet data_set;
    data_set.add(odil::registry::SpacingBetweenSlices, {12.34, 56.78});
    data_set.is_int(odil::registry::SpacingBetweenSlices);

    test_element<odil::Value::Reals>(
        odil::registry::SpacingBetweenSlices, {12.34, 56.78}, odil::VR::FL,
        &odil::DataSet::is_real, 
        &odil::DataSet::as_real, &odil::DataSet::as_real, &odil::DataSet::as_real);
}

BOOST_AUTO_TEST_CASE(String)
{
    odil::DataSet data_set;
    data_set.add(odil::registry::PatientID, {"foo", "bar"});
    data_set.is_int(odil::registry::PatientID);

    test_element<odil::Value::Strings>(
        odil::registry::PatientID, {"foo", "bar"}, odil::VR::LT,
        &odil::DataSet::is_string, 
        &odil::DataSet::as_string, &odil::DataSet::as_string, &odil::DataSet::as_string);
}

BOOST_AUTO_TEST_CASE(DataSets)
{
    auto data_set_1 = std::make_shared<odil::DataSet>();
    data_set_1->add("PatientID", {"DJ1234"});

    auto data_set_2 = std::make_shared<odil::DataSet>();
    data_set_2->add("EchoTime", {100});

    odil::DataSet data_set;
    data_set.add(
        odil::registry::ReferencedStudySequence, {data_set_1, data_set_2});
    data_set.is_int(odil::registry::ReferencedStudySequence);

    test_element<odil::Value::DataSets>(
        odil::registry::ReferencedStudySequence, {data_set_1, data_set_2}, odil::VR::SQ,
        &odil::DataSet::is_data_set, 
        &odil::DataSet::as_data_set, &odil::DataSet::as_data_set, &odil::DataSet::as_data_set);
}

BOOST_AUTO_TEST_CASE(Binary)
{
    odil::DataSet data_set;
    data_set.add(odil::registry::BadPixelImage, {{0x1, 0x2}, {0x3}});
    data_set.is_int(odil::registry::BadPixelImage);

    test_element<odil::Value::Binary>(
        odil::registry::BadPixelImage, {{0x1, 0x2}, {0x3}}, odil::VR::OB,
        &odil::DataSet::is_binary,
        &odil::DataSet::as_binary, &odil::DataSet::as_binary, &odil::DataSet::as_binary);
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

BOOST_AUTO_TEST_CASE(EmptyMissing)
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

BOOST_AUTO_TEST_CASE(ClearMissing)
{
    odil::Tag const tag("PatientID");
    odil::DataSet dataset;
    BOOST_CHECK_THROW(dataset.clear(tag), odil::Exception);
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

BOOST_AUTO_TEST_CASE(Clear)
{
    odil::DataSet data_set;
    data_set.add("PatientID", {"DJ1234"});
    data_set.clear("PatientID");
    BOOST_CHECK(data_set.empty("PatientID"));
    BOOST_CHECK_THROW(data_set.clear("PatietName"), odil::Exception);
}

