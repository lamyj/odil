/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/PDU.h"

#include <cstdint>
#include <istream>

#include "odil/Exception.h"
#include "odil/odil.h"
#include "odil/dul/Object.h"

namespace odil
{

namespace dul
{

PDU
::PDU(uint8_t type)
: Object()
{
    this->_item.add("PDU-type", type);
    this->_item.add("Reserved-1", uint8_t(0));
    this->_item.add("PDU-length", uint32_t(0));
}

PDU
::PDU(uint8_t type, std::istream & stream)
: Object()
{
    this->_item.read(stream, "PDU-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("PDU-type") != type)
    {
        throw Exception("Invalid PDU type");
    }

    this->_item.read(stream, "Reserved-1", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "PDU-length", Item::Field::Type::unsigned_int_32);
}

uint8_t
PDU
::get_pdu_type() const
{
    return this->get_item().as_unsigned_int_8("PDU-type");
}

uint32_t
PDU
::get_pdu_length() const
{
    return this->get_item().as_unsigned_int_32("PDU-length");
}

void
PDU
::_set_pdu_length(uint32_t length)
{
    this->_item.as_unsigned_int_32("PDU-length") = length;
}

}

}
