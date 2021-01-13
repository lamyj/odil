/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_4010
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_4010

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const LowEnergyDetectors(0x4010, 0x0001);
Tag const HighEnergyDetectors(0x4010, 0x0002);
Tag const DetectorGeometrySequence(0x4010, 0x0004);
Tag const ThreatROIVoxelSequence(0x4010, 0x1001);
Tag const ThreatROIBase(0x4010, 0x1004);
Tag const ThreatROIExtents(0x4010, 0x1005);
Tag const ThreatROIBitmap(0x4010, 0x1006);
Tag const RouteSegmentID(0x4010, 0x1007);
Tag const GantryType(0x4010, 0x1008);
Tag const OOIOwnerType(0x4010, 0x1009);
Tag const RouteSegmentSequence(0x4010, 0x100a);
Tag const PotentialThreatObjectID(0x4010, 0x1010);
Tag const ThreatSequence(0x4010, 0x1011);
Tag const ThreatCategory(0x4010, 0x1012);
Tag const ThreatCategoryDescription(0x4010, 0x1013);
Tag const ATDAbilityAssessment(0x4010, 0x1014);
Tag const ATDAssessmentFlag(0x4010, 0x1015);
Tag const ATDAssessmentProbability(0x4010, 0x1016);
Tag const Mass(0x4010, 0x1017);
Tag const Density(0x4010, 0x1018);
Tag const ZEffective(0x4010, 0x1019);
Tag const BoardingPassID(0x4010, 0x101a);
Tag const CenterOfMass(0x4010, 0x101b);
Tag const CenterOfPTO(0x4010, 0x101c);
Tag const BoundingPolygon(0x4010, 0x101d);
Tag const RouteSegmentStartLocationID(0x4010, 0x101e);
Tag const RouteSegmentEndLocationID(0x4010, 0x101f);
Tag const RouteSegmentLocationIDType(0x4010, 0x1020);
Tag const AbortReason(0x4010, 0x1021);
Tag const VolumeOfPTO(0x4010, 0x1023);
Tag const AbortFlag(0x4010, 0x1024);
Tag const RouteSegmentStartTime(0x4010, 0x1025);
Tag const RouteSegmentEndTime(0x4010, 0x1026);
Tag const TDRType(0x4010, 0x1027);
Tag const InternationalRouteSegment(0x4010, 0x1028);
Tag const ThreatDetectionAlgorithmAndVersion(0x4010, 0x1029);
Tag const AssignedLocation(0x4010, 0x102a);
Tag const AlarmDecisionTime(0x4010, 0x102b);
Tag const AlarmDecision(0x4010, 0x1031);
Tag const NumberOfTotalObjects(0x4010, 0x1033);
Tag const NumberOfAlarmObjects(0x4010, 0x1034);
Tag const PTORepresentationSequence(0x4010, 0x1037);
Tag const ATDAssessmentSequence(0x4010, 0x1038);
Tag const TIPType(0x4010, 0x1039);
Tag const DICOSVersion(0x4010, 0x103a);
Tag const OOIOwnerCreationTime(0x4010, 0x1041);
Tag const OOIType(0x4010, 0x1042);
Tag const OOISize(0x4010, 0x1043);
Tag const AcquisitionStatus(0x4010, 0x1044);
Tag const BasisMaterialsCodeSequence(0x4010, 0x1045);
Tag const PhantomType(0x4010, 0x1046);
Tag const OOIOwnerSequence(0x4010, 0x1047);
Tag const ScanType(0x4010, 0x1048);
Tag const ItineraryID(0x4010, 0x1051);
Tag const ItineraryIDType(0x4010, 0x1052);
Tag const ItineraryIDAssigningAuthority(0x4010, 0x1053);
Tag const RouteID(0x4010, 0x1054);
Tag const RouteIDAssigningAuthority(0x4010, 0x1055);
Tag const InboundArrivalType(0x4010, 0x1056);
Tag const CarrierID(0x4010, 0x1058);
Tag const CarrierIDAssigningAuthority(0x4010, 0x1059);
Tag const SourceOrientation(0x4010, 0x1060);
Tag const SourcePosition(0x4010, 0x1061);
Tag const BeltHeight(0x4010, 0x1062);
Tag const AlgorithmRoutingCodeSequence(0x4010, 0x1064);
Tag const TransportClassification(0x4010, 0x1067);
Tag const OOITypeDescriptor(0x4010, 0x1068);
Tag const TotalProcessingTime(0x4010, 0x1069);
Tag const DetectorCalibrationData(0x4010, 0x106c);
Tag const AdditionalScreeningPerformed(0x4010, 0x106d);
Tag const AdditionalInspectionSelectionCriteria(0x4010, 0x106e);
Tag const AdditionalInspectionMethodSequence(0x4010, 0x106f);
Tag const AITDeviceType(0x4010, 0x1070);
Tag const QRMeasurementsSequence(0x4010, 0x1071);
Tag const TargetMaterialSequence(0x4010, 0x1072);
Tag const SNRThreshold(0x4010, 0x1073);
Tag const ImageScaleRepresentation(0x4010, 0x1075);
Tag const ReferencedPTOSequence(0x4010, 0x1076);
Tag const ReferencedTDRInstanceSequence(0x4010, 0x1077);
Tag const PTOLocationDescription(0x4010, 0x1078);
Tag const AnomalyLocatorIndicatorSequence(0x4010, 0x1079);
Tag const AnomalyLocatorIndicator(0x4010, 0x107a);
Tag const PTORegionSequence(0x4010, 0x107b);
Tag const InspectionSelectionCriteria(0x4010, 0x107c);
Tag const SecondaryInspectionMethodSequence(0x4010, 0x107d);
Tag const PRCSToRCSOrientation(0x4010, 0x107e);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_4010