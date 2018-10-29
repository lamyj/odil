/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/Value.h"
#include "odil/webservices/BulkData.h"

namespace
{

odil::webservices::BulkData
constructor(
    odil::Value::Binary::value_type const & data = odil::Value::Binary::value_type(),
    std::string const & type = "", std::string const & location = "")
{
    odil::webservices::BulkData bulk_data;
    bulk_data.data = data;
    bulk_data.type = type;
    bulk_data.location = location;

    return bulk_data;
}

}

void wrap_webservices_BulkData(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil::webservices;

    class_<BulkData>(m, "BulkData")
        .def(
            init(&constructor), "",
            arg("data") = odil::Value::Binary::value_type(), arg("type")="",
            arg("location")="")
        .def_readwrite("data", &BulkData::data)
        .def_readwrite("type", &BulkData::type)
        .def_readwrite("location", &BulkData::location)
    ;
}
