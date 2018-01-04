/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/UserIdentityRQ.h"

#include <cstdint>
#include <istream>
#include <string>

#include "odil/Exception.h"
#include "odil/dul/SubItem.h"

namespace odil
{

namespace dul
{

UserIdentityRQ
::UserIdentityRQ()
: SubItem(type)
{
    this->_item.add("User-Identity-Type", uint8_t(1));
    this->_item.add("Positive-response-requested", uint8_t(0));
    this->_item.add("Primary-field-length", uint16_t(0));
    this->_item.add("Primary-field", std::string(""));
    this->_item.add("Secondary-field-length", uint16_t(0));
    this->_item.add("Secondary-field", std::string(""));

    this->_item.as_unsigned_int_16("Item-length") = this->_compute_length();
}

UserIdentityRQ
::UserIdentityRQ(std::istream & stream)
: SubItem(type, stream)
{
    this->_item.read(
        stream, "User-Identity-Type", Item::Field::Type::unsigned_int_8);
    this->_item.read(
        stream, "Positive-response-requested",
        Item::Field::Type::unsigned_int_8);
    this->_item.read(
        stream, "Primary-field-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "Primary-field", Item::Field::Type::string,
        this->_item.as_unsigned_int_16("Primary-field-length"));
    this->_item.read(
        stream, "Secondary-field-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "Secondary-field", Item::Field::Type::string,
        this->_item.as_unsigned_int_16("Secondary-field-length"));
}

uint8_t
UserIdentityRQ
::get_type() const
{
    return this->_item.as_unsigned_int_8("User-Identity-Type");
}

void
UserIdentityRQ
::set_type(uint8_t type)
{
    this->_item.as_unsigned_int_8("User-Identity-Type") = type;
}

bool
UserIdentityRQ
::get_positive_response_requested() const
{
    return
        (this->_item.as_unsigned_int_8("Positive-response-requested") != 0);
}

void
UserIdentityRQ
::set_positive_response_requested(bool value)
{
    this->_item.as_unsigned_int_8("Positive-response-requested") =
        value?1:0;
}

std::string const &
UserIdentityRQ
::get_primary_field() const
{
    return this->_item.as_string("Primary-field");
}

void
UserIdentityRQ
::set_primary_field(std::string const & value)
{
    this->_item.as_unsigned_int_16("Primary-field-length") = value.size();
    this->_item.as_string("Primary-field") = value;
    this->_set_sub_item_length(this->_compute_length());
}

std::string const &
UserIdentityRQ
::get_secondary_field() const
{
    return this->_item.as_string("Secondary-field");
}

void
UserIdentityRQ
::set_secondary_field(std::string const & value)
{
    this->_item.as_unsigned_int_16("Secondary-field-length") = value.size();
    this->_item.as_string("Secondary-field") = value;
    this->_set_sub_item_length(this->_compute_length());
}

void
UserIdentityRQ
::set_username(std::string const & username)
{
    this->set_type(1);
    this->set_primary_field(username);
    this->set_secondary_field("");
}

void
UserIdentityRQ
::set_username_and_passcode(
    std::string const & username, std::string const & passcode)
{
    this->set_type(2);
    this->set_primary_field(username);
    this->set_secondary_field(passcode);
}

void
UserIdentityRQ
::set_kerberos_service_ticket(std::string const & ticket)
{
    this->set_type(3);
    this->set_primary_field(ticket);
    this->set_secondary_field("");
}

void
UserIdentityRQ
::set_saml_assertion(std::string const & assertion)
{
    this->set_type(4);
    this->set_primary_field(assertion);
    this->set_secondary_field("");
}

}

}
