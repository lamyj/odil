/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/PresentationContext.h"

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

    auto const & value = this->_pdu_item.as_items(
        "Abstract/Transfer Syntax Sub-Items")[0].as_string(
            "Abstract-syntax-name");

    return (value[value.size()-1]=='\0')?(value.substr(0, value.size()-1)):value;
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

    auto const padded =
        (abstract_syntax.size()%2==0)?abstract_syntax:(abstract_syntax+'\0');
    auto const item = PresentationContext::_make_string_item(
        "Abstract-syntax", padded);
    this->_pdu_item.as_items("Abstract/Transfer Syntax Sub-Items")[0] = item;

    this->_update_size();
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

    auto const & items = this->_pdu_item.as_items(
        "Abstract/Transfer Syntax Sub-Items");
    std::vector<std::string> transfer_syntaxes;
    for(auto it=items.begin()+1; it != items.end(); ++it)
    {
        auto const & value = it->as_string("Transfer-syntax-name");
        transfer_syntaxes.push_back(
            (value[value.size()-1]=='\0')?(value.substr(0, value.size()-1)):value);
    }

    return transfer_syntaxes;
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

    auto & items = this->_pdu_item.as_items("Abstract/Transfer Syntax Sub-Items");
    items.resize(1);

    for(auto const & transfer_syntax: transfer_syntaxes)
    {
        auto const padded =
            (transfer_syntax.size()%2==0)?transfer_syntax:(transfer_syntax+'\0');
        auto const item = PresentationContext::_make_string_item(
            "Transfer-syntax", padded);
        items.push_back(item);
    }

    this->_update_size();
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

    auto const & value = this->_pdu_item.as_items(
        "Abstract/Transfer Syntax Sub-Items")[0].as_string(
            "Transfer-syntax-name");
    return (value[value.size()-1]=='\0')?(value.substr(0, value.size()-1)):value;
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

    auto const padded =
        (transfer_syntax.size()%2==0)?transfer_syntax:(transfer_syntax+'\0');
    auto const item = PresentationContext::_make_string_item(
        "Transfer-syntax", padded);
    this->_pdu_item.as_items("Abstract/Transfer Syntax Sub-Items")[0] = item;

    this->_update_size();
}

ProtocolDataUnitItem
PresentationContext
::_make_string_item(
    std::string const & type, std::string const & value)
{

    ProtocolDataUnitItem item;

    uint8_t item_type;
    if(type == "Abstract-syntax")
    {
        item_type = 0x30;
    }
    else if(type == "Transfer-syntax")
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
    item.add(type+"-name", value);

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
        std::vector<ProtocolDataUnitItem>{(ProtocolDataUnitItem())});
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
