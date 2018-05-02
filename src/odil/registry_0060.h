/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0060
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0060

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const HistogramSequence(0x0060, 0x3000);
Tag const HistogramNumberOfBins(0x0060, 0x3002);
Tag const HistogramFirstBinValue(0x0060, 0x3004);
Tag const HistogramLastBinValue(0x0060, 0x3006);
Tag const HistogramBinWidth(0x0060, 0x3008);
Tag const HistogramExplanation(0x0060, 0x3010);
Tag const HistogramData(0x0060, 0x3020);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0060