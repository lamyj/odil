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

void update_0082(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0082, 0x0001), ElementsDictionaryEntry("Assessment Summary", "AssessmentSummary",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0003), ElementsDictionaryEntry("Assessment Summary Description", "AssessmentSummaryDescription",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0004), ElementsDictionaryEntry("Assessed SOP Instance Sequence", "AssessedSOPInstanceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0005), ElementsDictionaryEntry("Referenced Comparison SOP Instance Sequence", "ReferencedComparisonSOPInstanceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0006), ElementsDictionaryEntry("Number of Assessment Observations", "NumberOfAssessmentObservations",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0007), ElementsDictionaryEntry("Assessment Observations Sequence", "AssessmentObservationsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0008), ElementsDictionaryEntry("Observation Significance", "ObservationSignificance",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x000a), ElementsDictionaryEntry("Observation Description", "ObservationDescription",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x000c), ElementsDictionaryEntry("Structured Constraint Observation Sequence", "StructuredConstraintObservationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0010), ElementsDictionaryEntry("Assessed Attribute Value Sequence", "AssessedAttributeValueSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0016), ElementsDictionaryEntry("Assessment Set ID", "AssessmentSetID",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0017), ElementsDictionaryEntry("Assessment Requester Sequence", "AssessmentRequesterSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0018), ElementsDictionaryEntry("Selector Attribute Name", "SelectorAttributeName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0019), ElementsDictionaryEntry("Selector Attribute Keyword", "SelectorAttributeKeyword",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0021), ElementsDictionaryEntry("Assessment Type Code Sequence", "AssessmentTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0022), ElementsDictionaryEntry("Observation Basis Code Sequence", "ObservationBasisCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0023), ElementsDictionaryEntry("Assessment Label", "AssessmentLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0032), ElementsDictionaryEntry("Constraint Type", "ConstraintType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0033), ElementsDictionaryEntry("Specification Selection Guidance", "SpecificationSelectionGuidance",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0034), ElementsDictionaryEntry("Constraint Value Sequence", "ConstraintValueSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0035), ElementsDictionaryEntry("Recommended Default Value Sequence", "RecommendedDefaultValueSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0036), ElementsDictionaryEntry("Constraint Violation Significance", "ConstraintViolationSignificance",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0037), ElementsDictionaryEntry("Constraint Violation Condition", "ConstraintViolationCondition",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0082, 0x0038), ElementsDictionaryEntry("Modifiable Constraint Flag", "ModifiableConstraintFlag",  "CS", "1"));

    public_tags.emplace("AssessmentSummary", Tag(0x0082, 0x0001));
    public_tags.emplace("AssessmentSummaryDescription", Tag(0x0082, 0x0003));
    public_tags.emplace("AssessedSOPInstanceSequence", Tag(0x0082, 0x0004));
    public_tags.emplace("ReferencedComparisonSOPInstanceSequence", Tag(0x0082, 0x0005));
    public_tags.emplace("NumberOfAssessmentObservations", Tag(0x0082, 0x0006));
    public_tags.emplace("AssessmentObservationsSequence", Tag(0x0082, 0x0007));
    public_tags.emplace("ObservationSignificance", Tag(0x0082, 0x0008));
    public_tags.emplace("ObservationDescription", Tag(0x0082, 0x000a));
    public_tags.emplace("StructuredConstraintObservationSequence", Tag(0x0082, 0x000c));
    public_tags.emplace("AssessedAttributeValueSequence", Tag(0x0082, 0x0010));
    public_tags.emplace("AssessmentSetID", Tag(0x0082, 0x0016));
    public_tags.emplace("AssessmentRequesterSequence", Tag(0x0082, 0x0017));
    public_tags.emplace("SelectorAttributeName", Tag(0x0082, 0x0018));
    public_tags.emplace("SelectorAttributeKeyword", Tag(0x0082, 0x0019));
    public_tags.emplace("AssessmentTypeCodeSequence", Tag(0x0082, 0x0021));
    public_tags.emplace("ObservationBasisCodeSequence", Tag(0x0082, 0x0022));
    public_tags.emplace("AssessmentLabel", Tag(0x0082, 0x0023));
    public_tags.emplace("ConstraintType", Tag(0x0082, 0x0032));
    public_tags.emplace("SpecificationSelectionGuidance", Tag(0x0082, 0x0033));
    public_tags.emplace("ConstraintValueSequence", Tag(0x0082, 0x0034));
    public_tags.emplace("RecommendedDefaultValueSequence", Tag(0x0082, 0x0035));
    public_tags.emplace("ConstraintViolationSignificance", Tag(0x0082, 0x0036));
    public_tags.emplace("ConstraintViolationCondition", Tag(0x0082, 0x0037));
    public_tags.emplace("ModifiableConstraintFlag", Tag(0x0082, 0x0038));
}

}

}