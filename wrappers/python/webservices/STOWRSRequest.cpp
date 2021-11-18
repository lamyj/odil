/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <algorithm>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "odil/DataSet.h"
#include "odil/webservices/STOWRSRequest.h"
#include "odil/webservices/HTTPRequest.h"

namespace
{

void
request_dicom(
    odil::webservices::STOWRSRequest& self, pybind11::sequence data_sets,
    odil::webservices::Selector const & selector,
    odil::webservices::Representation representation)
{
    odil::Value::DataSets cpp_val(pybind11::len(data_sets));
    std::transform(
        data_sets.begin(), data_sets.end(), cpp_val.begin(), 
        [](pybind11::handle const & h) 
        { return h.cast<std::shared_ptr<odil::DataSet>>(); });
    self.request_dicom(cpp_val, selector, representation);
}

}

void
wrap_webservices_STOWRSRequest(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    using namespace odil::webservices;

    class_<STOWRSRequest>(m, "STOWRSRequest")
        .def(init<URL>(), "", arg("base_url")=URL())
        .def(init<HTTPRequest>())
        .def(self == self)
        .def(self != self)
        .def("get_base_url", &STOWRSRequest::get_base_url)
        .def("set_base_url", &STOWRSRequest::set_base_url)
        .def("get_media_type", &STOWRSRequest::get_media_type)
        .def("get_representation",&STOWRSRequest::get_representation)
        .def("get_url", &STOWRSRequest::get_url)
        .def("get_selector", &STOWRSRequest::get_selector)
        .def(
            "get_data_sets",
            static_cast<Value::DataSets const & (STOWRSRequest::*)() const>(
                &STOWRSRequest::get_data_sets))
        .def("request_dicom", request_dicom)
        .def("get_http_request", &STOWRSRequest::get_http_request)
    ;
}
