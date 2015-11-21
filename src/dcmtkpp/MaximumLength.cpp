/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/MaximumLength.h"

#include <cstdint>
#include <istream>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/ProtocolDataUnitObjectBase.h"

namespace dcmtkpp
{

MaximumLength
::MaximumLength(uint32_t maximum_length)
{
    this->_pdu_item.add("Item-type", uint8_t(0x51));
    this->_pdu_item.add("Reserved", uint8_t(0));
    this->_pdu_item.add("Item-length", uint16_t(4));
    this->_pdu_item.add("Maximum-length-received", uint32_t(0));

    this->set_maximum_length(maximum_length);
}

MaximumLength
::MaximumLength(std::istream & stream)
{
    this->_pdu_item.read(
        stream, "Item-type", ProtocolDataUnitItem::Field::Type::unsigned_int_8);
    if(this->_pdu_item.as_unsigned_int_8("Item-type") != 0x51)
    {
        throw Exception("Invalid item type");
    }

    this->_pdu_item.read(
        stream, "Reserved", ProtocolDataUnitItem::Field::Type::unsigned_int_8);
    this->_pdu_item.read(
        stream, "Item-length",
        ProtocolDataUnitItem::Field::Type::unsigned_int_16);
    this->_pdu_item.read(
        stream, "Maximum-length-received",
        ProtocolDataUnitItem::Field::Type::unsigned_int_32);
}

uint32_t
MaximumLength
::get_maximum_length() const
{
    return this->_pdu_item.as_unsigned_int_32("Maximum-length-received");
}

void
MaximumLength
::set_maximum_length(uint32_t value)
{
    this->_pdu_item.as_unsigned_int_32("Maximum-length-received") = value;
}

}
