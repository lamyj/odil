/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0002
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0002

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const FileMetaInformationGroupLength(0x0002, 0x0000);
Tag const FileMetaInformationVersion(0x0002, 0x0001);
Tag const MediaStorageSOPClassUID(0x0002, 0x0002);
Tag const MediaStorageSOPInstanceUID(0x0002, 0x0003);
Tag const TransferSyntaxUID(0x0002, 0x0010);
Tag const ImplementationClassUID(0x0002, 0x0012);
Tag const ImplementationVersionName(0x0002, 0x0013);
Tag const SourceApplicationEntityTitle(0x0002, 0x0016);
Tag const SendingApplicationEntityTitle(0x0002, 0x0017);
Tag const ReceivingApplicationEntityTitle(0x0002, 0x0018);
Tag const SourcePresentationAddress(0x0002, 0x0026);
Tag const SendingPresentationAddress(0x0002, 0x0027);
Tag const ReceivingPresentationAddress(0x0002, 0x0028);
Tag const RTVMetaInformationVersion(0x0002, 0x0031);
Tag const RTVCommunicationSOPClassUID(0x0002, 0x0032);
Tag const RTVCommunicationSOPInstanceUID(0x0002, 0x0033);
Tag const RTVSourceIdentifier(0x0002, 0x0035);
Tag const RTVFlowIdentifier(0x0002, 0x0036);
Tag const RTVFlowRTPSamplingRate(0x0002, 0x0037);
Tag const RTVFlowActualFrameDuration(0x0002, 0x0038);
Tag const PrivateInformationCreatorUID(0x0002, 0x0100);
Tag const PrivateInformation(0x0002, 0x0102);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0002