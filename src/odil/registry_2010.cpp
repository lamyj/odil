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

void update_2010(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x2010, 0x0010), ElementsDictionaryEntry("Image Display Format", "ImageDisplayFormat",  "ST", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0030), ElementsDictionaryEntry("Annotation Display Format ID", "AnnotationDisplayFormatID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0040), ElementsDictionaryEntry("Film Orientation", "FilmOrientation",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0050), ElementsDictionaryEntry("Film Size ID", "FilmSizeID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0052), ElementsDictionaryEntry("Printer Resolution ID", "PrinterResolutionID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0054), ElementsDictionaryEntry("Default Printer Resolution ID", "DefaultPrinterResolutionID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0060), ElementsDictionaryEntry("Magnification Type", "MagnificationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0080), ElementsDictionaryEntry("Smoothing Type", "SmoothingType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x00a6), ElementsDictionaryEntry("Default Magnification Type", "DefaultMagnificationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x00a7), ElementsDictionaryEntry("Other Magnification Types Available", "OtherMagnificationTypesAvailable",  "CS", "1-n"));
    public_dictionary.emplace(Tag(0x2010, 0x00a8), ElementsDictionaryEntry("Default Smoothing Type", "DefaultSmoothingType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x00a9), ElementsDictionaryEntry("Other Smoothing Types Available", "OtherSmoothingTypesAvailable",  "CS", "1-n"));
    public_dictionary.emplace(Tag(0x2010, 0x0100), ElementsDictionaryEntry("Border Density", "BorderDensity",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0110), ElementsDictionaryEntry("Empty Image Density", "EmptyImageDensity",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0120), ElementsDictionaryEntry("Min Density", "MinDensity",  "US", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0130), ElementsDictionaryEntry("Max Density", "MaxDensity",  "US", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0140), ElementsDictionaryEntry("Trim", "Trim",  "CS", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0150), ElementsDictionaryEntry("Configuration Information", "ConfigurationInformation",  "ST", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0152), ElementsDictionaryEntry("Configuration Information Description", "ConfigurationInformationDescription",  "LT", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0154), ElementsDictionaryEntry("Maximum Collated Films", "MaximumCollatedFilms",  "IS", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x015e), ElementsDictionaryEntry("Illumination", "Illumination",  "US", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0160), ElementsDictionaryEntry("Reflected Ambient Light", "ReflectedAmbientLight",  "US", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0376), ElementsDictionaryEntry("Printer Pixel Spacing", "PrinterPixelSpacing",  "DS", "2"));
    public_dictionary.emplace(Tag(0x2010, 0x0500), ElementsDictionaryEntry("Referenced Film Session Sequence", "ReferencedFilmSessionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0510), ElementsDictionaryEntry("Referenced Image Box Sequence", "ReferencedImageBoxSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x2010, 0x0520), ElementsDictionaryEntry("Referenced Basic Annotation Box Sequence", "ReferencedBasicAnnotationBoxSequence",  "SQ", "1"));

    public_tags.emplace("ImageDisplayFormat", Tag(0x2010, 0x0010));
    public_tags.emplace("AnnotationDisplayFormatID", Tag(0x2010, 0x0030));
    public_tags.emplace("FilmOrientation", Tag(0x2010, 0x0040));
    public_tags.emplace("FilmSizeID", Tag(0x2010, 0x0050));
    public_tags.emplace("PrinterResolutionID", Tag(0x2010, 0x0052));
    public_tags.emplace("DefaultPrinterResolutionID", Tag(0x2010, 0x0054));
    public_tags.emplace("MagnificationType", Tag(0x2010, 0x0060));
    public_tags.emplace("SmoothingType", Tag(0x2010, 0x0080));
    public_tags.emplace("DefaultMagnificationType", Tag(0x2010, 0x00a6));
    public_tags.emplace("OtherMagnificationTypesAvailable", Tag(0x2010, 0x00a7));
    public_tags.emplace("DefaultSmoothingType", Tag(0x2010, 0x00a8));
    public_tags.emplace("OtherSmoothingTypesAvailable", Tag(0x2010, 0x00a9));
    public_tags.emplace("BorderDensity", Tag(0x2010, 0x0100));
    public_tags.emplace("EmptyImageDensity", Tag(0x2010, 0x0110));
    public_tags.emplace("MinDensity", Tag(0x2010, 0x0120));
    public_tags.emplace("MaxDensity", Tag(0x2010, 0x0130));
    public_tags.emplace("Trim", Tag(0x2010, 0x0140));
    public_tags.emplace("ConfigurationInformation", Tag(0x2010, 0x0150));
    public_tags.emplace("ConfigurationInformationDescription", Tag(0x2010, 0x0152));
    public_tags.emplace("MaximumCollatedFilms", Tag(0x2010, 0x0154));
    public_tags.emplace("Illumination", Tag(0x2010, 0x015e));
    public_tags.emplace("ReflectedAmbientLight", Tag(0x2010, 0x0160));
    public_tags.emplace("PrinterPixelSpacing", Tag(0x2010, 0x0376));
    public_tags.emplace("ReferencedFilmSessionSequence", Tag(0x2010, 0x0500));
    public_tags.emplace("ReferencedImageBoxSequence", Tag(0x2010, 0x0510));
    public_tags.emplace("ReferencedBasicAnnotationBoxSequence", Tag(0x2010, 0x0520));
}

}

}