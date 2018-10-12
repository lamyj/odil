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

void update_0044(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0044, 0x0001), ElementsDictionaryEntry("Product Package Identifier", "ProductPackageIdentifier",  "ST", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0002), ElementsDictionaryEntry("Substance Administration Approval", "SubstanceAdministrationApproval",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0003), ElementsDictionaryEntry("Approval Status Further Description", "ApprovalStatusFurtherDescription",  "LT", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0004), ElementsDictionaryEntry("Approval Status DateTime", "ApprovalStatusDateTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0007), ElementsDictionaryEntry("Product Type Code Sequence", "ProductTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0008), ElementsDictionaryEntry("Product Name", "ProductName",  "LO", "1-n"));
    public_dictionary.emplace(Tag(0x0044, 0x0009), ElementsDictionaryEntry("Product Description", "ProductDescription",  "LT", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x000a), ElementsDictionaryEntry("Product Lot Identifier", "ProductLotIdentifier",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x000b), ElementsDictionaryEntry("Product Expiration DateTime", "ProductExpirationDateTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0010), ElementsDictionaryEntry("Substance Administration DateTime", "SubstanceAdministrationDateTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0011), ElementsDictionaryEntry("Substance Administration Notes", "SubstanceAdministrationNotes",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0012), ElementsDictionaryEntry("Substance Administration Device ID", "SubstanceAdministrationDeviceID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0013), ElementsDictionaryEntry("Product Parameter Sequence", "ProductParameterSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0019), ElementsDictionaryEntry("Substance Administration Parameter Sequence", "SubstanceAdministrationParameterSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0100), ElementsDictionaryEntry("Approval Sequence", "ApprovalSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0101), ElementsDictionaryEntry("Assertion Code Sequence", "AssertionCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0102), ElementsDictionaryEntry("Assertion UID", "AssertionUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0103), ElementsDictionaryEntry("Asserter Identification Sequence", "AsserterIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0104), ElementsDictionaryEntry("Assertion DateTime", "AssertionDateTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0105), ElementsDictionaryEntry("Assertion Expiration DateTime", "AssertionExpirationDateTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0106), ElementsDictionaryEntry("Assertion Comments", "AssertionComments",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0107), ElementsDictionaryEntry("Related Assertion Sequence", "RelatedAssertionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0108), ElementsDictionaryEntry("Referenced Assertion UID", "ReferencedAssertionUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x0109), ElementsDictionaryEntry("Approval Subject Sequence", "ApprovalSubjectSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0044, 0x010a), ElementsDictionaryEntry("Organizational Role Code Sequence", "OrganizationalRoleCodeSequence",  "SQ", "1"));

    public_tags.emplace("ProductPackageIdentifier", Tag(0x0044, 0x0001));
    public_tags.emplace("SubstanceAdministrationApproval", Tag(0x0044, 0x0002));
    public_tags.emplace("ApprovalStatusFurtherDescription", Tag(0x0044, 0x0003));
    public_tags.emplace("ApprovalStatusDateTime", Tag(0x0044, 0x0004));
    public_tags.emplace("ProductTypeCodeSequence", Tag(0x0044, 0x0007));
    public_tags.emplace("ProductName", Tag(0x0044, 0x0008));
    public_tags.emplace("ProductDescription", Tag(0x0044, 0x0009));
    public_tags.emplace("ProductLotIdentifier", Tag(0x0044, 0x000a));
    public_tags.emplace("ProductExpirationDateTime", Tag(0x0044, 0x000b));
    public_tags.emplace("SubstanceAdministrationDateTime", Tag(0x0044, 0x0010));
    public_tags.emplace("SubstanceAdministrationNotes", Tag(0x0044, 0x0011));
    public_tags.emplace("SubstanceAdministrationDeviceID", Tag(0x0044, 0x0012));
    public_tags.emplace("ProductParameterSequence", Tag(0x0044, 0x0013));
    public_tags.emplace("SubstanceAdministrationParameterSequence", Tag(0x0044, 0x0019));
    public_tags.emplace("ApprovalSequence", Tag(0x0044, 0x0100));
    public_tags.emplace("AssertionCodeSequence", Tag(0x0044, 0x0101));
    public_tags.emplace("AssertionUID", Tag(0x0044, 0x0102));
    public_tags.emplace("AsserterIdentificationSequence", Tag(0x0044, 0x0103));
    public_tags.emplace("AssertionDateTime", Tag(0x0044, 0x0104));
    public_tags.emplace("AssertionExpirationDateTime", Tag(0x0044, 0x0105));
    public_tags.emplace("AssertionComments", Tag(0x0044, 0x0106));
    public_tags.emplace("RelatedAssertionSequence", Tag(0x0044, 0x0107));
    public_tags.emplace("ReferencedAssertionUID", Tag(0x0044, 0x0108));
    public_tags.emplace("ApprovalSubjectSequence", Tag(0x0044, 0x0109));
    public_tags.emplace("OrganizationalRoleCodeSequence", Tag(0x0044, 0x010a));
}

}

}