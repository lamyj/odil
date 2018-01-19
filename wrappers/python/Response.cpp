/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

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

void wrap_ResponseStatus()
{
    using namespace boost::python;
    using namespace odil;
    using namespace odil::message;

    enum_< Response::Status >("response_status")
            .value("Success", Response::Status::Success )
            .value("Cancel", Response::Status::Cancel )
            .value("Pending", Response::Status::Pending )
            .value("AttributeListError", Response::Status::AttributeListError )
            .value("AttributeValueOutOfRange", Response::Status::AttributeValueOutOfRange )
            .value("SOPClassNotSupported", Response::Status::SOPClassNotSupported )
            .value("ClassInstanceConflict", Response::Status::ClassInstanceConflict )
            .value("DuplicateSOPInstance", Response::Status::DuplicateSOPInstance )
            .value("DuplicateInvocation", Response::Status::DuplicateInvocation )
            .value("InvalidArgumentValue", Response::Status::InvalidArgumentValue )
            .value("InvalidAttributeValue", Response::Status::InvalidAttributeValue )
            .value("InvalidObjectInstance", Response::Status::InvalidObjectInstance )
            .value("MissingAttribute", Response::Status::MissingAttribute )
            .value("MissingAttributeValue", Response::Status::MissingAttributeValue )
            .value("MistypedArgument", Response::Status::MistypedArgument )
            .value("NoSuchArgument", Response::Status::NoSuchArgument )
            .value("NoSuchAttribute", Response::Status::NoSuchAttribute )
            .value("NoSuchEventType", Response::Status::NoSuchEventType )
            .value("NoSuchSOPInstance", Response::Status::NoSuchSOPInstance )
            .value("NoSuchSOPClass", Response::Status::NoSuchSOPClass )
            .value("ProcessingFailure", Response::Status::ProcessingFailure )
            .value("ResourceLimitation", Response::Status::ResourceLimitation )
            .value("UnrecognizedOperation", Response::Status::UnrecognizedOperation )
            .value("NoSuchActionType", Response::Status::NoSuchActionType)
    ;
}
