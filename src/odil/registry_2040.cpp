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

void update_2040(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x2040, 0x0010), ElementsDictionaryEntry("Referenced Overlay Plane Sequence", "ReferencedOverlayPlaneSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2040, 0x0011), ElementsDictionaryEntry("Referenced Overlay Plane Groups", "ReferencedOverlayPlaneGroups",  "US", "1-99"));
    public_dictionary.emplace(Tag(0x2040, 0x0020), ElementsDictionaryEntry("Overlay Pixel Data Sequence", "OverlayPixelDataSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2040, 0x0060), ElementsDictionaryEntry("Overlay Magnification Type", "OverlayMagnificationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2040, 0x0070), ElementsDictionaryEntry("Overlay Smoothing Type", "OverlaySmoothingType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2040, 0x0072), ElementsDictionaryEntry("Overlay or Image Magnification", "OverlayOrImageMagnification",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2040, 0x0074), ElementsDictionaryEntry("Magnify to Number of Columns", "MagnifyToNumberOfColumns",  "US", "1"));
    public_dictionary.emplace(Tag(0x2040, 0x0080), ElementsDictionaryEntry("Overlay Foreground Density", "OverlayForegroundDensity",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2040, 0x0082), ElementsDictionaryEntry("Overlay Background Density", "OverlayBackgroundDensity",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2040, 0x0090), ElementsDictionaryEntry("Overlay Mode", "OverlayMode",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2040, 0x0100), ElementsDictionaryEntry("Threshold Density", "ThresholdDensity",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2040, 0x0500), ElementsDictionaryEntry("Referenced Image Box Sequence (Retired)", "ReferencedImageBoxSequenceRetired",  "SQ", "1"));

    public_tags.emplace("ReferencedOverlayPlaneSequence", Tag(0x2040, 0x0010));
    public_tags.emplace("ReferencedOverlayPlaneGroups", Tag(0x2040, 0x0011));
    public_tags.emplace("OverlayPixelDataSequence", Tag(0x2040, 0x0020));
    public_tags.emplace("OverlayMagnificationType", Tag(0x2040, 0x0060));
    public_tags.emplace("OverlaySmoothingType", Tag(0x2040, 0x0070));
    public_tags.emplace("OverlayOrImageMagnification", Tag(0x2040, 0x0072));
    public_tags.emplace("MagnifyToNumberOfColumns", Tag(0x2040, 0x0074));
    public_tags.emplace("OverlayForegroundDensity", Tag(0x2040, 0x0080));
    public_tags.emplace("OverlayBackgroundDensity", Tag(0x2040, 0x0082));
    public_tags.emplace("OverlayMode", Tag(0x2040, 0x0090));
    public_tags.emplace("ThresholdDensity", Tag(0x2040, 0x0100));
    public_tags.emplace("ReferencedImageBoxSequenceRetired", Tag(0x2040, 0x0500));
}

}

}