/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/DataSet.h"

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "odil/Exception.h"
#include "odil/Tag.h"
#include "odil/VR.h"

namespace odil
{

DataSet
::DataSet(std::string const & transfer_syntax)
: _transfer_syntax(transfer_syntax)
{
    // Nothing else.
}

void
DataSet
::add(Tag const & tag, Element const & element)
{
    auto const iterator = this->_elements.find(tag);
    if(iterator == this->_elements.end())
    {
        this->_elements.insert({tag, element});
    }
    else
    {
        iterator->second = element;
    }
}

void
DataSet
::add(Tag const & tag, VR vr)
{
    if(vr == VR::UNKNOWN)
    {
        vr = as_vr(tag);
    }

    this->add(tag, Element(vr));
}

void
DataSet
::add(Tag const & tag, Value::Integers const & value, VR vr)
{
    if(vr == VR::UNKNOWN)
    {
        vr = as_vr(tag);
    }
    this->add(tag, Element(value, vr));
}

void
DataSet
::add(Tag const & tag, Value::Reals const & value, VR vr)
{
    if(vr == VR::UNKNOWN)
    {
        vr = as_vr(tag);
    }
    this->add(tag, Element(value, vr));
}

void
DataSet
::add(Tag const & tag, Value::Strings const & value, VR vr)
{
    if(vr == VR::UNKNOWN)
    {
        vr = as_vr(tag);
    }
    this->add(tag, Element(value, vr));
}

void
DataSet
::add(Tag const & tag, Value::DataSets const & value, VR vr)
{
    if(vr == VR::UNKNOWN)
    {
        vr = as_vr(tag);
    }
    this->add(tag, Element(value, vr));
}

void
DataSet
::add(Tag const & tag, Value::Binary const & value, VR vr)
{
    if(vr == VR::UNKNOWN)
    {
        vr = as_vr(tag);
    }
    this->add(tag, Element(value, vr));
}

void
DataSet
::add(Tag const & tag, std::initializer_list<int> const & value, VR vr)
{
    if(vr == VR::UNKNOWN)
    {
        vr = as_vr(tag);
    }
    this->add(tag, Element(value, vr));
}

void
DataSet
::add(
    Tag const & tag, std::initializer_list<Value::Integer> const & value, VR vr)
{
    if(vr == VR::UNKNOWN)
    {
        vr = as_vr(tag);
    }
    this->add(tag, Element(value, vr));
}

void
DataSet
::add(
    Tag const & tag, std::initializer_list<Value::Real> const & value, VR vr)
{
    if(vr == VR::UNKNOWN)
    {
        vr = as_vr(tag);
    }
    this->add(tag, Element(value, vr));
}

void
DataSet
::add(
    Tag const & tag, std::initializer_list<Value::String> const & value, VR vr)
{
    if(vr == VR::UNKNOWN)
    {
        vr = as_vr(tag);
    }
    this->add(tag, Element(value, vr));
}

void
DataSet
::add(
    Tag const & tag, std::initializer_list<DataSet> const & value, VR vr)
{
    if(vr == VR::UNKNOWN)
    {
        vr = as_vr(tag);
    }
    this->add(tag, Element(value, vr));
}

void
DataSet
::remove(Tag const & tag)
{
    if(!this->has(tag))
    {
        throw Exception("No such element " + std::string( tag ));
    }

    this->_elements.erase(tag);
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

Element const &
DataSet
::operator[](Tag const & tag) const
{
    ElementMap::const_iterator const it = this->_elements.find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element " + std::string( tag ));
    }

    return it->second;
}

Element &
DataSet
::operator[](Tag const & tag)
{
    ElementMap::iterator it = this->_elements.find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element " + std::string( tag ));
    }

    return it->second;
}

template<typename TContainer>
typename TContainer::value_type const & at_pos(
    TContainer const & container, unsigned int position)
{
    if(container.size() <= position)
    {
        throw Exception("No such element");
    }
    return container[position];
}

