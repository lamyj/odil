/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3002
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3002

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const RTImageLabel(0x3002, 0x0002);
Tag const RTImageName(0x3002, 0x0003);
Tag const RTImageDescription(0x3002, 0x0004);
Tag const ReportedValuesOrigin(0x3002, 0x000a);
Tag const RTImagePlane(0x3002, 0x000c);
Tag const XRayImageReceptorTranslation(0x3002, 0x000d);
Tag const XRayImageReceptorAngle(0x3002, 0x000e);
Tag const RTImageOrientation(0x3002, 0x0010);
Tag const ImagePlanePixelSpacing(0x3002, 0x0011);
Tag const RTImagePosition(0x3002, 0x0012);
Tag const RadiationMachineName(0x3002, 0x0020);
Tag const RadiationMachineSAD(0x3002, 0x0022);
Tag const RadiationMachineSSD(0x3002, 0x0024);
Tag const RTImageSID(0x3002, 0x0026);
Tag const SourceToReferenceObjectDistance(0x3002, 0x0028);
Tag const FractionNumber(0x3002, 0x0029);
Tag const ExposureSequence(0x3002, 0x0030);
Tag const MetersetExposure(0x3002, 0x0032);
Tag const DiaphragmPosition(0x3002, 0x0034);
Tag const FluenceMapSequence(0x3002, 0x0040);
Tag const FluenceDataSource(0x3002, 0x0041);
Tag const FluenceDataScale(0x3002, 0x0042);
Tag const PrimaryFluenceModeSequence(0x3002, 0x0050);
Tag const FluenceMode(0x3002, 0x0051);
Tag const FluenceModeID(0x3002, 0x0052);
Tag const SelectedFrameNumber(0x3002, 0x0100);
Tag const SelectedFrameFunctionalGroupsSequence(0x3002, 0x0101);
Tag const RTImageFrameGeneralContentSequence(0x3002, 0x0102);
Tag const RTImageFrameContextSequence(0x3002, 0x0103);
Tag const RTImageScopeSequence(0x3002, 0x0104);
Tag const BeamModifierCoordinatesPresenceFlag(0x3002, 0x0105);
Tag const StartCumulativeMeterset(0x3002, 0x0106);
Tag const StopCumulativeMeterset(0x3002, 0x0107);
Tag const RTAcquisitionPatientPositionSequence(0x3002, 0x0108);
Tag const RTImageFrameImagingDevicePositionSequence(0x3002, 0x0109);
Tag const RTImageFramekVRadiationAcquisitionSequence(0x3002, 0x010a);
Tag const RTImageFrameMVRadiationAcquisitionSequence(0x3002, 0x010b);
Tag const RTImageFrameRadiationAcquisitionSequence(0x3002, 0x010c);
Tag const ImagingSourcePositionSequence(0x3002, 0x010d);
Tag const ImageReceptorPositionSequence(0x3002, 0x010e);
Tag const DevicePositionToEquipmentMappingMatrix(0x3002, 0x010f);
Tag const DevicePositionParameterSequence(0x3002, 0x0110);
Tag const ImagingSourceLocationSpecificationType(0x3002, 0x0111);
Tag const ImagingDeviceLocationMatrixSequence(0x3002, 0x0112);
Tag const ImagingDeviceLocationParameterSequence(0x3002, 0x0113);
Tag const ImagingApertureSequence(0x3002, 0x0114);
Tag const ImagingApertureSpecificationType(0x3002, 0x0115);
Tag const NumberOfAcquisitionDevices(0x3002, 0x0116);
Tag const AcquisitionDeviceSequence(0x3002, 0x0117);
Tag const AcquisitionTaskSequence(0x3002, 0x0118);
Tag const AcquisitionTaskWorkitemCodeSequence(0x3002, 0x0119);
Tag const AcquisitionSubtaskSequence(0x3002, 0x011a);
Tag const SubtaskWorkitemCodeSequence(0x3002, 0x011b);
Tag const AcquisitionTaskIndex(0x3002, 0x011c);
Tag const AcquisitionSubtaskIndex(0x3002, 0x011d);
Tag const ReferencedBaselineParametersRTRadiationInstanceSequence(0x3002, 0x011e);
Tag const PositionAcquisitionTemplateIdentificationSequence(0x3002, 0x011f);
Tag const PositionAcquisitionTemplateID(0x3002, 0x0120);
Tag const PositionAcquisitionTemplateName(0x3002, 0x0121);
Tag const PositionAcquisitionTemplateCodeSequence(0x3002, 0x0122);
Tag const PositionAcquisitionTemplateDescription(0x3002, 0x0123);
Tag const AcquisitionTaskApplicabilitySequence(0x3002, 0x0124);
Tag const ProjectionImagingAcquisitionParameterSequence(0x3002, 0x0125);
Tag const CTImagingAcquisitionParameterSequence(0x3002, 0x0126);
Tag const KVImagingGenerationParametersSequence(0x3002, 0x0127);
Tag const MVImagingGenerationParametersSequence(0x3002, 0x0128);
Tag const AcquisitionSignalType(0x3002, 0x0129);
Tag const AcquisitionMethod(0x3002, 0x012a);
Tag const ScanStartPositionSequence(0x3002, 0x012b);
Tag const ScanStopPositionSequence(0x3002, 0x012c);
Tag const ImagingSourceToBeamModifierDefinitionPlaneDistance(0x3002, 0x012d);
Tag const ScanArcType(0x3002, 0x012e);
Tag const DetectorPositioningType(0x3002, 0x012f);
Tag const AdditionalRTAccessoryDeviceSequence(0x3002, 0x0130);
Tag const DeviceSpecificAcquisitionParameterSequence(0x3002, 0x0131);
Tag const ReferencedPositionReferenceInstanceSequence(0x3002, 0x0132);
Tag const EnergyDerivationCodeSequence(0x3002, 0x0133);
Tag const MaximumCumulativeMetersetExposure(0x3002, 0x0134);
Tag const AcquisitionInitiationSequence(0x3002, 0x0135);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3002