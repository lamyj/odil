#define BOOST_TEST_MODULE xml_converter
#include <boost/test/unit_test.hpp>

#include <boost/property_tree/xml_parser.hpp>

#include "odil/DataSet.h"
#include "odil/registry.h"
#include "odil/Tag.h"
#include "odil/Value.h"
#include "odil/VR.h"
#include "odil/xml_converter.h"

bool compare_ptree(
    boost::property_tree::ptree const & p1,
    boost::property_tree::ptree const & p2)
{
    if(p1.size() != p2.size())
    {
        return false;
    }
    typedef
        boost::property_tree::ptree::const_assoc_iterator::value_type
        iterator_value_type;
    return std::equal(
        p1.ordered_begin(), p1.not_found(), p2.ordered_begin(),
        [](iterator_value_type const v1, iterator_value_type const & v2)
        {
            return v1.first == v2.first && compare_ptree(v1.second, v2.second);
        });
}

template<typename TValue>
void test_parsing(
    odil::Tag const & tag, odil::VR vr, TValue const & odil_value,
    std::string const & xml_value)
{
    // Baseline data set
    auto data_set = std::make_shared<odil::DataSet>();
    data_set->add(tag, odil_value);

    // Baseline XML
    std::stringstream stream;
    stream
        << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
        << "<NativeDicomModel>"
        << "<DicomAttribute "
            << "tag=\"" << tag << "\" "
            << "vr=\"" << odil::as_string(vr) << "\" "
            << "keyword=\"" << tag.get_name() << "\">";
    stream << xml_value;
    stream
        << "</DicomAttribute>"
        << "</NativeDicomModel>";

    boost::property_tree::ptree xml;
    boost::property_tree::read_xml(stream, xml);

    BOOST_REQUIRE(*odil::as_dataset(xml) == *data_set);
    BOOST_REQUIRE(compare_ptree(xml, odil::as_xml(data_set)));
}

BOOST_AUTO_TEST_CASE(EmptyDataSet)
{
    // Baseline data set
    auto data_set = std::make_shared<odil::DataSet>();

    // Baseline XML
    std::stringstream stream;
    stream
        << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
        << "<NativeDicomModel>"
        << "</NativeDicomModel>";

    boost::property_tree::ptree xml;
    boost::property_tree::read_xml(stream, xml);

    BOOST_REQUIRE(*odil::as_dataset(xml) == *data_set);
    BOOST_REQUIRE(compare_ptree(xml, odil::as_xml(data_set)));
}

BOOST_AUTO_TEST_CASE(EmptyValue)
{
    auto const tag = odil::registry::SelectorSSValue;
    auto const vr = odil::VR::SS;
    odil::Value::Integers const value;

    std::stringstream stream;
    for(unsigned int i=0; i<value.size(); ++i)
    {
        stream
            << "<Value " << "number=\"" << 1+i << "\">"
            << value[i]
            << "</Value>\n";
    }

    test_parsing(tag, vr, value, ""/*stream.str()*/);
}

BOOST_AUTO_TEST_CASE(IntValues)
{
    auto const tag = odil::registry::SelectorSSValue;
    auto const vr = odil::VR::SS;
    odil::Value::Integers const value{-12, -34};

    std::stringstream stream;
    for(unsigned int i=0; i<value.size(); ++i)
    {
        stream
            << "<Value " << "number=\"" << 1+i << "\">"
            << value[i]
            << "</Value>\n";
    }

    test_parsing(tag, vr, value, stream.str());
}


BOOST_AUTO_TEST_CASE(RealValues)
{
    auto const tag = odil::registry::SelectorFLValue;
    auto const vr = odil::VR::FL;
    odil::Value::Reals const value{1.2, -3.4};

    std::stringstream stream;
    for(unsigned int i=0; i<value.size(); ++i)
    {
        stream
            << "<Value " << "number=\"" << 1+i << "\">"
            << value[i]
            << "</Value>\n";
    }

    test_parsing(tag, vr, value, stream.str());
}

BOOST_AUTO_TEST_CASE(StringValues)
{
    auto const tag = odil::registry::SelectorCSValue;
    auto const vr = odil::VR::CS;
    odil::Value::Strings const value{"foo", "bar"};

    std::stringstream stream;
    for(unsigned int i=0; i<value.size(); ++i)
    {
        stream
            << "<Value " << "number=\"" << 1+i << "\">"
            << value[i]
            << "</Value>\n";
    }

    test_parsing(tag, vr, value, stream.str());
}