bool
DataSet
::is_int(Tag const & tag) const
{
    return (*this)[tag].is_int();
}

Value::Integers const &
DataSet
::as_int(Tag const & tag) const
{
    return (*this)[tag].as_int();
}

Value::Integers &
DataSet
::as_int(Tag const & tag)
{
    return (*this)[tag].as_int();
}

Value::Integer const &
DataSet
::as_int(Tag const & tag, unsigned int position) const
{
    return at_pos(as_int(tag), position);
}

bool
DataSet
::is_real(Tag const & tag) const
{
    return (*this)[tag].is_real();
}

Value::Reals const &
DataSet
::as_real(Tag const & tag) const
{
    return (*this)[tag].as_real();
}

Value::Reals &
DataSet
::as_real(Tag const & tag)
{
    return (*this)[tag].as_real();
}

Value::Real const &
DataSet
::as_real(Tag const & tag, unsigned int position) const
{
    return at_pos(as_real(tag), position);
}

bool
DataSet
::is_string(Tag const & tag) const
{
    return (*this)[tag].is_string();
}

Value::Strings const &
DataSet
::as_string(Tag const & tag) const
{
    return (*this)[tag].as_string();
}

Value::Strings &
DataSet
::as_string(Tag const & tag)
{
    return (*this)[tag].as_string();
}

Value::String const &
DataSet
::as_string(Tag const & tag, unsigned int position) const
{
    return at_pos(as_string(tag), position);
}

bool
DataSet
::is_data_set(Tag const & tag) const
{
    return (*this)[tag].is_data_set();
}

Value::DataSets const &
DataSet
::as_data_set(Tag const & tag) const
{
    return (*this)[tag].as_data_set();
}

Value::DataSets &
DataSet
::as_data_set(Tag const & tag)
{
    return (*this)[tag].as_data_set();
}

DataSet const &
DataSet
::as_data_set(Tag const & tag, unsigned int position) const
{
    return at_pos(as_data_set(tag), position);
}

bool
DataSet
::is_binary(Tag const & tag) const
{
    return (*this)[tag].is_binary();
}

Value::Binary const &
DataSet
::as_binary(Tag const & tag) const
{
    return (*this)[tag].as_binary();
}

Value::Binary &
DataSet
::as_binary(Tag const & tag)
{
    return (*this)[tag].as_binary();
}

Value::Binary::value_type const &
DataSet
::as_binary(Tag const & tag, unsigned int position) const
{
    return at_pos(as_binary(tag), position);
}

bool
DataSet
::has(Tag const & tag) const
{
    return (this->_elements.find(tag) != this->_elements.end());
}

VR
DataSet
::get_vr(Tag const & tag) const
{
    ElementMap::const_iterator const it = this->_elements.find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element "+  std::string(tag) );
    }

    return it->second.vr;
}

bool
DataSet
::empty(Tag const & tag) const
{
    ElementMap::const_iterator const it = this->_elements.find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element " + std::string( tag ) );
    }

    return it->second.empty();
}

std::size_t
DataSet
::size(Tag const & tag) const
{
    ElementMap::const_iterator const it = this->_elements.find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element " + std::string( tag ));
    }

    return it->second.size();
}

bool
DataSet
::operator==(DataSet const & other) const
{
    return (this->_elements == other._elements);
}

bool
DataSet
::operator!=(DataSet const & other) const
{
    return !(*this == other);
}

void
DataSet
::clear(Tag const & tag)
{
    ElementMap::iterator const it = this->_elements.find(tag);
    if(it == this->_elements.end())
    {
        throw Exception("No such element: "+std::string(tag));
    }

    it->second.clear();
}

std::string const &
DataSet
::get_transfer_syntax() const
{
    return _transfer_syntax;
}

void
DataSet
::set_transfer_syntax(std::string const & transfer_syntax)
{
    this->_transfer_syntax = transfer_syntax;
}

}

