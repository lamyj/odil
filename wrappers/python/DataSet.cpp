/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <iterator>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include "odil/DataSet.h"

#include "value_constructor.h"

namespace
{

std::shared_ptr<odil::DataSet>
constructor()
{
    return std::make_shared<odil::DataSet>();
}

std::shared_ptr<odil::DataSet>
constructor_string(std::string const & s)
{
    return std::make_shared<odil::DataSet>(s);
}

bool equal(
    std::shared_ptr<odil::DataSet> left, std::shared_ptr<odil::DataSet> right)
{
    return *left == *right;
}

bool different(
    std::shared_ptr<odil::DataSet> left, std::shared_ptr<odil::DataSet> right)
{
    return !equal(left, right);
}

void add(
    odil::DataSet & data_set, odil::Tag const & tag,
    boost::python::object value_python=boost::python::object(), 
    odil::VR vr=odil::VR::UNKNOWN)
{
    if(vr == odil::VR::UNKNOWN)
    {
        vr = as_vr(tag);
    }
    
    if(!value_python.is_none())
    {
        auto const value_cpp = value_constructor(value_python);
        data_set.add(tag, odil::Element(*value_cpp, vr));
    }
    else
    {
        data_set.add(tag, vr);
    }
}

void set(
    odil::DataSet & data_set, odil::Tag const & tag,
    boost::python::object value_python)
{
    auto const value_cpp = value_constructor(value_python);
    if(value_cpp->get_type() == odil::Value::Type::Integers)
    {
        data_set.as_int(tag) = value_cpp->as_integers();
    }
    else if(value_cpp->get_type() == odil::Value::Type::Reals)
    {
        data_set.as_real(tag) = value_cpp->as_reals();
    }
    else if(value_cpp->get_type() == odil::Value::Type::Strings)
    {
        data_set.as_string(tag) = value_cpp->as_strings();
    }
    else if(value_cpp->get_type() == odil::Value::Type::DataSets)
    {
        data_set.as_data_set(tag) = value_cpp->as_data_sets();
    }
    else if(value_cpp->get_type() == odil::Value::Type::Binary)
    {
        data_set.as_binary(tag) = value_cpp->as_binary();
    }
    else
    {
        throw odil::Exception("Unknown value type");
    }
}


class ConstIteratorAdapter
{
public:
    typedef odil::DataSet::const_iterator::difference_type difference_type;
    typedef odil::DataSet::const_iterator::value_type::first_type value_type;
    typedef odil::DataSet::const_iterator::value_type::first_type const * pointer;
    typedef odil::DataSet::const_iterator::value_type::first_type const & reference;
    typedef std::bidirectional_iterator_tag iterator_category;

    ConstIteratorAdapter(odil::DataSet::const_iterator const & iterator)
    : _iterator(iterator)
    {
        // Nothing else.
    }

    reference operator*() const
    {
        return this->_iterator->first;
    }

    ConstIteratorAdapter & operator++()
    {
        ++this->_iterator;
        return *this;
    }

    ConstIteratorAdapter operator++(int)
    {
        ConstIteratorAdapter tmp(*this);
        ++(*this);
        return tmp;
    }

    ConstIteratorAdapter & operator--()
    {
        --this->_iterator;
        return *this;
    }

    ConstIteratorAdapter operator--(int)
    {
        ConstIteratorAdapter tmp(*this);
        --(*this);
        return tmp;
    }

    bool operator==(ConstIteratorAdapter const & other)
    {
        return this->_iterator == other._iterator;
    }