BOOST_AUTO_TEST_CASE(BulkDataURI)
{
    auto const bulk_data_creator =
        [](std::shared_ptr<odil::DataSet const>, odil::Tag const & tag)
        {
            std::pair<std::string, std::string> result;
            if(tag == odil::registry::EncapsulatedDocument)
            {
                result.first = "uri";
                result.second = "http://example.com";
            }
            return result;
        };

    auto const tag = odil::registry::EncapsulatedDocument;
    auto const vr = odil::VR::OB;
    odil::Value::Binary const odil_value{{0x01, 0x02, 0x03, 0x04}};

    std::string const xml_value = "<BulkData uri=\"http://example.com\"/>";

    // Baseline data set
    auto data_set = std::make_shared<odil::DataSet>();
    data_set->add(tag, odil_value);

    // Bulk-data data set
    auto bulk_data_set = std::make_shared<odil::DataSet>();
    bulk_data_set->add(tag, {"http://example.com"}, odil::VR::UR);

    // Baseline XML
    std::stringstream stream;
    stream
        << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
        << "<NativeDicomModel>"
        << "<DicomAttribute "
            << "tag=\"" << tag << "\" "
            << "vr=\"" << odil::as_string(vr) << "\" "
            << "keyword=\"" << tag.get_name() << "\">";
    stream << xml_value;
    stream
        << "</DicomAttribute>"
        << "</NativeDicomModel>";

    boost::property_tree::ptree xml;
    boost::property_tree::read_xml(stream, xml);

    BOOST_REQUIRE(*odil::as_dataset(xml) == *bulk_data_set);
    BOOST_REQUIRE(compare_ptree(xml, odil::as_xml(data_set, bulk_data_creator)));
}

BOOST_AUTO_TEST_CASE(BulkDataUUID)
{
    auto const bulk_data_creator =
        [](std::shared_ptr<odil::DataSet const>, odil::Tag const & tag)
        {
            std::pair<std::string, std::string> result;
            if(tag == odil::registry::EncapsulatedDocument)
            {
                result.first = "uuid";
                result.second = "http://example.com";
            }
            return result;
        };

    auto const tag = odil::registry::EncapsulatedDocument;
    auto const vr = odil::VR::OB;
    odil::Value::Binary const odil_value{{0x01, 0x02, 0x03, 0x04}};

    std::string const xml_value = "<BulkData uuid=\"http://example.com\"/>";

    // Baseline data set
    auto data_set = std::make_shared<odil::DataSet>();
    data_set->add(tag, odil_value);

    // Bulk-data data set
    auto bulk_data_set = std::make_shared<odil::DataSet>();
    bulk_data_set->add(tag, {"http://example.com"}, odil::VR::UR);

    // Baseline XML
    std::stringstream stream;
    stream
        << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
        << "<NativeDicomModel>"
        << "<DicomAttribute "
            << "tag=\"" << tag << "\" "
            << "vr=\"" << odil::as_string(vr) << "\" "
            << "keyword=\"" << tag.get_name() << "\">";
    stream << xml_value;
    stream
        << "</DicomAttribute>"
        << "</NativeDicomModel>";

    boost::property_tree::ptree xml;
    boost::property_tree::read_xml(stream, xml);

    BOOST_REQUIRE(*odil::as_dataset(xml) == *bulk_data_set);
    BOOST_REQUIRE(compare_ptree(xml, odil::as_xml(data_set, bulk_data_creator)));
}

BOOST_AUTO_TEST_CASE(PersonNameSingleRepresentationSingleComponent)
{
    auto const tag = odil::registry::SelectorPNValue;
    auto const vr = odil::VR::PN;
    odil::Value::Strings const value{"Last"};

    std::stringstream stream;
    stream
        << "<PersonName number=\"1\">"
            << "<Alphabetic>"
                << "<FamilyName>" << "Last" << "</FamilyName>"
            << "</Alphabetic>"
        << "</PersonName>";

    test_parsing(tag, vr, value, stream.str());
}

BOOST_AUTO_TEST_CASE(PersonNameSingleRepresentationMultipleComponent)
{
    auto const tag = odil::registry::SelectorPNValue;
    auto const vr = odil::VR::PN;
    odil::Value::Strings const value{"Last^^^Dr"};

    std::stringstream stream;
    stream
        << "<PersonName number=\"1\">"
            << "<Alphabetic>"
                << "<FamilyName>" << "Last" << "</FamilyName>"
                << "<NamePrefix>" << "Dr" << "</NamePrefix>"
            << "</Alphabetic>"
        << "</PersonName>";

    test_parsing(tag, vr, value, stream.str());
}

