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

namespace 
{

template<typename T>
pybind11::tuple pickle_pod_container(T const & container)
{
    return pybind11::make_tuple(
        pybind11::bytes(
            reinterpret_cast<char const*>(container.data()), 
            sizeof(typename T::value_type)*container.size()));
}

template<typename T>
T unpickle_pod_container(pybind11::tuple pickled)
{
    char * raw_buffer;
    ssize_t length;
    PYBIND11_BYTES_AS_STRING_AND_SIZE(
        pickled[0].cast<pybind11::bytes>().ptr(), &raw_buffer, &length);
    
    auto buffer = reinterpret_cast<typename T::value_type *>(raw_buffer);
    
    return T(buffer, buffer+length/sizeof(typename T::value_type));
}

template<typename T>
pybind11::tuple pickle_object_container(T const & container)
{
    pybind11::tuple pickled(container.size());
    for(std::size_t i=0; i<container.size(); ++i)
    {
        pickled[i] = container[i];
    }
    return pickled;
}

template<typename T>
T unpickle_object_container(pybind11::tuple pickled) 
{
    T value(pickled.size());
    for(std::size_t i=0; i<value.size(); ++i)
    {
        value[i] = pickled[i].cast<typename T::value_type>();
    }
    return value;
}

}

namespace odil
{

pybind11::object
as_memory_view(odil::Value::Binary::value_type const & binary_item)
{
    Py_buffer buffer;
    PyBuffer_FillInfo(
        &buffer, nullptr,
        const_cast<odil::Value::Binary::value_type::value_type*>(&binary_item[0]),
        binary_item.size(), 1, PyBUF_SIMPLE);
    PyObject * memory_view = PyMemoryView_FromBuffer(&buffer);

    return pybind11::reinterpret_steal<pybind11::object>(memory_view);
}

// TODO: add this to bind_vector
template<typename Vector, typename Class_>
void vector_accessor(Class_ &cl)
{
    using T = typename Vector::value_type;
    using SizeType = long; //typename Vector::size_type;
    using ItType   = typename Vector::iterator;

    cl.def(
        "__getitem__",
        [](Vector &v, SizeType i) -> T &
        {
            if((i>=0 && i >= SizeType(v.size())) || (i<0 && i < -SizeType(v.size())))
            {
                throw pybind11::index_error();
            }
            return v[i>=0?i:v.size()+i];
        },
        pybind11::return_value_policy::reference_internal // ref + keepalive
    );

    cl.def(
        "__iter__",
        [](Vector &v)
        {
            return pybind11::make_iterator<
                    pybind11::return_value_policy::reference_internal, ItType, ItType, T&
                >(v.begin(), v.end());
        },
        pybind11::keep_alive<0, 1>() /* Essential: keep list alive while iterator exists */
    );
}

template<typename Vector, typename holder_type = std::unique_ptr<Vector>, typename... Args>
pybind11::class_<Vector, holder_type>
bind_vector(pybind11::handle scope, std::string const &name, Args&&... args)
{
    using Class_ = pybind11::class_<Vector, holder_type>;

    // If the value_type is unregistered (e.g. a converting type) or is itself registered
    // module-local then make the vector binding module-local as well:
    using vtype = typename Vector::value_type;
    auto vtype_info = pybind11::detail::get_type_info(typeid(vtype));
    bool local = !vtype_info || vtype_info->module_local;

    Class_ cl(
        scope, name.c_str(), pybind11::module_local(local),
        std::forward<Args>(args)...);

    // Declare the buffer interface if a buffer_protocol() is passed in
    pybind11::detail::vector_buffer<Vector, Class_, Args...>(cl);

    cl.def(pybind11::init<>());

    // Register copy constructor (if possible)
    pybind11::detail::vector_if_copy_constructible<Vector, Class_>(cl);

    // Register comparison-related operators and functions (if possible)
    pybind11::detail::vector_if_equal_operator<Vector, Class_>(cl);

    // Register stream insertion operator (if possible)
    pybind11::detail::vector_if_insertion_operator<Vector, Class_>(cl, name);

    // Modifiers require copyable vector value type
    pybind11::detail::vector_modifiers<Vector, Class_>(cl);

    // Accessor and iterator; return by value if copyable, otherwise we return by ref + keep-alive
    odil::vector_accessor<Vector, Class_>(cl);

    cl.def(
        "__bool__",
        [](const Vector &v) -> bool
        {
            return !v.empty();
        },
        "Check whether the list is nonempty"
    );

    cl.def("__len__", &Vector::size);

    return cl;
}

}

void wrap_Value(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

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
        .def_property_readonly("type", &Value::get_type)
        .def(pickle(
            [](Value const & value) -> tuple {
                auto const type = value.get_type();
                if(type == Value::Type::Integers)
                {
                    return pybind11::make_tuple(type, value.as_integers());
                }
                else if(type == Value::Type::Reals)
                {
                    return pybind11::make_tuple(type, value.as_reals());
                }
                else if(type == Value::Type::Strings)
                {
                    return pybind11::make_tuple(type, value.as_strings());
                }
                else if(type == Value::Type::DataSets)
                {
                    return pybind11::make_tuple(type, value.as_data_sets());
                }
                else if(type == Value::Type::Binary)
                {
                    return pybind11::make_tuple(type, value.as_binary());
                }
                else
                {
                    throw Exception("Value: invalid pickled state");
                }
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
    
    odil::bind_vector<Value::Integers>(value, "Integers")
        .def(pickle(
            &pickle_pod_container<Value::Integers>,
            &unpickle_pod_container<Value::Integers>))
    ;
    odil::bind_vector<Value::Reals>(value, "Reals")
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
                typedef detail::iterator_state<
                    ItType, ItType, false, return_value_policy::copy> state;

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

    odil::bind_vector<Value::DataSets>(value, "DataSets")
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
    
    odil::bind_vector<Value::Binary::value_type>(value, "BinaryItem")
        .def("get_memory_view", as_memory_view)
        .def(pickle(
            [](Value::Binary::value_type b) {
                return make_tuple(
                    bytes(reinterpret_cast<char*>(b.data()), b.size()));
            },
            [](tuple pickled) {
                char * buffer;
                ssize_t length;
                PYBIND11_BYTES_AS_STRING_AND_SIZE(
                    pickled[0].ptr(), &buffer, &length);
                
                return Value::Binary::value_type{
                    reinterpret_cast<unsigned char*>(buffer), 
                    reinterpret_cast<unsigned char*>(buffer)+length};
            }
        ))
    ;
    odil::bind_vector<Value::Binary>(value, "Binary")
        .def(pickle(
            &pickle_object_container<Value::Binary>,
            &unpickle_object_container<Value::Binary>
        ))
    ;
}
