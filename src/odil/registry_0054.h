/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0054
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0054

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const EnergyWindowVector(0x0054, 0x0010);
Tag const NumberOfEnergyWindows(0x0054, 0x0011);
Tag const EnergyWindowInformationSequence(0x0054, 0x0012);
Tag const EnergyWindowRangeSequence(0x0054, 0x0013);
Tag const EnergyWindowLowerLimit(0x0054, 0x0014);
Tag const EnergyWindowUpperLimit(0x0054, 0x0015);
Tag const RadiopharmaceuticalInformationSequence(0x0054, 0x0016);
Tag const ResidualSyringeCounts(0x0054, 0x0017);
Tag const EnergyWindowName(0x0054, 0x0018);
Tag const DetectorVector(0x0054, 0x0020);
Tag const NumberOfDetectors(0x0054, 0x0021);
Tag const DetectorInformationSequence(0x0054, 0x0022);
Tag const PhaseVector(0x0054, 0x0030);
Tag const NumberOfPhases(0x0054, 0x0031);
Tag const PhaseInformationSequence(0x0054, 0x0032);
Tag const NumberOfFramesInPhase(0x0054, 0x0033);
Tag const PhaseDelay(0x0054, 0x0036);
Tag const PauseBetweenFrames(0x0054, 0x0038);
Tag const PhaseDescription(0x0054, 0x0039);
Tag const RotationVector(0x0054, 0x0050);
Tag const NumberOfRotations(0x0054, 0x0051);
Tag const RotationInformationSequence(0x0054, 0x0052);
Tag const NumberOfFramesInRotation(0x0054, 0x0053);
Tag const RRIntervalVector(0x0054, 0x0060);
Tag const NumberOfRRIntervals(0x0054, 0x0061);
Tag const GatedInformationSequence(0x0054, 0x0062);
Tag const DataInformationSequence(0x0054, 0x0063);
Tag const TimeSlotVector(0x0054, 0x0070);
Tag const NumberOfTimeSlots(0x0054, 0x0071);
Tag const TimeSlotInformationSequence(0x0054, 0x0072);
Tag const TimeSlotTime(0x0054, 0x0073);
Tag const SliceVector(0x0054, 0x0080);
Tag const NumberOfSlices(0x0054, 0x0081);
Tag const AngularViewVector(0x0054, 0x0090);
Tag const TimeSliceVector(0x0054, 0x0100);
Tag const NumberOfTimeSlices(0x0054, 0x0101);
Tag const StartAngle(0x0054, 0x0200);
Tag const TypeOfDetectorMotion(0x0054, 0x0202);
Tag const TriggerVector(0x0054, 0x0210);
Tag const NumberOfTriggersInPhase(0x0054, 0x0211);
Tag const ViewCodeSequence(0x0054, 0x0220);
Tag const ViewModifierCodeSequence(0x0054, 0x0222);
Tag const RadionuclideCodeSequence(0x0054, 0x0300);
Tag const AdministrationRouteCodeSequence(0x0054, 0x0302);
Tag const RadiopharmaceuticalCodeSequence(0x0054, 0x0304);
Tag const CalibrationDataSequence(0x0054, 0x0306);
Tag const EnergyWindowNumber(0x0054, 0x0308);
Tag const ImageID(0x0054, 0x0400);
Tag const PatientOrientationCodeSequence(0x0054, 0x0410);
Tag const PatientOrientationModifierCodeSequence(0x0054, 0x0412);
Tag const PatientGantryRelationshipCodeSequence(0x0054, 0x0414);
Tag const SliceProgressionDirection(0x0054, 0x0500);
Tag const ScanProgressionDirection(0x0054, 0x0501);
Tag const SeriesType(0x0054, 0x1000);
Tag const Units(0x0054, 0x1001);
Tag const CountsSource(0x0054, 0x1002);
Tag const ReprojectionMethod(0x0054, 0x1004);
Tag const SUVType(0x0054, 0x1006);
Tag const RandomsCorrectionMethod(0x0054, 0x1100);
Tag const AttenuationCorrectionMethod(0x0054, 0x1101);
Tag const DecayCorrection(0x0054, 0x1102);
Tag const ReconstructionMethod(0x0054, 0x1103);
Tag const DetectorLinesOfResponseUsed(0x0054, 0x1104);
Tag const ScatterCorrectionMethod(0x0054, 0x1105);
Tag const AxialAcceptance(0x0054, 0x1200);
Tag const AxialMash(0x0054, 0x1201);
Tag const TransverseMash(0x0054, 0x1202);
Tag const DetectorElementSize(0x0054, 0x1203);
Tag const CoincidenceWindowWidth(0x0054, 0x1210);
Tag const SecondaryCountsType(0x0054, 0x1220);
Tag const FrameReferenceTime(0x0054, 0x1300);
Tag const PrimaryPromptsCountsAccumulated(0x0054, 0x1310);
Tag const SecondaryCountsAccumulated(0x0054, 0x1311);
Tag const SliceSensitivityFactor(0x0054, 0x1320);
Tag const DecayFactor(0x0054, 0x1321);
Tag const DoseCalibrationFactor(0x0054, 0x1322);
Tag const ScatterFractionFactor(0x0054, 0x1323);
Tag const DeadTimeFactor(0x0054, 0x1324);
Tag const ImageIndex(0x0054, 0x1330);
Tag const CountsIncluded(0x0054, 0x1400);
Tag const DeadTimeCorrectionFlag(0x0054, 0x1401);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0054