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

void update_0048(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0048, 0x0001), ElementsDictionaryEntry("Imaged Volume Width", "ImagedVolumeWidth",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0002), ElementsDictionaryEntry("Imaged Volume Height", "ImagedVolumeHeight",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0003), ElementsDictionaryEntry("Imaged Volume Depth", "ImagedVolumeDepth",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0006), ElementsDictionaryEntry("Total Pixel Matrix Columns", "TotalPixelMatrixColumns",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0007), ElementsDictionaryEntry("Total Pixel Matrix Rows", "TotalPixelMatrixRows",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0008), ElementsDictionaryEntry("Total Pixel Matrix Origin Sequence", "TotalPixelMatrixOriginSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0010), ElementsDictionaryEntry("Specimen Label in Image", "SpecimenLabelInImage",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0011), ElementsDictionaryEntry("Focus Method", "FocusMethod",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0012), ElementsDictionaryEntry("Extended Depth of Field", "ExtendedDepthOfField",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0013), ElementsDictionaryEntry("Number of Focal Planes", "NumberOfFocalPlanes",  "US", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0014), ElementsDictionaryEntry("Distance Between Focal Planes", "DistanceBetweenFocalPlanes",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0015), ElementsDictionaryEntry("Recommended Absent Pixel CIELab Value", "RecommendedAbsentPixelCIELabValue",  "US", "3"));
    public_dictionary.emplace(Tag(0x0048, 0x0100), ElementsDictionaryEntry("Illuminator Type Code Sequence", "IlluminatorTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0102), ElementsDictionaryEntry("Image Orientation (Slide)", "ImageOrientationSlide",  "DS", "6"));
    public_dictionary.emplace(Tag(0x0048, 0x0105), ElementsDictionaryEntry("Optical Path Sequence", "OpticalPathSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0106), ElementsDictionaryEntry("Optical Path Identifier", "OpticalPathIdentifier",  "SH", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0107), ElementsDictionaryEntry("Optical Path Description", "OpticalPathDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0108), ElementsDictionaryEntry("Illumination Color Code Sequence", "IlluminationColorCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0110), ElementsDictionaryEntry("Specimen Reference Sequence", "SpecimenReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0111), ElementsDictionaryEntry("Condenser Lens Power", "CondenserLensPower",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0112), ElementsDictionaryEntry("Objective Lens Power", "ObjectiveLensPower",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0113), ElementsDictionaryEntry("Objective Lens Numerical Aperture", "ObjectiveLensNumericalAperture",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0114), ElementsDictionaryEntry("Confocal Mode", "ConfocalMode",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0115), ElementsDictionaryEntry("Tissue Location", "TissueLocation",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0116), ElementsDictionaryEntry("Confocal Microscopy Image Frame Type Sequence", "ConfocalMicroscopyImageFrameTypeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0117), ElementsDictionaryEntry("Image Acquisition Depth", "ImageAcquisitionDepth",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0120), ElementsDictionaryEntry("Palette Color Lookup Table Sequence", "PaletteColorLookupTableSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0200), ElementsDictionaryEntry("Referenced Image Navigation Sequence", "ReferencedImageNavigationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0201), ElementsDictionaryEntry("Top Left Hand Corner of Localizer Area", "TopLeftHandCornerOfLocalizerArea",  "US", "2"));
    public_dictionary.emplace(Tag(0x0048, 0x0202), ElementsDictionaryEntry("Bottom Right Hand Corner of Localizer Area", "BottomRightHandCornerOfLocalizerArea",  "US", "2"));
    public_dictionary.emplace(Tag(0x0048, 0x0207), ElementsDictionaryEntry("Optical Path Identification Sequence", "OpticalPathIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x021a), ElementsDictionaryEntry("Plane Position (Slide) Sequence", "PlanePositionSlideSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x021e), ElementsDictionaryEntry("Column Position In Total Image Pixel Matrix", "ColumnPositionInTotalImagePixelMatrix",  "SL", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x021f), ElementsDictionaryEntry("Row Position In Total Image Pixel Matrix", "RowPositionInTotalImagePixelMatrix",  "SL", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0301), ElementsDictionaryEntry("Pixel Origin Interpretation", "PixelOriginInterpretation",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0302), ElementsDictionaryEntry("Number of Optical Paths", "NumberOfOpticalPaths",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0048, 0x0303), ElementsDictionaryEntry("Total Pixel Matrix Focal Planes", "TotalPixelMatrixFocalPlanes",  "UL", "1"));

    public_tags.emplace("ImagedVolumeWidth", Tag(0x0048, 0x0001));
    public_tags.emplace("ImagedVolumeHeight", Tag(0x0048, 0x0002));
    public_tags.emplace("ImagedVolumeDepth", Tag(0x0048, 0x0003));
    public_tags.emplace("TotalPixelMatrixColumns", Tag(0x0048, 0x0006));
    public_tags.emplace("TotalPixelMatrixRows", Tag(0x0048, 0x0007));
    public_tags.emplace("TotalPixelMatrixOriginSequence", Tag(0x0048, 0x0008));
    public_tags.emplace("SpecimenLabelInImage", Tag(0x0048, 0x0010));
    public_tags.emplace("FocusMethod", Tag(0x0048, 0x0011));
    public_tags.emplace("ExtendedDepthOfField", Tag(0x0048, 0x0012));
    public_tags.emplace("NumberOfFocalPlanes", Tag(0x0048, 0x0013));
    public_tags.emplace("DistanceBetweenFocalPlanes", Tag(0x0048, 0x0014));
    public_tags.emplace("RecommendedAbsentPixelCIELabValue", Tag(0x0048, 0x0015));
    public_tags.emplace("IlluminatorTypeCodeSequence", Tag(0x0048, 0x0100));
    public_tags.emplace("ImageOrientationSlide", Tag(0x0048, 0x0102));
    public_tags.emplace("OpticalPathSequence", Tag(0x0048, 0x0105));
    public_tags.emplace("OpticalPathIdentifier", Tag(0x0048, 0x0106));
    public_tags.emplace("OpticalPathDescription", Tag(0x0048, 0x0107));
    public_tags.emplace("IlluminationColorCodeSequence", Tag(0x0048, 0x0108));
    public_tags.emplace("SpecimenReferenceSequence", Tag(0x0048, 0x0110));
    public_tags.emplace("CondenserLensPower", Tag(0x0048, 0x0111));
    public_tags.emplace("ObjectiveLensPower", Tag(0x0048, 0x0112));
    public_tags.emplace("ObjectiveLensNumericalAperture", Tag(0x0048, 0x0113));
    public_tags.emplace("ConfocalMode", Tag(0x0048, 0x0114));
    public_tags.emplace("TissueLocation", Tag(0x0048, 0x0115));
    public_tags.emplace("ConfocalMicroscopyImageFrameTypeSequence", Tag(0x0048, 0x0116));
    public_tags.emplace("ImageAcquisitionDepth", Tag(0x0048, 0x0117));
    public_tags.emplace("PaletteColorLookupTableSequence", Tag(0x0048, 0x0120));
    public_tags.emplace("ReferencedImageNavigationSequence", Tag(0x0048, 0x0200));
    public_tags.emplace("TopLeftHandCornerOfLocalizerArea", Tag(0x0048, 0x0201));
    public_tags.emplace("BottomRightHandCornerOfLocalizerArea", Tag(0x0048, 0x0202));
    public_tags.emplace("OpticalPathIdentificationSequence", Tag(0x0048, 0x0207));
    public_tags.emplace("PlanePositionSlideSequence", Tag(0x0048, 0x021a));
    public_tags.emplace("ColumnPositionInTotalImagePixelMatrix", Tag(0x0048, 0x021e));
    public_tags.emplace("RowPositionInTotalImagePixelMatrix", Tag(0x0048, 0x021f));
    public_tags.emplace("PixelOriginInterpretation", Tag(0x0048, 0x0301));
    public_tags.emplace("NumberOfOpticalPaths", Tag(0x0048, 0x0302));
    public_tags.emplace("TotalPixelMatrixFocalPlanes", Tag(0x0048, 0x0303));
}

}

}