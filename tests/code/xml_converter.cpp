#define BOOST_TEST_MODULE xml_converter
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/xml_converter.h"

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLEmpty)
{
    dcmtkpp::DataSet data_set;
    auto const xml = dcmtkpp::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel />

    BOOST_REQUIRE_EQUAL(xml.size(), 1);
    BOOST_CHECK_EQUAL(xml.front().first, "NativeDicomModel");
    BOOST_REQUIRE(xml.front().second.empty());
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLIntegers)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0x00280010,
        dcmtkpp::Element(dcmtkpp::Value::Integers({1, 2}), dcmtkpp::VR::US));
    auto const xml = dcmtkpp::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel>
    //     <DicomAttribute vr="US" tag="00280010" keyword="Rows">
    //         <Value number="1">1</Value>
    //         <Value number="2">2</Value>
    //     </DicomAttribute>
    // </NativeDicomModel>

    BOOST_REQUIRE_EQUAL(xml.size(), 1);
    BOOST_CHECK_EQUAL(xml.front().first, "NativeDicomModel");

    auto const native_dicom_model = xml.front().second;

    BOOST_REQUIRE_EQUAL(native_dicom_model.size(), 1);
    BOOST_CHECK_EQUAL(native_dicom_model.front().first, "DicomAttribute");
    BOOST_REQUIRE_EQUAL(native_dicom_model.front().second.size(), 3);

    auto it = native_dicom_model.front().second.begin();

    { // Look for Attribut of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 3);

    auto it_attr = (*it).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "vr");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "US");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "tag");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "00280010");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "keyword");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "Rows");
    }

    ++it;

    { // Look for First child of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "Value");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 1);
    BOOST_CHECK_EQUAL((*it).second.get_value<int>(), 1);

    { // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL((*it).second.front().first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it).second.front().second.size(), 1);

    auto it_attr = (*it).second.front().second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), 1);
    }

    }

    ++it;

    { // Look for Second child of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "Value");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 1);
    BOOST_CHECK_EQUAL((*it).second.get_value<int>(), 2);

    { // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL((*it).second.front().first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it).second.front().second.size(), 1);

    auto it_attr = (*it).second.front().second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), 2);
    }

    }
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLReals)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0x00089459,
        dcmtkpp::Element(dcmtkpp::Value::Reals({1.2, 3.4}), dcmtkpp::VR::FL));
    auto const xml = dcmtkpp::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel>
    //     <DicomAttribute vr="FL" tag="00089459"
    //                     keyword="RecommendedDisplayFrameRateInFloat">
    //         <Value number="1">1.2</Value>
    //         <Value number="2">3.4</Value>
    //     </DicomAttribute>
    // </NativeDicomModel>

    BOOST_REQUIRE_EQUAL(xml.size(), 1);
    BOOST_CHECK_EQUAL(xml.front().first, "NativeDicomModel");

    auto const native_dicom_model = xml.front().second;

    BOOST_REQUIRE_EQUAL(native_dicom_model.size(), 1);
    BOOST_CHECK_EQUAL(native_dicom_model.front().first, "DicomAttribute");
    BOOST_REQUIRE_EQUAL(native_dicom_model.front().second.size(), 3);

    auto it = native_dicom_model.front().second.begin();

    { // Look for Attribut of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 3);

    auto it_attr = (*it).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "vr");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "FL");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "tag");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "00089459");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "keyword");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(),
                      "RecommendedDisplayFrameRateInFloat");
    }

    ++it;

    { // Look for First child of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "Value");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 1);
    BOOST_CHECK_EQUAL((*it).second.get_value<double>(), 1.2);

    { // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL((*it).second.front().first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it).second.front().second.size(), 1);

    auto it_attr = (*it).second.front().second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), 1);
    }

    }

    ++it;

    { // Look for Second child of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "Value");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 1);
    BOOST_CHECK_EQUAL((*it).second.get_value<double>(), 3.4);

    { // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL((*it).second.front().first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it).second.front().second.size(), 1);

    auto it_attr = (*it).second.front().second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), 2);
    }

    }
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLStrings)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0x00080060,
        dcmtkpp::Element(
            dcmtkpp::Value::Strings({"FOO", "BAR"}),
            dcmtkpp::VR::CS));
    auto const xml = dcmtkpp::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel>
    //     <DicomAttribute vr="CS" tag="00080060" keyword="Modality">
    //         <Value number="1">FOO</Value>
    //         <Value number="2">BAR</Value>
    //     </DicomAttribute>
    // </NativeDicomModel>

    BOOST_REQUIRE_EQUAL(xml.size(), 1);
    BOOST_CHECK_EQUAL(xml.front().first, "NativeDicomModel");

    auto const native_dicom_model = xml.front().second;

    BOOST_REQUIRE_EQUAL(native_dicom_model.size(), 1);
    BOOST_CHECK_EQUAL(native_dicom_model.front().first, "DicomAttribute");
    BOOST_REQUIRE_EQUAL(native_dicom_model.front().second.size(), 3);

    auto it = native_dicom_model.front().second.begin();

    { // Look for Attribut of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 3);

    auto it_attr = (*it).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "vr");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "CS");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "tag");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "00080060");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "keyword");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "Modality");
    }

    ++it;

    { // Look for First child of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "Value");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 1);
    BOOST_CHECK_EQUAL((*it).second.get_value<std::string>(), "FOO");

    { // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL((*it).second.front().first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it).second.front().second.size(), 1);

    auto it_attr = (*it).second.front().second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), 1);
    }

    }

    ++it;

    { // Look for Second child of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "Value");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 1);
    BOOST_CHECK_EQUAL((*it).second.get_value<std::string>(), "BAR");

    { // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL((*it).second.front().first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it).second.front().second.size(), 1);

    auto it_attr = (*it).second.front().second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), 2);
    }

    }
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLPersonName)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0x00100010,
        dcmtkpp::Element(
            dcmtkpp::Value::Strings({"Alpha^Betic=Ideo^Graphic=Pho^Netic",
                                     "family^given^middle^prefix^suffix"}),
            dcmtkpp::VR::PN));
    auto const xml = dcmtkpp::as_xml(data_set);

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

    auto it = native_dicom_model.front().second.begin();

    { // Look for Attribut of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 3);

    auto it_attr = (*it).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "vr");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "PN");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "tag");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "00100010");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "keyword");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "PatientName");
    }

    ++it;

    { // Look for First child of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "PersonName");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 4);

    auto it_pname = (*it).second.begin();

    { // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL((*it_pname).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it_pname).second.size(), 1);

    auto it_attr = (*it_pname).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), 1);
    }

    ++it_pname;

    { // Look for Alphabetic XML tag of PersonName XML tag
    BOOST_CHECK_EQUAL((*it_pname).first, "Alphabetic");
    BOOST_REQUIRE_EQUAL((*it_pname).second.size(), 2);

    auto it_aname = (*it_pname).second.begin();

    BOOST_CHECK_EQUAL((*it_aname).first, "FamilyName");
    BOOST_REQUIRE((*it_aname).second.empty());
    BOOST_CHECK_EQUAL((*it_aname).second.get_value<std::string>(), "Alpha");

    ++it_aname;

    BOOST_CHECK_EQUAL((*it_aname).first, "GivenName");
    BOOST_REQUIRE((*it_aname).second.empty());
    BOOST_CHECK_EQUAL((*it_aname).second.get_value<std::string>(), "Betic");
    }

    ++it_pname;

    { // Look for Ideographic XML tag of PersonName XML tag
    BOOST_CHECK_EQUAL((*it_pname).first, "Ideographic");
    BOOST_REQUIRE_EQUAL((*it_pname).second.size(), 2);

    auto it_aname = (*it_pname).second.begin();

    BOOST_CHECK_EQUAL((*it_aname).first, "FamilyName");
    BOOST_REQUIRE((*it_aname).second.empty());
    BOOST_CHECK_EQUAL((*it_aname).second.get_value<std::string>(), "Ideo");

    ++it_aname;

    BOOST_CHECK_EQUAL((*it_aname).first, "GivenName");
    BOOST_REQUIRE((*it_aname).second.empty());
    BOOST_CHECK_EQUAL((*it_aname).second.get_value<std::string>(), "Graphic");
    }

    ++it_pname;

    { // Look for Phonetic XML tag of PersonName XML tag
    BOOST_CHECK_EQUAL((*it_pname).first, "Phonetic");
    BOOST_REQUIRE_EQUAL((*it_pname).second.size(), 2);

    auto it_aname = (*it_pname).second.begin();

    BOOST_CHECK_EQUAL((*it_aname).first, "FamilyName");
    BOOST_REQUIRE((*it_aname).second.empty());
    BOOST_CHECK_EQUAL((*it_aname).second.get_value<std::string>(), "Pho");

    ++it_aname;

    BOOST_CHECK_EQUAL((*it_aname).first, "GivenName");
    BOOST_REQUIRE((*it_aname).second.empty());
    BOOST_CHECK_EQUAL((*it_aname).second.get_value<std::string>(), "Netic");
    }

    }

    ++it;

    { // Look for Second child of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "PersonName");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 2);

    auto it_pname = (*it).second.begin();

    { // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL((*it_pname).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it_pname).second.size(), 1);

    auto it_attr = (*it_pname).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), 2);
    }

    ++it_pname;

    { // Look for Alphabetic XML tag of PersonName XML tag
    BOOST_CHECK_EQUAL((*it_pname).first, "Alphabetic");
    BOOST_REQUIRE_EQUAL((*it_pname).second.size(), 5);

    auto it_aname = (*it_pname).second.begin();

    BOOST_CHECK_EQUAL((*it_aname).first, "FamilyName");
    BOOST_REQUIRE((*it_aname).second.empty());
    BOOST_CHECK_EQUAL((*it_aname).second.get_value<std::string>(), "family");

    ++it_aname;

    BOOST_CHECK_EQUAL((*it_aname).first, "GivenName");
    BOOST_REQUIRE((*it_aname).second.empty());
    BOOST_CHECK_EQUAL((*it_aname).second.get_value<std::string>(), "given");

    ++it_aname;

    BOOST_CHECK_EQUAL((*it_aname).first, "MiddleName");
    BOOST_REQUIRE((*it_aname).second.empty());
    BOOST_CHECK_EQUAL((*it_aname).second.get_value<std::string>(), "middle");

    ++it_aname;

    BOOST_CHECK_EQUAL((*it_aname).first, "NamePrefix");
    BOOST_REQUIRE((*it_aname).second.empty());
    BOOST_CHECK_EQUAL((*it_aname).second.get_value<std::string>(), "prefix");

    ++it_aname;

    BOOST_CHECK_EQUAL((*it_aname).first, "NameSuffix");
    BOOST_REQUIRE((*it_aname).second.empty());
    BOOST_CHECK_EQUAL((*it_aname).second.get_value<std::string>(), "suffix");
    }

    }
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLDataSets)
{
    dcmtkpp::DataSet item1;
    item1.add(0x00100020,
        dcmtkpp::Element(dcmtkpp::Value::Strings({"valueLO1"}),
                         dcmtkpp::VR::LO));
    item1.add(0x00100022,
        dcmtkpp::Element(dcmtkpp::Value::Strings({"valueCS1"}),
                         dcmtkpp::VR::CS));
    dcmtkpp::DataSet item2;
    item2.add(0x00100022,
        dcmtkpp::Element(dcmtkpp::Value::Strings({"valueCS2"}),
                         dcmtkpp::VR::CS));
    dcmtkpp::DataSet data_set;
    data_set.add(0x00101002,
        dcmtkpp::Element(
            dcmtkpp::Value::DataSets({item1, item2}),
            dcmtkpp::VR::SQ));

    auto const xml = dcmtkpp::as_xml(data_set);

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

    auto it = native_dicom_model.front().second.begin();

    { // Look for Attribut of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 3);

    auto it_attr = (*it).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "vr");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "SQ");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "tag");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "00101002");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "keyword");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(),
                      "OtherPatientIDsSequence");
    }

    ++it;

    { // Look for First child of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "Item");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 3);

    auto it_item = (*it).second.begin();

    { // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL((*it_item).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it_item).second.size(), 1);

    auto it_attr = (*it_item).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), 1);
    }

    ++it_item;

    { // Look for first DicomAttribute XML tag of Item XML tag
    BOOST_CHECK_EQUAL((*it_item).first, "DicomAttribute");
    BOOST_REQUIRE_EQUAL((*it_item).second.size(), 2);

    auto it_dicomattr = (*it_item).second.begin();

    {
    BOOST_CHECK_EQUAL((*it_dicomattr).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it_dicomattr).second.size(), 3);

    auto it_attr = (*it_dicomattr).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "vr");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "LO");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "tag");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "00100020");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "keyword");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "PatientID");
    }

    ++it_dicomattr;

    BOOST_CHECK_EQUAL((*it_dicomattr).first, "Value");
    BOOST_REQUIRE_EQUAL((*it_dicomattr).second.size(), 1);
    BOOST_CHECK_EQUAL((*it_dicomattr).second.get_value<std::string>(),
                      "valueLO1");

    { // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL((*it_dicomattr).second.front().first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it_dicomattr).second.front().second.size(), 1);

    auto it_attr = (*it_dicomattr).second.front().second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), 1);
    }

    }

    ++it_item;

    { // Look for second DicomAttribute XML tag of Item XML tag
    BOOST_CHECK_EQUAL((*it_item).first, "DicomAttribute");
    BOOST_REQUIRE_EQUAL((*it_item).second.size(), 2);

    auto it_dicomattr = (*it_item).second.begin();

    {
    BOOST_CHECK_EQUAL((*it_dicomattr).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it_dicomattr).second.size(), 3);

    auto it_attr = (*it_dicomattr).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "vr");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "CS");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "tag");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "00100022");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "keyword");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(),
                      "TypeOfPatientID");
    }

    ++it_dicomattr;

    BOOST_CHECK_EQUAL((*it_dicomattr).first, "Value");
    BOOST_REQUIRE_EQUAL((*it_dicomattr).second.size(), 1);
    BOOST_CHECK_EQUAL((*it_dicomattr).second.get_value<std::string>(),
                      "valueCS1");

    { // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL((*it_dicomattr).second.front().first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it_dicomattr).second.front().second.size(), 1);

    auto it_attr = (*it_dicomattr).second.front().second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), 1);
    }

    }

    }

    ++it;

    { // Look for Second child of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "Item");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 2);

    auto it_item = (*it).second.begin();

    { // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL((*it_item).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it_item).second.size(), 1);

    auto it_attr = (*it_item).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), 2);
    }

    ++it_item;

    { // Look for First DicomAttribute XML tag of Item XML tag
    BOOST_CHECK_EQUAL((*it_item).first, "DicomAttribute");
    BOOST_REQUIRE_EQUAL((*it_item).second.size(), 2);

    auto it_dicomattr = (*it_item).second.begin();

    {
    BOOST_CHECK_EQUAL((*it_dicomattr).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it_dicomattr).second.size(), 3);

    auto it_attr = (*it_dicomattr).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "vr");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "CS");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "tag");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "00100022");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "keyword");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(),
                      "TypeOfPatientID");
    }

    ++it_dicomattr;

    BOOST_CHECK_EQUAL((*it_dicomattr).first, "Value");
    BOOST_REQUIRE_EQUAL((*it_dicomattr).second.size(), 1);
    BOOST_CHECK_EQUAL((*it_dicomattr).second.get_value<std::string>(),
                      "valueCS2");

    { // Look for Attribut of Value XML tag
    BOOST_CHECK_EQUAL((*it_dicomattr).second.front().first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it_dicomattr).second.front().second.size(), 1);

    auto it_attr = (*it_dicomattr).second.front().second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "number");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<int>(), 1);
    }

    }

    }
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLBinary)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0x00660023,
        dcmtkpp::Element(
            dcmtkpp::Value::Binary({0x1, 0x2, 0x3, 0x4, 0x5}),
            dcmtkpp::VR::OW));

    auto const xml = dcmtkpp::as_xml(data_set);

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

    auto it = native_dicom_model.front().second.begin();

    { // Look for Attribut of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 3);

    auto it_attr = (*it).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "vr");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "OW");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "tag");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "00660023");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "keyword");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(),
                      "TrianglePointIndexList");
    }

    ++it;

    { // Look for First child of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "InlineBinary");
    BOOST_REQUIRE((*it).second.empty());
    BOOST_CHECK_EQUAL((*it).second.get_value<std::string>(), "AQIDBAU=");
    }
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsXMLEmptyElement)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0x00080060,
        dcmtkpp::Element(
            dcmtkpp::Value::Strings({}),
            dcmtkpp::VR::CS));
    auto const xml = dcmtkpp::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel>
    //     <DicomAttribute vr="CS" tag="00080060" keyword="Modality" />
    // </NativeDicomModel>

    BOOST_REQUIRE_EQUAL(xml.size(), 1);
    BOOST_CHECK_EQUAL(xml.front().first, "NativeDicomModel");

    auto const native_dicom_model = xml.front().second;

    BOOST_REQUIRE_EQUAL(native_dicom_model.size(), 1);
    BOOST_CHECK_EQUAL(native_dicom_model.front().first, "DicomAttribute");
    BOOST_REQUIRE_EQUAL(native_dicom_model.front().second.size(), 1);

    auto it = native_dicom_model.front().second.begin();

    { // Look for Attribut of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "<xmlattr>");
    BOOST_REQUIRE_EQUAL((*it).second.size(), 3);

    auto it_attr = (*it).second.begin();

    BOOST_CHECK_EQUAL((*it_attr).first, "vr");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "CS");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "tag");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "00080060");

    ++it_attr;

    BOOST_CHECK_EQUAL((*it_attr).first, "keyword");
    BOOST_REQUIRE((*it_attr).second.empty());
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "Modality");
    }
}

