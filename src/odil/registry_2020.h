/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2020
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2020

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const ImageBoxPosition(0x2020, 0x0010);
Tag const Polarity(0x2020, 0x0020);
Tag const RequestedImageSize(0x2020, 0x0030);
Tag const RequestedDecimateCropBehavior(0x2020, 0x0040);
Tag const RequestedResolutionID(0x2020, 0x0050);
Tag const RequestedImageSizeFlag(0x2020, 0x00a0);
Tag const DecimateCropResult(0x2020, 0x00a2);
Tag const BasicGrayscaleImageSequence(0x2020, 0x0110);
Tag const BasicColorImageSequence(0x2020, 0x0111);
Tag const ReferencedImageOverlayBoxSequence(0x2020, 0x0130);
Tag const ReferencedVOILUTBoxSequence(0x2020, 0x0140);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2020