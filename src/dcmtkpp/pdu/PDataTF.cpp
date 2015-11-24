/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/pdu/PDataTF.h"

#include <algorithm>
#include <cstdint>
#include <istream>
#include <string>
#include <vector>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/pdu/Item.h"
#include "dcmtkpp/pdu/Object.h"

namespace dcmtkpp
{

namespace pdu
{

PDataTF::PresentationDataValueItem
::PresentationDataValueItem(
    uint8_t presentation_context_id, uint8_t control_header,
    std::string const & fragment)
{
    this->_item.add("Item-length", uint32_t(4));
    this->_item.add("Presentation-Context-ID", uint8_t(0));
    this->_item.add("Control-header", uint8_t(0));
    this->_item.add("Fragment", std::string());

    this->set_presentation_context_id(presentation_context_id);
    this->set_control_header(control_header);
    this->set_fragment(fragment);
}

PDataTF::PresentationDataValueItem
::PresentationDataValueItem(std::istream & stream)
{
    this->_item.read(stream, "Item-length", Item::Field::Type::unsigned_int_32);
    this->_item.read(
        stream, "Presentation-Context-ID", Item::Field::Type::unsigned_int_8);
    this->_item.read(
        stream, "Control-header", Item::Field::Type::unsigned_int_8);
    this->_item.read(
        stream, "Fragment", Item::Field::Type::string,
        this->_item.as_unsigned_int_32("Item-length")-2);
}

uint8_t
PDataTF::PresentationDataValueItem
::get_presentation_context_id() const
{
    return this->_item.as_unsigned_int_8("Presentation-Context-ID");
}

void
PDataTF::PresentationDataValueItem
::set_presentation_context_id(uint8_t value)
{
    if(value%2 == 0)
    {
        throw Exception("Invalid Presentation Context ID");
    }
    this->_item.as_unsigned_int_8("Presentation-Context-ID") = value;
}

uint8_t
PDataTF::PresentationDataValueItem
::get_control_header() const
{
    return this->_item.as_unsigned_int_8("Control-header");
}

void
PDataTF::PresentationDataValueItem
::set_control_header(uint8_t value)
{
    this->_item.as_unsigned_int_8("Control-header") = value;
}

bool
PDataTF::PresentationDataValueItem
::is_command() const
{
    return (this->get_control_header()%2==1);
}

bool
PDataTF::PresentationDataValueItem
::is_last_fragment() const
{
    return ((this->get_control_header()>>1)%2==1);
}

std::string const &
PDataTF::PresentationDataValueItem
::get_fragment() const
{
    return this->_item.as_string("Fragment");
}

void
PDataTF::PresentationDataValueItem
::set_fragment(std::string const & fragment)
{
    this->_item.as_string("Fragment") = fragment;
    this->_item.as_unsigned_int_32("Item-length") = 2+fragment.size();
}

PDataTF
::PDataTF(std::vector<PresentationDataValueItem> const & pdv_items)
{
    this->_item.add("PDU-type", uint8_t(0x04));
    this->_item.add("Reserved-1", uint8_t(0));
    this->_item.add("PDU-length", uint32_t(4));
    this->_item.add("Presentation-data-value-Items", std::vector<Item>());

    this->set_pdv_items(pdv_items);
}

PDataTF
::PDataTF(std::istream & stream)
{
    this->_item.read(stream, "PDU-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("PDU-type") != 0x04)
    {
        throw Exception("Invalid PDU type");
    }

    this->_item.read(stream, "Reserved-1", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "PDU-length", Item::Field::Type::unsigned_int_32);

    auto const pdu_length = this->_item.as_unsigned_int_32("PDU-length");
    auto const begin = stream.tellg();

    std::vector<PresentationDataValueItem> pdv_items;
    while(stream.tellg()-begin < pdu_length)
    {
        PresentationDataValueItem pdv_item(stream);
        pdv_items.push_back(pdv_item);
    }

    this->_item.add("Presentation-data-value-Items", std::vector<Item>());
    this->set_pdv_items(pdv_items);
}

std::vector<PDataTF::PresentationDataValueItem>
PDataTF
::get_pdv_items() const
{
    std::vector<PresentationDataValueItem> result;
    for(auto const & item: this->_item.as_items("Presentation-data-value-Items"))
    {
        PresentationDataValueItem const pdv_item(
            item.as_unsigned_int_8("Presentation-Context-ID"),
            item.as_unsigned_int_8("Control-header"),
            item.as_string("Fragment"));

        result.push_back(pdv_item);
    }
    return result;
}

void
PDataTF
::set_pdv_items(std::vector<PresentationDataValueItem> const &pdv_items)
{
    auto & items = this->_item.as_items("Presentation-data-value-Items");

    items.resize(pdv_items.size());
    std::transform(
        pdv_items.begin(), pdv_items.end(), items.begin(),
        [](PresentationDataValueItem const& x){ return x.get_item(); });

    this->_item.as_unsigned_int_32("PDU-length") = this->_compute_length();
}

}

}
