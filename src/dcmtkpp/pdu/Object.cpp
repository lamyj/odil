/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/pdu/Object.h"

#include <iterator>
#include <ostream>

#include "odil/Exception.h"
#include "odil/pdu/Item.h"

namespace odil
{

namespace pdu
{

Object
::~Object()
{
    // Nothing to do.
}

Item const &
Object
::get_item() const
{
    return this->_item;
}

uint32_t
Object
::_compute_length() const
{
    uint32_t length=0;

    // First 3 fields are always the same: type, reserved and length.
    auto it = this->_item.begin();
    std::advance(it, 3);
    for(; it!=this->_item.end(); ++it)
    {
        Item::Field const & field = it->second;
        length += this->_compute_length(field);
    }

    return length;
}

uint32_t
Object
::_compute_length(Item const & item) const
{
    uint32_t length=0;

    for(auto const & named_field: item)
    {
        Item::Field const & field = named_field.second;
        length += this->_compute_length(field);
    }

    return length;
}

uint32_t
Object
::_compute_length(Item::Field const & field) const
{
    uint32_t length=0;

    if(field.get_type() == Item::Field::Type::unsigned_int_8)
    {
        length += 1;
    }
    else if(field.get_type() == Item::Field::Type::unsigned_int_16)
    {
        length += 2;
    }
    else if(field.get_type() == Item::Field::Type::unsigned_int_32)
    {
        length += 4;
    }
    else if(field.get_type() == Item::Field::Type::string)
    {
        length += field.as_string().size();
    }
    else if(field.get_type() == Item::Field::Type::items)
    {
        auto const & items = field.as_items();
        for(auto const & item: items)
        {
            length += this->_compute_length(item);
        }
    }
    else
    {
        throw Exception("Unknown field type");
    }

    return length;
}

std::ostream &
operator<<(std::ostream & stream, Object const & object)
{
    stream << object.get_item();
    return stream;
}

}

}
