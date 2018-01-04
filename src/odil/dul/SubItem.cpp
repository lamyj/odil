/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/SubItem.h"

#include <cstdint>
#include <istream>

#include "odil/Exception.h"
#include "odil/odil.h"
#include "odil/dul/Object.h"

namespace odil
{

namespace dul
{

SubItem
::SubItem(uint8_t type)
: Object()
{
    this->_item.add("Item-type", type);
    this->_item.add("Reserved-1", uint8_t(0));
    this->_item.add("Item-length", uint16_t(0));
}

SubItem
::SubItem(uint8_t type, std::istream & stream)
: Object()
{
    this->_item.read(stream, "Item-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("Item-type") != type)
    {
        throw Exception("Invalid Item type");
    }

    this->_item.read(stream, "Reserved-1", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Item-length", Item::Field::Type::unsigned_int_16);
}

uint8_t
SubItem
::get_sub_item_type() const
{
    return this->get_item().as_unsigned_int_8("Item-type");
}

uint16_t
SubItem
::get_sub_item_length() const
{
    return this->get_item().as_unsigned_int_16("Item-length");
}

void
SubItem
::_set_sub_item_length(uint16_t length)
{
    this->_item.as_unsigned_int_16("Item-length") = length;
}

}

}
