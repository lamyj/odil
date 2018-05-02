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

void update_0066(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0066, 0x0001), ElementsDictionaryEntry("Number of Surfaces", "NumberOfSurfaces",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0002), ElementsDictionaryEntry("Surface Sequence", "SurfaceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0003), ElementsDictionaryEntry("Surface Number", "SurfaceNumber",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0004), ElementsDictionaryEntry("Surface Comments", "SurfaceComments",  "LT", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0009), ElementsDictionaryEntry("Surface Processing", "SurfaceProcessing",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x000a), ElementsDictionaryEntry("Surface Processing Ratio", "SurfaceProcessingRatio",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x000b), ElementsDictionaryEntry("Surface Processing Description", "SurfaceProcessingDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x000c), ElementsDictionaryEntry("Recommended Presentation Opacity", "RecommendedPresentationOpacity",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x000d), ElementsDictionaryEntry("Recommended Presentation Type", "RecommendedPresentationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x000e), ElementsDictionaryEntry("Finite Volume", "FiniteVolume",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0010), ElementsDictionaryEntry("Manifold", "Manifold",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0011), ElementsDictionaryEntry("Surface Points Sequence", "SurfacePointsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0012), ElementsDictionaryEntry("Surface Points Normals Sequence", "SurfacePointsNormalsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0013), ElementsDictionaryEntry("Surface Mesh Primitives Sequence", "SurfaceMeshPrimitivesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0015), ElementsDictionaryEntry("Number of Surface Points", "NumberOfSurfacePoints",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0016), ElementsDictionaryEntry("Point Coordinates Data", "PointCoordinatesData",  "OF", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0017), ElementsDictionaryEntry("Point Position Accuracy", "PointPositionAccuracy",  "FL", "3"));
    public_dictionary.emplace(Tag(0x0066, 0x0018), ElementsDictionaryEntry("Mean Point Distance", "MeanPointDistance",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0019), ElementsDictionaryEntry("Maximum Point Distance", "MaximumPointDistance",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x001a), ElementsDictionaryEntry("Points Bounding Box Coordinates", "PointsBoundingBoxCoordinates",  "FL", "6"));
    public_dictionary.emplace(Tag(0x0066, 0x001b), ElementsDictionaryEntry("Axis of Rotation", "AxisOfRotation",  "FL", "3"));
    public_dictionary.emplace(Tag(0x0066, 0x001c), ElementsDictionaryEntry("Center of Rotation", "CenterOfRotation",  "FL", "3"));
    public_dictionary.emplace(Tag(0x0066, 0x001e), ElementsDictionaryEntry("Number of Vectors", "NumberOfVectors",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x001f), ElementsDictionaryEntry("Vector Dimensionality", "VectorDimensionality",  "US", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0020), ElementsDictionaryEntry("Vector Accuracy", "VectorAccuracy",  "FL", "1-n"));
    public_dictionary.emplace(Tag(0x0066, 0x0021), ElementsDictionaryEntry("Vector Coordinate Data", "VectorCoordinateData",  "OF", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0023), ElementsDictionaryEntry("Triangle Point Index List", "TrianglePointIndexList",  "OW", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0024), ElementsDictionaryEntry("Edge Point Index List", "EdgePointIndexList",  "OW", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0025), ElementsDictionaryEntry("Vertex Point Index List", "VertexPointIndexList",  "OW", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0026), ElementsDictionaryEntry("Triangle Strip Sequence", "TriangleStripSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0027), ElementsDictionaryEntry("Triangle Fan Sequence", "TriangleFanSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0028), ElementsDictionaryEntry("Line Sequence", "LineSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0029), ElementsDictionaryEntry("Primitive Point Index List", "PrimitivePointIndexList",  "OW", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x002a), ElementsDictionaryEntry("Surface Count", "SurfaceCount",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x002b), ElementsDictionaryEntry("Referenced Surface Sequence", "ReferencedSurfaceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x002c), ElementsDictionaryEntry("Referenced Surface Number", "ReferencedSurfaceNumber",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x002d), ElementsDictionaryEntry("Segment Surface Generation Algorithm Identification Sequence", "SegmentSurfaceGenerationAlgorithmIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x002e), ElementsDictionaryEntry("Segment Surface Source Instance Sequence", "SegmentSurfaceSourceInstanceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x002f), ElementsDictionaryEntry("Algorithm Family Code Sequence", "AlgorithmFamilyCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0030), ElementsDictionaryEntry("Algorithm Name Code Sequence", "AlgorithmNameCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0031), ElementsDictionaryEntry("Algorithm Version", "AlgorithmVersion",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0032), ElementsDictionaryEntry("Algorithm Parameters", "AlgorithmParameters",  "LT", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0034), ElementsDictionaryEntry("Facet Sequence", "FacetSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0035), ElementsDictionaryEntry("Surface Processing Algorithm Identification Sequence", "SurfaceProcessingAlgorithmIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0036), ElementsDictionaryEntry("Algorithm Name", "AlgorithmName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0037), ElementsDictionaryEntry("Recommended Point Radius", "RecommendedPointRadius",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0038), ElementsDictionaryEntry("Recommended Line Thickness", "RecommendedLineThickness",  "FL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0040), ElementsDictionaryEntry("Long Primitive Point Index List", "LongPrimitivePointIndexList",  "OL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0041), ElementsDictionaryEntry("Long Triangle Point Index List", "LongTrianglePointIndexList",  "OL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0042), ElementsDictionaryEntry("Long Edge Point Index List", "LongEdgePointIndexList",  "OL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0043), ElementsDictionaryEntry("Long Vertex Point Index List", "LongVertexPointIndexList",  "OL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0101), ElementsDictionaryEntry("Track Set Sequence", "TrackSetSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0102), ElementsDictionaryEntry("Track Sequence", "TrackSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0103), ElementsDictionaryEntry("Recommended Display CIELab Value List", "RecommendedDisplayCIELabValueList",  "OW", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0104), ElementsDictionaryEntry("Tracking Algorithm Identification Sequence", "TrackingAlgorithmIdentificationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0105), ElementsDictionaryEntry("Track Set Number", "TrackSetNumber",  "UL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0106), ElementsDictionaryEntry("Track Set Label", "TrackSetLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0107), ElementsDictionaryEntry("Track Set Description", "TrackSetDescription",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0108), ElementsDictionaryEntry("Track Set Anatomical Type Code Sequence", "TrackSetAnatomicalTypeCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0121), ElementsDictionaryEntry("Measurements Sequence", "MeasurementsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0124), ElementsDictionaryEntry("Track Set Statistics Sequence", "TrackSetStatisticsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0125), ElementsDictionaryEntry("Floating Point Values", "FloatingPointValues",  "OF", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0129), ElementsDictionaryEntry("Track Point Index List", "TrackPointIndexList",  "OL", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0130), ElementsDictionaryEntry("Track Statistics Sequence", "TrackStatisticsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0132), ElementsDictionaryEntry("Measurement Values Sequence", "MeasurementValuesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0133), ElementsDictionaryEntry("Diffusion Acquisition Code Sequence", "DiffusionAcquisitionCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0066, 0x0134), ElementsDictionaryEntry("Diffusion Model Code Sequence", "DiffusionModelCodeSequence",  "SQ", "1"));

    public_tags.emplace("NumberOfSurfaces", Tag(0x0066, 0x0001));
    public_tags.emplace("SurfaceSequence", Tag(0x0066, 0x0002));
    public_tags.emplace("SurfaceNumber", Tag(0x0066, 0x0003));
    public_tags.emplace("SurfaceComments", Tag(0x0066, 0x0004));
    public_tags.emplace("SurfaceProcessing", Tag(0x0066, 0x0009));
    public_tags.emplace("SurfaceProcessingRatio", Tag(0x0066, 0x000a));
    public_tags.emplace("SurfaceProcessingDescription", Tag(0x0066, 0x000b));
    public_tags.emplace("RecommendedPresentationOpacity", Tag(0x0066, 0x000c));
    public_tags.emplace("RecommendedPresentationType", Tag(0x0066, 0x000d));
    public_tags.emplace("FiniteVolume", Tag(0x0066, 0x000e));
    public_tags.emplace("Manifold", Tag(0x0066, 0x0010));
    public_tags.emplace("SurfacePointsSequence", Tag(0x0066, 0x0011));
    public_tags.emplace("SurfacePointsNormalsSequence", Tag(0x0066, 0x0012));
    public_tags.emplace("SurfaceMeshPrimitivesSequence", Tag(0x0066, 0x0013));
    public_tags.emplace("NumberOfSurfacePoints", Tag(0x0066, 0x0015));
    public_tags.emplace("PointCoordinatesData", Tag(0x0066, 0x0016));
    public_tags.emplace("PointPositionAccuracy", Tag(0x0066, 0x0017));
    public_tags.emplace("MeanPointDistance", Tag(0x0066, 0x0018));
    public_tags.emplace("MaximumPointDistance", Tag(0x0066, 0x0019));
    public_tags.emplace("PointsBoundingBoxCoordinates", Tag(0x0066, 0x001a));
    public_tags.emplace("AxisOfRotation", Tag(0x0066, 0x001b));
    public_tags.emplace("CenterOfRotation", Tag(0x0066, 0x001c));
    public_tags.emplace("NumberOfVectors", Tag(0x0066, 0x001e));
    public_tags.emplace("VectorDimensionality", Tag(0x0066, 0x001f));
    public_tags.emplace("VectorAccuracy", Tag(0x0066, 0x0020));
    public_tags.emplace("VectorCoordinateData", Tag(0x0066, 0x0021));
    public_tags.emplace("TrianglePointIndexList", Tag(0x0066, 0x0023));
    public_tags.emplace("EdgePointIndexList", Tag(0x0066, 0x0024));
    public_tags.emplace("VertexPointIndexList", Tag(0x0066, 0x0025));
    public_tags.emplace("TriangleStripSequence", Tag(0x0066, 0x0026));
    public_tags.emplace("TriangleFanSequence", Tag(0x0066, 0x0027));
    public_tags.emplace("LineSequence", Tag(0x0066, 0x0028));
    public_tags.emplace("PrimitivePointIndexList", Tag(0x0066, 0x0029));
    public_tags.emplace("SurfaceCount", Tag(0x0066, 0x002a));
    public_tags.emplace("ReferencedSurfaceSequence", Tag(0x0066, 0x002b));
    public_tags.emplace("ReferencedSurfaceNumber", Tag(0x0066, 0x002c));
    public_tags.emplace("SegmentSurfaceGenerationAlgorithmIdentificationSequence", Tag(0x0066, 0x002d));
    public_tags.emplace("SegmentSurfaceSourceInstanceSequence", Tag(0x0066, 0x002e));
    public_tags.emplace("AlgorithmFamilyCodeSequence", Tag(0x0066, 0x002f));
    public_tags.emplace("AlgorithmNameCodeSequence", Tag(0x0066, 0x0030));
    public_tags.emplace("AlgorithmVersion", Tag(0x0066, 0x0031));
    public_tags.emplace("AlgorithmParameters", Tag(0x0066, 0x0032));
    public_tags.emplace("FacetSequence", Tag(0x0066, 0x0034));
    public_tags.emplace("SurfaceProcessingAlgorithmIdentificationSequence", Tag(0x0066, 0x0035));
    public_tags.emplace("AlgorithmName", Tag(0x0066, 0x0036));
    public_tags.emplace("RecommendedPointRadius", Tag(0x0066, 0x0037));
    public_tags.emplace("RecommendedLineThickness", Tag(0x0066, 0x0038));
    public_tags.emplace("LongPrimitivePointIndexList", Tag(0x0066, 0x0040));
    public_tags.emplace("LongTrianglePointIndexList", Tag(0x0066, 0x0041));
    public_tags.emplace("LongEdgePointIndexList", Tag(0x0066, 0x0042));
    public_tags.emplace("LongVertexPointIndexList", Tag(0x0066, 0x0043));
    public_tags.emplace("TrackSetSequence", Tag(0x0066, 0x0101));
    public_tags.emplace("TrackSequence", Tag(0x0066, 0x0102));
    public_tags.emplace("RecommendedDisplayCIELabValueList", Tag(0x0066, 0x0103));
    public_tags.emplace("TrackingAlgorithmIdentificationSequence", Tag(0x0066, 0x0104));
    public_tags.emplace("TrackSetNumber", Tag(0x0066, 0x0105));
    public_tags.emplace("TrackSetLabel", Tag(0x0066, 0x0106));
    public_tags.emplace("TrackSetDescription", Tag(0x0066, 0x0107));
    public_tags.emplace("TrackSetAnatomicalTypeCodeSequence", Tag(0x0066, 0x0108));
    public_tags.emplace("MeasurementsSequence", Tag(0x0066, 0x0121));
    public_tags.emplace("TrackSetStatisticsSequence", Tag(0x0066, 0x0124));
    public_tags.emplace("FloatingPointValues", Tag(0x0066, 0x0125));
    public_tags.emplace("TrackPointIndexList", Tag(0x0066, 0x0129));
    public_tags.emplace("TrackStatisticsSequence", Tag(0x0066, 0x0130));
    public_tags.emplace("MeasurementValuesSequence", Tag(0x0066, 0x0132));
    public_tags.emplace("DiffusionAcquisitionCodeSequence", Tag(0x0066, 0x0133));
    public_tags.emplace("DiffusionModelCodeSequence", Tag(0x0066, 0x0134));
}

}

}