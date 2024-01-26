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

void update_0012(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0012, 0x0010), ElementsDictionaryEntry("Clinical Trial Sponsor Name", "ClinicalTrialSponsorName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0020), ElementsDictionaryEntry("Clinical Trial Protocol ID", "ClinicalTrialProtocolID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0021), ElementsDictionaryEntry("Clinical Trial Protocol Name", "ClinicalTrialProtocolName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0030), ElementsDictionaryEntry("Clinical Trial Site ID", "ClinicalTrialSiteID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0031), ElementsDictionaryEntry("Clinical Trial Site Name", "ClinicalTrialSiteName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0040), ElementsDictionaryEntry("Clinical Trial Subject ID", "ClinicalTrialSubjectID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0042), ElementsDictionaryEntry("Clinical Trial Subject Reading ID", "ClinicalTrialSubjectReadingID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0050), ElementsDictionaryEntry("Clinical Trial Time Point ID", "ClinicalTrialTimePointID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0051), ElementsDictionaryEntry("Clinical Trial Time Point Description", "ClinicalTrialTimePointDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0052), ElementsDictionaryEntry("Longitudinal Temporal Offset from Event", "LongitudinalTemporalOffsetFromEvent",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0053), ElementsDictionaryEntry("Longitudinal Temporal Event Type", "LongitudinalTemporalEventType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0054), ElementsDictionaryEntry("Clinical Trial Time Point Type Code Sequence", "ClinicalTrialTimePointTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0060), ElementsDictionaryEntry("Clinical Trial Coordinating Center Name", "ClinicalTrialCoordinatingCenterName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0062), ElementsDictionaryEntry("Patient Identity Removed", "PatientIdentityRemoved",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0063), ElementsDictionaryEntry("De-identification Method", "DeidentificationMethod",  "LO", "1-n"));
    public_dictionary.emplace(Tag(0x0012, 0x0064), ElementsDictionaryEntry("De-identification Method Code Sequence", "DeidentificationMethodCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0071), ElementsDictionaryEntry("Clinical Trial Series ID", "ClinicalTrialSeriesID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0072), ElementsDictionaryEntry("Clinical Trial Series Description", "ClinicalTrialSeriesDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0081), ElementsDictionaryEntry("Clinical Trial Protocol Ethics Committee Name", "ClinicalTrialProtocolEthicsCommitteeName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0082), ElementsDictionaryEntry("Clinical Trial Protocol Ethics Committee Approval Number", "ClinicalTrialProtocolEthicsCommitteeApprovalNumber",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0083), ElementsDictionaryEntry("Consent for Clinical Trial Use Sequence", "ConsentForClinicalTrialUseSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0084), ElementsDictionaryEntry("Distribution Type", "DistributionType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0085), ElementsDictionaryEntry("Consent for Distribution Flag", "ConsentForDistributionFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0086), ElementsDictionaryEntry("Ethics Committee Approval Effectiveness Start Date", "EthicsCommitteeApprovalEffectivenessStartDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0012, 0x0087), ElementsDictionaryEntry("Ethics Committee Approval Effectiveness End Date", "EthicsCommitteeApprovalEffectivenessEndDate",  "DA", "1"));

    public_tags.emplace("ClinicalTrialSponsorName", Tag(0x0012, 0x0010));
    public_tags.emplace("ClinicalTrialProtocolID", Tag(0x0012, 0x0020));
    public_tags.emplace("ClinicalTrialProtocolName", Tag(0x0012, 0x0021));
    public_tags.emplace("ClinicalTrialSiteID", Tag(0x0012, 0x0030));
    public_tags.emplace("ClinicalTrialSiteName", Tag(0x0012, 0x0031));
    public_tags.emplace("ClinicalTrialSubjectID", Tag(0x0012, 0x0040));
    public_tags.emplace("ClinicalTrialSubjectReadingID", Tag(0x0012, 0x0042));
    public_tags.emplace("ClinicalTrialTimePointID", Tag(0x0012, 0x0050));
    public_tags.emplace("ClinicalTrialTimePointDescription", Tag(0x0012, 0x0051));
    public_tags.emplace("LongitudinalTemporalOffsetFromEvent", Tag(0x0012, 0x0052));
    public_tags.emplace("LongitudinalTemporalEventType", Tag(0x0012, 0x0053));
    public_tags.emplace("ClinicalTrialTimePointTypeCodeSequence", Tag(0x0012, 0x0054));
    public_tags.emplace("ClinicalTrialCoordinatingCenterName", Tag(0x0012, 0x0060));
    public_tags.emplace("PatientIdentityRemoved", Tag(0x0012, 0x0062));
    public_tags.emplace("DeidentificationMethod", Tag(0x0012, 0x0063));
    public_tags.emplace("DeidentificationMethodCodeSequence", Tag(0x0012, 0x0064));
    public_tags.emplace("ClinicalTrialSeriesID", Tag(0x0012, 0x0071));
    public_tags.emplace("ClinicalTrialSeriesDescription", Tag(0x0012, 0x0072));
    public_tags.emplace("ClinicalTrialProtocolEthicsCommitteeName", Tag(0x0012, 0x0081));
    public_tags.emplace("ClinicalTrialProtocolEthicsCommitteeApprovalNumber", Tag(0x0012, 0x0082));
    public_tags.emplace("ConsentForClinicalTrialUseSequence", Tag(0x0012, 0x0083));
    public_tags.emplace("DistributionType", Tag(0x0012, 0x0084));
    public_tags.emplace("ConsentForDistributionFlag", Tag(0x0012, 0x0085));
    public_tags.emplace("EthicsCommitteeApprovalEffectivenessStartDate", Tag(0x0012, 0x0086));
    public_tags.emplace("EthicsCommitteeApprovalEffectivenessEndDate", Tag(0x0012, 0x0087));
}

}

}