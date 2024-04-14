/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <algorithm>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include "odil/DataSet.h"
#include "odil/Value.h"

#include "opaque_types.h"
#include "type_casters.h"
#include "Value.h"

namespace odil
{

namespace wrappers
{

GetItem
::GetItem(std::size_t index)
: index(index)
{
    // Nothing else.
}
    
GetItem::result_type
GetItem
::operator()(odil::Value::Strings const & value) const
{
    return pybind11::bytes(value[this->index]).cast<pybind11::object>();
}

GetSlice
::GetSlice(std::size_t size, pybind11::slice slice)
{
    // WARNING: pybind11 <= 2.2.4 uses the unsigned size_t, not the signed 
    // ssize_t. Use the Python API directly.
    PySlice_GetIndicesEx(
        slice.ptr(), size, 
        &this->start, &this->stop, &this->step, &this->slice_length);
}

GetSlice::result_type
GetSlice
::operator()(odil::Value::Strings const & value) const
{
    result_type result(this->slice_length);
    std::size_t d = 0;
    for(pybind11::size_t s = this->start; s != this->stop; s += this->step) 
    { 
        result[d++] = pybind11::bytes(value[s]);
    }
    return result;
}

SetItem
::SetItem(std::size_t index, pybind11::object item)
: index(index), item(item)
{
    // Nothing else.
}

Iterate::result_type
Iterate
::operator()(odil::Value::Strings const & value) const
{
    return pybind11::make_iterator<
            pybind11::return_value_policy::reference_internal,
            decltype(value.begin()), decltype(value.end()), pybind11::bytes
        >(value.begin(), value.end());
}

Append
::Append(pybind11::object item)
: item(item) 
{
    // Nothing else.
}

Pickle
::Pickle(odil::Value::Type type)
:type(type)
{
    // Nothing else
}

}

}

