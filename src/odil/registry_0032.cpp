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

void update_0032(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0032, 0x000a), ElementsDictionaryEntry("Study Status ID", "StudyStatusID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x000c), ElementsDictionaryEntry("Study Priority ID", "StudyPriorityID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x0012), ElementsDictionaryEntry("Study ID Issuer", "StudyIDIssuer",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x0032), ElementsDictionaryEntry("Study Verified Date", "StudyVerifiedDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x0033), ElementsDictionaryEntry("Study Verified Time", "StudyVerifiedTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x0034), ElementsDictionaryEntry("Study Read Date", "StudyReadDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x0035), ElementsDictionaryEntry("Study Read Time", "StudyReadTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1000), ElementsDictionaryEntry("Scheduled Study Start Date", "ScheduledStudyStartDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1001), ElementsDictionaryEntry("Scheduled Study Start Time", "ScheduledStudyStartTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1010), ElementsDictionaryEntry("Scheduled Study Stop Date", "ScheduledStudyStopDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1011), ElementsDictionaryEntry("Scheduled Study Stop Time", "ScheduledStudyStopTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1020), ElementsDictionaryEntry("Scheduled Study Location", "ScheduledStudyLocation",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1021), ElementsDictionaryEntry("Scheduled Study Location AE Title", "ScheduledStudyLocationAETitle",  "AE", "1-n"));
    public_dictionary.emplace(Tag(0x0032, 0x1030), ElementsDictionaryEntry("Reason for Study", "ReasonForStudy",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1031), ElementsDictionaryEntry("Requesting Physician Identification Sequence", "RequestingPhysicianIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1032), ElementsDictionaryEntry("Requesting Physician", "RequestingPhysician",  "PN", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1033), ElementsDictionaryEntry("Requesting Service", "RequestingService",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1034), ElementsDictionaryEntry("Requesting Service Code Sequence", "RequestingServiceCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1040), ElementsDictionaryEntry("Study Arrival Date", "StudyArrivalDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1041), ElementsDictionaryEntry("Study Arrival Time", "StudyArrivalTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1050), ElementsDictionaryEntry("Study Completion Date", "StudyCompletionDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1051), ElementsDictionaryEntry("Study Completion Time", "StudyCompletionTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1055), ElementsDictionaryEntry("Study Component Status ID", "StudyComponentStatusID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1060), ElementsDictionaryEntry("Requested Procedure Description", "RequestedProcedureDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1064), ElementsDictionaryEntry("Requested Procedure Code Sequence", "RequestedProcedureCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x1070), ElementsDictionaryEntry("Requested Contrast Agent", "RequestedContrastAgent",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0032, 0x4000), ElementsDictionaryEntry("Study Comments", "StudyComments",  "LT", "1"));

    public_tags.emplace("StudyStatusID", Tag(0x0032, 0x000a));
    public_tags.emplace("StudyPriorityID", Tag(0x0032, 0x000c));
    public_tags.emplace("StudyIDIssuer", Tag(0x0032, 0x0012));
    public_tags.emplace("StudyVerifiedDate", Tag(0x0032, 0x0032));
    public_tags.emplace("StudyVerifiedTime", Tag(0x0032, 0x0033));
    public_tags.emplace("StudyReadDate", Tag(0x0032, 0x0034));
    public_tags.emplace("StudyReadTime", Tag(0x0032, 0x0035));
    public_tags.emplace("ScheduledStudyStartDate", Tag(0x0032, 0x1000));
    public_tags.emplace("ScheduledStudyStartTime", Tag(0x0032, 0x1001));
    public_tags.emplace("ScheduledStudyStopDate", Tag(0x0032, 0x1010));
    public_tags.emplace("ScheduledStudyStopTime", Tag(0x0032, 0x1011));
    public_tags.emplace("ScheduledStudyLocation", Tag(0x0032, 0x1020));
    public_tags.emplace("ScheduledStudyLocationAETitle", Tag(0x0032, 0x1021));
    public_tags.emplace("ReasonForStudy", Tag(0x0032, 0x1030));
    public_tags.emplace("RequestingPhysicianIdentificationSequence", Tag(0x0032, 0x1031));
    public_tags.emplace("RequestingPhysician", Tag(0x0032, 0x1032));
    public_tags.emplace("RequestingService", Tag(0x0032, 0x1033));
    public_tags.emplace("RequestingServiceCodeSequence", Tag(0x0032, 0x1034));
    public_tags.emplace("StudyArrivalDate", Tag(0x0032, 0x1040));
    public_tags.emplace("StudyArrivalTime", Tag(0x0032, 0x1041));
    public_tags.emplace("StudyCompletionDate", Tag(0x0032, 0x1050));
    public_tags.emplace("StudyCompletionTime", Tag(0x0032, 0x1051));
    public_tags.emplace("StudyComponentStatusID", Tag(0x0032, 0x1055));
    public_tags.emplace("RequestedProcedureDescription", Tag(0x0032, 0x1060));
    public_tags.emplace("RequestedProcedureCodeSequence", Tag(0x0032, 0x1064));
    public_tags.emplace("RequestedContrastAgent", Tag(0x0032, 0x1070));
    public_tags.emplace("StudyComments", Tag(0x0032, 0x4000));
}

}

}