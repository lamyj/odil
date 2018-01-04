/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/pdu/AAbort.h"

#include <cstdint>
#include <istream>

#include "odil/Exception.h"
#include "odil/pdu/Object.h"

namespace odil
{

namespace pdu
{

AAbort
::AAbort(unsigned char source, unsigned char reason)
{
    this->_item.add("PDU-type", uint8_t(0x07));
    this->_item.add("Reserved-1", uint8_t(0));
    this->_item.add("PDU-length", uint32_t(4));
    this->_item.add("Reserved-2", uint8_t(0));
    this->_item.add("Reserved-3", uint8_t(0));
    this->_item.add("Source", uint8_t(0));
    this->_item.add("Reason", uint8_t(0));

    this->set_source(source);
    this->set_reason(reason);
}

AAbort
::AAbort(std::istream & stream)
{
    this->_item.read(stream, "PDU-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("PDU-type") != 0x07)
    {
        throw Exception("Invalid PDU type");
    }

    this->_item.read(stream, "Reserved-1", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "PDU-length", Item::Field::Type::unsigned_int_32);
    this->_item.read(stream, "Reserved-2", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Reserved-3", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Source", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Reason", Item::Field::Type::unsigned_int_8);
}

unsigned char
AAbort
::get_source() const
{
    return this->_item.as_unsigned_int_8("Source");
}

void
AAbort
::set_source(unsigned char source)
{
    if(source > 2)
    {
        throw Exception("Unknown source");
    }
    this->_item.as_unsigned_int_8("Source") = source;
}

unsigned char
AAbort
::get_reason() const
{
    return this->_item.as_unsigned_int_8("Reason");
}

void
AAbort
::set_reason(unsigned char reason)
{
    if(reason > 6)
    {
        throw Exception("Unknown reason");
    }
    this->_item.as_unsigned_int_8("Reason") = reason;
}

}

}
