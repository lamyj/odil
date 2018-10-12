/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0078
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0078

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const ImplantTemplateGroupName(0x0078, 0x0001);
Tag const ImplantTemplateGroupDescription(0x0078, 0x0010);
Tag const ImplantTemplateGroupIssuer(0x0078, 0x0020);
Tag const ImplantTemplateGroupVersion(0x0078, 0x0024);
Tag const ReplacedImplantTemplateGroupSequence(0x0078, 0x0026);
Tag const ImplantTemplateGroupTargetAnatomySequence(0x0078, 0x0028);
Tag const ImplantTemplateGroupMembersSequence(0x0078, 0x002a);
Tag const ImplantTemplateGroupMemberID(0x0078, 0x002e);
Tag const ThreeDImplantTemplateGroupMemberMatchingPoint(0x0078, 0x0050);
Tag const ThreeDImplantTemplateGroupMemberMatchingAxes(0x0078, 0x0060);
Tag const ImplantTemplateGroupMemberMatching2DCoordinatesSequence(0x0078, 0x0070);
Tag const TwoDImplantTemplateGroupMemberMatchingPoint(0x0078, 0x0090);
Tag const TwoDImplantTemplateGroupMemberMatchingAxes(0x0078, 0x00a0);
Tag const ImplantTemplateGroupVariationDimensionSequence(0x0078, 0x00b0);
Tag const ImplantTemplateGroupVariationDimensionName(0x0078, 0x00b2);
Tag const ImplantTemplateGroupVariationDimensionRankSequence(0x0078, 0x00b4);
Tag const ReferencedImplantTemplateGroupMemberID(0x0078, 0x00b6);
Tag const ImplantTemplateGroupVariationDimensionRank(0x0078, 0x00b8);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0078