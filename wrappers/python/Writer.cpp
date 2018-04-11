/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <ostream>

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include <odil/registry.h>
#include <odil/Writer.h>

#include "streambuf.h"

namespace
{

// WARNING: when using odil::Writer::ItemEncoding instead of int and static_cast,
// "import odil" will fail with TypeError: No to_python (by-value) converter found for C++ type: odil::Writer::ItemEncoding
boost::shared_ptr<odil::Writer>
create_Writer_1(
    odil::wrappers::python::iostream & stream,
    odil::ByteOrdering byte_ordering, bool explicit_vr,
    int item_encoding, bool use_group_length)
{
    odil::Writer * writer = new odil::Writer(
        stream, byte_ordering, explicit_vr,
        static_cast<odil::Writer::ItemEncoding>(item_encoding),
        use_group_length);

    // Old versions of Boost.Python (Debian 7, Ubuntu 12.04) do not like
    // std::shared_ptr
    return boost::shared_ptr<odil::Writer>(writer);
}

boost::shared_ptr<odil::Writer>
create_Writer_2(
    odil::wrappers::python::iostream & stream,
    std::string const & transfer_syntax,
    int item_encoding, bool use_group_length)
{
    odil::Writer * writer = new odil::Writer(
        stream, transfer_syntax,
        static_cast<odil::Writer::ItemEncoding>(item_encoding),
        use_group_length);

    // Old versions of Boost.Python (Debian 7, Ubuntu 12.04) do not like
    // std::shared_ptr
    return boost::shared_ptr<odil::Writer>(writer);
}

void write_file(
    std::shared_ptr<odil::DataSet const> data_set,
    odil::wrappers::python::iostream & stream,
    std::shared_ptr<odil::DataSet const> meta_information,
    std::string const & transfer_syntax, int item_encoding,
    bool use_group_length)
{
    odil::Writer::write_file(
        data_set, stream, meta_information, transfer_syntax,
        static_cast<odil::Writer::ItemEncoding>(item_encoding),
        use_group_length);
}

}

void wrap_Writer()
{
    using namespace boost::python;
    using namespace odil;

    scope Writer_scope = class_<Writer>("Writer", no_init)
        .def_readwrite("byte_ordering", &Writer::byte_ordering)
        .def_readwrite("explicit_vr", &Writer::explicit_vr)
        .def_readwrite("item_encoding", &Writer::item_encoding)
        .def_readwrite("use_group_length", &Writer::use_group_length)
        .def(
            "__init__", make_constructor(
                create_Writer_1, default_call_policies(), (
                    arg("stream"), arg("byte_ordering"), arg("explicit_vr"),
                    arg("item_encoding")=static_cast<int>(Writer::ItemEncoding::ExplicitLength),
                    arg("use_group_length")=false)))
        .def(
            "__init__", make_constructor(
                create_Writer_2, default_call_policies(), (
                arg("stream"), arg("transfer_syntax"),
                arg("item_encoding")=static_cast<int>(Writer::ItemEncoding::ExplicitLength),
                arg("use_group_length")=false)))
        .def("write_data_set", &Writer::write_data_set)
        .def("write_tag", &Writer::write_tag)
        .def("write_element", &Writer::write_element)
        .def(
            "write_file", write_file,
            (
                arg("data_set"), arg("stream"),
                arg("meta_information")=DataSet(),
                arg("transfer_syntax")=registry::ExplicitVRLittleEndian,
                arg("item_encoding")=static_cast<int>(Writer::ItemEncoding::ExplicitLength),
                arg("use_group_length")=false))
        .staticmethod("write_file")
    ;

    enum_<Writer::ItemEncoding>("ItemEncoding")
        .value("ExplicitLength", Writer::ItemEncoding::ExplicitLength)
        .value("UndefinedLength", Writer::ItemEncoding::UndefinedLength)
    ;

}
