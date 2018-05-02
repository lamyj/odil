/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0020
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0020

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const StudyInstanceUID(0x0020, 0x000d);
Tag const SeriesInstanceUID(0x0020, 0x000e);
Tag const StudyID(0x0020, 0x0010);
Tag const SeriesNumber(0x0020, 0x0011);
Tag const AcquisitionNumber(0x0020, 0x0012);
Tag const InstanceNumber(0x0020, 0x0013);
Tag const IsotopeNumber(0x0020, 0x0014);
Tag const PhaseNumber(0x0020, 0x0015);
Tag const IntervalNumber(0x0020, 0x0016);
Tag const TimeSlotNumber(0x0020, 0x0017);
Tag const AngleNumber(0x0020, 0x0018);
Tag const ItemNumber(0x0020, 0x0019);
Tag const PatientOrientation(0x0020, 0x0020);
Tag const OverlayNumber(0x0020, 0x0022);
Tag const CurveNumber(0x0020, 0x0024);
Tag const LUTNumber(0x0020, 0x0026);
Tag const ImagePosition(0x0020, 0x0030);
Tag const ImagePositionPatient(0x0020, 0x0032);
Tag const ImageOrientation(0x0020, 0x0035);
Tag const ImageOrientationPatient(0x0020, 0x0037);
Tag const Location(0x0020, 0x0050);
Tag const FrameOfReferenceUID(0x0020, 0x0052);
Tag const Laterality(0x0020, 0x0060);
Tag const ImageLaterality(0x0020, 0x0062);
Tag const ImageGeometryType(0x0020, 0x0070);
Tag const MaskingImage(0x0020, 0x0080);
Tag const ReportNumber(0x0020, 0x00aa);
Tag const TemporalPositionIdentifier(0x0020, 0x0100);
Tag const NumberOfTemporalPositions(0x0020, 0x0105);
Tag const TemporalResolution(0x0020, 0x0110);
Tag const SynchronizationFrameOfReferenceUID(0x0020, 0x0200);
Tag const SOPInstanceUIDOfConcatenationSource(0x0020, 0x0242);
Tag const SeriesInStudy(0x0020, 0x1000);
Tag const AcquisitionsInSeries(0x0020, 0x1001);
Tag const ImagesInAcquisition(0x0020, 0x1002);
Tag const ImagesInSeries(0x0020, 0x1003);
Tag const AcquisitionsInStudy(0x0020, 0x1004);
Tag const ImagesInStudy(0x0020, 0x1005);
Tag const Reference(0x0020, 0x1020);
Tag const TargetPositionReferenceIndicator(0x0020, 0x103f);
Tag const PositionReferenceIndicator(0x0020, 0x1040);
Tag const SliceLocation(0x0020, 0x1041);
Tag const OtherStudyNumbers(0x0020, 0x1070);
Tag const NumberOfPatientRelatedStudies(0x0020, 0x1200);
Tag const NumberOfPatientRelatedSeries(0x0020, 0x1202);
Tag const NumberOfPatientRelatedInstances(0x0020, 0x1204);
Tag const NumberOfStudyRelatedSeries(0x0020, 0x1206);
Tag const NumberOfStudyRelatedInstances(0x0020, 0x1208);
Tag const NumberOfSeriesRelatedInstances(0x0020, 0x1209);
Tag const ModifyingDeviceID(0x0020, 0x3401);
Tag const ModifiedImageID(0x0020, 0x3402);
Tag const ModifiedImageDate(0x0020, 0x3403);
Tag const ModifyingDeviceManufacturer(0x0020, 0x3404);
Tag const ModifiedImageTime(0x0020, 0x3405);
Tag const ModifiedImageDescription(0x0020, 0x3406);
Tag const ImageComments(0x0020, 0x4000);
Tag const OriginalImageIdentification(0x0020, 0x5000);
Tag const OriginalImageIdentificationNomenclature(0x0020, 0x5002);
Tag const StackID(0x0020, 0x9056);
Tag const InStackPositionNumber(0x0020, 0x9057);
Tag const FrameAnatomySequence(0x0020, 0x9071);
Tag const FrameLaterality(0x0020, 0x9072);
Tag const FrameContentSequence(0x0020, 0x9111);
Tag const PlanePositionSequence(0x0020, 0x9113);
Tag const PlaneOrientationSequence(0x0020, 0x9116);
Tag const TemporalPositionIndex(0x0020, 0x9128);
Tag const NominalCardiacTriggerDelayTime(0x0020, 0x9153);
Tag const NominalCardiacTriggerTimePriorToRPeak(0x0020, 0x9154);
Tag const ActualCardiacTriggerTimePriorToRPeak(0x0020, 0x9155);
Tag const FrameAcquisitionNumber(0x0020, 0x9156);
Tag const DimensionIndexValues(0x0020, 0x9157);
Tag const FrameComments(0x0020, 0x9158);
Tag const ConcatenationUID(0x0020, 0x9161);
Tag const InConcatenationNumber(0x0020, 0x9162);
Tag const InConcatenationTotalNumber(0x0020, 0x9163);
Tag const DimensionOrganizationUID(0x0020, 0x9164);
Tag const DimensionIndexPointer(0x0020, 0x9165);
Tag const FunctionalGroupPointer(0x0020, 0x9167);
Tag const UnassignedSharedConvertedAttributesSequence(0x0020, 0x9170);
Tag const UnassignedPerFrameConvertedAttributesSequence(0x0020, 0x9171);
Tag const ConversionSourceAttributesSequence(0x0020, 0x9172);
Tag const DimensionIndexPrivateCreator(0x0020, 0x9213);
Tag const DimensionOrganizationSequence(0x0020, 0x9221);
Tag const DimensionIndexSequence(0x0020, 0x9222);
Tag const ConcatenationFrameOffsetNumber(0x0020, 0x9228);
Tag const FunctionalGroupPrivateCreator(0x0020, 0x9238);
Tag const NominalPercentageOfCardiacPhase(0x0020, 0x9241);
Tag const NominalPercentageOfRespiratoryPhase(0x0020, 0x9245);
Tag const StartingRespiratoryAmplitude(0x0020, 0x9246);
Tag const StartingRespiratoryPhase(0x0020, 0x9247);
Tag const EndingRespiratoryAmplitude(0x0020, 0x9248);
Tag const EndingRespiratoryPhase(0x0020, 0x9249);
Tag const RespiratoryTriggerType(0x0020, 0x9250);
Tag const RRIntervalTimeNominal(0x0020, 0x9251);
Tag const ActualCardiacTriggerDelayTime(0x0020, 0x9252);
Tag const RespiratorySynchronizationSequence(0x0020, 0x9253);
Tag const RespiratoryIntervalTime(0x0020, 0x9254);
Tag const NominalRespiratoryTriggerDelayTime(0x0020, 0x9255);
Tag const RespiratoryTriggerDelayThreshold(0x0020, 0x9256);
Tag const ActualRespiratoryTriggerDelayTime(0x0020, 0x9257);
Tag const ImagePositionVolume(0x0020, 0x9301);
Tag const ImageOrientationVolume(0x0020, 0x9302);
Tag const UltrasoundAcquisitionGeometry(0x0020, 0x9307);
Tag const ApexPosition(0x0020, 0x9308);
Tag const VolumeToTransducerMappingMatrix(0x0020, 0x9309);
Tag const VolumeToTableMappingMatrix(0x0020, 0x930a);
Tag const VolumeToTransducerRelationship(0x0020, 0x930b);
Tag const PatientFrameOfReferenceSource(0x0020, 0x930c);
Tag const TemporalPositionTimeOffset(0x0020, 0x930d);
Tag const PlanePositionVolumeSequence(0x0020, 0x930e);
Tag const PlaneOrientationVolumeSequence(0x0020, 0x930f);
Tag const TemporalPositionSequence(0x0020, 0x9310);
Tag const DimensionOrganizationType(0x0020, 0x9311);
Tag const VolumeFrameOfReferenceUID(0x0020, 0x9312);
Tag const TableFrameOfReferenceUID(0x0020, 0x9313);
Tag const DimensionDescriptionLabel(0x0020, 0x9421);
Tag const PatientOrientationInFrameSequence(0x0020, 0x9450);
Tag const FrameLabel(0x0020, 0x9453);
Tag const AcquisitionIndex(0x0020, 0x9518);
Tag const ContributingSOPInstancesReferenceSequence(0x0020, 0x9529);
Tag const ReconstructionIndex(0x0020, 0x9536);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0020