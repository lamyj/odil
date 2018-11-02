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

void update_0052(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0052, 0x0001), ElementsDictionaryEntry("Contrast/Bolus Ingredient Percent by Volume", "ContrastBolusIngredientPercentByVolume",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0002), ElementsDictionaryEntry("OCT Focal Distance", "OCTFocalDistance",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0003), ElementsDictionaryEntry("Beam Spot Size", "BeamSpotSize",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0004), ElementsDictionaryEntry("Effective Refractive Index", "EffectiveRefractiveIndex",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0006), ElementsDictionaryEntry("OCT Acquisition Domain", "OCTAcquisitionDomain",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0007), ElementsDictionaryEntry("OCT Optical Center Wavelength", "OCTOpticalCenterWavelength",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0008), ElementsDictionaryEntry("Axial Resolution", "AxialResolution",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0009), ElementsDictionaryEntry("Ranging Depth", "RangingDepth",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0011), ElementsDictionaryEntry("A-line Rate", "ALineRate",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0012), ElementsDictionaryEntry("A-lines Per Frame", "ALinesPerFrame",  "US", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0013), ElementsDictionaryEntry("Catheter Rotational Rate", "CatheterRotationalRate",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0014), ElementsDictionaryEntry("A-line Pixel Spacing", "ALinePixelSpacing",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0016), ElementsDictionaryEntry("Mode of Percutaneous Access Sequence", "ModeOfPercutaneousAccessSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0025), ElementsDictionaryEntry("Intravascular OCT Frame Type Sequence", "IntravascularOCTFrameTypeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0026), ElementsDictionaryEntry("OCT Z Offset Applied", "OCTZOffsetApplied",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0027), ElementsDictionaryEntry("Intravascular Frame Content Sequence", "IntravascularFrameContentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0028), ElementsDictionaryEntry("Intravascular Longitudinal Distance", "IntravascularLongitudinalDistance",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0029), ElementsDictionaryEntry("Intravascular OCT Frame Content Sequence", "IntravascularOCTFrameContentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0030), ElementsDictionaryEntry("OCT Z Offset Correction", "OCTZOffsetCorrection",  "SS", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0031), ElementsDictionaryEntry("Catheter Direction of Rotation", "CatheterDirectionOfRotation",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0033), ElementsDictionaryEntry("Seam Line Location", "SeamLineLocation",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0034), ElementsDictionaryEntry("First A-line Location", "FirstALineLocation",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0036), ElementsDictionaryEntry("Seam Line Index", "SeamLineIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0038), ElementsDictionaryEntry("Number of Padded A-lines", "NumberOfPaddedALines",  "US", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x0039), ElementsDictionaryEntry("Interpolation Type", "InterpolationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0052, 0x003a), ElementsDictionaryEntry("Refractive Index Applied", "RefractiveIndexApplied",  "CS", "1"));

    public_tags.emplace("ContrastBolusIngredientPercentByVolume", Tag(0x0052, 0x0001));
    public_tags.emplace("OCTFocalDistance", Tag(0x0052, 0x0002));
    public_tags.emplace("BeamSpotSize", Tag(0x0052, 0x0003));
    public_tags.emplace("EffectiveRefractiveIndex", Tag(0x0052, 0x0004));
    public_tags.emplace("OCTAcquisitionDomain", Tag(0x0052, 0x0006));
    public_tags.emplace("OCTOpticalCenterWavelength", Tag(0x0052, 0x0007));
    public_tags.emplace("AxialResolution", Tag(0x0052, 0x0008));
    public_tags.emplace("RangingDepth", Tag(0x0052, 0x0009));
    public_tags.emplace("ALineRate", Tag(0x0052, 0x0011));
    public_tags.emplace("ALinesPerFrame", Tag(0x0052, 0x0012));
    public_tags.emplace("CatheterRotationalRate", Tag(0x0052, 0x0013));
    public_tags.emplace("ALinePixelSpacing", Tag(0x0052, 0x0014));
    public_tags.emplace("ModeOfPercutaneousAccessSequence", Tag(0x0052, 0x0016));
    public_tags.emplace("IntravascularOCTFrameTypeSequence", Tag(0x0052, 0x0025));
    public_tags.emplace("OCTZOffsetApplied", Tag(0x0052, 0x0026));
    public_tags.emplace("IntravascularFrameContentSequence", Tag(0x0052, 0x0027));
    public_tags.emplace("IntravascularLongitudinalDistance", Tag(0x0052, 0x0028));
    public_tags.emplace("IntravascularOCTFrameContentSequence", Tag(0x0052, 0x0029));
    public_tags.emplace("OCTZOffsetCorrection", Tag(0x0052, 0x0030));
    public_tags.emplace("CatheterDirectionOfRotation", Tag(0x0052, 0x0031));
    public_tags.emplace("SeamLineLocation", Tag(0x0052, 0x0033));
    public_tags.emplace("FirstALineLocation", Tag(0x0052, 0x0034));
    public_tags.emplace("SeamLineIndex", Tag(0x0052, 0x0036));
    public_tags.emplace("NumberOfPaddedALines", Tag(0x0052, 0x0038));
    public_tags.emplace("InterpolationType", Tag(0x0052, 0x0039));
    public_tags.emplace("RefractiveIndexApplied", Tag(0x0052, 0x003a));
}

}

}