/******************************* TEST Error ************************************/
BOOST_AUTO_TEST_CASE(AsXMLInvalidPersonName)
{
    // Too many values separate by '^'
    {
    dcmtkpp::DataSet data_set;
    data_set.add(0x00100010,
        dcmtkpp::Element(
            dcmtkpp::Value::Strings({"Alpha^Betic^Ideo^Graphic^Pho^Netic"}),
            dcmtkpp::VR::PN));
    BOOST_REQUIRE_THROW(dcmtkpp::as_xml(data_set), dcmtkpp::Exception);
    }

    // Too many values separate by '='
    {
    dcmtkpp::DataSet data_set;
    data_set.add(0x00100010,
        dcmtkpp::Element(
            dcmtkpp::Value::Strings({"Alpha^Betic=Ideo^Graphic=Pho^Netic=Bad^Value"}),
            dcmtkpp::VR::PN));
    BOOST_REQUIRE_THROW(dcmtkpp::as_xml(data_set), dcmtkpp::Exception);
    }
}

/******************************* TEST Error ************************************/
BOOST_AUTO_TEST_CASE(AsXMLInvalidDICOMTag)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0xbad00bad,
        dcmtkpp::Element(
            dcmtkpp::Value::Strings({"value"}),
            dcmtkpp::VR::CS));
    BOOST_REQUIRE_THROW(dcmtkpp::as_xml(data_set), dcmtkpp::Exception);
}

