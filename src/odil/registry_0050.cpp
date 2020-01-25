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

void update_0050(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0050, 0x0004), ElementsDictionaryEntry("Calibration Image", "CalibrationImage",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x0010), ElementsDictionaryEntry("Device Sequence", "DeviceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x0012), ElementsDictionaryEntry("Container Component Type Code Sequence", "ContainerComponentTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x0013), ElementsDictionaryEntry("Container Component Thickness", "ContainerComponentThickness",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x0014), ElementsDictionaryEntry("Device Length", "DeviceLength",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x0015), ElementsDictionaryEntry("Container Component Width", "ContainerComponentWidth",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x0016), ElementsDictionaryEntry("Device Diameter", "DeviceDiameter",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x0017), ElementsDictionaryEntry("Device Diameter Units", "DeviceDiameterUnits",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x0018), ElementsDictionaryEntry("Device Volume", "DeviceVolume",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x0019), ElementsDictionaryEntry("Inter-Marker Distance", "InterMarkerDistance",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x001a), ElementsDictionaryEntry("Container Component Material", "ContainerComponentMaterial",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x001b), ElementsDictionaryEntry("Container Component ID", "ContainerComponentID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x001c), ElementsDictionaryEntry("Container Component Length", "ContainerComponentLength",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x001d), ElementsDictionaryEntry("Container Component Diameter", "ContainerComponentDiameter",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x001e), ElementsDictionaryEntry("Container Component Description", "ContainerComponentDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x0020), ElementsDictionaryEntry("Device Description", "DeviceDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0050, 0x0021), ElementsDictionaryEntry("Long Device Description", "LongDeviceDescription",  "ST", "1"));

    public_tags.emplace("CalibrationImage", Tag(0x0050, 0x0004));
    public_tags.emplace("DeviceSequence", Tag(0x0050, 0x0010));
    public_tags.emplace("ContainerComponentTypeCodeSequence", Tag(0x0050, 0x0012));
    public_tags.emplace("ContainerComponentThickness", Tag(0x0050, 0x0013));
    public_tags.emplace("DeviceLength", Tag(0x0050, 0x0014));
    public_tags.emplace("ContainerComponentWidth", Tag(0x0050, 0x0015));
    public_tags.emplace("DeviceDiameter", Tag(0x0050, 0x0016));
    public_tags.emplace("DeviceDiameterUnits", Tag(0x0050, 0x0017));
    public_tags.emplace("DeviceVolume", Tag(0x0050, 0x0018));
    public_tags.emplace("InterMarkerDistance", Tag(0x0050, 0x0019));
    public_tags.emplace("ContainerComponentMaterial", Tag(0x0050, 0x001a));
    public_tags.emplace("ContainerComponentID", Tag(0x0050, 0x001b));
    public_tags.emplace("ContainerComponentLength", Tag(0x0050, 0x001c));
    public_tags.emplace("ContainerComponentDiameter", Tag(0x0050, 0x001d));
    public_tags.emplace("ContainerComponentDescription", Tag(0x0050, 0x001e));
    public_tags.emplace("DeviceDescription", Tag(0x0050, 0x0020));
    public_tags.emplace("LongDeviceDescription", Tag(0x0050, 0x0021));
}

}

}