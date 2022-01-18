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

void update_0062(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0062, 0x0001), ElementsDictionaryEntry("Segmentation Type", "SegmentationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0002), ElementsDictionaryEntry("Segment Sequence", "SegmentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0003), ElementsDictionaryEntry("Segmented Property Category Code Sequence", "SegmentedPropertyCategoryCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0004), ElementsDictionaryEntry("Segment Number", "SegmentNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0005), ElementsDictionaryEntry("Segment Label", "SegmentLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0006), ElementsDictionaryEntry("Segment Description", "SegmentDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0007), ElementsDictionaryEntry("Segmentation Algorithm Identification Sequence", "SegmentationAlgorithmIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0008), ElementsDictionaryEntry("Segment Algorithm Type", "SegmentAlgorithmType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0009), ElementsDictionaryEntry("Segment Algorithm Name", "SegmentAlgorithmName",  "LO", "1-n"));
    public_dictionary.emplace(Tag(0x0062, 0x000a), ElementsDictionaryEntry("Segment Identification Sequence", "SegmentIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x000b), ElementsDictionaryEntry("Referenced Segment Number", "ReferencedSegmentNumber",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0062, 0x000c), ElementsDictionaryEntry("Recommended Display Grayscale Value", "RecommendedDisplayGrayscaleValue",  "US", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x000d), ElementsDictionaryEntry("Recommended Display CIELab Value", "RecommendedDisplayCIELabValue",  "US", "3"));
    public_dictionary.emplace(Tag(0x0062, 0x000e), ElementsDictionaryEntry("Maximum Fractional Value", "MaximumFractionalValue",  "US", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x000f), ElementsDictionaryEntry("Segmented Property Type Code Sequence", "SegmentedPropertyTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0010), ElementsDictionaryEntry("Segmentation Fractional Type", "SegmentationFractionalType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0011), ElementsDictionaryEntry("Segmented Property Type Modifier Code Sequence", "SegmentedPropertyTypeModifierCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0012), ElementsDictionaryEntry("Used Segments Sequence", "UsedSegmentsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0013), ElementsDictionaryEntry("Segments Overlap", "SegmentsOverlap",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0020), ElementsDictionaryEntry("Tracking ID", "TrackingID",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0062, 0x0021), ElementsDictionaryEntry("Tracking UID", "TrackingUID",  "UI", "1"));

    public_tags.emplace("SegmentationType", Tag(0x0062, 0x0001));
    public_tags.emplace("SegmentSequence", Tag(0x0062, 0x0002));
    public_tags.emplace("SegmentedPropertyCategoryCodeSequence", Tag(0x0062, 0x0003));
    public_tags.emplace("SegmentNumber", Tag(0x0062, 0x0004));
    public_tags.emplace("SegmentLabel", Tag(0x0062, 0x0005));
    public_tags.emplace("SegmentDescription", Tag(0x0062, 0x0006));
    public_tags.emplace("SegmentationAlgorithmIdentificationSequence", Tag(0x0062, 0x0007));
    public_tags.emplace("SegmentAlgorithmType", Tag(0x0062, 0x0008));
    public_tags.emplace("SegmentAlgorithmName", Tag(0x0062, 0x0009));
    public_tags.emplace("SegmentIdentificationSequence", Tag(0x0062, 0x000a));
    public_tags.emplace("ReferencedSegmentNumber", Tag(0x0062, 0x000b));
    public_tags.emplace("RecommendedDisplayGrayscaleValue", Tag(0x0062, 0x000c));
    public_tags.emplace("RecommendedDisplayCIELabValue", Tag(0x0062, 0x000d));
    public_tags.emplace("MaximumFractionalValue", Tag(0x0062, 0x000e));
    public_tags.emplace("SegmentedPropertyTypeCodeSequence", Tag(0x0062, 0x000f));
    public_tags.emplace("SegmentationFractionalType", Tag(0x0062, 0x0010));
    public_tags.emplace("SegmentedPropertyTypeModifierCodeSequence", Tag(0x0062, 0x0011));
    public_tags.emplace("UsedSegmentsSequence", Tag(0x0062, 0x0012));
    public_tags.emplace("SegmentsOverlap", Tag(0x0062, 0x0013));
    public_tags.emplace("TrackingID", Tag(0x0062, 0x0020));
    public_tags.emplace("TrackingUID", Tag(0x0062, 0x0021));
}

}

}