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

void update_4010(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x4010, 0x0001), ElementsDictionaryEntry("Low Energy Detectors", "LowEnergyDetectors",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x0002), ElementsDictionaryEntry("High Energy Detectors", "HighEnergyDetectors",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x0004), ElementsDictionaryEntry("Detector Geometry Sequence", "DetectorGeometrySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1001), ElementsDictionaryEntry("Threat ROI Voxel Sequence", "ThreatROIVoxelSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1004), ElementsDictionaryEntry("Threat ROI Base", "ThreatROIBase",  "FL", "3"));
    public_dictionary.emplace(Tag(0x4010, 0x1005), ElementsDictionaryEntry("Threat ROI Extents", "ThreatROIExtents",  "FL", "3"));
    public_dictionary.emplace(Tag(0x4010, 0x1006), ElementsDictionaryEntry("Threat ROI Bitmap", "ThreatROIBitmap",  "OB", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1007), ElementsDictionaryEntry("Route Segment ID", "RouteSegmentID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1008), ElementsDictionaryEntry("Gantry Type", "GantryType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1009), ElementsDictionaryEntry("OOI Owner Type", "OOIOwnerType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x100a), ElementsDictionaryEntry("Route Segment Sequence", "RouteSegmentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1010), ElementsDictionaryEntry("Potential Threat Object ID", "PotentialThreatObjectID",  "US", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1011), ElementsDictionaryEntry("Threat Sequence", "ThreatSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1012), ElementsDictionaryEntry("Threat Category", "ThreatCategory",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1013), ElementsDictionaryEntry("Threat Category Description", "ThreatCategoryDescription",  "LT", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1014), ElementsDictionaryEntry("ATD Ability Assessment", "ATDAbilityAssessment",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1015), ElementsDictionaryEntry("ATD Assessment Flag", "ATDAssessmentFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1016), ElementsDictionaryEntry("ATD Assessment Probability", "ATDAssessmentProbability",  "FL", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1017), ElementsDictionaryEntry("Mass", "Mass",  "FL", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1018), ElementsDictionaryEntry("Density", "Density",  "FL", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1019), ElementsDictionaryEntry("Z Effective", "ZEffective",  "FL", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x101a), ElementsDictionaryEntry("Boarding Pass ID", "BoardingPassID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x101b), ElementsDictionaryEntry("Center of Mass", "CenterOfMass",  "FL", "3"));
    public_dictionary.emplace(Tag(0x4010, 0x101c), ElementsDictionaryEntry("Center of PTO", "CenterOfPTO",  "FL", "3"));
    public_dictionary.emplace(Tag(0x4010, 0x101d), ElementsDictionaryEntry("Bounding Polygon", "BoundingPolygon",  "FL", "6-n"));
    public_dictionary.emplace(Tag(0x4010, 0x101e), ElementsDictionaryEntry("Route Segment Start Location ID", "RouteSegmentStartLocationID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x101f), ElementsDictionaryEntry("Route Segment End Location ID", "RouteSegmentEndLocationID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1020), ElementsDictionaryEntry("Route Segment Location ID Type", "RouteSegmentLocationIDType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1021), ElementsDictionaryEntry("Abort Reason", "AbortReason",  "CS", "1-n"));
    public_dictionary.emplace(Tag(0x4010, 0x1023), ElementsDictionaryEntry("Volume of PTO", "VolumeOfPTO",  "FL", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1024), ElementsDictionaryEntry("Abort Flag", "AbortFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1025), ElementsDictionaryEntry("Route Segment Start Time", "RouteSegmentStartTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1026), ElementsDictionaryEntry("Route Segment End Time", "RouteSegmentEndTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1027), ElementsDictionaryEntry("TDR Type", "TDRType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1028), ElementsDictionaryEntry("International Route Segment", "InternationalRouteSegment",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1029), ElementsDictionaryEntry("Threat Detection Algorithm and Version", "ThreatDetectionAlgorithmandVersion",  "LO", "1-n"));
    public_dictionary.emplace(Tag(0x4010, 0x102a), ElementsDictionaryEntry("Assigned Location", "AssignedLocation",  "SH", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x102b), ElementsDictionaryEntry("Alarm Decision Time", "AlarmDecisionTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1031), ElementsDictionaryEntry("Alarm Decision", "AlarmDecision",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1033), ElementsDictionaryEntry("Number of Total Objects", "NumberOfTotalObjects",  "US", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1034), ElementsDictionaryEntry("Number of Alarm Objects", "NumberOfAlarmObjects",  "US", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1037), ElementsDictionaryEntry("PTO Representation Sequence", "PTORepresentationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1038), ElementsDictionaryEntry("ATD Assessment Sequence", "ATDAssessmentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1039), ElementsDictionaryEntry("TIP Type", "TIPType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x103a), ElementsDictionaryEntry("DICOS Version", "DICOSVersion",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1041), ElementsDictionaryEntry("OOI Owner Creation Time", "OOIOwnerCreationTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1042), ElementsDictionaryEntry("OOI Type", "OOIType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1043), ElementsDictionaryEntry("OOI Size", "OOISize",  "FL", "3"));
    public_dictionary.emplace(Tag(0x4010, 0x1044), ElementsDictionaryEntry("Acquisition Status", "AcquisitionStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1045), ElementsDictionaryEntry("Basis Materials Code Sequence", "BasisMaterialsCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1046), ElementsDictionaryEntry("Phantom Type", "PhantomType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1047), ElementsDictionaryEntry("OOI Owner Sequence", "OOIOwnerSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1048), ElementsDictionaryEntry("Scan Type", "ScanType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1051), ElementsDictionaryEntry("Itinerary ID", "ItineraryID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1052), ElementsDictionaryEntry("Itinerary ID Type", "ItineraryIDType",  "SH", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1053), ElementsDictionaryEntry("Itinerary ID Assigning Authority", "ItineraryIDAssigningAuthority",  "LO", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1054), ElementsDictionaryEntry("Route ID", "RouteID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1055), ElementsDictionaryEntry("Route ID Assigning Authority", "RouteIDAssigningAuthority",  "SH", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1056), ElementsDictionaryEntry("Inbound Arrival Type", "InboundArrivalType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1058), ElementsDictionaryEntry("Carrier ID", "CarrierID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1059), ElementsDictionaryEntry("Carrier ID Assigning Authority", "CarrierIDAssigningAuthority",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1060), ElementsDictionaryEntry("Source Orientation", "SourceOrientation",  "FL", "3"));
    public_dictionary.emplace(Tag(0x4010, 0x1061), ElementsDictionaryEntry("Source Position", "SourcePosition",  "FL", "3"));
    public_dictionary.emplace(Tag(0x4010, 0x1062), ElementsDictionaryEntry("Belt Height", "BeltHeight",  "FL", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1064), ElementsDictionaryEntry("Algorithm Routing Code Sequence", "AlgorithmRoutingCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1067), ElementsDictionaryEntry("Transport Classification", "TransportClassification",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1068), ElementsDictionaryEntry("OOI Type Descriptor", "OOITypeDescriptor",  "LT", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1069), ElementsDictionaryEntry("Total Processing Time", "TotalProcessingTime",  "FL", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x106c), ElementsDictionaryEntry("Detector Calibration Data", "DetectorCalibrationData",  "OB", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x106d), ElementsDictionaryEntry("Additional Screening Performed", "AdditionalScreeningPerformed",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x106e), ElementsDictionaryEntry("Additional Inspection Selection Criteria", "AdditionalInspectionSelectionCriteria",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x106f), ElementsDictionaryEntry("Additional Inspection Method Sequence", "AdditionalInspectionMethodSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1070), ElementsDictionaryEntry("AIT Device Type", "AITDeviceType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1071), ElementsDictionaryEntry("QR Measurements Sequence", "QRMeasurementsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1072), ElementsDictionaryEntry("Target Material Sequence", "TargetMaterialSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1073), ElementsDictionaryEntry("SNR Threshold", "SNRThreshold",  "FD", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1075), ElementsDictionaryEntry("Image Scale Representation", "ImageScaleRepresentation",  "DS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1076), ElementsDictionaryEntry("Referenced PTO Sequence", "ReferencedPTOSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1077), ElementsDictionaryEntry("Referenced TDR Instance Sequence", "ReferencedTDRInstanceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1078), ElementsDictionaryEntry("PTO Location Description", "PTOLocationDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x1079), ElementsDictionaryEntry("Anomaly Locator Indicator Sequence", "AnomalyLocatorIndicatorSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x107a), ElementsDictionaryEntry("Anomaly Locator Indicator", "AnomalyLocatorIndicator",  "FL", "3"));
    public_dictionary.emplace(Tag(0x4010, 0x107b), ElementsDictionaryEntry("PTO Region Sequence", "PTORegionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x107c), ElementsDictionaryEntry("Inspection Selection Criteria", "InspectionSelectionCriteria",  "CS", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x107d), ElementsDictionaryEntry("Secondary Inspection Method Sequence", "SecondaryInspectionMethodSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x4010, 0x107e), ElementsDictionaryEntry("PRCS to RCS Orientation", "PRCSToRCSOrientation",  "DS", "6"));

    public_tags.emplace("LowEnergyDetectors", Tag(0x4010, 0x0001));
    public_tags.emplace("HighEnergyDetectors", Tag(0x4010, 0x0002));
    public_tags.emplace("DetectorGeometrySequence", Tag(0x4010, 0x0004));
    public_tags.emplace("ThreatROIVoxelSequence", Tag(0x4010, 0x1001));
    public_tags.emplace("ThreatROIBase", Tag(0x4010, 0x1004));
    public_tags.emplace("ThreatROIExtents", Tag(0x4010, 0x1005));
    public_tags.emplace("ThreatROIBitmap", Tag(0x4010, 0x1006));
    public_tags.emplace("RouteSegmentID", Tag(0x4010, 0x1007));
    public_tags.emplace("GantryType", Tag(0x4010, 0x1008));
    public_tags.emplace("OOIOwnerType", Tag(0x4010, 0x1009));
    public_tags.emplace("RouteSegmentSequence", Tag(0x4010, 0x100a));
    public_tags.emplace("PotentialThreatObjectID", Tag(0x4010, 0x1010));
    public_tags.emplace("ThreatSequence", Tag(0x4010, 0x1011));
    public_tags.emplace("ThreatCategory", Tag(0x4010, 0x1012));
    public_tags.emplace("ThreatCategoryDescription", Tag(0x4010, 0x1013));
    public_tags.emplace("ATDAbilityAssessment", Tag(0x4010, 0x1014));
    public_tags.emplace("ATDAssessmentFlag", Tag(0x4010, 0x1015));
    public_tags.emplace("ATDAssessmentProbability", Tag(0x4010, 0x1016));
    public_tags.emplace("Mass", Tag(0x4010, 0x1017));
    public_tags.emplace("Density", Tag(0x4010, 0x1018));
    public_tags.emplace("ZEffective", Tag(0x4010, 0x1019));
    public_tags.emplace("BoardingPassID", Tag(0x4010, 0x101a));
    public_tags.emplace("CenterOfMass", Tag(0x4010, 0x101b));
    public_tags.emplace("CenterOfPTO", Tag(0x4010, 0x101c));
    public_tags.emplace("BoundingPolygon", Tag(0x4010, 0x101d));
    public_tags.emplace("RouteSegmentStartLocationID", Tag(0x4010, 0x101e));
    public_tags.emplace("RouteSegmentEndLocationID", Tag(0x4010, 0x101f));
    public_tags.emplace("RouteSegmentLocationIDType", Tag(0x4010, 0x1020));
    public_tags.emplace("AbortReason", Tag(0x4010, 0x1021));
    public_tags.emplace("VolumeOfPTO", Tag(0x4010, 0x1023));
    public_tags.emplace("AbortFlag", Tag(0x4010, 0x1024));
    public_tags.emplace("RouteSegmentStartTime", Tag(0x4010, 0x1025));
    public_tags.emplace("RouteSegmentEndTime", Tag(0x4010, 0x1026));
    public_tags.emplace("TDRType", Tag(0x4010, 0x1027));
    public_tags.emplace("InternationalRouteSegment", Tag(0x4010, 0x1028));
    public_tags.emplace("ThreatDetectionAlgorithmandVersion", Tag(0x4010, 0x1029));
    public_tags.emplace("AssignedLocation", Tag(0x4010, 0x102a));
    public_tags.emplace("AlarmDecisionTime", Tag(0x4010, 0x102b));
    public_tags.emplace("AlarmDecision", Tag(0x4010, 0x1031));
    public_tags.emplace("NumberOfTotalObjects", Tag(0x4010, 0x1033));
    public_tags.emplace("NumberOfAlarmObjects", Tag(0x4010, 0x1034));
    public_tags.emplace("PTORepresentationSequence", Tag(0x4010, 0x1037));
    public_tags.emplace("ATDAssessmentSequence", Tag(0x4010, 0x1038));
    public_tags.emplace("TIPType", Tag(0x4010, 0x1039));
    public_tags.emplace("DICOSVersion", Tag(0x4010, 0x103a));
    public_tags.emplace("OOIOwnerCreationTime", Tag(0x4010, 0x1041));
    public_tags.emplace("OOIType", Tag(0x4010, 0x1042));
    public_tags.emplace("OOISize", Tag(0x4010, 0x1043));
    public_tags.emplace("AcquisitionStatus", Tag(0x4010, 0x1044));
    public_tags.emplace("BasisMaterialsCodeSequence", Tag(0x4010, 0x1045));
    public_tags.emplace("PhantomType", Tag(0x4010, 0x1046));
    public_tags.emplace("OOIOwnerSequence", Tag(0x4010, 0x1047));
    public_tags.emplace("ScanType", Tag(0x4010, 0x1048));
    public_tags.emplace("ItineraryID", Tag(0x4010, 0x1051));
    public_tags.emplace("ItineraryIDType", Tag(0x4010, 0x1052));
    public_tags.emplace("ItineraryIDAssigningAuthority", Tag(0x4010, 0x1053));
    public_tags.emplace("RouteID", Tag(0x4010, 0x1054));
    public_tags.emplace("RouteIDAssigningAuthority", Tag(0x4010, 0x1055));
    public_tags.emplace("InboundArrivalType", Tag(0x4010, 0x1056));
    public_tags.emplace("CarrierID", Tag(0x4010, 0x1058));
    public_tags.emplace("CarrierIDAssigningAuthority", Tag(0x4010, 0x1059));
    public_tags.emplace("SourceOrientation", Tag(0x4010, 0x1060));
    public_tags.emplace("SourcePosition", Tag(0x4010, 0x1061));
    public_tags.emplace("BeltHeight", Tag(0x4010, 0x1062));
    public_tags.emplace("AlgorithmRoutingCodeSequence", Tag(0x4010, 0x1064));
    public_tags.emplace("TransportClassification", Tag(0x4010, 0x1067));
    public_tags.emplace("OOITypeDescriptor", Tag(0x4010, 0x1068));
    public_tags.emplace("TotalProcessingTime", Tag(0x4010, 0x1069));
    public_tags.emplace("DetectorCalibrationData", Tag(0x4010, 0x106c));
    public_tags.emplace("AdditionalScreeningPerformed", Tag(0x4010, 0x106d));
    public_tags.emplace("AdditionalInspectionSelectionCriteria", Tag(0x4010, 0x106e));
    public_tags.emplace("AdditionalInspectionMethodSequence", Tag(0x4010, 0x106f));
    public_tags.emplace("AITDeviceType", Tag(0x4010, 0x1070));
    public_tags.emplace("QRMeasurementsSequence", Tag(0x4010, 0x1071));
    public_tags.emplace("TargetMaterialSequence", Tag(0x4010, 0x1072));
    public_tags.emplace("SNRThreshold", Tag(0x4010, 0x1073));
    public_tags.emplace("ImageScaleRepresentation", Tag(0x4010, 0x1075));
    public_tags.emplace("ReferencedPTOSequence", Tag(0x4010, 0x1076));
    public_tags.emplace("ReferencedTDRInstanceSequence", Tag(0x4010, 0x1077));
    public_tags.emplace("PTOLocationDescription", Tag(0x4010, 0x1078));
    public_tags.emplace("AnomalyLocatorIndicatorSequence", Tag(0x4010, 0x1079));
    public_tags.emplace("AnomalyLocatorIndicator", Tag(0x4010, 0x107a));
    public_tags.emplace("PTORegionSequence", Tag(0x4010, 0x107b));
    public_tags.emplace("InspectionSelectionCriteria", Tag(0x4010, 0x107c));
    public_tags.emplace("SecondaryInspectionMethodSequence", Tag(0x4010, 0x107d));
    public_tags.emplace("PRCSToRCSOrientation", Tag(0x4010, 0x107e));
}

}

}