/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/pdu/Item.h"

#include <algorithm>
#include <cstdint>
#include <istream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "dcmtkpp/endian.h"
#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

namespace pdu
{

Item::Field
::Field(uint8_t value)
: _type(Type::unsigned_int_8), _uint8(value)
{
    // Nothing else.
}

Item::Field
::Field(uint16_t value)
: _type(Type::unsigned_int_16), _uint16(value)
{
    // Nothing else.
}

Item::Field
::Field(uint32_t value)
: _type(Type::unsigned_int_32), _uint32(value)
{
    // Nothing else.
}

Item::Field
::Field(std::string const & value)
: _type(Type::string), _string(value)
{
    // Nothing else.
}

Item::Field
::Field(std::vector<Item> const & value)
: _type(Type::items), _items(value)
{
    // Nothing else.
}

Item::Field::Type
Item::Field
::get_type() const
{
    return this->_type;
}

uint8_t
Item::Field
::as_unsigned_int_8() const
{
    if(this->_type != Type::unsigned_int_8)
    {
        throw dcmtkpp::Exception("Incorrect type");
    }
    return this->_uint8;
}

uint8_t &
Item::Field
::as_unsigned_int_8()
{
    if(this->_type != Type::unsigned_int_8)
    {
        throw dcmtkpp::Exception("Incorrect type");
    }
    return this->_uint8;
}

uint16_t
Item::Field
::as_unsigned_int_16() const
{
    if(this->_type != Type::unsigned_int_16)
    {
        throw dcmtkpp::Exception("Incorrect type");
    }
    return this->_uint16;
}

uint16_t &
Item::Field
::as_unsigned_int_16()
{
    if(this->_type != Type::unsigned_int_16)
    {
        throw dcmtkpp::Exception("Incorrect type");
    }
    return this->_uint16;
}

uint32_t
Item::Field
::as_unsigned_int_32() const
{
    if(this->_type != Type::unsigned_int_32)
    {
        throw dcmtkpp::Exception("Incorrect type");
    }
    return this->_uint32;
}

uint32_t &
Item::Field
::as_unsigned_int_32()
{
    if(this->_type != Type::unsigned_int_32)
    {
        throw dcmtkpp::Exception("Incorrect type");
    }
    return this->_uint32;
}

std::string const &
Item::Field
::as_string() const
{
    if(this->_type != Type::string)
    {
        throw dcmtkpp::Exception("Incorrect type");
    }
    return this->_string;
}

std::string &
Item::Field
::as_string()
{
    if(this->_type != Type::string)
    {
        throw dcmtkpp::Exception("Incorrect type");
    }
    return this->_string;
}

std::vector<Item> const &
Item::Field
::as_items() const
{
    if(this->_type != Type::items)
    {
        throw dcmtkpp::Exception("Incorrect type");
    }
    return this->_items;
}

std::vector<Item> &
Item::Field
::as_items()
{
    if(this->_type != Type::items)
    {
        throw dcmtkpp::Exception("Incorrect type");
    }
    return this->_items;
}

Item
::Item()
{
    // Nothing to do.
}

Item
::Item(std::vector<std::pair<std::string, Field>> const & fields)
: _fields(fields)
{
    // Nothing else.
}

Item &
Item
::add(std::string const & name, Field const & field)
{
    this->_fields.push_back(std::make_pair(name, field));
    return *this;
}

Item::Container::size_type
Item
::size() const
{
    return this->_fields.size();
}

bool
Item
::empty() const
{
    return this->_fields.empty();
}

bool
Item
::has_field(std::string const & name) const
{
    auto const iterator = std::find_if(
        this->_fields.begin(), this->_fields.end(),
        [&name](std::pair<std::string, Field> const & x)
        { return (x.first == name); });
    return (iterator == this->_fields.end());
}

Item::Field const &
Item
::operator[](std::string const & name) const
{
    auto const iterator = std::find_if(
        this->_fields.begin(), this->_fields.end(),
        [&name](std::pair<std::string, Field> const & x)
        { return (x.first == name); });
    if(iterator == this->_fields.end())
    {
        throw Exception("No such field");
    }
    return iterator->second;
}

Item::Field &
Item
::operator[](std::string const & name)
{
    auto const iterator = std::find_if(
        this->_fields.begin(), this->_fields.end(),
        [&name](std::pair<std::string, Field> const & x)
        { return (x.first == name); });
    if(iterator == this->_fields.end())
    {
        throw Exception("No such field");
    }
    return iterator->second;
}

uint8_t
Item
::as_unsigned_int_8(std::string const & name) const
{
    auto const & field = (*this)[name];
    return field.as_unsigned_int_8();
}

uint8_t &
Item
::as_unsigned_int_8(std::string const & name)
{
    auto & field = (*this)[name];
    return field.as_unsigned_int_8();
}

uint16_t
Item
::as_unsigned_int_16(std::string const & name) const
{
    auto const & field = (*this)[name];
    return field.as_unsigned_int_16();
}

uint16_t &
Item
::as_unsigned_int_16(std::string const & name)
{
    auto & field = (*this)[name];
    return field.as_unsigned_int_16();
}

uint32_t
Item
::as_unsigned_int_32(std::string const & name) const
{
    auto const & field = (*this)[name];
    return field.as_unsigned_int_32();
}

uint32_t &
Item
::as_unsigned_int_32(std::string const & name)
{
    auto & field = (*this)[name];
    return field.as_unsigned_int_32();
}

std::string const &
Item
::as_string(std::string const & name) const
{
    auto & field = (*this)[name];
    return field.as_string();
}

std::string &
Item
::as_string(std::string const & name)
{
    auto & field = (*this)[name];
    return field.as_string();
}

std::vector<Item> const &
Item
::as_items(std::string const & name) const
{
    auto & field = (*this)[name];
    return field.as_items();
}

std::vector<Item> &
Item
::as_items(std::string const & name)
{
    auto & field = (*this)[name];
    return field.as_items();
}

Item::const_iterator
Item
::begin() const
{
    return this->_fields.begin();
}

Item::const_iterator
Item
::end() const
{
    return this->_fields.end();
}

void
Item
::read(
    std::istream & stream, std::string const & name, Field::Type type,
    std::streamsize size)
{
    if(type == Field::Type::unsigned_int_8)
    {
        uint8_t value;
        stream.read(reinterpret_cast<char*>(&value), sizeof(value));
        if(!stream.good())
        {
            throw Exception("Could not read unsigned_int_8 field");
        }

        this->add(name, Field(value));
    }
    else if(type == Field::Type::unsigned_int_16)
    {
        uint16_t value;
        stream.read(reinterpret_cast<char*>(&value), sizeof(value));
        if(!stream.good())
        {
            throw Exception("Could not read unsigned_int_16 field");
        }

        value = big_endian_to_host(value);
        this->add(name, Field(value));
    }
    else if(type == Field::Type::unsigned_int_32)
    {
        uint32_t value;
        stream.read(reinterpret_cast<char*>(&value), sizeof(value));
        if(!stream.good())
        {
            throw Exception("Could not read unsigned_int_32 field");
        }

        value = big_endian_to_host(value);
        this->add(name, Field(value));
    }
    else if(type == Field::Type::string)
    {
        std::string value(size, '\0');
        stream.read(reinterpret_cast<char*>(&value[0]), value.size());
        if(!stream.good())
        {
            throw Exception("Could not read string field");
        }

        this->add(name, Field(value));
    }
    else
    {
        throw Exception("Unknown field type");
    }
}

std::ostream &
operator<<(std::ostream & stream, Item const & item)
{
    for(auto const & named_field: item)
    {
        auto const & field = named_field.second;
        auto const type = field.get_type();
        if(type == Item::Field::Type::unsigned_int_8)
        {
            auto const value = field.as_unsigned_int_8();
            stream.write(reinterpret_cast<char const*>(&value), sizeof(value));
        }
        else if(type == Item::Field::Type::unsigned_int_16)
        {
            auto const value = host_to_big_endian(field.as_unsigned_int_16());
            stream.write(reinterpret_cast<char const*>(&value), sizeof(value));
        }
        else if(type == Item::Field::Type::unsigned_int_32)
        {
            auto const value = host_to_big_endian(field.as_unsigned_int_32());
            stream.write(reinterpret_cast<char const*>(&value), sizeof(value));
        }
        else if(type == Item::Field::Type::string)
        {
            auto const value = field.as_string();
            stream.write(reinterpret_cast<char const*>(&value[0]), value.size());
        }
        else if(type == Item::Field::Type::items)
        {
            auto const value = field.as_items();
            for(auto const & sub_item: value)
            {
                stream << sub_item;
            }
        }
        else
        {
            throw Exception("Unknown type");
        }
    }

    return stream;
}

}

}
