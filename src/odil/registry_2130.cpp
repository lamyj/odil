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

void update_2130(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x2130, 0x0010), ElementsDictionaryEntry("Print Management Capabilities Sequence", "PrintManagementCapabilitiesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2130, 0x0015), ElementsDictionaryEntry("Printer Characteristics Sequence", "PrinterCharacteristicsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2130, 0x0030), ElementsDictionaryEntry("Film Box Content Sequence", "FilmBoxContentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2130, 0x0040), ElementsDictionaryEntry("Image Box Content Sequence", "ImageBoxContentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2130, 0x0050), ElementsDictionaryEntry("Annotation Content Sequence", "AnnotationContentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2130, 0x0060), ElementsDictionaryEntry("Image Overlay Box Content Sequence", "ImageOverlayBoxContentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2130, 0x0080), ElementsDictionaryEntry("Presentation LUT Content Sequence", "PresentationLUTContentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2130, 0x00a0), ElementsDictionaryEntry("Proposed Study Sequence", "ProposedStudySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2130, 0x00c0), ElementsDictionaryEntry("Original Image Sequence", "OriginalImageSequence",  "SQ", "1"));

    public_tags.emplace("PrintManagementCapabilitiesSequence", Tag(0x2130, 0x0010));
    public_tags.emplace("PrinterCharacteristicsSequence", Tag(0x2130, 0x0015));
    public_tags.emplace("FilmBoxContentSequence", Tag(0x2130, 0x0030));
    public_tags.emplace("ImageBoxContentSequence", Tag(0x2130, 0x0040));
    public_tags.emplace("AnnotationContentSequence", Tag(0x2130, 0x0050));
    public_tags.emplace("ImageOverlayBoxContentSequence", Tag(0x2130, 0x0060));
    public_tags.emplace("PresentationLUTContentSequence", Tag(0x2130, 0x0080));
    public_tags.emplace("ProposedStudySequence", Tag(0x2130, 0x00a0));
    public_tags.emplace("OriginalImageSequence", Tag(0x2130, 0x00c0));
}

}

}