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

void update_0078(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0078, 0x0001), ElementsDictionaryEntry("Implant Template Group Name", "ImplantTemplateGroupName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0078, 0x0010), ElementsDictionaryEntry("Implant Template Group Description", "ImplantTemplateGroupDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x0078, 0x0020), ElementsDictionaryEntry("Implant Template Group Issuer", "ImplantTemplateGroupIssuer",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0078, 0x0024), ElementsDictionaryEntry("Implant Template Group Version", "ImplantTemplateGroupVersion",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0078, 0x0026), ElementsDictionaryEntry("Replaced Implant Template Group Sequence", "ReplacedImplantTemplateGroupSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0078, 0x0028), ElementsDictionaryEntry("Implant Template Group Target Anatomy Sequence", "ImplantTemplateGroupTargetAnatomySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0078, 0x002a), ElementsDictionaryEntry("Implant Template Group Members Sequence", "ImplantTemplateGroupMembersSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0078, 0x002e), ElementsDictionaryEntry("Implant Template Group Member ID", "ImplantTemplateGroupMemberID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0078, 0x0050), ElementsDictionaryEntry("3D Implant Template Group Member Matching Point", "ThreeDImplantTemplateGroupMemberMatchingPoint",  "FD", "3"));
    public_dictionary.emplace(Tag(0x0078, 0x0060), ElementsDictionaryEntry("3D Implant Template Group Member Matching Axes", "ThreeDImplantTemplateGroupMemberMatchingAxes",  "FD", "9"));
    public_dictionary.emplace(Tag(0x0078, 0x0070), ElementsDictionaryEntry("Implant Template Group Member Matching 2D Coordinates Sequence", "ImplantTemplateGroupMemberMatching2DCoordinatesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0078, 0x0090), ElementsDictionaryEntry("2D Implant Template Group Member Matching Point", "TwoDImplantTemplateGroupMemberMatchingPoint",  "FD", "2"));
    public_dictionary.emplace(Tag(0x0078, 0x00a0), ElementsDictionaryEntry("2D Implant Template Group Member Matching Axes", "TwoDImplantTemplateGroupMemberMatchingAxes",  "FD", "4"));
    public_dictionary.emplace(Tag(0x0078, 0x00b0), ElementsDictionaryEntry("Implant Template Group Variation Dimension Sequence", "ImplantTemplateGroupVariationDimensionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0078, 0x00b2), ElementsDictionaryEntry("Implant Template Group Variation Dimension Name", "ImplantTemplateGroupVariationDimensionName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0078, 0x00b4), ElementsDictionaryEntry("Implant Template Group Variation Dimension Rank Sequence", "ImplantTemplateGroupVariationDimensionRankSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0078, 0x00b6), ElementsDictionaryEntry("Referenced Implant Template Group Member ID", "ReferencedImplantTemplateGroupMemberID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0078, 0x00b8), ElementsDictionaryEntry("Implant Template Group Variation Dimension Rank", "ImplantTemplateGroupVariationDimensionRank",  "US", "1"));

    public_tags.emplace("ImplantTemplateGroupName", Tag(0x0078, 0x0001));
    public_tags.emplace("ImplantTemplateGroupDescription", Tag(0x0078, 0x0010));
    public_tags.emplace("ImplantTemplateGroupIssuer", Tag(0x0078, 0x0020));
    public_tags.emplace("ImplantTemplateGroupVersion", Tag(0x0078, 0x0024));
    public_tags.emplace("ReplacedImplantTemplateGroupSequence", Tag(0x0078, 0x0026));
    public_tags.emplace("ImplantTemplateGroupTargetAnatomySequence", Tag(0x0078, 0x0028));
    public_tags.emplace("ImplantTemplateGroupMembersSequence", Tag(0x0078, 0x002a));
    public_tags.emplace("ImplantTemplateGroupMemberID", Tag(0x0078, 0x002e));
    public_tags.emplace("ThreeDImplantTemplateGroupMemberMatchingPoint", Tag(0x0078, 0x0050));
    public_tags.emplace("ThreeDImplantTemplateGroupMemberMatchingAxes", Tag(0x0078, 0x0060));
    public_tags.emplace("ImplantTemplateGroupMemberMatching2DCoordinatesSequence", Tag(0x0078, 0x0070));
    public_tags.emplace("TwoDImplantTemplateGroupMemberMatchingPoint", Tag(0x0078, 0x0090));
    public_tags.emplace("TwoDImplantTemplateGroupMemberMatchingAxes", Tag(0x0078, 0x00a0));
    public_tags.emplace("ImplantTemplateGroupVariationDimensionSequence", Tag(0x0078, 0x00b0));
    public_tags.emplace("ImplantTemplateGroupVariationDimensionName", Tag(0x0078, 0x00b2));
    public_tags.emplace("ImplantTemplateGroupVariationDimensionRankSequence", Tag(0x0078, 0x00b4));
    public_tags.emplace("ReferencedImplantTemplateGroupMemberID", Tag(0x0078, 0x00b6));
    public_tags.emplace("ImplantTemplateGroupVariationDimensionRank", Tag(0x0078, 0x00b8));
}

}

}