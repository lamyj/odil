/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _99998287_59bb_4f7c_aadc_fe5ecb87f8c2
#define _99998287_59bb_4f7c_aadc_fe5ecb87f8c2

#include <boost/python.hpp>

#include <odil/Reader.h>

#include "streambuf.h"

namespace
{

boost::shared_ptr<odil::Reader>
constructor(
    odil::wrappers::python::iostream & stream,
    std::string const & transfer_syntax, bool keep_group_length)
{
    odil::Reader * reader = new odil::Reader(
        stream, transfer_syntax, keep_group_length);

    // Old versions of Boost.Python (Debian 7, Ubuntu 12.04) do not like
    // std::shared_ptr
    return boost::shared_ptr<odil::Reader>(reader);
}

std::function<bool(odil::Tag const &)>
wrap_halt_condition(boost::python::object const & halt_condition)
{
    std::function<bool(odil::Tag const &)> halt_condition_cpp =
        [](odil::Tag const &) { return false;};
    if(halt_condition)
    {
        halt_condition_cpp =
            [halt_condition](odil::Tag const & tag) -> bool
            {
                return boost::python::extract<bool>(halt_condition(tag));
            };
    }

    return halt_condition_cpp;
}

odil::DataSet
read_data_set(
    odil::Reader const & reader, boost::python::object const & halt_condition)
{
    return reader.read_data_set(wrap_halt_condition(halt_condition));
}

boost::python::tuple
read_file(
    odil::wrappers::python::iostream & stream, bool keep_group_length,
    boost::python::object const & halt_condition)
{
    auto const header_and_data_set = odil::Reader::read_file(
            stream, keep_group_length, wrap_halt_condition(halt_condition));

    return boost::python::make_tuple(
        header_and_data_set.first, header_and_data_set.second);
}


}

void wrap_Reader()
{
    using namespace boost::python;
    using namespace odil;

    class_<Reader>(
            "Reader",
            init<odil::wrappers::python::iostream &, std::string, bool>((
                    arg("stream"), arg("transfer_syntax"),
                    arg("keep_group_length")=false)))
        .def_readwrite("transfer_syntax", &Reader::transfer_syntax)
        .def_readwrite("byte_ordering", &Reader::byte_ordering)
        .def_readwrite("explicit_vr", &Reader::explicit_vr)
        .def_readwrite("keep_group_length", &Reader::keep_group_length)
        .def("read_data_set", read_data_set, arg("halt_condition")=object())
        .def("read_tag", &Reader::read_tag)
        .def("read_length", &Reader::read_length)
        .def(
            "read_element", &Reader::read_element, (
                arg("tag")=Tag(0xffff, 0xffff), arg("data_set")=DataSet()
        ))
        .def(
            "read_file", read_file, (
                arg("stream"), arg("keep_group_length")=false,
                arg("halt_condition")=object())
        )
        .staticmethod("read_file")
    ;
}

#endif // _99998287_59bb_4f7c_aadc_fe5ecb87f8c2
