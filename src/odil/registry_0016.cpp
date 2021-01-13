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

void update_0016(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0016, 0x0001), ElementsDictionaryEntry("White Point", "WhitePoint",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0002), ElementsDictionaryEntry("Primary Chromaticities", "PrimaryChromaticities",  "DS", "3"));
    public_dictionary.emplace(Tag(0x0016, 0x0003), ElementsDictionaryEntry("Battery Level", "BatteryLevel",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0004), ElementsDictionaryEntry("Exposure Time in Seconds", "ExposureTimeInSeconds",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0005), ElementsDictionaryEntry("F-Number", "FNumber",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0006), ElementsDictionaryEntry("OECF Rows", "OECFRows",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0007), ElementsDictionaryEntry("OECF Columns", "OECFColumns",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0008), ElementsDictionaryEntry("OECF Column Names", "OECFColumnNames",  "UC", "1-n"));
    public_dictionary.emplace(Tag(0x0016, 0x0009), ElementsDictionaryEntry("OECF Values", "OECFValues",  "DS", "1-n"));
    public_dictionary.emplace(Tag(0x0016, 0x000a), ElementsDictionaryEntry("Spatial Frequency Response Rows", "SpatialFrequencyResponseRows",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x000b), ElementsDictionaryEntry("Spatial Frequency Response Columns", "SpatialFrequencyResponseColumns",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x000c), ElementsDictionaryEntry("Spatial Frequency Response Column Names", "SpatialFrequencyResponseColumnNames",  "UC", "1-n"));
    public_dictionary.emplace(Tag(0x0016, 0x000d), ElementsDictionaryEntry("Spatial Frequency Response Values", "SpatialFrequencyResponseValues",  "DS", "1-n"));
    public_dictionary.emplace(Tag(0x0016, 0x000e), ElementsDictionaryEntry("Color Filter Array Pattern Rows", "ColorFilterArrayPatternRows",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x000f), ElementsDictionaryEntry("Color Filter Array Pattern Columns", "ColorFilterArrayPatternColumns",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0010), ElementsDictionaryEntry("Color Filter Array Pattern Values", "ColorFilterArrayPatternValues",  "DS", "1-n"));
    public_dictionary.emplace(Tag(0x0016, 0x0011), ElementsDictionaryEntry("Flash Firing Status", "FlashFiringStatus",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0012), ElementsDictionaryEntry("Flash Return Status", "FlashReturnStatus",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0013), ElementsDictionaryEntry("Flash Mode", "FlashMode",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0014), ElementsDictionaryEntry("Flash Function Present", "FlashFunctionPresent",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0015), ElementsDictionaryEntry("Flash Red Eye Mode", "FlashRedEyeMode",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0016), ElementsDictionaryEntry("Exposure Program", "ExposureProgram",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0017), ElementsDictionaryEntry("Spectral Sensitivity", "SpectralSensitivity",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0018), ElementsDictionaryEntry("Photographic Sensitivity", "PhotographicSensitivity",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0019), ElementsDictionaryEntry("Self Timer Mode", "SelfTimerMode",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x001a), ElementsDictionaryEntry("Sensitivity Type", "SensitivityType",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x001b), ElementsDictionaryEntry("Standard Output Sensitivity", "StandardOutputSensitivity",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x001c), ElementsDictionaryEntry("Recommended Exposure Index", "RecommendedExposureIndex",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x001d), ElementsDictionaryEntry("ISO Speed", "ISOSpeed",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x001e), ElementsDictionaryEntry("ISO Speed Latitude yyy", "ISOSpeedLatitudeyyy",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x001f), ElementsDictionaryEntry("ISO Speed Latitude zzz", "ISOSpeedLatitudezzz",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0020), ElementsDictionaryEntry("EXIF Version", "EXIFVersion",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0021), ElementsDictionaryEntry("Shutter Speed Value", "ShutterSpeedValue",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0022), ElementsDictionaryEntry("Aperture Value", "ApertureValue",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0023), ElementsDictionaryEntry("Brightness Value", "BrightnessValue",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0024), ElementsDictionaryEntry("Exposure Bias Value", "ExposureBiasValue",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0025), ElementsDictionaryEntry("Max Aperture Value", "MaxApertureValue",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0026), ElementsDictionaryEntry("Subject Distance", "SubjectDistance",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0027), ElementsDictionaryEntry("Metering Mode", "MeteringMode",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0028), ElementsDictionaryEntry("Light Source", "LightSource",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0029), ElementsDictionaryEntry("Focal Length", "FocalLength",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x002a), ElementsDictionaryEntry("Subject Area", "SubjectArea",  "IS", "2-4"));
    public_dictionary.emplace(Tag(0x0016, 0x002b), ElementsDictionaryEntry("Maker Note", "MakerNote",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0030), ElementsDictionaryEntry("Temperature", "Temperature",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0031), ElementsDictionaryEntry("Humidity", "Humidity",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0032), ElementsDictionaryEntry("Pressure", "Pressure",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0033), ElementsDictionaryEntry("Water Depth", "WaterDepth",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0034), ElementsDictionaryEntry("Acceleration", "Acceleration",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0035), ElementsDictionaryEntry("Camera Elevation Angle", "CameraElevationAngle",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0036), ElementsDictionaryEntry("Flash Energy", "FlashEnergy",  "DS", "1-2"));
    public_dictionary.emplace(Tag(0x0016, 0x0037), ElementsDictionaryEntry("Subject Location", "SubjectLocation",  "IS", "2"));
    public_dictionary.emplace(Tag(0x0016, 0x0038), ElementsDictionaryEntry("Photographic Exposure Index", "PhotographicExposureIndex",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0039), ElementsDictionaryEntry("Sensing Method", "SensingMethod",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x003a), ElementsDictionaryEntry("File Source", "FileSource",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x003b), ElementsDictionaryEntry("Scene Type", "SceneType",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0041), ElementsDictionaryEntry("Custom Rendered", "CustomRendered",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0042), ElementsDictionaryEntry("Exposure Mode", "ExposureMode",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0043), ElementsDictionaryEntry("White Balance", "WhiteBalance",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0044), ElementsDictionaryEntry("Digital Zoom Ratio", "DigitalZoomRatio",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0045), ElementsDictionaryEntry("Focal Length In 35mm Film", "FocalLengthIn35mmFilm",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0046), ElementsDictionaryEntry("Scene Capture Type", "SceneCaptureType",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0047), ElementsDictionaryEntry("Gain Control", "GainControl",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0048), ElementsDictionaryEntry("Contrast", "Contrast",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0049), ElementsDictionaryEntry("Saturation", "Saturation",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x004a), ElementsDictionaryEntry("Sharpness", "Sharpness",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x004b), ElementsDictionaryEntry("Device Setting Description", "DeviceSettingDescription",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x004c), ElementsDictionaryEntry("Subject Distance Range", "SubjectDistanceRange",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x004d), ElementsDictionaryEntry("Camera Owner Name", "CameraOwnerName",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x004e), ElementsDictionaryEntry("Lens Specification", "LensSpecification",  "DS", "4"));
    public_dictionary.emplace(Tag(0x0016, 0x004f), ElementsDictionaryEntry("Lens Make", "LensMake",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0050), ElementsDictionaryEntry("Lens Model", "LensModel",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0051), ElementsDictionaryEntry("Lens Serial Number", "LensSerialNumber",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0061), ElementsDictionaryEntry("Interoperability Index", "InteroperabilityIndex",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0062), ElementsDictionaryEntry("Interoperability Version", "InteroperabilityVersion",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0070), ElementsDictionaryEntry("GPS Version ID", "GPSVersionID",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0071), ElementsDictionaryEntry("GPS Latitude Ref", "GPSLatitudeRef",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0072), ElementsDictionaryEntry("GPS Latitude", "GPSLatitude",  "DS", "3"));
    public_dictionary.emplace(Tag(0x0016, 0x0073), ElementsDictionaryEntry("GPS Longitude Ref", "GPSLongitudeRef",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0074), ElementsDictionaryEntry("GPS Longitude", "GPSLongitude",  "DS", "3"));
    public_dictionary.emplace(Tag(0x0016, 0x0075), ElementsDictionaryEntry("GPS Altitude Ref", "GPSAltitudeRef",  "US", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0076), ElementsDictionaryEntry("GPS Altitude", "GPSAltitude",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0077), ElementsDictionaryEntry("GPS Time Stamp", "GPSTimeStamp",  "DT", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0078), ElementsDictionaryEntry("GPS Satellites", "GPSSatellites",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0079), ElementsDictionaryEntry("GPS Status", "GPSStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x007a), ElementsDictionaryEntry("GPS Measure Mode", "GPSMeasureMode",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x007b), ElementsDictionaryEntry("GPS DOP", "GPSDOP",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x007c), ElementsDictionaryEntry("GPS Speed Ref", "GPSSpeedRef",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x007d), ElementsDictionaryEntry("GPS Speed", "GPSSpeed",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x007e), ElementsDictionaryEntry("GPS Track Ref", "GPSTrackRef",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x007f), ElementsDictionaryEntry("GPS Track", "GPSTrack",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0080), ElementsDictionaryEntry("GPS Img Direction Ref", "GPSImgDirectionRef",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0081), ElementsDictionaryEntry("GPS Img Direction", "GPSImgDirection",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0082), ElementsDictionaryEntry("GPS Map Datum", "GPSMapDatum",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0083), ElementsDictionaryEntry("GPS Dest Latitude Ref", "GPSDestLatitudeRef",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0084), ElementsDictionaryEntry("GPS Dest Latitude", "GPSDestLatitude",  "DS", "3"));
    public_dictionary.emplace(Tag(0x0016, 0x0085), ElementsDictionaryEntry("GPS Dest Longitude Ref", "GPSDestLongitudeRef",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0086), ElementsDictionaryEntry("GPS Dest Longitude", "GPSDestLongitude",  "DS", "3"));
    public_dictionary.emplace(Tag(0x0016, 0x0087), ElementsDictionaryEntry("GPS Dest Bearing Ref", "GPSDestBearingRef",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0088), ElementsDictionaryEntry("GPS Dest Bearing", "GPSDestBearing",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x0089), ElementsDictionaryEntry("GPS Dest Distance Ref", "GPSDestDistanceRef",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x008a), ElementsDictionaryEntry("GPS Dest Distance", "GPSDestDistance",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x008b), ElementsDictionaryEntry("GPS Processing Method", "GPSProcessingMethod",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x008c), ElementsDictionaryEntry("GPS Area Information", "GPSAreaInformation",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x008d), ElementsDictionaryEntry("GPS Date Stamp", "GPSDateStamp",  "DT", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x008e), ElementsDictionaryEntry("GPS Differential", "GPSDifferential",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x1001), ElementsDictionaryEntry("Light Source Polarization", "LightSourcePolarization",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x1002), ElementsDictionaryEntry("Emitter Color Temperature", "EmitterColorTemperature",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x1003), ElementsDictionaryEntry("Contact Method", "ContactMethod",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0016, 0x1004), ElementsDictionaryEntry("Immersion Media", "ImmersionMedia",  "CS", "1-n"));
    public_dictionary.emplace(Tag(0x0016, 0x1005), ElementsDictionaryEntry("Optical Magnification Factor", "OpticalMagnificationFactor",  "DS", "1"));

    public_tags.emplace("WhitePoint", Tag(0x0016, 0x0001));
    public_tags.emplace("PrimaryChromaticities", Tag(0x0016, 0x0002));
    public_tags.emplace("BatteryLevel", Tag(0x0016, 0x0003));
    public_tags.emplace("ExposureTimeInSeconds", Tag(0x0016, 0x0004));
    public_tags.emplace("FNumber", Tag(0x0016, 0x0005));
    public_tags.emplace("OECFRows", Tag(0x0016, 0x0006));
    public_tags.emplace("OECFColumns", Tag(0x0016, 0x0007));
    public_tags.emplace("OECFColumnNames", Tag(0x0016, 0x0008));
    public_tags.emplace("OECFValues", Tag(0x0016, 0x0009));
    public_tags.emplace("SpatialFrequencyResponseRows", Tag(0x0016, 0x000a));
    public_tags.emplace("SpatialFrequencyResponseColumns", Tag(0x0016, 0x000b));
    public_tags.emplace("SpatialFrequencyResponseColumnNames", Tag(0x0016, 0x000c));
    public_tags.emplace("SpatialFrequencyResponseValues", Tag(0x0016, 0x000d));
    public_tags.emplace("ColorFilterArrayPatternRows", Tag(0x0016, 0x000e));
    public_tags.emplace("ColorFilterArrayPatternColumns", Tag(0x0016, 0x000f));
    public_tags.emplace("ColorFilterArrayPatternValues", Tag(0x0016, 0x0010));
    public_tags.emplace("FlashFiringStatus", Tag(0x0016, 0x0011));
    public_tags.emplace("FlashReturnStatus", Tag(0x0016, 0x0012));
    public_tags.emplace("FlashMode", Tag(0x0016, 0x0013));
    public_tags.emplace("FlashFunctionPresent", Tag(0x0016, 0x0014));
    public_tags.emplace("FlashRedEyeMode", Tag(0x0016, 0x0015));
    public_tags.emplace("ExposureProgram", Tag(0x0016, 0x0016));
    public_tags.emplace("SpectralSensitivity", Tag(0x0016, 0x0017));
    public_tags.emplace("PhotographicSensitivity", Tag(0x0016, 0x0018));
    public_tags.emplace("SelfTimerMode", Tag(0x0016, 0x0019));
    public_tags.emplace("SensitivityType", Tag(0x0016, 0x001a));
    public_tags.emplace("StandardOutputSensitivity", Tag(0x0016, 0x001b));
    public_tags.emplace("RecommendedExposureIndex", Tag(0x0016, 0x001c));
    public_tags.emplace("ISOSpeed", Tag(0x0016, 0x001d));
    public_tags.emplace("ISOSpeedLatitudeyyy", Tag(0x0016, 0x001e));
    public_tags.emplace("ISOSpeedLatitudezzz", Tag(0x0016, 0x001f));
    public_tags.emplace("EXIFVersion", Tag(0x0016, 0x0020));
    public_tags.emplace("ShutterSpeedValue", Tag(0x0016, 0x0021));
    public_tags.emplace("ApertureValue", Tag(0x0016, 0x0022));
    public_tags.emplace("BrightnessValue", Tag(0x0016, 0x0023));
    public_tags.emplace("ExposureBiasValue", Tag(0x0016, 0x0024));
    public_tags.emplace("MaxApertureValue", Tag(0x0016, 0x0025));
    public_tags.emplace("SubjectDistance", Tag(0x0016, 0x0026));
    public_tags.emplace("MeteringMode", Tag(0x0016, 0x0027));
    public_tags.emplace("LightSource", Tag(0x0016, 0x0028));
    public_tags.emplace("FocalLength", Tag(0x0016, 0x0029));
    public_tags.emplace("SubjectArea", Tag(0x0016, 0x002a));
    public_tags.emplace("MakerNote", Tag(0x0016, 0x002b));
    public_tags.emplace("Temperature", Tag(0x0016, 0x0030));
    public_tags.emplace("Humidity", Tag(0x0016, 0x0031));
    public_tags.emplace("Pressure", Tag(0x0016, 0x0032));
    public_tags.emplace("WaterDepth", Tag(0x0016, 0x0033));
    public_tags.emplace("Acceleration", Tag(0x0016, 0x0034));
    public_tags.emplace("CameraElevationAngle", Tag(0x0016, 0x0035));
    public_tags.emplace("FlashEnergy", Tag(0x0016, 0x0036));
    public_tags.emplace("SubjectLocation", Tag(0x0016, 0x0037));
    public_tags.emplace("PhotographicExposureIndex", Tag(0x0016, 0x0038));
    public_tags.emplace("SensingMethod", Tag(0x0016, 0x0039));
    public_tags.emplace("FileSource", Tag(0x0016, 0x003a));
    public_tags.emplace("SceneType", Tag(0x0016, 0x003b));
    public_tags.emplace("CustomRendered", Tag(0x0016, 0x0041));
    public_tags.emplace("ExposureMode", Tag(0x0016, 0x0042));
    public_tags.emplace("WhiteBalance", Tag(0x0016, 0x0043));
    public_tags.emplace("DigitalZoomRatio", Tag(0x0016, 0x0044));
    public_tags.emplace("FocalLengthIn35mmFilm", Tag(0x0016, 0x0045));
    public_tags.emplace("SceneCaptureType", Tag(0x0016, 0x0046));
    public_tags.emplace("GainControl", Tag(0x0016, 0x0047));
    public_tags.emplace("Contrast", Tag(0x0016, 0x0048));
    public_tags.emplace("Saturation", Tag(0x0016, 0x0049));
    public_tags.emplace("Sharpness", Tag(0x0016, 0x004a));
    public_tags.emplace("DeviceSettingDescription", Tag(0x0016, 0x004b));
    public_tags.emplace("SubjectDistanceRange", Tag(0x0016, 0x004c));
    public_tags.emplace("CameraOwnerName", Tag(0x0016, 0x004d));
    public_tags.emplace("LensSpecification", Tag(0x0016, 0x004e));
    public_tags.emplace("LensMake", Tag(0x0016, 0x004f));
    public_tags.emplace("LensModel", Tag(0x0016, 0x0050));
    public_tags.emplace("LensSerialNumber", Tag(0x0016, 0x0051));
    public_tags.emplace("InteroperabilityIndex", Tag(0x0016, 0x0061));
    public_tags.emplace("InteroperabilityVersion", Tag(0x0016, 0x0062));
    public_tags.emplace("GPSVersionID", Tag(0x0016, 0x0070));
    public_tags.emplace("GPSLatitudeRef", Tag(0x0016, 0x0071));
    public_tags.emplace("GPSLatitude", Tag(0x0016, 0x0072));
    public_tags.emplace("GPSLongitudeRef", Tag(0x0016, 0x0073));
    public_tags.emplace("GPSLongitude", Tag(0x0016, 0x0074));
    public_tags.emplace("GPSAltitudeRef", Tag(0x0016, 0x0075));
    public_tags.emplace("GPSAltitude", Tag(0x0016, 0x0076));
    public_tags.emplace("GPSTimeStamp", Tag(0x0016, 0x0077));
    public_tags.emplace("GPSSatellites", Tag(0x0016, 0x0078));
    public_tags.emplace("GPSStatus", Tag(0x0016, 0x0079));
    public_tags.emplace("GPSMeasureMode", Tag(0x0016, 0x007a));
    public_tags.emplace("GPSDOP", Tag(0x0016, 0x007b));
    public_tags.emplace("GPSSpeedRef", Tag(0x0016, 0x007c));
    public_tags.emplace("GPSSpeed", Tag(0x0016, 0x007d));
    public_tags.emplace("GPSTrackRef", Tag(0x0016, 0x007e));
    public_tags.emplace("GPSTrack", Tag(0x0016, 0x007f));
    public_tags.emplace("GPSImgDirectionRef", Tag(0x0016, 0x0080));
    public_tags.emplace("GPSImgDirection", Tag(0x0016, 0x0081));
    public_tags.emplace("GPSMapDatum", Tag(0x0016, 0x0082));
    public_tags.emplace("GPSDestLatitudeRef", Tag(0x0016, 0x0083));
    public_tags.emplace("GPSDestLatitude", Tag(0x0016, 0x0084));
    public_tags.emplace("GPSDestLongitudeRef", Tag(0x0016, 0x0085));
    public_tags.emplace("GPSDestLongitude", Tag(0x0016, 0x0086));
    public_tags.emplace("GPSDestBearingRef", Tag(0x0016, 0x0087));
    public_tags.emplace("GPSDestBearing", Tag(0x0016, 0x0088));
    public_tags.emplace("GPSDestDistanceRef", Tag(0x0016, 0x0089));
    public_tags.emplace("GPSDestDistance", Tag(0x0016, 0x008a));
    public_tags.emplace("GPSProcessingMethod", Tag(0x0016, 0x008b));
    public_tags.emplace("GPSAreaInformation", Tag(0x0016, 0x008c));
    public_tags.emplace("GPSDateStamp", Tag(0x0016, 0x008d));
    public_tags.emplace("GPSDifferential", Tag(0x0016, 0x008e));
    public_tags.emplace("LightSourcePolarization", Tag(0x0016, 0x1001));
    public_tags.emplace("EmitterColorTemperature", Tag(0x0016, 0x1002));
    public_tags.emplace("ContactMethod", Tag(0x0016, 0x1003));
    public_tags.emplace("ImmersionMedia", Tag(0x0016, 0x1004));
    public_tags.emplace("OpticalMagnificationFactor", Tag(0x0016, 0x1005));
}

}

}