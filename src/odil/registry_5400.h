/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_5400
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_5400

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const WaveformSequence(0x5400, 0x0100);
Tag const ChannelMinimumValue(0x5400, 0x0110);
Tag const ChannelMaximumValue(0x5400, 0x0112);
Tag const WaveformBitsAllocated(0x5400, 0x1004);
Tag const WaveformSampleInterpretation(0x5400, 0x1006);
Tag const WaveformPaddingValue(0x5400, 0x100a);
Tag const WaveformData(0x5400, 0x1010);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_5400