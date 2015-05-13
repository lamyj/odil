/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/Tag.h"

#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdicent.h>
#include <dcmtk/dcmdata/dcdict.h>
#include <dcmtk/dcmdata/dctagkey.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
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
    DcmTagKey const tag(this->group, this->element);
    DcmDictEntry const * entry = dcmDataDict.rdlock().findEntry(tag, NULL);
    if(entry == NULL)
    {
        throw Exception("No such element");
    }

    return entry->getTagName();
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
    DcmDictEntry const * entry = dcmDataDict.rdlock().findEntry(string.c_str());
    if(entry == NULL)
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
        DcmTagKey const tag = entry->getKey();
        this->group = tag.getGroup();
        this->element = tag.getElement();
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
