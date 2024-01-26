/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_300c
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_300c

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const ReferencedRTPlanSequence(0x300c, 0x0002);
Tag const ReferencedBeamSequence(0x300c, 0x0004);
Tag const ReferencedBeamNumber(0x300c, 0x0006);
Tag const ReferencedReferenceImageNumber(0x300c, 0x0007);
Tag const StartCumulativeMetersetWeight(0x300c, 0x0008);
Tag const EndCumulativeMetersetWeight(0x300c, 0x0009);
Tag const ReferencedBrachyApplicationSetupSequence(0x300c, 0x000a);
Tag const ReferencedBrachyApplicationSetupNumber(0x300c, 0x000c);
Tag const ReferencedSourceNumber(0x300c, 0x000e);
Tag const ReferencedFractionGroupSequence(0x300c, 0x0020);
Tag const ReferencedFractionGroupNumber(0x300c, 0x0022);
Tag const ReferencedVerificationImageSequence(0x300c, 0x0040);
Tag const ReferencedReferenceImageSequence(0x300c, 0x0042);
Tag const ReferencedDoseReferenceSequence(0x300c, 0x0050);
Tag const ReferencedDoseReferenceNumber(0x300c, 0x0051);
Tag const BrachyReferencedDoseReferenceSequence(0x300c, 0x0055);
Tag const ReferencedStructureSetSequence(0x300c, 0x0060);
Tag const ReferencedPatientSetupNumber(0x300c, 0x006a);
Tag const ReferencedDoseSequence(0x300c, 0x0080);
Tag const ReferencedToleranceTableNumber(0x300c, 0x00a0);
Tag const ReferencedBolusSequence(0x300c, 0x00b0);
Tag const ReferencedWedgeNumber(0x300c, 0x00c0);
Tag const ReferencedCompensatorNumber(0x300c, 0x00d0);
Tag const ReferencedBlockNumber(0x300c, 0x00e0);
Tag const ReferencedControlPointIndex(0x300c, 0x00f0);
Tag const ReferencedControlPointSequence(0x300c, 0x00f2);
Tag const ReferencedStartControlPointIndex(0x300c, 0x00f4);
Tag const ReferencedStopControlPointIndex(0x300c, 0x00f6);
Tag const ReferencedRangeShifterNumber(0x300c, 0x0100);
Tag const ReferencedLateralSpreadingDeviceNumber(0x300c, 0x0102);
Tag const ReferencedRangeModulatorNumber(0x300c, 0x0104);
Tag const OmittedBeamTaskSequence(0x300c, 0x0111);
Tag const ReasonForOmission(0x300c, 0x0112);
Tag const ReasonForOmissionDescription(0x300c, 0x0113);
Tag const PrescriptionOverviewSequence(0x300c, 0x0114);
Tag const TotalPrescriptionDose(0x300c, 0x0115);
Tag const PlanOverviewSequence(0x300c, 0x0116);
Tag const PlanOverviewIndex(0x300c, 0x0117);
Tag const ReferencedPlanOverviewIndex(0x300c, 0x0118);
Tag const NumberOfFractionsIncluded(0x300c, 0x0119);
Tag const DoseCalibrationConditionsSequence(0x300c, 0x0120);
Tag const AbsorbedDoseToMetersetRatio(0x300c, 0x0121);
Tag const DelineatedRadiationFieldSize(0x300c, 0x0122);
Tag const DoseCalibrationConditionsVerifiedFlag(0x300c, 0x0123);
Tag const CalibrationReferencePointDepth(0x300c, 0x0124);
Tag const GatingBeamHoldTransitionSequence(0x300c, 0x0125);
Tag const BeamHoldTransition(0x300c, 0x0126);
Tag const BeamHoldTransitionDateTime(0x300c, 0x0127);
Tag const BeamHoldOriginatingDeviceSequence(0x300c, 0x0128);
Tag const BeamHoldTransitionTriggerSource(0x300c, 0x0129);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_300c