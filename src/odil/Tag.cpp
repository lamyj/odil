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
#include <stdexcept>
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
    
    auto const iterator = find(registry::public_dictionary, *this);
    if(iterator != registry::public_dictionary.end())
    {
        name = iterator->second.keyword;
    }

    if(name.empty())
    {
        std::string const tag_string(*this);
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
    bool found = false;
    uint16_t group;
    uint16_t element;
    
    // Try string form of numeric tag
    if(string.size() == 8)
    {
        try
        {
            group = std::stol(string.substr(0, 4), 0, 16);
            element = std::stol(string.substr(4, 8), 0, 16);
            found = true;
        }
        catch(std::invalid_argument const &)
        {
            found = false;
        }
    }
    
    if(!found)
    {
        auto const it = registry::public_tags.find(string);
        if(it != registry::public_tags.end())
        {
            found = true;
            group = it->second.group;
            element = it->second.element;
        }
    }
    
    if(!found)
    {
        throw Exception("No such element: \""+string+"\"");
    }
    else
    {
        this->group = group;
        this->element = element;
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
