/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/MaximumLength.h"

#include <cstdint>
#include <istream>

#include "odil/Exception.h"
#include "odil/dul/Object.h"

namespace odil
{

namespace dul
{

MaximumLength
::MaximumLength(uint32_t maximum_length)
{
    this->_item.add("Item-type", uint8_t(0x51));
    this->_item.add("Reserved", uint8_t(0));
    this->_item.add("Item-length", uint16_t(4));
    this->_item.add("Maximum-length-received", uint32_t(0));

    this->set_maximum_length(maximum_length);
}

MaximumLength
::MaximumLength(std::istream & stream)
{
    this->_item.read(stream, "Item-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("Item-type") != 0x51)
    {
        throw Exception("Invalid item type");
    }

    this->_item.read(stream, "Reserved", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Item-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "Maximum-length-received", Item::Field::Type::unsigned_int_32);
}

uint32_t
MaximumLength
::get_maximum_length() const
{
    return this->_item.as_unsigned_int_32("Maximum-length-received");
}

void
MaximumLength
::set_maximum_length(uint32_t value)
{
    this->_item.as_unsigned_int_32("Maximum-length-received") = value;
}

}

}
