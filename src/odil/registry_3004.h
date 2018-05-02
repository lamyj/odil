/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3004
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3004

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const DVHType(0x3004, 0x0001);
Tag const DoseUnits(0x3004, 0x0002);
Tag const DoseType(0x3004, 0x0004);
Tag const SpatialTransformOfDose(0x3004, 0x0005);
Tag const DoseComment(0x3004, 0x0006);
Tag const NormalizationPoint(0x3004, 0x0008);
Tag const DoseSummationType(0x3004, 0x000a);
Tag const GridFrameOffsetVector(0x3004, 0x000c);
Tag const DoseGridScaling(0x3004, 0x000e);
Tag const RTDoseROISequence(0x3004, 0x0010);
Tag const DoseValue(0x3004, 0x0012);
Tag const TissueHeterogeneityCorrection(0x3004, 0x0014);
Tag const DVHNormalizationPoint(0x3004, 0x0040);
Tag const DVHNormalizationDoseValue(0x3004, 0x0042);
Tag const DVHSequence(0x3004, 0x0050);
Tag const DVHDoseScaling(0x3004, 0x0052);
Tag const DVHVolumeUnits(0x3004, 0x0054);
Tag const DVHNumberOfBins(0x3004, 0x0056);
Tag const DVHData(0x3004, 0x0058);
Tag const DVHReferencedROISequence(0x3004, 0x0060);
Tag const DVHROIContributionType(0x3004, 0x0062);
Tag const DVHMinimumDose(0x3004, 0x0070);
Tag const DVHMaximumDose(0x3004, 0x0072);
Tag const DVHMeanDose(0x3004, 0x0074);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3004