/******************************* TEST Error ************************************/
BOOST_AUTO_TEST_CASE(AsXMLBadVR)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0x00080060,
        dcmtkpp::Element(
            dcmtkpp::Value::Strings({"value"}),
            dcmtkpp::VR::UNKNOWN));
    BOOST_REQUIRE_THROW(dcmtkpp::as_xml(data_set), dcmtkpp::Exception);
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsDataSetEmpty)
{
    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", boost::property_tree::ptree());

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(dataset_xml);
    BOOST_REQUIRE(data_set.empty());
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsDataSetIntegers)
{
    boost::property_tree::ptree dicomattribute;
    dicomattribute.put("<xmlattr>.vr", "US");
    dicomattribute.put("<xmlattr>.tag", "00280010");
    dicomattribute.put("<xmlattr>.keyword", "Rows");
    {
    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 1);
    tag_value.put_value(128);
    dicomattribute.add_child("Value", tag_value);
    }
    {
    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 2);
    tag_value.put_value(256);
    dicomattribute.add_child("Value", tag_value);
    }

    boost::property_tree::ptree nativedicommodel;
    nativedicommodel.add_child("DicomAttribute", dicomattribute);

    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(dataset_xml);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("00280010"));
    BOOST_REQUIRE(data_set.get_vr("00280010") == dcmtkpp::VR::US);
    BOOST_REQUIRE(data_set.is_int("00280010"));
    BOOST_REQUIRE(data_set.as_int("00280010") == dcmtkpp::Value::Integers({128, 256}));
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsDataSetReals)
{
    boost::property_tree::ptree dicomattribute;
    dicomattribute.put("<xmlattr>.vr", "FL");
    dicomattribute.put("<xmlattr>.tag", "00089459");
    dicomattribute.put("<xmlattr>.keyword", "RecommendedDisplayFrameRateInFloat");
    {
    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 1);
    tag_value.put_value(1.2);
    dicomattribute.add_child("Value", tag_value);
    }
    {
    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 2);
    tag_value.put_value(3.4);
    dicomattribute.add_child("Value", tag_value);
    }

    boost::property_tree::ptree nativedicommodel;
    nativedicommodel.add_child("DicomAttribute", dicomattribute);

    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(dataset_xml);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("00089459"));
    BOOST_REQUIRE(data_set.get_vr("00089459") == dcmtkpp::VR::FL);
    BOOST_REQUIRE(data_set.is_real("00089459"));
    BOOST_REQUIRE(data_set.as_real("00089459") == dcmtkpp::Value::Reals({1.2, 3.4}));
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsDataSetStrings)
{
    boost::property_tree::ptree dicomattribute;
    dicomattribute.put("<xmlattr>.vr", "CS");
    dicomattribute.put("<xmlattr>.tag", "00080060");
    dicomattribute.put("<xmlattr>.keyword", "Modality");
    {
    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 1);
    tag_value.put_value("FOO");
    dicomattribute.add_child("Value", tag_value);
    }
    {
    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 2);
    tag_value.put_value("BAR");
    dicomattribute.add_child("Value", tag_value);
    }

    boost::property_tree::ptree nativedicommodel;
    nativedicommodel.add_child("DicomAttribute", dicomattribute);

    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(dataset_xml);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("00080060"));
    BOOST_REQUIRE(data_set.get_vr("00080060") == dcmtkpp::VR::CS);
    BOOST_REQUIRE(data_set.is_string("00080060"));
    BOOST_REQUIRE(data_set.as_string("00080060") == dcmtkpp::Value::Strings({"FOO", "BAR"}));
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsDataSetPersonName)
{
    boost::property_tree::ptree dicomattribute;
    dicomattribute.put("<xmlattr>.vr", "PN");
    dicomattribute.put("<xmlattr>.tag", "00100010");
    dicomattribute.put("<xmlattr>.keyword", "PatientName");
    {
    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 1);
    boost::property_tree::ptree tag_pname;
    boost::property_tree::ptree tag_family;
    tag_family.put_value("family");
    tag_pname.add_child("FamilyName", tag_family);
    boost::property_tree::ptree tag_given;
    tag_given.put_value("given");
    tag_pname.add_child("GivenName", tag_given);
    boost::property_tree::ptree tag_middle;
    tag_middle.put_value("middle");
    tag_pname.add_child("MiddleName", tag_middle);
    boost::property_tree::ptree tag_prefix;
    tag_prefix.put_value("prefix");
    tag_pname.add_child("NamePrefix", tag_prefix);
    boost::property_tree::ptree tag_suffix;
    tag_suffix.put_value("suffix");
    tag_pname.add_child("NameSuffix", tag_suffix);
    tag_value.add_child("Alphabetic", tag_pname);
    dicomattribute.add_child("PersonName", tag_value);
    }
    {
    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 2);
    boost::property_tree::ptree tag_alpha;
    boost::property_tree::ptree tag_afamily;
    tag_afamily.put_value("familyAlpha");
    tag_alpha.add_child("FamilyName", tag_afamily);
    tag_value.add_child("Alphabetic", tag_alpha);
    boost::property_tree::ptree tag_ideo;
    boost::property_tree::ptree tag_ifamily;
    tag_ifamily.put_value("familyIdeo");
    tag_ideo.add_child("FamilyName", tag_ifamily);
    tag_value.add_child("Ideographic", tag_ideo);
    boost::property_tree::ptree tag_phonetic;
    boost::property_tree::ptree tag_pfamily;
    tag_pfamily.put_value("familyPhonetic");
    tag_phonetic.add_child("FamilyName", tag_pfamily);
    tag_value.add_child("Phonetic", tag_phonetic);
    dicomattribute.add_child("PersonName", tag_value);
    }

    boost::property_tree::ptree nativedicommodel;
    nativedicommodel.add_child("DicomAttribute", dicomattribute);

    boost::property_tree::ptree dataset_xml;
    dataset_xml.add_child("NativeDicomModel", nativedicommodel);

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(dataset_xml);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("00100010"));
    BOOST_REQUIRE(data_set.get_vr("00100010") == dcmtkpp::VR::PN);
    BOOST_REQUIRE(data_set.is_string("00100010"));
    BOOST_REQUIRE(data_set.as_string("00100010") == dcmtkpp::Value::Strings(
        {"family^given^middle^prefix^suffix", "familyAlpha=familyIdeo=familyPhonetic"}));
}

