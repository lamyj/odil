/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _bf8eb8b7_3a82_495e_910e_f141d5605a08
#define _bf8eb8b7_3a82_495e_910e_f141d5605a08

#include <pybind11/pybind11.h>

#include "odil/Value.h"

namespace odil
{

namespace wrappers
{

/// @brief Retrieve a single element from a Value
struct IndexAccessorVisitor
{
    using result_type = pybind11::object;
    
    std::size_t index;
    
    IndexAccessorVisitor(std::size_t index);
    
    template<typename T>
    result_type operator()(T const & value) const;
    
    result_type operator()(odil::Value::Strings const & value) const;
};

/// @brief Retrieve a slice from a Value
struct SliceAccessorVisitor
{
    using result_type = pybind11::list;
    
    std::size_t start, stop, step, slice_length;
    
    SliceAccessorVisitor(std::size_t size, pybind11::slice slice);
    
    template<typename T>
    result_type operator()(T const & value) const;
    
    result_type operator()(odil::Value::Strings const & value) const;
};

/// @brief Return an iterator to a Value.
struct IteratorVisitor
{
    using result_type = pybind11::iterator;
    
    template<typename T>
    result_type operator()(T const & value) const;
    
    result_type operator()(odil::Value::Strings const & value) const;
};

/// @brief Return a pickled Value.
struct PickleVisitor
{
    using result_type = pybind11::tuple;
    
    odil::Value::Type type;
    
    PickleVisitor(odil::Value::Type type);
    
    template<typename T>
    result_type operator()(T const & value) const;
};

/// @brief Pickle a POD-containing Value (Integers, Reals)
template<typename T>
pybind11::tuple pickle_pod_container(T const & container);

/// @brief Unpickle a POD-containing Value (Integers, Reals)
template<typename T>
T unpickle_pod_container(pybind11::tuple pickled);

/// @brief Pickle a object-containing Value (Strings, Datasets, Binary)
template<typename T>
pybind11::tuple pickle_object_container(T const & container);

/// @brief Unpickle a object-containing Value (Strings, Datasets, Binary)
template<typename T>
T unpickle_object_container(pybind11::tuple pickled);

template<
    typename Vector, typename holder_type = std::unique_ptr<Vector>, 
    typename... Args>
pybind11::class_<Vector, holder_type>
bind_vector(pybind11::handle scope, std::string const &name, Args&&... args);

}

}

#include "Value.txx"

#endif // _bf8eb8b7_3a82_495e_910e_f141d5605a08
