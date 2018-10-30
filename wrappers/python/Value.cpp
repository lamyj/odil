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
    ;

    enum_<Value::Type>(value, "Type")
        .value("Integers", Value::Type::Integers)
        .value("Reals", Value::Type::Reals)
        .value("Strings", Value::Type::Strings)
        .value("DataSets", Value::Type::DataSets)
        .value("Binary", Value::Type::Binary)
    ;

    odil::bind_vector<Value::Integers>(value, "Integers");
    odil::bind_vector<Value::Reals>(value, "Reals");

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
    }

    odil::bind_vector<Value::DataSets>(value, "DataSets");
    odil::bind_vector<Value::Binary::value_type>(value, "BinaryItem")
        .def("get_memory_view", as_memory_view);
    odil::bind_vector<Value::Binary>(value, "Binary");
}
