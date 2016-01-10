/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/pdu/ImplementationClassUID.h"

#include <cstdint>
#include <istream>
#include <string>

#include "odil/Exception.h"
#include "odil/pdu/Object.h"

namespace odil
{

namespace pdu
{

ImplementationClassUID
::ImplementationClassUID(std::string const & implementation_class_uid)
{
    this->_item.add("Item-type", this->type);
    this->_item.add("Reserved", uint8_t(0));
    this->_item.add("Item-length", uint16_t(0));
    this->_item.add("Implementation-class-uid", std::string());

    this->set_implementation_class_uid(implementation_class_uid);
}

ImplementationClassUID
::ImplementationClassUID(std::istream & stream)
{
    this->_item.read(stream, "Item-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("Item-type") != this->type)
    {
        throw Exception("Invalid item type");
    }

    this->_item.read(stream, "Reserved", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Item-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "Implementation-class-uid", Item::Field::Type::string,
        this->_item.as_unsigned_int_16("Item-length"));
}

std::string
ImplementationClassUID
::get_implementation_class_uid() const
{
    return this->_item.as_string("Implementation-class-uid");
}

void
ImplementationClassUID
::set_implementation_class_uid(std::string const & value)
{
    this->_item.as_string("Implementation-class-uid") = value;
    this->_item.as_unsigned_int_16("Item-length") = this->_compute_length();
}

}

}
