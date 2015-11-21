/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/UserIdentityAC.h"

#include <cstdint>
#include <istream>
#include <string>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/ProtocolDataUnitObjectBase.h"

namespace dcmtkpp
{

UserIdentityAC
::UserIdentityAC(std::string const & server_response)
{
    this->_pdu_item.add("Item-type", uint8_t(0x59));
    this->_pdu_item.add("Reserved", uint8_t(0));
    this->_pdu_item.add("Item-length", uint16_t(0));

    this->_pdu_item.add("Server-response-length", uint16_t(0));
    this->_pdu_item.add("Server-response", std::string(""));

    this->set_server_response(server_response);
}

UserIdentityAC
::UserIdentityAC(std::istream & stream)
{
    this->_pdu_item.read(
        stream, "Item-type", ProtocolDataUnitItem::Field::Type::unsigned_int_8);
    if(this->_pdu_item.as_unsigned_int_8("Item-type") != 0x59)
    {
        throw Exception("Invalid item type");
    }

    this->_pdu_item.read(
        stream, "Reserved", ProtocolDataUnitItem::Field::Type::unsigned_int_8);
    this->_pdu_item.read(
        stream, "Item-length",
        ProtocolDataUnitItem::Field::Type::unsigned_int_16);
    this->_pdu_item.read(
        stream, "Server-response-length",
        ProtocolDataUnitItem::Field::Type::unsigned_int_16);
    this->_pdu_item.read(
        stream, "Server-response", ProtocolDataUnitItem::Field::Type::string,
        this->_pdu_item.as_unsigned_int_16("Server-response-length"));
}

std::string const &
UserIdentityAC
::get_server_response() const
{
    return this->_pdu_item.as_string("Server-response");
}

void
UserIdentityAC
::set_server_response(std::string const & value)
{
    this->_pdu_item.as_unsigned_int_16("Server-response-length") = value.size();
    this->_pdu_item.as_string("Server-response") = value;

    this->_pdu_item.as_unsigned_int_16("Item-length") =
        2+this->get_server_response().size();
}

}
