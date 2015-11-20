/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/ApplicationContext.h"

#include <cstdint>
#include <istream>
#include <string>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/ProtocolDataUnitObjectBase.h"

namespace dcmtkpp
{

ApplicationContext
::ApplicationContext(std::string const & name)
{
    this->_pdu_item.add("Item-type", uint8_t(0x10));
    this->_pdu_item.add("Reserved", uint8_t(0));
    this->_pdu_item.add("Item-length", uint16_t(0));
    this->_pdu_item.add("Application-context-name", std::string());

    this->set_name(name);
}

ApplicationContext
::ApplicationContext(std::istream & stream)
{
    this->_pdu_item.read(
        stream, "Item-type", ProtocolDataUnitItem::Field::Type::unsigned_int_8);
    if(this->_pdu_item.as_unsigned_int_8("Item-type") != 0x10)
    {
        throw Exception("Invalid item type");
    }

    this->_pdu_item.read(
        stream, "Reserved", ProtocolDataUnitItem::Field::Type::unsigned_int_8);
    this->_pdu_item.read(
        stream, "Item-length",
        ProtocolDataUnitItem::Field::Type::unsigned_int_16);
    this->_pdu_item.read(
        stream, "Application-context-name",
        ProtocolDataUnitItem::Field::Type::string,
        this->_pdu_item.as_unsigned_int_16("Item-length"));
}

std::string
ApplicationContext
::get_name() const
{
    auto const & value = this->_pdu_item.as_string("Application-context-name");
    auto const clamped =
        (value[value.size()-1]=='\0')?
            (value.substr(0, value.size()-1)):
            value;
    return clamped;
}

void
ApplicationContext
::set_name(std::string const & name)
{
    auto const padded = (name.size()%2==0)?name:(name+'\0');
    this->_pdu_item.as_unsigned_int_16("Item-length") = padded.size();
    this->_pdu_item.as_string("Application-context-name") = padded;
}

}