/******************************* TEST Nominal **********************************/
BOOST_AUTO_TEST_CASE(AsDataSetDataSets)
{
    boost::property_tree::ptree dicomattribute;
    dicomattribute.put("<xmlattr>.vr", "SQ");
    dicomattribute.put("<xmlattr>.tag", "00101002");
    dicomattribute.put("<xmlattr>.keyword", "OtherPatientIDsSequence");
    {
    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 1);

    {
    boost::property_tree::ptree subdicomattribute;
    subdicomattribute.put("<xmlattr>.vr", "LO");
    subdicomattribute.put("<xmlattr>.tag", "00100020");
    subdicomattribute.put("<xmlattr>.keyword", "PatientID");
    {
    boost::property_tree::ptree subtag_value;
    subtag_value.put("<xmlattr>.number", 1);
    subtag_value.put_value("FOO");
    subdicomattribute.add_child("Value", subtag_value);
    }

    boost::property_tree::ptree nativedicommodel;
    tag_value.add_child("DicomAttribute", subdicomattribute);
    }

    {
    boost::property_tree::ptree subdicomattribute;
    subdicomattribute.put("<xmlattr>.vr", "CS");
    subdicomattribute.put("<xmlattr>.tag", "00100022");
    subdicomattribute.put("<xmlattr>.keyword", "TypeOfPatientID");
    {
    boost::property_tree::ptree subtag_value;
    subtag_value.put("<xmlattr>.number", 1);
    subtag_value.put_value("BAR");
    subdicomattribute.add_child("Value", subtag_value);
    }

    boost::property_tree::ptree nativedicommodel;
    tag_value.add_child("DicomAttribute", subdicomattribute);
    }

    dicomattribute.add_child("Item", tag_value);
    }

    {
    boost::property_tree::ptree tag_value;
    tag_value.put("<xmlattr>.number", 2);

    {
    boost::property_tree::ptree subdicomattribute;
    subdicomattribute.put("<xmlattr>.vr", "LO");
    subdicomattribute.put("<xmlattr>.tag", "00100020");
    subdicomattribute.put("<xmlattr>.keyword", "PatientID");
    {
    boost::property_tree::ptree subtag_value;
    subtag_value.put("<xmlattr>.number", 1);
    subtag_value.put_value("OTHER");
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

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(dataset_xml);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("00101002"));
    BOOST_REQUIRE(data_set.get_vr("00101002") == dcmtkpp::VR::SQ);
    BOOST_REQUIRE(data_set.is_data_set("00101002"));

    dcmtkpp::DataSet item1;
    item1.add(0x00100020,
        dcmtkpp::Element(dcmtkpp::Value::Strings({"FOO"}), dcmtkpp::VR::LO));
    item1.add(0x00100022,
        dcmtkpp::Element(dcmtkpp::Value::Strings({"BAR"}), dcmtkpp::VR::CS));
    dcmtkpp::DataSet item2;
    item2.add(0x00100020,
        dcmtkpp::Element(dcmtkpp::Value::Strings({"OTHER"}), dcmtkpp::VR::LO));
    BOOST_REQUIRE(data_set.as_data_set("00101002") == dcmtkpp::Value::DataSets({item1, item2}));
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

    dcmtkpp::DataSet const data_set = dcmtkpp::as_dataset(dataset_xml);
    BOOST_REQUIRE_EQUAL(data_set.size(), 1);
    BOOST_REQUIRE(data_set.has("00660023"));
    BOOST_REQUIRE(data_set.get_vr("00660023") == dcmtkpp::VR::OW);
    BOOST_REQUIRE(data_set.is_binary("00660023"));
    BOOST_REQUIRE(data_set.as_binary("00660023") == dcmtkpp::Value::Binary(
        {0x1, 0x2, 0x3, 0x4, 0x5}));
}

/******************************* TEST Error ************************************/
BOOST_AUTO_TEST_CASE(AsDataSetMissingRootNode)
{
    BOOST_REQUIRE_THROW(dcmtkpp::as_dataset(boost::property_tree::ptree()),
                        dcmtkpp::Exception);
}
