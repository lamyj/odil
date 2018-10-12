/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0070
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0070

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const GraphicAnnotationSequence(0x0070, 0x0001);
Tag const GraphicLayer(0x0070, 0x0002);
Tag const BoundingBoxAnnotationUnits(0x0070, 0x0003);
Tag const AnchorPointAnnotationUnits(0x0070, 0x0004);
Tag const GraphicAnnotationUnits(0x0070, 0x0005);
Tag const UnformattedTextValue(0x0070, 0x0006);
Tag const TextObjectSequence(0x0070, 0x0008);
Tag const GraphicObjectSequence(0x0070, 0x0009);
Tag const BoundingBoxTopLeftHandCorner(0x0070, 0x0010);
Tag const BoundingBoxBottomRightHandCorner(0x0070, 0x0011);
Tag const BoundingBoxTextHorizontalJustification(0x0070, 0x0012);
Tag const AnchorPoint(0x0070, 0x0014);
Tag const AnchorPointVisibility(0x0070, 0x0015);
Tag const GraphicDimensions(0x0070, 0x0020);
Tag const NumberOfGraphicPoints(0x0070, 0x0021);
Tag const GraphicData(0x0070, 0x0022);
Tag const GraphicType(0x0070, 0x0023);
Tag const GraphicFilled(0x0070, 0x0024);
Tag const ImageRotationRetired(0x0070, 0x0040);
Tag const ImageHorizontalFlip(0x0070, 0x0041);
Tag const ImageRotation(0x0070, 0x0042);
Tag const DisplayedAreaTopLeftHandCornerTrial(0x0070, 0x0050);
Tag const DisplayedAreaBottomRightHandCornerTrial(0x0070, 0x0051);
Tag const DisplayedAreaTopLeftHandCorner(0x0070, 0x0052);
Tag const DisplayedAreaBottomRightHandCorner(0x0070, 0x0053);
Tag const DisplayedAreaSelectionSequence(0x0070, 0x005a);
Tag const GraphicLayerSequence(0x0070, 0x0060);
Tag const GraphicLayerOrder(0x0070, 0x0062);
Tag const GraphicLayerRecommendedDisplayGrayscaleValue(0x0070, 0x0066);
Tag const GraphicLayerRecommendedDisplayRGBValue(0x0070, 0x0067);
Tag const GraphicLayerDescription(0x0070, 0x0068);
Tag const ContentLabel(0x0070, 0x0080);
Tag const ContentDescription(0x0070, 0x0081);
Tag const PresentationCreationDate(0x0070, 0x0082);
Tag const PresentationCreationTime(0x0070, 0x0083);
Tag const ContentCreatorName(0x0070, 0x0084);
Tag const ContentCreatorIdentificationCodeSequence(0x0070, 0x0086);
Tag const AlternateContentDescriptionSequence(0x0070, 0x0087);
Tag const PresentationSizeMode(0x0070, 0x0100);
Tag const PresentationPixelSpacing(0x0070, 0x0101);
Tag const PresentationPixelAspectRatio(0x0070, 0x0102);
Tag const PresentationPixelMagnificationRatio(0x0070, 0x0103);
Tag const GraphicGroupLabel(0x0070, 0x0207);
Tag const GraphicGroupDescription(0x0070, 0x0208);
Tag const CompoundGraphicSequence(0x0070, 0x0209);
Tag const CompoundGraphicInstanceID(0x0070, 0x0226);
Tag const FontName(0x0070, 0x0227);
Tag const FontNameType(0x0070, 0x0228);
Tag const CSSFontName(0x0070, 0x0229);
Tag const RotationAngle(0x0070, 0x0230);
Tag const TextStyleSequence(0x0070, 0x0231);
Tag const LineStyleSequence(0x0070, 0x0232);
Tag const FillStyleSequence(0x0070, 0x0233);
Tag const GraphicGroupSequence(0x0070, 0x0234);
Tag const TextColorCIELabValue(0x0070, 0x0241);
Tag const HorizontalAlignment(0x0070, 0x0242);
Tag const VerticalAlignment(0x0070, 0x0243);
Tag const ShadowStyle(0x0070, 0x0244);
Tag const ShadowOffsetX(0x0070, 0x0245);
Tag const ShadowOffsetY(0x0070, 0x0246);
Tag const ShadowColorCIELabValue(0x0070, 0x0247);
Tag const Underlined(0x0070, 0x0248);
Tag const Bold(0x0070, 0x0249);
Tag const Italic(0x0070, 0x0250);
Tag const PatternOnColorCIELabValue(0x0070, 0x0251);
Tag const PatternOffColorCIELabValue(0x0070, 0x0252);
Tag const LineThickness(0x0070, 0x0253);
Tag const LineDashingStyle(0x0070, 0x0254);
Tag const LinePattern(0x0070, 0x0255);
Tag const FillPattern(0x0070, 0x0256);
Tag const FillMode(0x0070, 0x0257);
Tag const ShadowOpacity(0x0070, 0x0258);
Tag const GapLength(0x0070, 0x0261);
Tag const DiameterOfVisibility(0x0070, 0x0262);
Tag const RotationPoint(0x0070, 0x0273);
Tag const TickAlignment(0x0070, 0x0274);
Tag const ShowTickLabel(0x0070, 0x0278);
Tag const TickLabelAlignment(0x0070, 0x0279);
Tag const CompoundGraphicUnits(0x0070, 0x0282);
Tag const PatternOnOpacity(0x0070, 0x0284);
Tag const PatternOffOpacity(0x0070, 0x0285);
Tag const MajorTicksSequence(0x0070, 0x0287);
Tag const TickPosition(0x0070, 0x0288);
Tag const TickLabel(0x0070, 0x0289);
Tag const CompoundGraphicType(0x0070, 0x0294);
Tag const GraphicGroupID(0x0070, 0x0295);
Tag const ShapeType(0x0070, 0x0306);
Tag const RegistrationSequence(0x0070, 0x0308);
Tag const MatrixRegistrationSequence(0x0070, 0x0309);
Tag const MatrixSequence(0x0070, 0x030a);
Tag const FrameOfReferenceToDisplayedCoordinateSystemTransformationMatrix(0x0070, 0x030b);
Tag const FrameOfReferenceTransformationMatrixType(0x0070, 0x030c);
Tag const RegistrationTypeCodeSequence(0x0070, 0x030d);
Tag const FiducialDescription(0x0070, 0x030f);
Tag const FiducialIdentifier(0x0070, 0x0310);
Tag const FiducialIdentifierCodeSequence(0x0070, 0x0311);
Tag const ContourUncertaintyRadius(0x0070, 0x0312);
Tag const UsedFiducialsSequence(0x0070, 0x0314);
Tag const GraphicCoordinatesDataSequence(0x0070, 0x0318);
Tag const FiducialUID(0x0070, 0x031a);
Tag const ReferencedFiducialUID(0x0070, 0x031b);
Tag const FiducialSetSequence(0x0070, 0x031c);
Tag const FiducialSequence(0x0070, 0x031e);
Tag const FiducialsPropertyCategoryCodeSequence(0x0070, 0x031f);
Tag const GraphicLayerRecommendedDisplayCIELabValue(0x0070, 0x0401);
Tag const BlendingSequence(0x0070, 0x0402);
Tag const RelativeOpacity(0x0070, 0x0403);
Tag const ReferencedSpatialRegistrationSequence(0x0070, 0x0404);
Tag const BlendingPosition(0x0070, 0x0405);
Tag const PresentationDisplayCollectionUID(0x0070, 0x1101);
Tag const PresentationSequenceCollectionUID(0x0070, 0x1102);
Tag const PresentationSequencePositionIndex(0x0070, 0x1103);
Tag const RenderedImageReferenceSequence(0x0070, 0x1104);
Tag const VolumetricPresentationStateInputSequence(0x0070, 0x1201);
Tag const PresentationInputType(0x0070, 0x1202);
Tag const InputSequencePositionIndex(0x0070, 0x1203);
Tag const Crop(0x0070, 0x1204);
Tag const CroppingSpecificationIndex(0x0070, 0x1205);
Tag const CompositingMethod(0x0070, 0x1206);
Tag const VolumetricPresentationInputNumber(0x0070, 0x1207);
Tag const ImageVolumeGeometry(0x0070, 0x1208);
Tag const VolumetricPresentationInputSetUID(0x0070, 0x1209);
Tag const VolumetricPresentationInputSetSequence(0x0070, 0x120a);
Tag const GlobalCrop(0x0070, 0x120b);
Tag const GlobalCroppingSpecificationIndex(0x0070, 0x120c);
Tag const RenderingMethod(0x0070, 0x120d);
Tag const VolumeCroppingSequence(0x0070, 0x1301);
Tag const VolumeCroppingMethod(0x0070, 0x1302);
Tag const BoundingBoxCrop(0x0070, 0x1303);
Tag const ObliqueCroppingPlaneSequence(0x0070, 0x1304);
Tag const Plane(0x0070, 0x1305);
Tag const PlaneNormal(0x0070, 0x1306);
Tag const CroppingSpecificationNumber(0x0070, 0x1309);
Tag const MultiPlanarReconstructionStyle(0x0070, 0x1501);
Tag const MPRThicknessType(0x0070, 0x1502);
Tag const MPRSlabThickness(0x0070, 0x1503);
Tag const MPRTopLeftHandCorner(0x0070, 0x1505);
Tag const MPRViewWidthDirection(0x0070, 0x1507);
Tag const MPRViewWidth(0x0070, 0x1508);
Tag const NumberOfVolumetricCurvePoints(0x0070, 0x150c);
Tag const VolumetricCurvePoints(0x0070, 0x150d);
Tag const MPRViewHeightDirection(0x0070, 0x1511);
Tag const MPRViewHeight(0x0070, 0x1512);
Tag const RenderProjection(0x0070, 0x1602);
Tag const ViewpointPosition(0x0070, 0x1603);
Tag const ViewpointLookAtPoint(0x0070, 0x1604);
Tag const ViewpointUpDirection(0x0070, 0x1605);
Tag const RenderFieldOfView(0x0070, 0x1606);
Tag const SamplingStepSize(0x0070, 0x1607);
Tag const ShadingStyle(0x0070, 0x1701);
Tag const AmbientReflectionIntensity(0x0070, 0x1702);
Tag const LightDirection(0x0070, 0x1703);
Tag const DiffuseReflectionIntensity(0x0070, 0x1704);
Tag const SpecularReflectionIntensity(0x0070, 0x1705);
Tag const Shininess(0x0070, 0x1706);
Tag const PresentationStateClassificationComponentSequence(0x0070, 0x1801);
Tag const ComponentType(0x0070, 0x1802);
Tag const ComponentInputSequence(0x0070, 0x1803);
Tag const VolumetricPresentationInputIndex(0x0070, 0x1804);
Tag const PresentationStateCompositorComponentSequence(0x0070, 0x1805);
Tag const WeightingTransferFunctionSequence(0x0070, 0x1806);
Tag const WeightingLookupTableDescriptor(0x0070, 0x1807);
Tag const WeightingLookupTableData(0x0070, 0x1808);
Tag const VolumetricAnnotationSequence(0x0070, 0x1901);
Tag const ReferencedStructuredContextSequence(0x0070, 0x1903);
Tag const ReferencedContentItem(0x0070, 0x1904);
Tag const VolumetricPresentationInputAnnotationSequence(0x0070, 0x1905);
Tag const AnnotationClipping(0x0070, 0x1907);
Tag const PresentationAnimationStyle(0x0070, 0x1a01);
Tag const RecommendedAnimationRate(0x0070, 0x1a03);
Tag const AnimationCurveSequence(0x0070, 0x1a04);
Tag const AnimationStepSize(0x0070, 0x1a05);
Tag const SwivelRange(0x0070, 0x1a06);
Tag const VolumetricCurveUpDirections(0x0070, 0x1a07);
Tag const VolumeStreamSequence(0x0070, 0x1a08);
Tag const RGBATransferFunctionDescription(0x0070, 0x1a09);
Tag const AdvancedBlendingSequence(0x0070, 0x1b01);
Tag const BlendingInputNumber(0x0070, 0x1b02);
Tag const BlendingDisplayInputSequence(0x0070, 0x1b03);
Tag const BlendingDisplaySequence(0x0070, 0x1b04);
Tag const BlendingMode(0x0070, 0x1b06);
Tag const TimeSeriesBlending(0x0070, 0x1b07);
Tag const GeometryForDisplay(0x0070, 0x1b08);
Tag const ThresholdSequence(0x0070, 0x1b11);
Tag const ThresholdValueSequence(0x0070, 0x1b12);
Tag const ThresholdType(0x0070, 0x1b13);
Tag const ThresholdValue(0x0070, 0x1b14);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0070