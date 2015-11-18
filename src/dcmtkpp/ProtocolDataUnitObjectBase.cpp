/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/ProtocolDataUnitObjectBase.h"

#include <ostream>
#include "dcmtkpp/ProtocolDataUnitItem.h"

namespace dcmtkpp
{

ProtocolDataUnitItem const &
ProtocolDataUnitObjectBase
::get_pdu_item() const
{
    return this->_pdu_item;
}

std::ostream &
operator<<(std::ostream & stream, ProtocolDataUnitObjectBase const & object)
{
    stream << object.get_pdu_item();
    return stream;
}

}
