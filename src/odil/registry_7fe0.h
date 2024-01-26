/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_7fe0
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_7fe0

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const ExtendedOffsetTable(0x7fe0, 0x0001);
Tag const ExtendedOffsetTableLengths(0x7fe0, 0x0002);
Tag const EncapsulatedPixelDataValueTotalLength(0x7fe0, 0x0003);
Tag const FloatPixelData(0x7fe0, 0x0008);
Tag const DoubleFloatPixelData(0x7fe0, 0x0009);
Tag const PixelData(0x7fe0, 0x0010);
Tag const CoefficientsSDVN(0x7fe0, 0x0020);
Tag const CoefficientsSDHN(0x7fe0, 0x0030);
Tag const CoefficientsSDDN(0x7fe0, 0x0040);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_7fe0