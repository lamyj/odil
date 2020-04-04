/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _80f85d92_d528_44cf_a352_98eac994b9c2
#define _80f85d92_d528_44cf_a352_98eac994b9c2

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

#include "odil/Value.h"

#include "Value.h"

namespace odil
{

namespace wrappers
{

template<typename T>
IndexAccessorVisitor::result_type 
IndexAccessorVisitor
::operator()(T const & value) const
{
    return pybind11::cast(value[this->index]);
}

template<typename T>
SliceAccessorVisitor::result_type
SliceAccessorVisitor
::operator()(T const & value) const
{
    result_type result(this->slice_length);
    std::size_t d = 0;
    for(ssize_t s = this->start; s != this->stop; s += this->step)
    { 
        result[d++] = value[s];
    }
    return result;
}

template<typename T>
IteratorVisitor::result_type
IteratorVisitor
::operator()(T const & value) const
{
    return pybind11::make_iterator(value.begin(), value.end());
}

template<typename T>
PickleVisitor::result_type
PickleVisitor
::operator()(T const & value) const
{
    return pybind11::make_tuple(this->type, value);
}

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

template<typename Vector, typename holder_type, typename... Args>
pybind11::class_<Vector, holder_type>
bind_vector(pybind11::handle scope, std::string const &name, Args&&... args)
{
    using Class_ = pybind11::class_<Vector, holder_type>;

    // If the value_type is unregistered (e.g. a converting type) or is itself 
    // registered module-local then make the vector binding module-local 
    // as well:
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

    // Accessor and iterator; return by value if copyable, otherwise we return 
    // by ref + keep-alive
    
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

    cl.def(
        "__bool__", [](const Vector &v) { return !v.empty(); },
        "Check whether the list is nonempty");

    cl.def("__len__", &Vector::size);

    return cl;
}

}

}

#endif // _80f85d92_d528_44cf_a352_98eac994b9c2
