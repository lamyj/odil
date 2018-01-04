/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/UserIdentityAC.h"

#include <cstdint>
#include <istream>
#include <string>

#include "odil/Exception.h"
#include "odil/dul/SubItem.h"

namespace odil
{

namespace dul
{

UserIdentityAC
::UserIdentityAC(std::string const & server_response)
: SubItem(type)
{
    this->_item.add("Server-response-length", uint16_t(0));
    this->_item.add("Server-response", std::string(""));

    this->set_server_response(server_response);
}

UserIdentityAC
::UserIdentityAC(std::istream & stream)
: SubItem(type, stream)
{
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

    this->_set_sub_item_length(this->_compute_length());
}

}

}
