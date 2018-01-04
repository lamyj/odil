/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/pdu/UserIdentityAC.h"

#include <cstdint>
#include <istream>
#include <string>

#include "odil/Exception.h"
#include "odil/pdu/Object.h"

namespace odil
{

namespace pdu
{

UserIdentityAC
::UserIdentityAC(std::string const & server_response)
{
    this->_item.add("Item-type", uint8_t(0x59));
    this->_item.add("Reserved", uint8_t(0));
    this->_item.add("Item-length", uint16_t(0));

    this->_item.add("Server-response-length", uint16_t(0));
    this->_item.add("Server-response", std::string(""));

    this->set_server_response(server_response);
}

UserIdentityAC
::UserIdentityAC(std::istream & stream)
{
    this->_item.read(stream, "Item-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("Item-type") != 0x59)
    {
        throw Exception("Invalid item type");
    }

    this->_item.read(stream, "Reserved", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Item-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "Server-response-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "Server-response", Item::Field::Type::string,
        this->_item.as_unsigned_int_16("Server-response-length"));
}

std::string const &
UserIdentityAC
::get_server_response() const
{
    return this->_item.as_string("Server-response");
}

void
UserIdentityAC
::set_server_response(std::string const & value)
{
    this->_item.as_unsigned_int_16("Server-response-length") = value.size();
    this->_item.as_string("Server-response") = value;

    this->_item.as_unsigned_int_16("Item-length") =
        2+this->get_server_response().size();
}

}

}
