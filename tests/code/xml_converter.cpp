#define BOOST_TEST_MODULE xml_converter
#include <boost/test/unit_test.hpp>

#include "dcmtkpp/xml_converter.h"

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

BOOST_AUTO_TEST_CASE(AsXMLReals)
{
    dcmtkpp::DataSet data_set;
    data_set.add(0x00089459,
        dcmtkpp::Element(dcmtkpp::Value::Reals({1.2, 3.4}), dcmtkpp::VR::FL));
    auto const xml = dcmtkpp::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel>
    //     <DicomAttribute vr="FL" tag="00089459" keyword="RecommendedDisplayFrameRateInFloat">
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
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "RecommendedDisplayFrameRateInFloat");
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

BOOST_AUTO_TEST_CASE(AsXMLDataSets)
{
    dcmtkpp::DataSet item1;
    item1.add(0x00100020,
        dcmtkpp::Element(dcmtkpp::Value::Strings({"valueLO1"}), dcmtkpp::VR::LO));
    item1.add(0x00100022,
        dcmtkpp::Element(dcmtkpp::Value::Strings({"valueCS1"}), dcmtkpp::VR::CS));
    dcmtkpp::DataSet item2;
    item2.add(0x00100022,
        dcmtkpp::Element(dcmtkpp::Value::Strings({"valueCS2"}), dcmtkpp::VR::CS));
    dcmtkpp::DataSet data_set;
    data_set.add(0x00101002,
        dcmtkpp::Element(
            dcmtkpp::Value::DataSets({item1, item2}),
            dcmtkpp::VR::SQ));

    auto const xml = dcmtkpp::as_xml(data_set);

    // Expected result:
    // <NativeDicomModel>
    //     <DicomAttribute vr="SQ" tag="00101002" keyword="OtherPatientIDsSequence">
    //         <Item number="1">
    //             <DicomAttribute vr="LO" tag="00100020" keyword="PatientID">
    //                 <Value number="1">valueLO1</Value>
    //             </DicomAttribute>
    //             <DicomAttribute vr="CS" tag="00100022" keyword="TypeOfPatientID">
    //                 <Value number="1">valueCS1</Value>
    //             </DicomAttribute>
    //         </Item>
    //         <Item number="2">
    //             <DicomAttribute vr="CS" tag="00100022" keyword="TypeOfPatientID">
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
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "OtherPatientIDsSequence");
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
    BOOST_CHECK_EQUAL((*it_dicomattr).second.get_value<std::string>(), "valueLO1");

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
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "TypeOfPatientID");
    }

    ++it_dicomattr;

    BOOST_CHECK_EQUAL((*it_dicomattr).first, "Value");
    BOOST_REQUIRE_EQUAL((*it_dicomattr).second.size(), 1);
    BOOST_CHECK_EQUAL((*it_dicomattr).second.get_value<std::string>(), "valueCS1");

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
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "TypeOfPatientID");
    }

    ++it_dicomattr;

    BOOST_CHECK_EQUAL((*it_dicomattr).first, "Value");
    BOOST_REQUIRE_EQUAL((*it_dicomattr).second.size(), 1);
    BOOST_CHECK_EQUAL((*it_dicomattr).second.get_value<std::string>(), "valueCS2");

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
    //     <DicomAttribute vr="OW" tag="00660023" keyword="TrianglePointIndexList">
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
    BOOST_CHECK_EQUAL((*it_attr).second.get_value<std::string>(), "TrianglePointIndexList");
    }

    ++it;

    { // Look for First child of DicomAttribute XML tag
    BOOST_CHECK_EQUAL((*it).first, "InlineBinary");
    BOOST_REQUIRE((*it).second.empty());
    BOOST_CHECK_EQUAL((*it).second.get_value<std::string>(), "AQIDBAU=");
    }
}
