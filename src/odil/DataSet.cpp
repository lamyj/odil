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
::DataSet()
{
    // Nothing to do.
}

void
DataSet
::add(Tag const & tag, Element const & element)
{
    this->_elements[tag] = element;
}


void
DataSet
::add(Tag const & tag, VR vr)
{
    Value value;

    if(vr == VR::UNKNOWN)
    {
        vr = as_vr(tag);
    }

    if(::odil::is_int(vr))
    {
        value = Value::Integers();
    }
    else if(::odil::is_real(vr))
    {
        value = Value::Reals();
    }
    else if(::odil::is_string(vr))
    {
        value = Value::Strings();
    }
    else if(::odil::is_binary(vr))
    {
        value = Value::Binary();
    }
    else if(vr == VR::SQ)
    {
        value = Value::DataSets();
    }
    else
    {
        throw Exception("Unknown VR: "+::odil::as_string(vr));
    }

    this->add(tag, Element(value, vr));
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
        throw Exception("No such element");
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
        throw Exception("No such element");
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
        throw Exception("No such element");
    }

    return it->second;
}

template<typename TTester>
bool is_of_type(DataSet const & data_set, Tag const & tag, TTester tester)
{
    return (data_set[tag].*tester)();
}

template<typename TResult>
TResult const & as_type(
    DataSet const & data_set, Tag const & tag, 
    TResult (Element::*getter)() const)
{
    return (data_set[tag].*getter)();
}


template<typename TResult>
TResult & as_type(
    DataSet & data_set, Tag const & tag, 
    TResult (Element::*getter)())
{
    return (data_set[tag].*getter)();
}

template<typename TContainer>
typename TContainer::value_type const & as_type(
    DataSet const & data_set, Tag const & tag, unsigned int position,
    TContainer const & (Element::*getter)() const)
{
    auto const & data = (data_set[tag].*getter)();
    if(data.size() <= position) 
    { 
        throw Exception("No such element"); 
    } 
    return data[position]; 
}

bool
DataSet
::is_int(Tag const & tag) const 
{ 
    return is_of_type(*this, tag, &Element::is_int);
}

Value::Integers const &
DataSet
::as_int(Tag const & tag) const 
{ 
    return as_type(*this, tag, &Element::as_int);
}

Value::Integers &
DataSet
::as_int(Tag const & tag) 
{ 
    return as_type(*this, tag, &Element::as_int);
}

Value::Integer const &
DataSet
::as_int(Tag const & tag, unsigned int position) const 
{ 
    return as_type(*this, tag, position, &Element::as_int);
}

bool
DataSet
::is_real(Tag const & tag) const 
{ 
    return is_of_type(*this, tag, &Element::is_real);
}

Value::Reals const &
DataSet
::as_real(Tag const & tag) const 
{ 
    return as_type(*this, tag, &Element::as_real);
}

Value::Reals &
DataSet
::as_real(Tag const & tag) 
{ 
    return as_type(*this, tag, &Element::as_real);
}

Value::Real const &
DataSet
::as_real(Tag const & tag, unsigned int position) const 
{ 
    return as_type(*this, tag, position, &Element::as_real);
}

bool
DataSet
::is_string(Tag const & tag) const 
{ 
    return is_of_type(*this, tag, &Element::is_string);
}

Value::Strings const &
DataSet
::as_string(Tag const & tag) const 
{ 
    return as_type(*this, tag, &Element::as_string);
}

Value::Strings &
DataSet
::as_string(Tag const & tag) 
{ 
    return as_type(*this, tag, &Element::as_string);
}

Value::String const &
DataSet
::as_string(Tag const & tag, unsigned int position) const 
{ 
    return as_type(*this, tag, position, &Element::as_string);
}

bool
DataSet
::is_data_set(Tag const & tag) const 
{ 
    return is_of_type(*this, tag, &Element::is_data_set);
}

Value::DataSets const &
DataSet
::as_data_set(Tag const & tag) const 
{ 
    return as_type(*this, tag, &Element::as_data_set);
}

Value::DataSets &
DataSet
::as_data_set(Tag const & tag) 
{ 
    return as_type(*this, tag, &Element::as_data_set);
}

DataSet const &
DataSet
::as_data_set(Tag const & tag, unsigned int position) const 
{ 
    return as_type(*this, tag, position, &Element::as_data_set);
}

bool
DataSet
::is_binary(Tag const & tag) const 
{ 
    return is_of_type(*this, tag, &Element::is_binary);
}

Value::Binary const &
DataSet
::as_binary(Tag const & tag) const 
{ 
    return as_type(*this, tag, &Element::as_binary);
}

Value::Binary &
DataSet
::as_binary(Tag const & tag) 
{ 
    return as_type(*this, tag, &Element::as_binary);
}

Value::Binary::value_type const &
DataSet
::as_binary(Tag const & tag, unsigned int position) const 
{ 
    return as_type(*this, tag, position, &Element::as_binary);
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
        throw Exception("No such element");
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
        throw Exception("No such element");
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
        throw Exception("No such element");
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

}
