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

void update_0074(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0074, 0x0120), ElementsDictionaryEntry("Continuation Start Meterset", "ContinuationStartMeterset",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x0121), ElementsDictionaryEntry("Continuation End Meterset", "ContinuationEndMeterset",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1000), ElementsDictionaryEntry("Procedure Step State", "ProcedureStepState",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1002), ElementsDictionaryEntry("Procedure Step Progress Information Sequence", "ProcedureStepProgressInformationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1004), ElementsDictionaryEntry("Procedure Step Progress", "ProcedureStepProgress",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1006), ElementsDictionaryEntry("Procedure Step Progress Description", "ProcedureStepProgressDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1007), ElementsDictionaryEntry("Procedure Step Progress Parameters Sequence", "ProcedureStepProgressParametersSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1008), ElementsDictionaryEntry("Procedure Step Communications URI Sequence", "ProcedureStepCommunicationsURISequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x100a), ElementsDictionaryEntry("Contact URI", "ContactURI",  "UR", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x100c), ElementsDictionaryEntry("Contact Display Name", "ContactDisplayName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x100e), ElementsDictionaryEntry("Procedure Step Discontinuation Reason Code Sequence", "ProcedureStepDiscontinuationReasonCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1020), ElementsDictionaryEntry("Beam Task Sequence", "BeamTaskSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1022), ElementsDictionaryEntry("Beam Task Type", "BeamTaskType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1024), ElementsDictionaryEntry("Beam Order Index (Trial)", "BeamOrderIndexTrial",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1025), ElementsDictionaryEntry("Autosequence Flag", "AutosequenceFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1026), ElementsDictionaryEntry("Table Top Vertical Adjusted Position", "TableTopVerticalAdjustedPosition",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1027), ElementsDictionaryEntry("Table Top Longitudinal Adjusted Position", "TableTopLongitudinalAdjustedPosition",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1028), ElementsDictionaryEntry("Table Top Lateral Adjusted Position", "TableTopLateralAdjustedPosition",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x102a), ElementsDictionaryEntry("Patient Support Adjusted Angle", "PatientSupportAdjustedAngle",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x102b), ElementsDictionaryEntry("Table Top Eccentric Adjusted Angle", "TableTopEccentricAdjustedAngle",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x102c), ElementsDictionaryEntry("Table Top Pitch Adjusted Angle", "TableTopPitchAdjustedAngle",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x102d), ElementsDictionaryEntry("Table Top Roll Adjusted Angle", "TableTopRollAdjustedAngle",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1030), ElementsDictionaryEntry("Delivery Verification Image Sequence", "DeliveryVerificationImageSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1032), ElementsDictionaryEntry("Verification Image Timing", "VerificationImageTiming",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1034), ElementsDictionaryEntry("Double Exposure Flag", "DoubleExposureFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1036), ElementsDictionaryEntry("Double Exposure Ordering", "DoubleExposureOrdering",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1038), ElementsDictionaryEntry("Double Exposure Meterset (Trial)", "DoubleExposureMetersetTrial",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x103a), ElementsDictionaryEntry("Double Exposure Field Delta (Trial)", "DoubleExposureFieldDeltaTrial",  "DS", "4"));
    public_dictionary.emplace(Tag(0x0074, 0x1040), ElementsDictionaryEntry("Related Reference RT Image Sequence", "RelatedReferenceRTImageSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1042), ElementsDictionaryEntry("General Machine Verification Sequence", "GeneralMachineVerificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1044), ElementsDictionaryEntry("Conventional Machine Verification Sequence", "ConventionalMachineVerificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1046), ElementsDictionaryEntry("Ion Machine Verification Sequence", "IonMachineVerificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1048), ElementsDictionaryEntry("Failed Attributes Sequence", "FailedAttributesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x104a), ElementsDictionaryEntry("Overridden Attributes Sequence", "OverriddenAttributesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x104c), ElementsDictionaryEntry("Conventional Control Point Verification Sequence", "ConventionalControlPointVerificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x104e), ElementsDictionaryEntry("Ion Control Point Verification Sequence", "IonControlPointVerificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1050), ElementsDictionaryEntry("Attribute Occurrence Sequence", "AttributeOccurrenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1052), ElementsDictionaryEntry("Attribute Occurrence Pointer", "AttributeOccurrencePointer",  "AT", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1054), ElementsDictionaryEntry("Attribute Item Selector", "AttributeItemSelector",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1056), ElementsDictionaryEntry("Attribute Occurrence Private Creator", "AttributeOccurrencePrivateCreator",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1057), ElementsDictionaryEntry("Selector Sequence Pointer Items", "SelectorSequencePointerItems",  "IS", "1-n"));
    public_dictionary.emplace(Tag(0x0074, 0x1200), ElementsDictionaryEntry("Scheduled Procedure Step Priority", "ScheduledProcedureStepPriority",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1202), ElementsDictionaryEntry("Worklist Label", "WorklistLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1204), ElementsDictionaryEntry("Procedure Step Label", "ProcedureStepLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1210), ElementsDictionaryEntry("Scheduled Processing Parameters Sequence", "ScheduledProcessingParametersSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1212), ElementsDictionaryEntry("Performed Processing Parameters Sequence", "PerformedProcessingParametersSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1216), ElementsDictionaryEntry("Unified Procedure Step Performed Procedure Sequence", "UnifiedProcedureStepPerformedProcedureSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1220), ElementsDictionaryEntry("Related Procedure Step Sequence", "RelatedProcedureStepSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1222), ElementsDictionaryEntry("Procedure Step Relationship Type", "ProcedureStepRelationshipType",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1224), ElementsDictionaryEntry("Replaced Procedure Step Sequence", "ReplacedProcedureStepSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1230), ElementsDictionaryEntry("Deletion Lock", "DeletionLock",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1234), ElementsDictionaryEntry("Receiving AE", "ReceivingAE",  "AE", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1236), ElementsDictionaryEntry("Requesting AE", "RequestingAE",  "AE", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1238), ElementsDictionaryEntry("Reason for Cancellation", "ReasonForCancellation",  "LT", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1242), ElementsDictionaryEntry("SCP Status", "SCPStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1244), ElementsDictionaryEntry("Subscription List Status", "SubscriptionListStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1246), ElementsDictionaryEntry("Unified Procedure Step List Status", "UnifiedProcedureStepListStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1324), ElementsDictionaryEntry("Beam Order Index", "BeamOrderIndex",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1338), ElementsDictionaryEntry("Double Exposure Meterset", "DoubleExposureMeterset",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x133a), ElementsDictionaryEntry("Double Exposure Field Delta", "DoubleExposureFieldDelta",  "FD", "4"));
    public_dictionary.emplace(Tag(0x0074, 0x1401), ElementsDictionaryEntry("Brachy Task Sequence", "BrachyTaskSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1402), ElementsDictionaryEntry("Continuation Start Total Reference Air Kerma", "ContinuationStartTotalReferenceAirKerma",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1403), ElementsDictionaryEntry("Continuation End Total Reference Air Kerma", "ContinuationEndTotalReferenceAirKerma",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1404), ElementsDictionaryEntry("Continuation Pulse Number", "ContinuationPulseNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1405), ElementsDictionaryEntry("Channel Delivery Order Sequence", "ChannelDeliveryOrderSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1406), ElementsDictionaryEntry("Referenced Channel Number", "ReferencedChannelNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1407), ElementsDictionaryEntry("Start Cumulative Time Weight", "StartCumulativeTimeWeight",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1408), ElementsDictionaryEntry("End Cumulative Time Weight", "EndCumulativeTimeWeight",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x1409), ElementsDictionaryEntry("Omitted Channel Sequence", "OmittedChannelSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x140a), ElementsDictionaryEntry("Reason for Channel Omission", "ReasonForChannelOmission",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x140b), ElementsDictionaryEntry("Reason for Channel Omission Description", "ReasonForChannelOmissionDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x140c), ElementsDictionaryEntry("Channel Delivery Order Index", "ChannelDeliveryOrderIndex",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x140d), ElementsDictionaryEntry("Channel Delivery Continuation Sequence", "ChannelDeliveryContinuationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0074, 0x140e), ElementsDictionaryEntry("Omitted Application Setup Sequence", "OmittedApplicationSetupSequence",  "SQ", "1"));

    public_tags.emplace("ContinuationStartMeterset", Tag(0x0074, 0x0120));
    public_tags.emplace("ContinuationEndMeterset", Tag(0x0074, 0x0121));
    public_tags.emplace("ProcedureStepState", Tag(0x0074, 0x1000));
    public_tags.emplace("ProcedureStepProgressInformationSequence", Tag(0x0074, 0x1002));
    public_tags.emplace("ProcedureStepProgress", Tag(0x0074, 0x1004));
    public_tags.emplace("ProcedureStepProgressDescription", Tag(0x0074, 0x1006));
    public_tags.emplace("ProcedureStepProgressParametersSequence", Tag(0x0074, 0x1007));
    public_tags.emplace("ProcedureStepCommunicationsURISequence", Tag(0x0074, 0x1008));
    public_tags.emplace("ContactURI", Tag(0x0074, 0x100a));
    public_tags.emplace("ContactDisplayName", Tag(0x0074, 0x100c));
    public_tags.emplace("ProcedureStepDiscontinuationReasonCodeSequence", Tag(0x0074, 0x100e));
    public_tags.emplace("BeamTaskSequence", Tag(0x0074, 0x1020));
    public_tags.emplace("BeamTaskType", Tag(0x0074, 0x1022));
    public_tags.emplace("BeamOrderIndexTrial", Tag(0x0074, 0x1024));
    public_tags.emplace("AutosequenceFlag", Tag(0x0074, 0x1025));
    public_tags.emplace("TableTopVerticalAdjustedPosition", Tag(0x0074, 0x1026));
    public_tags.emplace("TableTopLongitudinalAdjustedPosition", Tag(0x0074, 0x1027));
    public_tags.emplace("TableTopLateralAdjustedPosition", Tag(0x0074, 0x1028));
    public_tags.emplace("PatientSupportAdjustedAngle", Tag(0x0074, 0x102a));
    public_tags.emplace("TableTopEccentricAdjustedAngle", Tag(0x0074, 0x102b));
    public_tags.emplace("TableTopPitchAdjustedAngle", Tag(0x0074, 0x102c));
    public_tags.emplace("TableTopRollAdjustedAngle", Tag(0x0074, 0x102d));
    public_tags.emplace("DeliveryVerificationImageSequence", Tag(0x0074, 0x1030));
    public_tags.emplace("VerificationImageTiming", Tag(0x0074, 0x1032));
    public_tags.emplace("DoubleExposureFlag", Tag(0x0074, 0x1034));
    public_tags.emplace("DoubleExposureOrdering", Tag(0x0074, 0x1036));
    public_tags.emplace("DoubleExposureMetersetTrial", Tag(0x0074, 0x1038));
    public_tags.emplace("DoubleExposureFieldDeltaTrial", Tag(0x0074, 0x103a));
    public_tags.emplace("RelatedReferenceRTImageSequence", Tag(0x0074, 0x1040));
    public_tags.emplace("GeneralMachineVerificationSequence", Tag(0x0074, 0x1042));
    public_tags.emplace("ConventionalMachineVerificationSequence", Tag(0x0074, 0x1044));
    public_tags.emplace("IonMachineVerificationSequence", Tag(0x0074, 0x1046));
    public_tags.emplace("FailedAttributesSequence", Tag(0x0074, 0x1048));
    public_tags.emplace("OverriddenAttributesSequence", Tag(0x0074, 0x104a));
    public_tags.emplace("ConventionalControlPointVerificationSequence", Tag(0x0074, 0x104c));
    public_tags.emplace("IonControlPointVerificationSequence", Tag(0x0074, 0x104e));
    public_tags.emplace("AttributeOccurrenceSequence", Tag(0x0074, 0x1050));
    public_tags.emplace("AttributeOccurrencePointer", Tag(0x0074, 0x1052));
    public_tags.emplace("AttributeItemSelector", Tag(0x0074, 0x1054));
    public_tags.emplace("AttributeOccurrencePrivateCreator", Tag(0x0074, 0x1056));
    public_tags.emplace("SelectorSequencePointerItems", Tag(0x0074, 0x1057));
    public_tags.emplace("ScheduledProcedureStepPriority", Tag(0x0074, 0x1200));
    public_tags.emplace("WorklistLabel", Tag(0x0074, 0x1202));
    public_tags.emplace("ProcedureStepLabel", Tag(0x0074, 0x1204));
    public_tags.emplace("ScheduledProcessingParametersSequence", Tag(0x0074, 0x1210));
    public_tags.emplace("PerformedProcessingParametersSequence", Tag(0x0074, 0x1212));
    public_tags.emplace("UnifiedProcedureStepPerformedProcedureSequence", Tag(0x0074, 0x1216));
    public_tags.emplace("RelatedProcedureStepSequence", Tag(0x0074, 0x1220));
    public_tags.emplace("ProcedureStepRelationshipType", Tag(0x0074, 0x1222));
    public_tags.emplace("ReplacedProcedureStepSequence", Tag(0x0074, 0x1224));
    public_tags.emplace("DeletionLock", Tag(0x0074, 0x1230));
    public_tags.emplace("ReceivingAE", Tag(0x0074, 0x1234));
    public_tags.emplace("RequestingAE", Tag(0x0074, 0x1236));
    public_tags.emplace("ReasonForCancellation", Tag(0x0074, 0x1238));
    public_tags.emplace("SCPStatus", Tag(0x0074, 0x1242));
    public_tags.emplace("SubscriptionListStatus", Tag(0x0074, 0x1244));
    public_tags.emplace("UnifiedProcedureStepListStatus", Tag(0x0074, 0x1246));
    public_tags.emplace("BeamOrderIndex", Tag(0x0074, 0x1324));
    public_tags.emplace("DoubleExposureMeterset", Tag(0x0074, 0x1338));
    public_tags.emplace("DoubleExposureFieldDelta", Tag(0x0074, 0x133a));
    public_tags.emplace("BrachyTaskSequence", Tag(0x0074, 0x1401));
    public_tags.emplace("ContinuationStartTotalReferenceAirKerma", Tag(0x0074, 0x1402));
    public_tags.emplace("ContinuationEndTotalReferenceAirKerma", Tag(0x0074, 0x1403));
    public_tags.emplace("ContinuationPulseNumber", Tag(0x0074, 0x1404));
    public_tags.emplace("ChannelDeliveryOrderSequence", Tag(0x0074, 0x1405));
    public_tags.emplace("ReferencedChannelNumber", Tag(0x0074, 0x1406));
    public_tags.emplace("StartCumulativeTimeWeight", Tag(0x0074, 0x1407));
    public_tags.emplace("EndCumulativeTimeWeight", Tag(0x0074, 0x1408));
    public_tags.emplace("OmittedChannelSequence", Tag(0x0074, 0x1409));
    public_tags.emplace("ReasonForChannelOmission", Tag(0x0074, 0x140a));
    public_tags.emplace("ReasonForChannelOmissionDescription", Tag(0x0074, 0x140b));
    public_tags.emplace("ChannelDeliveryOrderIndex", Tag(0x0074, 0x140c));
    public_tags.emplace("ChannelDeliveryContinuationSequence", Tag(0x0074, 0x140d));
    public_tags.emplace("OmittedApplicationSetupSequence", Tag(0x0074, 0x140e));
}

}

}