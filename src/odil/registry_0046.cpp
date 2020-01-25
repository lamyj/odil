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

void update_0046(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0046, 0x0012), ElementsDictionaryEntry("Lens Description", "LensDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0014), ElementsDictionaryEntry("Right Lens Sequence", "RightLensSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0015), ElementsDictionaryEntry("Left Lens Sequence", "LeftLensSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0016), ElementsDictionaryEntry("Unspecified Laterality Lens Sequence", "UnspecifiedLateralityLensSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0018), ElementsDictionaryEntry("Cylinder Sequence", "CylinderSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0028), ElementsDictionaryEntry("Prism Sequence", "PrismSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0030), ElementsDictionaryEntry("Horizontal Prism Power", "HorizontalPrismPower",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0032), ElementsDictionaryEntry("Horizontal Prism Base", "HorizontalPrismBase",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0034), ElementsDictionaryEntry("Vertical Prism Power", "VerticalPrismPower",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0036), ElementsDictionaryEntry("Vertical Prism Base", "VerticalPrismBase",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0038), ElementsDictionaryEntry("Lens Segment Type", "LensSegmentType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0040), ElementsDictionaryEntry("Optical Transmittance", "OpticalTransmittance",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0042), ElementsDictionaryEntry("Channel Width", "ChannelWidth",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0044), ElementsDictionaryEntry("Pupil Size", "PupilSize",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0046), ElementsDictionaryEntry("Corneal Size", "CornealSize",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0047), ElementsDictionaryEntry("Corneal Size Sequence", "CornealSizeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0050), ElementsDictionaryEntry("Autorefraction Right Eye Sequence", "AutorefractionRightEyeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0052), ElementsDictionaryEntry("Autorefraction Left Eye Sequence", "AutorefractionLeftEyeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0060), ElementsDictionaryEntry("Distance Pupillary Distance", "DistancePupillaryDistance",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0062), ElementsDictionaryEntry("Near Pupillary Distance", "NearPupillaryDistance",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0063), ElementsDictionaryEntry("Intermediate Pupillary Distance", "IntermediatePupillaryDistance",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0064), ElementsDictionaryEntry("Other Pupillary Distance", "OtherPupillaryDistance",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0070), ElementsDictionaryEntry("Keratometry Right Eye Sequence", "KeratometryRightEyeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0071), ElementsDictionaryEntry("Keratometry Left Eye Sequence", "KeratometryLeftEyeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0074), ElementsDictionaryEntry("Steep Keratometric Axis Sequence", "SteepKeratometricAxisSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0075), ElementsDictionaryEntry("Radius of Curvature", "RadiusOfCurvature",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0076), ElementsDictionaryEntry("Keratometric Power", "KeratometricPower",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0077), ElementsDictionaryEntry("Keratometric Axis", "KeratometricAxis",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0080), ElementsDictionaryEntry("Flat Keratometric Axis Sequence", "FlatKeratometricAxisSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0092), ElementsDictionaryEntry("Background Color", "BackgroundColor",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0094), ElementsDictionaryEntry("Optotype", "Optotype",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0095), ElementsDictionaryEntry("Optotype Presentation", "OptotypePresentation",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0097), ElementsDictionaryEntry("Subjective Refraction Right Eye Sequence", "SubjectiveRefractionRightEyeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0098), ElementsDictionaryEntry("Subjective Refraction Left Eye Sequence", "SubjectiveRefractionLeftEyeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0100), ElementsDictionaryEntry("Add Near Sequence", "AddNearSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0101), ElementsDictionaryEntry("Add Intermediate Sequence", "AddIntermediateSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0102), ElementsDictionaryEntry("Add Other Sequence", "AddOtherSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0104), ElementsDictionaryEntry("Add Power", "AddPower",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0106), ElementsDictionaryEntry("Viewing Distance", "ViewingDistance",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0110), ElementsDictionaryEntry("Cornea Measurements Sequence", "CorneaMeasurementsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0111), ElementsDictionaryEntry("Source of Cornea Measurement Data Code Sequence", "SourceOfCorneaMeasurementDataCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0112), ElementsDictionaryEntry("Steep Corneal Axis Sequence", "SteepCornealAxisSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0113), ElementsDictionaryEntry("Flat Corneal Axis Sequence", "FlatCornealAxisSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0114), ElementsDictionaryEntry("Corneal Power", "CornealPower",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0115), ElementsDictionaryEntry("Corneal Axis", "CornealAxis",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0116), ElementsDictionaryEntry("Cornea Measurement Method Code Sequence", "CorneaMeasurementMethodCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0117), ElementsDictionaryEntry("Refractive Index of Cornea", "RefractiveIndexOfCornea",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0118), ElementsDictionaryEntry("Refractive Index of Aqueous Humor", "RefractiveIndexOfAqueousHumor",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0121), ElementsDictionaryEntry("Visual Acuity Type Code Sequence", "VisualAcuityTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0122), ElementsDictionaryEntry("Visual Acuity Right Eye Sequence", "VisualAcuityRightEyeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0123), ElementsDictionaryEntry("Visual Acuity Left Eye Sequence", "VisualAcuityLeftEyeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0124), ElementsDictionaryEntry("Visual Acuity Both Eyes Open Sequence", "VisualAcuityBothEyesOpenSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0125), ElementsDictionaryEntry("Viewing Distance Type", "ViewingDistanceType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0135), ElementsDictionaryEntry("Visual Acuity Modifiers", "VisualAcuityModifiers",  "SS", "2"));
    public_dictionary.emplace(Tag(0x0046, 0x0137), ElementsDictionaryEntry("Decimal Visual Acuity", "DecimalVisualAcuity",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0139), ElementsDictionaryEntry("Optotype Detailed Definition", "OptotypeDetailedDefinition",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0145), ElementsDictionaryEntry("Referenced Refractive Measurements Sequence", "ReferencedRefractiveMeasurementsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0146), ElementsDictionaryEntry("Sphere Power", "SpherePower",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0147), ElementsDictionaryEntry("Cylinder Power", "CylinderPower",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0201), ElementsDictionaryEntry("Corneal Topography Surface", "CornealTopographySurface",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0202), ElementsDictionaryEntry("Corneal Vertex Location", "CornealVertexLocation",  "FL", "2"));
    public_dictionary.emplace(Tag(0x0046, 0x0203), ElementsDictionaryEntry("Pupil Centroid X-Coordinate", "PupilCentroidXCoordinate",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0204), ElementsDictionaryEntry("Pupil Centroid Y-Coordinate", "PupilCentroidYCoordinate",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0205), ElementsDictionaryEntry("Equivalent Pupil Radius", "EquivalentPupilRadius",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0207), ElementsDictionaryEntry("Corneal Topography Map Type Code Sequence", "CornealTopographyMapTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0208), ElementsDictionaryEntry("Vertices of the Outline of Pupil", "VerticesOfTheOutlineOfPupil",  "IS", "2-2n"));
    public_dictionary.emplace(Tag(0x0046, 0x0210), ElementsDictionaryEntry("Corneal Topography Mapping Normals Sequence", "CornealTopographyMappingNormalsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0211), ElementsDictionaryEntry("Maximum Corneal Curvature Sequence", "MaximumCornealCurvatureSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0212), ElementsDictionaryEntry("Maximum Corneal Curvature", "MaximumCornealCurvature",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0213), ElementsDictionaryEntry("Maximum Corneal Curvature Location", "MaximumCornealCurvatureLocation",  "FL", "2"));
    public_dictionary.emplace(Tag(0x0046, 0x0215), ElementsDictionaryEntry("Minimum Keratometric Sequence", "MinimumKeratometricSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0218), ElementsDictionaryEntry("Simulated Keratometric Cylinder Sequence", "SimulatedKeratometricCylinderSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0220), ElementsDictionaryEntry("Average Corneal Power", "AverageCornealPower",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0224), ElementsDictionaryEntry("Corneal I-S Value", "CornealISValue",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0227), ElementsDictionaryEntry("Analyzed Area", "AnalyzedArea",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0230), ElementsDictionaryEntry("Surface Regularity Index", "SurfaceRegularityIndex",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0232), ElementsDictionaryEntry("Surface Asymmetry Index", "SurfaceAsymmetryIndex",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0234), ElementsDictionaryEntry("Corneal Eccentricity Index", "CornealEccentricityIndex",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0236), ElementsDictionaryEntry("Keratoconus Prediction Index", "KeratoconusPredictionIndex",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0238), ElementsDictionaryEntry("Decimal Potential Visual Acuity", "DecimalPotentialVisualAcuity",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0242), ElementsDictionaryEntry("Corneal Topography Map Quality Evaluation", "CornealTopographyMapQualityEvaluation",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0244), ElementsDictionaryEntry("Source Image Corneal Processed Data Sequence", "SourceImageCornealProcessedDataSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0247), ElementsDictionaryEntry("Corneal Point Location", "CornealPointLocation",  "FL", "3"));
    public_dictionary.emplace(Tag(0x0046, 0x0248), ElementsDictionaryEntry("Corneal Point Estimated", "CornealPointEstimated",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0249), ElementsDictionaryEntry("Axial Power", "AxialPower",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0250), ElementsDictionaryEntry("Tangential Power", "TangentialPower",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0251), ElementsDictionaryEntry("Refractive Power", "RefractivePower",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0252), ElementsDictionaryEntry("Relative Elevation", "RelativeElevation",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0046, 0x0253), ElementsDictionaryEntry("Corneal Wavefront", "CornealWavefront",  "FL", "1"));

    public_tags.emplace("LensDescription", Tag(0x0046, 0x0012));
    public_tags.emplace("RightLensSequence", Tag(0x0046, 0x0014));
    public_tags.emplace("LeftLensSequence", Tag(0x0046, 0x0015));
    public_tags.emplace("UnspecifiedLateralityLensSequence", Tag(0x0046, 0x0016));
    public_tags.emplace("CylinderSequence", Tag(0x0046, 0x0018));
    public_tags.emplace("PrismSequence", Tag(0x0046, 0x0028));
    public_tags.emplace("HorizontalPrismPower", Tag(0x0046, 0x0030));
    public_tags.emplace("HorizontalPrismBase", Tag(0x0046, 0x0032));
    public_tags.emplace("VerticalPrismPower", Tag(0x0046, 0x0034));
    public_tags.emplace("VerticalPrismBase", Tag(0x0046, 0x0036));
    public_tags.emplace("LensSegmentType", Tag(0x0046, 0x0038));
    public_tags.emplace("OpticalTransmittance", Tag(0x0046, 0x0040));
    public_tags.emplace("ChannelWidth", Tag(0x0046, 0x0042));
    public_tags.emplace("PupilSize", Tag(0x0046, 0x0044));
    public_tags.emplace("CornealSize", Tag(0x0046, 0x0046));
    public_tags.emplace("CornealSizeSequence", Tag(0x0046, 0x0047));
    public_tags.emplace("AutorefractionRightEyeSequence", Tag(0x0046, 0x0050));
    public_tags.emplace("AutorefractionLeftEyeSequence", Tag(0x0046, 0x0052));
    public_tags.emplace("DistancePupillaryDistance", Tag(0x0046, 0x0060));
    public_tags.emplace("NearPupillaryDistance", Tag(0x0046, 0x0062));
    public_tags.emplace("IntermediatePupillaryDistance", Tag(0x0046, 0x0063));
    public_tags.emplace("OtherPupillaryDistance", Tag(0x0046, 0x0064));
    public_tags.emplace("KeratometryRightEyeSequence", Tag(0x0046, 0x0070));
    public_tags.emplace("KeratometryLeftEyeSequence", Tag(0x0046, 0x0071));
    public_tags.emplace("SteepKeratometricAxisSequence", Tag(0x0046, 0x0074));
    public_tags.emplace("RadiusOfCurvature", Tag(0x0046, 0x0075));
    public_tags.emplace("KeratometricPower", Tag(0x0046, 0x0076));
    public_tags.emplace("KeratometricAxis", Tag(0x0046, 0x0077));
    public_tags.emplace("FlatKeratometricAxisSequence", Tag(0x0046, 0x0080));
    public_tags.emplace("BackgroundColor", Tag(0x0046, 0x0092));
    public_tags.emplace("Optotype", Tag(0x0046, 0x0094));
    public_tags.emplace("OptotypePresentation", Tag(0x0046, 0x0095));
    public_tags.emplace("SubjectiveRefractionRightEyeSequence", Tag(0x0046, 0x0097));
    public_tags.emplace("SubjectiveRefractionLeftEyeSequence", Tag(0x0046, 0x0098));
    public_tags.emplace("AddNearSequence", Tag(0x0046, 0x0100));
    public_tags.emplace("AddIntermediateSequence", Tag(0x0046, 0x0101));
    public_tags.emplace("AddOtherSequence", Tag(0x0046, 0x0102));
    public_tags.emplace("AddPower", Tag(0x0046, 0x0104));
    public_tags.emplace("ViewingDistance", Tag(0x0046, 0x0106));
    public_tags.emplace("CorneaMeasurementsSequence", Tag(0x0046, 0x0110));
    public_tags.emplace("SourceOfCorneaMeasurementDataCodeSequence", Tag(0x0046, 0x0111));
    public_tags.emplace("SteepCornealAxisSequence", Tag(0x0046, 0x0112));
    public_tags.emplace("FlatCornealAxisSequence", Tag(0x0046, 0x0113));
    public_tags.emplace("CornealPower", Tag(0x0046, 0x0114));
    public_tags.emplace("CornealAxis", Tag(0x0046, 0x0115));
    public_tags.emplace("CorneaMeasurementMethodCodeSequence", Tag(0x0046, 0x0116));
    public_tags.emplace("RefractiveIndexOfCornea", Tag(0x0046, 0x0117));
    public_tags.emplace("RefractiveIndexOfAqueousHumor", Tag(0x0046, 0x0118));
    public_tags.emplace("VisualAcuityTypeCodeSequence", Tag(0x0046, 0x0121));
    public_tags.emplace("VisualAcuityRightEyeSequence", Tag(0x0046, 0x0122));
    public_tags.emplace("VisualAcuityLeftEyeSequence", Tag(0x0046, 0x0123));
    public_tags.emplace("VisualAcuityBothEyesOpenSequence", Tag(0x0046, 0x0124));
    public_tags.emplace("ViewingDistanceType", Tag(0x0046, 0x0125));
    public_tags.emplace("VisualAcuityModifiers", Tag(0x0046, 0x0135));
    public_tags.emplace("DecimalVisualAcuity", Tag(0x0046, 0x0137));
    public_tags.emplace("OptotypeDetailedDefinition", Tag(0x0046, 0x0139));
    public_tags.emplace("ReferencedRefractiveMeasurementsSequence", Tag(0x0046, 0x0145));
    public_tags.emplace("SpherePower", Tag(0x0046, 0x0146));
    public_tags.emplace("CylinderPower", Tag(0x0046, 0x0147));
    public_tags.emplace("CornealTopographySurface", Tag(0x0046, 0x0201));
    public_tags.emplace("CornealVertexLocation", Tag(0x0046, 0x0202));
    public_tags.emplace("PupilCentroidXCoordinate", Tag(0x0046, 0x0203));
    public_tags.emplace("PupilCentroidYCoordinate", Tag(0x0046, 0x0204));
    public_tags.emplace("EquivalentPupilRadius", Tag(0x0046, 0x0205));
    public_tags.emplace("CornealTopographyMapTypeCodeSequence", Tag(0x0046, 0x0207));
    public_tags.emplace("VerticesOfTheOutlineOfPupil", Tag(0x0046, 0x0208));
    public_tags.emplace("CornealTopographyMappingNormalsSequence", Tag(0x0046, 0x0210));
    public_tags.emplace("MaximumCornealCurvatureSequence", Tag(0x0046, 0x0211));
    public_tags.emplace("MaximumCornealCurvature", Tag(0x0046, 0x0212));
    public_tags.emplace("MaximumCornealCurvatureLocation", Tag(0x0046, 0x0213));
    public_tags.emplace("MinimumKeratometricSequence", Tag(0x0046, 0x0215));
    public_tags.emplace("SimulatedKeratometricCylinderSequence", Tag(0x0046, 0x0218));
    public_tags.emplace("AverageCornealPower", Tag(0x0046, 0x0220));
    public_tags.emplace("CornealISValue", Tag(0x0046, 0x0224));
    public_tags.emplace("AnalyzedArea", Tag(0x0046, 0x0227));
    public_tags.emplace("SurfaceRegularityIndex", Tag(0x0046, 0x0230));
    public_tags.emplace("SurfaceAsymmetryIndex", Tag(0x0046, 0x0232));
    public_tags.emplace("CornealEccentricityIndex", Tag(0x0046, 0x0234));
    public_tags.emplace("KeratoconusPredictionIndex", Tag(0x0046, 0x0236));
    public_tags.emplace("DecimalPotentialVisualAcuity", Tag(0x0046, 0x0238));
    public_tags.emplace("CornealTopographyMapQualityEvaluation", Tag(0x0046, 0x0242));
    public_tags.emplace("SourceImageCornealProcessedDataSequence", Tag(0x0046, 0x0244));
    public_tags.emplace("CornealPointLocation", Tag(0x0046, 0x0247));
    public_tags.emplace("CornealPointEstimated", Tag(0x0046, 0x0248));
    public_tags.emplace("AxialPower", Tag(0x0046, 0x0249));
    public_tags.emplace("TangentialPower", Tag(0x0046, 0x0250));
    public_tags.emplace("RefractivePower", Tag(0x0046, 0x0251));
    public_tags.emplace("RelativeElevation", Tag(0x0046, 0x0252));
    public_tags.emplace("CornealWavefront", Tag(0x0046, 0x0253));
}

}

}