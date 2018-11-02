/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_misc
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_misc

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
std::string const SourceImageIDs("002031xx");
std::string const RowsForNthOrderCoefficients("002804x0");
std::string const ColumnsForNthOrderCoefficients("002804x1");
std::string const CoefficientCoding("002804x2");
std::string const CoefficientCodingPointers("002804x3");
std::string const CodeLabel("002808x0");
std::string const NumberOfTables("002808x2");
std::string const CodeTableLocation("002808x3");
std::string const BitsForCodeWord("002808x4");
std::string const ImageDataLocation("002808x8");
std::string const EscapeTriplet("1000xxx0");
std::string const RunLengthTriplet("1000xxx1");
std::string const HuffmanTableSize("1000xxx2");
std::string const HuffmanTableTriplet("1000xxx3");
std::string const ShiftTableSize("1000xxx4");
std::string const ShiftTableTriplet("1000xxx5");
std::string const ZonalMap("1010xxxx");
std::string const CurveDimensions("50xx0005");
std::string const NumberOfPoints("50xx0010");
std::string const TypeOfData("50xx0020");
std::string const CurveDescription("50xx0022");
std::string const AxisUnits("50xx0030");
std::string const AxisLabels("50xx0040");
std::string const DataValueRepresentation("50xx0103");
std::string const MinimumCoordinateValue("50xx0104");
std::string const MaximumCoordinateValue("50xx0105");
std::string const CurveRange("50xx0106");
std::string const CurveDataDescriptor("50xx0110");
std::string const CoordinateStartValue("50xx0112");
std::string const CoordinateStepValue("50xx0114");
std::string const CurveActivationLayer("50xx1001");
std::string const AudioType("50xx2000");
std::string const AudioSampleFormat("50xx2002");
std::string const NumberOfChannels("50xx2004");
std::string const NumberOfSamples("50xx2006");
std::string const SampleRate("50xx2008");
std::string const TotalTime("50xx200A");
std::string const AudioSampleData("50xx200C");
std::string const AudioComments("50xx200E");
std::string const CurveLabel("50xx2500");
std::string const CurveReferencedOverlaySequence("50xx2600");
std::string const CurveReferencedOverlayGroup("50xx2610");
std::string const CurveData("50xx3000");
std::string const OverlayRows("60xx0010");
std::string const OverlayColumns("60xx0011");
std::string const OverlayPlanes("60xx0012");
std::string const NumberOfFramesInOverlay("60xx0015");
std::string const OverlayDescription("60xx0022");
std::string const OverlayType("60xx0040");
std::string const OverlaySubtype("60xx0045");
std::string const OverlayOrigin("60xx0050");
std::string const ImageFrameOrigin("60xx0051");
std::string const OverlayPlaneOrigin("60xx0052");
std::string const OverlayCompressionCode("60xx0060");
std::string const OverlayCompressionOriginator("60xx0061");
std::string const OverlayCompressionLabel("60xx0062");
std::string const OverlayCompressionDescription("60xx0063");
std::string const OverlayCompressionStepPointers("60xx0066");
std::string const OverlayRepeatInterval("60xx0068");
std::string const OverlayBitsGrouped("60xx0069");
std::string const OverlayBitsAllocated("60xx0100");
std::string const OverlayBitPosition("60xx0102");
std::string const OverlayFormat("60xx0110");
std::string const OverlayLocation("60xx0200");
std::string const OverlayCodeLabel("60xx0800");
std::string const OverlayNumberOfTables("60xx0802");
std::string const OverlayCodeTableLocation("60xx0803");
std::string const OverlayBitsForCodeWord("60xx0804");
std::string const OverlayActivationLayer("60xx1001");
std::string const OverlayDescriptorGray("60xx1100");
std::string const OverlayDescriptorRed("60xx1101");
std::string const OverlayDescriptorGreen("60xx1102");
std::string const OverlayDescriptorBlue("60xx1103");
std::string const OverlaysGray("60xx1200");
std::string const OverlaysRed("60xx1201");
std::string const OverlaysGreen("60xx1202");
std::string const OverlaysBlue("60xx1203");
std::string const ROIArea("60xx1301");
std::string const ROIMean("60xx1302");
std::string const ROIStandardDeviation("60xx1303");
std::string const OverlayLabel("60xx1500");
std::string const OverlayData("60xx3000");
std::string const OverlayComments("60xx4000");
std::string const VariablePixelData("7Fxx0010");
std::string const VariableNextDataGroup("7Fxx0011");
std::string const VariableCoefficientsSDVN("7Fxx0020");
std::string const VariableCoefficientsSDHN("7Fxx0030");
std::string const VariableCoefficientsSDDN("7Fxx0040");

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_misc