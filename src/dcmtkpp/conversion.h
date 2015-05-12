/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d5ecacb8_04ff_48b0_8026_570c9b2ae360
#define _d5ecacb8_04ff_48b0_8026_570c9b2ae360

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Element.h"
#include "dcmtkpp/Tag.h"
#include "dcmtkpp/VR.h"

namespace dcmtkpp
{

/// @brief Convert a dcmtkpp::VR to a DcmVR.
DcmVR convert(VR vr);

/// @brief Convert a DcmVR to a dcmtkpp::VR.
VR convert(DcmVR vr);

/// @brief Convert a dcmtkpp::Tag to a DcmTagKey.
DcmTagKey convert(Tag const & tag);

/// @brief Convert a DcmTagKey to a dcmtkpp::Tag.
Tag convert(DcmTagKey const & tag);

/// @brief Convert a dcmtkpp::Element to a DcmElement.
DcmElement * convert(Tag const & tag, Element const & source);

/// @brief Convert a DcmElement to a dcmtkpp::Element.
Element convert(DcmElement * source);

/// @brief Convert a dcmtkpp::DataSet to a DcmDataset.
DcmDataset convert(DataSet const & source);

/// @brief Convert a DcmDataset to a dcmtkpp::DataSet.
DataSet convert(DcmDataset const & source);

}

#endif // _d5ecacb8_04ff_48b0_8026_570c9b2ae360
