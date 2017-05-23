/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/WADORSRequest.h"

void wrap_webservices_Selector()
{
    using namespace boost::python;
    using namespace odil::webservices;

    class_<Selector>("Selector", init<>())
        .def(
            init<std::string, std::string, std::string, std::vector<int>>((
                arg("study"), arg("series")="",
                arg("instance")="", arg("frames")=std::vector<int>())))
        .def("get_path", &Selector::get_path)
        .def("is_study_present", &Selector::is_study_present)
        .def("is_series_present", &Selector::is_series_present)
        .def("is_instance_present", &Selector::is_instance_present)
        .def(
            "get_study", &Selector::get_study,
            return_value_policy<copy_const_reference>())
        .def(
            "get_series", &Selector::get_series,
            return_value_policy<copy_const_reference>())
        .def(
            "get_instance", &Selector::get_instance,
            return_value_policy<copy_const_reference>())
        .def(
            "get_frames", &Selector::get_frames,
            return_value_policy<copy_const_reference>())
        .def(
            "set_study",
            &Selector::set_study,
            return_value_policy<reference_existing_object>()
        )
        .def(
            "set_series",
            &Selector::set_series,
            return_value_policy<reference_existing_object>()
        )
        .def(
            "set_instance",
            &Selector::set_instance,
            return_value_policy<reference_existing_object>()
        )
        .def(
            "set_frames",
            &Selector::set_frames,
            return_value_policy<reference_existing_object>()
        )
        .def(self == self)
        .def(self != self)
    ;
}
