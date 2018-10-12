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

void update_0024(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0024, 0x0010), ElementsDictionaryEntry("Visual Field Horizontal Extent", "VisualFieldHorizontalExtent",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0011), ElementsDictionaryEntry("Visual Field Vertical Extent", "VisualFieldVerticalExtent",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0012), ElementsDictionaryEntry("Visual Field Shape", "VisualFieldShape",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0016), ElementsDictionaryEntry("Screening Test Mode Code Sequence", "ScreeningTestModeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0018), ElementsDictionaryEntry("Maximum Stimulus Luminance", "MaximumStimulusLuminance",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0020), ElementsDictionaryEntry("Background Luminance", "BackgroundLuminance",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0021), ElementsDictionaryEntry("Stimulus Color Code Sequence", "StimulusColorCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0024), ElementsDictionaryEntry("Background Illumination Color Code Sequence", "BackgroundIlluminationColorCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0025), ElementsDictionaryEntry("Stimulus Area", "StimulusArea",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0028), ElementsDictionaryEntry("Stimulus Presentation Time", "StimulusPresentationTime",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0032), ElementsDictionaryEntry("Fixation Sequence", "FixationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0033), ElementsDictionaryEntry("Fixation Monitoring Code Sequence", "FixationMonitoringCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0034), ElementsDictionaryEntry("Visual Field Catch Trial Sequence", "VisualFieldCatchTrialSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0035), ElementsDictionaryEntry("Fixation Checked Quantity", "FixationCheckedQuantity",  "US", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0036), ElementsDictionaryEntry("Patient Not Properly Fixated Quantity", "PatientNotProperlyFixatedQuantity",  "US", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0037), ElementsDictionaryEntry("Presented Visual Stimuli Data Flag", "PresentedVisualStimuliDataFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0038), ElementsDictionaryEntry("Number of Visual Stimuli", "NumberOfVisualStimuli",  "US", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0039), ElementsDictionaryEntry("Excessive Fixation Losses Data Flag", "ExcessiveFixationLossesDataFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0040), ElementsDictionaryEntry("Excessive Fixation Losses", "ExcessiveFixationLosses",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0042), ElementsDictionaryEntry("Stimuli Retesting Quantity", "StimuliRetestingQuantity",  "US", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0044), ElementsDictionaryEntry("Comments on Patient's Performance of Visual Field", "CommentsOnPatientPerformanceOfVisualField",  "LT", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0045), ElementsDictionaryEntry("False Negatives Estimate Flag", "FalseNegativesEstimateFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0046), ElementsDictionaryEntry("False Negatives Estimate", "FalseNegativesEstimate",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0048), ElementsDictionaryEntry("Negative Catch Trials Quantity", "NegativeCatchTrialsQuantity",  "US", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0050), ElementsDictionaryEntry("False Negatives Quantity", "FalseNegativesQuantity",  "US", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0051), ElementsDictionaryEntry("Excessive False Negatives Data Flag", "ExcessiveFalseNegativesDataFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0052), ElementsDictionaryEntry("Excessive False Negatives", "ExcessiveFalseNegatives",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0053), ElementsDictionaryEntry("False Positives Estimate Flag", "FalsePositivesEstimateFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0054), ElementsDictionaryEntry("False Positives Estimate", "FalsePositivesEstimate",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0055), ElementsDictionaryEntry("Catch Trials Data Flag", "CatchTrialsDataFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0056), ElementsDictionaryEntry("Positive Catch Trials Quantity", "PositiveCatchTrialsQuantity",  "US", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0057), ElementsDictionaryEntry("Test Point Normals Data Flag", "TestPointNormalsDataFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0058), ElementsDictionaryEntry("Test Point Normals Sequence", "TestPointNormalsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0059), ElementsDictionaryEntry("Global Deviation Probability Normals Flag", "GlobalDeviationProbabilityNormalsFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0060), ElementsDictionaryEntry("False Positives Quantity", "FalsePositivesQuantity",  "US", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0061), ElementsDictionaryEntry("Excessive False Positives Data Flag", "ExcessiveFalsePositivesDataFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0062), ElementsDictionaryEntry("Excessive False Positives", "ExcessiveFalsePositives",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0063), ElementsDictionaryEntry("Visual Field Test Normals Flag", "VisualFieldTestNormalsFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0064), ElementsDictionaryEntry("Results Normals Sequence", "ResultsNormalsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0065), ElementsDictionaryEntry("Age Corrected Sensitivity Deviation Algorithm Sequence", "AgeCorrectedSensitivityDeviationAlgorithmSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0066), ElementsDictionaryEntry("Global Deviation From Normal", "GlobalDeviationFromNormal",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0067), ElementsDictionaryEntry("Generalized Defect Sensitivity Deviation Algorithm Sequence", "GeneralizedDefectSensitivityDeviationAlgorithmSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0068), ElementsDictionaryEntry("Localized Deviation From Normal", "LocalizedDeviationFromNormal",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0069), ElementsDictionaryEntry("Patient Reliability Indicator", "PatientReliabilityIndicator",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0070), ElementsDictionaryEntry("Visual Field Mean Sensitivity", "VisualFieldMeanSensitivity",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0071), ElementsDictionaryEntry("Global Deviation Probability", "GlobalDeviationProbability",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0072), ElementsDictionaryEntry("Local Deviation Probability Normals Flag", "LocalDeviationProbabilityNormalsFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0073), ElementsDictionaryEntry("Localized Deviation Probability", "LocalizedDeviationProbability",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0074), ElementsDictionaryEntry("Short Term Fluctuation Calculated", "ShortTermFluctuationCalculated",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0075), ElementsDictionaryEntry("Short Term Fluctuation", "ShortTermFluctuation",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0076), ElementsDictionaryEntry("Short Term Fluctuation Probability Calculated", "ShortTermFluctuationProbabilityCalculated",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0077), ElementsDictionaryEntry("Short Term Fluctuation Probability", "ShortTermFluctuationProbability",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0078), ElementsDictionaryEntry("Corrected Localized Deviation From Normal Calculated", "CorrectedLocalizedDeviationFromNormalCalculated",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0079), ElementsDictionaryEntry("Corrected Localized Deviation From Normal", "CorrectedLocalizedDeviationFromNormal",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0080), ElementsDictionaryEntry("Corrected Localized Deviation From Normal Probability Calculated", "CorrectedLocalizedDeviationFromNormalProbabilityCalculated",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0081), ElementsDictionaryEntry("Corrected Localized Deviation From Normal Probability", "CorrectedLocalizedDeviationFromNormalProbability",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0083), ElementsDictionaryEntry("Global Deviation Probability Sequence", "GlobalDeviationProbabilitySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0085), ElementsDictionaryEntry("Localized Deviation Probability Sequence", "LocalizedDeviationProbabilitySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0086), ElementsDictionaryEntry("Foveal Sensitivity Measured", "FovealSensitivityMeasured",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0087), ElementsDictionaryEntry("Foveal Sensitivity", "FovealSensitivity",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0088), ElementsDictionaryEntry("Visual Field Test Duration", "VisualFieldTestDuration",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0089), ElementsDictionaryEntry("Visual Field Test Point Sequence", "VisualFieldTestPointSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0090), ElementsDictionaryEntry("Visual Field Test Point X-Coordinate", "VisualFieldTestPointXCoordinate",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0091), ElementsDictionaryEntry("Visual Field Test Point Y-Coordinate", "VisualFieldTestPointYCoordinate",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0092), ElementsDictionaryEntry("Age Corrected Sensitivity Deviation Value", "AgeCorrectedSensitivityDeviationValue",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0093), ElementsDictionaryEntry("Stimulus Results", "StimulusResults",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0094), ElementsDictionaryEntry("Sensitivity Value", "SensitivityValue",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0095), ElementsDictionaryEntry("Retest Stimulus Seen", "RetestStimulusSeen",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0096), ElementsDictionaryEntry("Retest Sensitivity Value", "RetestSensitivityValue",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0097), ElementsDictionaryEntry("Visual Field Test Point Normals Sequence", "VisualFieldTestPointNormalsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0098), ElementsDictionaryEntry("Quantified Defect", "QuantifiedDefect",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0100), ElementsDictionaryEntry("Age Corrected Sensitivity Deviation Probability Value", "AgeCorrectedSensitivityDeviationProbabilityValue",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0102), ElementsDictionaryEntry("Generalized Defect Corrected Sensitivity Deviation Flag", "GeneralizedDefectCorrectedSensitivityDeviationFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0103), ElementsDictionaryEntry("Generalized Defect Corrected Sensitivity Deviation Value", "GeneralizedDefectCorrectedSensitivityDeviationValue",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0104), ElementsDictionaryEntry("Generalized Defect Corrected Sensitivity Deviation Probability Value", "GeneralizedDefectCorrectedSensitivityDeviationProbabilityValue",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0105), ElementsDictionaryEntry("Minimum Sensitivity Value", "MinimumSensitivityValue",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0106), ElementsDictionaryEntry("Blind Spot Localized", "BlindSpotLocalized",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0107), ElementsDictionaryEntry("Blind Spot X-Coordinate", "BlindSpotXCoordinate",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0108), ElementsDictionaryEntry("Blind Spot Y-Coordinate", "BlindSpotYCoordinate",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0110), ElementsDictionaryEntry("Visual Acuity Measurement Sequence", "VisualAcuityMeasurementSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0112), ElementsDictionaryEntry("Refractive Parameters Used on Patient Sequence", "RefractiveParametersUsedOnPatientSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0113), ElementsDictionaryEntry("Measurement Laterality", "MeasurementLaterality",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0114), ElementsDictionaryEntry("Ophthalmic Patient Clinical Information Left Eye Sequence", "OphthalmicPatientClinicalInformationLeftEyeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0115), ElementsDictionaryEntry("Ophthalmic Patient Clinical Information Right Eye Sequence", "OphthalmicPatientClinicalInformationRightEyeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0117), ElementsDictionaryEntry("Foveal Point Normative Data Flag", "FovealPointNormativeDataFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0118), ElementsDictionaryEntry("Foveal Point Probability Value", "FovealPointProbabilityValue",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0120), ElementsDictionaryEntry("Screening Baseline Measured", "ScreeningBaselineMeasured",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0122), ElementsDictionaryEntry("Screening Baseline Measured Sequence", "ScreeningBaselineMeasuredSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0124), ElementsDictionaryEntry("Screening Baseline Type", "ScreeningBaselineType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0126), ElementsDictionaryEntry("Screening Baseline Value", "ScreeningBaselineValue",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0202), ElementsDictionaryEntry("Algorithm Source", "AlgorithmSource",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0306), ElementsDictionaryEntry("Data Set Name", "DataSetName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0307), ElementsDictionaryEntry("Data Set Version", "DataSetVersion",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0308), ElementsDictionaryEntry("Data Set Source", "DataSetSource",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0309), ElementsDictionaryEntry("Data Set Description", "DataSetDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0317), ElementsDictionaryEntry("Visual Field Test Reliability Global Index Sequence", "VisualFieldTestReliabilityGlobalIndexSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0320), ElementsDictionaryEntry("Visual Field Global Results Index Sequence", "VisualFieldGlobalResultsIndexSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0325), ElementsDictionaryEntry("Data Observation Sequence", "DataObservationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0338), ElementsDictionaryEntry("Index Normals Flag", "IndexNormalsFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0341), ElementsDictionaryEntry("Index Probability", "IndexProbability",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0024, 0x0344), ElementsDictionaryEntry("Index Probability Sequence", "IndexProbabilitySequence",  "SQ", "1"));

    public_tags.emplace("VisualFieldHorizontalExtent", Tag(0x0024, 0x0010));
    public_tags.emplace("VisualFieldVerticalExtent", Tag(0x0024, 0x0011));
    public_tags.emplace("VisualFieldShape", Tag(0x0024, 0x0012));
    public_tags.emplace("ScreeningTestModeCodeSequence", Tag(0x0024, 0x0016));
    public_tags.emplace("MaximumStimulusLuminance", Tag(0x0024, 0x0018));
    public_tags.emplace("BackgroundLuminance", Tag(0x0024, 0x0020));
    public_tags.emplace("StimulusColorCodeSequence", Tag(0x0024, 0x0021));
    public_tags.emplace("BackgroundIlluminationColorCodeSequence", Tag(0x0024, 0x0024));
    public_tags.emplace("StimulusArea", Tag(0x0024, 0x0025));
    public_tags.emplace("StimulusPresentationTime", Tag(0x0024, 0x0028));
    public_tags.emplace("FixationSequence", Tag(0x0024, 0x0032));
    public_tags.emplace("FixationMonitoringCodeSequence", Tag(0x0024, 0x0033));
    public_tags.emplace("VisualFieldCatchTrialSequence", Tag(0x0024, 0x0034));
    public_tags.emplace("FixationCheckedQuantity", Tag(0x0024, 0x0035));
    public_tags.emplace("PatientNotProperlyFixatedQuantity", Tag(0x0024, 0x0036));
    public_tags.emplace("PresentedVisualStimuliDataFlag", Tag(0x0024, 0x0037));
    public_tags.emplace("NumberOfVisualStimuli", Tag(0x0024, 0x0038));
    public_tags.emplace("ExcessiveFixationLossesDataFlag", Tag(0x0024, 0x0039));
    public_tags.emplace("ExcessiveFixationLosses", Tag(0x0024, 0x0040));
    public_tags.emplace("StimuliRetestingQuantity", Tag(0x0024, 0x0042));
    public_tags.emplace("CommentsOnPatientPerformanceOfVisualField", Tag(0x0024, 0x0044));
    public_tags.emplace("FalseNegativesEstimateFlag", Tag(0x0024, 0x0045));
    public_tags.emplace("FalseNegativesEstimate", Tag(0x0024, 0x0046));
    public_tags.emplace("NegativeCatchTrialsQuantity", Tag(0x0024, 0x0048));
    public_tags.emplace("FalseNegativesQuantity", Tag(0x0024, 0x0050));
    public_tags.emplace("ExcessiveFalseNegativesDataFlag", Tag(0x0024, 0x0051));
    public_tags.emplace("ExcessiveFalseNegatives", Tag(0x0024, 0x0052));
    public_tags.emplace("FalsePositivesEstimateFlag", Tag(0x0024, 0x0053));
    public_tags.emplace("FalsePositivesEstimate", Tag(0x0024, 0x0054));
    public_tags.emplace("CatchTrialsDataFlag", Tag(0x0024, 0x0055));
    public_tags.emplace("PositiveCatchTrialsQuantity", Tag(0x0024, 0x0056));
    public_tags.emplace("TestPointNormalsDataFlag", Tag(0x0024, 0x0057));
    public_tags.emplace("TestPointNormalsSequence", Tag(0x0024, 0x0058));
    public_tags.emplace("GlobalDeviationProbabilityNormalsFlag", Tag(0x0024, 0x0059));
    public_tags.emplace("FalsePositivesQuantity", Tag(0x0024, 0x0060));
    public_tags.emplace("ExcessiveFalsePositivesDataFlag", Tag(0x0024, 0x0061));
    public_tags.emplace("ExcessiveFalsePositives", Tag(0x0024, 0x0062));
    public_tags.emplace("VisualFieldTestNormalsFlag", Tag(0x0024, 0x0063));
    public_tags.emplace("ResultsNormalsSequence", Tag(0x0024, 0x0064));
    public_tags.emplace("AgeCorrectedSensitivityDeviationAlgorithmSequence", Tag(0x0024, 0x0065));
    public_tags.emplace("GlobalDeviationFromNormal", Tag(0x0024, 0x0066));
    public_tags.emplace("GeneralizedDefectSensitivityDeviationAlgorithmSequence", Tag(0x0024, 0x0067));
    public_tags.emplace("LocalizedDeviationFromNormal", Tag(0x0024, 0x0068));
    public_tags.emplace("PatientReliabilityIndicator", Tag(0x0024, 0x0069));
    public_tags.emplace("VisualFieldMeanSensitivity", Tag(0x0024, 0x0070));
    public_tags.emplace("GlobalDeviationProbability", Tag(0x0024, 0x0071));
    public_tags.emplace("LocalDeviationProbabilityNormalsFlag", Tag(0x0024, 0x0072));
    public_tags.emplace("LocalizedDeviationProbability", Tag(0x0024, 0x0073));
    public_tags.emplace("ShortTermFluctuationCalculated", Tag(0x0024, 0x0074));
    public_tags.emplace("ShortTermFluctuation", Tag(0x0024, 0x0075));
    public_tags.emplace("ShortTermFluctuationProbabilityCalculated", Tag(0x0024, 0x0076));
    public_tags.emplace("ShortTermFluctuationProbability", Tag(0x0024, 0x0077));
    public_tags.emplace("CorrectedLocalizedDeviationFromNormalCalculated", Tag(0x0024, 0x0078));
    public_tags.emplace("CorrectedLocalizedDeviationFromNormal", Tag(0x0024, 0x0079));
    public_tags.emplace("CorrectedLocalizedDeviationFromNormalProbabilityCalculated", Tag(0x0024, 0x0080));
    public_tags.emplace("CorrectedLocalizedDeviationFromNormalProbability", Tag(0x0024, 0x0081));
    public_tags.emplace("GlobalDeviationProbabilitySequence", Tag(0x0024, 0x0083));
    public_tags.emplace("LocalizedDeviationProbabilitySequence", Tag(0x0024, 0x0085));
    public_tags.emplace("FovealSensitivityMeasured", Tag(0x0024, 0x0086));
    public_tags.emplace("FovealSensitivity", Tag(0x0024, 0x0087));
    public_tags.emplace("VisualFieldTestDuration", Tag(0x0024, 0x0088));
    public_tags.emplace("VisualFieldTestPointSequence", Tag(0x0024, 0x0089));
    public_tags.emplace("VisualFieldTestPointXCoordinate", Tag(0x0024, 0x0090));
    public_tags.emplace("VisualFieldTestPointYCoordinate", Tag(0x0024, 0x0091));
    public_tags.emplace("AgeCorrectedSensitivityDeviationValue", Tag(0x0024, 0x0092));
    public_tags.emplace("StimulusResults", Tag(0x0024, 0x0093));
    public_tags.emplace("SensitivityValue", Tag(0x0024, 0x0094));
    public_tags.emplace("RetestStimulusSeen", Tag(0x0024, 0x0095));
    public_tags.emplace("RetestSensitivityValue", Tag(0x0024, 0x0096));
    public_tags.emplace("VisualFieldTestPointNormalsSequence", Tag(0x0024, 0x0097));
    public_tags.emplace("QuantifiedDefect", Tag(0x0024, 0x0098));
    public_tags.emplace("AgeCorrectedSensitivityDeviationProbabilityValue", Tag(0x0024, 0x0100));
    public_tags.emplace("GeneralizedDefectCorrectedSensitivityDeviationFlag", Tag(0x0024, 0x0102));
    public_tags.emplace("GeneralizedDefectCorrectedSensitivityDeviationValue", Tag(0x0024, 0x0103));
    public_tags.emplace("GeneralizedDefectCorrectedSensitivityDeviationProbabilityValue", Tag(0x0024, 0x0104));
    public_tags.emplace("MinimumSensitivityValue", Tag(0x0024, 0x0105));
    public_tags.emplace("BlindSpotLocalized", Tag(0x0024, 0x0106));
    public_tags.emplace("BlindSpotXCoordinate", Tag(0x0024, 0x0107));
    public_tags.emplace("BlindSpotYCoordinate", Tag(0x0024, 0x0108));
    public_tags.emplace("VisualAcuityMeasurementSequence", Tag(0x0024, 0x0110));
    public_tags.emplace("RefractiveParametersUsedOnPatientSequence", Tag(0x0024, 0x0112));
    public_tags.emplace("MeasurementLaterality", Tag(0x0024, 0x0113));
    public_tags.emplace("OphthalmicPatientClinicalInformationLeftEyeSequence", Tag(0x0024, 0x0114));
    public_tags.emplace("OphthalmicPatientClinicalInformationRightEyeSequence", Tag(0x0024, 0x0115));
    public_tags.emplace("FovealPointNormativeDataFlag", Tag(0x0024, 0x0117));
    public_tags.emplace("FovealPointProbabilityValue", Tag(0x0024, 0x0118));
    public_tags.emplace("ScreeningBaselineMeasured", Tag(0x0024, 0x0120));
    public_tags.emplace("ScreeningBaselineMeasuredSequence", Tag(0x0024, 0x0122));
    public_tags.emplace("ScreeningBaselineType", Tag(0x0024, 0x0124));
    public_tags.emplace("ScreeningBaselineValue", Tag(0x0024, 0x0126));
    public_tags.emplace("AlgorithmSource", Tag(0x0024, 0x0202));
    public_tags.emplace("DataSetName", Tag(0x0024, 0x0306));
    public_tags.emplace("DataSetVersion", Tag(0x0024, 0x0307));
    public_tags.emplace("DataSetSource", Tag(0x0024, 0x0308));
    public_tags.emplace("DataSetDescription", Tag(0x0024, 0x0309));
    public_tags.emplace("VisualFieldTestReliabilityGlobalIndexSequence", Tag(0x0024, 0x0317));
    public_tags.emplace("VisualFieldGlobalResultsIndexSequence", Tag(0x0024, 0x0320));
    public_tags.emplace("DataObservationSequence", Tag(0x0024, 0x0325));
    public_tags.emplace("IndexNormalsFlag", Tag(0x0024, 0x0338));
    public_tags.emplace("IndexProbability", Tag(0x0024, 0x0341));
    public_tags.emplace("IndexProbabilitySequence", Tag(0x0024, 0x0344));
}

}

}