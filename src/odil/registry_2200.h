/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2200
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2200

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const LabelUsingInformationExtractedFromInstances(0x2200, 0x0001);
Tag const LabelText(0x2200, 0x0002);
Tag const LabelStyleSelection(0x2200, 0x0003);
Tag const MediaDisposition(0x2200, 0x0004);
Tag const BarcodeValue(0x2200, 0x0005);
Tag const BarcodeSymbology(0x2200, 0x0006);
Tag const AllowMediaSplitting(0x2200, 0x0007);
Tag const IncludeNonDICOMObjects(0x2200, 0x0008);
Tag const IncludeDisplayApplication(0x2200, 0x0009);
Tag const PreserveCompositeInstancesAfterMediaCreation(0x2200, 0x000a);
Tag const TotalNumberOfPiecesOfMediaCreated(0x2200, 0x000b);
Tag const RequestedMediaApplicationProfile(0x2200, 0x000c);
Tag const ReferencedStorageMediaSequence(0x2200, 0x000d);
Tag const FailureAttributes(0x2200, 0x000e);
Tag const AllowLossyCompression(0x2200, 0x000f);
Tag const RequestPriority(0x2200, 0x0020);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2200