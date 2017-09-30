/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <vector>

#include <boost/python.hpp>

#include "odil/DataSet.h"
#include "odil/webservices/BulkData.h"
#include "odil/webservices/WADORSResponse.h"
#include "odil/Value.h"

boost::python::list
get_data_sets(odil::webservices::WADORSResponse& self)
{
    boost::python::list python_ds;
    auto const cpp_val = self.get_data_sets();
    for (auto const ds : cpp_val)
    {
        python_ds.append(ds);
    }
    return python_ds;
}

void
set_data_sets(odil::webservices::WADORSResponse& self,
                   boost::python::object data_sets)
{
    odil::Value::DataSets odil_ds;
    for(int i = 0; i < boost::python::len(data_sets) ; ++i)
    {
        odil_ds.push_back(boost::python::extract<odil::DataSet>(data_sets[i]));
    }
    self.set_data_sets(odil_ds);
}

boost::python::list
get_bulk_data(odil::webservices::WADORSResponse& self)
{
    auto const & cpp_val = self.get_bulk_data();
    boost::python::list python_val;
    for (auto const & bulk : cpp_val)
    {
        python_val.append(bulk);
    }
    return python_val;
}

void
set_bulk_data(odil::webservices::WADORSResponse& self,
                   boost::python::object bulk_data)
{
    std::vector<odil::webservices::BulkData> cpp_val;
    for (int i = 0; i < boost::python::len(bulk_data); ++i)
    {
        cpp_val.push_back(boost::python::extract<odil::webservices::BulkData>(bulk_data[i]));
    }
    self.set_bulk_data(cpp_val);
}

void
wrap_webservices_WADORSResponse()
{
    using namespace boost::python;
    using namespace odil;
    using namespace odil::webservices;

    class_<WADORSResponse>("WADORSResponse", init<>())
        .def(init<HTTPResponse>())
        .def("get_data_sets", get_data_sets)
        .def("set_data_sets", set_data_sets)
        .def("get_bulk_data", get_bulk_data)
        .def("set_bulk_data", set_bulk_data)
        // TODO: bulk_data
        .def("is_partial", &WADORSResponse::is_partial)
        .def("set_partial", &WADORSResponse::set_partial)
        .def("get_type", &WADORSResponse::get_type)
        .def(
            "get_representation", &WADORSResponse::get_representation,
            return_value_policy<copy_const_reference>())
        .def("respond_dicom", &WADORSResponse::respond_dicom)
        .def("respond_bulk_data", &WADORSResponse::respond_bulk_data)
        .def("respond_pixel_data", &WADORSResponse::respond_pixel_data)
        .def("get_http_response", &WADORSResponse::get_http_response)
        .def(self == self)
        .def(self != self)
    ;
}
