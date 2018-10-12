/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0080
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0080

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const SurfaceScanAcquisitionTypeCodeSequence(0x0080, 0x0001);
Tag const SurfaceScanModeCodeSequence(0x0080, 0x0002);
Tag const RegistrationMethodCodeSequence(0x0080, 0x0003);
Tag const ShotDurationTime(0x0080, 0x0004);
Tag const ShotOffsetTime(0x0080, 0x0005);
Tag const SurfacePointPresentationValueData(0x0080, 0x0006);
Tag const SurfacePointColorCIELabValueData(0x0080, 0x0007);
Tag const UVMappingSequence(0x0080, 0x0008);
Tag const TextureLabel(0x0080, 0x0009);
Tag const UValueData(0x0080, 0x0010);
Tag const VValueData(0x0080, 0x0011);
Tag const ReferencedTextureSequence(0x0080, 0x0012);
Tag const ReferencedSurfaceDataSequence(0x0080, 0x0013);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0080