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

void update_3004(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x3004, 0x0001), ElementsDictionaryEntry("DVH Type", "DVHType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0002), ElementsDictionaryEntry("Dose Units", "DoseUnits",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0004), ElementsDictionaryEntry("Dose Type", "DoseType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0005), ElementsDictionaryEntry("Spatial Transform of Dose", "SpatialTransformOfDose",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0006), ElementsDictionaryEntry("Dose Comment", "DoseComment",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0008), ElementsDictionaryEntry("Normalization Point", "NormalizationPoint",  "DS", "3"));
    public_dictionary.emplace(Tag(0x3004, 0x000a), ElementsDictionaryEntry("Dose Summation Type", "DoseSummationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x000c), ElementsDictionaryEntry("Grid Frame Offset Vector", "GridFrameOffsetVector",  "DS", "2-n"));
    public_dictionary.emplace(Tag(0x3004, 0x000e), ElementsDictionaryEntry("Dose Grid Scaling", "DoseGridScaling",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0010), ElementsDictionaryEntry("RT Dose ROI Sequence", "RTDoseROISequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0012), ElementsDictionaryEntry("Dose Value", "DoseValue",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0014), ElementsDictionaryEntry("Tissue Heterogeneity Correction", "TissueHeterogeneityCorrection",  "CS", "1-3"));
    public_dictionary.emplace(Tag(0x3004, 0x0040), ElementsDictionaryEntry("DVH Normalization Point", "DVHNormalizationPoint",  "DS", "3"));
    public_dictionary.emplace(Tag(0x3004, 0x0042), ElementsDictionaryEntry("DVH Normalization Dose Value", "DVHNormalizationDoseValue",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0050), ElementsDictionaryEntry("DVH Sequence", "DVHSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0052), ElementsDictionaryEntry("DVH Dose Scaling", "DVHDoseScaling",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0054), ElementsDictionaryEntry("DVH Volume Units", "DVHVolumeUnits",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0056), ElementsDictionaryEntry("DVH Number of Bins", "DVHNumberOfBins",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0058), ElementsDictionaryEntry("DVH Data", "DVHData",  "DS", "2-2n"));
    public_dictionary.emplace(Tag(0x3004, 0x0060), ElementsDictionaryEntry("DVH Referenced ROI Sequence", "DVHReferencedROISequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0062), ElementsDictionaryEntry("DVH ROI Contribution Type", "DVHROIContributionType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0070), ElementsDictionaryEntry("DVH Minimum Dose", "DVHMinimumDose",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0072), ElementsDictionaryEntry("DVH Maximum Dose", "DVHMaximumDose",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3004, 0x0074), ElementsDictionaryEntry("DVH Mean Dose", "DVHMeanDose",  "DS", "1"));

    public_tags.emplace("DVHType", Tag(0x3004, 0x0001));
    public_tags.emplace("DoseUnits", Tag(0x3004, 0x0002));
    public_tags.emplace("DoseType", Tag(0x3004, 0x0004));
    public_tags.emplace("SpatialTransformOfDose", Tag(0x3004, 0x0005));
    public_tags.emplace("DoseComment", Tag(0x3004, 0x0006));
    public_tags.emplace("NormalizationPoint", Tag(0x3004, 0x0008));
    public_tags.emplace("DoseSummationType", Tag(0x3004, 0x000a));
    public_tags.emplace("GridFrameOffsetVector", Tag(0x3004, 0x000c));
    public_tags.emplace("DoseGridScaling", Tag(0x3004, 0x000e));
    public_tags.emplace("RTDoseROISequence", Tag(0x3004, 0x0010));
    public_tags.emplace("DoseValue", Tag(0x3004, 0x0012));
    public_tags.emplace("TissueHeterogeneityCorrection", Tag(0x3004, 0x0014));
    public_tags.emplace("DVHNormalizationPoint", Tag(0x3004, 0x0040));
    public_tags.emplace("DVHNormalizationDoseValue", Tag(0x3004, 0x0042));
    public_tags.emplace("DVHSequence", Tag(0x3004, 0x0050));
    public_tags.emplace("DVHDoseScaling", Tag(0x3004, 0x0052));
    public_tags.emplace("DVHVolumeUnits", Tag(0x3004, 0x0054));
    public_tags.emplace("DVHNumberOfBins", Tag(0x3004, 0x0056));
    public_tags.emplace("DVHData", Tag(0x3004, 0x0058));
    public_tags.emplace("DVHReferencedROISequence", Tag(0x3004, 0x0060));
    public_tags.emplace("DVHROIContributionType", Tag(0x3004, 0x0062));
    public_tags.emplace("DVHMinimumDose", Tag(0x3004, 0x0070));
    public_tags.emplace("DVHMaximumDose", Tag(0x3004, 0x0072));
    public_tags.emplace("DVHMeanDose", Tag(0x3004, 0x0074));
}

}

}