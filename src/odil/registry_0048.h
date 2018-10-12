/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0048
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0048

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const ImagedVolumeWidth(0x0048, 0x0001);
Tag const ImagedVolumeHeight(0x0048, 0x0002);
Tag const ImagedVolumeDepth(0x0048, 0x0003);
Tag const TotalPixelMatrixColumns(0x0048, 0x0006);
Tag const TotalPixelMatrixRows(0x0048, 0x0007);
Tag const TotalPixelMatrixOriginSequence(0x0048, 0x0008);
Tag const SpecimenLabelInImage(0x0048, 0x0010);
Tag const FocusMethod(0x0048, 0x0011);
Tag const ExtendedDepthOfField(0x0048, 0x0012);
Tag const NumberOfFocalPlanes(0x0048, 0x0013);
Tag const DistanceBetweenFocalPlanes(0x0048, 0x0014);
Tag const RecommendedAbsentPixelCIELabValue(0x0048, 0x0015);
Tag const IlluminatorTypeCodeSequence(0x0048, 0x0100);
Tag const ImageOrientationSlide(0x0048, 0x0102);
Tag const OpticalPathSequence(0x0048, 0x0105);
Tag const OpticalPathIdentifier(0x0048, 0x0106);
Tag const OpticalPathDescription(0x0048, 0x0107);
Tag const IlluminationColorCodeSequence(0x0048, 0x0108);
Tag const SpecimenReferenceSequence(0x0048, 0x0110);
Tag const CondenserLensPower(0x0048, 0x0111);
Tag const ObjectiveLensPower(0x0048, 0x0112);
Tag const ObjectiveLensNumericalAperture(0x0048, 0x0113);
Tag const PaletteColorLookupTableSequence(0x0048, 0x0120);
Tag const ReferencedImageNavigationSequence(0x0048, 0x0200);
Tag const TopLeftHandCornerOfLocalizerArea(0x0048, 0x0201);
Tag const BottomRightHandCornerOfLocalizerArea(0x0048, 0x0202);
Tag const OpticalPathIdentificationSequence(0x0048, 0x0207);
Tag const PlanePositionSlideSequence(0x0048, 0x021a);
Tag const ColumnPositionInTotalImagePixelMatrix(0x0048, 0x021e);
Tag const RowPositionInTotalImagePixelMatrix(0x0048, 0x021f);
Tag const PixelOriginInterpretation(0x0048, 0x0301);
Tag const NumberOfOpticalPaths(0x0048, 0x0302);
Tag const TotalPixelMatrixFocalPlanes(0x0048, 0x0303);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0048