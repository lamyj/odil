/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0062
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0062

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const SegmentationType(0x0062, 0x0001);
Tag const SegmentSequence(0x0062, 0x0002);
Tag const SegmentedPropertyCategoryCodeSequence(0x0062, 0x0003);
Tag const SegmentNumber(0x0062, 0x0004);
Tag const SegmentLabel(0x0062, 0x0005);
Tag const SegmentDescription(0x0062, 0x0006);
Tag const SegmentationAlgorithmIdentificationSequence(0x0062, 0x0007);
Tag const SegmentAlgorithmType(0x0062, 0x0008);
Tag const SegmentAlgorithmName(0x0062, 0x0009);
Tag const SegmentIdentificationSequence(0x0062, 0x000a);
Tag const ReferencedSegmentNumber(0x0062, 0x000b);
Tag const RecommendedDisplayGrayscaleValue(0x0062, 0x000c);
Tag const RecommendedDisplayCIELabValue(0x0062, 0x000d);
Tag const MaximumFractionalValue(0x0062, 0x000e);
Tag const SegmentedPropertyTypeCodeSequence(0x0062, 0x000f);
Tag const SegmentationFractionalType(0x0062, 0x0010);
Tag const SegmentedPropertyTypeModifierCodeSequence(0x0062, 0x0011);
Tag const UsedSegmentsSequence(0x0062, 0x0012);
Tag const TrackingID(0x0062, 0x0020);
Tag const TrackingUID(0x0062, 0x0021);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0062