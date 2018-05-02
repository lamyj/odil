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

void update_0072(
    ElementsDictionary & public_dictionary,
    std::map<std::string, odil::Tag> & public_tags)
{

    public_dictionary.emplace(Tag(0x0072, 0x0002), ElementsDictionaryEntry("Hanging Protocol Name", "HangingProtocolName",  "SH", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0004), ElementsDictionaryEntry("Hanging Protocol Description", "HangingProtocolDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0006), ElementsDictionaryEntry("Hanging Protocol Level", "HangingProtocolLevel",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0008), ElementsDictionaryEntry("Hanging Protocol Creator", "HangingProtocolCreator",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x000a), ElementsDictionaryEntry("Hanging Protocol Creation DateTime", "HangingProtocolCreationDateTime",  "DT", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x000c), ElementsDictionaryEntry("Hanging Protocol Definition Sequence", "HangingProtocolDefinitionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x000e), ElementsDictionaryEntry("Hanging Protocol User Identification Code Sequence", "HangingProtocolUserIdentificationCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0010), ElementsDictionaryEntry("Hanging Protocol User Group Name", "HangingProtocolUserGroupName",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0012), ElementsDictionaryEntry("Source Hanging Protocol Sequence", "SourceHangingProtocolSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0014), ElementsDictionaryEntry("Number of Priors Referenced", "NumberOfPriorsReferenced",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0020), ElementsDictionaryEntry("Image Sets Sequence", "ImageSetsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0022), ElementsDictionaryEntry("Image Set Selector Sequence", "ImageSetSelectorSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0024), ElementsDictionaryEntry("Image Set Selector Usage Flag", "ImageSetSelectorUsageFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0026), ElementsDictionaryEntry("Selector Attribute", "SelectorAttribute",  "AT", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0028), ElementsDictionaryEntry("Selector Value Number", "SelectorValueNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0030), ElementsDictionaryEntry("Time Based Image Sets Sequence", "TimeBasedImageSetsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0032), ElementsDictionaryEntry("Image Set Number", "ImageSetNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0034), ElementsDictionaryEntry("Image Set Selector Category", "ImageSetSelectorCategory",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0038), ElementsDictionaryEntry("Relative Time", "RelativeTime",  "US", "2"));
    public_dictionary.emplace(Tag(0x0072, 0x003a), ElementsDictionaryEntry("Relative Time Units", "RelativeTimeUnits",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x003c), ElementsDictionaryEntry("Abstract Prior Value", "AbstractPriorValue",  "SS", "2"));
    public_dictionary.emplace(Tag(0x0072, 0x003e), ElementsDictionaryEntry("Abstract Prior Code Sequence", "AbstractPriorCodeSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0040), ElementsDictionaryEntry("Image Set Label", "ImageSetLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0050), ElementsDictionaryEntry("Selector Attribute VR", "SelectorAttributeVR",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0052), ElementsDictionaryEntry("Selector Sequence Pointer", "SelectorSequencePointer",  "AT", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0054), ElementsDictionaryEntry("Selector Sequence Pointer Private Creator", "SelectorSequencePointerPrivateCreator",  "LO", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0056), ElementsDictionaryEntry("Selector Attribute Private Creator", "SelectorAttributePrivateCreator",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x005e), ElementsDictionaryEntry("Selector AE Value", "SelectorAEValue",  "AE", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x005f), ElementsDictionaryEntry("Selector AS Value", "SelectorASValue",  "AS", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0060), ElementsDictionaryEntry("Selector AT Value", "SelectorATValue",  "AT", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0061), ElementsDictionaryEntry("Selector DA Value", "SelectorDAValue",  "DA", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0062), ElementsDictionaryEntry("Selector CS Value", "SelectorCSValue",  "CS", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0063), ElementsDictionaryEntry("Selector DT Value", "SelectorDTValue",  "DT", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0064), ElementsDictionaryEntry("Selector IS Value", "SelectorISValue",  "IS", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0065), ElementsDictionaryEntry("Selector OB Value", "SelectorOBValue",  "OB", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0066), ElementsDictionaryEntry("Selector LO Value", "SelectorLOValue",  "LO", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0067), ElementsDictionaryEntry("Selector OF Value", "SelectorOFValue",  "OF", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0068), ElementsDictionaryEntry("Selector LT Value", "SelectorLTValue",  "LT", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0069), ElementsDictionaryEntry("Selector OW Value", "SelectorOWValue",  "OW", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x006a), ElementsDictionaryEntry("Selector PN Value", "SelectorPNValue",  "PN", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x006b), ElementsDictionaryEntry("Selector TM Value", "SelectorTMValue",  "TM", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x006c), ElementsDictionaryEntry("Selector SH Value", "SelectorSHValue",  "SH", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x006d), ElementsDictionaryEntry("Selector UN Value", "SelectorUNValue",  "UN", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x006e), ElementsDictionaryEntry("Selector ST Value", "SelectorSTValue",  "ST", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x006f), ElementsDictionaryEntry("Selector UC Value", "SelectorUCValue",  "UC", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0070), ElementsDictionaryEntry("Selector UT Value", "SelectorUTValue",  "UT", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0071), ElementsDictionaryEntry("Selector UR Value", "SelectorURValue",  "UR", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0072), ElementsDictionaryEntry("Selector DS Value", "SelectorDSValue",  "DS", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0073), ElementsDictionaryEntry("Selector OD Value", "SelectorODValue",  "OD", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0074), ElementsDictionaryEntry("Selector FD Value", "SelectorFDValue",  "FD", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0075), ElementsDictionaryEntry("Selector OL Value", "SelectorOLValue",  "OL", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0076), ElementsDictionaryEntry("Selector FL Value", "SelectorFLValue",  "FL", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0078), ElementsDictionaryEntry("Selector UL Value", "SelectorULValue",  "UL", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x007a), ElementsDictionaryEntry("Selector US Value", "SelectorUSValue",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x007c), ElementsDictionaryEntry("Selector SL Value", "SelectorSLValue",  "SL", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x007e), ElementsDictionaryEntry("Selector SS Value", "SelectorSSValue",  "SS", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x007f), ElementsDictionaryEntry("Selector UI Value", "SelectorUIValue",  "UI", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0080), ElementsDictionaryEntry("Selector Code Sequence Value", "SelectorCodeSequenceValue",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0100), ElementsDictionaryEntry("Number of Screens", "NumberOfScreens",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0102), ElementsDictionaryEntry("Nominal Screen Definition Sequence", "NominalScreenDefinitionSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0104), ElementsDictionaryEntry("Number of Vertical Pixels", "NumberOfVerticalPixels",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0106), ElementsDictionaryEntry("Number of Horizontal Pixels", "NumberOfHorizontalPixels",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0108), ElementsDictionaryEntry("Display Environment Spatial Position", "DisplayEnvironmentSpatialPosition",  "FD", "4"));
    public_dictionary.emplace(Tag(0x0072, 0x010a), ElementsDictionaryEntry("Screen Minimum Grayscale Bit Depth", "ScreenMinimumGrayscaleBitDepth",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x010c), ElementsDictionaryEntry("Screen Minimum Color Bit Depth", "ScreenMinimumColorBitDepth",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x010e), ElementsDictionaryEntry("Application Maximum Repaint Time", "ApplicationMaximumRepaintTime",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0200), ElementsDictionaryEntry("Display Sets Sequence", "DisplaySetsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0202), ElementsDictionaryEntry("Display Set Number", "DisplaySetNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0203), ElementsDictionaryEntry("Display Set Label", "DisplaySetLabel",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0204), ElementsDictionaryEntry("Display Set Presentation Group", "DisplaySetPresentationGroup",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0206), ElementsDictionaryEntry("Display Set Presentation Group Description", "DisplaySetPresentationGroupDescription",  "LO", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0208), ElementsDictionaryEntry("Partial Data Display Handling", "PartialDataDisplayHandling",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0210), ElementsDictionaryEntry("Synchronized Scrolling Sequence", "SynchronizedScrollingSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0212), ElementsDictionaryEntry("Display Set Scrolling Group", "DisplaySetScrollingGroup",  "US", "2-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0214), ElementsDictionaryEntry("Navigation Indicator Sequence", "NavigationIndicatorSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0216), ElementsDictionaryEntry("Navigation Display Set", "NavigationDisplaySet",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0218), ElementsDictionaryEntry("Reference Display Sets", "ReferenceDisplaySets",  "US", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0300), ElementsDictionaryEntry("Image Boxes Sequence", "ImageBoxesSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0302), ElementsDictionaryEntry("Image Box Number", "ImageBoxNumber",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0304), ElementsDictionaryEntry("Image Box Layout Type", "ImageBoxLayoutType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0306), ElementsDictionaryEntry("Image Box Tile Horizontal Dimension", "ImageBoxTileHorizontalDimension",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0308), ElementsDictionaryEntry("Image Box Tile Vertical Dimension", "ImageBoxTileVerticalDimension",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0310), ElementsDictionaryEntry("Image Box Scroll Direction", "ImageBoxScrollDirection",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0312), ElementsDictionaryEntry("Image Box Small Scroll Type", "ImageBoxSmallScrollType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0314), ElementsDictionaryEntry("Image Box Small Scroll Amount", "ImageBoxSmallScrollAmount",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0316), ElementsDictionaryEntry("Image Box Large Scroll Type", "ImageBoxLargeScrollType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0318), ElementsDictionaryEntry("Image Box Large Scroll Amount", "ImageBoxLargeScrollAmount",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0320), ElementsDictionaryEntry("Image Box Overlap Priority", "ImageBoxOverlapPriority",  "US", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0330), ElementsDictionaryEntry("Cine Relative to Real-Time", "CineRelativeToRealTime",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0400), ElementsDictionaryEntry("Filter Operations Sequence", "FilterOperationsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0402), ElementsDictionaryEntry("Filter-by Category", "FilterByCategory",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0404), ElementsDictionaryEntry("Filter-by Attribute Presence", "FilterByAttributePresence",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0406), ElementsDictionaryEntry("Filter-by Operator", "FilterByOperator",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0420), ElementsDictionaryEntry("Structured Display Background CIELab Value", "StructuredDisplayBackgroundCIELabValue",  "US", "3"));
    public_dictionary.emplace(Tag(0x0072, 0x0421), ElementsDictionaryEntry("Empty Image Box CIELab Value", "EmptyImageBoxCIELabValue",  "US", "3"));
    public_dictionary.emplace(Tag(0x0072, 0x0422), ElementsDictionaryEntry("Structured Display Image Box Sequence", "StructuredDisplayImageBoxSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0424), ElementsDictionaryEntry("Structured Display Text Box Sequence", "StructuredDisplayTextBoxSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0427), ElementsDictionaryEntry("Referenced First Frame Sequence", "ReferencedFirstFrameSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0430), ElementsDictionaryEntry("Image Box Synchronization Sequence", "ImageBoxSynchronizationSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0432), ElementsDictionaryEntry("Synchronized Image Box List", "SynchronizedImageBoxList",  "US", "2-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0434), ElementsDictionaryEntry("Type of Synchronization", "TypeOfSynchronization",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0500), ElementsDictionaryEntry("Blending Operation Type", "BlendingOperationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0510), ElementsDictionaryEntry("Reformatting Operation Type", "ReformattingOperationType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0512), ElementsDictionaryEntry("Reformatting Thickness", "ReformattingThickness",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0514), ElementsDictionaryEntry("Reformatting Interval", "ReformattingInterval",  "FD", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0516), ElementsDictionaryEntry("Reformatting Operation Initial View Direction", "ReformattingOperationInitialViewDirection",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0520), ElementsDictionaryEntry("3D Rendering Type", "ThreeDRenderingType",  "CS", "1-n"));
    public_dictionary.emplace(Tag(0x0072, 0x0600), ElementsDictionaryEntry("Sorting Operations Sequence", "SortingOperationsSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0602), ElementsDictionaryEntry("Sort-by Category", "SortByCategory",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0604), ElementsDictionaryEntry("Sorting Direction", "SortingDirection",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0700), ElementsDictionaryEntry("Display Set Patient Orientation", "DisplaySetPatientOrientation",  "CS", "2"));
    public_dictionary.emplace(Tag(0x0072, 0x0702), ElementsDictionaryEntry("VOI Type", "VOIType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0704), ElementsDictionaryEntry("Pseudo-Color Type", "PseudoColorType",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0705), ElementsDictionaryEntry("Pseudo-Color Palette Instance Reference Sequence", "PseudoColorPaletteInstanceReferenceSequence",  "SQ", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0706), ElementsDictionaryEntry("Show Grayscale Inverted", "ShowGrayscaleInverted",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0710), ElementsDictionaryEntry("Show Image True Size Flag", "ShowImageTrueSizeFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0712), ElementsDictionaryEntry("Show Graphic Annotation Flag", "ShowGraphicAnnotationFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0714), ElementsDictionaryEntry("Show Patient Demographics Flag", "ShowPatientDemographicsFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0716), ElementsDictionaryEntry("Show Acquisition Techniques Flag", "ShowAcquisitionTechniquesFlag",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0717), ElementsDictionaryEntry("Display Set Horizontal Justification", "DisplaySetHorizontalJustification",  "CS", "1"));
    public_dictionary.emplace(Tag(0x0072, 0x0718), ElementsDictionaryEntry("Display Set Vertical Justification", "DisplaySetVerticalJustification",  "CS", "1"));

    public_tags.emplace("HangingProtocolName", Tag(0x0072, 0x0002));
    public_tags.emplace("HangingProtocolDescription", Tag(0x0072, 0x0004));
    public_tags.emplace("HangingProtocolLevel", Tag(0x0072, 0x0006));
    public_tags.emplace("HangingProtocolCreator", Tag(0x0072, 0x0008));
    public_tags.emplace("HangingProtocolCreationDateTime", Tag(0x0072, 0x000a));
    public_tags.emplace("HangingProtocolDefinitionSequence", Tag(0x0072, 0x000c));
    public_tags.emplace("HangingProtocolUserIdentificationCodeSequence", Tag(0x0072, 0x000e));
    public_tags.emplace("HangingProtocolUserGroupName", Tag(0x0072, 0x0010));
    public_tags.emplace("SourceHangingProtocolSequence", Tag(0x0072, 0x0012));
    public_tags.emplace("NumberOfPriorsReferenced", Tag(0x0072, 0x0014));
    public_tags.emplace("ImageSetsSequence", Tag(0x0072, 0x0020));
    public_tags.emplace("ImageSetSelectorSequence", Tag(0x0072, 0x0022));
    public_tags.emplace("ImageSetSelectorUsageFlag", Tag(0x0072, 0x0024));
    public_tags.emplace("SelectorAttribute", Tag(0x0072, 0x0026));
    public_tags.emplace("SelectorValueNumber", Tag(0x0072, 0x0028));
    public_tags.emplace("TimeBasedImageSetsSequence", Tag(0x0072, 0x0030));
    public_tags.emplace("ImageSetNumber", Tag(0x0072, 0x0032));
    public_tags.emplace("ImageSetSelectorCategory", Tag(0x0072, 0x0034));
    public_tags.emplace("RelativeTime", Tag(0x0072, 0x0038));
    public_tags.emplace("RelativeTimeUnits", Tag(0x0072, 0x003a));
    public_tags.emplace("AbstractPriorValue", Tag(0x0072, 0x003c));
    public_tags.emplace("AbstractPriorCodeSequence", Tag(0x0072, 0x003e));
    public_tags.emplace("ImageSetLabel", Tag(0x0072, 0x0040));
    public_tags.emplace("SelectorAttributeVR", Tag(0x0072, 0x0050));
    public_tags.emplace("SelectorSequencePointer", Tag(0x0072, 0x0052));
    public_tags.emplace("SelectorSequencePointerPrivateCreator", Tag(0x0072, 0x0054));
    public_tags.emplace("SelectorAttributePrivateCreator", Tag(0x0072, 0x0056));
    public_tags.emplace("SelectorAEValue", Tag(0x0072, 0x005e));
    public_tags.emplace("SelectorASValue", Tag(0x0072, 0x005f));
    public_tags.emplace("SelectorATValue", Tag(0x0072, 0x0060));
    public_tags.emplace("SelectorDAValue", Tag(0x0072, 0x0061));
    public_tags.emplace("SelectorCSValue", Tag(0x0072, 0x0062));
    public_tags.emplace("SelectorDTValue", Tag(0x0072, 0x0063));
    public_tags.emplace("SelectorISValue", Tag(0x0072, 0x0064));
    public_tags.emplace("SelectorOBValue", Tag(0x0072, 0x0065));
    public_tags.emplace("SelectorLOValue", Tag(0x0072, 0x0066));
    public_tags.emplace("SelectorOFValue", Tag(0x0072, 0x0067));
    public_tags.emplace("SelectorLTValue", Tag(0x0072, 0x0068));
    public_tags.emplace("SelectorOWValue", Tag(0x0072, 0x0069));
    public_tags.emplace("SelectorPNValue", Tag(0x0072, 0x006a));
    public_tags.emplace("SelectorTMValue", Tag(0x0072, 0x006b));
    public_tags.emplace("SelectorSHValue", Tag(0x0072, 0x006c));
    public_tags.emplace("SelectorUNValue", Tag(0x0072, 0x006d));
    public_tags.emplace("SelectorSTValue", Tag(0x0072, 0x006e));
    public_tags.emplace("SelectorUCValue", Tag(0x0072, 0x006f));
    public_tags.emplace("SelectorUTValue", Tag(0x0072, 0x0070));
    public_tags.emplace("SelectorURValue", Tag(0x0072, 0x0071));
    public_tags.emplace("SelectorDSValue", Tag(0x0072, 0x0072));
    public_tags.emplace("SelectorODValue", Tag(0x0072, 0x0073));
    public_tags.emplace("SelectorFDValue", Tag(0x0072, 0x0074));
    public_tags.emplace("SelectorOLValue", Tag(0x0072, 0x0075));
    public_tags.emplace("SelectorFLValue", Tag(0x0072, 0x0076));
    public_tags.emplace("SelectorULValue", Tag(0x0072, 0x0078));
    public_tags.emplace("SelectorUSValue", Tag(0x0072, 0x007a));
    public_tags.emplace("SelectorSLValue", Tag(0x0072, 0x007c));
    public_tags.emplace("SelectorSSValue", Tag(0x0072, 0x007e));
    public_tags.emplace("SelectorUIValue", Tag(0x0072, 0x007f));
    public_tags.emplace("SelectorCodeSequenceValue", Tag(0x0072, 0x0080));
    public_tags.emplace("NumberOfScreens", Tag(0x0072, 0x0100));
    public_tags.emplace("NominalScreenDefinitionSequence", Tag(0x0072, 0x0102));
    public_tags.emplace("NumberOfVerticalPixels", Tag(0x0072, 0x0104));
    public_tags.emplace("NumberOfHorizontalPixels", Tag(0x0072, 0x0106));
    public_tags.emplace("DisplayEnvironmentSpatialPosition", Tag(0x0072, 0x0108));
    public_tags.emplace("ScreenMinimumGrayscaleBitDepth", Tag(0x0072, 0x010a));
    public_tags.emplace("ScreenMinimumColorBitDepth", Tag(0x0072, 0x010c));
    public_tags.emplace("ApplicationMaximumRepaintTime", Tag(0x0072, 0x010e));
    public_tags.emplace("DisplaySetsSequence", Tag(0x0072, 0x0200));
    public_tags.emplace("DisplaySetNumber", Tag(0x0072, 0x0202));
    public_tags.emplace("DisplaySetLabel", Tag(0x0072, 0x0203));
    public_tags.emplace("DisplaySetPresentationGroup", Tag(0x0072, 0x0204));
    public_tags.emplace("DisplaySetPresentationGroupDescription", Tag(0x0072, 0x0206));
    public_tags.emplace("PartialDataDisplayHandling", Tag(0x0072, 0x0208));
    public_tags.emplace("SynchronizedScrollingSequence", Tag(0x0072, 0x0210));
    public_tags.emplace("DisplaySetScrollingGroup", Tag(0x0072, 0x0212));
    public_tags.emplace("NavigationIndicatorSequence", Tag(0x0072, 0x0214));
    public_tags.emplace("NavigationDisplaySet", Tag(0x0072, 0x0216));
    public_tags.emplace("ReferenceDisplaySets", Tag(0x0072, 0x0218));
    public_tags.emplace("ImageBoxesSequence", Tag(0x0072, 0x0300));
    public_tags.emplace("ImageBoxNumber", Tag(0x0072, 0x0302));
    public_tags.emplace("ImageBoxLayoutType", Tag(0x0072, 0x0304));
    public_tags.emplace("ImageBoxTileHorizontalDimension", Tag(0x0072, 0x0306));
    public_tags.emplace("ImageBoxTileVerticalDimension", Tag(0x0072, 0x0308));
    public_tags.emplace("ImageBoxScrollDirection", Tag(0x0072, 0x0310));
    public_tags.emplace("ImageBoxSmallScrollType", Tag(0x0072, 0x0312));
    public_tags.emplace("ImageBoxSmallScrollAmount", Tag(0x0072, 0x0314));
    public_tags.emplace("ImageBoxLargeScrollType", Tag(0x0072, 0x0316));
    public_tags.emplace("ImageBoxLargeScrollAmount", Tag(0x0072, 0x0318));
    public_tags.emplace("ImageBoxOverlapPriority", Tag(0x0072, 0x0320));
    public_tags.emplace("CineRelativeToRealTime", Tag(0x0072, 0x0330));
    public_tags.emplace("FilterOperationsSequence", Tag(0x0072, 0x0400));
    public_tags.emplace("FilterByCategory", Tag(0x0072, 0x0402));
    public_tags.emplace("FilterByAttributePresence", Tag(0x0072, 0x0404));
    public_tags.emplace("FilterByOperator", Tag(0x0072, 0x0406));
    public_tags.emplace("StructuredDisplayBackgroundCIELabValue", Tag(0x0072, 0x0420));
    public_tags.emplace("EmptyImageBoxCIELabValue", Tag(0x0072, 0x0421));
    public_tags.emplace("StructuredDisplayImageBoxSequence", Tag(0x0072, 0x0422));
    public_tags.emplace("StructuredDisplayTextBoxSequence", Tag(0x0072, 0x0424));
    public_tags.emplace("ReferencedFirstFrameSequence", Tag(0x0072, 0x0427));
    public_tags.emplace("ImageBoxSynchronizationSequence", Tag(0x0072, 0x0430));
    public_tags.emplace("SynchronizedImageBoxList", Tag(0x0072, 0x0432));
    public_tags.emplace("TypeOfSynchronization", Tag(0x0072, 0x0434));
    public_tags.emplace("BlendingOperationType", Tag(0x0072, 0x0500));
    public_tags.emplace("ReformattingOperationType", Tag(0x0072, 0x0510));
    public_tags.emplace("ReformattingThickness", Tag(0x0072, 0x0512));
    public_tags.emplace("ReformattingInterval", Tag(0x0072, 0x0514));
    public_tags.emplace("ReformattingOperationInitialViewDirection", Tag(0x0072, 0x0516));
    public_tags.emplace("ThreeDRenderingType", Tag(0x0072, 0x0520));
    public_tags.emplace("SortingOperationsSequence", Tag(0x0072, 0x0600));
    public_tags.emplace("SortByCategory", Tag(0x0072, 0x0602));
    public_tags.emplace("SortingDirection", Tag(0x0072, 0x0604));
    public_tags.emplace("DisplaySetPatientOrientation", Tag(0x0072, 0x0700));
    public_tags.emplace("VOIType", Tag(0x0072, 0x0702));
    public_tags.emplace("PseudoColorType", Tag(0x0072, 0x0704));
    public_tags.emplace("PseudoColorPaletteInstanceReferenceSequence", Tag(0x0072, 0x0705));
    public_tags.emplace("ShowGrayscaleInverted", Tag(0x0072, 0x0706));
    public_tags.emplace("ShowImageTrueSizeFlag", Tag(0x0072, 0x0710));
    public_tags.emplace("ShowGraphicAnnotationFlag", Tag(0x0072, 0x0712));
    public_tags.emplace("ShowPatientDemographicsFlag", Tag(0x0072, 0x0714));
    public_tags.emplace("ShowAcquisitionTechniquesFlag", Tag(0x0072, 0x0716));
    public_tags.emplace("DisplaySetHorizontalJustification", Tag(0x0072, 0x0717));
    public_tags.emplace("DisplaySetVerticalJustification", Tag(0x0072, 0x0718));
}

}

}