/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2040
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2040

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const ReferencedOverlayPlaneSequence(0x2040, 0x0010);
Tag const ReferencedOverlayPlaneGroups(0x2040, 0x0011);
Tag const OverlayPixelDataSequence(0x2040, 0x0020);
Tag const OverlayMagnificationType(0x2040, 0x0060);
Tag const OverlaySmoothingType(0x2040, 0x0070);
Tag const OverlayOrImageMagnification(0x2040, 0x0072);
Tag const MagnifyToNumberOfColumns(0x2040, 0x0074);
Tag const OverlayForegroundDensity(0x2040, 0x0080);
Tag const OverlayBackgroundDensity(0x2040, 0x0082);
Tag const OverlayMode(0x2040, 0x0090);
Tag const ThresholdDensity(0x2040, 0x0100);
Tag const ReferencedImageBoxSequenceRetired(0x2040, 0x0500);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2040