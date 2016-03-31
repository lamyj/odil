#define BOOST_TEST_MODULE xml_converter
#include <boost/test/unit_test.hpp>

#include "odil/xml_converter.h"

void check_attributes(boost::property_tree::ptree const & xml,
                      std::string const & tag,
                      std::string const & vr,
                      std::string const & keyword)
{
    BOOST_REQUIRE_EQUAL(xml.size(), 3);

    auto it_attr = xml.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "vr");
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), vr);
    BOOST_REQUIRE((*it_attr).second.empty());

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "tag");
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), tag);
    BOOST_REQUIRE((*it_attr).second.empty());

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "keyword");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), keyword);
}

template<typename TValueType>
void check_value(boost::property_tree::ptree const & xml,
                 TValueType const & values, int count)
{
    BOOST_REQUIRE_EQUAL(xml.size(), 1);
    BOOST_CHECK_EQUAL(
            xml.get_value<typename TValueType::value_type>(),
            values[count]);

    // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL(xml.front().first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL(xml.front().second.size(), 1);

    auto it_attr = xml.front().second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), count + 1);
}

template<typename TValueType>
void check_response(boost::property_tree::ptree const & xml,
                    std::string const & tag,
                    std::string const & vr,
                    std::string const & keyword,
                    TValueType const & values)
{
    BOOST_REQUIRE_EQUAL(xml.size(), 1);
    BOOST_CHECK_EQUAL(xml.front().first, "NativeDicomModel");

    auto const native_dicom_model = xml.front().second;

    BOOST_REQUIRE_EQUAL(native_dicom_model.size(), 1);
    BOOST_CHECK_EQUAL(native_dicom_model.front().first, "DicomAttribute");
    BOOST_REQUIRE_EQUAL(native_dicom_model.front().second.size(),
                        values.size() + 1);

    // Should contains <xmlattr>
    BOOST_REQUIRE_EQUAL(
                native_dicom_model.front().second.find("<xmlattr>")->first,
                "<xmlattr>");

    int count = 0;
    for (auto it = native_dicom_model.front().second.begin();
         it != native_dicom_model.front().second.end(); ++it)
    {
        if ((*it).first == "<xmlattr>")
        {
            check_attributes((*it).second, tag, vr, keyword);
        }
        else if ((*it).first == "Value")
        {
            BOOST_CHECK_EQUAL((*it).first, "Value");
            check_value(it->second, values, count);
            ++count;
        }
        else
        {
            BOOST_FAIL("Unexpected tag");
        }
    }

    BOOST_REQUIRE_EQUAL(count, values.size());
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLEmpty)
{
    odil::DataSet data_set;
    auto const xml = odil::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel />

    BOOST_REQUIRE_EQUAL(xml.size(), 1);
    BOOST_CHECK_EQUAL(xml.front().first, "NativeDicomModel");
    BOOST_REQUIRE(xml.front().second.empty());
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLIntegers)
{
    odil::DataSet data_set;
    data_set.add(0x00280010,
        odil::Element(odil::Value::Integers({1, 2}), odil::VR::US));
    auto const xml = odil::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel>
    //     <DicomAttribute vr="US" tag="00280010" keyword="Rows">
    //         <Value number="1">1</Value>
    //         <Value number="2">2</Value>
    //     </DicomAttribute>
    // </NativeDicomModel>

    check_response(xml, "00280010", "US", "Rows",
                   odil::Value::Integers({1, 2}));
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLReals)
{
    odil::DataSet data_set;
    data_set.add(0x00089459,
        odil::Element(odil::Value::Reals({1.2, 3.4}), odil::VR::FL));
    auto const xml = odil::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel>
    //     <DicomAttribute vr="FL" tag="00089459"
    //                     keyword="RecommendedDisplayFrameRateInFloat">
    //         <Value number="1">1.2</Value>
    //         <Value number="2">3.4</Value>
    //     </DicomAttribute>
    // </NativeDicomModel>

    check_response(xml, "00089459", "FL", "RecommendedDisplayFrameRateInFloat",
                   odil::Value::Reals({1.2, 3.4}));
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLStrings)
{
    odil::DataSet data_set;
    data_set.add(0x00080060,
        odil::Element(
            odil::Value::Strings({"FOO", "BAR"}),
            odil::VR::CS));
    auto const xml = odil::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel>
    //     <DicomAttribute vr="CS" tag="00080060" keyword="Modality">
    //         <Value number="1">FOO</Value>
    //         <Value number="2">BAR</Value>
    //     </DicomAttribute>
    // </NativeDicomModel>

    check_response(xml, "00080060", "CS", "Modality",
                   odil::Value::Strings({"FOO", "BAR"}));
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLPersonName)
{
    odil::DataSet data_set;
    data_set.add(0x00100010,
        odil::Element(
            odil::Value::Strings({"Alpha^Betic=Ideo^Graphic=Pho^Netic",
                                     "family^given^middle^prefix^suffix"}),
            odil::VR::PN));
    auto const xml = odil::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel>
    //     <DicomAttribute vr="PN" tag="00100010" keyword="PatientName">
    //         <PersonName number="1">
    //             <Alphabetic>
    //                 <FamilyName>Alpha</FamilyName>
    //                 <GivenName>Betic</GivenName>
    //             </Alphabetic>
    //             <Ideographic>
    //                 <FamilyName>Ideo</FamilyName>
    //                 <GivenName>Graphic</GivenName>
    //             </Ideographic>
    //             <Phonetic>
    //                 <FamilyName>Pho</FamilyName>
    //                 <GivenName>Netic</GivenName>
    //             </Phonetic>
    //         </PersonName>
    //         <PersonName number="2">
    //             <Alphabetic>
    //                 <FamilyName>family</FamilyName>
    //                 <GivenName>given</GivenName>
    //                 <MiddleName>middle</MiddleName>
    //                 <NamePrefix>prefix</NamePrefix>
    //                 <NameSuffix>suffix</NameSuffix>
    //             </Alphabetic>
    //         </PersonName>
    //     </DicomAttribute>
    // </NativeDicomModel>

    BOOST_REQUIRE_EQUAL(xml.size(), 1);
    BOOST_CHECK_EQUAL(xml.front().first, "NativeDicomModel");

    auto const native_dicom_model = xml.front().second;

    BOOST_REQUIRE_EQUAL(native_dicom_model.size(), 1);
    BOOST_CHECK_EQUAL(native_dicom_model.front().first, "DicomAttribute");
    BOOST_REQUIRE_EQUAL(native_dicom_model.front().second.size(), 3);

    // Should contains <xmlattr>
    BOOST_REQUIRE_EQUAL(
                native_dicom_model.front().second.find("<xmlattr>")->first,
                "<xmlattr>");

    std::vector<std::map<std::string,
                         std::map<std::string, std::string> > > values;
    std::map<std::string, std::map<std::string, std::string> > person_name1;
    {
    std::map<std::string, std::string> person_name_sub;
    person_name_sub.insert(std::pair<std::string, std::string>("FamilyName",
                                                               "Alpha"));
    person_name_sub.insert(std::pair<std::string, std::string>("GivenName",
                                                               "Betic"));
    person_name1.insert(std::pair<std::string,
                        std::map<std::string, std::string> >("Alphabetic",
                                                             person_name_sub));
    }
    {
    std::map<std::string, std::string> person_name_sub;
    person_name_sub.insert(std::pair<std::string, std::string>("FamilyName",
                                                               "Ideo"));
    person_name_sub.insert(std::pair<std::string, std::string>("GivenName",
                                                               "Graphic"));
    person_name1.insert(std::pair<std::string,
                        std::map<std::string, std::string> >("Ideographic",
                                                             person_name_sub));
    }
    {
    std::map<std::string, std::string> person_name_sub;
    person_name_sub.insert(std::pair<std::string, std::string>("FamilyName",
                                                               "Pho"));
    person_name_sub.insert(std::pair<std::string, std::string>("GivenName",
                                                               "Netic"));
    person_name1.insert(std::pair<std::string,
                        std::map<std::string, std::string> >("Phonetic",
                                                             person_name_sub));
    }
    values.push_back(person_name1);
    std::map<std::string, std::map<std::string, std::string> > person_name2;
    {
    std::map<std::string, std::string> person_name_sub;
    person_name_sub.insert(std::pair<std::string, std::string>("FamilyName",
                                                               "family"));
    person_name_sub.insert(std::pair<std::string, std::string>("GivenName",
                                                               "given"));
    person_name_sub.insert(std::pair<std::string, std::string>("MiddleName",
                                                               "middle"));
    person_name_sub.insert(std::pair<std::string, std::string>("NamePrefix",
                                                               "prefix"));
    person_name_sub.insert(std::pair<std::string, std::string>("NameSuffix",
                                                               "suffix"));
    person_name2.insert(std::pair<std::string,
                        std::map<std::string, std::string> >("Alphabetic",
                                                             person_name_sub));
    }
    values.push_back(person_name2);

    int count = 0;
    for (auto it = native_dicom_model.front().second.begin();
         it != native_dicom_model.front().second.end(); ++it)
    {
        if ((*it).first == "<xmlattr>")
        {
            // Look for Attribut of DicomAttribute XML tag
            BOOST_CHECK_EQUAL((*it).first, "<xmlattr>");
            check_attributes((*it).second, "00100010", "PN", "PatientName");
        }
        else if ((*it).first == "PersonName")
        {
            BOOST_REQUIRE_EQUAL((*it).second.size(),
                                values[count].size() + 1); // + 1 for <xmlattr>

            // Should contains <xmlattr>
            BOOST_REQUIRE_EQUAL(
                        (*it).second.find("<xmlattr>")->first, "<xmlattr>");

            auto const fields = { "Alphabetic", "Ideographic", "Phonetic" };
            for (auto it_pname = (*it).second.begin();
                 it_pname != (*it).second.end(); ++it_pname)
            {
                if ((*it_pname).first == "<xmlattr>")
                {
                    BOOST_CHECK_EQUAL((*it_pname).first, "<xmlattr>");
                    BOOST_REQUIRE_EQUAL((*it_pname).second.size(), 1);

                    auto it_attr = (*it_pname).second.begin();

                    BOOST_CHECK_EQUAL((*it_attr).first, "number");
                    BOOST_REQUIRE((*it_attr).second.empty());
                    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(),
                                      count + 1);
                }
                else if (std::find(fields.begin(),
                                   fields.end(),
                                   (*it_pname).first) != fields.end())
                {
                    BOOST_REQUIRE_EQUAL((*it_pname).second.size(),
                                        values[count][(*it_pname).first].size());

                    auto const fields_name = { "NameSuffix", "NamePrefix",
                                               "MiddleName", "GivenName",
                                               "FamilyName" };
                    for (auto it_subpname = (*it_pname).second.begin();
                         it_subpname != (*it_pname).second.end(); ++it_subpname)
                    {
                        if (std::find(fields_name.begin(),  fields_name.end(),
                                      (*it_subpname).first) != fields_name.end())
                        {
                            BOOST_REQUIRE((*it_subpname).second.empty());
                            BOOST_CHECK_EQUAL((*it_subpname).second.
                                get_value<std::string>(),
                                values[count][(*it_pname).first]
                                    [(*it_subpname).first]);
                        }
                        else
                        {
                            std::stringstream error;
                            error << "Unexpected tag: " << (*it_subpname).first;
                            BOOST_FAIL(error.str());
                        }
                    }
                }
                else
                {
                    std::stringstream error;
                    error << "Unexpected tag: " << (*it_pname).first;
                    BOOST_FAIL(error.str());
                }
            }

            ++count;
        }
        else
        {
            BOOST_FAIL("Unexpected tag");
        }
    }

    BOOST_REQUIRE_EQUAL(count, values.size());
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLDataSets)
{
    odil::DataSet item1;
    item1.add(0x00100020,
        odil::Element(odil::Value::Strings({"valueLO1"}),
                         odil::VR::LO));
    item1.add(0x00100022,
        odil::Element(odil::Value::Strings({"valueCS1"}),
                         odil::VR::CS));
    odil::DataSet item2;
    item2.add(0x00100022,
        odil::Element(odil::Value::Strings({"valueCS2"}),
                         odil::VR::CS));
    odil::DataSet data_set;
    data_set.add(0x00101002,
        odil::Element(
            odil::Value::DataSets({item1, item2}),
            odil::VR::SQ));

    auto const xml = odil::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel>
    //     <DicomAttribute vr="SQ" tag="00101002"
    //                     keyword="OtherPatientIDsSequence">
    //         <Item number="1">
    //             <DicomAttribute vr="LO" tag="00100020" keyword="PatientID">
    //                 <Value number="1">valueLO1</Value>
    //             </DicomAttribute>
    //             <DicomAttribute vr="CS" tag="00100022"
    //                             keyword="TypeOfPatientID">
    //                 <Value number="1">valueCS1</Value>
    //             </DicomAttribute>
    //         </Item>
    //         <Item number="2">
    //             <DicomAttribute vr="CS" tag="00100022"
    //                             keyword="TypeOfPatientID">
    //                 <Value number="1">valueCS2</Value>
    //             </DicomAttribute>
    //         </Item>
    //     </DicomAttribute>
    // </NativeDicomModel>

    BOOST_REQUIRE_EQUAL(xml.size(), 1);
    BOOST_CHECK_EQUAL(xml.front().first, "NativeDicomModel");

    auto const native_dicom_model = xml.front().second;

    BOOST_REQUIRE_EQUAL(native_dicom_model.size(), 1);
    BOOST_CHECK_EQUAL(native_dicom_model.front().first, "DicomAttribute");
    BOOST_REQUIRE_EQUAL(native_dicom_model.front().second.size(), 3);

    odil::Value::DataSets expected_values({item1, item2});

    int count = 0;
    for (auto it = native_dicom_model.front().second.begin();
         it != native_dicom_model.front().second.end(); ++it)
    {
        if ((*it).first == "<xmlattr>")
        {
            // Look for Attribut of DicomAttribute XML tag
            BOOST_CHECK_EQUAL((*it).first, "<xmlattr>");
            check_attributes((*it).second, "00101002", "SQ",
                             "OtherPatientIDsSequence");
        }
        else if ((*it).first == "Item")
        {
            auto current_value = expected_values[count].begin();

            BOOST_REQUIRE_EQUAL((*it).second.size(),
                                expected_values[count].size() + 1);

            // Should contains <xmlattr>
            BOOST_REQUIRE_EQUAL(
                        (*it).second.find("<xmlattr>")->first, "<xmlattr>");

            for (auto it_item = (*it).second.begin();
                 it_item != (*it).second.end(); ++it_item)
            {
                if ((*it_item).first == "<xmlattr>")
                {
                    BOOST_REQUIRE_EQUAL((*it_item).second.size(), 1);

                    auto it_attr = (*it_item).second.begin();

                    BOOST_CHECK_EQUAL((*it_attr).first, "number");
                    BOOST_REQUIRE((*it_attr).second.empty());
                    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(),
                                      count + 1);
                }
                else if ((*it_item).first == "DicomAttribute")
                {
                    BOOST_REQUIRE_EQUAL((*it_item).second.size(), 2);

                    // Should contains <xmlattr>
                    BOOST_REQUIRE_EQUAL(
                                (*it_item).second.find("<xmlattr>")->first,
                                "<xmlattr>");

                    for (auto it_dicomattr = (*it_item).second.begin();
                         it_dicomattr != (*it_item).second.end(); ++it_dicomattr)
                    {
                        if ((*it_dicomattr).first == "<xmlattr>")
                        {
                            check_attributes((*it_dicomattr).second,
                                             std::string(current_value->first),
                                             odil::as_string(
                                                 current_value->second.vr),
                                             current_value->first.get_name());
                        }
                        else if ((*it_dicomattr).first == "Value")
                        {
                            check_value((*it_dicomattr).second,
                                        current_value->second.as_string(), 0);
                        }
                        else
                        {
                            std::stringstream error;
                            error << "Unexpected tag: " << (*it_dicomattr).first;
                            BOOST_FAIL(error.str());
                        }
                    }

                    ++current_value;
                }
                else
                {
                    std::stringstream error;
                    error << "Unexpected tag: " << (*it_item).first;
                    BOOST_FAIL(error.str());
                }
            }

            ++count;
        }
        else
        {
            std::stringstream error;
            error << "Unexpected tag: " << (*it).first;
            BOOST_FAIL(error.str());
        }
    }

    BOOST_REQUIRE_EQUAL(count, expected_values.size());
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLBinary)
{
    odil::DataSet data_set;
    data_set.add(0x00660023,
        odil::Element(
            odil::Value::Binary({0x1, 0x2, 0x3, 0x4, 0x5}),
            odil::VR::OW));

    auto const xml = odil::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel>
    //     <DicomAttribute vr="OW" tag="00660023"
    //                     keyword="TrianglePointIndexList">
    //         <InlineBinary>AQIDBAU=</InlineBinary>
    //     </DicomAttribute>
    // </NativeDicomModel>

    BOOST_REQUIRE_EQUAL(xml.size(), 1);
    BOOST_CHECK_EQUAL(xml.front().first, "NativeDicomModel");

    auto const native_dicom_model = xml.front().second;

    BOOST_REQUIRE_EQUAL(native_dicom_model.size(), 1);
    BOOST_CHECK_EQUAL(native_dicom_model.front().first, "DicomAttribute");
    BOOST_REQUIRE_EQUAL(native_dicom_model.front().second.size(), 2);

    // Should contains <xmlattr>
    BOOST_REQUIRE_EQUAL(
                native_dicom_model.front().second.find("<xmlattr>")->first,
                "<xmlattr>");

    int count = 0;
    for (auto it = native_dicom_model.front().second.begin();
         it != native_dicom_model.front().second.end(); ++it)
    {
        if ((*it).first == "<xmlattr>")
        {
            check_attributes((*it).second, "00660023", "OW",
                             "TrianglePointIndexList");
        }
        else if ((*it).first == "InlineBinary")
        {
            BOOST_REQUIRE((*it).second.empty());
            BOOST_CHECK_EQUAL((*it).second.get_value<std::string>(), "AQIDBAU=");
            ++count;
        }
        else
        {
            std::stringstream error;
            error << "Unexpected tag: " << (*it).first;
            BOOST_FAIL(error.str());
        }
    }

    BOOST_REQUIRE_EQUAL(count, 1);
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLEmptyElement)
{
    odil::DataSet data_set;
    data_set.add(0x00080060,
        odil::Element(
            odil::Value::Strings({}),
            odil::VR::CS));
    auto const xml = odil::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel>
    //     <DicomAttribute vr="CS" tag="00080060" keyword="Modality" />
    // </NativeDicomModel>

    check_response(xml, "00080060", "CS", "Modality",
                   odil::Value::Strings({}));
}

