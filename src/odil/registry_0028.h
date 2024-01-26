/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0028
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0028

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const SamplesPerPixel(0x0028, 0x0002);
Tag const SamplesPerPixelUsed(0x0028, 0x0003);
Tag const PhotometricInterpretation(0x0028, 0x0004);
Tag const ImageDimensions(0x0028, 0x0005);
Tag const PlanarConfiguration(0x0028, 0x0006);
Tag const NumberOfFrames(0x0028, 0x0008);
Tag const FrameIncrementPointer(0x0028, 0x0009);
Tag const FrameDimensionPointer(0x0028, 0x000a);
Tag const Rows(0x0028, 0x0010);
Tag const Columns(0x0028, 0x0011);
Tag const Planes(0x0028, 0x0012);
Tag const UltrasoundColorDataPresent(0x0028, 0x0014);
Tag const PixelSpacing(0x0028, 0x0030);
Tag const ZoomFactor(0x0028, 0x0031);
Tag const ZoomCenter(0x0028, 0x0032);
Tag const PixelAspectRatio(0x0028, 0x0034);
Tag const ImageFormat(0x0028, 0x0040);
Tag const ManipulatedImage(0x0028, 0x0050);
Tag const CorrectedImage(0x0028, 0x0051);
Tag const CompressionRecognitionCode(0x0028, 0x005f);
Tag const CompressionCode(0x0028, 0x0060);
Tag const CompressionOriginator(0x0028, 0x0061);
Tag const CompressionLabel(0x0028, 0x0062);
Tag const CompressionDescription(0x0028, 0x0063);
Tag const CompressionSequence(0x0028, 0x0065);
Tag const CompressionStepPointers(0x0028, 0x0066);
Tag const RepeatInterval(0x0028, 0x0068);
Tag const BitsGrouped(0x0028, 0x0069);
Tag const PerimeterTable(0x0028, 0x0070);
Tag const PerimeterValue(0x0028, 0x0071);
Tag const PredictorRows(0x0028, 0x0080);
Tag const PredictorColumns(0x0028, 0x0081);
Tag const PredictorConstants(0x0028, 0x0082);
Tag const BlockedPixels(0x0028, 0x0090);
Tag const BlockRows(0x0028, 0x0091);
Tag const BlockColumns(0x0028, 0x0092);
Tag const RowOverlap(0x0028, 0x0093);
Tag const ColumnOverlap(0x0028, 0x0094);
Tag const BitsAllocated(0x0028, 0x0100);
Tag const BitsStored(0x0028, 0x0101);
Tag const HighBit(0x0028, 0x0102);
Tag const PixelRepresentation(0x0028, 0x0103);
Tag const SmallestValidPixelValue(0x0028, 0x0104);
Tag const LargestValidPixelValue(0x0028, 0x0105);
Tag const SmallestImagePixelValue(0x0028, 0x0106);
Tag const LargestImagePixelValue(0x0028, 0x0107);
Tag const SmallestPixelValueInSeries(0x0028, 0x0108);
Tag const LargestPixelValueInSeries(0x0028, 0x0109);
Tag const SmallestImagePixelValueInPlane(0x0028, 0x0110);
Tag const LargestImagePixelValueInPlane(0x0028, 0x0111);
Tag const PixelPaddingValue(0x0028, 0x0120);
Tag const PixelPaddingRangeLimit(0x0028, 0x0121);
Tag const FloatPixelPaddingValue(0x0028, 0x0122);
Tag const DoubleFloatPixelPaddingValue(0x0028, 0x0123);
Tag const FloatPixelPaddingRangeLimit(0x0028, 0x0124);
Tag const DoubleFloatPixelPaddingRangeLimit(0x0028, 0x0125);
Tag const ImageLocation(0x0028, 0x0200);
Tag const QualityControlImage(0x0028, 0x0300);
Tag const BurnedInAnnotation(0x0028, 0x0301);
Tag const RecognizableVisualFeatures(0x0028, 0x0302);
Tag const LongitudinalTemporalInformationModified(0x0028, 0x0303);
Tag const ReferencedColorPaletteInstanceUID(0x0028, 0x0304);
Tag const TransformLabel(0x0028, 0x0400);
Tag const TransformVersionNumber(0x0028, 0x0401);
Tag const NumberOfTransformSteps(0x0028, 0x0402);
Tag const SequenceOfCompressedData(0x0028, 0x0403);
Tag const DetailsOfCoefficients(0x0028, 0x0404);
Tag const DCTLabel(0x0028, 0x0700);
Tag const DataBlockDescription(0x0028, 0x0701);
Tag const DataBlock(0x0028, 0x0702);
Tag const NormalizationFactorFormat(0x0028, 0x0710);
Tag const ZonalMapNumberFormat(0x0028, 0x0720);
Tag const ZonalMapLocation(0x0028, 0x0721);
Tag const ZonalMapFormat(0x0028, 0x0722);
Tag const AdaptiveMapFormat(0x0028, 0x0730);
Tag const CodeNumberFormat(0x0028, 0x0740);
Tag const PixelSpacingCalibrationType(0x0028, 0x0a02);
Tag const PixelSpacingCalibrationDescription(0x0028, 0x0a04);
Tag const PixelIntensityRelationship(0x0028, 0x1040);
Tag const PixelIntensityRelationshipSign(0x0028, 0x1041);
Tag const WindowCenter(0x0028, 0x1050);
Tag const WindowWidth(0x0028, 0x1051);
Tag const RescaleIntercept(0x0028, 0x1052);
Tag const RescaleSlope(0x0028, 0x1053);
Tag const RescaleType(0x0028, 0x1054);
Tag const WindowCenterWidthExplanation(0x0028, 0x1055);
Tag const VOILUTFunction(0x0028, 0x1056);
Tag const GrayScale(0x0028, 0x1080);
Tag const RecommendedViewingMode(0x0028, 0x1090);
Tag const GrayLookupTableDescriptor(0x0028, 0x1100);
Tag const RedPaletteColorLookupTableDescriptor(0x0028, 0x1101);
Tag const GreenPaletteColorLookupTableDescriptor(0x0028, 0x1102);
Tag const BluePaletteColorLookupTableDescriptor(0x0028, 0x1103);
Tag const AlphaPaletteColorLookupTableDescriptor(0x0028, 0x1104);
Tag const LargeRedPaletteColorLookupTableDescriptor(0x0028, 0x1111);
Tag const LargeGreenPaletteColorLookupTableDescriptor(0x0028, 0x1112);
Tag const LargeBluePaletteColorLookupTableDescriptor(0x0028, 0x1113);
Tag const PaletteColorLookupTableUID(0x0028, 0x1199);
Tag const GrayLookupTableData(0x0028, 0x1200);
Tag const RedPaletteColorLookupTableData(0x0028, 0x1201);
Tag const GreenPaletteColorLookupTableData(0x0028, 0x1202);
Tag const BluePaletteColorLookupTableData(0x0028, 0x1203);
Tag const AlphaPaletteColorLookupTableData(0x0028, 0x1204);
Tag const LargeRedPaletteColorLookupTableData(0x0028, 0x1211);
Tag const LargeGreenPaletteColorLookupTableData(0x0028, 0x1212);
Tag const LargeBluePaletteColorLookupTableData(0x0028, 0x1213);
Tag const LargePaletteColorLookupTableUID(0x0028, 0x1214);
Tag const SegmentedRedPaletteColorLookupTableData(0x0028, 0x1221);
Tag const SegmentedGreenPaletteColorLookupTableData(0x0028, 0x1222);
Tag const SegmentedBluePaletteColorLookupTableData(0x0028, 0x1223);
Tag const SegmentedAlphaPaletteColorLookupTableData(0x0028, 0x1224);
Tag const StoredValueColorRangeSequence(0x0028, 0x1230);
Tag const MinimumStoredValueMapped(0x0028, 0x1231);
Tag const MaximumStoredValueMapped(0x0028, 0x1232);
Tag const BreastImplantPresent(0x0028, 0x1300);
Tag const PartialView(0x0028, 0x1350);
Tag const PartialViewDescription(0x0028, 0x1351);
Tag const PartialViewCodeSequence(0x0028, 0x1352);
Tag const SpatialLocationsPreserved(0x0028, 0x135a);
Tag const DataFrameAssignmentSequence(0x0028, 0x1401);
Tag const DataPathAssignment(0x0028, 0x1402);
Tag const BitsMappedToColorLookupTable(0x0028, 0x1403);
Tag const BlendingLUT1Sequence(0x0028, 0x1404);
Tag const BlendingLUT1TransferFunction(0x0028, 0x1405);
Tag const BlendingWeightConstant(0x0028, 0x1406);
Tag const BlendingLookupTableDescriptor(0x0028, 0x1407);
Tag const BlendingLookupTableData(0x0028, 0x1408);
Tag const EnhancedPaletteColorLookupTableSequence(0x0028, 0x140b);
Tag const BlendingLUT2Sequence(0x0028, 0x140c);
Tag const BlendingLUT2TransferFunction(0x0028, 0x140d);
Tag const DataPathID(0x0028, 0x140e);
Tag const RGBLUTTransferFunction(0x0028, 0x140f);
Tag const AlphaLUTTransferFunction(0x0028, 0x1410);
Tag const ICCProfile(0x0028, 0x2000);
Tag const ColorSpace(0x0028, 0x2002);
Tag const LossyImageCompression(0x0028, 0x2110);
Tag const LossyImageCompressionRatio(0x0028, 0x2112);
Tag const LossyImageCompressionMethod(0x0028, 0x2114);
Tag const ModalityLUTSequence(0x0028, 0x3000);
Tag const VariableModalityLUTSequence(0x0028, 0x3001);
Tag const LUTDescriptor(0x0028, 0x3002);
Tag const LUTExplanation(0x0028, 0x3003);
Tag const ModalityLUTType(0x0028, 0x3004);
Tag const LUTData(0x0028, 0x3006);
Tag const VOILUTSequence(0x0028, 0x3010);
Tag const SoftcopyVOILUTSequence(0x0028, 0x3110);
Tag const ImagePresentationComments(0x0028, 0x4000);
Tag const BiPlaneAcquisitionSequence(0x0028, 0x5000);
Tag const RepresentativeFrameNumber(0x0028, 0x6010);
Tag const FrameNumbersOfInterest(0x0028, 0x6020);
Tag const FrameOfInterestDescription(0x0028, 0x6022);
Tag const FrameOfInterestType(0x0028, 0x6023);
Tag const MaskPointers(0x0028, 0x6030);
Tag const RWavePointer(0x0028, 0x6040);
Tag const MaskSubtractionSequence(0x0028, 0x6100);
Tag const MaskOperation(0x0028, 0x6101);
Tag const ApplicableFrameRange(0x0028, 0x6102);
Tag const MaskFrameNumbers(0x0028, 0x6110);
Tag const ContrastFrameAveraging(0x0028, 0x6112);
Tag const MaskSubPixelShift(0x0028, 0x6114);
Tag const TIDOffset(0x0028, 0x6120);
Tag const MaskOperationExplanation(0x0028, 0x6190);
Tag const EquipmentAdministratorSequence(0x0028, 0x7000);
Tag const NumberOfDisplaySubsystems(0x0028, 0x7001);
Tag const CurrentConfigurationID(0x0028, 0x7002);
Tag const DisplaySubsystemID(0x0028, 0x7003);
Tag const DisplaySubsystemName(0x0028, 0x7004);
Tag const DisplaySubsystemDescription(0x0028, 0x7005);
Tag const SystemStatus(0x0028, 0x7006);
Tag const SystemStatusComment(0x0028, 0x7007);
Tag const TargetLuminanceCharacteristicsSequence(0x0028, 0x7008);
Tag const LuminanceCharacteristicsID(0x0028, 0x7009);
Tag const DisplaySubsystemConfigurationSequence(0x0028, 0x700a);
Tag const ConfigurationID(0x0028, 0x700b);
Tag const ConfigurationName(0x0028, 0x700c);
Tag const ConfigurationDescription(0x0028, 0x700d);
Tag const ReferencedTargetLuminanceCharacteristicsID(0x0028, 0x700e);
Tag const QAResultsSequence(0x0028, 0x700f);
Tag const DisplaySubsystemQAResultsSequence(0x0028, 0x7010);
Tag const ConfigurationQAResultsSequence(0x0028, 0x7011);
Tag const MeasurementEquipmentSequence(0x0028, 0x7012);
Tag const MeasurementFunctions(0x0028, 0x7013);
Tag const MeasurementEquipmentType(0x0028, 0x7014);
Tag const VisualEvaluationResultSequence(0x0028, 0x7015);
Tag const DisplayCalibrationResultSequence(0x0028, 0x7016);
Tag const DDLValue(0x0028, 0x7017);
Tag const CIExyWhitePoint(0x0028, 0x7018);
Tag const DisplayFunctionType(0x0028, 0x7019);
Tag const GammaValue(0x0028, 0x701a);
Tag const NumberOfLuminancePoints(0x0028, 0x701b);
Tag const LuminanceResponseSequence(0x0028, 0x701c);
Tag const TargetMinimumLuminance(0x0028, 0x701d);
Tag const TargetMaximumLuminance(0x0028, 0x701e);
Tag const LuminanceValue(0x0028, 0x701f);
Tag const LuminanceResponseDescription(0x0028, 0x7020);
Tag const WhitePointFlag(0x0028, 0x7021);
Tag const DisplayDeviceTypeCodeSequence(0x0028, 0x7022);
Tag const DisplaySubsystemSequence(0x0028, 0x7023);
Tag const LuminanceResultSequence(0x0028, 0x7024);
Tag const AmbientLightValueSource(0x0028, 0x7025);
Tag const MeasuredCharacteristics(0x0028, 0x7026);
Tag const LuminanceUniformityResultSequence(0x0028, 0x7027);
Tag const VisualEvaluationTestSequence(0x0028, 0x7028);
Tag const TestResult(0x0028, 0x7029);
Tag const TestResultComment(0x0028, 0x702a);
Tag const TestImageValidation(0x0028, 0x702b);
Tag const TestPatternCodeSequence(0x0028, 0x702c);
Tag const MeasurementPatternCodeSequence(0x0028, 0x702d);
Tag const VisualEvaluationMethodCodeSequence(0x0028, 0x702e);
Tag const PixelDataProviderURL(0x0028, 0x7fe0);
Tag const DataPointRows(0x0028, 0x9001);
Tag const DataPointColumns(0x0028, 0x9002);
Tag const SignalDomainColumns(0x0028, 0x9003);
Tag const LargestMonochromePixelValue(0x0028, 0x9099);
Tag const DataRepresentation(0x0028, 0x9108);
Tag const PixelMeasuresSequence(0x0028, 0x9110);
Tag const FrameVOILUTSequence(0x0028, 0x9132);
Tag const PixelValueTransformationSequence(0x0028, 0x9145);
Tag const SignalDomainRows(0x0028, 0x9235);
Tag const DisplayFilterPercentage(0x0028, 0x9411);
Tag const FramePixelShiftSequence(0x0028, 0x9415);
Tag const SubtractionItemID(0x0028, 0x9416);
Tag const PixelIntensityRelationshipLUTSequence(0x0028, 0x9422);
Tag const FramePixelDataPropertiesSequence(0x0028, 0x9443);
Tag const GeometricalProperties(0x0028, 0x9444);
Tag const GeometricMaximumDistortion(0x0028, 0x9445);
Tag const ImageProcessingApplied(0x0028, 0x9446);
Tag const MaskSelectionMode(0x0028, 0x9454);
Tag const LUTFunction(0x0028, 0x9474);
Tag const MaskVisibilityPercentage(0x0028, 0x9478);
Tag const PixelShiftSequence(0x0028, 0x9501);
Tag const RegionPixelShiftSequence(0x0028, 0x9502);
Tag const VerticesOfTheRegion(0x0028, 0x9503);
Tag const MultiFramePresentationSequence(0x0028, 0x9505);
Tag const PixelShiftFrameRange(0x0028, 0x9506);
Tag const LUTFrameRange(0x0028, 0x9507);
Tag const ImageToEquipmentMappingMatrix(0x0028, 0x9520);
Tag const EquipmentCoordinateSystemIdentification(0x0028, 0x9537);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0028