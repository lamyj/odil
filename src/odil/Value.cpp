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
#include <utility>
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

#define ODIL_VALUE_CONSTRUCTORS(type, holder) \
    Value\
    ::Value(type const & value)\
    : _type(Type::type), holder(value) \
    {} \
    \
    Value\
    ::Value(type && value)\
    : _type(Type::type), holder(std::move(value)) \
    {} \
    \
    Value\
    ::Value(std::initializer_list<type::value_type> const & value)\
    : _type(Type::type), holder(value) \
    {}
    /*
     * No need for for a rvalue reference version of std::initializer_list:
     * copying a std::initializer_list does not copy the underlying objects.
     */

    ODIL_VALUE_CONSTRUCTORS(Integers, _integers);
    ODIL_VALUE_CONSTRUCTORS(Reals, _reals);
    ODIL_VALUE_CONSTRUCTORS(Strings, _strings);
    ODIL_VALUE_CONSTRUCTORS(Binary, _binary);

#undef ODIL_VALUE_CONSTRUCTORS

Value
::Value(DataSets const & value)
: _type(Type::DataSets), _data_sets(std::make_shared<DataSets>(value))
{
}

Value
::Value(DataSets && value)
: _type(Type::DataSets), _data_sets(std::make_shared<DataSets>(std::move(value)))
{
}

Value
::Value(std::initializer_list<DataSets::value_type> const & value)
: _type(Type::DataSets), _data_sets(std::make_shared<DataSets>(value))
{
}

Value
::Value(std::initializer_list<int> const & value)
: _type(Type::Integers)
{
    this->_integers.resize(value.size());
    std::copy(value.begin(), value.end(), this->_integers.begin());
}

Value
::Value(std::initializer_list<std::initializer_list<uint8_t>> const & value)
: _type(Type::Binary)
{
    this->_binary.resize(value.size());
    std::copy(value.begin(), value.end(), this->_binary.begin());
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
        return (
            this->_data_sets->size() == other._data_sets->size()
            && std::equal(
                this->_data_sets->begin(), this->_data_sets->end(),
                other._data_sets->begin(),
                [](std::shared_ptr<DataSet const> x, std::shared_ptr<DataSet const> y) {
                    return *x == *y;
                }
            )
        );
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

