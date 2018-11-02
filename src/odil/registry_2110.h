/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2110
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2110

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const PrinterStatus(0x2110, 0x0010);
Tag const PrinterStatusInfo(0x2110, 0x0020);
Tag const PrinterName(0x2110, 0x0030);
Tag const PrintQueueID(0x2110, 0x0099);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2110