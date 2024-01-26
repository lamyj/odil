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
    public_dictionary.emplace(Tag(0x3002, 0x0100), ElementsDictionaryEntry("Selected Frame Number", "SelectedFrameNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0101), ElementsDictionaryEntry("Selected Frame Functional Groups Sequence", "SelectedFrameFunctionalGroupsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0102), ElementsDictionaryEntry("RT Image Frame General Content Sequence", "RTImageFrameGeneralContentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0103), ElementsDictionaryEntry("RT Image Frame Context Sequence", "RTImageFrameContextSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0104), ElementsDictionaryEntry("RT Image Scope Sequence", "RTImageScopeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0105), ElementsDictionaryEntry("Beam Modifier Coordinates Presence Flag", "BeamModifierCoordinatesPresenceFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0106), ElementsDictionaryEntry("Start Cumulative Meterset", "StartCumulativeMeterset",  "FD", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0107), ElementsDictionaryEntry("Stop Cumulative Meterset", "StopCumulativeMeterset",  "FD", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0108), ElementsDictionaryEntry("RT Acquisition Patient Position Sequence", "RTAcquisitionPatientPositionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0109), ElementsDictionaryEntry("RT Image Frame Imaging Device Position Sequence", "RTImageFrameImagingDevicePositionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x010a), ElementsDictionaryEntry("RT Image Frame kV Radiation Acquisition Sequence", "RTImageFramekVRadiationAcquisitionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x010b), ElementsDictionaryEntry("RT Image Frame MV Radiation Acquisition Sequence", "RTImageFrameMVRadiationAcquisitionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x010c), ElementsDictionaryEntry("RT Image Frame Radiation Acquisition Sequence", "RTImageFrameRadiationAcquisitionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x010d), ElementsDictionaryEntry("Imaging Source Position Sequence", "ImagingSourcePositionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x010e), ElementsDictionaryEntry("Image Receptor Position Sequence", "ImageReceptorPositionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x010f), ElementsDictionaryEntry("Device Position to Equipment Mapping Matrix", "DevicePositionToEquipmentMappingMatrix",  "FD", "16"));
    public_dictionary.emplace(Tag(0x3002, 0x0110), ElementsDictionaryEntry("Device Position Parameter Sequence", "DevicePositionParameterSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0111), ElementsDictionaryEntry("Imaging Source Location Specification Type", "ImagingSourceLocationSpecificationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0112), ElementsDictionaryEntry("Imaging Device Location Matrix Sequence", "ImagingDeviceLocationMatrixSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0113), ElementsDictionaryEntry("Imaging Device Location Parameter Sequence", "ImagingDeviceLocationParameterSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0114), ElementsDictionaryEntry("Imaging Aperture Sequence", "ImagingApertureSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0115), ElementsDictionaryEntry("Imaging Aperture Specification Type", "ImagingApertureSpecificationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0116), ElementsDictionaryEntry("Number of Acquisition Devices", "NumberOfAcquisitionDevices",  "US", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0117), ElementsDictionaryEntry("Acquisition Device Sequence", "AcquisitionDeviceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0118), ElementsDictionaryEntry("Acquisition Task Sequence", "AcquisitionTaskSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0119), ElementsDictionaryEntry("Acquisition Task Workitem Code Sequence", "AcquisitionTaskWorkitemCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x011a), ElementsDictionaryEntry("Acquisition Subtask Sequence", "AcquisitionSubtaskSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x011b), ElementsDictionaryEntry("Subtask Workitem Code Sequence", "SubtaskWorkitemCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x011c), ElementsDictionaryEntry("Acquisition Task Index", "AcquisitionTaskIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x011d), ElementsDictionaryEntry("Acquisition Subtask Index", "AcquisitionSubtaskIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x011e), ElementsDictionaryEntry("Referenced Baseline Parameters RT Radiation Instance Sequence", "ReferencedBaselineParametersRTRadiationInstanceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x011f), ElementsDictionaryEntry("Position Acquisition Template Identification Sequence", "PositionAcquisitionTemplateIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0120), ElementsDictionaryEntry("Position Acquisition Template ID", "PositionAcquisitionTemplateID",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0121), ElementsDictionaryEntry("Position Acquisition Template Name", "PositionAcquisitionTemplateName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0122), ElementsDictionaryEntry("Position Acquisition Template Code Sequence", "PositionAcquisitionTemplateCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0123), ElementsDictionaryEntry("Position Acquisition Template Description", "PositionAcquisitionTemplateDescription",  "LT", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0124), ElementsDictionaryEntry("Acquisition Task Applicability Sequence", "AcquisitionTaskApplicabilitySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0125), ElementsDictionaryEntry("Projection Imaging Acquisition Parameter Sequence", "ProjectionImagingAcquisitionParameterSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0126), ElementsDictionaryEntry("CT Imaging Acquisition Parameter Sequence", "CTImagingAcquisitionParameterSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0127), ElementsDictionaryEntry("KV Imaging Generation Parameters Sequence", "KVImagingGenerationParametersSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0128), ElementsDictionaryEntry("MV Imaging Generation Parameters Sequence", "MVImagingGenerationParametersSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0129), ElementsDictionaryEntry("Acquisition Signal Type", "AcquisitionSignalType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x012a), ElementsDictionaryEntry("Acquisition Method", "AcquisitionMethod",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x012b), ElementsDictionaryEntry("Scan Start Position Sequence", "ScanStartPositionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x012c), ElementsDictionaryEntry("Scan Stop Position Sequence", "ScanStopPositionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x012d), ElementsDictionaryEntry("Imaging Source to Beam Modifier Definition Plane Distance", "ImagingSourceToBeamModifierDefinitionPlaneDistance",  "FD", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x012e), ElementsDictionaryEntry("Scan Arc Type", "ScanArcType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x012f), ElementsDictionaryEntry("Detector Positioning Type", "DetectorPositioningType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0130), ElementsDictionaryEntry("Additional RT Accessory Device Sequence", "AdditionalRTAccessoryDeviceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0131), ElementsDictionaryEntry("Device-Specific Acquisition Parameter Sequence", "DeviceSpecificAcquisitionParameterSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0132), ElementsDictionaryEntry("Referenced Position Reference Instance Sequence", "ReferencedPositionReferenceInstanceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0133), ElementsDictionaryEntry("Energy Derivation Code Sequence", "EnergyDerivationCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0134), ElementsDictionaryEntry("Maximum Cumulative Meterset Exposure", "MaximumCumulativeMetersetExposure",  "FD", "1"));
    public_dictionary.emplace(Tag(0x3002, 0x0135), ElementsDictionaryEntry("Acquisition Initiation Sequence", "AcquisitionInitiationSequence",  "SQ", "1"));

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
    public_tags.emplace("SelectedFrameNumber", Tag(0x3002, 0x0100));
    public_tags.emplace("SelectedFrameFunctionalGroupsSequence", Tag(0x3002, 0x0101));
    public_tags.emplace("RTImageFrameGeneralContentSequence", Tag(0x3002, 0x0102));
    public_tags.emplace("RTImageFrameContextSequence", Tag(0x3002, 0x0103));
    public_tags.emplace("RTImageScopeSequence", Tag(0x3002, 0x0104));
    public_tags.emplace("BeamModifierCoordinatesPresenceFlag", Tag(0x3002, 0x0105));
    public_tags.emplace("StartCumulativeMeterset", Tag(0x3002, 0x0106));
    public_tags.emplace("StopCumulativeMeterset", Tag(0x3002, 0x0107));
    public_tags.emplace("RTAcquisitionPatientPositionSequence", Tag(0x3002, 0x0108));
    public_tags.emplace("RTImageFrameImagingDevicePositionSequence", Tag(0x3002, 0x0109));
    public_tags.emplace("RTImageFramekVRadiationAcquisitionSequence", Tag(0x3002, 0x010a));
    public_tags.emplace("RTImageFrameMVRadiationAcquisitionSequence", Tag(0x3002, 0x010b));
    public_tags.emplace("RTImageFrameRadiationAcquisitionSequence", Tag(0x3002, 0x010c));
    public_tags.emplace("ImagingSourcePositionSequence", Tag(0x3002, 0x010d));
    public_tags.emplace("ImageReceptorPositionSequence", Tag(0x3002, 0x010e));
    public_tags.emplace("DevicePositionToEquipmentMappingMatrix", Tag(0x3002, 0x010f));
    public_tags.emplace("DevicePositionParameterSequence", Tag(0x3002, 0x0110));
    public_tags.emplace("ImagingSourceLocationSpecificationType", Tag(0x3002, 0x0111));
    public_tags.emplace("ImagingDeviceLocationMatrixSequence", Tag(0x3002, 0x0112));
    public_tags.emplace("ImagingDeviceLocationParameterSequence", Tag(0x3002, 0x0113));
    public_tags.emplace("ImagingApertureSequence", Tag(0x3002, 0x0114));
    public_tags.emplace("ImagingApertureSpecificationType", Tag(0x3002, 0x0115));
    public_tags.emplace("NumberOfAcquisitionDevices", Tag(0x3002, 0x0116));
    public_tags.emplace("AcquisitionDeviceSequence", Tag(0x3002, 0x0117));
    public_tags.emplace("AcquisitionTaskSequence", Tag(0x3002, 0x0118));
    public_tags.emplace("AcquisitionTaskWorkitemCodeSequence", Tag(0x3002, 0x0119));
    public_tags.emplace("AcquisitionSubtaskSequence", Tag(0x3002, 0x011a));
    public_tags.emplace("SubtaskWorkitemCodeSequence", Tag(0x3002, 0x011b));
    public_tags.emplace("AcquisitionTaskIndex", Tag(0x3002, 0x011c));
    public_tags.emplace("AcquisitionSubtaskIndex", Tag(0x3002, 0x011d));
    public_tags.emplace("ReferencedBaselineParametersRTRadiationInstanceSequence", Tag(0x3002, 0x011e));
    public_tags.emplace("PositionAcquisitionTemplateIdentificationSequence", Tag(0x3002, 0x011f));
    public_tags.emplace("PositionAcquisitionTemplateID", Tag(0x3002, 0x0120));
    public_tags.emplace("PositionAcquisitionTemplateName", Tag(0x3002, 0x0121));
    public_tags.emplace("PositionAcquisitionTemplateCodeSequence", Tag(0x3002, 0x0122));
    public_tags.emplace("PositionAcquisitionTemplateDescription", Tag(0x3002, 0x0123));
    public_tags.emplace("AcquisitionTaskApplicabilitySequence", Tag(0x3002, 0x0124));
    public_tags.emplace("ProjectionImagingAcquisitionParameterSequence", Tag(0x3002, 0x0125));
    public_tags.emplace("CTImagingAcquisitionParameterSequence", Tag(0x3002, 0x0126));
    public_tags.emplace("KVImagingGenerationParametersSequence", Tag(0x3002, 0x0127));
    public_tags.emplace("MVImagingGenerationParametersSequence", Tag(0x3002, 0x0128));
    public_tags.emplace("AcquisitionSignalType", Tag(0x3002, 0x0129));
    public_tags.emplace("AcquisitionMethod", Tag(0x3002, 0x012a));
    public_tags.emplace("ScanStartPositionSequence", Tag(0x3002, 0x012b));
    public_tags.emplace("ScanStopPositionSequence", Tag(0x3002, 0x012c));
    public_tags.emplace("ImagingSourceToBeamModifierDefinitionPlaneDistance", Tag(0x3002, 0x012d));
    public_tags.emplace("ScanArcType", Tag(0x3002, 0x012e));
    public_tags.emplace("DetectorPositioningType", Tag(0x3002, 0x012f));
    public_tags.emplace("AdditionalRTAccessoryDeviceSequence", Tag(0x3002, 0x0130));
    public_tags.emplace("DeviceSpecificAcquisitionParameterSequence", Tag(0x3002, 0x0131));
    public_tags.emplace("ReferencedPositionReferenceInstanceSequence", Tag(0x3002, 0x0132));
    public_tags.emplace("EnergyDerivationCodeSequence", Tag(0x3002, 0x0133));
    public_tags.emplace("MaximumCumulativeMetersetExposure", Tag(0x3002, 0x0134));
    public_tags.emplace("AcquisitionInitiationSequence", Tag(0x3002, 0x0135));
}

}

}