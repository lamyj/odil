/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/AReleaseRQ.h"

#include <cstdint>
#include <istream>

#include "odil/Exception.h"
#include "odil/dul/Object.h"

namespace odil
{

namespace dul
{

AReleaseRQ
::AReleaseRQ()
: PDU(type)
{
    this->_set_pdu_length(4);

    this->_item.add("Reserved-2", uint32_t(0));
}

AReleaseRQ
::AReleaseRQ(std::istream & stream)
: PDU(type, stream)
{
    this->_item.read(stream, "Reserved-2", Item::Field::Type::unsigned_int_32);
}

}

}
