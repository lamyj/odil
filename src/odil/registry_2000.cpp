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

void update_2000(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x2000, 0x0010), ElementsDictionaryEntry("Number of Copies", "NumberOfCopies",  "IS", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x001e), ElementsDictionaryEntry("Printer Configuration Sequence", "PrinterConfigurationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x0020), ElementsDictionaryEntry("Print Priority", "PrintPriority",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x0030), ElementsDictionaryEntry("Medium Type", "MediumType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x0040), ElementsDictionaryEntry("Film Destination", "FilmDestination",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x0050), ElementsDictionaryEntry("Film Session Label", "FilmSessionLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x0060), ElementsDictionaryEntry("Memory Allocation", "MemoryAllocation",  "IS", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x0061), ElementsDictionaryEntry("Maximum Memory Allocation", "MaximumMemoryAllocation",  "IS", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x0062), ElementsDictionaryEntry("Color Image Printing Flag", "ColorImagePrintingFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x0063), ElementsDictionaryEntry("Collation Flag", "CollationFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x0065), ElementsDictionaryEntry("Annotation Flag", "AnnotationFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x0067), ElementsDictionaryEntry("Image Overlay Flag", "ImageOverlayFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x0069), ElementsDictionaryEntry("Presentation LUT Flag", "PresentationLUTFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x006a), ElementsDictionaryEntry("Image Box Presentation LUT Flag", "ImageBoxPresentationLUTFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x00a0), ElementsDictionaryEntry("Memory Bit Depth", "MemoryBitDepth",  "US", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x00a1), ElementsDictionaryEntry("Printing Bit Depth", "PrintingBitDepth",  "US", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x00a2), ElementsDictionaryEntry("Media Installed Sequence", "MediaInstalledSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x00a4), ElementsDictionaryEntry("Other Media Available Sequence", "OtherMediaAvailableSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x00a8), ElementsDictionaryEntry("Supported Image Display Formats Sequence", "SupportedImageDisplayFormatsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x0500), ElementsDictionaryEntry("Referenced Film Box Sequence", "ReferencedFilmBoxSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2000, 0x0510), ElementsDictionaryEntry("Referenced Stored Print Sequence", "ReferencedStoredPrintSequence",  "SQ", "1"));

    public_tags.emplace("NumberOfCopies", Tag(0x2000, 0x0010));
    public_tags.emplace("PrinterConfigurationSequence", Tag(0x2000, 0x001e));
    public_tags.emplace("PrintPriority", Tag(0x2000, 0x0020));
    public_tags.emplace("MediumType", Tag(0x2000, 0x0030));
    public_tags.emplace("FilmDestination", Tag(0x2000, 0x0040));
    public_tags.emplace("FilmSessionLabel", Tag(0x2000, 0x0050));
    public_tags.emplace("MemoryAllocation", Tag(0x2000, 0x0060));
    public_tags.emplace("MaximumMemoryAllocation", Tag(0x2000, 0x0061));
    public_tags.emplace("ColorImagePrintingFlag", Tag(0x2000, 0x0062));
    public_tags.emplace("CollationFlag", Tag(0x2000, 0x0063));
    public_tags.emplace("AnnotationFlag", Tag(0x2000, 0x0065));
    public_tags.emplace("ImageOverlayFlag", Tag(0x2000, 0x0067));
    public_tags.emplace("PresentationLUTFlag", Tag(0x2000, 0x0069));
    public_tags.emplace("ImageBoxPresentationLUTFlag", Tag(0x2000, 0x006a));
    public_tags.emplace("MemoryBitDepth", Tag(0x2000, 0x00a0));
    public_tags.emplace("PrintingBitDepth", Tag(0x2000, 0x00a1));
    public_tags.emplace("MediaInstalledSequence", Tag(0x2000, 0x00a2));
    public_tags.emplace("OtherMediaAvailableSequence", Tag(0x2000, 0x00a4));
    public_tags.emplace("SupportedImageDisplayFormatsSequence", Tag(0x2000, 0x00a8));
    public_tags.emplace("ReferencedFilmBoxSequence", Tag(0x2000, 0x0500));
    public_tags.emplace("ReferencedStoredPrintSequence", Tag(0x2000, 0x0510));
}

}

}