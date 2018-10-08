/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/WADORSRequest.h"

void wrap_webservices_Selector(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil::webservices;

    class_<Selector>(m, "Selector")
        .def(
            init<std::map<std::string, std::string>, std::vector<int>>(),
            "",
            arg("selector") = std::map<std::string, std::string>(),
            arg("frames")=std::vector<int>())
        //"selector : {\"studies\" : \"StudiesInstanceUID\", \"series\" : \"SeriesInstanceUID\", \"instances\" : \"SOPInstanceUID\"} "))
        .def("get_path", &Selector::get_path)
        .def("is_study_present", &Selector::is_study_present)
        .def("is_series_present", &Selector::is_series_present)
        .def("is_instance_present", &Selector::is_instance_present)
        .def("get_study", &Selector::get_study, return_value_policy::copy)
        .def("get_series", &Selector::get_series, return_value_policy::copy)
        .def("get_instance", &Selector::get_instance, return_value_policy::copy)
        .def("get_frames", &Selector::get_frames, return_value_policy::copy)
        .def("set_study", &Selector::set_study, return_value_policy::copy)
        .def("set_series", &Selector::set_series, return_value_policy::copy)
        .def("set_instance", &Selector::set_instance, return_value_policy::copy)
        .def(
            "set_frames", &Selector::set_frames,
            return_value_policy::reference_internal)
        .def(self == self)
        .def(self != self)
    ;
}
