/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/pdu/AsynchronousOperationsWindow.h"

#include <cstdint>
#include <istream>

#include "odil/Exception.h"
#include "odil/pdu/Object.h"

namespace odil
{

namespace pdu
{

AsynchronousOperationsWindow
::AsynchronousOperationsWindow(
    uint16_t maximum_number_operations_invoked,
    uint16_t maximum_number_operations_performed)
{
    this->_item.add("Item-type", this->type);
    this->_item.add("Reserved", uint8_t(0));
    this->_item.add("Item-length", uint16_t(4));
    this->_item.add("Maximum-number-operations-invoked", uint16_t(0));
    this->_item.add("Maximum-number-operations-performed", uint16_t(0));

    this->set_maximum_number_operations_invoked(maximum_number_operations_invoked);
    this->set_maximum_number_operations_performed(maximum_number_operations_performed);
}

AsynchronousOperationsWindow
::AsynchronousOperationsWindow(std::istream & stream)
{
    this->_item.read(stream, "Item-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("Item-type") != this->type)
    {
        throw Exception("Invalid item type");
    }

    this->_item.read(stream, "Reserved", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Item-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "Maximum-number-operations-invoked", 
        Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "Maximum-number-operations-performed", 
        Item::Field::Type::unsigned_int_16);
}

uint16_t
AsynchronousOperationsWindow
::get_maximum_number_operations_invoked() const
{
    return this->_item.as_unsigned_int_16("Maximum-number-operations-invoked");
}

void
AsynchronousOperationsWindow
::set_maximum_number_operations_invoked(uint16_t value)
{
    this->_item.as_unsigned_int_16("Maximum-number-operations-invoked") = value;
}

uint16_t
AsynchronousOperationsWindow
::get_maximum_number_operations_performed() const
{
    return this->_item.as_unsigned_int_16("Maximum-number-operations-performed");
}

void
AsynchronousOperationsWindow
::set_maximum_number_operations_performed(uint16_t value)
{
    this->_item.as_unsigned_int_16("Maximum-number-operations-performed") = value;
}

}

}
