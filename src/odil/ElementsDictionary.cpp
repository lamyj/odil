/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/ElementsDictionary.h"

#include <string>

#include "odil/Exception.h"

namespace odil
{

ElementsDictionaryKey
::ElementsDictionaryKey()
: _type(Type::None)
{
    // Nothing else.
}

ElementsDictionaryKey
::ElementsDictionaryKey(Tag const & value)
{
    this->set(value);
}

ElementsDictionaryKey
::ElementsDictionaryKey(std::string const & value)
{
    this->set(value);
}

ElementsDictionaryKey::Type const &
ElementsDictionaryKey
::get_type() const
{
    return this->_type;
}

Tag const &
ElementsDictionaryKey
::get_tag() const
{
    if(this->_type != Type::Tag)
    {
        throw Exception("Invalid type");
    }
    return this->_tag;
}

std::string const &
ElementsDictionaryKey
::get_string() const
{
    if(this->_type != Type::String)
    {
        throw Exception("Invalid type");
    }
    return this->_string;
}

void
ElementsDictionaryKey
::set(Tag const value)
{
    this->_type = Type::Tag;
    this->_tag = value;
}

void
ElementsDictionaryKey
::set(std::string const & value)
{
    this->_type = Type::String;
    this->_string = value;
}

bool
ElementsDictionaryKey
::operator<(ElementsDictionaryKey const & other) const
{
    if(this->_type == other._type)
    {
        if(this->_type == Type::Tag)
        {
            return (this->_tag < other._tag);
        }
        else if(this->_type == Type::String)
        {
            return (this->_string < other._string);
        }
        else
        {
            throw Exception("Invalid type");
        }
    }
    else
    {
        return static_cast<int>(this->_type) < static_cast<int>(other._type);
    }
}
bool
ElementsDictionaryKey
::operator==(ElementsDictionaryKey const & other) const
{
    if(this->_type == other._type)
    {
        if(this->_type == Type::Tag)
        {
            return (this->_tag == other._tag);
        }
        else if(this->_type == Type::String)
        {
            return (this->_string == other._string);
        }
        else
        {
            throw Exception("Invalid type");
        }
    }
    else
    {
        return false;
    }
}

ElementsDictionaryEntry
::ElementsDictionaryEntry(
    std::string const & name, std::string const & keyword,
    std::string const & vr, std::string const & vm)
: name(name), keyword(keyword), vr(vr), vm(vm)
{
    // Nothing else
}

}
