/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0072
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0072

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const HangingProtocolName(0x0072, 0x0002);
Tag const HangingProtocolDescription(0x0072, 0x0004);
Tag const HangingProtocolLevel(0x0072, 0x0006);
Tag const HangingProtocolCreator(0x0072, 0x0008);
Tag const HangingProtocolCreationDateTime(0x0072, 0x000a);
Tag const HangingProtocolDefinitionSequence(0x0072, 0x000c);
Tag const HangingProtocolUserIdentificationCodeSequence(0x0072, 0x000e);
Tag const HangingProtocolUserGroupName(0x0072, 0x0010);
Tag const SourceHangingProtocolSequence(0x0072, 0x0012);
Tag const NumberOfPriorsReferenced(0x0072, 0x0014);
Tag const ImageSetsSequence(0x0072, 0x0020);
Tag const ImageSetSelectorSequence(0x0072, 0x0022);
Tag const ImageSetSelectorUsageFlag(0x0072, 0x0024);
Tag const SelectorAttribute(0x0072, 0x0026);
Tag const SelectorValueNumber(0x0072, 0x0028);
Tag const TimeBasedImageSetsSequence(0x0072, 0x0030);
Tag const ImageSetNumber(0x0072, 0x0032);
Tag const ImageSetSelectorCategory(0x0072, 0x0034);
Tag const RelativeTime(0x0072, 0x0038);
Tag const RelativeTimeUnits(0x0072, 0x003a);
Tag const AbstractPriorValue(0x0072, 0x003c);
Tag const AbstractPriorCodeSequence(0x0072, 0x003e);
Tag const ImageSetLabel(0x0072, 0x0040);
Tag const SelectorAttributeVR(0x0072, 0x0050);
Tag const SelectorSequencePointer(0x0072, 0x0052);
Tag const SelectorSequencePointerPrivateCreator(0x0072, 0x0054);
Tag const SelectorAttributePrivateCreator(0x0072, 0x0056);
Tag const SelectorAEValue(0x0072, 0x005e);
Tag const SelectorASValue(0x0072, 0x005f);
Tag const SelectorATValue(0x0072, 0x0060);
Tag const SelectorDAValue(0x0072, 0x0061);
Tag const SelectorCSValue(0x0072, 0x0062);
Tag const SelectorDTValue(0x0072, 0x0063);
Tag const SelectorISValue(0x0072, 0x0064);
Tag const SelectorOBValue(0x0072, 0x0065);
Tag const SelectorLOValue(0x0072, 0x0066);
Tag const SelectorOFValue(0x0072, 0x0067);
Tag const SelectorLTValue(0x0072, 0x0068);
Tag const SelectorOWValue(0x0072, 0x0069);
Tag const SelectorPNValue(0x0072, 0x006a);
Tag const SelectorTMValue(0x0072, 0x006b);
Tag const SelectorSHValue(0x0072, 0x006c);
Tag const SelectorUNValue(0x0072, 0x006d);
Tag const SelectorSTValue(0x0072, 0x006e);
Tag const SelectorUCValue(0x0072, 0x006f);
Tag const SelectorUTValue(0x0072, 0x0070);
Tag const SelectorURValue(0x0072, 0x0071);
Tag const SelectorDSValue(0x0072, 0x0072);
Tag const SelectorODValue(0x0072, 0x0073);
Tag const SelectorFDValue(0x0072, 0x0074);
Tag const SelectorOLValue(0x0072, 0x0075);
Tag const SelectorFLValue(0x0072, 0x0076);
Tag const SelectorULValue(0x0072, 0x0078);
Tag const SelectorUSValue(0x0072, 0x007a);
Tag const SelectorSLValue(0x0072, 0x007c);
Tag const SelectorSSValue(0x0072, 0x007e);
Tag const SelectorUIValue(0x0072, 0x007f);
Tag const SelectorCodeSequenceValue(0x0072, 0x0080);
Tag const SelectorOVValue(0x0072, 0x0081);
Tag const SelectorSVValue(0x0072, 0x0082);
Tag const SelectorUVValue(0x0072, 0x0083);
Tag const NumberOfScreens(0x0072, 0x0100);
Tag const NominalScreenDefinitionSequence(0x0072, 0x0102);
Tag const NumberOfVerticalPixels(0x0072, 0x0104);
Tag const NumberOfHorizontalPixels(0x0072, 0x0106);
Tag const DisplayEnvironmentSpatialPosition(0x0072, 0x0108);
Tag const ScreenMinimumGrayscaleBitDepth(0x0072, 0x010a);
Tag const ScreenMinimumColorBitDepth(0x0072, 0x010c);
Tag const ApplicationMaximumRepaintTime(0x0072, 0x010e);
Tag const DisplaySetsSequence(0x0072, 0x0200);
Tag const DisplaySetNumber(0x0072, 0x0202);
Tag const DisplaySetLabel(0x0072, 0x0203);
Tag const DisplaySetPresentationGroup(0x0072, 0x0204);
Tag const DisplaySetPresentationGroupDescription(0x0072, 0x0206);
Tag const PartialDataDisplayHandling(0x0072, 0x0208);
Tag const SynchronizedScrollingSequence(0x0072, 0x0210);
Tag const DisplaySetScrollingGroup(0x0072, 0x0212);
Tag const NavigationIndicatorSequence(0x0072, 0x0214);
Tag const NavigationDisplaySet(0x0072, 0x0216);
Tag const ReferenceDisplaySets(0x0072, 0x0218);
Tag const ImageBoxesSequence(0x0072, 0x0300);
Tag const ImageBoxNumber(0x0072, 0x0302);
Tag const ImageBoxLayoutType(0x0072, 0x0304);
Tag const ImageBoxTileHorizontalDimension(0x0072, 0x0306);
Tag const ImageBoxTileVerticalDimension(0x0072, 0x0308);
Tag const ImageBoxScrollDirection(0x0072, 0x0310);
Tag const ImageBoxSmallScrollType(0x0072, 0x0312);
Tag const ImageBoxSmallScrollAmount(0x0072, 0x0314);
Tag const ImageBoxLargeScrollType(0x0072, 0x0316);
Tag const ImageBoxLargeScrollAmount(0x0072, 0x0318);
Tag const ImageBoxOverlapPriority(0x0072, 0x0320);
Tag const CineRelativeToRealTime(0x0072, 0x0330);
Tag const FilterOperationsSequence(0x0072, 0x0400);
Tag const FilterByCategory(0x0072, 0x0402);
Tag const FilterByAttributePresence(0x0072, 0x0404);
Tag const FilterByOperator(0x0072, 0x0406);
Tag const StructuredDisplayBackgroundCIELabValue(0x0072, 0x0420);
Tag const EmptyImageBoxCIELabValue(0x0072, 0x0421);
Tag const StructuredDisplayImageBoxSequence(0x0072, 0x0422);
Tag const StructuredDisplayTextBoxSequence(0x0072, 0x0424);
Tag const ReferencedFirstFrameSequence(0x0072, 0x0427);
Tag const ImageBoxSynchronizationSequence(0x0072, 0x0430);
Tag const SynchronizedImageBoxList(0x0072, 0x0432);
Tag const TypeOfSynchronization(0x0072, 0x0434);
Tag const BlendingOperationType(0x0072, 0x0500);
Tag const ReformattingOperationType(0x0072, 0x0510);
Tag const ReformattingThickness(0x0072, 0x0512);
Tag const ReformattingInterval(0x0072, 0x0514);
Tag const ReformattingOperationInitialViewDirection(0x0072, 0x0516);
Tag const ThreeDRenderingType(0x0072, 0x0520);
Tag const SortingOperationsSequence(0x0072, 0x0600);
Tag const SortByCategory(0x0072, 0x0602);
Tag const SortingDirection(0x0072, 0x0604);
Tag const DisplaySetPatientOrientation(0x0072, 0x0700);
Tag const VOIType(0x0072, 0x0702);
Tag const PseudoColorType(0x0072, 0x0704);
Tag const PseudoColorPaletteInstanceReferenceSequence(0x0072, 0x0705);
Tag const ShowGrayscaleInverted(0x0072, 0x0706);
Tag const ShowImageTrueSizeFlag(0x0072, 0x0710);
Tag const ShowGraphicAnnotationFlag(0x0072, 0x0712);
Tag const ShowPatientDemographicsFlag(0x0072, 0x0714);
Tag const ShowAcquisitionTechniquesFlag(0x0072, 0x0716);
Tag const DisplaySetHorizontalJustification(0x0072, 0x0717);
Tag const DisplaySetVerticalJustification(0x0072, 0x0718);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0072