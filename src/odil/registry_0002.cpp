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

void update_0002(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0002, 0x0000), ElementsDictionaryEntry("File Meta Information Group Length", "FileMetaInformationGroupLength",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0001), ElementsDictionaryEntry("File Meta Information Version", "FileMetaInformationVersion",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0002), ElementsDictionaryEntry("Media Storage SOP Class UID", "MediaStorageSOPClassUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0003), ElementsDictionaryEntry("Media Storage SOP Instance UID", "MediaStorageSOPInstanceUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0010), ElementsDictionaryEntry("Transfer Syntax UID", "TransferSyntaxUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0012), ElementsDictionaryEntry("Implementation Class UID", "ImplementationClassUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0013), ElementsDictionaryEntry("Implementation Version Name", "ImplementationVersionName",  "SH", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0016), ElementsDictionaryEntry("Source Application Entity Title", "SourceApplicationEntityTitle",  "AE", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0017), ElementsDictionaryEntry("Sending Application Entity Title", "SendingApplicationEntityTitle",  "AE", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0018), ElementsDictionaryEntry("Receiving Application Entity Title", "ReceivingApplicationEntityTitle",  "AE", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0026), ElementsDictionaryEntry("Source Presentation Address", "SourcePresentationAddress",  "UR", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0027), ElementsDictionaryEntry("Sending Presentation Address", "SendingPresentationAddress",  "UR", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0028), ElementsDictionaryEntry("Receiving Presentation Address", "ReceivingPresentationAddress",  "UR", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0031), ElementsDictionaryEntry("RTV Meta Information Version", "RTVMetaInformationVersion",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0032), ElementsDictionaryEntry("RTV Communication SOP Class UID", "RTVCommunicationSOPClassUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0033), ElementsDictionaryEntry("RTV Communication SOP Instance UID", "RTVCommunicationSOPInstanceUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0035), ElementsDictionaryEntry("RTV Source Identifier", "RTVSourceIdentifier",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0036), ElementsDictionaryEntry("RTV Flow Identifier", "RTVFlowIdentifier",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0037), ElementsDictionaryEntry("RTV Flow RTP Sampling Rate", "RTVFlowRTPSamplingRate",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0038), ElementsDictionaryEntry("RTV Flow Actual Frame Duration", "RTVFlowActualFrameDuration",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0100), ElementsDictionaryEntry("Private Information Creator UID", "PrivateInformationCreatorUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0002, 0x0102), ElementsDictionaryEntry("Private Information", "PrivateInformation",  "OB", "1"));

    public_tags.emplace("FileMetaInformationGroupLength", Tag(0x0002, 0x0000));
    public_tags.emplace("FileMetaInformationVersion", Tag(0x0002, 0x0001));
    public_tags.emplace("MediaStorageSOPClassUID", Tag(0x0002, 0x0002));
    public_tags.emplace("MediaStorageSOPInstanceUID", Tag(0x0002, 0x0003));
    public_tags.emplace("TransferSyntaxUID", Tag(0x0002, 0x0010));
    public_tags.emplace("ImplementationClassUID", Tag(0x0002, 0x0012));
    public_tags.emplace("ImplementationVersionName", Tag(0x0002, 0x0013));
    public_tags.emplace("SourceApplicationEntityTitle", Tag(0x0002, 0x0016));
    public_tags.emplace("SendingApplicationEntityTitle", Tag(0x0002, 0x0017));
    public_tags.emplace("ReceivingApplicationEntityTitle", Tag(0x0002, 0x0018));
    public_tags.emplace("SourcePresentationAddress", Tag(0x0002, 0x0026));
    public_tags.emplace("SendingPresentationAddress", Tag(0x0002, 0x0027));
    public_tags.emplace("ReceivingPresentationAddress", Tag(0x0002, 0x0028));
    public_tags.emplace("RTVMetaInformationVersion", Tag(0x0002, 0x0031));
    public_tags.emplace("RTVCommunicationSOPClassUID", Tag(0x0002, 0x0032));
    public_tags.emplace("RTVCommunicationSOPInstanceUID", Tag(0x0002, 0x0033));
    public_tags.emplace("RTVSourceIdentifier", Tag(0x0002, 0x0035));
    public_tags.emplace("RTVFlowIdentifier", Tag(0x0002, 0x0036));
    public_tags.emplace("RTVFlowRTPSamplingRate", Tag(0x0002, 0x0037));
    public_tags.emplace("RTVFlowActualFrameDuration", Tag(0x0002, 0x0038));
    public_tags.emplace("PrivateInformationCreatorUID", Tag(0x0002, 0x0100));
    public_tags.emplace("PrivateInformation", Tag(0x0002, 0x0102));
}

}

}