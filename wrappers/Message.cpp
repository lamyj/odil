/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/message/Message.h"

void wrap_Message()
{
    using namespace boost::python;
    using namespace odil::message;

    class_<Message>("Message", no_init)
        .add_property(
            "command_field", 
            make_function(
                &Message::get_command_field, 
                return_value_policy<copy_const_reference>()),
            &Message::set_command_field)
    ;
}
