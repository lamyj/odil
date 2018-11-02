/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0064
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0064

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const DeformableRegistrationSequence(0x0064, 0x0002);
Tag const SourceFrameOfReferenceUID(0x0064, 0x0003);
Tag const DeformableRegistrationGridSequence(0x0064, 0x0005);
Tag const GridDimensions(0x0064, 0x0007);
Tag const GridResolution(0x0064, 0x0008);
Tag const VectorGridData(0x0064, 0x0009);
Tag const PreDeformationMatrixRegistrationSequence(0x0064, 0x000f);
Tag const PostDeformationMatrixRegistrationSequence(0x0064, 0x0010);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_0064