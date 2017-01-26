/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/Value.h"

#include <cstdint>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "odil/DataSet.h"
#include "odil/Exception.h"

namespace
{

struct IsEmptyValue
{
    typedef bool result_type;

    template <typename T>
    result_type operator()(T const & container) const
    {
        return container.empty();
    }
};

struct ValueSizeGetter
{
    typedef std::size_t result_type;

    template <typename T>
    result_type operator()(T const & container) const
    {
        return container.size();
    }
};

struct ClearValue
{
    typedef void result_type;

    template <typename T>
    result_type operator()(T & container) const
    {
        return container.clear();
    }
};
}

namespace odil
{

Value
::Value(Integers const & integers)
: _type(Type::Integers), _integers(integers)
{
    // Nothing else.
}

Value
::Value(Reals const & reals)
: _type(Type::Reals), _reals(reals)
{
    // Nothing else.
}

Value
::Value(Strings const & strings)
: _type(Type::Strings), _strings(strings)
{
    // Nothing else.
}

Value
::Value(DataSets const & datasets)
: _type(Type::DataSets), _data_sets(std::make_shared<DataSets>(datasets))
{
    // Nothing else.
}

Value
::Value(Binary const & binary)
: _type(Type::Binary), _binary(binary)
{
    // Nothing else.
}

Value
::Value(std::initializer_list<int> const & list)
: _type(Type::Integers)
{
    this->_integers.resize(list.size());
    std::copy(list.begin(), list.end(), this->_integers.begin());
}

Value
::Value(std::initializer_list<Integer> const & list)
: _type(Type::Integers), _integers(list)
{
    // Nothing else
}

Value
::Value(std::initializer_list<Real> const & list)
: _type(Type::Reals), _reals(list)
{
    // Nothing else
}

Value
::Value(std::initializer_list<String> const & list)
: _type(Type::Strings), _strings(list)
{
    // Nothing else
}

Value
::Value(std::initializer_list<DataSet> const & list)
: _type(Type::DataSets), _data_sets(std::make_shared<DataSets>(list))
{
    // Nothing else
}

Value::Type
Value
::get_type() const
{
    return this->_type;
}

bool
Value
::empty() const
{
    return apply_visitor(IsEmptyValue(), *this);
}

std::size_t
Value
::size() const
{
    return apply_visitor(ValueSizeGetter(), *this);
}

#define DECLARE_CONST_ACCESSOR(type, name) \
Value::type const & \
Value \
::as_##name() const \
{ \
    if(this->get_type() != Type::type) \
    { \
        throw Exception("Type mismatch"); \
    } \
    return this->_##name; \
}

#define DECLARE_NON_CONST_ACCESSOR(type, name) \
Value::type & \
Value \
::as_##name() \
{ \
    if(this->get_type() != Type::type) \
    { \
        throw Exception("Type mismatch"); \
    } \
    return this->_##name; \
}

DECLARE_CONST_ACCESSOR(Integers, integers)
DECLARE_NON_CONST_ACCESSOR(Integers, integers)

DECLARE_CONST_ACCESSOR(Reals, reals)
DECLARE_NON_CONST_ACCESSOR(Reals, reals)

DECLARE_CONST_ACCESSOR(Strings, strings)
DECLARE_NON_CONST_ACCESSOR(Strings, strings)

Value::DataSets const & 
Value
::as_data_sets() const
{
    if(this->get_type() != Type::DataSets)
    {
        throw Exception("Type mismatch");
    }
	return *this->_data_sets;
}

Value::DataSets &
Value
::as_data_sets()
{
    if(this->get_type() != Type::DataSets)
    {
        throw Exception("Type mismatch");
    }
	return *this->_data_sets;
}

DECLARE_CONST_ACCESSOR(Binary, binary)
DECLARE_NON_CONST_ACCESSOR(Binary, binary)

#undef DECLARE_NON_CONST_ACCESSOR
#undef DECLARE_CONST_ACCESSOR

bool
Value
::operator==(Value const & other) const
{
    if(this->_type != other._type)
    {
        return false;
    }
    else if(this->_type == Value::Type::Integers)
    {
        return this->_integers == other._integers;
    }
    else if(this->_type == Value::Type::Reals)
    {
        return this->_reals == other._reals;
    }
    else if(this->_type == Value::Type::Strings)
    {
        return this->_strings == other._strings;
    }
    else if(this->_type == Value::Type::DataSets)
    {
        return *(this->_data_sets) == *(other._data_sets);
    }
    else if(this->_type == Value::Type::Binary)
    {
        return this->_binary == other._binary;
    }
    else
    {
        throw Exception("Unknown type");
    }
}

bool
Value
::operator!=(Value const & other) const
{
    return !(*this == other);
}

void
Value
::clear()
{
    apply_visitor(ClearValue(), *this);
}

}

