/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/PresentationContext.h"

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/ProtocolDataUnitObjectBase.h"
#include "dcmtkpp/ProtocolDataUnitItem.h"

namespace dcmtkpp
{

PresentationContext
::PresentationContext(
    std::string const & abstract_syntax,
    std::vector<std::string> const & transfer_syntaxes)
{
    this->_add_fields();

    this->_pdu_item.as_unsigned_int_8("Item-type") = 0x20;
    this->set_abstract_syntax(abstract_syntax);
    this->set_transfer_syntaxes(transfer_syntaxes);
}

PresentationContext
::PresentationContext(std::string const & transfer_syntax)
{
    this->_add_fields();

    this->_pdu_item.as_unsigned_int_8("Item-type") = 0x21;
    this->set_transfer_syntax(transfer_syntax);
}

PresentationContext
::PresentationContext(std::istream & stream)
{
    this->_pdu_item.read(
        stream, "Item-type", ProtocolDataUnitItem::Field::Type::unsigned_int_8);
    if(this->get_item_type() != 0x20 && this->get_item_type() != 0x21)
    {
        throw Exception("Invalid item type");
    }

    this->_pdu_item.read(
        stream, "Reserved-1",
        ProtocolDataUnitItem::Field::Type::unsigned_int_8);
    this->_pdu_item.read(
        stream, "Item-length",
        ProtocolDataUnitItem::Field::Type::unsigned_int_16);
    auto const item_length = this->_pdu_item.as_unsigned_int_16("Item-length");

    auto const begin = stream.tellg();

    this->_pdu_item.read(
        stream, "Presentation-context-id",
        ProtocolDataUnitItem::Field::Type::unsigned_int_8);

    this->_pdu_item.read(
        stream, "Reserved-2",
        ProtocolDataUnitItem::Field::Type::unsigned_int_8);
    this->_pdu_item.read(
        stream, "Result/Reason",
        ProtocolDataUnitItem::Field::Type::unsigned_int_8);
    this->_pdu_item.read(
        stream, "Reserved-3",
        ProtocolDataUnitItem::Field::Type::unsigned_int_8);

    std::vector<ProtocolDataUnitItem> sub_items;
    while(stream.tellg()-begin < item_length)
    {
        ProtocolDataUnitItem item;
        item.read(
            stream, "Item-type",
            ProtocolDataUnitItem::Field::Type::unsigned_int_8);

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

        item.read(
            stream, "Reserved",
            ProtocolDataUnitItem::Field::Type::unsigned_int_8);
        item.read(
            stream, "Item-length",
            ProtocolDataUnitItem::Field::Type::unsigned_int_16);
        item.read(
            stream, type+"-syntax-name",
            ProtocolDataUnitItem::Field::Type::string,
            item.as_unsigned_int_16("Item-length"));

        sub_items.push_back(item);
    }

    this->_pdu_item.add("Abstract/Transfer Syntax Sub-Items", sub_items);
}

uint8_t
PresentationContext
::get_item_type() const
{
    return this->_pdu_item.as_unsigned_int_8("Item-type");
}

uint8_t
PresentationContext
::get_id() const
{
    return this->_pdu_item.as_unsigned_int_8("Presentation-context-id");
}

void
PresentationContext
::set_id(u_int8_t id)
{
    this->_pdu_item.as_unsigned_int_8("Presentation-context-id") = id;
}

uint8_t
PresentationContext
::get_result_reason() const
{
    if(this->_pdu_item.as_unsigned_int_8("Item-type") != 0x21)
    {
        throw dcmtkpp::Exception(
            "Only valid for A-ASSOCIATE-AC Presentation context");
    }
    return this->_pdu_item.as_unsigned_int_8("Result/Reason");
}

void
PresentationContext
::set_result_reason(u_int8_t result_reason)
{
    if(this->_pdu_item.as_unsigned_int_8("Item-type") != 0x21)
    {
        throw dcmtkpp::Exception(
            "Only valid for A-ASSOCIATE-AC Presentation context");
    }
    this->_pdu_item.as_unsigned_int_8("Result/Reason") = result_reason;
}

std::string
PresentationContext
::get_abstract_syntax() const
{
    if(this->_pdu_item.as_unsigned_int_8("Item-type") != 0x20)
    {
        throw dcmtkpp::Exception(
            "Only valid for A-ASSOCIATE-RQ Presentation context");
    }

    auto const & syntaxes = this->_get_syntaxes("Abstract");
    if(syntaxes.empty())
    {
        throw Exception("No Abstract Syntax sub-item");
    }
    else if(syntaxes.size() > 1)
    {
        throw Exception("Several Abstract Syntax sub-items");
    }

    return syntaxes[0];
}

void
PresentationContext
::set_abstract_syntax(std::string const & abstract_syntax)
{
    if(this->_pdu_item.as_unsigned_int_8("Item-type") != 0x20)
    {
        throw dcmtkpp::Exception(
            "Only valid for A-ASSOCIATE-RQ Presentation context");
    }

    this->_set_syntaxes("Abstract", {abstract_syntax});
}

std::vector<std::string>
PresentationContext
::get_transfer_syntaxes() const
{
    if(this->_pdu_item.as_unsigned_int_8("Item-type") != 0x20)
    {
        throw dcmtkpp::Exception(
            "Only valid for A-ASSOCIATE-RQ Presentation context");
    }

    return this->_get_syntaxes("Transfer");
}

void
PresentationContext
::set_transfer_syntaxes(
    std::vector<std::string> const & transfer_syntaxes)
{
    if(this->_pdu_item.as_unsigned_int_8("Item-type") != 0x20)
    {
        throw dcmtkpp::Exception(
            "Only valid for A-ASSOCIATE-RQ Presentation context");
    }

    this->_set_syntaxes("Transfer", transfer_syntaxes);
}

std::string
PresentationContext
::get_transfer_syntax() const
{
    if(this->_pdu_item.as_unsigned_int_8("Item-type") != 0x21)
    {
        throw dcmtkpp::Exception(
            "Only valid for A-ASSOCIATE-AC Presentation context");
    }

    auto const & syntaxes = this->_get_syntaxes("Transfer");
    if(syntaxes.empty())
    {
        throw Exception("No Transfer Syntax sub-item");
    }
    else if(syntaxes.size() > 1)
    {
        throw Exception("Several Transfer Syntax sub-items");
    }

    return syntaxes[0];
}

void
PresentationContext
::set_transfer_syntax(std::string const & transfer_syntax)
{
    if(this->_pdu_item.as_unsigned_int_8("Item-type") != 0x21)
    {
        throw dcmtkpp::Exception(
            "Only valid for A-ASSOCIATE-AC Presentation context");
    }

    this->_set_syntaxes("Transfer", {transfer_syntax});
}

ProtocolDataUnitItem
PresentationContext
::_make_string_item(
    std::string const & type, std::string const & value)
{
    ProtocolDataUnitItem item;

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
    this->_pdu_item.add("Item-type", uint8_t(0x0));
    this->_pdu_item.add("Reserved-1", uint8_t(0));
    this->_pdu_item.add("Item-length", uint16_t(0));
    this->_pdu_item.add("Presentation-context-id", uint8_t(0));
    this->_pdu_item.add("Reserved-2", uint8_t(0));
    this->_pdu_item.add("Result/Reason", uint8_t(0));
    this->_pdu_item.add("Reserved-3", uint8_t(0));

    this->_pdu_item.add(
        "Abstract/Transfer Syntax Sub-Items",
        std::vector<ProtocolDataUnitItem>());
}

std::vector<std::string>
PresentationContext
::_get_syntaxes(std::string const & type) const
{
    auto const & sub_items = this->_pdu_item.as_items(
        "Abstract/Transfer Syntax Sub-Items");

    std::vector<std::string> result;
    std::for_each(
        sub_items.begin(), sub_items.end(),
        [&type, &result](ProtocolDataUnitItem const & item)
        {
            uint8_t const item_type = (type=="Abstract")?0x30:0x40;
            if(item.as_unsigned_int_8("Item-type") == item_type)
            {
                auto const value = item.as_string(type+"-syntax-name");
                auto const clamped =
                    (value[value.size()-1]=='\0')?
                        (value.substr(0, value.size()-1)):
                        value;
                result.push_back(clamped);
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

    auto & sub_items = this->_pdu_item.as_items(
        "Abstract/Transfer Syntax Sub-Items");

    sub_items.resize(other_syntaxes.size()+syntaxes.size());

    auto const & abstract_syntaxes = (type=="Abstract")?syntaxes:other_syntaxes;
    auto const & transfer_syntaxes = (type=="Abstract")?other_syntaxes:syntaxes;

    auto make_item = [this] (std::string const & type, std::string const & name) {
        auto const padded = (name.size()%2==0)?name:(name+'\0');
        return PresentationContext::_make_string_item(type, padded);
    };

    std::transform(
        abstract_syntaxes.begin(), abstract_syntaxes.end(),
        sub_items.begin(),
        [&make_item](std::string const & name)
        { return make_item("Abstract", name); });

    std::transform(
        transfer_syntaxes.begin(), transfer_syntaxes.end(),
        sub_items.begin()+abstract_syntaxes.size(),
        [&make_item](std::string const & name)
        { return make_item("Transfer", name); });

    this->_update_size();
}

void
PresentationContext
::_update_size()
{
    uint16_t size = 4;
    for(auto const & item: this->_pdu_item.as_items("Abstract/Transfer Syntax Sub-Items"))
    {
        size += 4 + item.as_unsigned_int_16("Item-length");
    }
    this->_pdu_item.as_unsigned_int_16("Item-length") = size;
}

}
