/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0022
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0022

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const LightPathFilterPassThroughWavelength(0x0022, 0x0001);
Tag const LightPathFilterPassBand(0x0022, 0x0002);
Tag const ImagePathFilterPassThroughWavelength(0x0022, 0x0003);
Tag const ImagePathFilterPassBand(0x0022, 0x0004);
Tag const PatientEyeMovementCommanded(0x0022, 0x0005);
Tag const PatientEyeMovementCommandCodeSequence(0x0022, 0x0006);
Tag const SphericalLensPower(0x0022, 0x0007);
Tag const CylinderLensPower(0x0022, 0x0008);
Tag const CylinderAxis(0x0022, 0x0009);
Tag const EmmetropicMagnification(0x0022, 0x000a);
Tag const IntraOcularPressure(0x0022, 0x000b);
Tag const HorizontalFieldOfView(0x0022, 0x000c);
Tag const PupilDilated(0x0022, 0x000d);
Tag const DegreeOfDilation(0x0022, 0x000e);
Tag const StereoBaselineAngle(0x0022, 0x0010);
Tag const StereoBaselineDisplacement(0x0022, 0x0011);
Tag const StereoHorizontalPixelOffset(0x0022, 0x0012);
Tag const StereoVerticalPixelOffset(0x0022, 0x0013);
Tag const StereoRotation(0x0022, 0x0014);
Tag const AcquisitionDeviceTypeCodeSequence(0x0022, 0x0015);
Tag const IlluminationTypeCodeSequence(0x0022, 0x0016);
Tag const LightPathFilterTypeStackCodeSequence(0x0022, 0x0017);
Tag const ImagePathFilterTypeStackCodeSequence(0x0022, 0x0018);
Tag const LensesCodeSequence(0x0022, 0x0019);
Tag const ChannelDescriptionCodeSequence(0x0022, 0x001a);
Tag const RefractiveStateSequence(0x0022, 0x001b);
Tag const MydriaticAgentCodeSequence(0x0022, 0x001c);
Tag const RelativeImagePositionCodeSequence(0x0022, 0x001d);
Tag const CameraAngleOfView(0x0022, 0x001e);
Tag const StereoPairsSequence(0x0022, 0x0020);
Tag const LeftImageSequence(0x0022, 0x0021);
Tag const RightImageSequence(0x0022, 0x0022);
Tag const StereoPairsPresent(0x0022, 0x0028);
Tag const AxialLengthOfTheEye(0x0022, 0x0030);
Tag const OphthalmicFrameLocationSequence(0x0022, 0x0031);
Tag const ReferenceCoordinates(0x0022, 0x0032);
Tag const DepthSpatialResolution(0x0022, 0x0035);
Tag const MaximumDepthDistortion(0x0022, 0x0036);
Tag const AlongScanSpatialResolution(0x0022, 0x0037);
Tag const MaximumAlongScanDistortion(0x0022, 0x0038);
Tag const OphthalmicImageOrientation(0x0022, 0x0039);
Tag const DepthOfTransverseImage(0x0022, 0x0041);
Tag const MydriaticAgentConcentrationUnitsSequence(0x0022, 0x0042);
Tag const AcrossScanSpatialResolution(0x0022, 0x0048);
Tag const MaximumAcrossScanDistortion(0x0022, 0x0049);
Tag const MydriaticAgentConcentration(0x0022, 0x004e);
Tag const IlluminationWaveLength(0x0022, 0x0055);
Tag const IlluminationPower(0x0022, 0x0056);
Tag const IlluminationBandwidth(0x0022, 0x0057);
Tag const MydriaticAgentSequence(0x0022, 0x0058);
Tag const OphthalmicAxialMeasurementsRightEyeSequence(0x0022, 0x1007);
Tag const OphthalmicAxialMeasurementsLeftEyeSequence(0x0022, 0x1008);
Tag const OphthalmicAxialMeasurementsDeviceType(0x0022, 0x1009);
Tag const OphthalmicAxialLengthMeasurementsType(0x0022, 0x1010);
Tag const OphthalmicAxialLengthSequence(0x0022, 0x1012);
Tag const OphthalmicAxialLength(0x0022, 0x1019);
Tag const LensStatusCodeSequence(0x0022, 0x1024);
Tag const VitreousStatusCodeSequence(0x0022, 0x1025);
Tag const IOLFormulaCodeSequence(0x0022, 0x1028);
Tag const IOLFormulaDetail(0x0022, 0x1029);
Tag const KeratometerIndex(0x0022, 0x1033);
Tag const SourceOfOphthalmicAxialLengthCodeSequence(0x0022, 0x1035);
Tag const TargetRefraction(0x0022, 0x1037);
Tag const RefractiveProcedureOccurred(0x0022, 0x1039);
Tag const RefractiveSurgeryTypeCodeSequence(0x0022, 0x1040);
Tag const OphthalmicUltrasoundMethodCodeSequence(0x0022, 0x1044);
Tag const OphthalmicAxialLengthMeasurementsSequence(0x0022, 0x1050);
Tag const IOLPower(0x0022, 0x1053);
Tag const PredictedRefractiveError(0x0022, 0x1054);
Tag const OphthalmicAxialLengthVelocity(0x0022, 0x1059);
Tag const LensStatusDescription(0x0022, 0x1065);
Tag const VitreousStatusDescription(0x0022, 0x1066);
Tag const IOLPowerSequence(0x0022, 0x1090);
Tag const LensConstantSequence(0x0022, 0x1092);
Tag const IOLManufacturer(0x0022, 0x1093);
Tag const LensConstantDescription(0x0022, 0x1094);
Tag const ImplantName(0x0022, 0x1095);
Tag const KeratometryMeasurementTypeCodeSequence(0x0022, 0x1096);
Tag const ImplantPartNumber(0x0022, 0x1097);
Tag const ReferencedOphthalmicAxialMeasurementsSequence(0x0022, 0x1100);
Tag const OphthalmicAxialLengthMeasurementsSegmentNameCodeSequence(0x0022, 0x1101);
Tag const RefractiveErrorBeforeRefractiveSurgeryCodeSequence(0x0022, 0x1103);
Tag const IOLPowerForExactEmmetropia(0x0022, 0x1121);
Tag const IOLPowerForExactTargetRefraction(0x0022, 0x1122);
Tag const AnteriorChamberDepthDefinitionCodeSequence(0x0022, 0x1125);
Tag const LensThicknessSequence(0x0022, 0x1127);
Tag const AnteriorChamberDepthSequence(0x0022, 0x1128);
Tag const LensThickness(0x0022, 0x1130);
Tag const AnteriorChamberDepth(0x0022, 0x1131);
Tag const SourceOfLensThicknessDataCodeSequence(0x0022, 0x1132);
Tag const SourceOfAnteriorChamberDepthDataCodeSequence(0x0022, 0x1133);
Tag const SourceOfRefractiveMeasurementsSequence(0x0022, 0x1134);
Tag const SourceOfRefractiveMeasurementsCodeSequence(0x0022, 0x1135);
Tag const OphthalmicAxialLengthMeasurementModified(0x0022, 0x1140);
Tag const OphthalmicAxialLengthDataSourceCodeSequence(0x0022, 0x1150);
Tag const OphthalmicAxialLengthAcquisitionMethodCodeSequence(0x0022, 0x1153);
Tag const SignalToNoiseRatio(0x0022, 0x1155);
Tag const OphthalmicAxialLengthDataSourceDescription(0x0022, 0x1159);
Tag const OphthalmicAxialLengthMeasurementsTotalLengthSequence(0x0022, 0x1210);
Tag const OphthalmicAxialLengthMeasurementsSegmentalLengthSequence(0x0022, 0x1211);
Tag const OphthalmicAxialLengthMeasurementsLengthSummationSequence(0x0022, 0x1212);
Tag const UltrasoundOphthalmicAxialLengthMeasurementsSequence(0x0022, 0x1220);
Tag const OpticalOphthalmicAxialLengthMeasurementsSequence(0x0022, 0x1225);
Tag const UltrasoundSelectedOphthalmicAxialLengthSequence(0x0022, 0x1230);
Tag const OphthalmicAxialLengthSelectionMethodCodeSequence(0x0022, 0x1250);
Tag const OpticalSelectedOphthalmicAxialLengthSequence(0x0022, 0x1255);
Tag const SelectedSegmentalOphthalmicAxialLengthSequence(0x0022, 0x1257);
Tag const SelectedTotalOphthalmicAxialLengthSequence(0x0022, 0x1260);
Tag const OphthalmicAxialLengthQualityMetricSequence(0x0022, 0x1262);
Tag const OphthalmicAxialLengthQualityMetricTypeCodeSequence(0x0022, 0x1265);
Tag const OphthalmicAxialLengthQualityMetricTypeDescription(0x0022, 0x1273);
Tag const IntraocularLensCalculationsRightEyeSequence(0x0022, 0x1300);
Tag const IntraocularLensCalculationsLeftEyeSequence(0x0022, 0x1310);
Tag const ReferencedOphthalmicAxialLengthMeasurementQCImageSequence(0x0022, 0x1330);
Tag const OphthalmicMappingDeviceType(0x0022, 0x1415);
Tag const AcquisitionMethodCodeSequence(0x0022, 0x1420);
Tag const AcquisitionMethodAlgorithmSequence(0x0022, 0x1423);
Tag const OphthalmicThicknessMapTypeCodeSequence(0x0022, 0x1436);
Tag const OphthalmicThicknessMappingNormalsSequence(0x0022, 0x1443);
Tag const RetinalThicknessDefinitionCodeSequence(0x0022, 0x1445);
Tag const PixelValueMappingToCodedConceptSequence(0x0022, 0x1450);
Tag const MappedPixelValue(0x0022, 0x1452);
Tag const PixelValueMappingExplanation(0x0022, 0x1454);
Tag const OphthalmicThicknessMapQualityThresholdSequence(0x0022, 0x1458);
Tag const OphthalmicThicknessMapThresholdQualityRating(0x0022, 0x1460);
Tag const AnatomicStructureReferencePoint(0x0022, 0x1463);
Tag const RegistrationToLocalizerSequence(0x0022, 0x1465);
Tag const RegisteredLocalizerUnits(0x0022, 0x1466);
Tag const RegisteredLocalizerTopLeftHandCorner(0x0022, 0x1467);
Tag const RegisteredLocalizerBottomRightHandCorner(0x0022, 0x1468);
Tag const OphthalmicThicknessMapQualityRatingSequence(0x0022, 0x1470);
Tag const RelevantOPTAttributesSequence(0x0022, 0x1472);
Tag const TransformationMethodCodeSequence(0x0022, 0x1512);
Tag const TransformationAlgorithmSequence(0x0022, 0x1513);
Tag const OphthalmicAxialLengthMethod(0x0022, 0x1515);
Tag const OphthalmicFOV(0x0022, 0x1517);
Tag const TwoDimensionalToThreeDimensionalMapSequence(0x0022, 0x1518);
Tag const WideFieldOphthalmicPhotographyQualityRatingSequence(0x0022, 0x1525);
Tag const WideFieldOphthalmicPhotographyQualityThresholdSequence(0x0022, 0x1526);
Tag const WideFieldOphthalmicPhotographyThresholdQualityRating(0x0022, 0x1527);
Tag const XCoordinatesCenterPixelViewAngle(0x0022, 0x1528);
Tag const YCoordinatesCenterPixelViewAngle(0x0022, 0x1529);
Tag const NumberOfMapPoints(0x0022, 0x1530);
Tag const TwoDimensionalToThreeDimensionalMapData(0x0022, 0x1531);
Tag const DerivationAlgorithmSequence(0x0022, 0x1612);
Tag const OphthalmicImageTypeCodeSequence(0x0022, 0x1615);
Tag const OphthalmicImageTypeDescription(0x0022, 0x1616);
Tag const ScanPatternTypeCodeSequence(0x0022, 0x1618);
Tag const ReferencedSurfaceMeshIdentificationSequence(0x0022, 0x1620);
Tag const OphthalmicVolumetricPropertiesFlag(0x0022, 0x1622);
Tag const OphthalmicAnatomicReferencePointXCoordinate(0x0022, 0x1624);
Tag const OphthalmicAnatomicReferencePointYCoordinate(0x0022, 0x1626);
Tag const OphthalmicEnFaceImageQualityRatingSequence(0x0022, 0x1628);
Tag const QualityThreshold(0x0022, 0x1630);
Tag const OCTBscanAnalysisAcquisitionParametersSequence(0x0022, 0x1640);
Tag const NumberofBscansPerFrame(0x0022, 0x1642);
Tag const BscanSlabThickness(0x0022, 0x1643);
Tag const DistanceBetweenBscanSlabs(0x0022, 0x1644);
Tag const BscanCycleTime(0x0022, 0x1645);
Tag const BscanCycleTimeVector(0x0022, 0x1646);
Tag const AscanRate(0x0022, 0x1649);
Tag const BscanRate(0x0022, 0x1650);
Tag const SurfaceMeshZPixelOffset(0x0022, 0x1658);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0022