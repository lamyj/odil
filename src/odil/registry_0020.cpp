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

void update_0020(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0020, 0x000d), ElementsDictionaryEntry("Study Instance UID", "StudyInstanceUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x000e), ElementsDictionaryEntry("Series Instance UID", "SeriesInstanceUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0010), ElementsDictionaryEntry("Study ID", "StudyID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0011), ElementsDictionaryEntry("Series Number", "SeriesNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0012), ElementsDictionaryEntry("Acquisition Number", "AcquisitionNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0013), ElementsDictionaryEntry("Instance Number", "InstanceNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0014), ElementsDictionaryEntry("Isotope Number", "IsotopeNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0015), ElementsDictionaryEntry("Phase Number", "PhaseNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0016), ElementsDictionaryEntry("Interval Number", "IntervalNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0017), ElementsDictionaryEntry("Time Slot Number", "TimeSlotNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0018), ElementsDictionaryEntry("Angle Number", "AngleNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0019), ElementsDictionaryEntry("Item Number", "ItemNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0020), ElementsDictionaryEntry("Patient Orientation", "PatientOrientation",  "CS", "2"));
    public_dictionary.emplace(Tag(0x0020, 0x0022), ElementsDictionaryEntry("Overlay Number", "OverlayNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0024), ElementsDictionaryEntry("Curve Number", "CurveNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0026), ElementsDictionaryEntry("LUT Number", "LUTNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0030), ElementsDictionaryEntry("Image Position", "ImagePosition",  "DS", "3"));
    public_dictionary.emplace(Tag(0x0020, 0x0032), ElementsDictionaryEntry("Image Position (Patient)", "ImagePositionPatient",  "DS", "3"));
    public_dictionary.emplace(Tag(0x0020, 0x0035), ElementsDictionaryEntry("Image Orientation", "ImageOrientation",  "DS", "6"));
    public_dictionary.emplace(Tag(0x0020, 0x0037), ElementsDictionaryEntry("Image Orientation (Patient)", "ImageOrientationPatient",  "DS", "6"));
    public_dictionary.emplace(Tag(0x0020, 0x0050), ElementsDictionaryEntry("Location", "Location",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0052), ElementsDictionaryEntry("Frame of Reference UID", "FrameOfReferenceUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0060), ElementsDictionaryEntry("Laterality", "Laterality",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0062), ElementsDictionaryEntry("Image Laterality", "ImageLaterality",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0070), ElementsDictionaryEntry("Image Geometry Type", "ImageGeometryType",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0080), ElementsDictionaryEntry("Masking Image", "MaskingImage",  "CS", "1-n"));
    public_dictionary.emplace(Tag(0x0020, 0x00aa), ElementsDictionaryEntry("Report Number", "ReportNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0100), ElementsDictionaryEntry("Temporal Position Identifier", "TemporalPositionIdentifier",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0105), ElementsDictionaryEntry("Number of Temporal Positions", "NumberOfTemporalPositions",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0110), ElementsDictionaryEntry("Temporal Resolution", "TemporalResolution",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0200), ElementsDictionaryEntry("Synchronization Frame of Reference UID", "SynchronizationFrameOfReferenceUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x0242), ElementsDictionaryEntry("SOP Instance UID of Concatenation Source", "SOPInstanceUIDOfConcatenationSource",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1000), ElementsDictionaryEntry("Series in Study", "SeriesInStudy",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1001), ElementsDictionaryEntry("Acquisitions in Series", "AcquisitionsInSeries",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1002), ElementsDictionaryEntry("Images in Acquisition", "ImagesInAcquisition",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1003), ElementsDictionaryEntry("Images in Series", "ImagesInSeries",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1004), ElementsDictionaryEntry("Acquisitions in Study", "AcquisitionsInStudy",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1005), ElementsDictionaryEntry("Images in Study", "ImagesInStudy",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1020), ElementsDictionaryEntry("Reference", "Reference",  "LO", "1-n"));
    public_dictionary.emplace(Tag(0x0020, 0x103f), ElementsDictionaryEntry("Target Position Reference Indicator", "TargetPositionReferenceIndicator",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1040), ElementsDictionaryEntry("Position Reference Indicator", "PositionReferenceIndicator",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1041), ElementsDictionaryEntry("Slice Location", "SliceLocation",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1070), ElementsDictionaryEntry("Other Study Numbers", "OtherStudyNumbers",  "IS", "1-n"));
    public_dictionary.emplace(Tag(0x0020, 0x1200), ElementsDictionaryEntry("Number of Patient Related Studies", "NumberOfPatientRelatedStudies",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1202), ElementsDictionaryEntry("Number of Patient Related Series", "NumberOfPatientRelatedSeries",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1204), ElementsDictionaryEntry("Number of Patient Related Instances", "NumberOfPatientRelatedInstances",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1206), ElementsDictionaryEntry("Number of Study Related Series", "NumberOfStudyRelatedSeries",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1208), ElementsDictionaryEntry("Number of Study Related Instances", "NumberOfStudyRelatedInstances",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x1209), ElementsDictionaryEntry("Number of Series Related Instances", "NumberOfSeriesRelatedInstances",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x3401), ElementsDictionaryEntry("Modifying Device ID", "ModifyingDeviceID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x3402), ElementsDictionaryEntry("Modified Image ID", "ModifiedImageID",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x3403), ElementsDictionaryEntry("Modified Image Date", "ModifiedImageDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x3404), ElementsDictionaryEntry("Modifying Device Manufacturer", "ModifyingDeviceManufacturer",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x3405), ElementsDictionaryEntry("Modified Image Time", "ModifiedImageTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x3406), ElementsDictionaryEntry("Modified Image Description", "ModifiedImageDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x4000), ElementsDictionaryEntry("Image Comments", "ImageComments",  "LT", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x5000), ElementsDictionaryEntry("Original Image Identification", "OriginalImageIdentification",  "AT", "1-n"));
    public_dictionary.emplace(Tag(0x0020, 0x5002), ElementsDictionaryEntry("Original Image Identification Nomenclature", "OriginalImageIdentificationNomenclature",  "LO", "1-n"));
    public_dictionary.emplace(Tag(0x0020, 0x9056), ElementsDictionaryEntry("Stack ID", "StackID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9057), ElementsDictionaryEntry("In-Stack Position Number", "InStackPositionNumber",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9071), ElementsDictionaryEntry("Frame Anatomy Sequence", "FrameAnatomySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9072), ElementsDictionaryEntry("Frame Laterality", "FrameLaterality",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9111), ElementsDictionaryEntry("Frame Content Sequence", "FrameContentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9113), ElementsDictionaryEntry("Plane Position Sequence", "PlanePositionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9116), ElementsDictionaryEntry("Plane Orientation Sequence", "PlaneOrientationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9128), ElementsDictionaryEntry("Temporal Position Index", "TemporalPositionIndex",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9153), ElementsDictionaryEntry("Nominal Cardiac Trigger Delay Time", "NominalCardiacTriggerDelayTime",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9154), ElementsDictionaryEntry("Nominal Cardiac Trigger Time Prior To R-Peak", "NominalCardiacTriggerTimePriorToRPeak",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9155), ElementsDictionaryEntry("Actual Cardiac Trigger Time Prior To R-Peak", "ActualCardiacTriggerTimePriorToRPeak",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9156), ElementsDictionaryEntry("Frame Acquisition Number", "FrameAcquisitionNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9157), ElementsDictionaryEntry("Dimension Index Values", "DimensionIndexValues",  "UL", "1-n"));
    public_dictionary.emplace(Tag(0x0020, 0x9158), ElementsDictionaryEntry("Frame Comments", "FrameComments",  "LT", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9161), ElementsDictionaryEntry("Concatenation UID", "ConcatenationUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9162), ElementsDictionaryEntry("In-concatenation Number", "InConcatenationNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9163), ElementsDictionaryEntry("In-concatenation Total Number", "InConcatenationTotalNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9164), ElementsDictionaryEntry("Dimension Organization UID", "DimensionOrganizationUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9165), ElementsDictionaryEntry("Dimension Index Pointer", "DimensionIndexPointer",  "AT", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9167), ElementsDictionaryEntry("Functional Group Pointer", "FunctionalGroupPointer",  "AT", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9170), ElementsDictionaryEntry("Unassigned Shared Converted Attributes Sequence", "UnassignedSharedConvertedAttributesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9171), ElementsDictionaryEntry("Unassigned Per-Frame Converted Attributes Sequence", "UnassignedPerFrameConvertedAttributesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9172), ElementsDictionaryEntry("Conversion Source Attributes Sequence", "ConversionSourceAttributesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9213), ElementsDictionaryEntry("Dimension Index Private Creator", "DimensionIndexPrivateCreator",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9221), ElementsDictionaryEntry("Dimension Organization Sequence", "DimensionOrganizationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9222), ElementsDictionaryEntry("Dimension Index Sequence", "DimensionIndexSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9228), ElementsDictionaryEntry("Concatenation Frame Offset Number", "ConcatenationFrameOffsetNumber",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9238), ElementsDictionaryEntry("Functional Group Private Creator", "FunctionalGroupPrivateCreator",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9241), ElementsDictionaryEntry("Nominal Percentage of Cardiac Phase", "NominalPercentageOfCardiacPhase",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9245), ElementsDictionaryEntry("Nominal Percentage of Respiratory Phase", "NominalPercentageOfRespiratoryPhase",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9246), ElementsDictionaryEntry("Starting Respiratory Amplitude", "StartingRespiratoryAmplitude",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9247), ElementsDictionaryEntry("Starting Respiratory Phase", "StartingRespiratoryPhase",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9248), ElementsDictionaryEntry("Ending Respiratory Amplitude", "EndingRespiratoryAmplitude",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9249), ElementsDictionaryEntry("Ending Respiratory Phase", "EndingRespiratoryPhase",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9250), ElementsDictionaryEntry("Respiratory Trigger Type", "RespiratoryTriggerType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9251), ElementsDictionaryEntry("R-R Interval Time Nominal", "RRIntervalTimeNominal",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9252), ElementsDictionaryEntry("Actual Cardiac Trigger Delay Time", "ActualCardiacTriggerDelayTime",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9253), ElementsDictionaryEntry("Respiratory Synchronization Sequence", "RespiratorySynchronizationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9254), ElementsDictionaryEntry("Respiratory Interval Time", "RespiratoryIntervalTime",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9255), ElementsDictionaryEntry("Nominal Respiratory Trigger Delay Time", "NominalRespiratoryTriggerDelayTime",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9256), ElementsDictionaryEntry("Respiratory Trigger Delay Threshold", "RespiratoryTriggerDelayThreshold",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9257), ElementsDictionaryEntry("Actual Respiratory Trigger Delay Time", "ActualRespiratoryTriggerDelayTime",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9301), ElementsDictionaryEntry("Image Position (Volume)", "ImagePositionVolume",  "FD", "3"));
    public_dictionary.emplace(Tag(0x0020, 0x9302), ElementsDictionaryEntry("Image Orientation (Volume)", "ImageOrientationVolume",  "FD", "6"));
    public_dictionary.emplace(Tag(0x0020, 0x9307), ElementsDictionaryEntry("Ultrasound Acquisition Geometry", "UltrasoundAcquisitionGeometry",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9308), ElementsDictionaryEntry("Apex Position", "ApexPosition",  "FD", "3"));
    public_dictionary.emplace(Tag(0x0020, 0x9309), ElementsDictionaryEntry("Volume to Transducer Mapping Matrix", "VolumeToTransducerMappingMatrix",  "FD", "16"));
    public_dictionary.emplace(Tag(0x0020, 0x930a), ElementsDictionaryEntry("Volume to Table Mapping Matrix", "VolumeToTableMappingMatrix",  "FD", "16"));
    public_dictionary.emplace(Tag(0x0020, 0x930b), ElementsDictionaryEntry("Volume to Transducer Relationship", "VolumeToTransducerRelationship",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x930c), ElementsDictionaryEntry("Patient Frame of Reference Source", "PatientFrameOfReferenceSource",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x930d), ElementsDictionaryEntry("Temporal Position Time Offset", "TemporalPositionTimeOffset",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x930e), ElementsDictionaryEntry("Plane Position (Volume) Sequence", "PlanePositionVolumeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x930f), ElementsDictionaryEntry("Plane Orientation (Volume) Sequence", "PlaneOrientationVolumeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9310), ElementsDictionaryEntry("Temporal Position Sequence", "TemporalPositionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9311), ElementsDictionaryEntry("Dimension Organization Type", "DimensionOrganizationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9312), ElementsDictionaryEntry("Volume Frame of Reference UID", "VolumeFrameOfReferenceUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9313), ElementsDictionaryEntry("Table Frame of Reference UID", "TableFrameOfReferenceUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9421), ElementsDictionaryEntry("Dimension Description Label", "DimensionDescriptionLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9450), ElementsDictionaryEntry("Patient Orientation in Frame Sequence", "PatientOrientationInFrameSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9453), ElementsDictionaryEntry("Frame Label", "FrameLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9518), ElementsDictionaryEntry("Acquisition Index", "AcquisitionIndex",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0020, 0x9529), ElementsDictionaryEntry("Contributing SOP Instances Reference Sequence", "ContributingSOPInstancesReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0020, 0x9536), ElementsDictionaryEntry("Reconstruction Index", "ReconstructionIndex",  "US", "1"));

    public_tags.emplace("StudyInstanceUID", Tag(0x0020, 0x000d));
    public_tags.emplace("SeriesInstanceUID", Tag(0x0020, 0x000e));
    public_tags.emplace("StudyID", Tag(0x0020, 0x0010));
    public_tags.emplace("SeriesNumber", Tag(0x0020, 0x0011));
    public_tags.emplace("AcquisitionNumber", Tag(0x0020, 0x0012));
    public_tags.emplace("InstanceNumber", Tag(0x0020, 0x0013));
    public_tags.emplace("IsotopeNumber", Tag(0x0020, 0x0014));
    public_tags.emplace("PhaseNumber", Tag(0x0020, 0x0015));
    public_tags.emplace("IntervalNumber", Tag(0x0020, 0x0016));
    public_tags.emplace("TimeSlotNumber", Tag(0x0020, 0x0017));
    public_tags.emplace("AngleNumber", Tag(0x0020, 0x0018));
    public_tags.emplace("ItemNumber", Tag(0x0020, 0x0019));
    public_tags.emplace("PatientOrientation", Tag(0x0020, 0x0020));
    public_tags.emplace("OverlayNumber", Tag(0x0020, 0x0022));
    public_tags.emplace("CurveNumber", Tag(0x0020, 0x0024));
    public_tags.emplace("LUTNumber", Tag(0x0020, 0x0026));
    public_tags.emplace("ImagePosition", Tag(0x0020, 0x0030));
    public_tags.emplace("ImagePositionPatient", Tag(0x0020, 0x0032));
    public_tags.emplace("ImageOrientation", Tag(0x0020, 0x0035));
    public_tags.emplace("ImageOrientationPatient", Tag(0x0020, 0x0037));
    public_tags.emplace("Location", Tag(0x0020, 0x0050));
    public_tags.emplace("FrameOfReferenceUID", Tag(0x0020, 0x0052));
    public_tags.emplace("Laterality", Tag(0x0020, 0x0060));
    public_tags.emplace("ImageLaterality", Tag(0x0020, 0x0062));
    public_tags.emplace("ImageGeometryType", Tag(0x0020, 0x0070));
    public_tags.emplace("MaskingImage", Tag(0x0020, 0x0080));
    public_tags.emplace("ReportNumber", Tag(0x0020, 0x00aa));
    public_tags.emplace("TemporalPositionIdentifier", Tag(0x0020, 0x0100));
    public_tags.emplace("NumberOfTemporalPositions", Tag(0x0020, 0x0105));
    public_tags.emplace("TemporalResolution", Tag(0x0020, 0x0110));
    public_tags.emplace("SynchronizationFrameOfReferenceUID", Tag(0x0020, 0x0200));
    public_tags.emplace("SOPInstanceUIDOfConcatenationSource", Tag(0x0020, 0x0242));
    public_tags.emplace("SeriesInStudy", Tag(0x0020, 0x1000));
    public_tags.emplace("AcquisitionsInSeries", Tag(0x0020, 0x1001));
    public_tags.emplace("ImagesInAcquisition", Tag(0x0020, 0x1002));
    public_tags.emplace("ImagesInSeries", Tag(0x0020, 0x1003));
    public_tags.emplace("AcquisitionsInStudy", Tag(0x0020, 0x1004));
    public_tags.emplace("ImagesInStudy", Tag(0x0020, 0x1005));
    public_tags.emplace("Reference", Tag(0x0020, 0x1020));
    public_tags.emplace("TargetPositionReferenceIndicator", Tag(0x0020, 0x103f));
    public_tags.emplace("PositionReferenceIndicator", Tag(0x0020, 0x1040));
    public_tags.emplace("SliceLocation", Tag(0x0020, 0x1041));
    public_tags.emplace("OtherStudyNumbers", Tag(0x0020, 0x1070));
    public_tags.emplace("NumberOfPatientRelatedStudies", Tag(0x0020, 0x1200));
    public_tags.emplace("NumberOfPatientRelatedSeries", Tag(0x0020, 0x1202));
    public_tags.emplace("NumberOfPatientRelatedInstances", Tag(0x0020, 0x1204));
    public_tags.emplace("NumberOfStudyRelatedSeries", Tag(0x0020, 0x1206));
    public_tags.emplace("NumberOfStudyRelatedInstances", Tag(0x0020, 0x1208));
    public_tags.emplace("NumberOfSeriesRelatedInstances", Tag(0x0020, 0x1209));
    public_tags.emplace("ModifyingDeviceID", Tag(0x0020, 0x3401));
    public_tags.emplace("ModifiedImageID", Tag(0x0020, 0x3402));
    public_tags.emplace("ModifiedImageDate", Tag(0x0020, 0x3403));
    public_tags.emplace("ModifyingDeviceManufacturer", Tag(0x0020, 0x3404));
    public_tags.emplace("ModifiedImageTime", Tag(0x0020, 0x3405));
    public_tags.emplace("ModifiedImageDescription", Tag(0x0020, 0x3406));
    public_tags.emplace("ImageComments", Tag(0x0020, 0x4000));
    public_tags.emplace("OriginalImageIdentification", Tag(0x0020, 0x5000));
    public_tags.emplace("OriginalImageIdentificationNomenclature", Tag(0x0020, 0x5002));
    public_tags.emplace("StackID", Tag(0x0020, 0x9056));
    public_tags.emplace("InStackPositionNumber", Tag(0x0020, 0x9057));
    public_tags.emplace("FrameAnatomySequence", Tag(0x0020, 0x9071));
    public_tags.emplace("FrameLaterality", Tag(0x0020, 0x9072));
    public_tags.emplace("FrameContentSequence", Tag(0x0020, 0x9111));
    public_tags.emplace("PlanePositionSequence", Tag(0x0020, 0x9113));
    public_tags.emplace("PlaneOrientationSequence", Tag(0x0020, 0x9116));
    public_tags.emplace("TemporalPositionIndex", Tag(0x0020, 0x9128));
    public_tags.emplace("NominalCardiacTriggerDelayTime", Tag(0x0020, 0x9153));
    public_tags.emplace("NominalCardiacTriggerTimePriorToRPeak", Tag(0x0020, 0x9154));
    public_tags.emplace("ActualCardiacTriggerTimePriorToRPeak", Tag(0x0020, 0x9155));
    public_tags.emplace("FrameAcquisitionNumber", Tag(0x0020, 0x9156));
    public_tags.emplace("DimensionIndexValues", Tag(0x0020, 0x9157));
    public_tags.emplace("FrameComments", Tag(0x0020, 0x9158));
    public_tags.emplace("ConcatenationUID", Tag(0x0020, 0x9161));
    public_tags.emplace("InConcatenationNumber", Tag(0x0020, 0x9162));
    public_tags.emplace("InConcatenationTotalNumber", Tag(0x0020, 0x9163));
    public_tags.emplace("DimensionOrganizationUID", Tag(0x0020, 0x9164));
    public_tags.emplace("DimensionIndexPointer", Tag(0x0020, 0x9165));
    public_tags.emplace("FunctionalGroupPointer", Tag(0x0020, 0x9167));
    public_tags.emplace("UnassignedSharedConvertedAttributesSequence", Tag(0x0020, 0x9170));
    public_tags.emplace("UnassignedPerFrameConvertedAttributesSequence", Tag(0x0020, 0x9171));
    public_tags.emplace("ConversionSourceAttributesSequence", Tag(0x0020, 0x9172));
    public_tags.emplace("DimensionIndexPrivateCreator", Tag(0x0020, 0x9213));
    public_tags.emplace("DimensionOrganizationSequence", Tag(0x0020, 0x9221));
    public_tags.emplace("DimensionIndexSequence", Tag(0x0020, 0x9222));
    public_tags.emplace("ConcatenationFrameOffsetNumber", Tag(0x0020, 0x9228));
    public_tags.emplace("FunctionalGroupPrivateCreator", Tag(0x0020, 0x9238));
    public_tags.emplace("NominalPercentageOfCardiacPhase", Tag(0x0020, 0x9241));
    public_tags.emplace("NominalPercentageOfRespiratoryPhase", Tag(0x0020, 0x9245));
    public_tags.emplace("StartingRespiratoryAmplitude", Tag(0x0020, 0x9246));
    public_tags.emplace("StartingRespiratoryPhase", Tag(0x0020, 0x9247));
    public_tags.emplace("EndingRespiratoryAmplitude", Tag(0x0020, 0x9248));
    public_tags.emplace("EndingRespiratoryPhase", Tag(0x0020, 0x9249));
    public_tags.emplace("RespiratoryTriggerType", Tag(0x0020, 0x9250));
    public_tags.emplace("RRIntervalTimeNominal", Tag(0x0020, 0x9251));
    public_tags.emplace("ActualCardiacTriggerDelayTime", Tag(0x0020, 0x9252));
    public_tags.emplace("RespiratorySynchronizationSequence", Tag(0x0020, 0x9253));
    public_tags.emplace("RespiratoryIntervalTime", Tag(0x0020, 0x9254));
    public_tags.emplace("NominalRespiratoryTriggerDelayTime", Tag(0x0020, 0x9255));
    public_tags.emplace("RespiratoryTriggerDelayThreshold", Tag(0x0020, 0x9256));
    public_tags.emplace("ActualRespiratoryTriggerDelayTime", Tag(0x0020, 0x9257));
    public_tags.emplace("ImagePositionVolume", Tag(0x0020, 0x9301));
    public_tags.emplace("ImageOrientationVolume", Tag(0x0020, 0x9302));
    public_tags.emplace("UltrasoundAcquisitionGeometry", Tag(0x0020, 0x9307));
    public_tags.emplace("ApexPosition", Tag(0x0020, 0x9308));
    public_tags.emplace("VolumeToTransducerMappingMatrix", Tag(0x0020, 0x9309));
    public_tags.emplace("VolumeToTableMappingMatrix", Tag(0x0020, 0x930a));
    public_tags.emplace("VolumeToTransducerRelationship", Tag(0x0020, 0x930b));
    public_tags.emplace("PatientFrameOfReferenceSource", Tag(0x0020, 0x930c));
    public_tags.emplace("TemporalPositionTimeOffset", Tag(0x0020, 0x930d));
    public_tags.emplace("PlanePositionVolumeSequence", Tag(0x0020, 0x930e));
    public_tags.emplace("PlaneOrientationVolumeSequence", Tag(0x0020, 0x930f));
    public_tags.emplace("TemporalPositionSequence", Tag(0x0020, 0x9310));
    public_tags.emplace("DimensionOrganizationType", Tag(0x0020, 0x9311));
    public_tags.emplace("VolumeFrameOfReferenceUID", Tag(0x0020, 0x9312));
    public_tags.emplace("TableFrameOfReferenceUID", Tag(0x0020, 0x9313));
    public_tags.emplace("DimensionDescriptionLabel", Tag(0x0020, 0x9421));
    public_tags.emplace("PatientOrientationInFrameSequence", Tag(0x0020, 0x9450));
    public_tags.emplace("FrameLabel", Tag(0x0020, 0x9453));
    public_tags.emplace("AcquisitionIndex", Tag(0x0020, 0x9518));
    public_tags.emplace("ContributingSOPInstancesReferenceSequence", Tag(0x0020, 0x9529));
    public_tags.emplace("ReconstructionIndex", Tag(0x0020, 0x9536));
}

}

}