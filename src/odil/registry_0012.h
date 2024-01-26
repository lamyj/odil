/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0012
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0012

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const ClinicalTrialSponsorName(0x0012, 0x0010);
Tag const ClinicalTrialProtocolID(0x0012, 0x0020);
Tag const ClinicalTrialProtocolName(0x0012, 0x0021);
Tag const ClinicalTrialSiteID(0x0012, 0x0030);
Tag const ClinicalTrialSiteName(0x0012, 0x0031);
Tag const ClinicalTrialSubjectID(0x0012, 0x0040);
Tag const ClinicalTrialSubjectReadingID(0x0012, 0x0042);
Tag const ClinicalTrialTimePointID(0x0012, 0x0050);
Tag const ClinicalTrialTimePointDescription(0x0012, 0x0051);
Tag const LongitudinalTemporalOffsetFromEvent(0x0012, 0x0052);
Tag const LongitudinalTemporalEventType(0x0012, 0x0053);
Tag const ClinicalTrialTimePointTypeCodeSequence(0x0012, 0x0054);
Tag const ClinicalTrialCoordinatingCenterName(0x0012, 0x0060);
Tag const PatientIdentityRemoved(0x0012, 0x0062);
Tag const DeidentificationMethod(0x0012, 0x0063);
Tag const DeidentificationMethodCodeSequence(0x0012, 0x0064);
Tag const ClinicalTrialSeriesID(0x0012, 0x0071);
Tag const ClinicalTrialSeriesDescription(0x0012, 0x0072);
Tag const ClinicalTrialProtocolEthicsCommitteeName(0x0012, 0x0081);
Tag const ClinicalTrialProtocolEthicsCommitteeApprovalNumber(0x0012, 0x0082);
Tag const ConsentForClinicalTrialUseSequence(0x0012, 0x0083);
Tag const DistributionType(0x0012, 0x0084);
Tag const ConsentForDistributionFlag(0x0012, 0x0085);
Tag const EthicsCommitteeApprovalEffectivenessStartDate(0x0012, 0x0086);
Tag const EthicsCommitteeApprovalEffectivenessEndDate(0x0012, 0x0087);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0012