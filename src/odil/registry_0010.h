/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0010
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0010

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const PatientName(0x0010, 0x0010);
Tag const PatientID(0x0010, 0x0020);
Tag const IssuerOfPatientID(0x0010, 0x0021);
Tag const TypeOfPatientID(0x0010, 0x0022);
Tag const IssuerOfPatientIDQualifiersSequence(0x0010, 0x0024);
Tag const SourcePatientGroupIdentificationSequence(0x0010, 0x0026);
Tag const GroupOfPatientsIdentificationSequence(0x0010, 0x0027);
Tag const SubjectRelativePositionInImage(0x0010, 0x0028);
Tag const PatientBirthDate(0x0010, 0x0030);
Tag const PatientBirthTime(0x0010, 0x0032);
Tag const PatientBirthDateInAlternativeCalendar(0x0010, 0x0033);
Tag const PatientDeathDateInAlternativeCalendar(0x0010, 0x0034);
Tag const PatientAlternativeCalendar(0x0010, 0x0035);
Tag const PatientSex(0x0010, 0x0040);
Tag const PatientInsurancePlanCodeSequence(0x0010, 0x0050);
Tag const PatientPrimaryLanguageCodeSequence(0x0010, 0x0101);
Tag const PatientPrimaryLanguageModifierCodeSequence(0x0010, 0x0102);
Tag const QualityControlSubject(0x0010, 0x0200);
Tag const QualityControlSubjectTypeCodeSequence(0x0010, 0x0201);
Tag const StrainDescription(0x0010, 0x0212);
Tag const StrainNomenclature(0x0010, 0x0213);
Tag const StrainStockNumber(0x0010, 0x0214);
Tag const StrainSourceRegistryCodeSequence(0x0010, 0x0215);
Tag const StrainStockSequence(0x0010, 0x0216);
Tag const StrainSource(0x0010, 0x0217);
Tag const StrainAdditionalInformation(0x0010, 0x0218);
Tag const StrainCodeSequence(0x0010, 0x0219);
Tag const GeneticModificationsSequence(0x0010, 0x0221);
Tag const GeneticModificationsDescription(0x0010, 0x0222);
Tag const GeneticModificationsNomenclature(0x0010, 0x0223);
Tag const GeneticModificationsCodeSequence(0x0010, 0x0229);
Tag const OtherPatientIDs(0x0010, 0x1000);
Tag const OtherPatientNames(0x0010, 0x1001);
Tag const OtherPatientIDsSequence(0x0010, 0x1002);
Tag const PatientBirthName(0x0010, 0x1005);
Tag const PatientAge(0x0010, 0x1010);
Tag const PatientSize(0x0010, 0x1020);
Tag const PatientSizeCodeSequence(0x0010, 0x1021);
Tag const PatientBodyMassIndex(0x0010, 0x1022);
Tag const MeasuredAPDimension(0x0010, 0x1023);
Tag const MeasuredLateralDimension(0x0010, 0x1024);
Tag const PatientWeight(0x0010, 0x1030);
Tag const PatientAddress(0x0010, 0x1040);
Tag const InsurancePlanIdentification(0x0010, 0x1050);
Tag const PatientMotherBirthName(0x0010, 0x1060);
Tag const MilitaryRank(0x0010, 0x1080);
Tag const BranchOfService(0x0010, 0x1081);
Tag const MedicalRecordLocator(0x0010, 0x1090);
Tag const ReferencedPatientPhotoSequence(0x0010, 0x1100);
Tag const MedicalAlerts(0x0010, 0x2000);
Tag const Allergies(0x0010, 0x2110);
Tag const CountryOfResidence(0x0010, 0x2150);
Tag const RegionOfResidence(0x0010, 0x2152);
Tag const PatientTelephoneNumbers(0x0010, 0x2154);
Tag const PatientTelecomInformation(0x0010, 0x2155);
Tag const EthnicGroup(0x0010, 0x2160);
Tag const Occupation(0x0010, 0x2180);
Tag const SmokingStatus(0x0010, 0x21a0);
Tag const AdditionalPatientHistory(0x0010, 0x21b0);
Tag const PregnancyStatus(0x0010, 0x21c0);
Tag const LastMenstrualDate(0x0010, 0x21d0);
Tag const PatientReligiousPreference(0x0010, 0x21f0);
Tag const PatientSpeciesDescription(0x0010, 0x2201);
Tag const PatientSpeciesCodeSequence(0x0010, 0x2202);
Tag const PatientSexNeutered(0x0010, 0x2203);
Tag const AnatomicalOrientationType(0x0010, 0x2210);
Tag const PatientBreedDescription(0x0010, 0x2292);
Tag const PatientBreedCodeSequence(0x0010, 0x2293);
Tag const BreedRegistrationSequence(0x0010, 0x2294);
Tag const BreedRegistrationNumber(0x0010, 0x2295);
Tag const BreedRegistryCodeSequence(0x0010, 0x2296);
Tag const ResponsiblePerson(0x0010, 0x2297);
Tag const ResponsiblePersonRole(0x0010, 0x2298);
Tag const ResponsibleOrganization(0x0010, 0x2299);
Tag const PatientComments(0x0010, 0x4000);
Tag const ExaminedBodyThickness(0x0010, 0x9431);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0010