BOOST_AUTO_TEST_CASE(PersonNameMultipleRepresentationSingleComponent)
{
    auto const tag = odil::registry::SelectorPNValue;
    auto const vr = odil::VR::PN;
    odil::Value::Strings const value{"Last==Family"};

    std::stringstream stream;
    stream
        << "<PersonName number=\"1\">"
            << "<Alphabetic>"
                << "<FamilyName>" << "Last" << "</FamilyName>"
            << "</Alphabetic>"
            << "<Phonetic>"
                << "<FamilyName>" << "Family" << "</FamilyName>"
            << "</Phonetic>"
        << "</PersonName>";

    test_parsing(tag, vr, value, stream.str());
}

BOOST_AUTO_TEST_CASE(PersonNameMultipleRepresentationMultipleComponent)
{
    auto const tag = odil::registry::SelectorPNValue;
    auto const vr = odil::VR::PN;
    odil::Value::Strings const value{"Last^^X^Dr==Family^^^Mr"};

    std::stringstream stream;
    stream
        << "<PersonName number=\"1\">"
            << "<Alphabetic>"
                << "<FamilyName>" << "Last" << "</FamilyName>"
                << "<MiddleName>" << "X" << "</MiddleName>"
                << "<NamePrefix>" << "Dr" << "</NamePrefix>"
            << "</Alphabetic>"
            << "<Phonetic>"
                << "<FamilyName>" << "Family" << "</FamilyName>"
                << "<NamePrefix>" << "Mr" << "</NamePrefix>"
            << "</Phonetic>"
        << "</PersonName>";

    test_parsing(tag, vr, value, stream.str());
}

BOOST_AUTO_TEST_CASE(Item)
{
    auto const tag = odil::registry::ReferencedSeriesSequence;
    auto const vr = odil::VR::SQ;
    auto data_set_1 = std::make_shared<odil::DataSet>();
    data_set_1->add("PatientID", {"DJ1234"});
    auto data_set_2 = std::make_shared<odil::DataSet>();
    data_set_2->add("NumberOfSeriesRelatedInstances", {1234});
    odil::Value::DataSets const value{data_set_1, data_set_2};

    std::stringstream stream;
    stream
        << "<Item number=\"1\">"
            << "<DicomAttribute tag=\"00100020\" keyword=\"PatientID\" vr=\"LO\">"
                << "<Value number=\"1\">DJ1234</Value>"
            << "</DicomAttribute>"
        << "</Item>"
        << "<Item number=\"2\">"
            << "<DicomAttribute tag=\"00201209\" keyword=\"NumberOfSeriesRelatedInstances\" vr=\"IS\">"
                << "<Value number=\"1\">1234</Value>"
            << "</DicomAttribute>"
        << "</Item>";

    test_parsing(tag, vr, value, stream.str());
}

BOOST_AUTO_TEST_CASE(InlineBinary)
{
    auto const tag = odil::registry::SelectorOWValue;
    auto const vr = odil::VR::OW;
    odil::Value::Binary const value{{0x01, 0x02, 0x03, 0x04}};

    std::stringstream stream;
    stream << "<InlineBinary>AQIDBA==</InlineBinary>";

    test_parsing(tag, vr, value, stream.str());
}

BOOST_AUTO_TEST_CASE(MissingRootNode)
{
    BOOST_REQUIRE_THROW(
        odil::as_dataset(boost::property_tree::ptree()), odil::Exception);
}

BOOST_AUTO_TEST_CASE(BadVRCreation)
{
    auto data_set = std::make_shared<odil::DataSet>();
    data_set->add(odil::registry::PatientID, {"value"}, odil::VR::INVALID);
    BOOST_REQUIRE_THROW(odil::as_xml(data_set), odil::Exception);
}

BOOST_AUTO_TEST_CASE(BadVRParsing)
{
    std::stringstream stream;
    stream
        << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
        << "<NativeDicomModel>"
        << "<DicomAttribute "
            << "tag=\"00100010\" "
            << "vr=\"XX\" "
            << "keyword=\"PatientName\">"
        << "</DicomAttribute>"
        << "</NativeDicomModel>";

    boost::property_tree::ptree xml;
    boost::property_tree::read_xml(stream, xml);

    BOOST_REQUIRE_THROW(odil::as_dataset(xml), odil::Exception);
}
