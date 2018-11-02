/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2010
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2010

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const ImageDisplayFormat(0x2010, 0x0010);
Tag const AnnotationDisplayFormatID(0x2010, 0x0030);
Tag const FilmOrientation(0x2010, 0x0040);
Tag const FilmSizeID(0x2010, 0x0050);
Tag const PrinterResolutionID(0x2010, 0x0052);
Tag const DefaultPrinterResolutionID(0x2010, 0x0054);
Tag const MagnificationType(0x2010, 0x0060);
Tag const SmoothingType(0x2010, 0x0080);
Tag const DefaultMagnificationType(0x2010, 0x00a6);
Tag const OtherMagnificationTypesAvailable(0x2010, 0x00a7);
Tag const DefaultSmoothingType(0x2010, 0x00a8);
Tag const OtherSmoothingTypesAvailable(0x2010, 0x00a9);
Tag const BorderDensity(0x2010, 0x0100);
Tag const EmptyImageDensity(0x2010, 0x0110);
Tag const MinDensity(0x2010, 0x0120);
Tag const MaxDensity(0x2010, 0x0130);
Tag const Trim(0x2010, 0x0140);
Tag const ConfigurationInformation(0x2010, 0x0150);
Tag const ConfigurationInformationDescription(0x2010, 0x0152);
Tag const MaximumCollatedFilms(0x2010, 0x0154);
Tag const Illumination(0x2010, 0x015e);
Tag const ReflectedAmbientLight(0x2010, 0x0160);
Tag const PrinterPixelSpacing(0x2010, 0x0376);
Tag const ReferencedFilmSessionSequence(0x2010, 0x0500);
Tag const ReferencedImageBoxSequence(0x2010, 0x0510);
Tag const ReferencedBasicAnnotationBoxSequence(0x2010, 0x0520);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2010