/******************************* TEST Error ************************************/
BOOST_AUTO_TEST_CASE(AsXMLInvalidPersonName)
{
    // Too many values separate by '^'
    {
    odil::DataSet data_set;
    data_set.add(0x00100010,
        odil::Element(
            odil::Value::Strings({"Alpha^Betic^Ideo^Graphic^Pho^Netic"}),
            odil::VR::PN));
    BOOST_REQUIRE_THROW(odil::as_xml(data_set), odil::Exception);
    }

    // Too many values separate by '='
    {
    odil::DataSet data_set;
    data_set.add(0x00100010,
        odil::Element(
            odil::Value::Strings(
                {"Alpha^Betic=Ideo^Graphic=Pho^Netic=Bad^Value"}),
            odil::VR::PN));
    BOOST_REQUIRE_THROW(odil::as_xml(data_set), odil::Exception);
    }
}

/******************************* TEST Error ************************************/
BOOST_AUTO_TEST_CASE(AsXMLBadVR)
{
    odil::DataSet data_set;
    data_set.add(0x00080060,
        odil::Element(
            odil::Value::Strings({"value"}),
            odil::VR::UNKNOWN));
    BOOST_REQUIRE_THROW(odil::as_xml(data_set), odil::Exception);
}

template<typename TValueType>
odil::DataSet create_dataset(std::string const & tag, std::string const & vr,
                                std::string const & keyword,
                                TValueType const & values,
                                std::vector<int> const & order)
{
    boost::property_tree::ptree dicomattribute;
    dicomattribute.put("<xmlattr>.vr", vr);
    dicomattribute.put("<xmlattr>.tag", tag);
    dicomattribute.put("<xmlattr>.keyword", keyword);

    for (unsigned int i = 0; i < values.size(); ++i)
    {
        boost::property_tree::ptree tag_value;
        tag_value.put("<xmlattr>.number", order[i] + 1);
        tag_value.put_value(values[order[i]]);
        dicomattribute.add_child("Value", tag_value);
    }

    boost::property_tree::ptree nativedicommodel;
    nativedicommodel.add_child("DicomAttribute", dicomattribute);

    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    return odil::as_dataset(dataset_xml);
}

