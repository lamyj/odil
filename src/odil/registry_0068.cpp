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

void update_0068(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0068, 0x6210), ElementsDictionaryEntry("Implant Size", "ImplantSize",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6221), ElementsDictionaryEntry("Implant Template Version", "ImplantTemplateVersion",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6222), ElementsDictionaryEntry("Replaced Implant Template Sequence", "ReplacedImplantTemplateSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6223), ElementsDictionaryEntry("Implant Type", "ImplantType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6224), ElementsDictionaryEntry("Derivation Implant Template Sequence", "DerivationImplantTemplateSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6225), ElementsDictionaryEntry("Original Implant Template Sequence", "OriginalImplantTemplateSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6226), ElementsDictionaryEntry("Effective DateTime", "EffectiveDateTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6230), ElementsDictionaryEntry("Implant Target Anatomy Sequence", "ImplantTargetAnatomySequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6260), ElementsDictionaryEntry("Information From Manufacturer Sequence", "InformationFromManufacturerSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6265), ElementsDictionaryEntry("Notification From Manufacturer Sequence", "NotificationFromManufacturerSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6270), ElementsDictionaryEntry("Information Issue DateTime", "InformationIssueDateTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6280), ElementsDictionaryEntry("Information Summary", "InformationSummary",  "ST", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x62a0), ElementsDictionaryEntry("Implant Regulatory Disapproval Code Sequence", "ImplantRegulatoryDisapprovalCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x62a5), ElementsDictionaryEntry("Overall Template Spatial Tolerance", "OverallTemplateSpatialTolerance",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x62c0), ElementsDictionaryEntry("HPGL Document Sequence", "HPGLDocumentSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x62d0), ElementsDictionaryEntry("HPGL Document ID", "HPGLDocumentID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x62d5), ElementsDictionaryEntry("HPGL Document Label", "HPGLDocumentLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x62e0), ElementsDictionaryEntry("View Orientation Code Sequence", "ViewOrientationCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x62f0), ElementsDictionaryEntry("View Orientation Modifier Code Sequence", "ViewOrientationModifierCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x62f2), ElementsDictionaryEntry("HPGL Document Scaling", "HPGLDocumentScaling",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6300), ElementsDictionaryEntry("HPGL Document", "HPGLDocument",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6310), ElementsDictionaryEntry("HPGL Contour Pen Number", "HPGLContourPenNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6320), ElementsDictionaryEntry("HPGL Pen Sequence", "HPGLPenSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6330), ElementsDictionaryEntry("HPGL Pen Number", "HPGLPenNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6340), ElementsDictionaryEntry("HPGL Pen Label", "HPGLPenLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6345), ElementsDictionaryEntry("HPGL Pen Description", "HPGLPenDescription",  "ST", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6346), ElementsDictionaryEntry("Recommended Rotation Point", "RecommendedRotationPoint",  "FD", "2"));
    public_dictionary.emplace(Tag(0x0068, 0x6347), ElementsDictionaryEntry("Bounding Rectangle", "BoundingRectangle",  "FD", "4"));
    public_dictionary.emplace(Tag(0x0068, 0x6350), ElementsDictionaryEntry("Implant Template 3D Model Surface Number", "ImplantTemplate3DModelSurfaceNumber",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0068, 0x6360), ElementsDictionaryEntry("Surface Model Description Sequence", "SurfaceModelDescriptionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6380), ElementsDictionaryEntry("Surface Model Label", "SurfaceModelLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6390), ElementsDictionaryEntry("Surface Model Scaling Factor", "SurfaceModelScalingFactor",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x63a0), ElementsDictionaryEntry("Materials Code Sequence", "MaterialsCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x63a4), ElementsDictionaryEntry("Coating Materials Code Sequence", "CoatingMaterialsCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x63a8), ElementsDictionaryEntry("Implant Type Code Sequence", "ImplantTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x63ac), ElementsDictionaryEntry("Fixation Method Code Sequence", "FixationMethodCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x63b0), ElementsDictionaryEntry("Mating Feature Sets Sequence", "MatingFeatureSetsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x63c0), ElementsDictionaryEntry("Mating Feature Set ID", "MatingFeatureSetID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x63d0), ElementsDictionaryEntry("Mating Feature Set Label", "MatingFeatureSetLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x63e0), ElementsDictionaryEntry("Mating Feature Sequence", "MatingFeatureSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x63f0), ElementsDictionaryEntry("Mating Feature ID", "MatingFeatureID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6400), ElementsDictionaryEntry("Mating Feature Degree of Freedom Sequence", "MatingFeatureDegreeOfFreedomSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6410), ElementsDictionaryEntry("Degree of Freedom ID", "DegreeOfFreedomID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6420), ElementsDictionaryEntry("Degree of Freedom Type", "DegreeOfFreedomType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6430), ElementsDictionaryEntry("2D Mating Feature Coordinates Sequence", "TwoDMatingFeatureCoordinatesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6440), ElementsDictionaryEntry("Referenced HPGL Document ID", "ReferencedHPGLDocumentID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6450), ElementsDictionaryEntry("2D Mating Point", "TwoDMatingPoint",  "FD", "2"));
    public_dictionary.emplace(Tag(0x0068, 0x6460), ElementsDictionaryEntry("2D Mating Axes", "TwoDMatingAxes",  "FD", "4"));
    public_dictionary.emplace(Tag(0x0068, 0x6470), ElementsDictionaryEntry("2D Degree of Freedom Sequence", "TwoDDegreeOfFreedomSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6490), ElementsDictionaryEntry("3D Degree of Freedom Axis", "ThreeDDegreeOfFreedomAxis",  "FD", "3"));
    public_dictionary.emplace(Tag(0x0068, 0x64a0), ElementsDictionaryEntry("Range of Freedom", "RangeOfFreedom",  "FD", "2"));
    public_dictionary.emplace(Tag(0x0068, 0x64c0), ElementsDictionaryEntry("3D Mating Point", "ThreeDMatingPoint",  "FD", "3"));
    public_dictionary.emplace(Tag(0x0068, 0x64d0), ElementsDictionaryEntry("3D Mating Axes", "ThreeDMatingAxes",  "FD", "9"));
    public_dictionary.emplace(Tag(0x0068, 0x64f0), ElementsDictionaryEntry("2D Degree of Freedom Axis", "TwoDDegreeOfFreedomAxis",  "FD", "3"));
    public_dictionary.emplace(Tag(0x0068, 0x6500), ElementsDictionaryEntry("Planning Landmark Point Sequence", "PlanningLandmarkPointSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6510), ElementsDictionaryEntry("Planning Landmark Line Sequence", "PlanningLandmarkLineSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6520), ElementsDictionaryEntry("Planning Landmark Plane Sequence", "PlanningLandmarkPlaneSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6530), ElementsDictionaryEntry("Planning Landmark ID", "PlanningLandmarkID",  "US", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6540), ElementsDictionaryEntry("Planning Landmark Description", "PlanningLandmarkDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6545), ElementsDictionaryEntry("Planning Landmark Identification Code Sequence", "PlanningLandmarkIdentificationCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6550), ElementsDictionaryEntry("2D Point Coordinates Sequence", "TwoDPointCoordinatesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x6560), ElementsDictionaryEntry("2D Point Coordinates", "TwoDPointCoordinates",  "FD", "2"));
    public_dictionary.emplace(Tag(0x0068, 0x6590), ElementsDictionaryEntry("3D Point Coordinates", "ThreeDPointCoordinates",  "FD", "3"));
    public_dictionary.emplace(Tag(0x0068, 0x65a0), ElementsDictionaryEntry("2D Line Coordinates Sequence", "TwoDLineCoordinatesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x65b0), ElementsDictionaryEntry("2D Line Coordinates", "TwoDLineCoordinates",  "FD", "4"));
    public_dictionary.emplace(Tag(0x0068, 0x65d0), ElementsDictionaryEntry("3D Line Coordinates", "ThreeDLineCoordinates",  "FD", "6"));
    public_dictionary.emplace(Tag(0x0068, 0x65e0), ElementsDictionaryEntry("2D Plane Coordinates Sequence", "TwoDPlaneCoordinatesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x65f0), ElementsDictionaryEntry("2D Plane Intersection", "TwoDPlaneIntersection",  "FD", "4"));
    public_dictionary.emplace(Tag(0x0068, 0x6610), ElementsDictionaryEntry("3D Plane Origin", "ThreeDPlaneOrigin",  "FD", "3"));
    public_dictionary.emplace(Tag(0x0068, 0x6620), ElementsDictionaryEntry("3D Plane Normal", "ThreeDPlaneNormal",  "FD", "3"));
    public_dictionary.emplace(Tag(0x0068, 0x7001), ElementsDictionaryEntry("Model Modification", "ModelModification",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x7002), ElementsDictionaryEntry("Model Mirroring", "ModelMirroring",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0068, 0x7003), ElementsDictionaryEntry("Model Usage Code Sequence", "ModelUsageCodeSequence",  "SQ", "1"));

    public_tags.emplace("ImplantSize", Tag(0x0068, 0x6210));
    public_tags.emplace("ImplantTemplateVersion", Tag(0x0068, 0x6221));
    public_tags.emplace("ReplacedImplantTemplateSequence", Tag(0x0068, 0x6222));
    public_tags.emplace("ImplantType", Tag(0x0068, 0x6223));
    public_tags.emplace("DerivationImplantTemplateSequence", Tag(0x0068, 0x6224));
    public_tags.emplace("OriginalImplantTemplateSequence", Tag(0x0068, 0x6225));
    public_tags.emplace("EffectiveDateTime", Tag(0x0068, 0x6226));
    public_tags.emplace("ImplantTargetAnatomySequence", Tag(0x0068, 0x6230));
    public_tags.emplace("InformationFromManufacturerSequence", Tag(0x0068, 0x6260));
    public_tags.emplace("NotificationFromManufacturerSequence", Tag(0x0068, 0x6265));
    public_tags.emplace("InformationIssueDateTime", Tag(0x0068, 0x6270));
    public_tags.emplace("InformationSummary", Tag(0x0068, 0x6280));
    public_tags.emplace("ImplantRegulatoryDisapprovalCodeSequence", Tag(0x0068, 0x62a0));
    public_tags.emplace("OverallTemplateSpatialTolerance", Tag(0x0068, 0x62a5));
    public_tags.emplace("HPGLDocumentSequence", Tag(0x0068, 0x62c0));
    public_tags.emplace("HPGLDocumentID", Tag(0x0068, 0x62d0));
    public_tags.emplace("HPGLDocumentLabel", Tag(0x0068, 0x62d5));
    public_tags.emplace("ViewOrientationCodeSequence", Tag(0x0068, 0x62e0));
    public_tags.emplace("ViewOrientationModifierCodeSequence", Tag(0x0068, 0x62f0));
    public_tags.emplace("HPGLDocumentScaling", Tag(0x0068, 0x62f2));
    public_tags.emplace("HPGLDocument", Tag(0x0068, 0x6300));
    public_tags.emplace("HPGLContourPenNumber", Tag(0x0068, 0x6310));
    public_tags.emplace("HPGLPenSequence", Tag(0x0068, 0x6320));
    public_tags.emplace("HPGLPenNumber", Tag(0x0068, 0x6330));
    public_tags.emplace("HPGLPenLabel", Tag(0x0068, 0x6340));
    public_tags.emplace("HPGLPenDescription", Tag(0x0068, 0x6345));
    public_tags.emplace("RecommendedRotationPoint", Tag(0x0068, 0x6346));
    public_tags.emplace("BoundingRectangle", Tag(0x0068, 0x6347));
    public_tags.emplace("ImplantTemplate3DModelSurfaceNumber", Tag(0x0068, 0x6350));
    public_tags.emplace("SurfaceModelDescriptionSequence", Tag(0x0068, 0x6360));
    public_tags.emplace("SurfaceModelLabel", Tag(0x0068, 0x6380));
    public_tags.emplace("SurfaceModelScalingFactor", Tag(0x0068, 0x6390));
    public_tags.emplace("MaterialsCodeSequence", Tag(0x0068, 0x63a0));
    public_tags.emplace("CoatingMaterialsCodeSequence", Tag(0x0068, 0x63a4));
    public_tags.emplace("ImplantTypeCodeSequence", Tag(0x0068, 0x63a8));
    public_tags.emplace("FixationMethodCodeSequence", Tag(0x0068, 0x63ac));
    public_tags.emplace("MatingFeatureSetsSequence", Tag(0x0068, 0x63b0));
    public_tags.emplace("MatingFeatureSetID", Tag(0x0068, 0x63c0));
    public_tags.emplace("MatingFeatureSetLabel", Tag(0x0068, 0x63d0));
    public_tags.emplace("MatingFeatureSequence", Tag(0x0068, 0x63e0));
    public_tags.emplace("MatingFeatureID", Tag(0x0068, 0x63f0));
    public_tags.emplace("MatingFeatureDegreeOfFreedomSequence", Tag(0x0068, 0x6400));
    public_tags.emplace("DegreeOfFreedomID", Tag(0x0068, 0x6410));
    public_tags.emplace("DegreeOfFreedomType", Tag(0x0068, 0x6420));
    public_tags.emplace("TwoDMatingFeatureCoordinatesSequence", Tag(0x0068, 0x6430));
    public_tags.emplace("ReferencedHPGLDocumentID", Tag(0x0068, 0x6440));
    public_tags.emplace("TwoDMatingPoint", Tag(0x0068, 0x6450));
    public_tags.emplace("TwoDMatingAxes", Tag(0x0068, 0x6460));
    public_tags.emplace("TwoDDegreeOfFreedomSequence", Tag(0x0068, 0x6470));
    public_tags.emplace("ThreeDDegreeOfFreedomAxis", Tag(0x0068, 0x6490));
    public_tags.emplace("RangeOfFreedom", Tag(0x0068, 0x64a0));
    public_tags.emplace("ThreeDMatingPoint", Tag(0x0068, 0x64c0));
    public_tags.emplace("ThreeDMatingAxes", Tag(0x0068, 0x64d0));
    public_tags.emplace("TwoDDegreeOfFreedomAxis", Tag(0x0068, 0x64f0));
    public_tags.emplace("PlanningLandmarkPointSequence", Tag(0x0068, 0x6500));
    public_tags.emplace("PlanningLandmarkLineSequence", Tag(0x0068, 0x6510));
    public_tags.emplace("PlanningLandmarkPlaneSequence", Tag(0x0068, 0x6520));
    public_tags.emplace("PlanningLandmarkID", Tag(0x0068, 0x6530));
    public_tags.emplace("PlanningLandmarkDescription", Tag(0x0068, 0x6540));
    public_tags.emplace("PlanningLandmarkIdentificationCodeSequence", Tag(0x0068, 0x6545));
    public_tags.emplace("TwoDPointCoordinatesSequence", Tag(0x0068, 0x6550));
    public_tags.emplace("TwoDPointCoordinates", Tag(0x0068, 0x6560));
    public_tags.emplace("ThreeDPointCoordinates", Tag(0x0068, 0x6590));
    public_tags.emplace("TwoDLineCoordinatesSequence", Tag(0x0068, 0x65a0));
    public_tags.emplace("TwoDLineCoordinates", Tag(0x0068, 0x65b0));
    public_tags.emplace("ThreeDLineCoordinates", Tag(0x0068, 0x65d0));
    public_tags.emplace("TwoDPlaneCoordinatesSequence", Tag(0x0068, 0x65e0));
    public_tags.emplace("TwoDPlaneIntersection", Tag(0x0068, 0x65f0));
    public_tags.emplace("ThreeDPlaneOrigin", Tag(0x0068, 0x6610));
    public_tags.emplace("ThreeDPlaneNormal", Tag(0x0068, 0x6620));
    public_tags.emplace("ModelModification", Tag(0x0068, 0x7001));
    public_tags.emplace("ModelMirroring", Tag(0x0068, 0x7002));
    public_tags.emplace("ModelUsageCodeSequence", Tag(0x0068, 0x7003));
}

}

}