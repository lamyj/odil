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

void update_3010(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x3010, 0x0001), ElementsDictionaryEntry("Radiobiological Dose Effect Sequence", "RadiobiologicalDoseEffectSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0002), ElementsDictionaryEntry("Radiobiological Dose Effect Flag", "RadiobiologicalDoseEffectFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0003), ElementsDictionaryEntry("Effective Dose Calculation Method Category Code Sequence", "EffectiveDoseCalculationMethodCategoryCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0004), ElementsDictionaryEntry("Effective Dose Calculation Method Code Sequence", "EffectiveDoseCalculationMethodCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0005), ElementsDictionaryEntry("Effective Dose Calculation Method Description", "EffectiveDoseCalculationMethodDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0006), ElementsDictionaryEntry("Conceptual Volume UID", "ConceptualVolumeUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0007), ElementsDictionaryEntry("Originating SOP Instance Reference Sequence", "OriginatingSOPInstanceReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0008), ElementsDictionaryEntry("Conceptual Volume Constituent Sequence", "ConceptualVolumeConstituentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0009), ElementsDictionaryEntry("Equivalent Conceptual Volume Instance Reference Sequence", "EquivalentConceptualVolumeInstanceReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x000a), ElementsDictionaryEntry("Equivalent Conceptual Volumes Sequence", "EquivalentConceptualVolumesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x000b), ElementsDictionaryEntry("Referenced Conceptual Volume UID", "ReferencedConceptualVolumeUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x000c), ElementsDictionaryEntry("Conceptual Volume Combination Expression", "ConceptualVolumeCombinationExpression",  "UT", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x000d), ElementsDictionaryEntry("Conceptual Volume Constituent Index", "ConceptualVolumeConstituentIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x000e), ElementsDictionaryEntry("Conceptual Volume Combination Flag", "ConceptualVolumeCombinationFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x000f), ElementsDictionaryEntry("Conceptual Volume Combination Description", "ConceptualVolumeCombinationDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0010), ElementsDictionaryEntry("Conceptual Volume Segmentation Defined Flag", "ConceptualVolumeSegmentationDefinedFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0011), ElementsDictionaryEntry("Conceptual Volume Segmentation Reference Sequence", "ConceptualVolumeSegmentationReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0012), ElementsDictionaryEntry("Conceptual Volume Constituent Segmentation Reference Sequence", "ConceptualVolumeConstituentSegmentationReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0013), ElementsDictionaryEntry("Constituent Conceptual Volume UID", "ConstituentConceptualVolumeUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0014), ElementsDictionaryEntry("Derivation Conceptual Volume Sequence", "DerivationConceptualVolumeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0015), ElementsDictionaryEntry("Source Conceptual Volume UID", "SourceConceptualVolumeUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0016), ElementsDictionaryEntry("Conceptual Volume Derivation Algorithm Sequence", "ConceptualVolumeDerivationAlgorithmSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0017), ElementsDictionaryEntry("Conceptual Volume Description", "ConceptualVolumeDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0018), ElementsDictionaryEntry("Source Conceptual Volume Sequence", "SourceConceptualVolumeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0019), ElementsDictionaryEntry("Author Identification Sequence", "AuthorIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x001a), ElementsDictionaryEntry("Manufacturer's Model Version", "ManufacturerModelVersion",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x001b), ElementsDictionaryEntry("Device Alternate Identifier", "DeviceAlternateIdentifier",  "UC", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x001c), ElementsDictionaryEntry("Device Alternate Identifier Type", "DeviceAlternateIdentifierType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x001d), ElementsDictionaryEntry("Device Alternate Identifier Format", "DeviceAlternateIdentifierFormat",  "LT", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x001e), ElementsDictionaryEntry("Segmentation Creation Template Label", "SegmentationCreationTemplateLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x001f), ElementsDictionaryEntry("Segmentation Template UID", "SegmentationTemplateUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0020), ElementsDictionaryEntry("Referenced Segment Reference Index", "ReferencedSegmentReferenceIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0021), ElementsDictionaryEntry("Segment Reference Sequence", "SegmentReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0022), ElementsDictionaryEntry("Segment Reference Index", "SegmentReferenceIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0023), ElementsDictionaryEntry("Direct Segment Reference Sequence", "DirectSegmentReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0024), ElementsDictionaryEntry("Combination Segment Reference Sequence", "CombinationSegmentReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0025), ElementsDictionaryEntry("Conceptual Volume Sequence", "ConceptualVolumeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0026), ElementsDictionaryEntry("Segmented RT Accessory Device Sequence", "SegmentedRTAccessoryDeviceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0027), ElementsDictionaryEntry("Segment Characteristics Sequence", "SegmentCharacteristicsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0028), ElementsDictionaryEntry("Related Segment Characteristics Sequence", "RelatedSegmentCharacteristicsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0029), ElementsDictionaryEntry("Segment Characteristics Precedence", "SegmentCharacteristicsPrecedence",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x002a), ElementsDictionaryEntry("RT Segment Annotation Sequence", "RTSegmentAnnotationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x002b), ElementsDictionaryEntry("Segment Annotation Category Code Sequence", "SegmentAnnotationCategoryCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x002c), ElementsDictionaryEntry("Segment Annotation Type Code Sequence", "SegmentAnnotationTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x002d), ElementsDictionaryEntry("Device Label", "DeviceLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x002e), ElementsDictionaryEntry("Device Type Code Sequence", "DeviceTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x002f), ElementsDictionaryEntry("Segment Annotation Type Modifier Code Sequence", "SegmentAnnotationTypeModifierCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0030), ElementsDictionaryEntry("Patient Equipment Relationship Code Sequence", "PatientEquipmentRelationshipCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0031), ElementsDictionaryEntry("Referenced Fiducials UID", "ReferencedFiducialsUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0032), ElementsDictionaryEntry("Patient Treatment Orientation Sequence", "PatientTreatmentOrientationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0033), ElementsDictionaryEntry("User Content Label", "UserContentLabel",  "SH", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0034), ElementsDictionaryEntry("User Content Long Label", "UserContentLongLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0035), ElementsDictionaryEntry("Entity Label", "EntityLabel",  "SH", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0036), ElementsDictionaryEntry("Entity Name", "EntityName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0037), ElementsDictionaryEntry("Entity Description", "EntityDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0038), ElementsDictionaryEntry("Entity Long Label", "EntityLongLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0039), ElementsDictionaryEntry("Device Index", "DeviceIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x003a), ElementsDictionaryEntry("RT Treatment Phase Index", "RTTreatmentPhaseIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x003b), ElementsDictionaryEntry("RT Treatment Phase UID", "RTTreatmentPhaseUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x003c), ElementsDictionaryEntry("RT Prescription Index", "RTPrescriptionIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x003d), ElementsDictionaryEntry("RT Segment Annotation Index", "RTSegmentAnnotationIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x003e), ElementsDictionaryEntry("Basis RT Treatment Phase Index", "BasisRTTreatmentPhaseIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x003f), ElementsDictionaryEntry("Related RT Treatment Phase Index", "RelatedRTTreatmentPhaseIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0040), ElementsDictionaryEntry("Referenced RT Treatment Phase Index", "ReferencedRTTreatmentPhaseIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0041), ElementsDictionaryEntry("Referenced RT Prescription Index", "ReferencedRTPrescriptionIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0042), ElementsDictionaryEntry("Referenced Parent RT Prescription Index", "ReferencedParentRTPrescriptionIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0043), ElementsDictionaryEntry("Manufacturer's Device Identifier", "ManufacturerDeviceIdentifier",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0044), ElementsDictionaryEntry("Instance-Level Referenced Performed Procedure Step Sequence", "InstanceLevelReferencedPerformedProcedureStepSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0045), ElementsDictionaryEntry("RT Treatment Phase Intent Presence Flag", "RTTreatmentPhaseIntentPresenceFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0046), ElementsDictionaryEntry("Radiotherapy Treatment Type", "RadiotherapyTreatmentType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0047), ElementsDictionaryEntry("Teletherapy Radiation Type", "TeletherapyRadiationType",  "CS", "1-n"));
    public_dictionary.emplace(Tag(0x3010, 0x0048), ElementsDictionaryEntry("Brachytherapy Source Type", "BrachytherapySourceType",  "CS", "1-n"));
    public_dictionary.emplace(Tag(0x3010, 0x0049), ElementsDictionaryEntry("Referenced RT Treatment Phase Sequence", "ReferencedRTTreatmentPhaseSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x004a), ElementsDictionaryEntry("Referenced Direct Segment Instance Sequence", "ReferencedDirectSegmentInstanceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x004b), ElementsDictionaryEntry("Intended RT Treatment Phase Sequence", "IntendedRTTreatmentPhaseSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x004c), ElementsDictionaryEntry("Intended Phase Start Date", "IntendedPhaseStartDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x004d), ElementsDictionaryEntry("Intended Phase End Date", "IntendedPhaseEndDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x004e), ElementsDictionaryEntry("RT Treatment Phase Interval Sequence", "RTTreatmentPhaseIntervalSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x004f), ElementsDictionaryEntry("Temporal Relationship Interval Anchor", "TemporalRelationshipIntervalAnchor",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0050), ElementsDictionaryEntry("Minimum Number of Interval Days", "MinimumNumberOfIntervalDays",  "FD", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0051), ElementsDictionaryEntry("Maximum Number of Interval Days", "MaximumNumberOfIntervalDays",  "FD", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0052), ElementsDictionaryEntry("Pertinent SOP Classes in Study", "PertinentSOPClassesInStudy",  "UI", "1-n"));
    public_dictionary.emplace(Tag(0x3010, 0x0053), ElementsDictionaryEntry("Pertinent SOP Classes in Series", "PertinentSOPClassesInSeries",  "UI", "1-n"));
    public_dictionary.emplace(Tag(0x3010, 0x0054), ElementsDictionaryEntry("RT Prescription Label", "RTPrescriptionLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0055), ElementsDictionaryEntry("RT Physician Intent Predecessor Sequence", "RTPhysicianIntentPredecessorSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0056), ElementsDictionaryEntry("RT Treatment Approach Label", "RTTreatmentApproachLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0057), ElementsDictionaryEntry("RT Physician Intent Sequence", "RTPhysicianIntentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0058), ElementsDictionaryEntry("RT Physician Intent Index", "RTPhysicianIntentIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0059), ElementsDictionaryEntry("RT Treatment Intent Type", "RTTreatmentIntentType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x005a), ElementsDictionaryEntry("RT Physician Intent Narrative", "RTPhysicianIntentNarrative",  "UT", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x005b), ElementsDictionaryEntry("RT Protocol Code Sequence", "RTProtocolCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x005c), ElementsDictionaryEntry("Reason for Superseding", "ReasonForSuperseding",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x005d), ElementsDictionaryEntry("RT Diagnosis Code Sequence", "RTDiagnosisCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x005e), ElementsDictionaryEntry("Referenced RT Physician Intent Index", "ReferencedRTPhysicianIntentIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x005f), ElementsDictionaryEntry("RT Physician Intent Input Instance Sequence", "RTPhysicianIntentInputInstanceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0060), ElementsDictionaryEntry("RT Anatomic Prescription Sequence", "RTAnatomicPrescriptionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0061), ElementsDictionaryEntry("Prior Treatment Dose Description", "PriorTreatmentDoseDescription",  "UT", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0062), ElementsDictionaryEntry("Prior Treatment Reference Sequence", "PriorTreatmentReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0063), ElementsDictionaryEntry("Dosimetric Objective Evaluation Scope", "DosimetricObjectiveEvaluationScope",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0064), ElementsDictionaryEntry("Therapeutic Role Category Code Sequence", "TherapeuticRoleCategoryCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0065), ElementsDictionaryEntry("Therapeutic Role Type Code Sequence", "TherapeuticRoleTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0066), ElementsDictionaryEntry("Conceptual Volume Optimization Precedence", "ConceptualVolumeOptimizationPrecedence",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0067), ElementsDictionaryEntry("Conceptual Volume Category Code Sequence", "ConceptualVolumeCategoryCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0068), ElementsDictionaryEntry("Conceptual Volume Blocking Constraint", "ConceptualVolumeBlockingConstraint",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0069), ElementsDictionaryEntry("Conceptual Volume Type Code Sequence", "ConceptualVolumeTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x006a), ElementsDictionaryEntry("Conceptual Volume Type Modifier Code Sequence", "ConceptualVolumeTypeModifierCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x006b), ElementsDictionaryEntry("RT Prescription Sequence", "RTPrescriptionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x006c), ElementsDictionaryEntry("Dosimetric Objective Sequence", "DosimetricObjectiveSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x006d), ElementsDictionaryEntry("Dosimetric Objective Type Code Sequence", "DosimetricObjectiveTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x006e), ElementsDictionaryEntry("Dosimetric Objective UID", "DosimetricObjectiveUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x006f), ElementsDictionaryEntry("Referenced Dosimetric Objective UID", "ReferencedDosimetricObjectiveUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0070), ElementsDictionaryEntry("Dosimetric Objective Parameter Sequence", "DosimetricObjectiveParameterSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0071), ElementsDictionaryEntry("Referenced Dosimetric Objectives Sequence", "ReferencedDosimetricObjectivesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0073), ElementsDictionaryEntry("Absolute Dosimetric Objective Flag", "AbsoluteDosimetricObjectiveFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0074), ElementsDictionaryEntry("Dosimetric Objective Weight", "DosimetricObjectiveWeight",  "FD", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0075), ElementsDictionaryEntry("Dosimetric Objective Purpose", "DosimetricObjectivePurpose",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0076), ElementsDictionaryEntry("Planning Input Information Sequence", "PlanningInputInformationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0077), ElementsDictionaryEntry("Treatment Site", "TreatmentSite",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0078), ElementsDictionaryEntry("Treatment Site Code Sequence", "TreatmentSiteCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0079), ElementsDictionaryEntry("Fraction Pattern Sequence", "FractionPatternSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x007a), ElementsDictionaryEntry("Treatment Technique Notes", "TreatmentTechniqueNotes",  "UT", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x007b), ElementsDictionaryEntry("Prescription Notes", "PrescriptionNotes",  "UT", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x007c), ElementsDictionaryEntry("Number of Interval Fractions", "NumberOfIntervalFractions",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x007d), ElementsDictionaryEntry("Number of Fractions", "NumberOfFractions",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x007e), ElementsDictionaryEntry("Intended Delivery Duration", "IntendedDeliveryDuration",  "US", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x007f), ElementsDictionaryEntry("Fractionation Notes", "FractionationNotes",  "UT", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0080), ElementsDictionaryEntry("RT Treatment Technique Code Sequence", "RTTreatmentTechniqueCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0081), ElementsDictionaryEntry("Prescription Notes Sequence", "PrescriptionNotesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0082), ElementsDictionaryEntry("Fraction-Based Relationship Sequence", "FractionBasedRelationshipSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0083), ElementsDictionaryEntry("Fraction-Based Relationship Interval Anchor", "FractionBasedRelationshipIntervalAnchor",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0084), ElementsDictionaryEntry("Minimum Hours between Fractions", "MinimumHoursBetweenFractions",  "FD", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0085), ElementsDictionaryEntry("Intended Fraction Start Time", "IntendedFractionStartTime",  "TM", "1-n"));
    public_dictionary.emplace(Tag(0x3010, 0x0086), ElementsDictionaryEntry("Intended Start Day of Week", "IntendedStartDayOfWeek",  "LT", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0087), ElementsDictionaryEntry("Weekday Fraction Pattern Sequence", "WeekdayFractionPatternSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0088), ElementsDictionaryEntry("Delivery Time Structure Code Sequence", "DeliveryTimeStructureCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0089), ElementsDictionaryEntry("Treatment Site Modifier Code Sequence", "TreatmentSiteModifierCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0090), ElementsDictionaryEntry("Robotic Base Location Indicator", "RoboticBaseLocationIndicator",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0091), ElementsDictionaryEntry("Robotic Path Node Set Code Sequence", "RoboticPathNodeSetCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0092), ElementsDictionaryEntry("Robotic Node Identifier", "RoboticNodeIdentifier",  "UL", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0093), ElementsDictionaryEntry("RT Treatment Source Coordinates", "RTTreatmentSourceCoordinates",  "FD", "3"));
    public_dictionary.emplace(Tag(0x3010, 0x0094), ElementsDictionaryEntry("Radiation Source Coordinate SystemYaw Angle", "RadiationSourceCoordinateSystemYawAngle",  "FD", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0095), ElementsDictionaryEntry("Radiation Source Coordinate SystemRoll Angle", "RadiationSourceCoordinateSystemRollAngle",  "FD", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0096), ElementsDictionaryEntry("Radiation Source Coordinate System Pitch Angle", "RadiationSourceCoordinateSystemPitchAngle",  "FD", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0097), ElementsDictionaryEntry("Robotic Path Control Point Sequence", "RoboticPathControlPointSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0098), ElementsDictionaryEntry("Tomotherapeutic Control Point Sequence", "TomotherapeuticControlPointSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3010, 0x0099), ElementsDictionaryEntry("Tomotherapeutic Leaf Open Durations", "TomotherapeuticLeafOpenDurations",  "FD", "1-n"));
    public_dictionary.emplace(Tag(0x3010, 0x009a), ElementsDictionaryEntry("Tomotherapeutic Leaf Initial Closed Durations", "TomotherapeuticLeafInitialClosedDurations",  "FD", "1-n"));
    public_dictionary.emplace(Tag(0x3010, 0x00a0), ElementsDictionaryEntry("Conceptual Volume Identification Sequence", "ConceptualVolumeIdentificationSequence",  "SQ", "1"));

    public_tags.emplace("RadiobiologicalDoseEffectSequence", Tag(0x3010, 0x0001));
    public_tags.emplace("RadiobiologicalDoseEffectFlag", Tag(0x3010, 0x0002));
    public_tags.emplace("EffectiveDoseCalculationMethodCategoryCodeSequence", Tag(0x3010, 0x0003));
    public_tags.emplace("EffectiveDoseCalculationMethodCodeSequence", Tag(0x3010, 0x0004));
    public_tags.emplace("EffectiveDoseCalculationMethodDescription", Tag(0x3010, 0x0005));
    public_tags.emplace("ConceptualVolumeUID", Tag(0x3010, 0x0006));
    public_tags.emplace("OriginatingSOPInstanceReferenceSequence", Tag(0x3010, 0x0007));
    public_tags.emplace("ConceptualVolumeConstituentSequence", Tag(0x3010, 0x0008));
    public_tags.emplace("EquivalentConceptualVolumeInstanceReferenceSequence", Tag(0x3010, 0x0009));
    public_tags.emplace("EquivalentConceptualVolumesSequence", Tag(0x3010, 0x000a));
    public_tags.emplace("ReferencedConceptualVolumeUID", Tag(0x3010, 0x000b));
    public_tags.emplace("ConceptualVolumeCombinationExpression", Tag(0x3010, 0x000c));
    public_tags.emplace("ConceptualVolumeConstituentIndex", Tag(0x3010, 0x000d));
    public_tags.emplace("ConceptualVolumeCombinationFlag", Tag(0x3010, 0x000e));
    public_tags.emplace("ConceptualVolumeCombinationDescription", Tag(0x3010, 0x000f));
    public_tags.emplace("ConceptualVolumeSegmentationDefinedFlag", Tag(0x3010, 0x0010));
    public_tags.emplace("ConceptualVolumeSegmentationReferenceSequence", Tag(0x3010, 0x0011));
    public_tags.emplace("ConceptualVolumeConstituentSegmentationReferenceSequence", Tag(0x3010, 0x0012));
    public_tags.emplace("ConstituentConceptualVolumeUID", Tag(0x3010, 0x0013));
    public_tags.emplace("DerivationConceptualVolumeSequence", Tag(0x3010, 0x0014));
    public_tags.emplace("SourceConceptualVolumeUID", Tag(0x3010, 0x0015));
    public_tags.emplace("ConceptualVolumeDerivationAlgorithmSequence", Tag(0x3010, 0x0016));
    public_tags.emplace("ConceptualVolumeDescription", Tag(0x3010, 0x0017));
    public_tags.emplace("SourceConceptualVolumeSequence", Tag(0x3010, 0x0018));
    public_tags.emplace("AuthorIdentificationSequence", Tag(0x3010, 0x0019));
    public_tags.emplace("ManufacturerModelVersion", Tag(0x3010, 0x001a));
    public_tags.emplace("DeviceAlternateIdentifier", Tag(0x3010, 0x001b));
    public_tags.emplace("DeviceAlternateIdentifierType", Tag(0x3010, 0x001c));
    public_tags.emplace("DeviceAlternateIdentifierFormat", Tag(0x3010, 0x001d));
    public_tags.emplace("SegmentationCreationTemplateLabel", Tag(0x3010, 0x001e));
    public_tags.emplace("SegmentationTemplateUID", Tag(0x3010, 0x001f));
    public_tags.emplace("ReferencedSegmentReferenceIndex", Tag(0x3010, 0x0020));
    public_tags.emplace("SegmentReferenceSequence", Tag(0x3010, 0x0021));
    public_tags.emplace("SegmentReferenceIndex", Tag(0x3010, 0x0022));
    public_tags.emplace("DirectSegmentReferenceSequence", Tag(0x3010, 0x0023));
    public_tags.emplace("CombinationSegmentReferenceSequence", Tag(0x3010, 0x0024));
    public_tags.emplace("ConceptualVolumeSequence", Tag(0x3010, 0x0025));
    public_tags.emplace("SegmentedRTAccessoryDeviceSequence", Tag(0x3010, 0x0026));
    public_tags.emplace("SegmentCharacteristicsSequence", Tag(0x3010, 0x0027));
    public_tags.emplace("RelatedSegmentCharacteristicsSequence", Tag(0x3010, 0x0028));
    public_tags.emplace("SegmentCharacteristicsPrecedence", Tag(0x3010, 0x0029));
    public_tags.emplace("RTSegmentAnnotationSequence", Tag(0x3010, 0x002a));
    public_tags.emplace("SegmentAnnotationCategoryCodeSequence", Tag(0x3010, 0x002b));
    public_tags.emplace("SegmentAnnotationTypeCodeSequence", Tag(0x3010, 0x002c));
    public_tags.emplace("DeviceLabel", Tag(0x3010, 0x002d));
    public_tags.emplace("DeviceTypeCodeSequence", Tag(0x3010, 0x002e));
    public_tags.emplace("SegmentAnnotationTypeModifierCodeSequence", Tag(0x3010, 0x002f));
    public_tags.emplace("PatientEquipmentRelationshipCodeSequence", Tag(0x3010, 0x0030));
    public_tags.emplace("ReferencedFiducialsUID", Tag(0x3010, 0x0031));
    public_tags.emplace("PatientTreatmentOrientationSequence", Tag(0x3010, 0x0032));
    public_tags.emplace("UserContentLabel", Tag(0x3010, 0x0033));
    public_tags.emplace("UserContentLongLabel", Tag(0x3010, 0x0034));
    public_tags.emplace("EntityLabel", Tag(0x3010, 0x0035));
    public_tags.emplace("EntityName", Tag(0x3010, 0x0036));
    public_tags.emplace("EntityDescription", Tag(0x3010, 0x0037));
    public_tags.emplace("EntityLongLabel", Tag(0x3010, 0x0038));
    public_tags.emplace("DeviceIndex", Tag(0x3010, 0x0039));
    public_tags.emplace("RTTreatmentPhaseIndex", Tag(0x3010, 0x003a));
    public_tags.emplace("RTTreatmentPhaseUID", Tag(0x3010, 0x003b));
    public_tags.emplace("RTPrescriptionIndex", Tag(0x3010, 0x003c));
    public_tags.emplace("RTSegmentAnnotationIndex", Tag(0x3010, 0x003d));
    public_tags.emplace("BasisRTTreatmentPhaseIndex", Tag(0x3010, 0x003e));
    public_tags.emplace("RelatedRTTreatmentPhaseIndex", Tag(0x3010, 0x003f));
    public_tags.emplace("ReferencedRTTreatmentPhaseIndex", Tag(0x3010, 0x0040));
    public_tags.emplace("ReferencedRTPrescriptionIndex", Tag(0x3010, 0x0041));
    public_tags.emplace("ReferencedParentRTPrescriptionIndex", Tag(0x3010, 0x0042));
    public_tags.emplace("ManufacturerDeviceIdentifier", Tag(0x3010, 0x0043));
    public_tags.emplace("InstanceLevelReferencedPerformedProcedureStepSequence", Tag(0x3010, 0x0044));
    public_tags.emplace("RTTreatmentPhaseIntentPresenceFlag", Tag(0x3010, 0x0045));
    public_tags.emplace("RadiotherapyTreatmentType", Tag(0x3010, 0x0046));
    public_tags.emplace("TeletherapyRadiationType", Tag(0x3010, 0x0047));
    public_tags.emplace("BrachytherapySourceType", Tag(0x3010, 0x0048));
    public_tags.emplace("ReferencedRTTreatmentPhaseSequence", Tag(0x3010, 0x0049));
    public_tags.emplace("ReferencedDirectSegmentInstanceSequence", Tag(0x3010, 0x004a));
    public_tags.emplace("IntendedRTTreatmentPhaseSequence", Tag(0x3010, 0x004b));
    public_tags.emplace("IntendedPhaseStartDate", Tag(0x3010, 0x004c));
    public_tags.emplace("IntendedPhaseEndDate", Tag(0x3010, 0x004d));
    public_tags.emplace("RTTreatmentPhaseIntervalSequence", Tag(0x3010, 0x004e));
    public_tags.emplace("TemporalRelationshipIntervalAnchor", Tag(0x3010, 0x004f));
    public_tags.emplace("MinimumNumberOfIntervalDays", Tag(0x3010, 0x0050));
    public_tags.emplace("MaximumNumberOfIntervalDays", Tag(0x3010, 0x0051));
    public_tags.emplace("PertinentSOPClassesInStudy", Tag(0x3010, 0x0052));
    public_tags.emplace("PertinentSOPClassesInSeries", Tag(0x3010, 0x0053));
    public_tags.emplace("RTPrescriptionLabel", Tag(0x3010, 0x0054));
    public_tags.emplace("RTPhysicianIntentPredecessorSequence", Tag(0x3010, 0x0055));
    public_tags.emplace("RTTreatmentApproachLabel", Tag(0x3010, 0x0056));
    public_tags.emplace("RTPhysicianIntentSequence", Tag(0x3010, 0x0057));
    public_tags.emplace("RTPhysicianIntentIndex", Tag(0x3010, 0x0058));
    public_tags.emplace("RTTreatmentIntentType", Tag(0x3010, 0x0059));
    public_tags.emplace("RTPhysicianIntentNarrative", Tag(0x3010, 0x005a));
    public_tags.emplace("RTProtocolCodeSequence", Tag(0x3010, 0x005b));
    public_tags.emplace("ReasonForSuperseding", Tag(0x3010, 0x005c));
    public_tags.emplace("RTDiagnosisCodeSequence", Tag(0x3010, 0x005d));
    public_tags.emplace("ReferencedRTPhysicianIntentIndex", Tag(0x3010, 0x005e));
    public_tags.emplace("RTPhysicianIntentInputInstanceSequence", Tag(0x3010, 0x005f));
    public_tags.emplace("RTAnatomicPrescriptionSequence", Tag(0x3010, 0x0060));
    public_tags.emplace("PriorTreatmentDoseDescription", Tag(0x3010, 0x0061));
    public_tags.emplace("PriorTreatmentReferenceSequence", Tag(0x3010, 0x0062));
    public_tags.emplace("DosimetricObjectiveEvaluationScope", Tag(0x3010, 0x0063));
    public_tags.emplace("TherapeuticRoleCategoryCodeSequence", Tag(0x3010, 0x0064));
    public_tags.emplace("TherapeuticRoleTypeCodeSequence", Tag(0x3010, 0x0065));
    public_tags.emplace("ConceptualVolumeOptimizationPrecedence", Tag(0x3010, 0x0066));
    public_tags.emplace("ConceptualVolumeCategoryCodeSequence", Tag(0x3010, 0x0067));
    public_tags.emplace("ConceptualVolumeBlockingConstraint", Tag(0x3010, 0x0068));
    public_tags.emplace("ConceptualVolumeTypeCodeSequence", Tag(0x3010, 0x0069));
    public_tags.emplace("ConceptualVolumeTypeModifierCodeSequence", Tag(0x3010, 0x006a));
    public_tags.emplace("RTPrescriptionSequence", Tag(0x3010, 0x006b));
    public_tags.emplace("DosimetricObjectiveSequence", Tag(0x3010, 0x006c));
    public_tags.emplace("DosimetricObjectiveTypeCodeSequence", Tag(0x3010, 0x006d));
    public_tags.emplace("DosimetricObjectiveUID", Tag(0x3010, 0x006e));
    public_tags.emplace("ReferencedDosimetricObjectiveUID", Tag(0x3010, 0x006f));
    public_tags.emplace("DosimetricObjectiveParameterSequence", Tag(0x3010, 0x0070));
    public_tags.emplace("ReferencedDosimetricObjectivesSequence", Tag(0x3010, 0x0071));
    public_tags.emplace("AbsoluteDosimetricObjectiveFlag", Tag(0x3010, 0x0073));
    public_tags.emplace("DosimetricObjectiveWeight", Tag(0x3010, 0x0074));
    public_tags.emplace("DosimetricObjectivePurpose", Tag(0x3010, 0x0075));
    public_tags.emplace("PlanningInputInformationSequence", Tag(0x3010, 0x0076));
    public_tags.emplace("TreatmentSite", Tag(0x3010, 0x0077));
    public_tags.emplace("TreatmentSiteCodeSequence", Tag(0x3010, 0x0078));
    public_tags.emplace("FractionPatternSequence", Tag(0x3010, 0x0079));
    public_tags.emplace("TreatmentTechniqueNotes", Tag(0x3010, 0x007a));
    public_tags.emplace("PrescriptionNotes", Tag(0x3010, 0x007b));
    public_tags.emplace("NumberOfIntervalFractions", Tag(0x3010, 0x007c));
    public_tags.emplace("NumberOfFractions", Tag(0x3010, 0x007d));
    public_tags.emplace("IntendedDeliveryDuration", Tag(0x3010, 0x007e));
    public_tags.emplace("FractionationNotes", Tag(0x3010, 0x007f));
    public_tags.emplace("RTTreatmentTechniqueCodeSequence", Tag(0x3010, 0x0080));
    public_tags.emplace("PrescriptionNotesSequence", Tag(0x3010, 0x0081));
    public_tags.emplace("FractionBasedRelationshipSequence", Tag(0x3010, 0x0082));
    public_tags.emplace("FractionBasedRelationshipIntervalAnchor", Tag(0x3010, 0x0083));
    public_tags.emplace("MinimumHoursBetweenFractions", Tag(0x3010, 0x0084));
    public_tags.emplace("IntendedFractionStartTime", Tag(0x3010, 0x0085));
    public_tags.emplace("IntendedStartDayOfWeek", Tag(0x3010, 0x0086));
    public_tags.emplace("WeekdayFractionPatternSequence", Tag(0x3010, 0x0087));
    public_tags.emplace("DeliveryTimeStructureCodeSequence", Tag(0x3010, 0x0088));
    public_tags.emplace("TreatmentSiteModifierCodeSequence", Tag(0x3010, 0x0089));
    public_tags.emplace("RoboticBaseLocationIndicator", Tag(0x3010, 0x0090));
    public_tags.emplace("RoboticPathNodeSetCodeSequence", Tag(0x3010, 0x0091));
    public_tags.emplace("RoboticNodeIdentifier", Tag(0x3010, 0x0092));
    public_tags.emplace("RTTreatmentSourceCoordinates", Tag(0x3010, 0x0093));
    public_tags.emplace("RadiationSourceCoordinateSystemYawAngle", Tag(0x3010, 0x0094));
    public_tags.emplace("RadiationSourceCoordinateSystemRollAngle", Tag(0x3010, 0x0095));
    public_tags.emplace("RadiationSourceCoordinateSystemPitchAngle", Tag(0x3010, 0x0096));
    public_tags.emplace("RoboticPathControlPointSequence", Tag(0x3010, 0x0097));
    public_tags.emplace("TomotherapeuticControlPointSequence", Tag(0x3010, 0x0098));
    public_tags.emplace("TomotherapeuticLeafOpenDurations", Tag(0x3010, 0x0099));
    public_tags.emplace("TomotherapeuticLeafInitialClosedDurations", Tag(0x3010, 0x009a));
    public_tags.emplace("ConceptualVolumeIdentificationSequence", Tag(0x3010, 0x00a0));
}

}

}