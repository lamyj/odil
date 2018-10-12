/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0014
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0014

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const CADFileFormat(0x0014, 0x0023);
Tag const ComponentReferenceSystem(0x0014, 0x0024);
Tag const ComponentManufacturingProcedure(0x0014, 0x0025);
Tag const ComponentManufacturer(0x0014, 0x0028);
Tag const MaterialThickness(0x0014, 0x0030);
Tag const MaterialPipeDiameter(0x0014, 0x0032);
Tag const MaterialIsolationDiameter(0x0014, 0x0034);
Tag const MaterialGrade(0x0014, 0x0042);
Tag const MaterialPropertiesDescription(0x0014, 0x0044);
Tag const MaterialPropertiesFileFormatRetired(0x0014, 0x0045);
Tag const MaterialNotes(0x0014, 0x0046);
Tag const ComponentShape(0x0014, 0x0050);
Tag const CurvatureType(0x0014, 0x0052);
Tag const OuterDiameter(0x0014, 0x0054);
Tag const InnerDiameter(0x0014, 0x0056);
Tag const ComponentWelderIDs(0x0014, 0x0100);
Tag const SecondaryApprovalStatus(0x0014, 0x0101);
Tag const SecondaryReviewDate(0x0014, 0x0102);
Tag const SecondaryReviewTime(0x0014, 0x0103);
Tag const SecondaryReviewerName(0x0014, 0x0104);
Tag const RepairID(0x0014, 0x0105);
Tag const MultipleComponentApprovalSequence(0x0014, 0x0106);
Tag const OtherApprovalStatus(0x0014, 0x0107);
Tag const OtherSecondaryApprovalStatus(0x0014, 0x0108);
Tag const ActualEnvironmentalConditions(0x0014, 0x1010);
Tag const ExpiryDate(0x0014, 0x1020);
Tag const EnvironmentalConditions(0x0014, 0x1040);
Tag const EvaluatorSequence(0x0014, 0x2002);
Tag const EvaluatorNumber(0x0014, 0x2004);
Tag const EvaluatorName(0x0014, 0x2006);
Tag const EvaluationAttempt(0x0014, 0x2008);
Tag const IndicationSequence(0x0014, 0x2012);
Tag const IndicationNumber(0x0014, 0x2014);
Tag const IndicationLabel(0x0014, 0x2016);
Tag const IndicationDescription(0x0014, 0x2018);
Tag const IndicationType(0x0014, 0x201a);
Tag const IndicationDisposition(0x0014, 0x201c);
Tag const IndicationROISequence(0x0014, 0x201e);
Tag const IndicationPhysicalPropertySequence(0x0014, 0x2030);
Tag const PropertyLabel(0x0014, 0x2032);
Tag const CoordinateSystemNumberOfAxes(0x0014, 0x2202);
Tag const CoordinateSystemAxesSequence(0x0014, 0x2204);
Tag const CoordinateSystemAxisDescription(0x0014, 0x2206);
Tag const CoordinateSystemDataSetMapping(0x0014, 0x2208);
Tag const CoordinateSystemAxisNumber(0x0014, 0x220a);
Tag const CoordinateSystemAxisType(0x0014, 0x220c);
Tag const CoordinateSystemAxisUnits(0x0014, 0x220e);
Tag const CoordinateSystemAxisValues(0x0014, 0x2210);
Tag const CoordinateSystemTransformSequence(0x0014, 0x2220);
Tag const TransformDescription(0x0014, 0x2222);
Tag const TransformNumberOfAxes(0x0014, 0x2224);
Tag const TransformOrderOfAxes(0x0014, 0x2226);
Tag const TransformedAxisUnits(0x0014, 0x2228);
Tag const CoordinateSystemTransformRotationAndScaleMatrix(0x0014, 0x222a);
Tag const CoordinateSystemTransformTranslationMatrix(0x0014, 0x222c);
Tag const InternalDetectorFrameTime(0x0014, 0x3011);
Tag const NumberOfFramesIntegrated(0x0014, 0x3012);
Tag const DetectorTemperatureSequence(0x0014, 0x3020);
Tag const SensorName(0x0014, 0x3022);
Tag const HorizontalOffsetOfSensor(0x0014, 0x3024);
Tag const VerticalOffsetOfSensor(0x0014, 0x3026);
Tag const SensorTemperature(0x0014, 0x3028);
Tag const DarkCurrentSequence(0x0014, 0x3040);
Tag const DarkCurrentCounts(0x0014, 0x3050);
Tag const GainCorrectionReferenceSequence(0x0014, 0x3060);
Tag const AirCounts(0x0014, 0x3070);
Tag const KVUsedInGainCalibration(0x0014, 0x3071);
Tag const MAUsedInGainCalibration(0x0014, 0x3072);
Tag const NumberOfFramesUsedForIntegration(0x0014, 0x3073);
Tag const FilterMaterialUsedInGainCalibration(0x0014, 0x3074);
Tag const FilterThicknessUsedInGainCalibration(0x0014, 0x3075);
Tag const DateOfGainCalibration(0x0014, 0x3076);
Tag const TimeOfGainCalibration(0x0014, 0x3077);
Tag const BadPixelImage(0x0014, 0x3080);
Tag const CalibrationNotes(0x0014, 0x3099);
Tag const PulserEquipmentSequence(0x0014, 0x4002);
Tag const PulserType(0x0014, 0x4004);
Tag const PulserNotes(0x0014, 0x4006);
Tag const ReceiverEquipmentSequence(0x0014, 0x4008);
Tag const AmplifierType(0x0014, 0x400a);
Tag const ReceiverNotes(0x0014, 0x400c);
Tag const PreAmplifierEquipmentSequence(0x0014, 0x400e);
Tag const PreAmplifierNotes(0x0014, 0x400f);
Tag const TransmitTransducerSequence(0x0014, 0x4010);
Tag const ReceiveTransducerSequence(0x0014, 0x4011);
Tag const NumberOfElements(0x0014, 0x4012);
Tag const ElementShape(0x0014, 0x4013);
Tag const ElementDimensionA(0x0014, 0x4014);
Tag const ElementDimensionB(0x0014, 0x4015);
Tag const ElementPitchA(0x0014, 0x4016);
Tag const MeasuredBeamDimensionA(0x0014, 0x4017);
Tag const MeasuredBeamDimensionB(0x0014, 0x4018);
Tag const LocationOfMeasuredBeamDiameter(0x0014, 0x4019);
Tag const NominalFrequency(0x0014, 0x401a);
Tag const MeasuredCenterFrequency(0x0014, 0x401b);
Tag const MeasuredBandwidth(0x0014, 0x401c);
Tag const ElementPitchB(0x0014, 0x401d);
Tag const PulserSettingsSequence(0x0014, 0x4020);
Tag const PulseWidth(0x0014, 0x4022);
Tag const ExcitationFrequency(0x0014, 0x4024);
Tag const ModulationType(0x0014, 0x4026);
Tag const Damping(0x0014, 0x4028);
Tag const ReceiverSettingsSequence(0x0014, 0x4030);
Tag const AcquiredSoundpathLength(0x0014, 0x4031);
Tag const AcquisitionCompressionType(0x0014, 0x4032);
Tag const AcquisitionSampleSize(0x0014, 0x4033);
Tag const RectifierSmoothing(0x0014, 0x4034);
Tag const DACSequence(0x0014, 0x4035);
Tag const DACType(0x0014, 0x4036);
Tag const DACGainPoints(0x0014, 0x4038);
Tag const DACTimePoints(0x0014, 0x403a);
Tag const DACAmplitude(0x0014, 0x403c);
Tag const PreAmplifierSettingsSequence(0x0014, 0x4040);
Tag const TransmitTransducerSettingsSequence(0x0014, 0x4050);
Tag const ReceiveTransducerSettingsSequence(0x0014, 0x4051);
Tag const IncidentAngle(0x0014, 0x4052);
Tag const CouplingTechnique(0x0014, 0x4054);
Tag const CouplingMedium(0x0014, 0x4056);
Tag const CouplingVelocity(0x0014, 0x4057);
Tag const ProbeCenterLocationX(0x0014, 0x4058);
Tag const ProbeCenterLocationZ(0x0014, 0x4059);
Tag const SoundPathLength(0x0014, 0x405a);
Tag const DelayLawIdentifier(0x0014, 0x405c);
Tag const GateSettingsSequence(0x0014, 0x4060);
Tag const GateThreshold(0x0014, 0x4062);
Tag const VelocityOfSound(0x0014, 0x4064);
Tag const CalibrationSettingsSequence(0x0014, 0x4070);
Tag const CalibrationProcedure(0x0014, 0x4072);
Tag const ProcedureVersion(0x0014, 0x4074);
Tag const ProcedureCreationDate(0x0014, 0x4076);
Tag const ProcedureExpirationDate(0x0014, 0x4078);
Tag const ProcedureLastModifiedDate(0x0014, 0x407a);
Tag const CalibrationTime(0x0014, 0x407c);
Tag const CalibrationDate(0x0014, 0x407e);
Tag const ProbeDriveEquipmentSequence(0x0014, 0x4080);
Tag const DriveType(0x0014, 0x4081);
Tag const ProbeDriveNotes(0x0014, 0x4082);
Tag const DriveProbeSequence(0x0014, 0x4083);
Tag const ProbeInductance(0x0014, 0x4084);
Tag const ProbeResistance(0x0014, 0x4085);
Tag const ReceiveProbeSequence(0x0014, 0x4086);
Tag const ProbeDriveSettingsSequence(0x0014, 0x4087);
Tag const BridgeResistors(0x0014, 0x4088);
Tag const ProbeOrientationAngle(0x0014, 0x4089);
Tag const UserSelectedGainY(0x0014, 0x408b);
Tag const UserSelectedPhase(0x0014, 0x408c);
Tag const UserSelectedOffsetX(0x0014, 0x408d);
Tag const UserSelectedOffsetY(0x0014, 0x408e);
Tag const ChannelSettingsSequence(0x0014, 0x4091);
Tag const ChannelThreshold(0x0014, 0x4092);
Tag const ScannerSettingsSequence(0x0014, 0x409a);
Tag const ScanProcedure(0x0014, 0x409b);
Tag const TranslationRateX(0x0014, 0x409c);
Tag const TranslationRateY(0x0014, 0x409d);
Tag const ChannelOverlap(0x0014, 0x409f);
Tag const ImageQualityIndicatorType(0x0014, 0x40a0);
Tag const ImageQualityIndicatorMaterial(0x0014, 0x40a1);
Tag const ImageQualityIndicatorSize(0x0014, 0x40a2);
Tag const LINACEnergy(0x0014, 0x5002);
Tag const LINACOutput(0x0014, 0x5004);
Tag const ActiveAperture(0x0014, 0x5100);
Tag const TotalAperture(0x0014, 0x5101);
Tag const ApertureElevation(0x0014, 0x5102);
Tag const MainLobeAngle(0x0014, 0x5103);
Tag const MainRoofAngle(0x0014, 0x5104);
Tag const ConnectorType(0x0014, 0x5105);
Tag const WedgeModelNumber(0x0014, 0x5106);
Tag const WedgeAngleFloat(0x0014, 0x5107);
Tag const WedgeRoofAngle(0x0014, 0x5108);
Tag const WedgeElement1Position(0x0014, 0x5109);
Tag const WedgeMaterialVelocity(0x0014, 0x510a);
Tag const WedgeMaterial(0x0014, 0x510b);
Tag const WedgeOffsetZ(0x0014, 0x510c);
Tag const WedgeOriginOffsetX(0x0014, 0x510d);
Tag const WedgeTimeDelay(0x0014, 0x510e);
Tag const WedgeName(0x0014, 0x510f);
Tag const WedgeManufacturerName(0x0014, 0x5110);
Tag const WedgeDescription(0x0014, 0x5111);
Tag const NominalBeamAngle(0x0014, 0x5112);
Tag const WedgeOffsetX(0x0014, 0x5113);
Tag const WedgeOffsetY(0x0014, 0x5114);
Tag const WedgeTotalLength(0x0014, 0x5115);
Tag const WedgeInContactLength(0x0014, 0x5116);
Tag const WedgeFrontGap(0x0014, 0x5117);
Tag const WedgeTotalHeight(0x0014, 0x5118);
Tag const WedgeFrontHeight(0x0014, 0x5119);
Tag const WedgeRearHeight(0x0014, 0x511a);
Tag const WedgeTotalWidth(0x0014, 0x511b);
Tag const WedgeInContactWidth(0x0014, 0x511c);
Tag const WedgeChamferHeight(0x0014, 0x511d);
Tag const WedgeCurve(0x0014, 0x511e);
Tag const RadiusAlongWedge(0x0014, 0x511f);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0014