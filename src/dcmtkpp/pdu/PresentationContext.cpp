/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/pdu/PresentationContext.h"

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/pdu/Object.h"
#include "dcmtkpp/pdu/Item.h"

namespace dcmtkpp
{

namespace pdu
{

PresentationContext
::PresentationContext()
{
    // Nothing to do.
}

PresentationContext
::PresentationContext(std::istream & stream)
{
    this->_item.read(stream, "Item-type", Item::Field::Type::unsigned_int_8);
    if(this->get_item_type() != 0x20 && this->get_item_type() != 0x21)
    {
        throw Exception("Invalid item type");
    }

    this->_item.read(stream, "Reserved-1", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Item-length", Item::Field::Type::unsigned_int_16);
    auto const item_length = this->_item.as_unsigned_int_16("Item-length");

    auto const begin = stream.tellg();

    this->_item.read(
        stream, "Presentation-context-id", Item::Field::Type::unsigned_int_8);

    this->_item.read(stream, "Reserved-2", Item::Field::Type::unsigned_int_8);
    this->_item.read(
        stream, "Result/Reason", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "Reserved-3", Item::Field::Type::unsigned_int_8);

    std::vector<Item> sub_items;
    while(stream.tellg()-begin < item_length)
    {
        Item item;
        item.read(stream, "Item-type", Item::Field::Type::unsigned_int_8);

        std::string type;

        auto const & item_type = item.as_unsigned_int_8("Item-type");
        if(item_type == 0x30)
        {
            type = "Abstract";
        }
        else if(item_type == 0x40)
        {
            type = "Transfer";
        }
        else
        {
            throw Exception("Invalid item");
        }

        item.read(stream, "Reserved", Item::Field::Type::unsigned_int_8);
        item.read(stream, "Item-length", Item::Field::Type::unsigned_int_16);
        item.read(
            stream, type+"-syntax-name", Item::Field::Type::string,
            item.as_unsigned_int_16("Item-length"));

        sub_items.push_back(item);
    }

    this->_item.add("Abstract/Transfer Syntax Sub-Items", sub_items);
}

uint8_t
PresentationContext
::get_item_type() const
{
    return this->_item.as_unsigned_int_8("Item-type");
}

uint8_t
PresentationContext
::get_id() const
{
    return this->_item.as_unsigned_int_8("Presentation-context-id");
}

void
PresentationContext
::set_id(u_int8_t id)
{
    this->_item.as_unsigned_int_8("Presentation-context-id") = id;
}

Item
PresentationContext
::_make_string_item(
    std::string const & type, std::string const & value)
{
    Item item;

    uint8_t item_type;
    if(type == "Abstract")
    {
        item_type = 0x30;
    }
    else if(type == "Transfer")
    {
        item_type = 0x40;
    }
    else
    {
        throw Exception("Unknown sub-item type");
    }
    item.add("Item-type", item_type);

    item.add("Reserved", uint8_t(0));

    item.add("Item-length", uint16_t(value.size()));
    item.add(type+"-syntax-name", value);

    return item;
}

void
PresentationContext
::_add_fields()
{
    this->_item.add("Item-type", uint8_t(0x0));
    this->_item.add("Reserved-1", uint8_t(0));
    this->_item.add("Item-length", uint16_t(0));
    this->_item.add("Presentation-context-id", uint8_t(0));
    this->_item.add("Reserved-2", uint8_t(0));
    this->_item.add("Result/Reason", uint8_t(0));
    this->_item.add("Reserved-3", uint8_t(0));

    this->_item.add("Abstract/Transfer Syntax Sub-Items", std::vector<Item>());
}

std::vector<std::string>
PresentationContext
::_get_syntaxes(std::string const & type) const
{
    auto const & sub_items = this->_item.as_items(
        "Abstract/Transfer Syntax Sub-Items");

    std::vector<std::string> result;
    std::for_each(
        sub_items.begin(), sub_items.end(),
        [&type, &result](Item const & item)
        {
            uint8_t const item_type = (type=="Abstract")?0x30:0x40;
            if(item.as_unsigned_int_8("Item-type") == item_type)
            {
                auto const value = item.as_string(type+"-syntax-name");
                result.push_back(value);
            }
        });

    return result;
}

void
PresentationContext
::_set_syntaxes(
    std::string const & type, std::vector<std::string> const & syntaxes)
{
    std::string const other_type = (type=="Abstract")?"Transfer":"Abstract";
    auto const other_syntaxes = this->_get_syntaxes(other_type);

    auto & sub_items = this->_item.as_items(
        "Abstract/Transfer Syntax Sub-Items");

    sub_items.resize(other_syntaxes.size()+syntaxes.size());

    auto const & abstract_syntaxes = (type=="Abstract")?syntaxes:other_syntaxes;
    auto const & transfer_syntaxes = (type=="Abstract")?other_syntaxes:syntaxes;

    std::transform(
        abstract_syntaxes.begin(), abstract_syntaxes.end(),
        sub_items.begin(),
        [this](std::string const & name)
        { return PresentationContext::_make_string_item("Abstract", name); });

    std::transform(
        transfer_syntaxes.begin(), transfer_syntaxes.end(),
        sub_items.begin()+abstract_syntaxes.size(),
        [this](std::string const & name)
        { return PresentationContext::_make_string_item("Transfer", name); });

    this->_item.as_unsigned_int_16("Item-length") = this->_compute_length();
}

}

}
