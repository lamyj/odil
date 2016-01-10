/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/pdu/AReleaseRQ.h"

#include <cstdint>
#include <istream>

#include "odil/Exception.h"
#include "odil/pdu/Object.h"

namespace odil
{

namespace pdu
{

AReleaseRQ
::AReleaseRQ()
{
    this->_item.add("PDU-type", uint8_t(0x05));
    this->_item.add("Reserved-1", uint8_t(0));
    this->_item.add("PDU-length", uint32_t(4));
    this->_item.add("Reserved-2", uint32_t(0));
}

AReleaseRQ
::AReleaseRQ(std::istream & stream)
{
    this->_item.read(stream, "PDU-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("PDU-type") != 0x05)
    {
        throw Exception("Invalid PDU type");
    }

    this->_item.read(stream, "Reserved-1", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "PDU-length", Item::Field::Type::unsigned_int_32);
    this->_item.read(stream, "Reserved-2", Item::Field::Type::unsigned_int_32);
}

}

}