template<typename T>
void create_dataset_error(std::string const & tag, std::string const & vr,
                          std::string const & keyword,
                          T const & value)
{
    boost::property_tree::ptree dicomattribute;
    dicomattribute.put("<xmlattr>.vr", vr);
    dicomattribute.put("<xmlattr>.tag", tag);
    dicomattribute.put("<xmlattr>.keyword", keyword);

    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 1);
    tag_value.put_value(value);
    dicomattribute.add_child("BadNode", tag_value);

    boost::property_tree::ptree nativedicommodel;
    nativedicommodel.add_child("DicomAttribute", dicomattribute);

    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    // throw Exception
    odil::as_dataset(dataset_xml);
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsDataSetEmpty)
{
    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", boost::property_tree::ptree());

    odil::DataSet const data_set = odil::as_dataset(dataset_xml);
    BOOST_REQUIRE(data_set.empty());
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsDataSetIntegers)
{
    odil::Value::Integers values({128, 256});

    // Tag Value sorted by number and not sorted
    std::vector<std::vector<int> > orders = {{0, 1}, {1, 0}};
    for (auto order : orders)
    {
        auto const data_set = create_dataset("00280010", "US", "Rows",
                                             values, order);
        BOOST_REQUIRE_EQUAL(data_set.size(), 1);
        BOOST_REQUIRE(data_set.has("00280010"));
        BOOST_REQUIRE(data_set.get_vr("00280010") == odil::VR::US);
        BOOST_REQUIRE(data_set.is_int("00280010"));
        BOOST_REQUIRE(data_set.as_int("00280010") == values);
    }
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsDataSetReals)
{
    odil::Value::Reals values({1.2, 3.4});

    // Tag Value sorted by number and not sorted
    std::vector<std::vector<int> > orders = {{0, 1}, {1, 0}};
    for (auto order : orders)
    {
        auto const data_set = create_dataset(
                    "00089459", "FL", "RecommendedDisplayFrameRateInFloat",
                    values, order);
        BOOST_REQUIRE_EQUAL(data_set.size(), 1);
        BOOST_REQUIRE(data_set.has("00089459"));
        BOOST_REQUIRE(data_set.get_vr("00089459") == odil::VR::FL);
        BOOST_REQUIRE(data_set.is_real("00089459"));
        BOOST_REQUIRE(data_set.as_real("00089459") == values);
    }
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsDataSetStrings)
{
    odil::Value::Strings values({"FOO", "BAR"});

    // Tag Value sorted by number and not sorted
    std::vector<std::vector<int> > orders = {{0, 1}, {1, 0}};
    for (auto order : orders)
    {
        auto const data_set = create_dataset("00080060", "CS", "Modality",
                                             values, order);
        BOOST_REQUIRE_EQUAL(data_set.size(), 1);
        BOOST_REQUIRE(data_set.has("00080060"));
        BOOST_REQUIRE(data_set.get_vr("00080060") == odil::VR::CS);
        BOOST_REQUIRE(data_set.is_string("00080060"));
        BOOST_REQUIRE(data_set.as_string("00080060") == values);
    }
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsDataSetPersonName)
{
    std::vector<std::map<std::string,
            std::map<std::string, std::string> > > values;

    std::map<std::string, std::string> name;
    name.insert(std::pair<std::string, std::string>("FamilyName", "family"));
    name.insert(std::pair<std::string, std::string>("GivenName", "given"));
    name.insert(std::pair<std::string, std::string>("MiddleName", "middle"));
    name.insert(std::pair<std::string, std::string>("NamePrefix", "prefix"));
    name.insert(std::pair<std::string, std::string>("NameSuffix", "suffix"));

    std::map<std::string, std::map<std::string, std::string> > person_name1;
    person_name1.insert(std::pair<std::string,
                        std::map<std::string, std::string> >("Alphabetic",
                                                             name));

    values.push_back(person_name1);

    std::map<std::string, std::string> name2;
    name2.insert(std::pair<std::string, std::string>("FamilyName", "family"));

    std::map<std::string, std::map<std::string, std::string> > person_name2;
    person_name2.insert(std::pair<std::string,
                        std::map<std::string, std::string> >("Alphabetic",
                                                             name2));
    person_name2.insert(std::pair<std::string,
                        std::map<std::string, std::string> >("Ideographic",
                                                             name2));
    person_name2.insert(std::pair<std::string,
                        std::map<std::string, std::string> >("Phonetic", name2));

    values.push_back(person_name2);

    std::vector<std::vector<int> > orders = {{0, 1}, {1, 0}};
    for (auto order : orders)
    {
        boost::property_tree::ptree dicomattribute;
        dicomattribute.put("<xmlattr>.vr", "PN");
        dicomattribute.put("<xmlattr>.tag", "00100010");
        dicomattribute.put("<xmlattr>.keyword", "PatientName");

        for (int number : order)
        {
            boost::property_tree::ptree tag_value;
            tag_value.put("<xmlattr>.number", number + 1);

            for (auto it = values[number].begin();
                 it != values[number].end(); ++it)
            {
                boost::property_tree::ptree tag_pname;
                for (auto it_name = it->second.begin();
                     it_name != it->second.end(); ++it_name)
                {
                    boost::property_tree::ptree tag_name;
                    tag_name.put_value(it_name->second);
                    tag_pname.add_child(it_name->first, tag_name);
                }

                tag_value.add_child(it->first, tag_pname);
            }

            dicomattribute.add_child("PersonName", tag_value);
        }

        boost::property_tree::ptree nativedicommodel;
        nativedicommodel.add_child("DicomAttribute", dicomattribute);

        boost::property_tree::ptree dataset_xml;
        dataset_xml.add_child("NativeDicomModel", nativedicommodel);

        odil::DataSet const data_set = odil::as_dataset(dataset_xml);
        BOOST_REQUIRE_EQUAL(data_set.size(), 1);
        BOOST_REQUIRE(data_set.has("00100010"));
        BOOST_REQUIRE(data_set.get_vr("00100010") == odil::VR::PN);
        BOOST_REQUIRE(data_set.is_string("00100010"));
        BOOST_REQUIRE(data_set.as_string("00100010") == odil::Value::Strings(
            {"family^given^middle^prefix^suffix", "family=family=family"}));
    }
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsDataSetDataSets)
{
    odil::DataSet item1;
    item1.add(0x00100020,
        odil::Element(odil::Value::Strings({"FOO"}), odil::VR::LO));
    item1.add(0x00100022,
        odil::Element(odil::Value::Strings({"BAR"}), odil::VR::CS));
    odil::DataSet item2;
    item2.add(0x00100020,
        odil::Element(odil::Value::Strings({"OTHER"}), odil::VR::LO));

    odil::Value::DataSets expected_result({item1, item2});

    std::vector<std::vector<int> > orders = {{0, 1}, {1, 0}};
    for (auto order : orders)
    {
        boost::property_tree::ptree dicomattribute;
        dicomattribute.put("<xmlattr>.vr", "SQ");
        dicomattribute.put("<xmlattr>.tag", "00101002");
        dicomattribute.put("<xmlattr>.keyword", "OtherPatientIDsSequence");

        for (int number : order)
        {
            boost::property_tree::ptree tag_value;
            tag_value.put("<xmlattr>.number", number + 1);

            for (auto it = expected_result[number].begin();
                 it != expected_result[number].end(); ++it)
            {
                boost::property_tree::ptree subdicomattribute;
                subdicomattribute.put("<xmlattr>.vr",
                                      odil::as_string(it->second.vr));
                subdicomattribute.put("<xmlattr>.tag", std::string(it->first));
                subdicomattribute.put("<xmlattr>.keyword", it->first.get_name());

                for (auto value : it->second.as_string())
                {
                    boost::property_tree::ptree subtag_value;
                    subtag_value.put("<xmlattr>.number", 1);
                    subtag_value.put_value(value);
                    subdicomattribute.add_child("Value", subtag_value);
                }

                boost::property_tree::ptree nativedicommodel;
                tag_value.add_child("DicomAttribute", subdicomattribute);
            }

            dicomattribute.add_child("Item", tag_value);
        }

        boost::property_tree::ptree nativedicommodel;
        nativedicommodel.add_child("DicomAttribute", dicomattribute);

        boost::property_tree::ptree dataset_xml;
        dataset_xml.add_child("NativeDicomModel", nativedicommodel);

        odil::DataSet const data_set = odil::as_dataset(dataset_xml);
        BOOST_REQUIRE_EQUAL(data_set.size(), 1);
        BOOST_REQUIRE(data_set.has("00101002"));
        BOOST_REQUIRE(data_set.get_vr("00101002") == odil::VR::SQ);
        BOOST_REQUIRE(data_set.is_data_set("00101002"));

        BOOST_REQUIRE(data_set.as_data_set("00101002") == expected_result);
    }
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsDataSetBinary)
{
    boost::property_tree::ptree dicomattribute;
    dicomattribute.put("<xmlattr>.vr", "OW");
    dicomattribute.put("<xmlattr>.tag", "00660023");
    dicomattribute.put("<xmlattr>.keyword", "TrianglePointIndexList");
    {
    boost::property_tree::ptree tag_value;
    tag_value.put_value("AQIDBAU=");
    dicomattribute.add_child("InlineBinary", tag_value);
    }

    boost::property_tree::ptree nativedicommodel;
    nativedicommodel.add_child("DicomAttribute", dicomattribute);

    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    odil::DataSet const data_set = odil::as_dataset(dataset_xml);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("00660023"));
    BOOST_REQUIRE(data_set.get_vr("00660023") == odil::VR::OW);
    BOOST_REQUIRE(data_set.is_binary("00660023"));
    BOOST_REQUIRE(data_set.as_binary("00660023") == odil::Value::Binary(
        {0x1, 0x2, 0x3, 0x4, 0x5}));
}

