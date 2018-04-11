/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>

#include "odil/DataSet.h"
#include "odil/webservices/STOWRSRequest.h"
#include "odil/webservices/HTTPRequest.h"


boost::python::list
get_data_sets(odil::webservices::STOWRSRequest& self)
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
request_dicom(odil::webservices::STOWRSRequest& self,
                      boost::python::object data_sets,
                      odil::webservices::Selector selector,
                      odil::webservices::Representation representation
                      )
{
    odil::Value::DataSets cpp_val;
    for(int i = 0; i < boost::python::len(data_sets); ++i)
    {
        cpp_val.push_back(boost::python::extract<std::shared_ptr<odil::DataSet>>(data_sets[i]));
    }
    self.request_dicom(cpp_val, selector, representation);
}

void
wrap_webservices_STOWRSRequest()
{
    using namespace boost::python;
    using namespace odil::webservices;

    class_<STOWRSRequest>(
        "STOWRSRequest", no_init)
        .def(init<URL>((arg("base_url")=URL())))
        .def(init<HTTPRequest>())
        .def(self == self)
        .def(self != self)
        .def("get_base_url", &STOWRSRequest::get_base_url,
             return_value_policy<copy_const_reference>())
        .def("set_base_url", &STOWRSRequest::set_base_url)
        .def("get_media_type", &STOWRSRequest::get_media_type,
             return_value_policy<copy_const_reference>())
        .def("get_representation",&STOWRSRequest::get_representation,
             return_value_policy<copy_const_reference>())
        .def("get_url", &STOWRSRequest::get_url,
             return_value_policy<copy_const_reference>())
        .def("get_selector", &STOWRSRequest::get_selector,
             return_value_policy<copy_const_reference>())
        .def("get_data_sets", get_data_sets)
        .def("request_dicom", request_dicom,
             (arg("data_sets"),
              arg("selector"),
              arg("representation")
            ))
        .def("get_http_request", &STOWRSRequest::get_http_request)
    ;
}
