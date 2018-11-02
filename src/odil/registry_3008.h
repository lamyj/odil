/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3008
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3008

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const MeasuredDoseReferenceSequence(0x3008, 0x0010);
Tag const MeasuredDoseDescription(0x3008, 0x0012);
Tag const MeasuredDoseType(0x3008, 0x0014);
Tag const MeasuredDoseValue(0x3008, 0x0016);
Tag const TreatmentSessionBeamSequence(0x3008, 0x0020);
Tag const TreatmentSessionIonBeamSequence(0x3008, 0x0021);
Tag const CurrentFractionNumber(0x3008, 0x0022);
Tag const TreatmentControlPointDate(0x3008, 0x0024);
Tag const TreatmentControlPointTime(0x3008, 0x0025);
Tag const TreatmentTerminationStatus(0x3008, 0x002a);
Tag const TreatmentTerminationCode(0x3008, 0x002b);
Tag const TreatmentVerificationStatus(0x3008, 0x002c);
Tag const ReferencedTreatmentRecordSequence(0x3008, 0x0030);
Tag const SpecifiedPrimaryMeterset(0x3008, 0x0032);
Tag const SpecifiedSecondaryMeterset(0x3008, 0x0033);
Tag const DeliveredPrimaryMeterset(0x3008, 0x0036);
Tag const DeliveredSecondaryMeterset(0x3008, 0x0037);
Tag const SpecifiedTreatmentTime(0x3008, 0x003a);
Tag const DeliveredTreatmentTime(0x3008, 0x003b);
Tag const ControlPointDeliverySequence(0x3008, 0x0040);
Tag const IonControlPointDeliverySequence(0x3008, 0x0041);
Tag const SpecifiedMeterset(0x3008, 0x0042);
Tag const DeliveredMeterset(0x3008, 0x0044);
Tag const MetersetRateSet(0x3008, 0x0045);
Tag const MetersetRateDelivered(0x3008, 0x0046);
Tag const ScanSpotMetersetsDelivered(0x3008, 0x0047);
Tag const DoseRateDelivered(0x3008, 0x0048);
Tag const TreatmentSummaryCalculatedDoseReferenceSequence(0x3008, 0x0050);
Tag const CumulativeDoseToDoseReference(0x3008, 0x0052);
Tag const FirstTreatmentDate(0x3008, 0x0054);
Tag const MostRecentTreatmentDate(0x3008, 0x0056);
Tag const NumberOfFractionsDelivered(0x3008, 0x005a);
Tag const OverrideSequence(0x3008, 0x0060);
Tag const ParameterSequencePointer(0x3008, 0x0061);
Tag const OverrideParameterPointer(0x3008, 0x0062);
Tag const ParameterItemIndex(0x3008, 0x0063);
Tag const MeasuredDoseReferenceNumber(0x3008, 0x0064);
Tag const ParameterPointer(0x3008, 0x0065);
Tag const OverrideReason(0x3008, 0x0066);
Tag const ParameterValueNumber(0x3008, 0x0067);
Tag const CorrectedParameterSequence(0x3008, 0x0068);
Tag const CorrectionValue(0x3008, 0x006a);
Tag const CalculatedDoseReferenceSequence(0x3008, 0x0070);
Tag const CalculatedDoseReferenceNumber(0x3008, 0x0072);
Tag const CalculatedDoseReferenceDescription(0x3008, 0x0074);
Tag const CalculatedDoseReferenceDoseValue(0x3008, 0x0076);
Tag const StartMeterset(0x3008, 0x0078);
Tag const EndMeterset(0x3008, 0x007a);
Tag const ReferencedMeasuredDoseReferenceSequence(0x3008, 0x0080);
Tag const ReferencedMeasuredDoseReferenceNumber(0x3008, 0x0082);
Tag const ReferencedCalculatedDoseReferenceSequence(0x3008, 0x0090);
Tag const ReferencedCalculatedDoseReferenceNumber(0x3008, 0x0092);
Tag const BeamLimitingDeviceLeafPairsSequence(0x3008, 0x00a0);
Tag const RecordedWedgeSequence(0x3008, 0x00b0);
Tag const RecordedCompensatorSequence(0x3008, 0x00c0);
Tag const RecordedBlockSequence(0x3008, 0x00d0);
Tag const TreatmentSummaryMeasuredDoseReferenceSequence(0x3008, 0x00e0);
Tag const RecordedSnoutSequence(0x3008, 0x00f0);
Tag const RecordedRangeShifterSequence(0x3008, 0x00f2);
Tag const RecordedLateralSpreadingDeviceSequence(0x3008, 0x00f4);
Tag const RecordedRangeModulatorSequence(0x3008, 0x00f6);
Tag const RecordedSourceSequence(0x3008, 0x0100);
Tag const SourceSerialNumber(0x3008, 0x0105);
Tag const TreatmentSessionApplicationSetupSequence(0x3008, 0x0110);
Tag const ApplicationSetupCheck(0x3008, 0x0116);
Tag const RecordedBrachyAccessoryDeviceSequence(0x3008, 0x0120);
Tag const ReferencedBrachyAccessoryDeviceNumber(0x3008, 0x0122);
Tag const RecordedChannelSequence(0x3008, 0x0130);
Tag const SpecifiedChannelTotalTime(0x3008, 0x0132);
Tag const DeliveredChannelTotalTime(0x3008, 0x0134);
Tag const SpecifiedNumberOfPulses(0x3008, 0x0136);
Tag const DeliveredNumberOfPulses(0x3008, 0x0138);
Tag const SpecifiedPulseRepetitionInterval(0x3008, 0x013a);
Tag const DeliveredPulseRepetitionInterval(0x3008, 0x013c);
Tag const RecordedSourceApplicatorSequence(0x3008, 0x0140);
Tag const ReferencedSourceApplicatorNumber(0x3008, 0x0142);
Tag const RecordedChannelShieldSequence(0x3008, 0x0150);
Tag const ReferencedChannelShieldNumber(0x3008, 0x0152);
Tag const BrachyControlPointDeliveredSequence(0x3008, 0x0160);
Tag const SafePositionExitDate(0x3008, 0x0162);
Tag const SafePositionExitTime(0x3008, 0x0164);
Tag const SafePositionReturnDate(0x3008, 0x0166);
Tag const SafePositionReturnTime(0x3008, 0x0168);
Tag const PulseSpecificBrachyControlPointDeliveredSequence(0x3008, 0x0171);
Tag const PulseNumber(0x3008, 0x0172);
Tag const BrachyPulseControlPointDeliveredSequence(0x3008, 0x0173);
Tag const CurrentTreatmentStatus(0x3008, 0x0200);
Tag const TreatmentStatusComment(0x3008, 0x0202);
Tag const FractionGroupSummarySequence(0x3008, 0x0220);
Tag const ReferencedFractionNumber(0x3008, 0x0223);
Tag const FractionGroupType(0x3008, 0x0224);
Tag const BeamStopperPosition(0x3008, 0x0230);
Tag const FractionStatusSummarySequence(0x3008, 0x0240);
Tag const TreatmentDate(0x3008, 0x0250);
Tag const TreatmentTime(0x3008, 0x0251);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3008