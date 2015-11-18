/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _da2270e3_d393_415a_9c5c_6253152ed9da
#define _da2270e3_d393_415a_9c5c_6253152ed9da

#include <ostream>
#include "dcmtkpp/ProtocolDataUnitItem.h"

namespace dcmtkpp
{

/**
 * @brief Base class for all PDU-related high-level objects (PDU, items and
 * sub-items).
 */
class ProtocolDataUnitObjectBase
{
public:
    /// @brief Get the underlying PDU item.
    ProtocolDataUnitItem const & get_pdu_item() const;

protected:
    ProtocolDataUnitItem _pdu_item;
};

/// @brief Dump the PDU-object in its binary form.
std::ostream &
operator<<(std::ostream & stream, ProtocolDataUnitObjectBase const & object);

}

#endif // _da2270e3_d393_415a_9c5c_6253152ed9da
