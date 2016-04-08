/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <iterator>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include "odil/DataSet.h"

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(add_overloads_2, odil::DataSet::add, 1, 2);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(add_overloads_3, odil::DataSet::add, 2, 3);

namespace
{

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

}

void wrap_DataSet()
{
    using namespace boost::python;
    using namespace odil;


    class_<DataSet>("DataSet", init<>())
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, Element const &)>(
                &DataSet::add))
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, VR)>(&DataSet::add),
            add_overloads_2())
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, Value::Integers const &, VR)>(
                &DataSet::add),
            add_overloads_3())
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, Value::Reals const &, VR)>(
                &DataSet::add),
            add_overloads_3())
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, Value::Strings const &, VR)>(
                &DataSet::add),
            add_overloads_3())
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, Value::DataSets const &, VR)>(
                &DataSet::add),
            add_overloads_3())
        .def(
            "add", 
            static_cast<void (DataSet::*)(Tag const &, Value::Binary const &, VR)>(
                &DataSet::add),
            add_overloads_3())
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
            static_cast<Element & (DataSet::*)(Tag const&)>(&DataSet::operator[]),
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
        .def("keys", &keys)
        .def("__iter__", range(&begin, &end))
        .def("values", &values)
        .def("items", &items)
        .def(self == self)
        .def(self != self)
        .def(
            "__len__", 
            static_cast<std::size_t (DataSet::*)() const>(&DataSet::size)) 
    ;
}
