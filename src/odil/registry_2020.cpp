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

void update_2020(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x2020, 0x0010), ElementsDictionaryEntry("Image Box Position", "ImageBoxPosition",  "US", "1"));
    public_dictionary.emplace(Tag(0x2020, 0x0020), ElementsDictionaryEntry("Polarity", "Polarity",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2020, 0x0030), ElementsDictionaryEntry("Requested Image Size", "RequestedImageSize",  "DS", "1"));
    public_dictionary.emplace(Tag(0x2020, 0x0040), ElementsDictionaryEntry("Requested Decimate/Crop Behavior", "RequestedDecimateCropBehavior",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2020, 0x0050), ElementsDictionaryEntry("Requested Resolution ID", "RequestedResolutionID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2020, 0x00a0), ElementsDictionaryEntry("Requested Image Size Flag", "RequestedImageSizeFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2020, 0x00a2), ElementsDictionaryEntry("Decimate/Crop Result", "DecimateCropResult",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2020, 0x0110), ElementsDictionaryEntry("Basic Grayscale Image Sequence", "BasicGrayscaleImageSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2020, 0x0111), ElementsDictionaryEntry("Basic Color Image Sequence", "BasicColorImageSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2020, 0x0130), ElementsDictionaryEntry("Referenced Image Overlay Box Sequence", "ReferencedImageOverlayBoxSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2020, 0x0140), ElementsDictionaryEntry("Referenced VOI LUT Box Sequence", "ReferencedVOILUTBoxSequence",  "SQ", "1"));

    public_tags.emplace("ImageBoxPosition", Tag(0x2020, 0x0010));
    public_tags.emplace("Polarity", Tag(0x2020, 0x0020));
    public_tags.emplace("RequestedImageSize", Tag(0x2020, 0x0030));
    public_tags.emplace("RequestedDecimateCropBehavior", Tag(0x2020, 0x0040));
    public_tags.emplace("RequestedResolutionID", Tag(0x2020, 0x0050));
    public_tags.emplace("RequestedImageSizeFlag", Tag(0x2020, 0x00a0));
    public_tags.emplace("DecimateCropResult", Tag(0x2020, 0x00a2));
    public_tags.emplace("BasicGrayscaleImageSequence", Tag(0x2020, 0x0110));
    public_tags.emplace("BasicColorImageSequence", Tag(0x2020, 0x0111));
    public_tags.emplace("ReferencedImageOverlayBoxSequence", Tag(0x2020, 0x0130));
    public_tags.emplace("ReferencedVOILUTBoxSequence", Tag(0x2020, 0x0140));
}

}

}