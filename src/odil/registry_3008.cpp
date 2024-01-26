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

void update_3008(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x3008, 0x0010), ElementsDictionaryEntry("Measured Dose Reference Sequence", "MeasuredDoseReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0012), ElementsDictionaryEntry("Measured Dose Description", "MeasuredDoseDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0014), ElementsDictionaryEntry("Measured Dose Type", "MeasuredDoseType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0016), ElementsDictionaryEntry("Measured Dose Value", "MeasuredDoseValue",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0020), ElementsDictionaryEntry("Treatment Session Beam Sequence", "TreatmentSessionBeamSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0021), ElementsDictionaryEntry("Treatment Session Ion Beam Sequence", "TreatmentSessionIonBeamSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0022), ElementsDictionaryEntry("Current Fraction Number", "CurrentFractionNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0024), ElementsDictionaryEntry("Treatment Control Point Date", "TreatmentControlPointDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0025), ElementsDictionaryEntry("Treatment Control Point Time", "TreatmentControlPointTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x002a), ElementsDictionaryEntry("Treatment Termination Status", "TreatmentTerminationStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x002b), ElementsDictionaryEntry("Treatment Termination Code", "TreatmentTerminationCode",  "SH", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x002c), ElementsDictionaryEntry("Treatment Verification Status", "TreatmentVerificationStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0030), ElementsDictionaryEntry("Referenced Treatment Record Sequence", "ReferencedTreatmentRecordSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0032), ElementsDictionaryEntry("Specified Primary Meterset", "SpecifiedPrimaryMeterset",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0033), ElementsDictionaryEntry("Specified Secondary Meterset", "SpecifiedSecondaryMeterset",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0036), ElementsDictionaryEntry("Delivered Primary Meterset", "DeliveredPrimaryMeterset",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0037), ElementsDictionaryEntry("Delivered Secondary Meterset", "DeliveredSecondaryMeterset",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x003a), ElementsDictionaryEntry("Specified Treatment Time", "SpecifiedTreatmentTime",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x003b), ElementsDictionaryEntry("Delivered Treatment Time", "DeliveredTreatmentTime",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0040), ElementsDictionaryEntry("Control Point Delivery Sequence", "ControlPointDeliverySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0041), ElementsDictionaryEntry("Ion Control Point Delivery Sequence", "IonControlPointDeliverySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0042), ElementsDictionaryEntry("Specified Meterset", "SpecifiedMeterset",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0044), ElementsDictionaryEntry("Delivered Meterset", "DeliveredMeterset",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0045), ElementsDictionaryEntry("Meterset Rate Set", "MetersetRateSet",  "FL", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0046), ElementsDictionaryEntry("Meterset Rate Delivered", "MetersetRateDelivered",  "FL", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0047), ElementsDictionaryEntry("Scan Spot Metersets Delivered", "ScanSpotMetersetsDelivered",  "FL", "1-n"));
    public_dictionary.emplace(Tag(0x3008, 0x0048), ElementsDictionaryEntry("Dose Rate Delivered", "DoseRateDelivered",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0050), ElementsDictionaryEntry("Treatment Summary Calculated Dose Reference Sequence", "TreatmentSummaryCalculatedDoseReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0052), ElementsDictionaryEntry("Cumulative Dose to Dose Reference", "CumulativeDoseToDoseReference",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0054), ElementsDictionaryEntry("First Treatment Date", "FirstTreatmentDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0056), ElementsDictionaryEntry("Most Recent Treatment Date", "MostRecentTreatmentDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x005a), ElementsDictionaryEntry("Number of Fractions Delivered", "NumberOfFractionsDelivered",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0060), ElementsDictionaryEntry("Override Sequence", "OverrideSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0061), ElementsDictionaryEntry("Parameter Sequence Pointer", "ParameterSequencePointer",  "AT", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0062), ElementsDictionaryEntry("Override Parameter Pointer", "OverrideParameterPointer",  "AT", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0063), ElementsDictionaryEntry("Parameter Item Index", "ParameterItemIndex",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0064), ElementsDictionaryEntry("Measured Dose Reference Number", "MeasuredDoseReferenceNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0065), ElementsDictionaryEntry("Parameter Pointer", "ParameterPointer",  "AT", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0066), ElementsDictionaryEntry("Override Reason", "OverrideReason",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0067), ElementsDictionaryEntry("Parameter Value Number", "ParameterValueNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0068), ElementsDictionaryEntry("Corrected Parameter Sequence", "CorrectedParameterSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x006a), ElementsDictionaryEntry("Correction Value", "CorrectionValue",  "FL", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0070), ElementsDictionaryEntry("Calculated Dose Reference Sequence", "CalculatedDoseReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0072), ElementsDictionaryEntry("Calculated Dose Reference Number", "CalculatedDoseReferenceNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0074), ElementsDictionaryEntry("Calculated Dose Reference Description", "CalculatedDoseReferenceDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0076), ElementsDictionaryEntry("Calculated Dose Reference Dose Value", "CalculatedDoseReferenceDoseValue",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0078), ElementsDictionaryEntry("Start Meterset", "StartMeterset",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x007a), ElementsDictionaryEntry("End Meterset", "EndMeterset",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0080), ElementsDictionaryEntry("Referenced Measured Dose Reference Sequence", "ReferencedMeasuredDoseReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0082), ElementsDictionaryEntry("Referenced Measured Dose Reference Number", "ReferencedMeasuredDoseReferenceNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0090), ElementsDictionaryEntry("Referenced Calculated Dose Reference Sequence", "ReferencedCalculatedDoseReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0092), ElementsDictionaryEntry("Referenced Calculated Dose Reference Number", "ReferencedCalculatedDoseReferenceNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x00a0), ElementsDictionaryEntry("Beam Limiting Device Leaf Pairs Sequence", "BeamLimitingDeviceLeafPairsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x00a1), ElementsDictionaryEntry("Enhanced RT Beam Limiting Device Sequence", "EnhancedRTBeamLimitingDeviceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x00a2), ElementsDictionaryEntry("Enhanced RT Beam Limiting Opening Sequence", "EnhancedRTBeamLimitingOpeningSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x00a3), ElementsDictionaryEntry("Enhanced RT Beam Limiting Device Definition Flag", "EnhancedRTBeamLimitingDeviceDefinitionFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x00a4), ElementsDictionaryEntry("Parallel RT Beam Delimiter Opening Extents", "ParallelRTBeamDelimiterOpeningExtents",  "FD", "2-2n"));
    public_dictionary.emplace(Tag(0x3008, 0x00b0), ElementsDictionaryEntry("Recorded Wedge Sequence", "RecordedWedgeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x00c0), ElementsDictionaryEntry("Recorded Compensator Sequence", "RecordedCompensatorSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x00d0), ElementsDictionaryEntry("Recorded Block Sequence", "RecordedBlockSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x00d1), ElementsDictionaryEntry("Recorded Block Slab Sequence", "RecordedBlockSlabSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x00e0), ElementsDictionaryEntry("Treatment Summary Measured Dose Reference Sequence", "TreatmentSummaryMeasuredDoseReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x00f0), ElementsDictionaryEntry("Recorded Snout Sequence", "RecordedSnoutSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x00f2), ElementsDictionaryEntry("Recorded Range Shifter Sequence", "RecordedRangeShifterSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x00f4), ElementsDictionaryEntry("Recorded Lateral Spreading Device Sequence", "RecordedLateralSpreadingDeviceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x00f6), ElementsDictionaryEntry("Recorded Range Modulator Sequence", "RecordedRangeModulatorSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0100), ElementsDictionaryEntry("Recorded Source Sequence", "RecordedSourceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0105), ElementsDictionaryEntry("Source Serial Number", "SourceSerialNumber",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0110), ElementsDictionaryEntry("Treatment Session Application Setup Sequence", "TreatmentSessionApplicationSetupSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0116), ElementsDictionaryEntry("Application Setup Check", "ApplicationSetupCheck",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0120), ElementsDictionaryEntry("Recorded Brachy Accessory Device Sequence", "RecordedBrachyAccessoryDeviceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0122), ElementsDictionaryEntry("Referenced Brachy Accessory Device Number", "ReferencedBrachyAccessoryDeviceNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0130), ElementsDictionaryEntry("Recorded Channel Sequence", "RecordedChannelSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0132), ElementsDictionaryEntry("Specified Channel Total Time", "SpecifiedChannelTotalTime",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0134), ElementsDictionaryEntry("Delivered Channel Total Time", "DeliveredChannelTotalTime",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0136), ElementsDictionaryEntry("Specified Number of Pulses", "SpecifiedNumberOfPulses",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0138), ElementsDictionaryEntry("Delivered Number of Pulses", "DeliveredNumberOfPulses",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x013a), ElementsDictionaryEntry("Specified Pulse Repetition Interval", "SpecifiedPulseRepetitionInterval",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x013c), ElementsDictionaryEntry("Delivered Pulse Repetition Interval", "DeliveredPulseRepetitionInterval",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0140), ElementsDictionaryEntry("Recorded Source Applicator Sequence", "RecordedSourceApplicatorSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0142), ElementsDictionaryEntry("Referenced Source Applicator Number", "ReferencedSourceApplicatorNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0150), ElementsDictionaryEntry("Recorded Channel Shield Sequence", "RecordedChannelShieldSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0152), ElementsDictionaryEntry("Referenced Channel Shield Number", "ReferencedChannelShieldNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0160), ElementsDictionaryEntry("Brachy Control Point Delivered Sequence", "BrachyControlPointDeliveredSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0162), ElementsDictionaryEntry("Safe Position Exit Date", "SafePositionExitDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0164), ElementsDictionaryEntry("Safe Position Exit Time", "SafePositionExitTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0166), ElementsDictionaryEntry("Safe Position Return Date", "SafePositionReturnDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0168), ElementsDictionaryEntry("Safe Position Return Time", "SafePositionReturnTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0171), ElementsDictionaryEntry("Pulse Specific Brachy Control Point Delivered Sequence", "PulseSpecificBrachyControlPointDeliveredSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0172), ElementsDictionaryEntry("Pulse Number", "PulseNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0173), ElementsDictionaryEntry("Brachy Pulse Control Point Delivered Sequence", "BrachyPulseControlPointDeliveredSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0200), ElementsDictionaryEntry("Current Treatment Status", "CurrentTreatmentStatus",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0202), ElementsDictionaryEntry("Treatment Status Comment", "TreatmentStatusComment",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0220), ElementsDictionaryEntry("Fraction Group Summary Sequence", "FractionGroupSummarySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0223), ElementsDictionaryEntry("Referenced Fraction Number", "ReferencedFractionNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0224), ElementsDictionaryEntry("Fraction Group Type", "FractionGroupType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0230), ElementsDictionaryEntry("Beam Stopper Position", "BeamStopperPosition",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0240), ElementsDictionaryEntry("Fraction Status Summary Sequence", "FractionStatusSummarySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0250), ElementsDictionaryEntry("Treatment Date", "TreatmentDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x3008, 0x0251), ElementsDictionaryEntry("Treatment Time", "TreatmentTime",  "TM", "1"));

    public_tags.emplace("MeasuredDoseReferenceSequence", Tag(0x3008, 0x0010));
    public_tags.emplace("MeasuredDoseDescription", Tag(0x3008, 0x0012));
    public_tags.emplace("MeasuredDoseType", Tag(0x3008, 0x0014));
    public_tags.emplace("MeasuredDoseValue", Tag(0x3008, 0x0016));
    public_tags.emplace("TreatmentSessionBeamSequence", Tag(0x3008, 0x0020));
    public_tags.emplace("TreatmentSessionIonBeamSequence", Tag(0x3008, 0x0021));
    public_tags.emplace("CurrentFractionNumber", Tag(0x3008, 0x0022));
    public_tags.emplace("TreatmentControlPointDate", Tag(0x3008, 0x0024));
    public_tags.emplace("TreatmentControlPointTime", Tag(0x3008, 0x0025));
    public_tags.emplace("TreatmentTerminationStatus", Tag(0x3008, 0x002a));
    public_tags.emplace("TreatmentTerminationCode", Tag(0x3008, 0x002b));
    public_tags.emplace("TreatmentVerificationStatus", Tag(0x3008, 0x002c));
    public_tags.emplace("ReferencedTreatmentRecordSequence", Tag(0x3008, 0x0030));
    public_tags.emplace("SpecifiedPrimaryMeterset", Tag(0x3008, 0x0032));
    public_tags.emplace("SpecifiedSecondaryMeterset", Tag(0x3008, 0x0033));
    public_tags.emplace("DeliveredPrimaryMeterset", Tag(0x3008, 0x0036));
    public_tags.emplace("DeliveredSecondaryMeterset", Tag(0x3008, 0x0037));
    public_tags.emplace("SpecifiedTreatmentTime", Tag(0x3008, 0x003a));
    public_tags.emplace("DeliveredTreatmentTime", Tag(0x3008, 0x003b));
    public_tags.emplace("ControlPointDeliverySequence", Tag(0x3008, 0x0040));
    public_tags.emplace("IonControlPointDeliverySequence", Tag(0x3008, 0x0041));
    public_tags.emplace("SpecifiedMeterset", Tag(0x3008, 0x0042));
    public_tags.emplace("DeliveredMeterset", Tag(0x3008, 0x0044));
    public_tags.emplace("MetersetRateSet", Tag(0x3008, 0x0045));
    public_tags.emplace("MetersetRateDelivered", Tag(0x3008, 0x0046));
    public_tags.emplace("ScanSpotMetersetsDelivered", Tag(0x3008, 0x0047));
    public_tags.emplace("DoseRateDelivered", Tag(0x3008, 0x0048));
    public_tags.emplace("TreatmentSummaryCalculatedDoseReferenceSequence", Tag(0x3008, 0x0050));
    public_tags.emplace("CumulativeDoseToDoseReference", Tag(0x3008, 0x0052));
    public_tags.emplace("FirstTreatmentDate", Tag(0x3008, 0x0054));
    public_tags.emplace("MostRecentTreatmentDate", Tag(0x3008, 0x0056));
    public_tags.emplace("NumberOfFractionsDelivered", Tag(0x3008, 0x005a));
    public_tags.emplace("OverrideSequence", Tag(0x3008, 0x0060));
    public_tags.emplace("ParameterSequencePointer", Tag(0x3008, 0x0061));
    public_tags.emplace("OverrideParameterPointer", Tag(0x3008, 0x0062));
    public_tags.emplace("ParameterItemIndex", Tag(0x3008, 0x0063));
    public_tags.emplace("MeasuredDoseReferenceNumber", Tag(0x3008, 0x0064));
    public_tags.emplace("ParameterPointer", Tag(0x3008, 0x0065));
    public_tags.emplace("OverrideReason", Tag(0x3008, 0x0066));
    public_tags.emplace("ParameterValueNumber", Tag(0x3008, 0x0067));
    public_tags.emplace("CorrectedParameterSequence", Tag(0x3008, 0x0068));
    public_tags.emplace("CorrectionValue", Tag(0x3008, 0x006a));
    public_tags.emplace("CalculatedDoseReferenceSequence", Tag(0x3008, 0x0070));
    public_tags.emplace("CalculatedDoseReferenceNumber", Tag(0x3008, 0x0072));
    public_tags.emplace("CalculatedDoseReferenceDescription", Tag(0x3008, 0x0074));
    public_tags.emplace("CalculatedDoseReferenceDoseValue", Tag(0x3008, 0x0076));
    public_tags.emplace("StartMeterset", Tag(0x3008, 0x0078));
    public_tags.emplace("EndMeterset", Tag(0x3008, 0x007a));
    public_tags.emplace("ReferencedMeasuredDoseReferenceSequence", Tag(0x3008, 0x0080));
    public_tags.emplace("ReferencedMeasuredDoseReferenceNumber", Tag(0x3008, 0x0082));
    public_tags.emplace("ReferencedCalculatedDoseReferenceSequence", Tag(0x3008, 0x0090));
    public_tags.emplace("ReferencedCalculatedDoseReferenceNumber", Tag(0x3008, 0x0092));
    public_tags.emplace("BeamLimitingDeviceLeafPairsSequence", Tag(0x3008, 0x00a0));
    public_tags.emplace("EnhancedRTBeamLimitingDeviceSequence", Tag(0x3008, 0x00a1));
    public_tags.emplace("EnhancedRTBeamLimitingOpeningSequence", Tag(0x3008, 0x00a2));
    public_tags.emplace("EnhancedRTBeamLimitingDeviceDefinitionFlag", Tag(0x3008, 0x00a3));
    public_tags.emplace("ParallelRTBeamDelimiterOpeningExtents", Tag(0x3008, 0x00a4));
    public_tags.emplace("RecordedWedgeSequence", Tag(0x3008, 0x00b0));
    public_tags.emplace("RecordedCompensatorSequence", Tag(0x3008, 0x00c0));
    public_tags.emplace("RecordedBlockSequence", Tag(0x3008, 0x00d0));
    public_tags.emplace("RecordedBlockSlabSequence", Tag(0x3008, 0x00d1));
    public_tags.emplace("TreatmentSummaryMeasuredDoseReferenceSequence", Tag(0x3008, 0x00e0));
    public_tags.emplace("RecordedSnoutSequence", Tag(0x3008, 0x00f0));
    public_tags.emplace("RecordedRangeShifterSequence", Tag(0x3008, 0x00f2));
    public_tags.emplace("RecordedLateralSpreadingDeviceSequence", Tag(0x3008, 0x00f4));
    public_tags.emplace("RecordedRangeModulatorSequence", Tag(0x3008, 0x00f6));
    public_tags.emplace("RecordedSourceSequence", Tag(0x3008, 0x0100));
    public_tags.emplace("SourceSerialNumber", Tag(0x3008, 0x0105));
    public_tags.emplace("TreatmentSessionApplicationSetupSequence", Tag(0x3008, 0x0110));
    public_tags.emplace("ApplicationSetupCheck", Tag(0x3008, 0x0116));
    public_tags.emplace("RecordedBrachyAccessoryDeviceSequence", Tag(0x3008, 0x0120));
    public_tags.emplace("ReferencedBrachyAccessoryDeviceNumber", Tag(0x3008, 0x0122));
    public_tags.emplace("RecordedChannelSequence", Tag(0x3008, 0x0130));
    public_tags.emplace("SpecifiedChannelTotalTime", Tag(0x3008, 0x0132));
    public_tags.emplace("DeliveredChannelTotalTime", Tag(0x3008, 0x0134));
    public_tags.emplace("SpecifiedNumberOfPulses", Tag(0x3008, 0x0136));
    public_tags.emplace("DeliveredNumberOfPulses", Tag(0x3008, 0x0138));
    public_tags.emplace("SpecifiedPulseRepetitionInterval", Tag(0x3008, 0x013a));
    public_tags.emplace("DeliveredPulseRepetitionInterval", Tag(0x3008, 0x013c));
    public_tags.emplace("RecordedSourceApplicatorSequence", Tag(0x3008, 0x0140));
    public_tags.emplace("ReferencedSourceApplicatorNumber", Tag(0x3008, 0x0142));
    public_tags.emplace("RecordedChannelShieldSequence", Tag(0x3008, 0x0150));
    public_tags.emplace("ReferencedChannelShieldNumber", Tag(0x3008, 0x0152));
    public_tags.emplace("BrachyControlPointDeliveredSequence", Tag(0x3008, 0x0160));
    public_tags.emplace("SafePositionExitDate", Tag(0x3008, 0x0162));
    public_tags.emplace("SafePositionExitTime", Tag(0x3008, 0x0164));
    public_tags.emplace("SafePositionReturnDate", Tag(0x3008, 0x0166));
    public_tags.emplace("SafePositionReturnTime", Tag(0x3008, 0x0168));
    public_tags.emplace("PulseSpecificBrachyControlPointDeliveredSequence", Tag(0x3008, 0x0171));
    public_tags.emplace("PulseNumber", Tag(0x3008, 0x0172));
    public_tags.emplace("BrachyPulseControlPointDeliveredSequence", Tag(0x3008, 0x0173));
    public_tags.emplace("CurrentTreatmentStatus", Tag(0x3008, 0x0200));
    public_tags.emplace("TreatmentStatusComment", Tag(0x3008, 0x0202));
    public_tags.emplace("FractionGroupSummarySequence", Tag(0x3008, 0x0220));
    public_tags.emplace("ReferencedFractionNumber", Tag(0x3008, 0x0223));
    public_tags.emplace("FractionGroupType", Tag(0x3008, 0x0224));
    public_tags.emplace("BeamStopperPosition", Tag(0x3008, 0x0230));
    public_tags.emplace("FractionStatusSummarySequence", Tag(0x3008, 0x0240));
    public_tags.emplace("TreatmentDate", Tag(0x3008, 0x0250));
    public_tags.emplace("TreatmentTime", Tag(0x3008, 0x0251));
}

}

}