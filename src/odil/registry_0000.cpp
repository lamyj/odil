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

void update_0000(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0000, 0x0000), ElementsDictionaryEntry("Command Group Length", "CommandGroupLength",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x0002), ElementsDictionaryEntry("Affected SOP Class UID", "AffectedSOPClassUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x0003), ElementsDictionaryEntry("Requested SOP Class UID", "RequestedSOPClassUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x0100), ElementsDictionaryEntry("Command Field", "CommandField",  "US", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x0110), ElementsDictionaryEntry("Message ID", "MessageID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x0120), ElementsDictionaryEntry("Message ID Being Responded To", "MessageIDBeingRespondedTo",  "US", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x0600), ElementsDictionaryEntry("Move Destination", "MoveDestination",  "AE", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x0700), ElementsDictionaryEntry("Priority", "Priority",  "US", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x0800), ElementsDictionaryEntry("Command Data Set Type", "CommandDataSetType",  "US", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x0900), ElementsDictionaryEntry("Status", "Status",  "US", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x0901), ElementsDictionaryEntry("Offending Element", "OffendingElement",  "AT", "1-n"));
    public_dictionary.emplace(Tag(0x0000, 0x0902), ElementsDictionaryEntry("Error Comment", "ErrorComment",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x0903), ElementsDictionaryEntry("Error ID", "ErrorID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x1000), ElementsDictionaryEntry("Affected SOP Instance UID", "AffectedSOPInstanceUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x1001), ElementsDictionaryEntry("Requested SOP Instance UID", "RequestedSOPInstanceUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x1002), ElementsDictionaryEntry("Event Type ID", "EventTypeID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x1005), ElementsDictionaryEntry("Attribute Identifier List", "AttributeIdentifierList",  "AT", "1-n"));
    public_dictionary.emplace(Tag(0x0000, 0x1008), ElementsDictionaryEntry("Action Type ID", "ActionTypeID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x1020), ElementsDictionaryEntry("Number of Remaining Sub-operations", "NumberOfRemainingSuboperations",  "US", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x1021), ElementsDictionaryEntry("Number of Completed Sub-operations", "NumberOfCompletedSuboperations",  "US", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x1022), ElementsDictionaryEntry("Number of Failed Sub-operations", "NumberOfFailedSuboperations",  "US", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x1023), ElementsDictionaryEntry("Number of Warning Sub-operations", "NumberOfWarningSuboperations",  "US", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x1030), ElementsDictionaryEntry("Move Originator Application Entity Title", "MoveOriginatorApplicationEntityTitle",  "AE", "1"));
    public_dictionary.emplace(Tag(0x0000, 0x1031), ElementsDictionaryEntry("Move Originator Message ID", "MoveOriginatorMessageID",  "US", "1"));

    public_tags.emplace("CommandGroupLength", Tag(0x0000, 0x0000));
    public_tags.emplace("AffectedSOPClassUID", Tag(0x0000, 0x0002));
    public_tags.emplace("RequestedSOPClassUID", Tag(0x0000, 0x0003));
    public_tags.emplace("CommandField", Tag(0x0000, 0x0100));
    public_tags.emplace("MessageID", Tag(0x0000, 0x0110));
    public_tags.emplace("MessageIDBeingRespondedTo", Tag(0x0000, 0x0120));
    public_tags.emplace("MoveDestination", Tag(0x0000, 0x0600));
    public_tags.emplace("Priority", Tag(0x0000, 0x0700));
    public_tags.emplace("CommandDataSetType", Tag(0x0000, 0x0800));
    public_tags.emplace("Status", Tag(0x0000, 0x0900));
    public_tags.emplace("OffendingElement", Tag(0x0000, 0x0901));
    public_tags.emplace("ErrorComment", Tag(0x0000, 0x0902));
    public_tags.emplace("ErrorID", Tag(0x0000, 0x0903));
    public_tags.emplace("AffectedSOPInstanceUID", Tag(0x0000, 0x1000));
    public_tags.emplace("RequestedSOPInstanceUID", Tag(0x0000, 0x1001));
    public_tags.emplace("EventTypeID", Tag(0x0000, 0x1002));
    public_tags.emplace("AttributeIdentifierList", Tag(0x0000, 0x1005));
    public_tags.emplace("ActionTypeID", Tag(0x0000, 0x1008));
    public_tags.emplace("NumberOfRemainingSuboperations", Tag(0x0000, 0x1020));
    public_tags.emplace("NumberOfCompletedSuboperations", Tag(0x0000, 0x1021));
    public_tags.emplace("NumberOfFailedSuboperations", Tag(0x0000, 0x1022));
    public_tags.emplace("NumberOfWarningSuboperations", Tag(0x0000, 0x1023));
    public_tags.emplace("MoveOriginatorApplicationEntityTitle", Tag(0x0000, 0x1030));
    public_tags.emplace("MoveOriginatorMessageID", Tag(0x0000, 0x1031));
}

}

}