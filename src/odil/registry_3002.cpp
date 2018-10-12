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

void update_3002(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x3002, 0x0002), ElementsDictionaryEntry("RT Image Label", "RTImageLabel",  "SH", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0003), ElementsDictionaryEntry("RT Image Name", "RTImageName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0004), ElementsDictionaryEntry("RT Image Description", "RTImageDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x000a), ElementsDictionaryEntry("Reported Values Origin", "ReportedValuesOrigin",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x000c), ElementsDictionaryEntry("RT Image Plane", "RTImagePlane",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x000d), ElementsDictionaryEntry("X-Ray Image Receptor Translation", "XRayImageReceptorTranslation",  "DS", "3"));
    public_dictionary.emplace(Tag(0x3002, 0x000e), ElementsDictionaryEntry("X-Ray Image Receptor Angle", "XRayImageReceptorAngle",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0010), ElementsDictionaryEntry("RT Image Orientation", "RTImageOrientation",  "DS", "6"));
    public_dictionary.emplace(Tag(0x3002, 0x0011), ElementsDictionaryEntry("Image Plane Pixel Spacing", "ImagePlanePixelSpacing",  "DS", "2"));
    public_dictionary.emplace(Tag(0x3002, 0x0012), ElementsDictionaryEntry("RT Image Position", "RTImagePosition",  "DS", "2"));
    public_dictionary.emplace(Tag(0x3002, 0x0020), ElementsDictionaryEntry("Radiation Machine Name", "RadiationMachineName",  "SH", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0022), ElementsDictionaryEntry("Radiation Machine SAD", "RadiationMachineSAD",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0024), ElementsDictionaryEntry("Radiation Machine SSD", "RadiationMachineSSD",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0026), ElementsDictionaryEntry("RT Image SID", "RTImageSID",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0028), ElementsDictionaryEntry("Source to Reference Object Distance", "SourceToReferenceObjectDistance",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0029), ElementsDictionaryEntry("Fraction Number", "FractionNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0030), ElementsDictionaryEntry("Exposure Sequence", "ExposureSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0032), ElementsDictionaryEntry("Meterset Exposure", "MetersetExposure",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0034), ElementsDictionaryEntry("Diaphragm Position", "DiaphragmPosition",  "DS", "4"));
    public_dictionary.emplace(Tag(0x3002, 0x0040), ElementsDictionaryEntry("Fluence Map Sequence", "FluenceMapSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0041), ElementsDictionaryEntry("Fluence Data Source", "FluenceDataSource",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0042), ElementsDictionaryEntry("Fluence Data Scale", "FluenceDataScale",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0050), ElementsDictionaryEntry("Primary Fluence Mode Sequence", "PrimaryFluenceModeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0051), ElementsDictionaryEntry("Fluence Mode", "FluenceMode",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0052), ElementsDictionaryEntry("Fluence Mode ID", "FluenceModeID",  "SH", "1"));

    public_tags.emplace("RTImageLabel", Tag(0x3002, 0x0002));
    public_tags.emplace("RTImageName", Tag(0x3002, 0x0003));
    public_tags.emplace("RTImageDescription", Tag(0x3002, 0x0004));
    public_tags.emplace("ReportedValuesOrigin", Tag(0x3002, 0x000a));
    public_tags.emplace("RTImagePlane", Tag(0x3002, 0x000c));
    public_tags.emplace("XRayImageReceptorTranslation", Tag(0x3002, 0x000d));
    public_tags.emplace("XRayImageReceptorAngle", Tag(0x3002, 0x000e));
    public_tags.emplace("RTImageOrientation", Tag(0x3002, 0x0010));
    public_tags.emplace("ImagePlanePixelSpacing", Tag(0x3002, 0x0011));
    public_tags.emplace("RTImagePosition", Tag(0x3002, 0x0012));
    public_tags.emplace("RadiationMachineName", Tag(0x3002, 0x0020));
    public_tags.emplace("RadiationMachineSAD", Tag(0x3002, 0x0022));
    public_tags.emplace("RadiationMachineSSD", Tag(0x3002, 0x0024));
    public_tags.emplace("RTImageSID", Tag(0x3002, 0x0026));
    public_tags.emplace("SourceToReferenceObjectDistance", Tag(0x3002, 0x0028));
    public_tags.emplace("FractionNumber", Tag(0x3002, 0x0029));
    public_tags.emplace("ExposureSequence", Tag(0x3002, 0x0030));
    public_tags.emplace("MetersetExposure", Tag(0x3002, 0x0032));
    public_tags.emplace("DiaphragmPosition", Tag(0x3002, 0x0034));
    public_tags.emplace("FluenceMapSequence", Tag(0x3002, 0x0040));
    public_tags.emplace("FluenceDataSource", Tag(0x3002, 0x0041));
    public_tags.emplace("FluenceDataScale", Tag(0x3002, 0x0042));
    public_tags.emplace("PrimaryFluenceModeSequence", Tag(0x3002, 0x0050));
    public_tags.emplace("FluenceMode", Tag(0x3002, 0x0051));
    public_tags.emplace("FluenceModeID", Tag(0x3002, 0x0052));
}

}

}