/******************************* TEST Error ************************************/
BOOST_AUTO_TEST_CASE(AsDataSetMissingRootNode)
{
    BOOST_REQUIRE_THROW(odil::as_dataset(boost::property_tree::ptree()),
                        odil::Exception);
}

/******************************* TEST Error ************************************/
BOOST_AUTO_TEST_CASE(AsDataSetBadDICOMNode)
{
    boost::property_tree::ptree nativedicommodel;
    nativedicommodel.add_child("BadValue", boost::property_tree::ptree());

    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    BOOST_REQUIRE_THROW(odil::as_dataset(dataset_xml), odil::Exception);
}

/******************************* TEST Error ************************************/
BOOST_AUTO_TEST_CASE(AsDataSetBadDicomAttributeSubNode)
{
    // String value
    BOOST_REQUIRE_THROW(create_dataset_error("00080060", "CS",
                                             "Modality", "FOO"),
                        odil::Exception);

    { // Person Name
    boost::property_tree::ptree dicomattribute;
    dicomattribute.put("<xmlattr>.vr", "PN");
    dicomattribute.put("<xmlattr>.tag", "00100010");
    dicomattribute.put("<xmlattr>.keyword", "PatientName");

    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 1);
    boost::property_tree::ptree tag_pname;
    boost::property_tree::ptree tag_family;
    tag_family.put_value("family");
    tag_pname.add_child("FamilyName", tag_family);
    tag_value.add_child("Alphabetic", tag_pname);
    dicomattribute.add_child("BadNode", tag_value);

    boost::property_tree::ptree nativedicommodel;
    nativedicommodel.add_child("DicomAttribute", dicomattribute);

    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    BOOST_REQUIRE_THROW(odil::as_dataset(dataset_xml), odil::Exception);
    }

    // Real value
    BOOST_REQUIRE_THROW(create_dataset_error(
                            "00089459", "FL",
                            "RecommendedDisplayFrameRateInFloat", 1.2),
                        odil::Exception);

    // Integer value
    BOOST_REQUIRE_THROW(create_dataset_error("00280010", "US", "Rows", 1),
                        odil::Exception);

    { // Sequence
    boost::property_tree::ptree dicomattribute;
    dicomattribute.put("<xmlattr>.vr", "SQ");
    dicomattribute.put("<xmlattr>.tag", "00101002");
    dicomattribute.put("<xmlattr>.keyword", "OtherPatientIDsSequence");

    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 1);
    dicomattribute.add_child("BadNode", tag_value);

    boost::property_tree::ptree nativedicommodel;
    nativedicommodel.add_child("DicomAttribute", dicomattribute);

    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    BOOST_REQUIRE_THROW(odil::as_dataset(dataset_xml), odil::Exception);
    }

    // Binary
    BOOST_REQUIRE_THROW(create_dataset_error(
                            "00660023", "OW",
                            "TrianglePointIndexList", "AQIDBAU="),
                        odil::Exception);
}

