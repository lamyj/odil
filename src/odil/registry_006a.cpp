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

void update_006a(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x006a, 0x0001), ElementsDictionaryEntry("Annotation Coordinate Type", "AnnotationCoordinateType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x006a, 0x0002), ElementsDictionaryEntry("Annotation Group Sequence", "AnnotationGroupSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x006a, 0x0003), ElementsDictionaryEntry("Annotation Group UID", "AnnotationGroupUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x006a, 0x0005), ElementsDictionaryEntry("Annotation Group Label", "AnnotationGroupLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x006a, 0x0006), ElementsDictionaryEntry("Annotation Group Description", "AnnotationGroupDescription",  "UT", "1"));
    public_dictionary.emplace(Tag(0x006a, 0x0007), ElementsDictionaryEntry("Annotation Group Generation Type", "AnnotationGroupGenerationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x006a, 0x0008), ElementsDictionaryEntry("Annotation Group Algorithm Identification Sequence", "AnnotationGroupAlgorithmIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x006a, 0x0009), ElementsDictionaryEntry("Annotation Property Category Code Sequence", "AnnotationPropertyCategoryCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x006a, 0x000a), ElementsDictionaryEntry("Annotation Property Type Code Sequence", "AnnotationPropertyTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x006a, 0x000b), ElementsDictionaryEntry("Annotation Property Type Modifier Code Sequence", "AnnotationPropertyTypeModifierCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x006a, 0x000c), ElementsDictionaryEntry("Number of Annotations", "NumberOfAnnotations",  "UL", "1"));
    public_dictionary.emplace(Tag(0x006a, 0x000d), ElementsDictionaryEntry("Annotation Applies to All Optical Paths", "AnnotationAppliesToAllOpticalPaths",  "CS", "1"));
    public_dictionary.emplace(Tag(0x006a, 0x000e), ElementsDictionaryEntry("Referenced Optical Path Identifier", "ReferencedOpticalPathIdentifier",  "SH", "1-n"));
    public_dictionary.emplace(Tag(0x006a, 0x000f), ElementsDictionaryEntry("Annotation Applies to All Z Planes", "AnnotationAppliesToAllZPlanes",  "CS", "1"));
    public_dictionary.emplace(Tag(0x006a, 0x0010), ElementsDictionaryEntry("Common Z Coordinate Value", "CommonZCoordinateValue",  "FD", "1-n"));
    public_dictionary.emplace(Tag(0x006a, 0x0011), ElementsDictionaryEntry("Annotation Index List", "AnnotationIndexList",  "OL", "1"));

    public_tags.emplace("AnnotationCoordinateType", Tag(0x006a, 0x0001));
    public_tags.emplace("AnnotationGroupSequence", Tag(0x006a, 0x0002));
    public_tags.emplace("AnnotationGroupUID", Tag(0x006a, 0x0003));
    public_tags.emplace("AnnotationGroupLabel", Tag(0x006a, 0x0005));
    public_tags.emplace("AnnotationGroupDescription", Tag(0x006a, 0x0006));
    public_tags.emplace("AnnotationGroupGenerationType", Tag(0x006a, 0x0007));
    public_tags.emplace("AnnotationGroupAlgorithmIdentificationSequence", Tag(0x006a, 0x0008));
    public_tags.emplace("AnnotationPropertyCategoryCodeSequence", Tag(0x006a, 0x0009));
    public_tags.emplace("AnnotationPropertyTypeCodeSequence", Tag(0x006a, 0x000a));
    public_tags.emplace("AnnotationPropertyTypeModifierCodeSequence", Tag(0x006a, 0x000b));
    public_tags.emplace("NumberOfAnnotations", Tag(0x006a, 0x000c));
    public_tags.emplace("AnnotationAppliesToAllOpticalPaths", Tag(0x006a, 0x000d));
    public_tags.emplace("ReferencedOpticalPathIdentifier", Tag(0x006a, 0x000e));
    public_tags.emplace("AnnotationAppliesToAllZPlanes", Tag(0x006a, 0x000f));
    public_tags.emplace("CommonZCoordinateValue", Tag(0x006a, 0x0010));
    public_tags.emplace("AnnotationIndexList", Tag(0x006a, 0x0011));
}

}

}