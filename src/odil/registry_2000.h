/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2000
#define _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2000

#include <map>
#include <string>

#include "odil/odil.h"
#include "odil/Tag.h"

namespace odil
{

namespace registry
{
Tag const NumberOfCopies(0x2000, 0x0010);
Tag const PrinterConfigurationSequence(0x2000, 0x001e);
Tag const PrintPriority(0x2000, 0x0020);
Tag const MediumType(0x2000, 0x0030);
Tag const FilmDestination(0x2000, 0x0040);
Tag const FilmSessionLabel(0x2000, 0x0050);
Tag const MemoryAllocation(0x2000, 0x0060);
Tag const MaximumMemoryAllocation(0x2000, 0x0061);
Tag const ColorImagePrintingFlag(0x2000, 0x0062);
Tag const CollationFlag(0x2000, 0x0063);
Tag const AnnotationFlag(0x2000, 0x0065);
Tag const ImageOverlayFlag(0x2000, 0x0067);
Tag const PresentationLUTFlag(0x2000, 0x0069);
Tag const ImageBoxPresentationLUTFlag(0x2000, 0x006a);
Tag const MemoryBitDepth(0x2000, 0x00a0);
Tag const PrintingBitDepth(0x2000, 0x00a1);
Tag const MediaInstalledSequence(0x2000, 0x00a2);
Tag const OtherMediaAvailableSequence(0x2000, 0x00a4);
Tag const SupportedImageDisplayFormatsSequence(0x2000, 0x00a8);
Tag const ReferencedFilmBoxSequence(0x2000, 0x0500);
Tag const ReferencedStoredPrintSequence(0x2000, 0x0510);

}

}

#endif // _afc7b2d7_0869_4fea_9a9b_7fe6228baca9_2000