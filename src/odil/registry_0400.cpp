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

void update_0400(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0400, 0x0005), ElementsDictionaryEntry("MAC ID Number", "MACIDNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0010), ElementsDictionaryEntry("MAC Calculation Transfer Syntax UID", "MACCalculationTransferSyntaxUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0015), ElementsDictionaryEntry("MAC Algorithm", "MACAlgorithm",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0020), ElementsDictionaryEntry("Data Elements Signed", "DataElementsSigned",  "AT", "1-n"));
    public_dictionary.emplace(Tag(0x0400, 0x0100), ElementsDictionaryEntry("Digital Signature UID", "DigitalSignatureUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0105), ElementsDictionaryEntry("Digital Signature DateTime", "DigitalSignatureDateTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0110), ElementsDictionaryEntry("Certificate Type", "CertificateType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0115), ElementsDictionaryEntry("Certificate of Signer", "CertificateOfSigner",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0120), ElementsDictionaryEntry("Signature", "Signature",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0305), ElementsDictionaryEntry("Certified Timestamp Type", "CertifiedTimestampType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0310), ElementsDictionaryEntry("Certified Timestamp", "CertifiedTimestamp",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0401), ElementsDictionaryEntry("Digital Signature Purpose Code Sequence", "DigitalSignaturePurposeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0402), ElementsDictionaryEntry("Referenced Digital Signature Sequence", "ReferencedDigitalSignatureSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0403), ElementsDictionaryEntry("Referenced SOP Instance MAC Sequence", "ReferencedSOPInstanceMACSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0404), ElementsDictionaryEntry("MAC", "MAC",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0500), ElementsDictionaryEntry("Encrypted Attributes Sequence", "EncryptedAttributesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0510), ElementsDictionaryEntry("Encrypted Content Transfer Syntax UID", "EncryptedContentTransferSyntaxUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0520), ElementsDictionaryEntry("Encrypted Content", "EncryptedContent",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0550), ElementsDictionaryEntry("Modified Attributes Sequence", "ModifiedAttributesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0561), ElementsDictionaryEntry("Original Attributes Sequence", "OriginalAttributesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0562), ElementsDictionaryEntry("Attribute Modification DateTime", "AttributeModificationDateTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0563), ElementsDictionaryEntry("Modifying System", "ModifyingSystem",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0564), ElementsDictionaryEntry("Source of Previous Values", "SourceOfPreviousValues",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0400, 0x0565), ElementsDictionaryEntry("Reason for the Attribute Modification", "ReasonForTheAttributeModification",  "CS", "1"));

    public_tags.emplace("MACIDNumber", Tag(0x0400, 0x0005));
    public_tags.emplace("MACCalculationTransferSyntaxUID", Tag(0x0400, 0x0010));
    public_tags.emplace("MACAlgorithm", Tag(0x0400, 0x0015));
    public_tags.emplace("DataElementsSigned", Tag(0x0400, 0x0020));
    public_tags.emplace("DigitalSignatureUID", Tag(0x0400, 0x0100));
    public_tags.emplace("DigitalSignatureDateTime", Tag(0x0400, 0x0105));
    public_tags.emplace("CertificateType", Tag(0x0400, 0x0110));
    public_tags.emplace("CertificateOfSigner", Tag(0x0400, 0x0115));
    public_tags.emplace("Signature", Tag(0x0400, 0x0120));
    public_tags.emplace("CertifiedTimestampType", Tag(0x0400, 0x0305));
    public_tags.emplace("CertifiedTimestamp", Tag(0x0400, 0x0310));
    public_tags.emplace("DigitalSignaturePurposeCodeSequence", Tag(0x0400, 0x0401));
    public_tags.emplace("ReferencedDigitalSignatureSequence", Tag(0x0400, 0x0402));
    public_tags.emplace("ReferencedSOPInstanceMACSequence", Tag(0x0400, 0x0403));
    public_tags.emplace("MAC", Tag(0x0400, 0x0404));
    public_tags.emplace("EncryptedAttributesSequence", Tag(0x0400, 0x0500));
    public_tags.emplace("EncryptedContentTransferSyntaxUID", Tag(0x0400, 0x0510));
    public_tags.emplace("EncryptedContent", Tag(0x0400, 0x0520));
    public_tags.emplace("ModifiedAttributesSequence", Tag(0x0400, 0x0550));
    public_tags.emplace("OriginalAttributesSequence", Tag(0x0400, 0x0561));
    public_tags.emplace("AttributeModificationDateTime", Tag(0x0400, 0x0562));
    public_tags.emplace("ModifyingSystem", Tag(0x0400, 0x0563));
    public_tags.emplace("SourceOfPreviousValues", Tag(0x0400, 0x0564));
    public_tags.emplace("ReasonForTheAttributeModification", Tag(0x0400, 0x0565));
}

}

}