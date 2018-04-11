/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>

#include "odil/webservices/STOWRSResponse.h"

void
wrap_webservices_STOWRSResponse()
{

    using namespace odil::webservices;
    using namespace boost::python;

    class_<STOWRSResponse>(
        "STOWRSResponse")
        .def(init<HTTPResponse>())
        .def(self == self)
        .def(self != self)
        .def("set_store_instance_responses", &STOWRSResponse::set_store_instance_responses)
        .def("get_store_instance_responses", &STOWRSResponse::get_store_instance_responses)
        .def("get_media_type", &STOWRSResponse::get_media_type,
             return_value_policy<copy_const_reference>())
        .def("set_representation", &STOWRSResponse::set_representation)
        .def("get_representation", &STOWRSResponse::get_representation,
             return_value_policy<copy_const_reference>())
        .def("set_warning", &STOWRSResponse::set_warning)
        .def("is_status_warning", &STOWRSResponse::is_status_warning)
        .def("set_failure_code", &STOWRSResponse::set_failure_code)
        .def("get_failure_code", &STOWRSResponse::get_failure_code)
        .def("set_reason", &STOWRSResponse::set_reason)
        .def("get_reason", &STOWRSResponse::get_reason,
             return_value_policy<copy_const_reference>())
        .def("get_http_response", &STOWRSResponse::get_http_response)
        ;
}
