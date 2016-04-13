/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/Tag.h"

#include <algorithm>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>

#include "odil/ElementsDictionary.h"
#include "odil/Exception.h"
#include "odil/registry.h"

namespace odil
{

Tag
::Tag(uint16_t group, uint16_t element)
: group(group), element(element)
{
    // Nothing else
}

Tag
::Tag(uint32_t tag)
: group(tag >> 16), element(tag & 0xffff)
{
    // Nothing else
}

Tag
::Tag(std::string const & string)
{
    this->_from_string(string);
}

Tag
::Tag(char const * string)
{
    this->_from_string(string);
}

bool
Tag
::is_private() const
{
    return (this->group%2 == 1);
}

std::string
Tag
::get_name() const
{
    std::string name;
    std::string const tag_string(*this);

    for(auto const item: registry::public_dictionary)
    {
        auto const & key = item.first;
        auto const & entry = item.second;

        if(key.get_type() == ElementsDictionaryKey::Type::Tag &&
            key.get_tag() == *this)
        {
            name = entry.keyword;
            break;
        }
        else if(key.get_type() == ElementsDictionaryKey::Type::String)
        {
            auto const is_equal = std::equal(
                tag_string.begin(), tag_string.end(), key.get_string().begin(), 
                [](char t, char k) { return (k=='x' || t==k); });
            if(is_equal)
            {
                name = entry.keyword;
                break;
            }
        }
    }

    if(name.empty())
    {
        throw Exception("No such element: "+tag_string);
    }

    return name;
}

bool
Tag
::operator==(Tag const & other) const
{
    return ((this->group == other.group) && (this->element == other.element));
}

bool
Tag
::operator!=(Tag const & other) const
{
    return !(*this == other);
}

bool
Tag
::operator<(Tag const & other) const
{
    return (
        (this->group < other.group) ||
        (this->group == other.group && this->element < other.element));
}

bool
Tag
::operator>(Tag const & other) const
{
    return (
        (this->group > other.group) ||
        (this->group == other.group && this->element > other.element));
}

bool
Tag
::operator<=(Tag const & other) const
{
    return !(*this > other);
}

bool
Tag
::operator>=(Tag const & other) const
{
    return !(*this < other);
}

void
Tag
::_from_string(std::string const & string)
{
    ElementsDictionary::const_iterator it = registry::public_dictionary.begin();
    while(it != registry::public_dictionary.end())
    {
        if(it->second.keyword == string)
        {
            break;
        }
        ++it;
    }

    if(it == registry::public_dictionary.end())
    {
        // Try with string form of numeric tag
        uint16_t group;
        uint16_t element;
        bool parsed = true;

        if(string.size() != 8)
        {
            parsed = false;
        }
        else
        {
            std::string const first = string.substr(0, 4);
            char * endptr;
            group = strtol(first.c_str(), &endptr, 16);
            if(*endptr != '\0')
            {
                parsed = false;
            }
            else
            {
                std::string const second = string.substr(4, 4);
                element = strtol(second.c_str(), &endptr, 16);
                if(*endptr != '\0')
                {
                    parsed = false;
                }
            }
        }

        if(!parsed)
        {
            throw Exception("No such element: "+string);
        }
        else
        {
            this->group = group;
            this->element = element;
        }
    }
    else
    {
        if(it->first.get_type() != ElementsDictionaryKey::Type::Tag)
        {
            throw Exception("InvalidType");
        }
        auto const & tag = it->first.get_tag();
        this->group = tag.group;
        this->element = tag.element;
    }
}

Tag
::operator std::string() const
{
    std::ostringstream stream;
    stream << (*this);
    return stream.str();
}

std::ostream & operator<<(std::ostream & stream, Tag const & tag)
{
    std::ostream::char_type const old_fill = stream.fill();
    std::streamsize const old_width = stream.width();
    std::ios::fmtflags const flags = stream.flags();

    stream << std::hex
           << std::setw(4) << std::setfill('0') << tag.group
           << std::setw(4) << std::setfill('0') << tag.element;

    stream.setf(flags);
    stream.width(old_width);
    stream.fill(old_fill);

    return stream;
}

}
