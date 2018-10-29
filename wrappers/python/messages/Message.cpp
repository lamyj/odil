/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/DataSet.h"
#include "odil/message/Message.h"

void wrap_Message(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    using namespace odil::message;

    auto message_scope = class_<Message, std::shared_ptr<Message>>(m, "Message")
        .def(init<std::shared_ptr<DataSet>>())
        .def(init<std::shared_ptr<DataSet>, std::shared_ptr<DataSet>>())
        .def("get_command_set", &Message::get_command_set)
        .def("has_data_set", &Message::has_data_set)
        .def(
            "get_data_set",
            static_cast<std::shared_ptr<DataSet const> (Message::*)() const>(&Message::get_data_set))
        .def(
            "get_command_field", &Message::get_command_field,
            return_value_policy::reference_internal)
        .def("set_command_field", &Message::set_command_field)
    ;

    enum_<Message::Command::Type>(message_scope, "Command")
        .value("C_STORE_RQ", Message::Command::Type::C_STORE_RQ)
        .value("C_STORE_RSP", Message::Command::Type::C_STORE_RSP)
        .value("C_FIND_RQ", Message::Command::Type::C_FIND_RQ)
        .value("C_FIND_RSP", Message::Command::Type::C_FIND_RSP)
        .value("C_CANCEL_RQ", Message::Command::Type::C_CANCEL_RQ)
        .value("C_GET_RQ", Message::Command::Type::C_GET_RQ)
        .value("C_GET_RSP", Message::Command::Type::C_GET_RSP)
        .value("C_MOVE_RQ", Message::Command::Type::C_MOVE_RQ)
        .value("C_MOVE_RSP", Message::Command::Type::C_MOVE_RSP)
        .value("C_ECHO_RQ", Message::Command::Type::C_ECHO_RQ)
        .value("C_ECHO_RSP", Message::Command::Type::C_ECHO_RSP)
        .value("N_EVENT_REPORT_RQ", Message::Command::Type::N_EVENT_REPORT_RQ)
        .value("N_EVENT_REPORT_RSP", Message::Command::Type::N_EVENT_REPORT_RSP)
        .value("N_GET_RQ", Message::Command::Type::N_GET_RQ)
        .value("N_GET_RSP", Message::Command::Type::N_GET_RSP)
        .value("N_SET_RQ", Message::Command::Type::N_SET_RQ)
        .value("N_SET_RSP", Message::Command::Type::N_SET_RSP)
        .value("N_ACTION_RQ", Message::Command::Type::N_ACTION_RQ)
        .value("N_ACTION_RSP", Message::Command::Type::N_ACTION_RSP)
        .value("N_CREATE_RQ", Message::Command::Type::N_CREATE_RQ)
        .value("N_CREATE_RSP", Message::Command::Type::N_CREATE_RSP)
        .value("N_DELETE_RQ", Message::Command::Type::N_DELETE_RQ)
        .value("N_DELETE_RSP", Message::Command::Type::N_DELETE_RSP)
    ;
}

