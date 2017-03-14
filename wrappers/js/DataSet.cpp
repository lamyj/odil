/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <emscripten/bind.h>

#include "odil/DataSet.h"

std::vector<odil::Tag>
get_tags(odil::DataSet const & data_set)
{
    std::vector<odil::Tag> result;
    result.reserve(data_set.size());
    for(auto const & item: data_set)
    {
        result.push_back(item.first);
    }
    
    return result;
}

std::vector<int32_t>
as_int(odil::DataSet const & data_set, odil::Tag const & tag)
{
    auto const & value = data_set.as_int(tag);
    std::vector<int32_t> result;
    result.resize(value.size());
    std::copy(value.begin(), value.end(), result.begin());
    return result;
}

emscripten::val as_bytes(odil::DataSet const & data_set, odil::Tag const & tag) 
{
    using namespace emscripten;
    
    // FIXME: handle multi-valued binary items.
    auto const & value = data_set.as_binary(tag, 0);
    return val(typed_memory_view(value.size(), &value[0]));
}

void wrap_DataSet()
{
    using namespace emscripten;
    using namespace odil;
    
    class_<DataSet>("DataSet")
        .constructor<>()
        // add
        .function("remove", &DataSet::remove)
        .function("empty", select_overload<bool() const>(&DataSet::empty))
        .function("size", select_overload<std::size_t() const>(&DataSet::size))
        .function("has", &DataSet::has)
        .function("get_vr", &DataSet::get_vr)
        .function(
            "empty_tag", 
            select_overload<bool(Tag const &) const>(&DataSet::empty))
        .function(
            "size_tag", 
            select_overload<std::size_t(Tag const &) const>(&DataSet::size))
        .function("is_int", &DataSet::is_int)
        // FIXME: Javascript has no 64-bits int
        .function(
            "as_int", &as_int
            // select_overload<Value::Integers const & (Tag const &) const>(
            //     &DataSet::as_int)
        )
        .function("is_real", &DataSet::is_real)
        .function(
            "as_real", 
            select_overload<Value::Reals const & (Tag const &) const>(
                &DataSet::as_real))
        .function("is_string", &DataSet::is_string)
        .function(
            "as_string", 
            select_overload<Value::Strings const & (Tag const &) const>(
                &DataSet::as_string))
        .function("is_data_set", &DataSet::is_data_set)
        .function(
            "as_data_set", 
            select_overload<Value::DataSets const & (Tag const &) const>(
                &DataSet::as_data_set))
        .function("is_binary", &DataSet::is_binary)
        .function(
            "as_binary", 
            select_overload<Value::Binary const & (Tag const &) const>(
                &DataSet::as_binary))
        .function(
            "as_binary", 
            select_overload<Value::Binary const & (Tag const &) const>(
                &DataSet::as_binary))
        .function("as_bytes", &as_bytes)
        .function("get_tags", &get_tags)
        .function("equal", &DataSet::operator==)
        .function("notEqual", &DataSet::operator!=)
        .function("clear", &DataSet::clear)
        .function("get_transfer_syntax", &DataSet::get_transfer_syntax)
        .function("set_transfer_syntax", &DataSet::set_transfer_syntax)
    ;
}
