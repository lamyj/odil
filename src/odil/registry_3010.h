/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3010
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3010

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const RadiobiologicalDoseEffectSequence(0x3010, 0x0001);
Tag const RadiobiologicalDoseEffectFlag(0x3010, 0x0002);
Tag const EffectiveDoseCalculationMethodCategoryCodeSequence(0x3010, 0x0003);
Tag const EffectiveDoseCalculationMethodCodeSequence(0x3010, 0x0004);
Tag const EffectiveDoseCalculationMethodDescription(0x3010, 0x0005);
Tag const ConceptualVolumeUID(0x3010, 0x0006);
Tag const OriginatingSOPInstanceReferenceSequence(0x3010, 0x0007);
Tag const ConceptualVolumeConstituentSequence(0x3010, 0x0008);
Tag const EquivalentConceptualVolumeInstanceReferenceSequence(0x3010, 0x0009);
Tag const EquivalentConceptualVolumesSequence(0x3010, 0x000a);
Tag const ReferencedConceptualVolumeUID(0x3010, 0x000b);
Tag const ConceptualVolumeCombinationExpression(0x3010, 0x000c);
Tag const ConceptualVolumeConstituentIndex(0x3010, 0x000d);
Tag const ConceptualVolumeCombinationFlag(0x3010, 0x000e);
Tag const ConceptualVolumeCombinationDescription(0x3010, 0x000f);
Tag const ConceptualVolumeSegmentationDefinedFlag(0x3010, 0x0010);
Tag const ConceptualVolumeSegmentationReferenceSequence(0x3010, 0x0011);
Tag const ConceptualVolumeConstituentSegmentationReferenceSequence(0x3010, 0x0012);
Tag const ConstituentConceptualVolumeUID(0x3010, 0x0013);
Tag const DerivationConceptualVolumeSequence(0x3010, 0x0014);
Tag const SourceConceptualVolumeUID(0x3010, 0x0015);
Tag const ConceptualVolumeDerivationAlgorithmSequence(0x3010, 0x0016);
Tag const ConceptualVolumeDescription(0x3010, 0x0017);
Tag const SourceConceptualVolumeSequence(0x3010, 0x0018);
Tag const AuthorIdentificationSequence(0x3010, 0x0019);
Tag const ManufacturerModelVersion(0x3010, 0x001a);
Tag const DeviceAlternateIdentifier(0x3010, 0x001b);
Tag const DeviceAlternateIdentifierType(0x3010, 0x001c);
Tag const DeviceAlternateIdentifierFormat(0x3010, 0x001d);
Tag const SegmentationCreationTemplateLabel(0x3010, 0x001e);
Tag const SegmentationTemplateUID(0x3010, 0x001f);
Tag const ReferencedSegmentReferenceIndex(0x3010, 0x0020);
Tag const SegmentReferenceSequence(0x3010, 0x0021);
Tag const SegmentReferenceIndex(0x3010, 0x0022);
Tag const DirectSegmentReferenceSequence(0x3010, 0x0023);
Tag const CombinationSegmentReferenceSequence(0x3010, 0x0024);
Tag const ConceptualVolumeSequence(0x3010, 0x0025);
Tag const SegmentedRTAccessoryDeviceSequence(0x3010, 0x0026);
Tag const SegmentCharacteristicsSequence(0x3010, 0x0027);
Tag const RelatedSegmentCharacteristicsSequence(0x3010, 0x0028);
Tag const SegmentCharacteristicsPrecedence(0x3010, 0x0029);
Tag const RTSegmentAnnotationSequence(0x3010, 0x002a);
Tag const SegmentAnnotationCategoryCodeSequence(0x3010, 0x002b);
Tag const SegmentAnnotationTypeCodeSequence(0x3010, 0x002c);
Tag const DeviceLabel(0x3010, 0x002d);
Tag const DeviceTypeCodeSequence(0x3010, 0x002e);
Tag const SegmentAnnotationTypeModifierCodeSequence(0x3010, 0x002f);
Tag const PatientEquipmentRelationshipCodeSequence(0x3010, 0x0030);
Tag const ReferencedFiducialsUID(0x3010, 0x0031);
Tag const PatientTreatmentOrientationSequence(0x3010, 0x0032);
Tag const UserContentLabel(0x3010, 0x0033);
Tag const UserContentLongLabel(0x3010, 0x0034);
Tag const EntityLabel(0x3010, 0x0035);
Tag const EntityName(0x3010, 0x0036);
Tag const EntityDescription(0x3010, 0x0037);
Tag const EntityLongLabel(0x3010, 0x0038);
Tag const DeviceIndex(0x3010, 0x0039);
Tag const RTTreatmentPhaseIndex(0x3010, 0x003a);
Tag const RTTreatmentPhaseUID(0x3010, 0x003b);
Tag const RTPrescriptionIndex(0x3010, 0x003c);
Tag const RTSegmentAnnotationIndex(0x3010, 0x003d);
Tag const BasisRTTreatmentPhaseIndex(0x3010, 0x003e);
Tag const RelatedRTTreatmentPhaseIndex(0x3010, 0x003f);
Tag const ReferencedRTTreatmentPhaseIndex(0x3010, 0x0040);
Tag const ReferencedRTPrescriptionIndex(0x3010, 0x0041);
Tag const ReferencedParentRTPrescriptionIndex(0x3010, 0x0042);
Tag const ManufacturerDeviceIdentifier(0x3010, 0x0043);
Tag const InstanceLevelReferencedPerformedProcedureStepSequence(0x3010, 0x0044);
Tag const RTTreatmentPhaseIntentPresenceFlag(0x3010, 0x0045);
Tag const RadiotherapyTreatmentType(0x3010, 0x0046);
Tag const TeletherapyRadiationType(0x3010, 0x0047);
Tag const BrachytherapySourceType(0x3010, 0x0048);
Tag const ReferencedRTTreatmentPhaseSequence(0x3010, 0x0049);
Tag const ReferencedDirectSegmentInstanceSequence(0x3010, 0x004a);
Tag const IntendedRTTreatmentPhaseSequence(0x3010, 0x004b);
Tag const IntendedPhaseStartDate(0x3010, 0x004c);
Tag const IntendedPhaseEndDate(0x3010, 0x004d);
Tag const RTTreatmentPhaseIntervalSequence(0x3010, 0x004e);
Tag const TemporalRelationshipIntervalAnchor(0x3010, 0x004f);
Tag const MinimumNumberOfIntervalDays(0x3010, 0x0050);
Tag const MaximumNumberOfIntervalDays(0x3010, 0x0051);
Tag const PertinentSOPClassesInStudy(0x3010, 0x0052);
Tag const PertinentSOPClassesInSeries(0x3010, 0x0053);
Tag const RTPrescriptionLabel(0x3010, 0x0054);
Tag const RTPhysicianIntentPredecessorSequence(0x3010, 0x0055);
Tag const RTTreatmentApproachLabel(0x3010, 0x0056);
Tag const RTPhysicianIntentSequence(0x3010, 0x0057);
Tag const RTPhysicianIntentIndex(0x3010, 0x0058);
Tag const RTTreatmentIntentType(0x3010, 0x0059);
Tag const RTPhysicianIntentNarrative(0x3010, 0x005a);
Tag const RTProtocolCodeSequence(0x3010, 0x005b);
Tag const ReasonForSuperseding(0x3010, 0x005c);
Tag const RTDiagnosisCodeSequence(0x3010, 0x005d);
Tag const ReferencedRTPhysicianIntentIndex(0x3010, 0x005e);
Tag const RTPhysicianIntentInputInstanceSequence(0x3010, 0x005f);
Tag const RTAnatomicPrescriptionSequence(0x3010, 0x0060);
Tag const PriorTreatmentDoseDescription(0x3010, 0x0061);
Tag const PriorTreatmentReferenceSequence(0x3010, 0x0062);
Tag const DosimetricObjectiveEvaluationScope(0x3010, 0x0063);
Tag const TherapeuticRoleCategoryCodeSequence(0x3010, 0x0064);
Tag const TherapeuticRoleTypeCodeSequence(0x3010, 0x0065);
Tag const ConceptualVolumeOptimizationPrecedence(0x3010, 0x0066);
Tag const ConceptualVolumeCategoryCodeSequence(0x3010, 0x0067);
Tag const ConceptualVolumeBlockingConstraint(0x3010, 0x0068);
Tag const ConceptualVolumeTypeCodeSequence(0x3010, 0x0069);
Tag const ConceptualVolumeTypeModifierCodeSequence(0x3010, 0x006a);
Tag const RTPrescriptionSequence(0x3010, 0x006b);
Tag const DosimetricObjectiveSequence(0x3010, 0x006c);
Tag const DosimetricObjectiveTypeCodeSequence(0x3010, 0x006d);
Tag const DosimetricObjectiveUID(0x3010, 0x006e);
Tag const ReferencedDosimetricObjectiveUID(0x3010, 0x006f);
Tag const DosimetricObjectiveParameterSequence(0x3010, 0x0070);
Tag const ReferencedDosimetricObjectivesSequence(0x3010, 0x0071);
Tag const AbsoluteDosimetricObjectiveFlag(0x3010, 0x0073);
Tag const DosimetricObjectiveWeight(0x3010, 0x0074);
Tag const DosimetricObjectivePurpose(0x3010, 0x0075);
Tag const PlanningInputInformationSequence(0x3010, 0x0076);
Tag const TreatmentSite(0x3010, 0x0077);
Tag const TreatmentSiteCodeSequence(0x3010, 0x0078);
Tag const FractionPatternSequence(0x3010, 0x0079);
Tag const TreatmentTechniqueNotes(0x3010, 0x007a);
Tag const PrescriptionNotes(0x3010, 0x007b);
Tag const NumberOfIntervalFractions(0x3010, 0x007c);
Tag const NumberOfFractions(0x3010, 0x007d);
Tag const IntendedDeliveryDuration(0x3010, 0x007e);
Tag const FractionationNotes(0x3010, 0x007f);
Tag const RTTreatmentTechniqueCodeSequence(0x3010, 0x0080);
Tag const PrescriptionNotesSequence(0x3010, 0x0081);
Tag const FractionBasedRelationshipSequence(0x3010, 0x0082);
Tag const FractionBasedRelationshipIntervalAnchor(0x3010, 0x0083);
Tag const MinimumHoursBetweenFractions(0x3010, 0x0084);
Tag const IntendedFractionStartTime(0x3010, 0x0085);
Tag const IntendedStartDayOfWeek(0x3010, 0x0086);
Tag const WeekdayFractionPatternSequence(0x3010, 0x0087);
Tag const DeliveryTimeStructureCodeSequence(0x3010, 0x0088);
Tag const TreatmentSiteModifierCodeSequence(0x3010, 0x0089);
Tag const RoboticBaseLocationIndicator(0x3010, 0x0090);
Tag const RoboticPathNodeSetCodeSequence(0x3010, 0x0091);
Tag const RoboticNodeIdentifier(0x3010, 0x0092);
Tag const RTTreatmentSourceCoordinates(0x3010, 0x0093);
Tag const RadiationSourceCoordinateSystemYawAngle(0x3010, 0x0094);
Tag const RadiationSourceCoordinateSystemRollAngle(0x3010, 0x0095);
Tag const RadiationSourceCoordinateSystemPitchAngle(0x3010, 0x0096);
Tag const RoboticPathControlPointSequence(0x3010, 0x0097);
Tag const TomotherapeuticControlPointSequence(0x3010, 0x0098);
Tag const TomotherapeuticLeafOpenDurations(0x3010, 0x0099);
Tag const TomotherapeuticLeafInitialClosedDurations(0x3010, 0x009a);
Tag const ConceptualVolumeIdentificationSequence(0x3010, 0x00a0);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3010