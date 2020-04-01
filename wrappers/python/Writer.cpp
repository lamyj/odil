/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <fstream>

#include <pybind11/pybind11.h>

#include <odil/registry.h>
#include <odil/Writer.h>

#include "opaque_types.h"
#include "type_casters.h"

#include "streambuf.h"

void wrap_Writer(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<Writer> writer(m, "Writer");

    enum_<Writer::ItemEncoding>(writer, "ItemEncoding")
        .value("ExplicitLength", Writer::ItemEncoding::ExplicitLength)
        .value("UndefinedLength", Writer::ItemEncoding::UndefinedLength)
    ;

    writer
        .def_readwrite("byte_ordering", &Writer::byte_ordering)
        .def_readwrite("explicit_vr", &Writer::explicit_vr)
        .def_readwrite("item_encoding", &Writer::item_encoding)
        .def_readwrite("use_group_length", &Writer::use_group_length)
        .def(
            init<
                odil::wrappers::python::iostream &, ByteOrdering, bool,
                Writer::ItemEncoding, bool>(),
            "stream"_a, "byte_ordering"_a, "explicit_vr"_a,
            "item_encoding"_a=Writer::ItemEncoding::ExplicitLength,
            "use_group_length"_a=false)
        .def(
            init<
                odil::wrappers::python::iostream &, std::string const &,
                Writer::ItemEncoding, bool>(),
            "stream"_a, "transfer_syntax"_a,
            "item_encoding"_a=Writer::ItemEncoding::ExplicitLength,
            "use_group_length"_a=false)
        .def("write_data_set", &Writer::write_data_set)
        .def("write_tag", &Writer::write_tag)
        .def("write_element", &Writer::write_element)
        .def_static(
            "write_file",
            [](
                std::shared_ptr<DataSet> const data_set,
                odil::wrappers::python::iostream & stream,
                std::shared_ptr<DataSet const> meta_information,
                std::string const & transfer_syntax,
                Writer::ItemEncoding item_encoding, bool use_group_length)
            {
                Writer::write_file(
                    data_set, stream, meta_information, transfer_syntax,
                    item_encoding, use_group_length);
            },
            "data_set"_a, "stream"_a,
            "meta_information"_a=std::make_shared<DataSet>(),
            "transfer_syntax"_a=registry::ExplicitVRLittleEndian,
            "item_encoding"_a=Writer::ItemEncoding::ExplicitLength,
            "use_group_length"_a=false)
        .def_static(
            "write_file",
            [](
                std::shared_ptr<DataSet> const data_set,
                std::string const & file_name,
                std::shared_ptr<DataSet const> meta_information,
                std::string const & transfer_syntax,
                Writer::ItemEncoding item_encoding, bool use_group_length)
            {
                std::ofstream stream(file_name, std::ios::binary);
                if(!stream)
                {
                    throw Exception("Could not open stream");
                }
                
                Writer::write_file(
                    data_set, stream, meta_information, transfer_syntax,
                    item_encoding, use_group_length);
            },
            "data_set"_a, "file_name"_a,
            "meta_information"_a=std::make_shared<DataSet>(),
            "transfer_syntax"_a=registry::ExplicitVRLittleEndian,
            "item_encoding"_a=Writer::ItemEncoding::ExplicitLength,
            "use_group_length"_a=false)
    ;
}
