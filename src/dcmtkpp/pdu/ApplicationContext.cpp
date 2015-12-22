/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/pdu/ApplicationContext.h"

#include <cstdint>
#include <istream>
#include <string>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/pdu/Object.h"

namespace dcmtkpp
{

namespace pdu
{

ApplicationContext
::ApplicationContext(std::string const & name)
{
    this->_item.add("Item-type", uint8_t(0x10));
    this->_item.add("Reserved", uint8_t(0));
    this->_item.add("Item-length", uint16_t(0));
    this->_item.add("Application-context-name", std::string());

    this->set_name(name);
}

ApplicationContext
::ApplicationContext(std::istream & stream)
{
    this->_item.read(stream, "Item-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("Item-type") != 0x10)
    {
        throw Exception("Invalid item type");
    }

    this->_item.read(stream, "Reserved", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Item-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "Application-context-name", Item::Field::Type::string,
        this->_item.as_unsigned_int_16("Item-length"));
}

std::string
ApplicationContext
::get_name() const
{
    // Application Context is not padded: PS 3.8 F.1
    return this->_item.as_string("Application-context-name");
}

void
ApplicationContext
::set_name(std::string const & name)
{
    // Application Context is not padded: PS 3.8 F.1
    this->_item.as_string("Application-context-name") = name;
    this->_item.as_unsigned_int_16("Item-length") = this->_compute_length();
}

}

}