/******************************* TEST Error ************************************/
BOOST_AUTO_TEST_CASE(AsDataSetUnknownVR)
{
    BOOST_REQUIRE_THROW(create_dataset_error("00080060", "UR",
                                             "Modality", "FOO"),
                        odil::Exception);
}

/******************************* TEST Error ************************************/
BOOST_AUTO_TEST_CASE(AsDataSetBadPersonNameSubNode)
{
    boost::property_tree::ptree dicomattribute;
    dicomattribute.put("<xmlattr>.vr", "PN");
    dicomattribute.put("<xmlattr>.tag", "00100010");
    dicomattribute.put("<xmlattr>.keyword", "PatientName");

    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 1);
    boost::property_tree::ptree tag_pname;
    boost::property_tree::ptree tag_family;
    tag_family.put_value("family");
    tag_pname.add_child("FamilyName", tag_family);
    tag_value.add_child("BadNode", tag_pname);
    dicomattribute.add_child("PersonName", tag_value);

    boost::property_tree::ptree nativedicommodel;
    nativedicommodel.add_child("DicomAttribute", dicomattribute);

    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    BOOST_REQUIRE_THROW(odil::as_dataset(dataset_xml), odil::Exception);
}

/******************************* TEST Error ************************************/
BOOST_AUTO_TEST_CASE(AsDataSetBadAlphabeticSubNode)
{
    boost::property_tree::ptree dicomattribute;
    dicomattribute.put("<xmlattr>.vr", "PN");
    dicomattribute.put("<xmlattr>.tag", "00100010");
    dicomattribute.put("<xmlattr>.keyword", "PatientName");

    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 1);
    boost::property_tree::ptree tag_pname;
    boost::property_tree::ptree tag_family;
    tag_family.put_value("family");
    tag_pname.add_child("BadNode", tag_family);
    tag_value.add_child("Alphabetic", tag_pname);
    dicomattribute.add_child("PersonName", tag_value);

    boost::property_tree::ptree nativedicommodel;
    nativedicommodel.add_child("DicomAttribute", dicomattribute);

    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    BOOST_REQUIRE_THROW(odil::as_dataset(dataset_xml), odil::Exception);
}

/******************************* TEST Error ************************************/
BOOST_AUTO_TEST_CASE(AsDataSetTooManyInlineBinaryNode)
{
    boost::property_tree::ptree dicomattribute;
    dicomattribute.put("<xmlattr>.vr", "OW");
    dicomattribute.put("<xmlattr>.tag", "00660023");
    dicomattribute.put("<xmlattr>.keyword", "TrianglePointIndexList");
    {
    boost::property_tree::ptree tag_value;
    tag_value.put_value("AQIDBAU=");
    dicomattribute.add_child("InlineBinary", tag_value);
    }
    {
    boost::property_tree::ptree tag_value;
    tag_value.put_value("AQIDBAU=");
    dicomattribute.add_child("InlineBinary", tag_value);
    }

    boost::property_tree::ptree nativedicommodel;
    nativedicommodel.add_child("DicomAttribute", dicomattribute);

    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    BOOST_REQUIRE_THROW(odil::as_dataset(dataset_xml), odil::Exception);
}
