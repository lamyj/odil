/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/message/Response.h"

void wrap_Response()
{
    using namespace boost::python;
    using namespace odil;
    using namespace odil::message;

    class_<Response, bases<Message>>(
            "Response", init<Value::Integer, Value::Integer>())
        .def(init<Message const &>())
        .def(
            "get_message_id_being_responded_to",
            &Response::get_message_id_being_responded_to,
            return_value_policy<copy_const_reference>())
        .def(
            "set_message_id_being_responded_to",
            &Response::set_message_id_being_responded_to)
        .def(
            "get_status", &Response::get_status,
            return_value_policy<copy_const_reference>())
        .def("set_status", &Response::set_status)
        .def(
            "is_pending",
            static_cast<bool (Response::*)() const>(&Response::is_pending))
        .def(
            "is_warning",
            static_cast<bool (Response::*)() const>(&Response::is_warning))
        .def(
            "is_failure",
            static_cast<bool (Response::*)() const>(&Response::is_failure))
    ;
}
