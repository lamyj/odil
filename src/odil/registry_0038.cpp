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

void update_0038(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0038, 0x0004), ElementsDictionaryEntry("Referenced Patient Alias Sequence", "ReferencedPatientAliasSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0008), ElementsDictionaryEntry("Visit Status ID", "VisitStatusID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0010), ElementsDictionaryEntry("Admission ID", "AdmissionID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0011), ElementsDictionaryEntry("Issuer of Admission ID", "IssuerOfAdmissionID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0014), ElementsDictionaryEntry("Issuer of Admission ID Sequence", "IssuerOfAdmissionIDSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0016), ElementsDictionaryEntry("Route of Admissions", "RouteOfAdmissions",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x001a), ElementsDictionaryEntry("Scheduled Admission Date", "ScheduledAdmissionDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x001b), ElementsDictionaryEntry("Scheduled Admission Time", "ScheduledAdmissionTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x001c), ElementsDictionaryEntry("Scheduled Discharge Date", "ScheduledDischargeDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x001d), ElementsDictionaryEntry("Scheduled Discharge Time", "ScheduledDischargeTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x001e), ElementsDictionaryEntry("Scheduled Patient Institution Residence", "ScheduledPatientInstitutionResidence",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0020), ElementsDictionaryEntry("Admitting Date", "AdmittingDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0021), ElementsDictionaryEntry("Admitting Time", "AdmittingTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0030), ElementsDictionaryEntry("Discharge Date", "DischargeDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0032), ElementsDictionaryEntry("Discharge Time", "DischargeTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0040), ElementsDictionaryEntry("Discharge Diagnosis Description", "DischargeDiagnosisDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0044), ElementsDictionaryEntry("Discharge Diagnosis Code Sequence", "DischargeDiagnosisCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0050), ElementsDictionaryEntry("Special Needs", "SpecialNeeds",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0060), ElementsDictionaryEntry("Service Episode ID", "ServiceEpisodeID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0061), ElementsDictionaryEntry("Issuer of Service Episode ID", "IssuerOfServiceEpisodeID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0062), ElementsDictionaryEntry("Service Episode Description", "ServiceEpisodeDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0064), ElementsDictionaryEntry("Issuer of Service Episode ID Sequence", "IssuerOfServiceEpisodeIDSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0100), ElementsDictionaryEntry("Pertinent Documents Sequence", "PertinentDocumentsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0101), ElementsDictionaryEntry("Pertinent Resources Sequence", "PertinentResourcesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0102), ElementsDictionaryEntry("Resource Description", "ResourceDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0300), ElementsDictionaryEntry("Current Patient Location", "CurrentPatientLocation",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0400), ElementsDictionaryEntry("Patient's Institution Residence", "PatientInstitutionResidence",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0500), ElementsDictionaryEntry("Patient State", "PatientState",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x0502), ElementsDictionaryEntry("Patient Clinical Trial Participation Sequence", "PatientClinicalTrialParticipationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0038, 0x4000), ElementsDictionaryEntry("Visit Comments", "VisitComments",  "LT", "1"));

    public_tags.emplace("ReferencedPatientAliasSequence", Tag(0x0038, 0x0004));
    public_tags.emplace("VisitStatusID", Tag(0x0038, 0x0008));
    public_tags.emplace("AdmissionID", Tag(0x0038, 0x0010));
    public_tags.emplace("IssuerOfAdmissionID", Tag(0x0038, 0x0011));
    public_tags.emplace("IssuerOfAdmissionIDSequence", Tag(0x0038, 0x0014));
    public_tags.emplace("RouteOfAdmissions", Tag(0x0038, 0x0016));
    public_tags.emplace("ScheduledAdmissionDate", Tag(0x0038, 0x001a));
    public_tags.emplace("ScheduledAdmissionTime", Tag(0x0038, 0x001b));
    public_tags.emplace("ScheduledDischargeDate", Tag(0x0038, 0x001c));
    public_tags.emplace("ScheduledDischargeTime", Tag(0x0038, 0x001d));
    public_tags.emplace("ScheduledPatientInstitutionResidence", Tag(0x0038, 0x001e));
    public_tags.emplace("AdmittingDate", Tag(0x0038, 0x0020));
    public_tags.emplace("AdmittingTime", Tag(0x0038, 0x0021));
    public_tags.emplace("DischargeDate", Tag(0x0038, 0x0030));
    public_tags.emplace("DischargeTime", Tag(0x0038, 0x0032));
    public_tags.emplace("DischargeDiagnosisDescription", Tag(0x0038, 0x0040));
    public_tags.emplace("DischargeDiagnosisCodeSequence", Tag(0x0038, 0x0044));
    public_tags.emplace("SpecialNeeds", Tag(0x0038, 0x0050));
    public_tags.emplace("ServiceEpisodeID", Tag(0x0038, 0x0060));
    public_tags.emplace("IssuerOfServiceEpisodeID", Tag(0x0038, 0x0061));
    public_tags.emplace("ServiceEpisodeDescription", Tag(0x0038, 0x0062));
    public_tags.emplace("IssuerOfServiceEpisodeIDSequence", Tag(0x0038, 0x0064));
    public_tags.emplace("PertinentDocumentsSequence", Tag(0x0038, 0x0100));
    public_tags.emplace("PertinentResourcesSequence", Tag(0x0038, 0x0101));
    public_tags.emplace("ResourceDescription", Tag(0x0038, 0x0102));
    public_tags.emplace("CurrentPatientLocation", Tag(0x0038, 0x0300));
    public_tags.emplace("PatientInstitutionResidence", Tag(0x0038, 0x0400));
    public_tags.emplace("PatientState", Tag(0x0038, 0x0500));
    public_tags.emplace("PatientClinicalTrialParticipationSequence", Tag(0x0038, 0x0502));
    public_tags.emplace("VisitComments", Tag(0x0038, 0x4000));
}

}

}