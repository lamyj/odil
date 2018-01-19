/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <fstream>
#include <string>

#include <boost/python.hpp>

#include "odil/Exception.h"
#include "odil/Writer.h"

namespace
{

void
write(
    odil::DataSet const & data_set, std::string const & path,
    odil::DataSet const & meta_information = odil::DataSet(),
    std::string const & transfer_syntax = odil::registry::ExplicitVRLittleEndian,
    odil::Writer::ItemEncoding item_encoding=odil::Writer::ItemEncoding::ExplicitLength,
    bool use_group_length=false
)
{
    std::ofstream stream(path);
    if(!stream)
    {
        throw odil::Exception("Could not open "+path);
    }

    odil::Writer::write_file(data_set, stream, meta_information, 
        transfer_syntax, item_encoding, use_group_length);
}

}

void wrap_write()
{
    using namespace boost::python;
    using namespace odil;

    def(
        "write", 
        static_cast<
            void (*)(
                DataSet const &, std::string const &, DataSet const &, 
                std::string const &, Writer::ItemEncoding, bool)
        >(write),
        (
            arg("data_set"), arg("path"), 
            arg("meta_information")=odil::DataSet(), 
            arg("transfer_syntax")=odil::registry::ExplicitVRLittleEndian,
            arg("item_encoding")=odil::Writer::ItemEncoding::ExplicitLength,
            arg("use_group_length")=false
        )
    );
}

