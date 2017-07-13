/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/message/CEchoResponse.h"

void wrap_CEchoResponse()
{
    using namespace boost::python;
    using namespace odil;
    using namespace odil::message;

    class_<CEchoResponse, bases<Response>>(
            "CEchoResponse", init<Value::Integer,Value::Integer, Value::String const &>())
        .def(init<Message const &>())
        .def(
            "get_affected_sop_class_uid",
            &CEchoResponse::get_affected_sop_class_uid,
            return_value_policy<copy_const_reference>())
        .def(
            "set_affected_sop_class_uid",
            &CEchoResponse::set_affected_sop_class_uid)
    ;
}
