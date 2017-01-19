/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/message/NSetRequest.h"

void wrap_NSetRequest()
{
    using namespace boost::python;
    using namespace odil;
    using namespace odil::message;

    class_<NSetRequest, bases<Request>>(
            "NSetRequest",
            init<
                Value::Integer, Value::String const &, Value::String const &,
                Value::Integer, DataSet const &
            >())
        .def(init<Message>())
        .def(
            "get_requested_sop_class_uid",
            &NSetRequest::get_requested_sop_class_uid,
            return_value_policy<copy_const_reference>())
        .def(
            "set_requested_sop_class_uid",
            &NSetRequest::set_requested_sop_class_uid)
        .def(
            "get_requested_sop_instance_uid",
            &NSetRequest::get_requested_sop_instance_uid,
            return_value_policy<copy_const_reference>())
        .def(
            "set_requested_sop_instance_uid",
            &NSetRequest::set_requested_sop_instance_uid)
        .def(
            "has_command_data_set_type",
            &NSetRequest::has_command_data_set_type)
        .def(
            "get_command_data_set_type",
            &NSetRequest::get_command_data_set_type,
            return_value_policy<copy_const_reference>())
        .def(
            "set_command_data_set_type",
            &NSetRequest::set_command_data_set_type)
        .def("has_command_field",
             &NSetRequest::set_command_field)
        .def(
            "get_command_field",
            &NSetRequest::get_command_field,
            return_value_policy<copy_const_reference>())
        .def(
            "set_command_field",
            &NSetRequest::set_command_field)
        .def(
            "has_command_group_length",
            &NSetRequest::has_command_group_length)
        .def(
            "get_command_group_length",
            &NSetRequest::get_command_group_length,
            return_value_policy<copy_const_reference>())
        .def(
            "set_command_group_length",
            &NSetRequest::set_command_group_length)
    ;
}
