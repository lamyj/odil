/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0016
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0016

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const WhitePoint(0x0016, 0x0001);
Tag const PrimaryChromaticities(0x0016, 0x0002);
Tag const BatteryLevel(0x0016, 0x0003);
Tag const ExposureTimeInSeconds(0x0016, 0x0004);
Tag const FNumber(0x0016, 0x0005);
Tag const OECFRows(0x0016, 0x0006);
Tag const OECFColumns(0x0016, 0x0007);
Tag const OECFColumnNames(0x0016, 0x0008);
Tag const OECFValues(0x0016, 0x0009);
Tag const SpatialFrequencyResponseRows(0x0016, 0x000a);
Tag const SpatialFrequencyResponseColumns(0x0016, 0x000b);
Tag const SpatialFrequencyResponseColumnNames(0x0016, 0x000c);
Tag const SpatialFrequencyResponseValues(0x0016, 0x000d);
Tag const ColorFilterArrayPatternRows(0x0016, 0x000e);
Tag const ColorFilterArrayPatternColumns(0x0016, 0x000f);
Tag const ColorFilterArrayPatternValues(0x0016, 0x0010);
Tag const FlashFiringStatus(0x0016, 0x0011);
Tag const FlashReturnStatus(0x0016, 0x0012);
Tag const FlashMode(0x0016, 0x0013);
Tag const FlashFunctionPresent(0x0016, 0x0014);
Tag const FlashRedEyeMode(0x0016, 0x0015);
Tag const ExposureProgram(0x0016, 0x0016);
Tag const SpectralSensitivity(0x0016, 0x0017);
Tag const PhotographicSensitivity(0x0016, 0x0018);
Tag const SelfTimerMode(0x0016, 0x0019);
Tag const SensitivityType(0x0016, 0x001a);
Tag const StandardOutputSensitivity(0x0016, 0x001b);
Tag const RecommendedExposureIndex(0x0016, 0x001c);
Tag const ISOSpeed(0x0016, 0x001d);
Tag const ISOSpeedLatitudeyyy(0x0016, 0x001e);
Tag const ISOSpeedLatitudezzz(0x0016, 0x001f);
Tag const EXIFVersion(0x0016, 0x0020);
Tag const ShutterSpeedValue(0x0016, 0x0021);
Tag const ApertureValue(0x0016, 0x0022);
Tag const BrightnessValue(0x0016, 0x0023);
Tag const ExposureBiasValue(0x0016, 0x0024);
Tag const MaxApertureValue(0x0016, 0x0025);
Tag const SubjectDistance(0x0016, 0x0026);
Tag const MeteringMode(0x0016, 0x0027);
Tag const LightSource(0x0016, 0x0028);
Tag const FocalLength(0x0016, 0x0029);
Tag const SubjectArea(0x0016, 0x002a);
Tag const MakerNote(0x0016, 0x002b);
Tag const Temperature(0x0016, 0x0030);
Tag const Humidity(0x0016, 0x0031);
Tag const Pressure(0x0016, 0x0032);
Tag const WaterDepth(0x0016, 0x0033);
Tag const Acceleration(0x0016, 0x0034);
Tag const CameraElevationAngle(0x0016, 0x0035);
Tag const FlashEnergy(0x0016, 0x0036);
Tag const SubjectLocation(0x0016, 0x0037);
Tag const PhotographicExposureIndex(0x0016, 0x0038);
Tag const SensingMethod(0x0016, 0x0039);
Tag const FileSource(0x0016, 0x003a);
Tag const SceneType(0x0016, 0x003b);
Tag const CustomRendered(0x0016, 0x0041);
Tag const ExposureMode(0x0016, 0x0042);
Tag const WhiteBalance(0x0016, 0x0043);
Tag const DigitalZoomRatio(0x0016, 0x0044);
Tag const FocalLengthIn35mmFilm(0x0016, 0x0045);
Tag const SceneCaptureType(0x0016, 0x0046);
Tag const GainControl(0x0016, 0x0047);
Tag const Contrast(0x0016, 0x0048);
Tag const Saturation(0x0016, 0x0049);
Tag const Sharpness(0x0016, 0x004a);
Tag const DeviceSettingDescription(0x0016, 0x004b);
Tag const SubjectDistanceRange(0x0016, 0x004c);
Tag const CameraOwnerName(0x0016, 0x004d);
Tag const LensSpecification(0x0016, 0x004e);
Tag const LensMake(0x0016, 0x004f);
Tag const LensModel(0x0016, 0x0050);
Tag const LensSerialNumber(0x0016, 0x0051);
Tag const InteroperabilityIndex(0x0016, 0x0061);
Tag const InteroperabilityVersion(0x0016, 0x0062);
Tag const GPSVersionID(0x0016, 0x0070);
Tag const GPSLatitudeRef(0x0016, 0x0071);
Tag const GPSLatitude(0x0016, 0x0072);
Tag const GPSLongitudeRef(0x0016, 0x0073);
Tag const GPSLongitude(0x0016, 0x0074);
Tag const GPSAltitudeRef(0x0016, 0x0075);
Tag const GPSAltitude(0x0016, 0x0076);
Tag const GPSTimeStamp(0x0016, 0x0077);
Tag const GPSSatellites(0x0016, 0x0078);
Tag const GPSStatus(0x0016, 0x0079);
Tag const GPSMeasureMode(0x0016, 0x007a);
Tag const GPSDOP(0x0016, 0x007b);
Tag const GPSSpeedRef(0x0016, 0x007c);
Tag const GPSSpeed(0x0016, 0x007d);
Tag const GPSTrackRef(0x0016, 0x007e);
Tag const GPSTrack(0x0016, 0x007f);
Tag const GPSImgDirectionRef(0x0016, 0x0080);
Tag const GPSImgDirection(0x0016, 0x0081);
Tag const GPSMapDatum(0x0016, 0x0082);
Tag const GPSDestLatitudeRef(0x0016, 0x0083);
Tag const GPSDestLatitude(0x0016, 0x0084);
Tag const GPSDestLongitudeRef(0x0016, 0x0085);
Tag const GPSDestLongitude(0x0016, 0x0086);
Tag const GPSDestBearingRef(0x0016, 0x0087);
Tag const GPSDestBearing(0x0016, 0x0088);
Tag const GPSDestDistanceRef(0x0016, 0x0089);
Tag const GPSDestDistance(0x0016, 0x008a);
Tag const GPSProcessingMethod(0x0016, 0x008b);
Tag const GPSAreaInformation(0x0016, 0x008c);
Tag const GPSDateStamp(0x0016, 0x008d);
Tag const GPSDifferential(0x0016, 0x008e);
Tag const LightSourcePolarization(0x0016, 0x1001);
Tag const EmitterColorTemperature(0x0016, 0x1002);
Tag const ContactMethod(0x0016, 0x1003);
Tag const ImmersionMedia(0x0016, 0x1004);
Tag const OpticalMagnificationFactor(0x0016, 0x1005);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0016