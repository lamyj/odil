/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/pdu/AAssociateAC.h"

#include <algorithm>
#include <cstdint>
#include <istream>
#include <iterator>
#include <string>
#include <vector>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/pdu/ApplicationContext.h"
#include "dcmtkpp/pdu/Item.h"
#include "dcmtkpp/pdu/Object.h"
#include "dcmtkpp/pdu/PresentationContext.h"
#include "dcmtkpp/pdu/UserInformation.h"

namespace dcmtkpp
{

namespace pdu
{

AAssociateAC
::AAssociateAC()
{
    this->_item.add("PDU-type", uint8_t(0x02));
    this->_item.add("Reserved-1", uint8_t(0));
    this->_item.add("PDU-length", uint32_t(0));
    this->_item.add("Protocol-version", uint16_t(0));
    this->_item.add("Reserved-2", uint16_t(0));
    this->_item.add("Called-AE-title", std::string());
    this->_item.add("Calling-AE-title", std::string());
    this->_item.add("Reserved-3", std::string(32, '\0'));
    this->_item.add("Variable-items", std::vector<Item>());

    this->_item.as_unsigned_int_32("PDU-length") = this->_compute_length();
}

AAssociateAC
::AAssociateAC(std::istream & stream)
{
    this->_item.read(stream, "PDU-type", Item::Field::Type::unsigned_int_8);
    if(this->_item.as_unsigned_int_8("PDU-type") != 0x02)
    {
        throw Exception("Invalid PDU type");
    }

    this->_item.read(stream, "Reserved-1", Item::Field::Type::unsigned_int_8);
    this->_item.read(stream, "PDU-length", Item::Field::Type::unsigned_int_32);

    auto const begin = stream.tellg();

    this->_item.read(
        stream, "Protocol-version", Item::Field::Type::unsigned_int_16);
    this->_item.read(stream, "Reserved-2", Item::Field::Type::unsigned_int_16);
    this->_item.read(stream, "Called-AE-title", Item::Field::Type::string, 16);
    this->_item.read(stream, "Calling-AE-title", Item::Field::Type::string, 16);
    this->_item.read(stream, "Reserved-3", Item::Field::Type::string, 32);

    auto const length = this->_item.as_unsigned_int_32("PDU-length");

    this->_item.add("Variable-items", std::vector<Item>());
    auto & variable_items = this->_item.as_items("Variable-items");
    while(stream.tellg()-begin < length)
    {
        auto const type = stream.peek();
        Item sub_item;
        if(type == 0x10)
        {
            sub_item = ApplicationContext(stream).get_item();
        }
        else if(type == 0x21)
        {
            sub_item = PresentationContext(stream).get_item();
        }
        else if(type == 0x50)
        {
            sub_item = UserInformation(stream).get_item();
        }
        else
        {
            throw Exception("Invalid sub-item");
        }

        variable_items.push_back(sub_item);
    }

    this->_item.as_unsigned_int_32("PDU-length") = this->_compute_length();
}

uint16_t
AAssociateAC
::get_protocol_version() const
{
    return this->_item.as_unsigned_int_16("Protocol-version");
}

void
AAssociateAC
::set_protocol_version(uint16_t value)
{
    this->_item.as_unsigned_int_16("Protocol-version") = value;
}

std::string
AAssociateAC
::get_called_ae_title() const
{
    return this->_decode_ae_title(this->_item.as_string("Called-AE-title"));
}

void
AAssociateAC
::set_called_ae_title(std::string const & value)
{
    this->_item.as_string("Called-AE-title") = this->_encode_ae_title(value);
}

std::string
AAssociateAC
::get_calling_ae_title() const
{
    return this->_decode_ae_title(this->_item.as_string("Calling-AE-title"));
}

void
AAssociateAC
::set_calling_ae_title(std::string const & value)
{
    this->_item.as_string("Calling-AE-title") = this->_encode_ae_title(value);
}

ApplicationContext
AAssociateAC
::get_application_context() const
{
    auto const & sub_items = this->_item.as_items("Variable-items");
    auto const it = std::find_if(
        sub_items.begin(), sub_items.end(),
        [](Item const & x) {
            return x.as_unsigned_int_8("Item-type") == 0x10; });
    if(it == sub_items.end())
    {
        throw Exception("No Application Context");
    }

    std::stringstream stream;
    stream << *it;
    return ApplicationContext(stream);
}

void
AAssociateAC
::set_application_context(ApplicationContext const & value)
{
    auto const & old_items = this->_item.as_items("Variable-items");
    std::vector<Item> new_items;

    new_items.push_back(value.get_item());

    std::copy_if(
        old_items.begin(), old_items.end(), std::back_inserter(new_items),
        [](Item const & item) {
            return item.as_unsigned_int_8("Item-type") == 0x21; });

    std::copy_if(
        old_items.begin(), old_items.end(), std::back_inserter(new_items),
        [](Item const & item) {
            return item.as_unsigned_int_8("Item-type") == 0x50; });

    this->_item.as_items("Variable-items") = new_items;

    this->_item.as_unsigned_int_32("PDU-length") = this->_compute_length();
}

std::vector<PresentationContext>
AAssociateAC
::get_presentation_contexts() const
{
    std::vector<PresentationContext> result;
    for(auto const & item: this->_item.as_items("Variable-items"))
    {
        if(item.as_unsigned_int_8("Item-type") == 0x21)
        {
            std::stringstream stream;
            stream << item;
            result.push_back(PresentationContext(stream));
        }
    }

    return result;
}

void
AAssociateAC
::set_presentation_contexts(std::vector<PresentationContext> const & value)
{
    auto const & old_items = this->_item.as_items("Variable-items");
    std::vector<Item> new_items;

    std::copy_if(
        old_items.begin(), old_items.end(), std::back_inserter(new_items),
        [](Item const & item)  {
            return item.as_unsigned_int_8("Item-type") == 0x10; });

    std::transform(
        value.begin(), value.end(), std::back_inserter(new_items),
        [](PresentationContext const & x) { return x.get_item(); });

    std::copy_if(
        old_items.begin(), old_items.end(), std::back_inserter(new_items),
        [](Item const & item) {
            return item.as_unsigned_int_8("Item-type") == 0x50; });

    this->_item.as_items("Variable-items") = new_items;
    this->_item.as_unsigned_int_32("PDU-length") = this->_compute_length();
}

UserInformation
AAssociateAC
::get_user_information() const
{
    auto const & sub_items = this->_item.as_items("Variable-items");
    auto const it = std::find_if(
        sub_items.begin(), sub_items.end(),
        [](Item const & x) {
            return x.as_unsigned_int_8("Item-type") == 0x50; });
    if(it == sub_items.end())
    {
        throw Exception("No User Information");
    }

    std::stringstream stream;
    stream << *it;
    return UserInformation(stream);
}

void
AAssociateAC
::set_user_information(UserInformation const & value)
{
    auto const & old_items = this->_item.as_items("Variable-items");
    std::vector<Item> new_items;

    std::copy_if(
        old_items.begin(), old_items.end(), std::back_inserter(new_items),
        [](Item const & item) {
            return item.as_unsigned_int_8("Item-type") == 0x10; });

    std::copy_if(
        old_items.begin(), old_items.end(), std::back_inserter(new_items),
        [](Item const & item) {
            return item.as_unsigned_int_8("Item-type") == 0x21; });

    new_items.push_back(value.get_item());

    this->_item.as_items("Variable-items") = new_items;

    this->_item.as_unsigned_int_32("PDU-length") = this->_compute_length();
}

std::string
AAssociateAC
::_encode_ae_title(std::string const & value)
{
    if(value.empty() || value.size() > 16)
    {
        throw Exception("Invalid AE title");
    }

    auto const padded = value+std::string(16-value.size(), ' ');
    return padded;
}

std::string
AAssociateAC
::_decode_ae_title(std::string const & value)
{
    auto const begin = value.find_first_not_of(' ');
    if(begin == std::string::npos)
    {
        return "";
    }
    else
    {
        auto const end = value.find_last_not_of(' ');
        return value.substr(begin, end-begin+1);
    }
}

}

}
