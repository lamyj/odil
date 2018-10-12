/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2100
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2100

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const PrintJobID(0x2100, 0x0010);
Tag const ExecutionStatus(0x2100, 0x0020);
Tag const ExecutionStatusInfo(0x2100, 0x0030);
Tag const CreationDate(0x2100, 0x0040);
Tag const CreationTime(0x2100, 0x0050);
Tag const Originator(0x2100, 0x0070);
Tag const DestinationAE(0x2100, 0x0140);
Tag const OwnerID(0x2100, 0x0160);
Tag const NumberOfFilms(0x2100, 0x0170);
Tag const ReferencedPrintJobSequencePullStoredPrint(0x2100, 0x0500);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2100