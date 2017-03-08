/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/message/CMoveRequest.h"

void wrap_CMoveRequest()
{
    using namespace boost::python;
    using namespace odil;
    using namespace odil::message;

    class_<CMoveRequest, bases<Request>>(
            "CMoveRequest",
            init<
                Value::Integer, Value::String const &, Value::Integer,
                Value::String const &, DataSet const &
            >())
        .def(init<Message>())
        .def(
            "get_affected_sop_class_uid",
            &CMoveRequest::get_affected_sop_class_uid,
            return_value_policy<copy_const_reference>())
        .def(
            "set_affected_sop_class_uid",
            &CMoveRequest::set_affected_sop_class_uid)
        .def(
            "get_priority", &CMoveRequest::get_priority,
            return_value_policy<copy_const_reference>())
        .def("set_priority", &CMoveRequest::set_priority)
        .def(
            "get_move_destination", &CMoveRequest::get_move_destination,
            return_value_policy<copy_const_reference>())
        .def("set_move_destination", &CMoveRequest::set_move_destination)
    ;
}
