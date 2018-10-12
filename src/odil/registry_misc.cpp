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

void update_misc(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(std::string("002031xx"), ElementsDictionaryEntry("Source Image IDs", "SourceImageIDs",  "CS", "1-n"));
    public_dictionary.emplace(std::string("002804x0"), ElementsDictionaryEntry("Rows For Nth Order Coefficients", "RowsForNthOrderCoefficients",  "US", "1"));
    public_dictionary.emplace(std::string("002804x1"), ElementsDictionaryEntry("Columns For Nth Order Coefficients", "ColumnsForNthOrderCoefficients",  "US", "1"));
    public_dictionary.emplace(std::string("002804x2"), ElementsDictionaryEntry("Coefficient Coding", "CoefficientCoding",  "LO", "1-n"));
    public_dictionary.emplace(std::string("002804x3"), ElementsDictionaryEntry("Coefficient Coding Pointers", "CoefficientCodingPointers",  "AT", "1-n"));
    public_dictionary.emplace(std::string("002808x0"), ElementsDictionaryEntry("Code Label", "CodeLabel",  "CS", "1-n"));
    public_dictionary.emplace(std::string("002808x2"), ElementsDictionaryEntry("Number of Tables", "NumberOfTables",  "US", "1"));
    public_dictionary.emplace(std::string("002808x3"), ElementsDictionaryEntry("Code Table Location", "CodeTableLocation",  "AT", "1-n"));
    public_dictionary.emplace(std::string("002808x4"), ElementsDictionaryEntry("Bits For Code Word", "BitsForCodeWord",  "US", "1"));
    public_dictionary.emplace(std::string("002808x8"), ElementsDictionaryEntry("Image Data Location", "ImageDataLocation",  "AT", "1-n"));
    public_dictionary.emplace(std::string("1000xxx0"), ElementsDictionaryEntry("Escape Triplet", "EscapeTriplet",  "US", "3"));
    public_dictionary.emplace(std::string("1000xxx1"), ElementsDictionaryEntry("Run Length Triplet", "RunLengthTriplet",  "US", "3"));
    public_dictionary.emplace(std::string("1000xxx2"), ElementsDictionaryEntry("Huffman Table Size", "HuffmanTableSize",  "US", "1"));
    public_dictionary.emplace(std::string("1000xxx3"), ElementsDictionaryEntry("Huffman Table Triplet", "HuffmanTableTriplet",  "US", "3"));
    public_dictionary.emplace(std::string("1000xxx4"), ElementsDictionaryEntry("Shift Table Size", "ShiftTableSize",  "US", "1"));
    public_dictionary.emplace(std::string("1000xxx5"), ElementsDictionaryEntry("Shift Table Triplet", "ShiftTableTriplet",  "US", "3"));
    public_dictionary.emplace(std::string("1010xxxx"), ElementsDictionaryEntry("Zonal Map", "ZonalMap",  "US", "1-n"));
    public_dictionary.emplace(std::string("50xx0005"), ElementsDictionaryEntry("Curve Dimensions", "CurveDimensions",  "US", "1"));
    public_dictionary.emplace(std::string("50xx0010"), ElementsDictionaryEntry("Number of Points", "NumberOfPoints",  "US", "1"));
    public_dictionary.emplace(std::string("50xx0020"), ElementsDictionaryEntry("Type of Data", "TypeOfData",  "CS", "1"));
    public_dictionary.emplace(std::string("50xx0022"), ElementsDictionaryEntry("Curve Description", "CurveDescription",  "LO", "1"));
    public_dictionary.emplace(std::string("50xx0030"), ElementsDictionaryEntry("Axis Units", "AxisUnits",  "SH", "1-n"));
    public_dictionary.emplace(std::string("50xx0040"), ElementsDictionaryEntry("Axis Labels", "AxisLabels",  "SH", "1-n"));
    public_dictionary.emplace(std::string("50xx0103"), ElementsDictionaryEntry("Data Value Representation", "DataValueRepresentation",  "US", "1"));
    public_dictionary.emplace(std::string("50xx0104"), ElementsDictionaryEntry("Minimum Coordinate Value", "MinimumCoordinateValue",  "US", "1-n"));
    public_dictionary.emplace(std::string("50xx0105"), ElementsDictionaryEntry("Maximum Coordinate Value", "MaximumCoordinateValue",  "US", "1-n"));
    public_dictionary.emplace(std::string("50xx0106"), ElementsDictionaryEntry("Curve Range", "CurveRange",  "SH", "1-n"));
    public_dictionary.emplace(std::string("50xx0110"), ElementsDictionaryEntry("Curve Data Descriptor", "CurveDataDescriptor",  "US", "1-n"));
    public_dictionary.emplace(std::string("50xx0112"), ElementsDictionaryEntry("Coordinate Start Value", "CoordinateStartValue",  "US", "1-n"));
    public_dictionary.emplace(std::string("50xx0114"), ElementsDictionaryEntry("Coordinate Step Value", "CoordinateStepValue",  "US", "1-n"));
    public_dictionary.emplace(std::string("50xx1001"), ElementsDictionaryEntry("Curve Activation Layer", "CurveActivationLayer",  "CS", "1"));
    public_dictionary.emplace(std::string("50xx2000"), ElementsDictionaryEntry("Audio Type", "AudioType",  "US", "1"));
    public_dictionary.emplace(std::string("50xx2002"), ElementsDictionaryEntry("Audio Sample Format", "AudioSampleFormat",  "US", "1"));
    public_dictionary.emplace(std::string("50xx2004"), ElementsDictionaryEntry("Number of Channels", "NumberOfChannels",  "US", "1"));
    public_dictionary.emplace(std::string("50xx2006"), ElementsDictionaryEntry("Number of Samples", "NumberOfSamples",  "UL", "1"));
    public_dictionary.emplace(std::string("50xx2008"), ElementsDictionaryEntry("Sample Rate", "SampleRate",  "UL", "1"));
    public_dictionary.emplace(std::string("50xx200A"), ElementsDictionaryEntry("Total Time", "TotalTime",  "UL", "1"));
    public_dictionary.emplace(std::string("50xx200C"), ElementsDictionaryEntry("Audio Sample Data", "AudioSampleData",  "OB or OW", "1"));
    public_dictionary.emplace(std::string("50xx200E"), ElementsDictionaryEntry("Audio Comments", "AudioComments",  "LT", "1"));
    public_dictionary.emplace(std::string("50xx2500"), ElementsDictionaryEntry("Curve Label", "CurveLabel",  "LO", "1"));
    public_dictionary.emplace(std::string("50xx2600"), ElementsDictionaryEntry("Curve Referenced Overlay Sequence", "CurveReferencedOverlaySequence",  "SQ", "1"));
    public_dictionary.emplace(std::string("50xx2610"), ElementsDictionaryEntry("Curve Referenced Overlay Group", "CurveReferencedOverlayGroup",  "US", "1"));
    public_dictionary.emplace(std::string("50xx3000"), ElementsDictionaryEntry("Curve Data", "CurveData",  "OB or OW", "1"));
    public_dictionary.emplace(std::string("60xx0010"), ElementsDictionaryEntry("Overlay Rows", "OverlayRows",  "US", "1"));
    public_dictionary.emplace(std::string("60xx0011"), ElementsDictionaryEntry("Overlay Columns", "OverlayColumns",  "US", "1"));
    public_dictionary.emplace(std::string("60xx0012"), ElementsDictionaryEntry("Overlay Planes", "OverlayPlanes",  "US", "1"));
    public_dictionary.emplace(std::string("60xx0015"), ElementsDictionaryEntry("Number of Frames in Overlay", "NumberOfFramesInOverlay",  "IS", "1"));
    public_dictionary.emplace(std::string("60xx0022"), ElementsDictionaryEntry("Overlay Description", "OverlayDescription",  "LO", "1"));
    public_dictionary.emplace(std::string("60xx0040"), ElementsDictionaryEntry("Overlay Type", "OverlayType",  "CS", "1"));
    public_dictionary.emplace(std::string("60xx0045"), ElementsDictionaryEntry("Overlay Subtype", "OverlaySubtype",  "LO", "1"));
    public_dictionary.emplace(std::string("60xx0050"), ElementsDictionaryEntry("Overlay Origin", "OverlayOrigin",  "SS", "2"));
    public_dictionary.emplace(std::string("60xx0051"), ElementsDictionaryEntry("Image Frame Origin", "ImageFrameOrigin",  "US", "1"));
    public_dictionary.emplace(std::string("60xx0052"), ElementsDictionaryEntry("Overlay Plane Origin", "OverlayPlaneOrigin",  "US", "1"));
    public_dictionary.emplace(std::string("60xx0060"), ElementsDictionaryEntry("Overlay Compression Code", "OverlayCompressionCode",  "CS", "1"));
    public_dictionary.emplace(std::string("60xx0061"), ElementsDictionaryEntry("Overlay Compression Originator", "OverlayCompressionOriginator",  "SH", "1"));
    public_dictionary.emplace(std::string("60xx0062"), ElementsDictionaryEntry("Overlay Compression Label", "OverlayCompressionLabel",  "SH", "1"));
    public_dictionary.emplace(std::string("60xx0063"), ElementsDictionaryEntry("Overlay Compression Description", "OverlayCompressionDescription",  "CS", "1"));
    public_dictionary.emplace(std::string("60xx0066"), ElementsDictionaryEntry("Overlay Compression Step Pointers", "OverlayCompressionStepPointers",  "AT", "1-n"));
    public_dictionary.emplace(std::string("60xx0068"), ElementsDictionaryEntry("Overlay Repeat Interval", "OverlayRepeatInterval",  "US", "1"));
    public_dictionary.emplace(std::string("60xx0069"), ElementsDictionaryEntry("Overlay Bits Grouped", "OverlayBitsGrouped",  "US", "1"));
    public_dictionary.emplace(std::string("60xx0100"), ElementsDictionaryEntry("Overlay Bits Allocated", "OverlayBitsAllocated",  "US", "1"));
    public_dictionary.emplace(std::string("60xx0102"), ElementsDictionaryEntry("Overlay Bit Position", "OverlayBitPosition",  "US", "1"));
    public_dictionary.emplace(std::string("60xx0110"), ElementsDictionaryEntry("Overlay Format", "OverlayFormat",  "CS", "1"));
    public_dictionary.emplace(std::string("60xx0200"), ElementsDictionaryEntry("Overlay Location", "OverlayLocation",  "US", "1"));
    public_dictionary.emplace(std::string("60xx0800"), ElementsDictionaryEntry("Overlay Code Label", "OverlayCodeLabel",  "CS", "1-n"));
    public_dictionary.emplace(std::string("60xx0802"), ElementsDictionaryEntry("Overlay Number of Tables", "OverlayNumberOfTables",  "US", "1"));
    public_dictionary.emplace(std::string("60xx0803"), ElementsDictionaryEntry("Overlay Code Table Location", "OverlayCodeTableLocation",  "AT", "1-n"));
    public_dictionary.emplace(std::string("60xx0804"), ElementsDictionaryEntry("Overlay Bits For Code Word", "OverlayBitsForCodeWord",  "US", "1"));
    public_dictionary.emplace(std::string("60xx1001"), ElementsDictionaryEntry("Overlay Activation Layer", "OverlayActivationLayer",  "CS", "1"));
    public_dictionary.emplace(std::string("60xx1100"), ElementsDictionaryEntry("Overlay Descriptor - Gray", "OverlayDescriptorGray",  "US", "1"));
    public_dictionary.emplace(std::string("60xx1101"), ElementsDictionaryEntry("Overlay Descriptor - Red", "OverlayDescriptorRed",  "US", "1"));
    public_dictionary.emplace(std::string("60xx1102"), ElementsDictionaryEntry("Overlay Descriptor - Green", "OverlayDescriptorGreen",  "US", "1"));
    public_dictionary.emplace(std::string("60xx1103"), ElementsDictionaryEntry("Overlay Descriptor - Blue", "OverlayDescriptorBlue",  "US", "1"));
    public_dictionary.emplace(std::string("60xx1200"), ElementsDictionaryEntry("Overlays - Gray", "OverlaysGray",  "US", "1-n"));
    public_dictionary.emplace(std::string("60xx1201"), ElementsDictionaryEntry("Overlays - Red", "OverlaysRed",  "US", "1-n"));
    public_dictionary.emplace(std::string("60xx1202"), ElementsDictionaryEntry("Overlays - Green", "OverlaysGreen",  "US", "1-n"));
    public_dictionary.emplace(std::string("60xx1203"), ElementsDictionaryEntry("Overlays - Blue", "OverlaysBlue",  "US", "1-n"));
    public_dictionary.emplace(std::string("60xx1301"), ElementsDictionaryEntry("ROI Area", "ROIArea",  "IS", "1"));
    public_dictionary.emplace(std::string("60xx1302"), ElementsDictionaryEntry("ROI Mean", "ROIMean",  "DS", "1"));
    public_dictionary.emplace(std::string("60xx1303"), ElementsDictionaryEntry("ROI Standard Deviation", "ROIStandardDeviation",  "DS", "1"));
    public_dictionary.emplace(std::string("60xx1500"), ElementsDictionaryEntry("Overlay Label", "OverlayLabel",  "LO", "1"));
    public_dictionary.emplace(std::string("60xx3000"), ElementsDictionaryEntry("Overlay Data", "OverlayData",  "OB or OW", "1"));
    public_dictionary.emplace(std::string("60xx4000"), ElementsDictionaryEntry("Overlay Comments", "OverlayComments",  "LT", "1"));
    public_dictionary.emplace(std::string("7Fxx0010"), ElementsDictionaryEntry("Variable Pixel Data", "VariablePixelData",  "OB or OW", "1"));
    public_dictionary.emplace(std::string("7Fxx0011"), ElementsDictionaryEntry("Variable Next Data Group", "VariableNextDataGroup",  "US", "1"));
    public_dictionary.emplace(std::string("7Fxx0020"), ElementsDictionaryEntry("Variable Coefficients SDVN", "VariableCoefficientsSDVN",  "OW", "1"));
    public_dictionary.emplace(std::string("7Fxx0030"), ElementsDictionaryEntry("Variable Coefficients SDHN", "VariableCoefficientsSDHN",  "OW", "1"));
    public_dictionary.emplace(std::string("7Fxx0040"), ElementsDictionaryEntry("Variable Coefficients SDDN", "VariableCoefficientsSDDN",  "OW", "1"));

}

}

}