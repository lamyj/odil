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

void update_3006(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x3006, 0x0002), ElementsDictionaryEntry("Structure Set Label", "StructureSetLabel",  "SH", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0004), ElementsDictionaryEntry("Structure Set Name", "StructureSetName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0006), ElementsDictionaryEntry("Structure Set Description", "StructureSetDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0008), ElementsDictionaryEntry("Structure Set Date", "StructureSetDate",  "DA", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0009), ElementsDictionaryEntry("Structure Set Time", "StructureSetTime",  "TM", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0010), ElementsDictionaryEntry("Referenced Frame of Reference Sequence", "ReferencedFrameOfReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0012), ElementsDictionaryEntry("RT Referenced Study Sequence", "RTReferencedStudySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0014), ElementsDictionaryEntry("RT Referenced Series Sequence", "RTReferencedSeriesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0016), ElementsDictionaryEntry("Contour Image Sequence", "ContourImageSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0018), ElementsDictionaryEntry("Predecessor Structure Set Sequence", "PredecessorStructureSetSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0020), ElementsDictionaryEntry("Structure Set ROI Sequence", "StructureSetROISequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0022), ElementsDictionaryEntry("ROI Number", "ROINumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0024), ElementsDictionaryEntry("Referenced Frame of Reference UID", "ReferencedFrameOfReferenceUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0026), ElementsDictionaryEntry("ROI Name", "ROIName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0028), ElementsDictionaryEntry("ROI Description", "ROIDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x002a), ElementsDictionaryEntry("ROI Display Color", "ROIDisplayColor",  "IS", "3"));
    public_dictionary.emplace(Tag(0x3006, 0x002c), ElementsDictionaryEntry("ROI Volume", "ROIVolume",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0030), ElementsDictionaryEntry("RT Related ROI Sequence", "RTRelatedROISequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0033), ElementsDictionaryEntry("RT ROI Relationship", "RTROIRelationship",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0036), ElementsDictionaryEntry("ROI Generation Algorithm", "ROIGenerationAlgorithm",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0037), ElementsDictionaryEntry("ROI Derivation Algorithm Identification Sequence", "ROIDerivationAlgorithmIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0038), ElementsDictionaryEntry("ROI Generation Description", "ROIGenerationDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0039), ElementsDictionaryEntry("ROI Contour Sequence", "ROIContourSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0040), ElementsDictionaryEntry("Contour Sequence", "ContourSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0042), ElementsDictionaryEntry("Contour Geometric Type", "ContourGeometricType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0044), ElementsDictionaryEntry("Contour Slab Thickness", "ContourSlabThickness",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0045), ElementsDictionaryEntry("Contour Offset Vector", "ContourOffsetVector",  "DS", "3"));
    public_dictionary.emplace(Tag(0x3006, 0x0046), ElementsDictionaryEntry("Number of Contour Points", "NumberOfContourPoints",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0048), ElementsDictionaryEntry("Contour Number", "ContourNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0049), ElementsDictionaryEntry("Attached Contours", "AttachedContours",  "IS", "1-n"));
    public_dictionary.emplace(Tag(0x3006, 0x0050), ElementsDictionaryEntry("Contour Data", "ContourData",  "DS", "3-3n"));
    public_dictionary.emplace(Tag(0x3006, 0x0080), ElementsDictionaryEntry("RT ROI Observations Sequence", "RTROIObservationsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0082), ElementsDictionaryEntry("Observation Number", "ObservationNumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0084), ElementsDictionaryEntry("Referenced ROI Number", "ReferencedROINumber",  "IS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0085), ElementsDictionaryEntry("ROI Observation Label", "ROIObservationLabel",  "SH", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0086), ElementsDictionaryEntry("RT ROI Identification Code Sequence", "RTROIIdentificationCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x0088), ElementsDictionaryEntry("ROI Observation Description", "ROIObservationDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00a0), ElementsDictionaryEntry("Related RT ROI Observations Sequence", "RelatedRTROIObservationsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00a4), ElementsDictionaryEntry("RT ROI Interpreted Type", "RTROIInterpretedType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00a6), ElementsDictionaryEntry("ROI Interpreter", "ROIInterpreter",  "PN", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00b0), ElementsDictionaryEntry("ROI Physical Properties Sequence", "ROIPhysicalPropertiesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00b2), ElementsDictionaryEntry("ROI Physical Property", "ROIPhysicalProperty",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00b4), ElementsDictionaryEntry("ROI Physical Property Value", "ROIPhysicalPropertyValue",  "DS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00b6), ElementsDictionaryEntry("ROI Elemental Composition Sequence", "ROIElementalCompositionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00b7), ElementsDictionaryEntry("ROI Elemental Composition Atomic Number", "ROIElementalCompositionAtomicNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00b8), ElementsDictionaryEntry("ROI Elemental Composition Atomic Mass Fraction", "ROIElementalCompositionAtomicMassFraction",  "FL", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00b9), ElementsDictionaryEntry("Additional RT ROI Identification Code Sequence", "AdditionalRTROIIdentificationCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00c0), ElementsDictionaryEntry("Frame of Reference Relationship Sequence", "FrameOfReferenceRelationshipSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00c2), ElementsDictionaryEntry("Related Frame of Reference UID", "RelatedFrameOfReferenceUID",  "UI", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00c4), ElementsDictionaryEntry("Frame of Reference Transformation Type", "FrameOfReferenceTransformationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x3006, 0x00c6), ElementsDictionaryEntry("Frame of Reference Transformation Matrix", "FrameOfReferenceTransformationMatrix",  "DS", "16"));
    public_dictionary.emplace(Tag(0x3006, 0x00c8), ElementsDictionaryEntry("Frame of Reference Transformation Comment", "FrameOfReferenceTransformationComment",  "LO", "1"));

    public_tags.emplace("StructureSetLabel", Tag(0x3006, 0x0002));
    public_tags.emplace("StructureSetName", Tag(0x3006, 0x0004));
    public_tags.emplace("StructureSetDescription", Tag(0x3006, 0x0006));
    public_tags.emplace("StructureSetDate", Tag(0x3006, 0x0008));
    public_tags.emplace("StructureSetTime", Tag(0x3006, 0x0009));
    public_tags.emplace("ReferencedFrameOfReferenceSequence", Tag(0x3006, 0x0010));
    public_tags.emplace("RTReferencedStudySequence", Tag(0x3006, 0x0012));
    public_tags.emplace("RTReferencedSeriesSequence", Tag(0x3006, 0x0014));
    public_tags.emplace("ContourImageSequence", Tag(0x3006, 0x0016));
    public_tags.emplace("PredecessorStructureSetSequence", Tag(0x3006, 0x0018));
    public_tags.emplace("StructureSetROISequence", Tag(0x3006, 0x0020));
    public_tags.emplace("ROINumber", Tag(0x3006, 0x0022));
    public_tags.emplace("ReferencedFrameOfReferenceUID", Tag(0x3006, 0x0024));
    public_tags.emplace("ROIName", Tag(0x3006, 0x0026));
    public_tags.emplace("ROIDescription", Tag(0x3006, 0x0028));
    public_tags.emplace("ROIDisplayColor", Tag(0x3006, 0x002a));
    public_tags.emplace("ROIVolume", Tag(0x3006, 0x002c));
    public_tags.emplace("RTRelatedROISequence", Tag(0x3006, 0x0030));
    public_tags.emplace("RTROIRelationship", Tag(0x3006, 0x0033));
    public_tags.emplace("ROIGenerationAlgorithm", Tag(0x3006, 0x0036));
    public_tags.emplace("ROIDerivationAlgorithmIdentificationSequence", Tag(0x3006, 0x0037));
    public_tags.emplace("ROIGenerationDescription", Tag(0x3006, 0x0038));
    public_tags.emplace("ROIContourSequence", Tag(0x3006, 0x0039));
    public_tags.emplace("ContourSequence", Tag(0x3006, 0x0040));
    public_tags.emplace("ContourGeometricType", Tag(0x3006, 0x0042));
    public_tags.emplace("ContourSlabThickness", Tag(0x3006, 0x0044));
    public_tags.emplace("ContourOffsetVector", Tag(0x3006, 0x0045));
    public_tags.emplace("NumberOfContourPoints", Tag(0x3006, 0x0046));
    public_tags.emplace("ContourNumber", Tag(0x3006, 0x0048));
    public_tags.emplace("AttachedContours", Tag(0x3006, 0x0049));
    public_tags.emplace("ContourData", Tag(0x3006, 0x0050));
    public_tags.emplace("RTROIObservationsSequence", Tag(0x3006, 0x0080));
    public_tags.emplace("ObservationNumber", Tag(0x3006, 0x0082));
    public_tags.emplace("ReferencedROINumber", Tag(0x3006, 0x0084));
    public_tags.emplace("ROIObservationLabel", Tag(0x3006, 0x0085));
    public_tags.emplace("RTROIIdentificationCodeSequence", Tag(0x3006, 0x0086));
    public_tags.emplace("ROIObservationDescription", Tag(0x3006, 0x0088));
    public_tags.emplace("RelatedRTROIObservationsSequence", Tag(0x3006, 0x00a0));
    public_tags.emplace("RTROIInterpretedType", Tag(0x3006, 0x00a4));
    public_tags.emplace("ROIInterpreter", Tag(0x3006, 0x00a6));
    public_tags.emplace("ROIPhysicalPropertiesSequence", Tag(0x3006, 0x00b0));
    public_tags.emplace("ROIPhysicalProperty", Tag(0x3006, 0x00b2));
    public_tags.emplace("ROIPhysicalPropertyValue", Tag(0x3006, 0x00b4));
    public_tags.emplace("ROIElementalCompositionSequence", Tag(0x3006, 0x00b6));
    public_tags.emplace("ROIElementalCompositionAtomicNumber", Tag(0x3006, 0x00b7));
    public_tags.emplace("ROIElementalCompositionAtomicMassFraction", Tag(0x3006, 0x00b8));
    public_tags.emplace("AdditionalRTROIIdentificationCodeSequence", Tag(0x3006, 0x00b9));
    public_tags.emplace("FrameOfReferenceRelationshipSequence", Tag(0x3006, 0x00c0));
    public_tags.emplace("RelatedFrameOfReferenceUID", Tag(0x3006, 0x00c2));
    public_tags.emplace("FrameOfReferenceTransformationType", Tag(0x3006, 0x00c4));
    public_tags.emplace("FrameOfReferenceTransformationMatrix", Tag(0x3006, 0x00c6));
    public_tags.emplace("FrameOfReferenceTransformationComment", Tag(0x3006, 0x00c8));
}

}

}