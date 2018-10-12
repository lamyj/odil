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

void update_0054(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0054, 0x0010), ElementsDictionaryEntry("Energy Window Vector", "EnergyWindowVector",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0054, 0x0011), ElementsDictionaryEntry("Number of Energy Windows", "NumberOfEnergyWindows",  "US", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0012), ElementsDictionaryEntry("Energy Window Information Sequence", "EnergyWindowInformationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0013), ElementsDictionaryEntry("Energy Window Range Sequence", "EnergyWindowRangeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0014), ElementsDictionaryEntry("Energy Window Lower Limit", "EnergyWindowLowerLimit",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0015), ElementsDictionaryEntry("Energy Window Upper Limit", "EnergyWindowUpperLimit",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0016), ElementsDictionaryEntry("Radiopharmaceutical Information Sequence", "RadiopharmaceuticalInformationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0017), ElementsDictionaryEntry("Residual Syringe Counts", "ResidualSyringeCounts",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0018), ElementsDictionaryEntry("Energy Window Name", "EnergyWindowName",  "SH", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0020), ElementsDictionaryEntry("Detector Vector", "DetectorVector",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0054, 0x0021), ElementsDictionaryEntry("Number of Detectors", "NumberOfDetectors",  "US", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0022), ElementsDictionaryEntry("Detector Information Sequence", "DetectorInformationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0030), ElementsDictionaryEntry("Phase Vector", "PhaseVector",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0054, 0x0031), ElementsDictionaryEntry("Number of Phases", "NumberOfPhases",  "US", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0032), ElementsDictionaryEntry("Phase Information Sequence", "PhaseInformationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0033), ElementsDictionaryEntry("Number of Frames in Phase", "NumberOfFramesInPhase",  "US", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0036), ElementsDictionaryEntry("Phase Delay", "PhaseDelay",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0038), ElementsDictionaryEntry("Pause Between Frames", "PauseBetweenFrames",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0039), ElementsDictionaryEntry("Phase Description", "PhaseDescription",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0050), ElementsDictionaryEntry("Rotation Vector", "RotationVector",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0054, 0x0051), ElementsDictionaryEntry("Number of Rotations", "NumberOfRotations",  "US", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0052), ElementsDictionaryEntry("Rotation Information Sequence", "RotationInformationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0053), ElementsDictionaryEntry("Number of Frames in Rotation", "NumberOfFramesInRotation",  "US", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0060), ElementsDictionaryEntry("R-R Interval Vector", "RRIntervalVector",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0054, 0x0061), ElementsDictionaryEntry("Number of R-R Intervals", "NumberOfRRIntervals",  "US", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0062), ElementsDictionaryEntry("Gated Information Sequence", "GatedInformationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0063), ElementsDictionaryEntry("Data Information Sequence", "DataInformationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0070), ElementsDictionaryEntry("Time Slot Vector", "TimeSlotVector",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0054, 0x0071), ElementsDictionaryEntry("Number of Time Slots", "NumberOfTimeSlots",  "US", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0072), ElementsDictionaryEntry("Time Slot Information Sequence", "TimeSlotInformationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0073), ElementsDictionaryEntry("Time Slot Time", "TimeSlotTime",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0080), ElementsDictionaryEntry("Slice Vector", "SliceVector",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0054, 0x0081), ElementsDictionaryEntry("Number of Slices", "NumberOfSlices",  "US", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0090), ElementsDictionaryEntry("Angular View Vector", "AngularViewVector",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0054, 0x0100), ElementsDictionaryEntry("Time Slice Vector", "TimeSliceVector",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0054, 0x0101), ElementsDictionaryEntry("Number of Time Slices", "NumberOfTimeSlices",  "US", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0200), ElementsDictionaryEntry("Start Angle", "StartAngle",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0202), ElementsDictionaryEntry("Type of Detector Motion", "TypeOfDetectorMotion",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0210), ElementsDictionaryEntry("Trigger Vector", "TriggerVector",  "IS", "1-n"));
    public_dictionary.emplace(Tag(0x0054, 0x0211), ElementsDictionaryEntry("Number of Triggers in Phase", "NumberOfTriggersInPhase",  "US", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0220), ElementsDictionaryEntry("View Code Sequence", "ViewCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0222), ElementsDictionaryEntry("View Modifier Code Sequence", "ViewModifierCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0300), ElementsDictionaryEntry("Radionuclide Code Sequence", "RadionuclideCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0302), ElementsDictionaryEntry("Administration Route Code Sequence", "AdministrationRouteCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0304), ElementsDictionaryEntry("Radiopharmaceutical Code Sequence", "RadiopharmaceuticalCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0306), ElementsDictionaryEntry("Calibration Data Sequence", "CalibrationDataSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0308), ElementsDictionaryEntry("Energy Window Number", "EnergyWindowNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0400), ElementsDictionaryEntry("Image ID", "ImageID",  "SH", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0410), ElementsDictionaryEntry("Patient Orientation Code Sequence", "PatientOrientationCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0412), ElementsDictionaryEntry("Patient Orientation Modifier Code Sequence", "PatientOrientationModifierCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0414), ElementsDictionaryEntry("Patient Gantry Relationship Code Sequence", "PatientGantryRelationshipCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0500), ElementsDictionaryEntry("Slice Progression Direction", "SliceProgressionDirection",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x0501), ElementsDictionaryEntry("Scan Progression Direction", "ScanProgressionDirection",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1000), ElementsDictionaryEntry("Series Type", "SeriesType",  "CS", "2"));
    public_dictionary.emplace(Tag(0x0054, 0x1001), ElementsDictionaryEntry("Units", "Units",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1002), ElementsDictionaryEntry("Counts Source", "CountsSource",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1004), ElementsDictionaryEntry("Reprojection Method", "ReprojectionMethod",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1006), ElementsDictionaryEntry("SUV Type", "SUVType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1100), ElementsDictionaryEntry("Randoms Correction Method", "RandomsCorrectionMethod",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1101), ElementsDictionaryEntry("Attenuation Correction Method", "AttenuationCorrectionMethod",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1102), ElementsDictionaryEntry("Decay Correction", "DecayCorrection",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1103), ElementsDictionaryEntry("Reconstruction Method", "ReconstructionMethod",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1104), ElementsDictionaryEntry("Detector Lines of Response Used", "DetectorLinesOfResponseUsed",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1105), ElementsDictionaryEntry("Scatter Correction Method", "ScatterCorrectionMethod",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1200), ElementsDictionaryEntry("Axial Acceptance", "AxialAcceptance",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1201), ElementsDictionaryEntry("Axial Mash", "AxialMash",  "IS", "2"));
    public_dictionary.emplace(Tag(0x0054, 0x1202), ElementsDictionaryEntry("Transverse Mash", "TransverseMash",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1203), ElementsDictionaryEntry("Detector Element Size", "DetectorElementSize",  "DS", "2"));
    public_dictionary.emplace(Tag(0x0054, 0x1210), ElementsDictionaryEntry("Coincidence Window Width", "CoincidenceWindowWidth",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1220), ElementsDictionaryEntry("Secondary Counts Type", "SecondaryCountsType",  "CS", "1-n"));
    public_dictionary.emplace(Tag(0x0054, 0x1300), ElementsDictionaryEntry("Frame Reference Time", "FrameReferenceTime",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1310), ElementsDictionaryEntry("Primary (Prompts) Counts Accumulated", "PrimaryPromptsCountsAccumulated",  "IS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1311), ElementsDictionaryEntry("Secondary Counts Accumulated", "SecondaryCountsAccumulated",  "IS", "1-n"));
    public_dictionary.emplace(Tag(0x0054, 0x1320), ElementsDictionaryEntry("Slice Sensitivity Factor", "SliceSensitivityFactor",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1321), ElementsDictionaryEntry("Decay Factor", "DecayFactor",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1322), ElementsDictionaryEntry("Dose Calibration Factor", "DoseCalibrationFactor",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1323), ElementsDictionaryEntry("Scatter Fraction Factor", "ScatterFractionFactor",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1324), ElementsDictionaryEntry("Dead Time Factor", "DeadTimeFactor",  "DS", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1330), ElementsDictionaryEntry("Image Index", "ImageIndex",  "US", "1"));
    public_dictionary.emplace(Tag(0x0054, 0x1400), ElementsDictionaryEntry("Counts Included", "CountsIncluded",  "CS", "1-n"));
    public_dictionary.emplace(Tag(0x0054, 0x1401), ElementsDictionaryEntry("Dead Time Correction Flag", "DeadTimeCorrectionFlag",  "CS", "1"));

    public_tags.emplace("EnergyWindowVector", Tag(0x0054, 0x0010));
    public_tags.emplace("NumberOfEnergyWindows", Tag(0x0054, 0x0011));
    public_tags.emplace("EnergyWindowInformationSequence", Tag(0x0054, 0x0012));
    public_tags.emplace("EnergyWindowRangeSequence", Tag(0x0054, 0x0013));
    public_tags.emplace("EnergyWindowLowerLimit", Tag(0x0054, 0x0014));
    public_tags.emplace("EnergyWindowUpperLimit", Tag(0x0054, 0x0015));
    public_tags.emplace("RadiopharmaceuticalInformationSequence", Tag(0x0054, 0x0016));
    public_tags.emplace("ResidualSyringeCounts", Tag(0x0054, 0x0017));
    public_tags.emplace("EnergyWindowName", Tag(0x0054, 0x0018));
    public_tags.emplace("DetectorVector", Tag(0x0054, 0x0020));
    public_tags.emplace("NumberOfDetectors", Tag(0x0054, 0x0021));
    public_tags.emplace("DetectorInformationSequence", Tag(0x0054, 0x0022));
    public_tags.emplace("PhaseVector", Tag(0x0054, 0x0030));
    public_tags.emplace("NumberOfPhases", Tag(0x0054, 0x0031));
    public_tags.emplace("PhaseInformationSequence", Tag(0x0054, 0x0032));
    public_tags.emplace("NumberOfFramesInPhase", Tag(0x0054, 0x0033));
    public_tags.emplace("PhaseDelay", Tag(0x0054, 0x0036));
    public_tags.emplace("PauseBetweenFrames", Tag(0x0054, 0x0038));
    public_tags.emplace("PhaseDescription", Tag(0x0054, 0x0039));
    public_tags.emplace("RotationVector", Tag(0x0054, 0x0050));
    public_tags.emplace("NumberOfRotations", Tag(0x0054, 0x0051));
    public_tags.emplace("RotationInformationSequence", Tag(0x0054, 0x0052));
    public_tags.emplace("NumberOfFramesInRotation", Tag(0x0054, 0x0053));
    public_tags.emplace("RRIntervalVector", Tag(0x0054, 0x0060));
    public_tags.emplace("NumberOfRRIntervals", Tag(0x0054, 0x0061));
    public_tags.emplace("GatedInformationSequence", Tag(0x0054, 0x0062));
    public_tags.emplace("DataInformationSequence", Tag(0x0054, 0x0063));
    public_tags.emplace("TimeSlotVector", Tag(0x0054, 0x0070));
    public_tags.emplace("NumberOfTimeSlots", Tag(0x0054, 0x0071));
    public_tags.emplace("TimeSlotInformationSequence", Tag(0x0054, 0x0072));
    public_tags.emplace("TimeSlotTime", Tag(0x0054, 0x0073));
    public_tags.emplace("SliceVector", Tag(0x0054, 0x0080));
    public_tags.emplace("NumberOfSlices", Tag(0x0054, 0x0081));
    public_tags.emplace("AngularViewVector", Tag(0x0054, 0x0090));
    public_tags.emplace("TimeSliceVector", Tag(0x0054, 0x0100));
    public_tags.emplace("NumberOfTimeSlices", Tag(0x0054, 0x0101));
    public_tags.emplace("StartAngle", Tag(0x0054, 0x0200));
    public_tags.emplace("TypeOfDetectorMotion", Tag(0x0054, 0x0202));
    public_tags.emplace("TriggerVector", Tag(0x0054, 0x0210));
    public_tags.emplace("NumberOfTriggersInPhase", Tag(0x0054, 0x0211));
    public_tags.emplace("ViewCodeSequence", Tag(0x0054, 0x0220));
    public_tags.emplace("ViewModifierCodeSequence", Tag(0x0054, 0x0222));
    public_tags.emplace("RadionuclideCodeSequence", Tag(0x0054, 0x0300));
    public_tags.emplace("AdministrationRouteCodeSequence", Tag(0x0054, 0x0302));
    public_tags.emplace("RadiopharmaceuticalCodeSequence", Tag(0x0054, 0x0304));
    public_tags.emplace("CalibrationDataSequence", Tag(0x0054, 0x0306));
    public_tags.emplace("EnergyWindowNumber", Tag(0x0054, 0x0308));
    public_tags.emplace("ImageID", Tag(0x0054, 0x0400));
    public_tags.emplace("PatientOrientationCodeSequence", Tag(0x0054, 0x0410));
    public_tags.emplace("PatientOrientationModifierCodeSequence", Tag(0x0054, 0x0412));
    public_tags.emplace("PatientGantryRelationshipCodeSequence", Tag(0x0054, 0x0414));
    public_tags.emplace("SliceProgressionDirection", Tag(0x0054, 0x0500));
    public_tags.emplace("ScanProgressionDirection", Tag(0x0054, 0x0501));
    public_tags.emplace("SeriesType", Tag(0x0054, 0x1000));
    public_tags.emplace("Units", Tag(0x0054, 0x1001));
    public_tags.emplace("CountsSource", Tag(0x0054, 0x1002));
    public_tags.emplace("ReprojectionMethod", Tag(0x0054, 0x1004));
    public_tags.emplace("SUVType", Tag(0x0054, 0x1006));
    public_tags.emplace("RandomsCorrectionMethod", Tag(0x0054, 0x1100));
    public_tags.emplace("AttenuationCorrectionMethod", Tag(0x0054, 0x1101));
    public_tags.emplace("DecayCorrection", Tag(0x0054, 0x1102));
    public_tags.emplace("ReconstructionMethod", Tag(0x0054, 0x1103));
    public_tags.emplace("DetectorLinesOfResponseUsed", Tag(0x0054, 0x1104));
    public_tags.emplace("ScatterCorrectionMethod", Tag(0x0054, 0x1105));
    public_tags.emplace("AxialAcceptance", Tag(0x0054, 0x1200));
    public_tags.emplace("AxialMash", Tag(0x0054, 0x1201));
    public_tags.emplace("TransverseMash", Tag(0x0054, 0x1202));
    public_tags.emplace("DetectorElementSize", Tag(0x0054, 0x1203));
    public_tags.emplace("CoincidenceWindowWidth", Tag(0x0054, 0x1210));
    public_tags.emplace("SecondaryCountsType", Tag(0x0054, 0x1220));
    public_tags.emplace("FrameReferenceTime", Tag(0x0054, 0x1300));
    public_tags.emplace("PrimaryPromptsCountsAccumulated", Tag(0x0054, 0x1310));
    public_tags.emplace("SecondaryCountsAccumulated", Tag(0x0054, 0x1311));
    public_tags.emplace("SliceSensitivityFactor", Tag(0x0054, 0x1320));
    public_tags.emplace("DecayFactor", Tag(0x0054, 0x1321));
    public_tags.emplace("DoseCalibrationFactor", Tag(0x0054, 0x1322));
    public_tags.emplace("ScatterFractionFactor", Tag(0x0054, 0x1323));
    public_tags.emplace("DeadTimeFactor", Tag(0x0054, 0x1324));
    public_tags.emplace("ImageIndex", Tag(0x0054, 0x1330));
    public_tags.emplace("CountsIncluded", Tag(0x0054, 0x1400));
    public_tags.emplace("DeadTimeCorrectionFlag", Tag(0x0054, 0x1401));
}

}

}