/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _99998287_59bb_4f7c_aadc_fe5ecb87f8c2
#define _99998287_59bb_4f7c_aadc_fe5ecb87f8c2

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

#include <odil/Reader.h>

#include "opaque_types.h"
#include "type_casters.h"

#include "streambuf.h"

void wrap_Reader(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    std::function<bool(Tag const &)> default_halt_condition =
        [](Tag const &)->bool { return false;};

    class_<Reader>(m, "Reader")
        .def(
            init<odil::wrappers::python::iostream &, std::string const &, bool>(),
            "stream"_a, "transfer_syntax"_a, "keep_group_length"_a=false)
        .def_readwrite("transfer_syntax", &Reader::transfer_syntax)
        .def_readwrite("byte_ordering", &Reader::byte_ordering)
        .def_readwrite("explicit_vr", &Reader::explicit_vr)
        .def_readwrite("keep_group_length", &Reader::keep_group_length)
        .def(
            "read_data_set", &Reader::read_data_set,
            "halt_condition"_a=default_halt_condition)
        .def("read_tag", &Reader::read_tag)
        .def("read_length", &Reader::read_length)
        .def(
            "read_element", &Reader::read_element,
            "tag"_a=Tag(0xffff, 0xffff), "data_set"_a=std::make_shared<DataSet>())
        .def_static(
            "read_file",
            [](
                odil::wrappers::python::iostream & stream,
                bool keep_group_length,
                std::function<bool(Tag const &)> halt_condition)
            {
                return Reader::read_file(stream, keep_group_length, halt_condition);
            },
            "stream"_a, "keep_group_length"_a=false,
            "halt_condition"_a=default_halt_condition)
    ;
}

#endif // _99998287_59bb_4f7c_aadc_fe5ecb87f8c2
