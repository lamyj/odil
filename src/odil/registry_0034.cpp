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

void update_0034(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0034, 0x0001), ElementsDictionaryEntry("Flow Identifier Sequence", "FlowIdentifierSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0034, 0x0002), ElementsDictionaryEntry("Flow Identifier", "FlowIdentifier",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0034, 0x0003), ElementsDictionaryEntry("Flow Transfer Syntax UID", "FlowTransferSyntaxUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0034, 0x0004), ElementsDictionaryEntry("Flow RTP Sampling Rate", "FlowRTPSamplingRate",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0034, 0x0005), ElementsDictionaryEntry("Source Identifier", "SourceIdentifier",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0034, 0x0007), ElementsDictionaryEntry("Frame Origin Timestamp", "FrameOriginTimestamp",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0034, 0x0008), ElementsDictionaryEntry("Includes Imaging Subject", "IncludesImagingSubject",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0034, 0x0009), ElementsDictionaryEntry("Frame Usefulness Group Sequence", "FrameUsefulnessGroupSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0034, 0x000a), ElementsDictionaryEntry("Real-Time Bulk Data Flow Sequence", "RealTimeBulkDataFlowSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0034, 0x000b), ElementsDictionaryEntry("Camera Position Group Sequence", "CameraPositionGroupSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0034, 0x000c), ElementsDictionaryEntry("Includes Information", "IncludesInformation",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0034, 0x000d), ElementsDictionaryEntry("Time of Frame Group Sequence", "TimeOfFrameGroupSequence",  "SQ", "1"));

    public_tags.emplace("FlowIdentifierSequence", Tag(0x0034, 0x0001));
    public_tags.emplace("FlowIdentifier", Tag(0x0034, 0x0002));
    public_tags.emplace("FlowTransferSyntaxUID", Tag(0x0034, 0x0003));
    public_tags.emplace("FlowRTPSamplingRate", Tag(0x0034, 0x0004));
    public_tags.emplace("SourceIdentifier", Tag(0x0034, 0x0005));
    public_tags.emplace("FrameOriginTimestamp", Tag(0x0034, 0x0007));
    public_tags.emplace("IncludesImagingSubject", Tag(0x0034, 0x0008));
    public_tags.emplace("FrameUsefulnessGroupSequence", Tag(0x0034, 0x0009));
    public_tags.emplace("RealTimeBulkDataFlowSequence", Tag(0x0034, 0x000a));
    public_tags.emplace("CameraPositionGroupSequence", Tag(0x0034, 0x000b));
    public_tags.emplace("IncludesInformation", Tag(0x0034, 0x000c));
    public_tags.emplace("TimeOfFrameGroupSequence", Tag(0x0034, 0x000d));
}

}

}