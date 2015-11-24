/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/pdu/UserInformation.h"

#include <algorithm>
#include <istream>
#include <vector>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/pdu/MaximumLength.h"
#include "dcmtkpp/pdu/Object.h"
#include "dcmtkpp/pdu/UserIdentityAC.h"
#include "dcmtkpp/pdu/UserIdentityRQ.h"

namespace dcmtkpp
{

namespace pdu
{

UserInformation
::UserInformation()
{
    this->_item.add("Item-type", uint8_t(0x50));
    this->_item.add("Reserved", uint8_t(0));
    this->_item.add("Item-length", uint16_t(4));
    this->_item.add("User-data", std::vector<Item>());
}

UserInformation
::UserInformation(std::istream & stream)
{
    this->_item.read(stream, "Item-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("Item-type") != 0x50)
    {
        throw Exception("Invalid item type");
    }

    this->_item.read(stream, "Reserved", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Item-length", Item::Field::Type::unsigned_int_16);

    this->_item.add("User-data", std::vector<Item>());

    auto const begin = stream.tellg();
    auto const item_length = this->_item.as_unsigned_int_16("Item-length");

    while(stream.tellg()-begin < item_length)
    {
        uint8_t const type = stream.peek();
        if(type == 0x51)
        {
            MaximumLength const sub_item(stream);
            this->set_maximum_length(sub_item);
        }
        else if(type == 0x58)
        {
            UserIdentityRQ const sub_item(stream);
            this->set_user_identity_rq(sub_item);
        }
        else if(type == 0x59)
        {
            UserIdentityAC const sub_item(stream);
            this->set_user_identity_ac(sub_item);
        }
        else
        {
            throw Exception("Invalid sub-item type");
        }
    }
}

bool
UserInformation
::has_maximum_length() const
{
    auto const it = this->_find_sub_item(0x51);
    return (it != this->_item.as_items("User-data").end());
}

MaximumLength
UserInformation
::get_maximum_length() const
{
    auto const it = this->_find_sub_item(0x51);
    if(it == this->_item.as_items("User-data").end())
    {
        throw Exception("No Maximum Length sub-item");
    }

    return MaximumLength(it->as_unsigned_int_32("Maximum-length-received"));
}

void
UserInformation
::set_maximum_length(MaximumLength const & item)
{
    auto it = this->_find_sub_item(0x51);
    if(it != this->_item.as_items("User-data").end())
    {
        *it = item.get_item();
    }
    else
    {
        auto & items = this->_item.as_items("User-data");
        items.insert(items.begin(), item.get_item());
    }

    this->_update_length();
}

void
UserInformation
::delete_maximum_length()
{
    auto const it = this->_find_sub_item(0x51);
    auto & items = this->_item.as_items("User-data");
    if(it == items.end())
    {
        throw Exception("No Maximum Length sub-item");
    }
    items.erase(it);

    this->_update_length();
}

bool
UserInformation
::has_user_identity_rq() const
{
    auto const it = this->_find_sub_item(0x58);
    return (it != this->_item.as_items("User-data").end());
}

UserIdentityRQ
UserInformation
::get_user_identity_rq() const
{
    auto const it = this->_find_sub_item(0x58);
    if(it == this->_item.as_items("User-data").end())
    {
        throw Exception("No User Identity (A-ASSOCIATE-RQ) sub-item");
    }

    UserIdentityRQ item;
    item.set_type(it->as_unsigned_int_8("User-Identity-Type"));
    item.set_positive_response_requested(
        it->as_unsigned_int_8("Positive-response-requested"));
    item.set_primary_field(it->as_string("Primary-field"));
    item.set_secondary_field(it->as_string("Secondary-field"));

    return item;
}

void
UserInformation
::set_user_identity_rq(UserIdentityRQ const & item)
{
    if(this->has_user_identity_ac())
    {
        throw Exception("Cannot set both User Identity sub-items");
    }

    auto it = this->_find_sub_item(0x58);
    if(it != this->_item.as_items("User-data").end())
    {
        *it = item.get_item();
    }
    else
    {
        auto & items = this->_item.as_items("User-data");
        items.insert(this->_find_sub_item(0x59), item.get_item());
    }

    this->_update_length();
}

void
UserInformation
::delete_user_identity_rq()
{
    auto const it = this->_find_sub_item(0x58);
    auto & items = this->_item.as_items("User-data");
    if(it == items.end())
    {
        throw Exception("No User Identity (A-ASSOCIATE-RQ) sub-item");
    }
    items.erase(it);

    this->_update_length();
}

bool
UserInformation
::has_user_identity_ac() const
{
    auto const it = this->_find_sub_item(0x59);
    return (it != this->_item.as_items("User-data").end());
}

UserIdentityAC
UserInformation
::get_user_identity_ac() const
{
    auto const it = this->_find_sub_item(0x59);
    if(it == this->_item.as_items("User-data").end())
    {
        throw Exception("No User Identity (A-ASSOCIATE-AC) sub-item");
    }

    UserIdentityAC item;
    item.set_server_response(it->as_string("Server-response"));

    return item;
}

void
UserInformation
::set_user_identity_ac(UserIdentityAC const & item)
{
    if(this->has_user_identity_rq())
    {
        throw Exception("Cannot set both User Identity sub-items");
    }

    auto it = this->_find_sub_item(0x59);
    if(it != this->_item.as_items("User-data").end())
    {
        *it = item.get_item();
    }
    else
    {
        auto & items = this->_item.as_items("User-data");
        items.insert(this->_find_sub_item(0x60), item.get_item());
    }

    this->_update_length();
}

void
UserInformation
::delete_user_identity_ac()
{
    auto const it = this->_find_sub_item(0x59);
    auto & items = this->_item.as_items("User-data");
    if(it == items.end())
    {
        throw Exception("No User Identity (A-ASSOCIATE-AC) sub-item");
    }
    items.erase(it);

    this->_update_length();
}

UserInformation::Items::const_iterator
UserInformation
::_find_sub_item(uint8_t type) const
{
    auto const & sub_items = this->_item.as_items("User-data");
    auto const it = std::find_if(
        sub_items.begin(), sub_items.end(),
        [type](Item const & item)
        { return item.as_unsigned_int_8("Item-type") == type; });
    return it;
}

UserInformation::Items::iterator
UserInformation
::_find_sub_item(uint8_t type)
{
    auto & sub_items = this->_item.as_items("User-data");
    auto const it = std::find_if(
        sub_items.begin(), sub_items.end(),
        [type](Item const & item)
        { return item.as_unsigned_int_8("Item-type") == type; });
    return it;
}

void
UserInformation
::_update_length()
{
    uint16_t length = 0;
    for(auto const & item: this->_item.as_items("User-data"))
    {
        length += 4+item.as_unsigned_int_16("Item-length");
    }
    this->_item.as_unsigned_int_16("Item-length") = length;
}

}

}
