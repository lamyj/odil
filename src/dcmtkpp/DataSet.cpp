/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/DataSet.h"

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdicent.h>
#include <dcmtk/dcmdata/dcdict.h>
#include <dcmtk/dcmdata/dctagkey.h>

#include "dcmtkpp/Exception.h"
#include "dcmtkpp/Tag.h"
#include "dcmtkpp/VR.h"

namespace dcmtkpp
{

void
DataSet
::add(Tag const & tag, VR const & vr)
{
    Value value;
    if(this->_is_int_vr(vr))
    {
        value = Value::Integers();
    }
    else if(this->_is_real_vr(vr))
    {
        value = Value::Reals();
    }
    else if(this->_is_string_vr(vr))
    {
        value = Value::Strings();
    }
    else
    {
        throw Exception("Unknown VR: "+::dcmtkpp::as_string(vr));
    }

    this->_elements[this->_as_numeric_tag(tag)] = Element(value, vr);
}

void
DataSet
::add(Tag const & tag)
{
    DcmTagKey const dcmtk_tag(tag.group, tag.element);
    DcmDictEntry const * entry = dcmDataDict.rdlock().findEntry(dcmtk_tag, NULL);
    if(entry == NULL)
    {
        throw Exception("No such element");
    }

    VR const vr(as_vr(entry->getVR().getValidVRName()));
    this->add(tag, vr);
}

void
DataSet
::remove(Tag const & tag)
{
    if(!this->has(tag))
    {
        throw Exception("No such element");
    }

    uint32_t const numeric_tag = this->_as_numeric_tag(tag);
    this->_elements.erase(numeric_tag);
}

bool
DataSet
::empty() const
{
    return this->_elements.empty();
}

std::size_t
DataSet
::size() const
{
    return this->_elements.size();
}

bool
DataSet
::has(Tag const & tag) const
{
    return (this->_find(tag) != this->_elements.end());
}

VR
DataSet
::get_vr(Tag const & tag) const
{
    ElementMap::const_iterator const it = this->_find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element");
    }

    return it->second.vr;
}

bool
DataSet
::empty(Tag const & tag) const
{
    ElementMap::const_iterator const it = this->_find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element");
    }

    return it->second.empty();
}

std::size_t
DataSet
::size(Tag const & tag) const
{
    ElementMap::const_iterator const it = this->_find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element");
    }

    return it->second.size();
}

bool
DataSet
::is_int(Tag const & tag) const
{
    auto const it = this->_find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element");
    }

    return it->second.is_int();
}

std::vector<int64_t> const &
DataSet
::as_int(Tag const & tag) const
{
    auto const it = this->_find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element");
    }

    return it->second.as_int();
}

std::vector<int64_t> &
DataSet
::as_int(Tag const & tag)
{
    auto const it = this->_find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element");
    }

    return it->second.as_int();
}

bool
DataSet
::is_real(Tag const & tag) const
{
    auto const it = this->_find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element");
    }

    return it->second.is_real();
}

std::vector<double> const &
DataSet
::as_real(Tag const & tag) const
{
    auto const it = this->_find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element");
    }

    return it->second.as_real();
}

std::vector<double> &
DataSet
::as_real(Tag const & tag)
{
    auto const it = this->_find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element");
    }

    return it->second.as_real();
}

bool
DataSet
::is_string(Tag const & tag) const
{
    auto const it = this->_find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element");
    }

    return it->second.is_string();
}

std::vector<std::string> const &
DataSet
::as_string(Tag const & tag) const
{
    auto const it = this->_find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element");
    }

    return it->second.as_string();
}

std::vector<std::string> &
DataSet
::as_string(Tag const & tag)
{
    auto const it = this->_find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element");
    }

    return it->second.as_string();
}

uint32_t
DataSet
::_as_numeric_tag(Tag const & tag)
{
    return (tag.group<<16) + tag.element;
}

bool
DataSet
::_is_int_vr(VR vr)
{
    return (
        vr == VR::IS || vr == VR::SL || vr == VR::SS || vr == VR::UL ||
        vr == VR::US);
}

bool
DataSet
::_is_real_vr(VR vr)
{
    return (vr == VR::DS || vr == VR::FL || vr == VR::FD);
}

bool
DataSet
::_is_string_vr(VR vr)
{
    // FIXME: PN
    return (
        vr == VR::AE || vr == VR::AS || vr == VR::CS || vr == VR::DA ||
        vr == VR::DA || vr == VR::LO || vr == VR::LT || vr == VR::PN ||
        vr == VR::SH || vr == VR::ST || vr == VR::TM || vr == VR::UC ||
        vr == VR::UI || vr == VR::UR || vr == VR::UT);
}


DataSet::ElementMap::const_iterator
DataSet
::_find(Tag const & tag) const
{
    uint32_t const numeric_tag = this->_as_numeric_tag(tag);
    return this->_elements.find(numeric_tag);
}

DataSet::ElementMap::iterator
DataSet
::_find(Tag const & tag)
{
    uint32_t const numeric_tag = this->_as_numeric_tag(tag);
    return this->_elements.find(numeric_tag);
}

}