    bool operator!=(ConstIteratorAdapter const & other)
    {
        return this->_iterator != other._iterator;
    }

private:
    odil::DataSet::const_iterator _iterator;
};

ConstIteratorAdapter begin(odil::DataSet const & data_set)
{
    return ConstIteratorAdapter(data_set.begin());
}

ConstIteratorAdapter end(odil::DataSet const & data_set)
{
    return ConstIteratorAdapter(data_set.end());
}

boost::python::list keys(odil::DataSet const & data_set)
{
    boost::python::list result;
    for(auto const & item: data_set)
    {
        result.append(item.first);
    }

    return result;
}

boost::python::list values(odil::DataSet const & data_set)
{
    boost::python::list result;
    for(auto const & item: data_set)
    {
        result.append(item.second);
    }

    return result;
}

boost::python::list items(odil::DataSet const & data_set)
{
    boost::python::list result;
    for(auto const & item: data_set)
    {
        result.append(boost::python::make_tuple(item.first, item.second));
    }

    return result;
}

odil::Element & set_item(
    odil::DataSet & data_set, odil::Tag const & tag, odil::Element const & value) 
{
    return data_set[tag] = value;
}

}

BOOST_PYTHON_FUNCTION_OVERLOADS(add_overloads, add, 2, 4);

void wrap_DataSet()
{
    using namespace boost::python;
    using namespace odil;

    class_<DataSet, std::shared_ptr<DataSet>>("DataSet", no_init)
        .def("__init__", make_constructor(constructor))
        .def("__init__", make_constructor(constructor_string))
        .def("add", add, add_overloads())
        .def("remove", &DataSet::remove)
        .def("has", &DataSet::has)
        .def("empty", static_cast<bool (DataSet::*)() const>(&DataSet::empty))
        .def(
            "size",
            static_cast<std::size_t (DataSet::*)() const>(&DataSet::size))
        .def("get_vr", &DataSet::get_vr)
        .def(
            "empty",
            static_cast<bool (DataSet::*)(Tag const &) const>(&DataSet::empty))
        .def(
            "size",
            static_cast<std::size_t (DataSet::*)(Tag const &) const>(
                &DataSet::size))
        .def(
            "__getitem__",
            static_cast<Element const & (DataSet::*)(Tag const&) const>(&DataSet::operator[]),
            return_value_policy<reference_existing_object>())
        .def(
            "__setitem__", &set_item,
            return_value_policy<reference_existing_object>())
        .def("is_int", &DataSet::is_int)
        .def(
            "as_int",
            static_cast<Value::Integers & (DataSet::*)(Tag const &)>(
                &DataSet::as_int),
            return_value_policy<reference_existing_object>())
        .def("is_real", &DataSet::is_real)
        .def(
            "as_real",
            static_cast<Value::Reals & (DataSet::*)(Tag const &)>(
                &DataSet::as_real),
            return_value_policy<reference_existing_object>())
        .def("is_string", &DataSet::is_string)
        .def(
            "as_string",
            static_cast<Value::Strings & (DataSet::*)(Tag const &)>(
                &DataSet::as_string),
            return_value_policy<reference_existing_object>())
        .def("is_data_set", &DataSet::is_data_set)
        .def(
            "as_data_set",
            static_cast<Value::DataSets & (DataSet::*)(Tag const &)>(
                &DataSet::as_data_set),
            return_value_policy<reference_existing_object>())
        .def("is_binary", &DataSet::is_binary)
        .def(
            "as_binary",
            static_cast<Value::Binary & (DataSet::*)(Tag const &)>(
                &DataSet::as_binary),
            return_value_policy<reference_existing_object>())
        .def(
            "get_transfer_syntax", &DataSet::get_transfer_syntax,
            return_value_policy<copy_const_reference>())
        .def("set_transfer_syntax", &DataSet::set_transfer_syntax)
        .def("set", &set)
        .def("keys", &keys)
        .def("__iter__", range(&begin, &end))
        .def("values", &values)
        .def("items", &items)
        .def("__eq__", equal)
        .def("__ne__", different)
        .def(
            "__len__",
            static_cast<std::size_t (DataSet::*)() const>(&DataSet::size))
        .def("clear", static_cast<void(DataSet::*)()>(&DataSet::clear))
        .def("clear", static_cast<void(DataSet::*)(Tag const &)>(&DataSet::clear))
    ;
}

