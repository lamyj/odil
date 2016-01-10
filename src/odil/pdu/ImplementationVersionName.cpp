/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/pdu/ImplementationVersionName.h"

#include <cstdint>
#include <istream>
#include <string>

#include "odil/Exception.h"
#include "odil/pdu/Object.h"

namespace odil
{

namespace pdu
{

ImplementationVersionName
::ImplementationVersionName(std::string const & implementation_version_name)
{
    this->_item.add("Item-type", this->type);
    this->_item.add("Reserved", uint8_t(0));
    this->_item.add("Item-length", uint16_t(0));
    this->_item.add("Implementation-version-name", std::string());

    this->set_implementation_version_name(implementation_version_name);
}

ImplementationVersionName
::ImplementationVersionName(std::istream & stream)
{
    this->_item.read(stream, "Item-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("Item-type") != this->type)
    {
        throw Exception("Invalid item type");
    }

    this->_item.read(stream, "Reserved", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Item-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "Implementation-version-name", Item::Field::Type::string,
        this->_item.as_unsigned_int_16("Item-length"));
}

std::string
ImplementationVersionName
::get_implementation_version_name() const
{
    return this->_item.as_string("Implementation-version-name");
}

void
ImplementationVersionName
::set_implementation_version_name(std::string const & value)
{
    if(value.empty() || value.size()>16)
    {
        throw Exception("Invalid implementation version name");
    }
    this->_item.as_string("Implementation-version-name") = value;
    this->_item.as_unsigned_int_16("Item-length") = this->_compute_length();
}

}

}
