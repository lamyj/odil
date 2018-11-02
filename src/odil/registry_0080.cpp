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

void update_0080(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0080, 0x0001), ElementsDictionaryEntry("Surface Scan Acquisition Type Code Sequence", "SurfaceScanAcquisitionTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0080, 0x0002), ElementsDictionaryEntry("Surface Scan Mode Code Sequence", "SurfaceScanModeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0080, 0x0003), ElementsDictionaryEntry("Registration Method Code Sequence", "RegistrationMethodCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0080, 0x0004), ElementsDictionaryEntry("Shot Duration Time", "ShotDurationTime",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0080, 0x0005), ElementsDictionaryEntry("Shot Offset Time", "ShotOffsetTime",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0080, 0x0006), ElementsDictionaryEntry("Surface Point Presentation Value Data", "SurfacePointPresentationValueData",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0080, 0x0007), ElementsDictionaryEntry("Surface Point Color CIELab Value Data", "SurfacePointColorCIELabValueData",  "US", "3-3n"));
    public_dictionary.emplace(Tag(0x0080, 0x0008), ElementsDictionaryEntry("UV Mapping Sequence", "UVMappingSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0080, 0x0009), ElementsDictionaryEntry("Texture Label", "TextureLabel",  "SH", "1"));
    public_dictionary.emplace(Tag(0x0080, 0x0010), ElementsDictionaryEntry("U Value Data", "UValueData",  "OF", "1"));
    public_dictionary.emplace(Tag(0x0080, 0x0011), ElementsDictionaryEntry("V Value Data", "VValueData",  "OF", "1"));
    public_dictionary.emplace(Tag(0x0080, 0x0012), ElementsDictionaryEntry("Referenced Texture Sequence", "ReferencedTextureSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0080, 0x0013), ElementsDictionaryEntry("Referenced Surface Data Sequence", "ReferencedSurfaceDataSequence",  "SQ", "1"));

    public_tags.emplace("SurfaceScanAcquisitionTypeCodeSequence", Tag(0x0080, 0x0001));
    public_tags.emplace("SurfaceScanModeCodeSequence", Tag(0x0080, 0x0002));
    public_tags.emplace("RegistrationMethodCodeSequence", Tag(0x0080, 0x0003));
    public_tags.emplace("ShotDurationTime", Tag(0x0080, 0x0004));
    public_tags.emplace("ShotOffsetTime", Tag(0x0080, 0x0005));
    public_tags.emplace("SurfacePointPresentationValueData", Tag(0x0080, 0x0006));
    public_tags.emplace("SurfacePointColorCIELabValueData", Tag(0x0080, 0x0007));
    public_tags.emplace("UVMappingSequence", Tag(0x0080, 0x0008));
    public_tags.emplace("TextureLabel", Tag(0x0080, 0x0009));
    public_tags.emplace("UValueData", Tag(0x0080, 0x0010));
    public_tags.emplace("VValueData", Tag(0x0080, 0x0011));
    public_tags.emplace("ReferencedTextureSequence", Tag(0x0080, 0x0012));
    public_tags.emplace("ReferencedSurfaceDataSequence", Tag(0x0080, 0x0013));
}

}

}