void wrap_Value(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    using namespace odil::wrappers;

    class_<Value> value(m, "Value");
    value
        .def(init<Value::Integers>())
        .def(init<Value::Reals>())
        .def(init<Value::Strings>())
        .def(init<Value::DataSets>())
        .def(init<Value::Binary>())
        // Explicit constructor since Value::XXX are opaque
        // WARNING: define *after* other constructors for correct priority
        .def(
            init([](sequence & source) {
                return convert_sequence<Value>(source);
            }))
        .def("get_type", &Value::get_type)
        .def("empty", &Value::empty)
        .def("size", &Value::size)
        .def(
            "as_integers", (Value::Integers & (Value::*)()) &Value::as_integers,
            return_value_policy::reference_internal)
        .def(
            "as_reals", (Value::Reals & (Value::*)()) &Value::as_reals,
            return_value_policy::reference_internal)
        .def(
            "as_strings", (Value::Strings & (Value::*)()) &Value::as_strings,
            return_value_policy::reference_internal)
        .def(
            "as_data_sets", (Value::DataSets & (Value::*)()) &Value::as_data_sets,
            return_value_policy::reference_internal)
        .def(
            "as_binary", (Value::Binary & (Value::*)()) &Value::as_binary,
            return_value_policy::reference_internal)
        .def(self == self)
        .def(self != self)
        .def("clear", &Value::clear)
        .def("__len__", &Value::size)
        .def(
            "__getitem__", [](Value const & self, pybind11::ssize_t index) {
                if(index < 0)
                {
                    index += self.size();
                }
                
                if(index >= self.size())
                {
                    throw std::out_of_range("list index out of range");
                }
                
                return apply_visitor(GetItem(index), self);
            })
        .def(
            "__getitem__", [](Value const & self, slice slice_) {
                return apply_visitor(GetSlice(self.size(), slice_), self);
            })
        .def(
            "__setitem__", [](Value & self, pybind11::size_t index, object item) {
                if(index < 0)
                {
                    index += self.size();
                }
                
                if(index >= self.size())
                {
                    throw std::out_of_range("list index out of range");
                }
                
                return apply_visitor(SetItem(index, item), self);
            })
        .def(
            "__iter__", 
            [](Value const & self) 
            { 
                return apply_visitor(Iterate(), self);
            })
        .def(
            "append", [](Value & self, object item) {
                return apply_visitor(Append(item), self);
            })
        .def_property_readonly("type", &Value::get_type)
        .def(pickle(
            [](Value const & value) -> tuple {
                return apply_visitor(Pickle(value.get_type()), value);
            },
            [](tuple pickled) {
                auto const type = pickled[0].cast<Value::Type>();
                if(type == Value::Type::Integers)
                {
                    return Value(pickled[1].cast<Value::Integers>());
                }
                else if(type == Value::Type::Reals)
                {
                    return Value(pickled[1].cast<Value::Reals>());
                }
                else if(type == Value::Type::Strings)
                {
                    return Value(pickled[1].cast<Value::Strings>());
                }
                else if(type == Value::Type::DataSets)
                {
                    return Value(pickled[1].cast<Value::DataSets>());
                }
                else if(type == Value::Type::Binary)
                {
                    return Value(pickled[1].cast<Value::Binary>());
                }
                else
                {
                    throw Exception("Value: invalid pickled state");
                }
            }
        ))
    ;

    enum_<Value::Type>(value, "Type")
        .value("Integers", Value::Type::Integers)
        .value("Reals", Value::Type::Reals)
        .value("Strings", Value::Type::Strings)
        .value("DataSets", Value::Type::DataSets)
        .value("Binary", Value::Type::Binary)
    ;
    
    odil::wrappers::bind_vector<Value::Integers>(value, "Integers")
        .def(pickle(
            &pickle_pod_container<Value::Integers>,
            &unpickle_pod_container<Value::Integers>))
    ;
    odil::wrappers::bind_vector<Value::Reals>(value, "Reals")
        .def(pickle(
            &pickle_pod_container<Value::Reals>,
            &unpickle_pod_container<Value::Reals>))
    ;

    // NOTE Using bind_vector brings back #63.
    // Re-use the code of bind_vector and modify where needed.
    {
        using Vector = Value::Strings;
        std::string const name = "Strings";

        using Class_ = class_<Vector>;
        Class_ cl(value, name.c_str(), module_local(true));
        cl.def(init<>());

        detail::vector_if_copy_constructible<Vector, Class_>(cl);
        detail::vector_if_equal_operator<Vector, Class_>(cl);
        detail::vector_if_insertion_operator<Vector, Class_>(cl);
        detail::vector_modifiers<Vector, Class_>(cl);

        // vector_accessor
        using T = typename Vector::value_type;
        using SizeType = long; //typename Vector::size_type;
        using ItType   = typename Vector::iterator;

        cl.def("__getitem__",
            [](Vector &v, SizeType i) {
                if((i>=0 && i >= SizeType(v.size())) || (i<0 && i < -SizeType(v.size())))
                {
                    throw pybind11::index_error();
                }
                return bytes(v[i>=0?i:v.size()+i]);
            });

        cl.def(
            "__iter__",
            [](Vector &v) {
#if PYBIND11_VERSION_HEX < 0x02080000
                using state = detail::iterator_state<
                    ItType, ItType, false, return_value_policy::copy>;
#else
                using state = detail::iterator_state<
                    detail::iterator_access<ItType>,
                    return_value_policy::copy, ItType, ItType, T>;
#endif
                if (!detail::get_type_info(typeid(state), false))
                {
                    class_<state>(handle(), "iterator", pybind11::module_local())
                        .def("__iter__", [](state &s) -> state& { return s; })
                        .def("__next__", [](state &s) -> bytes {
                            if (!s.first_or_done)
                            {
                                ++s.it;
                            }
                            else
                            {
                                s.first_or_done = false;
                            }
                            if (s.it == s.end)
                            {
                                s.first_or_done = true;
                                throw stop_iteration();
                            }
                            return bytes(*s.it);
                        })
                    ;
                }
                return cast(state{v.begin(), v.end(), true});
            }
        );

        // bind_vector
        cl.def("__bool__",
            [](const Vector &v) -> bool {
                return !v.empty();
            },
            "Check whether the list is nonempty"
        );

        cl.def("__len__", &Vector::size);
        
        cl.def(pickle(
            &pickle_object_container<Value::Strings>,
            &unpickle_object_container<Value::Strings>
        ));
    }

    odil::wrappers::bind_vector<Value::DataSets>(value, "DataSets")
        .def(pickle(
            [](Value::DataSets const & value) {
                tuple pickled(value.size());
                for(std::size_t i=0; i<value.size(); ++i)
                {
                    pickled[i] = value[i];
                }
                return pickled;
            },
            [](tuple pickled) {
                Value::DataSets value(pickled.size());
                for(std::size_t i=0; i<value.size(); ++i)
                {
                    value[i] = std::make_shared<DataSet>(
                        pickled[i].cast<DataSet>());
                }
                return value;
            }
        ))
    ;
    
    odil::wrappers::bind_vector<Value::Binary::value_type>(value, "BinaryItem")
        .def(
            "get_memory_view", 
            [](Value::Binary::value_type const & binary_item)
            {
                Py_buffer buffer;
                PyBuffer_FillInfo(
                    &buffer, nullptr,
                    const_cast<Value::Binary::value_type::value_type*>(&binary_item[0]),
                    binary_item.size(), 1, PyBUF_SIMPLE);
                PyObject * memory_view = PyMemoryView_FromBuffer(&buffer);

                return reinterpret_steal<object>(memory_view);
            })
        .def(pickle(
            [](Value::Binary::value_type b) {
                return make_tuple(
                    bytes(reinterpret_cast<char*>(b.data()), b.size()));
            },
            [](tuple pickled) {
                char * buffer;
                pybind11::ssize_t length;
                PYBIND11_BYTES_AS_STRING_AND_SIZE(
                    pickled[0].ptr(), &buffer, &length);
                
                return Value::Binary::value_type{
                    reinterpret_cast<unsigned char*>(buffer), 
                    reinterpret_cast<unsigned char*>(buffer)+length};
            }
        ))
    ;
    odil::wrappers::bind_vector<Value::Binary>(value, "Binary")
        .def(pickle(
            &pickle_object_container<Value::Binary>,
            &unpickle_object_container<Value::Binary>
        ))
    ;
}
