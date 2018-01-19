/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>

#include "odil/Value.h"
#include "odil/webservices/BulkData.h"

namespace
{
boost::shared_ptr<odil::webservices::BulkData>
constructor(
        odil::Value::Binary::value_type const & data = odil::Value::Binary::value_type(),
        std::string const & type = "",
        std::string const & location = ""
        )
{
    boost::shared_ptr<odil::webservices::BulkData> bulk_data(new odil::webservices::BulkData);
    bulk_data->data = data;
    bulk_data->type = type;
    bulk_data->location = location;

    return bulk_data;
}

}

void wrap_webservices_BulkData()
{
    using namespace boost::python;
    using namespace odil::webservices;

    class_<BulkData>("BulkData", no_init)
        .def(
            "__init__",
            make_constructor(constructor, default_call_policies(),
            ( arg("data") = odil::Value::Binary::value_type(), arg("type")="", arg("location")=""))
            )
        .def_readwrite("data", &BulkData::data)
        .def_readwrite("type", &BulkData::type)
        .def_readwrite("location", &BulkData::location)
    ;
}
