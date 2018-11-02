/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0000
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0000

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const CommandGroupLength(0x0000, 0x0000);
Tag const AffectedSOPClassUID(0x0000, 0x0002);
Tag const RequestedSOPClassUID(0x0000, 0x0003);
Tag const CommandField(0x0000, 0x0100);
Tag const MessageID(0x0000, 0x0110);
Tag const MessageIDBeingRespondedTo(0x0000, 0x0120);
Tag const MoveDestination(0x0000, 0x0600);
Tag const Priority(0x0000, 0x0700);
Tag const CommandDataSetType(0x0000, 0x0800);
Tag const Status(0x0000, 0x0900);
Tag const OffendingElement(0x0000, 0x0901);
Tag const ErrorComment(0x0000, 0x0902);
Tag const ErrorID(0x0000, 0x0903);
Tag const AffectedSOPInstanceUID(0x0000, 0x1000);
Tag const RequestedSOPInstanceUID(0x0000, 0x1001);
Tag const EventTypeID(0x0000, 0x1002);
Tag const AttributeIdentifierList(0x0000, 0x1005);
Tag const ActionTypeID(0x0000, 0x1008);
Tag const NumberOfRemainingSuboperations(0x0000, 0x1020);
Tag const NumberOfCompletedSuboperations(0x0000, 0x1021);
Tag const NumberOfFailedSuboperations(0x0000, 0x1022);
Tag const NumberOfWarningSuboperations(0x0000, 0x1023);
Tag const MoveOriginatorApplicationEntityTitle(0x0000, 0x1030);
Tag const MoveOriginatorMessageID(0x0000, 0x1031);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0000