/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <map>
#include <string>
#include <tuple>

#include "odil/ElementsDictionary.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{

void update_0010(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0010, 0x0010), ElementsDictionaryEntry("Patient's Name", "PatientName",  "PN", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0020), ElementsDictionaryEntry("Patient ID", "PatientID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0021), ElementsDictionaryEntry("Issuer of Patient ID", "IssuerOfPatientID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0022), ElementsDictionaryEntry("Type of Patient ID", "TypeOfPatientID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0024), ElementsDictionaryEntry("Issuer of Patient ID Qualifiers Sequence", "IssuerOfPatientIDQualifiersSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0026), ElementsDictionaryEntry("Source Patient Group Identification Sequence", "SourcePatientGroupIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0027), ElementsDictionaryEntry("Group of Patients Identification Sequence", "GroupOfPatientsIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0028), ElementsDictionaryEntry("Subject Relative Position in Image", "SubjectRelativePositionInImage",  "US", "3"));
    public_dictionary.emplace(Tag(0x0010, 0x0030), ElementsDictionaryEntry("Patient's Birth Date", "PatientBirthDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0032), ElementsDictionaryEntry("Patient's Birth Time", "PatientBirthTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0033), ElementsDictionaryEntry("Patient's Birth Date in Alternative Calendar", "PatientBirthDateInAlternativeCalendar",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0034), ElementsDictionaryEntry("Patient's Death Date in Alternative Calendar", "PatientDeathDateInAlternativeCalendar",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0035), ElementsDictionaryEntry("Patient's Alternative Calendar", "PatientAlternativeCalendar",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0040), ElementsDictionaryEntry("Patient's Sex", "PatientSex",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0050), ElementsDictionaryEntry("Patient's Insurance Plan Code Sequence", "PatientInsurancePlanCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0101), ElementsDictionaryEntry("Patient's Primary Language Code Sequence", "PatientPrimaryLanguageCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0102), ElementsDictionaryEntry("Patient's Primary Language Modifier Code Sequence", "PatientPrimaryLanguageModifierCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0200), ElementsDictionaryEntry("Quality Control Subject", "QualityControlSubject",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0201), ElementsDictionaryEntry("Quality Control Subject Type Code Sequence", "QualityControlSubjectTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0212), ElementsDictionaryEntry("Strain Description", "StrainDescription",  "UC", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0213), ElementsDictionaryEntry("Strain Nomenclature", "StrainNomenclature",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0214), ElementsDictionaryEntry("Strain Stock Number", "StrainStockNumber",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0215), ElementsDictionaryEntry("Strain Source Registry Code Sequence", "StrainSourceRegistryCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0216), ElementsDictionaryEntry("Strain Stock Sequence", "StrainStockSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0217), ElementsDictionaryEntry("Strain Source", "StrainSource",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0218), ElementsDictionaryEntry("Strain Additional Information", "StrainAdditionalInformation",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0219), ElementsDictionaryEntry("Strain Code Sequence", "StrainCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0221), ElementsDictionaryEntry("Genetic Modifications Sequence", "GeneticModificationsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0222), ElementsDictionaryEntry("Genetic Modifications Description", "GeneticModificationsDescription",  "UC", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0223), ElementsDictionaryEntry("Genetic Modifications Nomenclature", "GeneticModificationsNomenclature",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x0229), ElementsDictionaryEntry("Genetic Modifications Code Sequence", "GeneticModificationsCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1000), ElementsDictionaryEntry("Other Patient IDs", "OtherPatientIDs",  "LO", "1-n"));
    public_dictionary.emplace(Tag(0x0010, 0x1001), ElementsDictionaryEntry("Other Patient Names", "OtherPatientNames",  "PN", "1-n"));
    public_dictionary.emplace(Tag(0x0010, 0x1002), ElementsDictionaryEntry("Other Patient IDs Sequence", "OtherPatientIDsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1005), ElementsDictionaryEntry("Patient's Birth Name", "PatientBirthName",  "PN", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1010), ElementsDictionaryEntry("Patient's Age", "PatientAge",  "AS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1020), ElementsDictionaryEntry("Patient's Size", "PatientSize",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1021), ElementsDictionaryEntry("Patient's Size Code Sequence", "PatientSizeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1022), ElementsDictionaryEntry("Patient's Body Mass Index", "PatientBodyMassIndex",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1023), ElementsDictionaryEntry("Measured AP Dimension", "MeasuredAPDimension",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1024), ElementsDictionaryEntry("Measured Lateral Dimension", "MeasuredLateralDimension",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1030), ElementsDictionaryEntry("Patient's Weight", "PatientWeight",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1040), ElementsDictionaryEntry("Patient's Address", "PatientAddress",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1050), ElementsDictionaryEntry("Insurance Plan Identification", "InsurancePlanIdentification",  "LO", "1-n"));
    public_dictionary.emplace(Tag(0x0010, 0x1060), ElementsDictionaryEntry("Patient's Mother's Birth Name", "PatientMotherBirthName",  "PN", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1080), ElementsDictionaryEntry("Military Rank", "MilitaryRank",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1081), ElementsDictionaryEntry("Branch of Service", "BranchOfService",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1090), ElementsDictionaryEntry("Medical Record Locator", "MedicalRecordLocator",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x1100), ElementsDictionaryEntry("Referenced Patient Photo Sequence", "ReferencedPatientPhotoSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2000), ElementsDictionaryEntry("Medical Alerts", "MedicalAlerts",  "LO", "1-n"));
    public_dictionary.emplace(Tag(0x0010, 0x2110), ElementsDictionaryEntry("Allergies", "Allergies",  "LO", "1-n"));
    public_dictionary.emplace(Tag(0x0010, 0x2150), ElementsDictionaryEntry("Country of Residence", "CountryOfResidence",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2152), ElementsDictionaryEntry("Region of Residence", "RegionOfResidence",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2154), ElementsDictionaryEntry("Patient's Telephone Numbers", "PatientTelephoneNumbers",  "SH", "1-n"));
    public_dictionary.emplace(Tag(0x0010, 0x2155), ElementsDictionaryEntry("Patient's Telecom Information", "PatientTelecomInformation",  "LT", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2160), ElementsDictionaryEntry("Ethnic Group", "EthnicGroup",  "SH", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2180), ElementsDictionaryEntry("Occupation", "Occupation",  "SH", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x21a0), ElementsDictionaryEntry("Smoking Status", "SmokingStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x21b0), ElementsDictionaryEntry("Additional Patient History", "AdditionalPatientHistory",  "LT", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x21c0), ElementsDictionaryEntry("Pregnancy Status", "PregnancyStatus",  "US", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x21d0), ElementsDictionaryEntry("Last Menstrual Date", "LastMenstrualDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x21f0), ElementsDictionaryEntry("Patient's Religious Preference", "PatientReligiousPreference",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2201), ElementsDictionaryEntry("Patient Species Description", "PatientSpeciesDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2202), ElementsDictionaryEntry("Patient Species Code Sequence", "PatientSpeciesCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2203), ElementsDictionaryEntry("Patient's Sex Neutered", "PatientSexNeutered",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2210), ElementsDictionaryEntry("Anatomical Orientation Type", "AnatomicalOrientationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2292), ElementsDictionaryEntry("Patient Breed Description", "PatientBreedDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2293), ElementsDictionaryEntry("Patient Breed Code Sequence", "PatientBreedCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2294), ElementsDictionaryEntry("Breed Registration Sequence", "BreedRegistrationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2295), ElementsDictionaryEntry("Breed Registration Number", "BreedRegistrationNumber",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2296), ElementsDictionaryEntry("Breed Registry Code Sequence", "BreedRegistryCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2297), ElementsDictionaryEntry("Responsible Person", "ResponsiblePerson",  "PN", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2298), ElementsDictionaryEntry("Responsible Person Role", "ResponsiblePersonRole",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x2299), ElementsDictionaryEntry("Responsible Organization", "ResponsibleOrganization",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x4000), ElementsDictionaryEntry("Patient Comments", "PatientComments",  "LT", "1"));
    public_dictionary.emplace(Tag(0x0010, 0x9431), ElementsDictionaryEntry("Examined Body Thickness", "ExaminedBodyThickness",  "FL", "1"));

    public_tags.emplace("PatientName", Tag(0x0010, 0x0010));
    public_tags.emplace("PatientID", Tag(0x0010, 0x0020));
    public_tags.emplace("IssuerOfPatientID", Tag(0x0010, 0x0021));
    public_tags.emplace("TypeOfPatientID", Tag(0x0010, 0x0022));
    public_tags.emplace("IssuerOfPatientIDQualifiersSequence", Tag(0x0010, 0x0024));
    public_tags.emplace("SourcePatientGroupIdentificationSequence", Tag(0x0010, 0x0026));
    public_tags.emplace("GroupOfPatientsIdentificationSequence", Tag(0x0010, 0x0027));
    public_tags.emplace("SubjectRelativePositionInImage", Tag(0x0010, 0x0028));
    public_tags.emplace("PatientBirthDate", Tag(0x0010, 0x0030));
    public_tags.emplace("PatientBirthTime", Tag(0x0010, 0x0032));
    public_tags.emplace("PatientBirthDateInAlternativeCalendar", Tag(0x0010, 0x0033));
    public_tags.emplace("PatientDeathDateInAlternativeCalendar", Tag(0x0010, 0x0034));
    public_tags.emplace("PatientAlternativeCalendar", Tag(0x0010, 0x0035));
    public_tags.emplace("PatientSex", Tag(0x0010, 0x0040));
    public_tags.emplace("PatientInsurancePlanCodeSequence", Tag(0x0010, 0x0050));
    public_tags.emplace("PatientPrimaryLanguageCodeSequence", Tag(0x0010, 0x0101));
    public_tags.emplace("PatientPrimaryLanguageModifierCodeSequence", Tag(0x0010, 0x0102));
    public_tags.emplace("QualityControlSubject", Tag(0x0010, 0x0200));
    public_tags.emplace("QualityControlSubjectTypeCodeSequence", Tag(0x0010, 0x0201));
    public_tags.emplace("StrainDescription", Tag(0x0010, 0x0212));
    public_tags.emplace("StrainNomenclature", Tag(0x0010, 0x0213));
    public_tags.emplace("StrainStockNumber", Tag(0x0010, 0x0214));
    public_tags.emplace("StrainSourceRegistryCodeSequence", Tag(0x0010, 0x0215));
    public_tags.emplace("StrainStockSequence", Tag(0x0010, 0x0216));
    public_tags.emplace("StrainSource", Tag(0x0010, 0x0217));
    public_tags.emplace("StrainAdditionalInformation", Tag(0x0010, 0x0218));
    public_tags.emplace("StrainCodeSequence", Tag(0x0010, 0x0219));
    public_tags.emplace("GeneticModificationsSequence", Tag(0x0010, 0x0221));
    public_tags.emplace("GeneticModificationsDescription", Tag(0x0010, 0x0222));
    public_tags.emplace("GeneticModificationsNomenclature", Tag(0x0010, 0x0223));
    public_tags.emplace("GeneticModificationsCodeSequence", Tag(0x0010, 0x0229));
    public_tags.emplace("OtherPatientIDs", Tag(0x0010, 0x1000));
    public_tags.emplace("OtherPatientNames", Tag(0x0010, 0x1001));
    public_tags.emplace("OtherPatientIDsSequence", Tag(0x0010, 0x1002));
    public_tags.emplace("PatientBirthName", Tag(0x0010, 0x1005));
    public_tags.emplace("PatientAge", Tag(0x0010, 0x1010));
    public_tags.emplace("PatientSize", Tag(0x0010, 0x1020));
    public_tags.emplace("PatientSizeCodeSequence", Tag(0x0010, 0x1021));
    public_tags.emplace("PatientBodyMassIndex", Tag(0x0010, 0x1022));
    public_tags.emplace("MeasuredAPDimension", Tag(0x0010, 0x1023));
    public_tags.emplace("MeasuredLateralDimension", Tag(0x0010, 0x1024));
    public_tags.emplace("PatientWeight", Tag(0x0010, 0x1030));
    public_tags.emplace("PatientAddress", Tag(0x0010, 0x1040));
    public_tags.emplace("InsurancePlanIdentification", Tag(0x0010, 0x1050));
    public_tags.emplace("PatientMotherBirthName", Tag(0x0010, 0x1060));
    public_tags.emplace("MilitaryRank", Tag(0x0010, 0x1080));
    public_tags.emplace("BranchOfService", Tag(0x0010, 0x1081));
    public_tags.emplace("MedicalRecordLocator", Tag(0x0010, 0x1090));
    public_tags.emplace("ReferencedPatientPhotoSequence", Tag(0x0010, 0x1100));
    public_tags.emplace("MedicalAlerts", Tag(0x0010, 0x2000));
    public_tags.emplace("Allergies", Tag(0x0010, 0x2110));
    public_tags.emplace("CountryOfResidence", Tag(0x0010, 0x2150));
    public_tags.emplace("RegionOfResidence", Tag(0x0010, 0x2152));
    public_tags.emplace("PatientTelephoneNumbers", Tag(0x0010, 0x2154));
    public_tags.emplace("PatientTelecomInformation", Tag(0x0010, 0x2155));
    public_tags.emplace("EthnicGroup", Tag(0x0010, 0x2160));
    public_tags.emplace("Occupation", Tag(0x0010, 0x2180));
    public_tags.emplace("SmokingStatus", Tag(0x0010, 0x21a0));
    public_tags.emplace("AdditionalPatientHistory", Tag(0x0010, 0x21b0));
    public_tags.emplace("PregnancyStatus", Tag(0x0010, 0x21c0));
    public_tags.emplace("LastMenstrualDate", Tag(0x0010, 0x21d0));
    public_tags.emplace("PatientReligiousPreference", Tag(0x0010, 0x21f0));
    public_tags.emplace("PatientSpeciesDescription", Tag(0x0010, 0x2201));
    public_tags.emplace("PatientSpeciesCodeSequence", Tag(0x0010, 0x2202));
    public_tags.emplace("PatientSexNeutered", Tag(0x0010, 0x2203));
    public_tags.emplace("AnatomicalOrientationType", Tag(0x0010, 0x2210));
    public_tags.emplace("PatientBreedDescription", Tag(0x0010, 0x2292));
    public_tags.emplace("PatientBreedCodeSequence", Tag(0x0010, 0x2293));
    public_tags.emplace("BreedRegistrationSequence", Tag(0x0010, 0x2294));
    public_tags.emplace("BreedRegistrationNumber", Tag(0x0010, 0x2295));
    public_tags.emplace("BreedRegistryCodeSequence", Tag(0x0010, 0x2296));
    public_tags.emplace("ResponsiblePerson", Tag(0x0010, 0x2297));
    public_tags.emplace("ResponsiblePersonRole", Tag(0x0010, 0x2298));
    public_tags.emplace("ResponsibleOrganization", Tag(0x0010, 0x2299));
    public_tags.emplace("PatientComments", Tag(0x0010, 0x4000));
    public_tags.emplace("ExaminedBodyThickness", Tag(0x0010, 0x9431));
}

}

}