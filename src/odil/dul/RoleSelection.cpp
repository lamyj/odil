/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/RoleSelection.h"

#include <cstdint>
#include <istream>
#include <string>

#include "odil/Exception.h"
#include "odil/dul/Item.h"
#include "odil/dul/Object.h"

namespace odil
{

namespace dul
{

RoleSelection
::RoleSelection(
    std::string const & sop_class_uid,
    bool scu_role_support, bool scp_role_support)
{
    this->_item.add("Item-type", this->type);
    this->_item.add("Reserved", uint8_t(0));
    this->_item.add("Item-length", uint16_t(0));
    this->_item.add("UID-length", uint16_t(0));
    this->_item.add("SOP-class-uid", std::string());
    this->_item.add("SCU-role", uint8_t(0));
    this->_item.add("SCP-role", uint8_t(0));

    this->set_sop_class_uid(sop_class_uid);
    this->set_scu_role_support(scu_role_support);
    this->set_scp_role_support(scp_role_support);
}

RoleSelection
::RoleSelection(std::istream & stream)
{
    this->_item.read(stream, "Item-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("Item-type") != this->type)
    {
        throw Exception("Invalid item type");
    }

    this->_item.read(stream, "Reserved", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Item-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(stream, "UID-length", Item::Field::Type::unsigned_int_16);
    this->_item.read(
        stream, "SOP-class-uid", Item::Field::Type::string,
        this->_item.as_unsigned_int_16("UID-length"));
    this->_item.read(stream, "SCU-role", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "SCP-role", Item::Field::Type::unsigned_int_8);
}

std::string const &
RoleSelection
::get_sop_class_uid() const
{
    return this->_item.as_string("SOP-class-uid");
}

void
RoleSelection
::set_sop_class_uid(std::string const & value)
{
    this->_item.as_string("SOP-class-uid") = value;
    this->_item.as_unsigned_int_16("UID-length") = value.size();
    this->_item.as_unsigned_int_16("Item-length") = this->_compute_length();
}

bool
RoleSelection
::get_scu_role_support() const
{
    return (this->_item.as_unsigned_int_8("SCU-role")!=0);
}

void
RoleSelection
::set_scu_role_support(bool value)
{
    this->_item.as_unsigned_int_8("SCU-role") = value?1:0;
}

bool
RoleSelection
::get_scp_role_support() const
{
    return (this->_item.as_unsigned_int_8("SCP-role")!=0);
}

void
RoleSelection
::set_scp_role_support(bool value)
{
    this->_item.as_unsigned_int_8("SCP-role") = value?1:0;
}

}

}
