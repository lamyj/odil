/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0032
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0032

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const StudyStatusID(0x0032, 0x000a);
Tag const StudyPriorityID(0x0032, 0x000c);
Tag const StudyIDIssuer(0x0032, 0x0012);
Tag const StudyVerifiedDate(0x0032, 0x0032);
Tag const StudyVerifiedTime(0x0032, 0x0033);
Tag const StudyReadDate(0x0032, 0x0034);
Tag const StudyReadTime(0x0032, 0x0035);
Tag const ScheduledStudyStartDate(0x0032, 0x1000);
Tag const ScheduledStudyStartTime(0x0032, 0x1001);
Tag const ScheduledStudyStopDate(0x0032, 0x1010);
Tag const ScheduledStudyStopTime(0x0032, 0x1011);
Tag const ScheduledStudyLocation(0x0032, 0x1020);
Tag const ScheduledStudyLocationAETitle(0x0032, 0x1021);
Tag const ReasonForStudy(0x0032, 0x1030);
Tag const RequestingPhysicianIdentificationSequence(0x0032, 0x1031);
Tag const RequestingPhysician(0x0032, 0x1032);
Tag const RequestingService(0x0032, 0x1033);
Tag const RequestingServiceCodeSequence(0x0032, 0x1034);
Tag const StudyArrivalDate(0x0032, 0x1040);
Tag const StudyArrivalTime(0x0032, 0x1041);
Tag const StudyCompletionDate(0x0032, 0x1050);
Tag const StudyCompletionTime(0x0032, 0x1051);
Tag const StudyComponentStatusID(0x0032, 0x1055);
Tag const RequestedProcedureDescription(0x0032, 0x1060);
Tag const RequestedProcedureCodeSequence(0x0032, 0x1064);
Tag const RequestedLateralityCodeSequence(0x0032, 0x1065);
Tag const ReasonForVisit(0x0032, 0x1066);
Tag const ReasonForVisitCodeSequence(0x0032, 0x1067);
Tag const RequestedContrastAgent(0x0032, 0x1070);
Tag const StudyComments(0x0032, 0x4000);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0032