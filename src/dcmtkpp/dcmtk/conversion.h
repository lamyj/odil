/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d5ecacb8_04ff_48b0_8026_570c9b2ae360
#define _d5ecacb8_04ff_48b0_8026_570c9b2ae360

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "odil/DataSet.h"
#include "odil/Element.h"
#include "odil/Tag.h"
#include "odil/VR.h"

namespace odil
{

namespace dcmtk
{

/// @brief Convert a odil::VR to a DcmVR.
DcmEVR convert(VR vr);

/// @brief Convert a DcmVR to a odil::VR.
VR convert(DcmEVR evr);

/// @brief Convert a odil::Tag to a DcmTagKey.
DcmTagKey convert(Tag const & tag);

/// @brief Convert a DcmTagKey to a odil::Tag.
Tag convert(DcmTagKey const & tag);

/// @brief Convert a odil::Element to a DcmElement.
DcmElement * convert(Tag const & tag, Element const & source);

/// @brief Low-level element converter.
template<typename TSourceType, typename TDestinationType>
void convert(
    Element const & source, DcmElement * destination,
    TSourceType const & (Element::*getter)() const);

/// @brief Convert a DcmElement to a odil::Element.
Element convert(DcmElement * source);

/// @brief Low-level element converter.
template<typename TSourceType>
void convert(
    Element const & source, DcmElement * destination,
    TSourceType const & (Element::*getter)() const);

/// @brief Low-level element converter.
void convert(Element const & source, DcmOtherByteOtherWord * destination);

/// @brief Low-level element converter.
void convert(Element const & source, DcmOtherFloat * destination);

/// @brief Low-level element converter.
template<typename TSourceType, typename TDestinationType>
void convert(
    DcmElement * source, Element & destination,
    TDestinationType & (Element::*getter)());

/// @brief Convert a odil::DataSet to a DcmDataset or a DcmItem.
DcmItem * convert(DataSet const & source, bool as_data_set=true);

/// @brief Convert a DcmDataset to a odil::DataSet.
DataSet convert(DcmItem * source);

}

}

#include "odil/dcmtk/conversion.txx"

#endif // _d5ecacb8_04ff_48b0_8026_570c9b2ae360
