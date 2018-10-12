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

void update_300c(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x300c, 0x0002), ElementsDictionaryEntry("Referenced RT Plan Sequence", "ReferencedRTPlanSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0004), ElementsDictionaryEntry("Referenced Beam Sequence", "ReferencedBeamSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0006), ElementsDictionaryEntry("Referenced Beam Number", "ReferencedBeamNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0007), ElementsDictionaryEntry("Referenced Reference Image Number", "ReferencedReferenceImageNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0008), ElementsDictionaryEntry("Start Cumulative Meterset Weight", "StartCumulativeMetersetWeight",  "DS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0009), ElementsDictionaryEntry("End Cumulative Meterset Weight", "EndCumulativeMetersetWeight",  "DS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x000a), ElementsDictionaryEntry("Referenced Brachy Application Setup Sequence", "ReferencedBrachyApplicationSetupSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x000c), ElementsDictionaryEntry("Referenced Brachy Application Setup Number", "ReferencedBrachyApplicationSetupNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x000e), ElementsDictionaryEntry("Referenced Source Number", "ReferencedSourceNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0020), ElementsDictionaryEntry("Referenced Fraction Group Sequence", "ReferencedFractionGroupSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0022), ElementsDictionaryEntry("Referenced Fraction Group Number", "ReferencedFractionGroupNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0040), ElementsDictionaryEntry("Referenced Verification Image Sequence", "ReferencedVerificationImageSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0042), ElementsDictionaryEntry("Referenced Reference Image Sequence", "ReferencedReferenceImageSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0050), ElementsDictionaryEntry("Referenced Dose Reference Sequence", "ReferencedDoseReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0051), ElementsDictionaryEntry("Referenced Dose Reference Number", "ReferencedDoseReferenceNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0055), ElementsDictionaryEntry("Brachy Referenced Dose Reference Sequence", "BrachyReferencedDoseReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0060), ElementsDictionaryEntry("Referenced Structure Set Sequence", "ReferencedStructureSetSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x006a), ElementsDictionaryEntry("Referenced Patient Setup Number", "ReferencedPatientSetupNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0080), ElementsDictionaryEntry("Referenced Dose Sequence", "ReferencedDoseSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x00a0), ElementsDictionaryEntry("Referenced Tolerance Table Number", "ReferencedToleranceTableNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x00b0), ElementsDictionaryEntry("Referenced Bolus Sequence", "ReferencedBolusSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x00c0), ElementsDictionaryEntry("Referenced Wedge Number", "ReferencedWedgeNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x00d0), ElementsDictionaryEntry("Referenced Compensator Number", "ReferencedCompensatorNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x00e0), ElementsDictionaryEntry("Referenced Block Number", "ReferencedBlockNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x00f0), ElementsDictionaryEntry("Referenced Control Point Index", "ReferencedControlPointIndex",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x00f2), ElementsDictionaryEntry("Referenced Control Point Sequence", "ReferencedControlPointSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x00f4), ElementsDictionaryEntry("Referenced Start Control Point Index", "ReferencedStartControlPointIndex",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x00f6), ElementsDictionaryEntry("Referenced Stop Control Point Index", "ReferencedStopControlPointIndex",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0100), ElementsDictionaryEntry("Referenced Range Shifter Number", "ReferencedRangeShifterNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0102), ElementsDictionaryEntry("Referenced Lateral Spreading Device Number", "ReferencedLateralSpreadingDeviceNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0104), ElementsDictionaryEntry("Referenced Range Modulator Number", "ReferencedRangeModulatorNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0111), ElementsDictionaryEntry("Omitted Beam Task Sequence", "OmittedBeamTaskSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0112), ElementsDictionaryEntry("Reason for Omission", "ReasonForOmission",  "CS", "1"));
    public_dictionary.emplace(Tag(0x300c, 0x0113), ElementsDictionaryEntry("Reason for Omission Description", "ReasonForOmissionDescription",  "LO", "1"));

    public_tags.emplace("ReferencedRTPlanSequence", Tag(0x300c, 0x0002));
    public_tags.emplace("ReferencedBeamSequence", Tag(0x300c, 0x0004));
    public_tags.emplace("ReferencedBeamNumber", Tag(0x300c, 0x0006));
    public_tags.emplace("ReferencedReferenceImageNumber", Tag(0x300c, 0x0007));
    public_tags.emplace("StartCumulativeMetersetWeight", Tag(0x300c, 0x0008));
    public_tags.emplace("EndCumulativeMetersetWeight", Tag(0x300c, 0x0009));
    public_tags.emplace("ReferencedBrachyApplicationSetupSequence", Tag(0x300c, 0x000a));
    public_tags.emplace("ReferencedBrachyApplicationSetupNumber", Tag(0x300c, 0x000c));
    public_tags.emplace("ReferencedSourceNumber", Tag(0x300c, 0x000e));
    public_tags.emplace("ReferencedFractionGroupSequence", Tag(0x300c, 0x0020));
    public_tags.emplace("ReferencedFractionGroupNumber", Tag(0x300c, 0x0022));
    public_tags.emplace("ReferencedVerificationImageSequence", Tag(0x300c, 0x0040));
    public_tags.emplace("ReferencedReferenceImageSequence", Tag(0x300c, 0x0042));
    public_tags.emplace("ReferencedDoseReferenceSequence", Tag(0x300c, 0x0050));
    public_tags.emplace("ReferencedDoseReferenceNumber", Tag(0x300c, 0x0051));
    public_tags.emplace("BrachyReferencedDoseReferenceSequence", Tag(0x300c, 0x0055));
    public_tags.emplace("ReferencedStructureSetSequence", Tag(0x300c, 0x0060));
    public_tags.emplace("ReferencedPatientSetupNumber", Tag(0x300c, 0x006a));
    public_tags.emplace("ReferencedDoseSequence", Tag(0x300c, 0x0080));
    public_tags.emplace("ReferencedToleranceTableNumber", Tag(0x300c, 0x00a0));
    public_tags.emplace("ReferencedBolusSequence", Tag(0x300c, 0x00b0));
    public_tags.emplace("ReferencedWedgeNumber", Tag(0x300c, 0x00c0));
    public_tags.emplace("ReferencedCompensatorNumber", Tag(0x300c, 0x00d0));
    public_tags.emplace("ReferencedBlockNumber", Tag(0x300c, 0x00e0));
    public_tags.emplace("ReferencedControlPointIndex", Tag(0x300c, 0x00f0));
    public_tags.emplace("ReferencedControlPointSequence", Tag(0x300c, 0x00f2));
    public_tags.emplace("ReferencedStartControlPointIndex", Tag(0x300c, 0x00f4));
    public_tags.emplace("ReferencedStopControlPointIndex", Tag(0x300c, 0x00f6));
    public_tags.emplace("ReferencedRangeShifterNumber", Tag(0x300c, 0x0100));
    public_tags.emplace("ReferencedLateralSpreadingDeviceNumber", Tag(0x300c, 0x0102));
    public_tags.emplace("ReferencedRangeModulatorNumber", Tag(0x300c, 0x0104));
    public_tags.emplace("OmittedBeamTaskSequence", Tag(0x300c, 0x0111));
    public_tags.emplace("ReasonForOmission", Tag(0x300c, 0x0112));
    public_tags.emplace("ReasonForOmissionDescription", Tag(0x300c, 0x0113));
}

}

}