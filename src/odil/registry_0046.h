/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0046
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0046

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const LensDescription(0x0046, 0x0012);
Tag const RightLensSequence(0x0046, 0x0014);
Tag const LeftLensSequence(0x0046, 0x0015);
Tag const UnspecifiedLateralityLensSequence(0x0046, 0x0016);
Tag const CylinderSequence(0x0046, 0x0018);
Tag const PrismSequence(0x0046, 0x0028);
Tag const HorizontalPrismPower(0x0046, 0x0030);
Tag const HorizontalPrismBase(0x0046, 0x0032);
Tag const VerticalPrismPower(0x0046, 0x0034);
Tag const VerticalPrismBase(0x0046, 0x0036);
Tag const LensSegmentType(0x0046, 0x0038);
Tag const OpticalTransmittance(0x0046, 0x0040);
Tag const ChannelWidth(0x0046, 0x0042);
Tag const PupilSize(0x0046, 0x0044);
Tag const CornealSize(0x0046, 0x0046);
Tag const CornealSizeSequence(0x0046, 0x0047);
Tag const AutorefractionRightEyeSequence(0x0046, 0x0050);
Tag const AutorefractionLeftEyeSequence(0x0046, 0x0052);
Tag const DistancePupillaryDistance(0x0046, 0x0060);
Tag const NearPupillaryDistance(0x0046, 0x0062);
Tag const IntermediatePupillaryDistance(0x0046, 0x0063);
Tag const OtherPupillaryDistance(0x0046, 0x0064);
Tag const KeratometryRightEyeSequence(0x0046, 0x0070);
Tag const KeratometryLeftEyeSequence(0x0046, 0x0071);
Tag const SteepKeratometricAxisSequence(0x0046, 0x0074);
Tag const RadiusOfCurvature(0x0046, 0x0075);
Tag const KeratometricPower(0x0046, 0x0076);
Tag const KeratometricAxis(0x0046, 0x0077);
Tag const FlatKeratometricAxisSequence(0x0046, 0x0080);
Tag const BackgroundColor(0x0046, 0x0092);
Tag const Optotype(0x0046, 0x0094);
Tag const OptotypePresentation(0x0046, 0x0095);
Tag const SubjectiveRefractionRightEyeSequence(0x0046, 0x0097);
Tag const SubjectiveRefractionLeftEyeSequence(0x0046, 0x0098);
Tag const AddNearSequence(0x0046, 0x0100);
Tag const AddIntermediateSequence(0x0046, 0x0101);
Tag const AddOtherSequence(0x0046, 0x0102);
Tag const AddPower(0x0046, 0x0104);
Tag const ViewingDistance(0x0046, 0x0106);
Tag const CorneaMeasurementsSequence(0x0046, 0x0110);
Tag const SourceOfCorneaMeasurementDataCodeSequence(0x0046, 0x0111);
Tag const SteepCornealAxisSequence(0x0046, 0x0112);
Tag const FlatCornealAxisSequence(0x0046, 0x0113);
Tag const CornealPower(0x0046, 0x0114);
Tag const CornealAxis(0x0046, 0x0115);
Tag const CorneaMeasurementMethodCodeSequence(0x0046, 0x0116);
Tag const RefractiveIndexOfCornea(0x0046, 0x0117);
Tag const RefractiveIndexOfAqueousHumor(0x0046, 0x0118);
Tag const VisualAcuityTypeCodeSequence(0x0046, 0x0121);
Tag const VisualAcuityRightEyeSequence(0x0046, 0x0122);
Tag const VisualAcuityLeftEyeSequence(0x0046, 0x0123);
Tag const VisualAcuityBothEyesOpenSequence(0x0046, 0x0124);
Tag const ViewingDistanceType(0x0046, 0x0125);
Tag const VisualAcuityModifiers(0x0046, 0x0135);
Tag const DecimalVisualAcuity(0x0046, 0x0137);
Tag const OptotypeDetailedDefinition(0x0046, 0x0139);
Tag const ReferencedRefractiveMeasurementsSequence(0x0046, 0x0145);
Tag const SpherePower(0x0046, 0x0146);
Tag const CylinderPower(0x0046, 0x0147);
Tag const CornealTopographySurface(0x0046, 0x0201);
Tag const CornealVertexLocation(0x0046, 0x0202);
Tag const PupilCentroidXCoordinate(0x0046, 0x0203);
Tag const PupilCentroidYCoordinate(0x0046, 0x0204);
Tag const EquivalentPupilRadius(0x0046, 0x0205);
Tag const CornealTopographyMapTypeCodeSequence(0x0046, 0x0207);
Tag const VerticesOfTheOutlineOfPupil(0x0046, 0x0208);
Tag const CornealTopographyMappingNormalsSequence(0x0046, 0x0210);
Tag const MaximumCornealCurvatureSequence(0x0046, 0x0211);
Tag const MaximumCornealCurvature(0x0046, 0x0212);
Tag const MaximumCornealCurvatureLocation(0x0046, 0x0213);
Tag const MinimumKeratometricSequence(0x0046, 0x0215);
Tag const SimulatedKeratometricCylinderSequence(0x0046, 0x0218);
Tag const AverageCornealPower(0x0046, 0x0220);
Tag const CornealISValue(0x0046, 0x0224);
Tag const AnalyzedArea(0x0046, 0x0227);
Tag const SurfaceRegularityIndex(0x0046, 0x0230);
Tag const SurfaceAsymmetryIndex(0x0046, 0x0232);
Tag const CornealEccentricityIndex(0x0046, 0x0234);
Tag const KeratoconusPredictionIndex(0x0046, 0x0236);
Tag const DecimalPotentialVisualAcuity(0x0046, 0x0238);
Tag const CornealTopographyMapQualityEvaluation(0x0046, 0x0242);
Tag const SourceImageCornealProcessedDataSequence(0x0046, 0x0244);
Tag const CornealPointLocation(0x0046, 0x0247);
Tag const CornealPointEstimated(0x0046, 0x0248);
Tag const AxialPower(0x0046, 0x0249);
Tag const TangentialPower(0x0046, 0x0250);
Tag const RefractivePower(0x0046, 0x0251);
Tag const RelativeElevation(0x0046, 0x0252);
Tag const CornealWavefront(0x0046, 0x0253);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0046