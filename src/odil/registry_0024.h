/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0024
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0024

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const VisualFieldHorizontalExtent(0x0024, 0x0010);
Tag const VisualFieldVerticalExtent(0x0024, 0x0011);
Tag const VisualFieldShape(0x0024, 0x0012);
Tag const ScreeningTestModeCodeSequence(0x0024, 0x0016);
Tag const MaximumStimulusLuminance(0x0024, 0x0018);
Tag const BackgroundLuminance(0x0024, 0x0020);
Tag const StimulusColorCodeSequence(0x0024, 0x0021);
Tag const BackgroundIlluminationColorCodeSequence(0x0024, 0x0024);
Tag const StimulusArea(0x0024, 0x0025);
Tag const StimulusPresentationTime(0x0024, 0x0028);
Tag const FixationSequence(0x0024, 0x0032);
Tag const FixationMonitoringCodeSequence(0x0024, 0x0033);
Tag const VisualFieldCatchTrialSequence(0x0024, 0x0034);
Tag const FixationCheckedQuantity(0x0024, 0x0035);
Tag const PatientNotProperlyFixatedQuantity(0x0024, 0x0036);
Tag const PresentedVisualStimuliDataFlag(0x0024, 0x0037);
Tag const NumberOfVisualStimuli(0x0024, 0x0038);
Tag const ExcessiveFixationLossesDataFlag(0x0024, 0x0039);
Tag const ExcessiveFixationLosses(0x0024, 0x0040);
Tag const StimuliRetestingQuantity(0x0024, 0x0042);
Tag const CommentsOnPatientPerformanceOfVisualField(0x0024, 0x0044);
Tag const FalseNegativesEstimateFlag(0x0024, 0x0045);
Tag const FalseNegativesEstimate(0x0024, 0x0046);
Tag const NegativeCatchTrialsQuantity(0x0024, 0x0048);
Tag const FalseNegativesQuantity(0x0024, 0x0050);
Tag const ExcessiveFalseNegativesDataFlag(0x0024, 0x0051);
Tag const ExcessiveFalseNegatives(0x0024, 0x0052);
Tag const FalsePositivesEstimateFlag(0x0024, 0x0053);
Tag const FalsePositivesEstimate(0x0024, 0x0054);
Tag const CatchTrialsDataFlag(0x0024, 0x0055);
Tag const PositiveCatchTrialsQuantity(0x0024, 0x0056);
Tag const TestPointNormalsDataFlag(0x0024, 0x0057);
Tag const TestPointNormalsSequence(0x0024, 0x0058);
Tag const GlobalDeviationProbabilityNormalsFlag(0x0024, 0x0059);
Tag const FalsePositivesQuantity(0x0024, 0x0060);
Tag const ExcessiveFalsePositivesDataFlag(0x0024, 0x0061);
Tag const ExcessiveFalsePositives(0x0024, 0x0062);
Tag const VisualFieldTestNormalsFlag(0x0024, 0x0063);
Tag const ResultsNormalsSequence(0x0024, 0x0064);
Tag const AgeCorrectedSensitivityDeviationAlgorithmSequence(0x0024, 0x0065);
Tag const GlobalDeviationFromNormal(0x0024, 0x0066);
Tag const GeneralizedDefectSensitivityDeviationAlgorithmSequence(0x0024, 0x0067);
Tag const LocalizedDeviationFromNormal(0x0024, 0x0068);
Tag const PatientReliabilityIndicator(0x0024, 0x0069);
Tag const VisualFieldMeanSensitivity(0x0024, 0x0070);
Tag const GlobalDeviationProbability(0x0024, 0x0071);
Tag const LocalDeviationProbabilityNormalsFlag(0x0024, 0x0072);
Tag const LocalizedDeviationProbability(0x0024, 0x0073);
Tag const ShortTermFluctuationCalculated(0x0024, 0x0074);
Tag const ShortTermFluctuation(0x0024, 0x0075);
Tag const ShortTermFluctuationProbabilityCalculated(0x0024, 0x0076);
Tag const ShortTermFluctuationProbability(0x0024, 0x0077);
Tag const CorrectedLocalizedDeviationFromNormalCalculated(0x0024, 0x0078);
Tag const CorrectedLocalizedDeviationFromNormal(0x0024, 0x0079);
Tag const CorrectedLocalizedDeviationFromNormalProbabilityCalculated(0x0024, 0x0080);
Tag const CorrectedLocalizedDeviationFromNormalProbability(0x0024, 0x0081);
Tag const GlobalDeviationProbabilitySequence(0x0024, 0x0083);
Tag const LocalizedDeviationProbabilitySequence(0x0024, 0x0085);
Tag const FovealSensitivityMeasured(0x0024, 0x0086);
Tag const FovealSensitivity(0x0024, 0x0087);
Tag const VisualFieldTestDuration(0x0024, 0x0088);
Tag const VisualFieldTestPointSequence(0x0024, 0x0089);
Tag const VisualFieldTestPointXCoordinate(0x0024, 0x0090);
Tag const VisualFieldTestPointYCoordinate(0x0024, 0x0091);
Tag const AgeCorrectedSensitivityDeviationValue(0x0024, 0x0092);
Tag const StimulusResults(0x0024, 0x0093);
Tag const SensitivityValue(0x0024, 0x0094);
Tag const RetestStimulusSeen(0x0024, 0x0095);
Tag const RetestSensitivityValue(0x0024, 0x0096);
Tag const VisualFieldTestPointNormalsSequence(0x0024, 0x0097);
Tag const QuantifiedDefect(0x0024, 0x0098);
Tag const AgeCorrectedSensitivityDeviationProbabilityValue(0x0024, 0x0100);
Tag const GeneralizedDefectCorrectedSensitivityDeviationFlag(0x0024, 0x0102);
Tag const GeneralizedDefectCorrectedSensitivityDeviationValue(0x0024, 0x0103);
Tag const GeneralizedDefectCorrectedSensitivityDeviationProbabilityValue(0x0024, 0x0104);
Tag const MinimumSensitivityValue(0x0024, 0x0105);
Tag const BlindSpotLocalized(0x0024, 0x0106);
Tag const BlindSpotXCoordinate(0x0024, 0x0107);
Tag const BlindSpotYCoordinate(0x0024, 0x0108);
Tag const VisualAcuityMeasurementSequence(0x0024, 0x0110);
Tag const RefractiveParametersUsedOnPatientSequence(0x0024, 0x0112);
Tag const MeasurementLaterality(0x0024, 0x0113);
Tag const OphthalmicPatientClinicalInformationLeftEyeSequence(0x0024, 0x0114);
Tag const OphthalmicPatientClinicalInformationRightEyeSequence(0x0024, 0x0115);
Tag const FovealPointNormativeDataFlag(0x0024, 0x0117);
Tag const FovealPointProbabilityValue(0x0024, 0x0118);
Tag const ScreeningBaselineMeasured(0x0024, 0x0120);
Tag const ScreeningBaselineMeasuredSequence(0x0024, 0x0122);
Tag const ScreeningBaselineType(0x0024, 0x0124);
Tag const ScreeningBaselineValue(0x0024, 0x0126);
Tag const AlgorithmSource(0x0024, 0x0202);
Tag const DataSetName(0x0024, 0x0306);
Tag const DataSetVersion(0x0024, 0x0307);
Tag const DataSetSource(0x0024, 0x0308);
Tag const DataSetDescription(0x0024, 0x0309);
Tag const VisualFieldTestReliabilityGlobalIndexSequence(0x0024, 0x0317);
Tag const VisualFieldGlobalResultsIndexSequence(0x0024, 0x0320);
Tag const DataObservationSequence(0x0024, 0x0325);
Tag const IndexNormalsFlag(0x0024, 0x0338);
Tag const IndexProbability(0x0024, 0x0341);
Tag const IndexProbabilitySequence(0x0024, 0x0344);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0024