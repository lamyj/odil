/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0082
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0082

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const AssessmentSummary(0x0082, 0x0001);
Tag const AssessmentSummaryDescription(0x0082, 0x0003);
Tag const AssessedSOPInstanceSequence(0x0082, 0x0004);
Tag const ReferencedComparisonSOPInstanceSequence(0x0082, 0x0005);
Tag const NumberOfAssessmentObservations(0x0082, 0x0006);
Tag const AssessmentObservationsSequence(0x0082, 0x0007);
Tag const ObservationSignificance(0x0082, 0x0008);
Tag const ObservationDescription(0x0082, 0x000a);
Tag const StructuredConstraintObservationSequence(0x0082, 0x000c);
Tag const AssessedAttributeValueSequence(0x0082, 0x0010);
Tag const AssessmentSetID(0x0082, 0x0016);
Tag const AssessmentRequesterSequence(0x0082, 0x0017);
Tag const SelectorAttributeName(0x0082, 0x0018);
Tag const SelectorAttributeKeyword(0x0082, 0x0019);
Tag const AssessmentTypeCodeSequence(0x0082, 0x0021);
Tag const ObservationBasisCodeSequence(0x0082, 0x0022);
Tag const AssessmentLabel(0x0082, 0x0023);
Tag const ConstraintType(0x0082, 0x0032);
Tag const SpecificationSelectionGuidance(0x0082, 0x0033);
Tag const ConstraintValueSequence(0x0082, 0x0034);
Tag const RecommendedDefaultValueSequence(0x0082, 0x0035);
Tag const ConstraintViolationSignificance(0x0082, 0x0036);
Tag const ConstraintViolationCondition(0x0082, 0x0037);
Tag const ModifiableConstraintFlag(0x0082, 0x0038);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0082