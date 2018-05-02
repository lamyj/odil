/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0038
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0038

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const ReferencedPatientAliasSequence(0x0038, 0x0004);
Tag const VisitStatusID(0x0038, 0x0008);
Tag const AdmissionID(0x0038, 0x0010);
Tag const IssuerOfAdmissionID(0x0038, 0x0011);
Tag const IssuerOfAdmissionIDSequence(0x0038, 0x0014);
Tag const RouteOfAdmissions(0x0038, 0x0016);
Tag const ScheduledAdmissionDate(0x0038, 0x001a);
Tag const ScheduledAdmissionTime(0x0038, 0x001b);
Tag const ScheduledDischargeDate(0x0038, 0x001c);
Tag const ScheduledDischargeTime(0x0038, 0x001d);
Tag const ScheduledPatientInstitutionResidence(0x0038, 0x001e);
Tag const AdmittingDate(0x0038, 0x0020);
Tag const AdmittingTime(0x0038, 0x0021);
Tag const DischargeDate(0x0038, 0x0030);
Tag const DischargeTime(0x0038, 0x0032);
Tag const DischargeDiagnosisDescription(0x0038, 0x0040);
Tag const DischargeDiagnosisCodeSequence(0x0038, 0x0044);
Tag const SpecialNeeds(0x0038, 0x0050);
Tag const ServiceEpisodeID(0x0038, 0x0060);
Tag const IssuerOfServiceEpisodeID(0x0038, 0x0061);
Tag const ServiceEpisodeDescription(0x0038, 0x0062);
Tag const IssuerOfServiceEpisodeIDSequence(0x0038, 0x0064);
Tag const PertinentDocumentsSequence(0x0038, 0x0100);
Tag const PertinentResourcesSequence(0x0038, 0x0101);
Tag const ResourceDescription(0x0038, 0x0102);
Tag const CurrentPatientLocation(0x0038, 0x0300);
Tag const PatientInstitutionResidence(0x0038, 0x0400);
Tag const PatientState(0x0038, 0x0500);
Tag const PatientClinicalTrialParticipationSequence(0x0038, 0x0502);
Tag const VisitComments(0x0038, 0x4000);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0038