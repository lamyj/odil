/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3002
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3002

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const RTImageLabel(0x3002, 0x0002);
Tag const RTImageName(0x3002, 0x0003);
Tag const RTImageDescription(0x3002, 0x0004);
Tag const ReportedValuesOrigin(0x3002, 0x000a);
Tag const RTImagePlane(0x3002, 0x000c);
Tag const XRayImageReceptorTranslation(0x3002, 0x000d);
Tag const XRayImageReceptorAngle(0x3002, 0x000e);
Tag const RTImageOrientation(0x3002, 0x0010);
Tag const ImagePlanePixelSpacing(0x3002, 0x0011);
Tag const RTImagePosition(0x3002, 0x0012);
Tag const RadiationMachineName(0x3002, 0x0020);
Tag const RadiationMachineSAD(0x3002, 0x0022);
Tag const RadiationMachineSSD(0x3002, 0x0024);
Tag const RTImageSID(0x3002, 0x0026);
Tag const SourceToReferenceObjectDistance(0x3002, 0x0028);
Tag const FractionNumber(0x3002, 0x0029);
Tag const ExposureSequence(0x3002, 0x0030);
Tag const MetersetExposure(0x3002, 0x0032);
Tag const DiaphragmPosition(0x3002, 0x0034);
Tag const FluenceMapSequence(0x3002, 0x0040);
Tag const FluenceDataSource(0x3002, 0x0041);
Tag const FluenceDataScale(0x3002, 0x0042);
Tag const PrimaryFluenceModeSequence(0x3002, 0x0050);
Tag const FluenceMode(0x3002, 0x0051);
Tag const FluenceModeID(0x3002, 0x0052);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_3002