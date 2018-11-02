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

void update_4008(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x4008, 0x0040), ElementsDictionaryEntry("Results ID", "ResultsID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0042), ElementsDictionaryEntry("Results ID Issuer", "ResultsIDIssuer",  "LO", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0050), ElementsDictionaryEntry("Referenced Interpretation Sequence", "ReferencedInterpretationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x00ff), ElementsDictionaryEntry("Report Production Status (Trial)", "ReportProductionStatusTrial",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0100), ElementsDictionaryEntry("Interpretation Recorded Date", "InterpretationRecordedDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0101), ElementsDictionaryEntry("Interpretation Recorded Time", "InterpretationRecordedTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0102), ElementsDictionaryEntry("Interpretation Recorder", "InterpretationRecorder",  "PN", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0103), ElementsDictionaryEntry("Reference to Recorded Sound", "ReferenceToRecordedSound",  "LO", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0108), ElementsDictionaryEntry("Interpretation Transcription Date", "InterpretationTranscriptionDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0109), ElementsDictionaryEntry("Interpretation Transcription Time", "InterpretationTranscriptionTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x010a), ElementsDictionaryEntry("Interpretation Transcriber", "InterpretationTranscriber",  "PN", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x010b), ElementsDictionaryEntry("Interpretation Text", "InterpretationText",  "ST", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x010c), ElementsDictionaryEntry("Interpretation Author", "InterpretationAuthor",  "PN", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0111), ElementsDictionaryEntry("Interpretation Approver Sequence", "InterpretationApproverSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0112), ElementsDictionaryEntry("Interpretation Approval Date", "InterpretationApprovalDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0113), ElementsDictionaryEntry("Interpretation Approval Time", "InterpretationApprovalTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0114), ElementsDictionaryEntry("Physician Approving Interpretation", "PhysicianApprovingInterpretation",  "PN", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0115), ElementsDictionaryEntry("Interpretation Diagnosis Description", "InterpretationDiagnosisDescription",  "LT", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0117), ElementsDictionaryEntry("Interpretation Diagnosis Code Sequence", "InterpretationDiagnosisCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0118), ElementsDictionaryEntry("Results Distribution List Sequence", "ResultsDistributionListSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0119), ElementsDictionaryEntry("Distribution Name", "DistributionName",  "PN", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x011a), ElementsDictionaryEntry("Distribution Address", "DistributionAddress",  "LO", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0200), ElementsDictionaryEntry("Interpretation ID", "InterpretationID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0202), ElementsDictionaryEntry("Interpretation ID Issuer", "InterpretationIDIssuer",  "LO", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0210), ElementsDictionaryEntry("Interpretation Type ID", "InterpretationTypeID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0212), ElementsDictionaryEntry("Interpretation Status ID", "InterpretationStatusID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x0300), ElementsDictionaryEntry("Impressions", "Impressions",  "ST", "1"));
    public_dictionary.emplace(Tag(0x4008, 0x4000), ElementsDictionaryEntry("Results Comments", "ResultsComments",  "ST", "1"));

    public_tags.emplace("ResultsID", Tag(0x4008, 0x0040));
    public_tags.emplace("ResultsIDIssuer", Tag(0x4008, 0x0042));
    public_tags.emplace("ReferencedInterpretationSequence", Tag(0x4008, 0x0050));
    public_tags.emplace("ReportProductionStatusTrial", Tag(0x4008, 0x00ff));
    public_tags.emplace("InterpretationRecordedDate", Tag(0x4008, 0x0100));
    public_tags.emplace("InterpretationRecordedTime", Tag(0x4008, 0x0101));
    public_tags.emplace("InterpretationRecorder", Tag(0x4008, 0x0102));
    public_tags.emplace("ReferenceToRecordedSound", Tag(0x4008, 0x0103));
    public_tags.emplace("InterpretationTranscriptionDate", Tag(0x4008, 0x0108));
    public_tags.emplace("InterpretationTranscriptionTime", Tag(0x4008, 0x0109));
    public_tags.emplace("InterpretationTranscriber", Tag(0x4008, 0x010a));
    public_tags.emplace("InterpretationText", Tag(0x4008, 0x010b));
    public_tags.emplace("InterpretationAuthor", Tag(0x4008, 0x010c));
    public_tags.emplace("InterpretationApproverSequence", Tag(0x4008, 0x0111));
    public_tags.emplace("InterpretationApprovalDate", Tag(0x4008, 0x0112));
    public_tags.emplace("InterpretationApprovalTime", Tag(0x4008, 0x0113));
    public_tags.emplace("PhysicianApprovingInterpretation", Tag(0x4008, 0x0114));
    public_tags.emplace("InterpretationDiagnosisDescription", Tag(0x4008, 0x0115));
    public_tags.emplace("InterpretationDiagnosisCodeSequence", Tag(0x4008, 0x0117));
    public_tags.emplace("ResultsDistributionListSequence", Tag(0x4008, 0x0118));
    public_tags.emplace("DistributionName", Tag(0x4008, 0x0119));
    public_tags.emplace("DistributionAddress", Tag(0x4008, 0x011a));
    public_tags.emplace("InterpretationID", Tag(0x4008, 0x0200));
    public_tags.emplace("InterpretationIDIssuer", Tag(0x4008, 0x0202));
    public_tags.emplace("InterpretationTypeID", Tag(0x4008, 0x0210));
    public_tags.emplace("InterpretationStatusID", Tag(0x4008, 0x0212));
    public_tags.emplace("Impressions", Tag(0x4008, 0x0300));
    public_tags.emplace("ResultsComments", Tag(0x4008, 0x4000));
}

}

}