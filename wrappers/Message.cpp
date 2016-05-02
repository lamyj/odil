/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/DataSet.h"
#include "odil/message/Message.h"

void wrap_Message()
{
    using namespace boost::python;
    using namespace odil;
    using namespace odil::message;

    class_<Message>("Message", init<>())
        .def(init<DataSet const &>())
        .def(init<DataSet const &, DataSet const &>())
        .def(
            "get_command_set", &Message::get_command_set,
            return_value_policy<copy_const_reference>())
        .def("has_data_set", &Message::has_data_set)
        .def(
            "get_data_set", &Message::get_data_set,
            return_value_policy<copy_const_reference>())
        .def(
            "get_command_field", &Message::get_command_field,
            return_value_policy<copy_const_reference>())
        .def("set_command_field", &Message::set_command_field)
    ;
}
