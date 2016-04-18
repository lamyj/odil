/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/message/Request.h"

void wrap_Request()
{
    using namespace boost::python;
    using namespace odil::message;

    class_<Request, bases<Message>>("Request", no_init)
        .add_property(
            "message_id", 
            make_function(
                &Request::get_message_id, 
                return_value_policy<copy_const_reference>()),
            &Request::set_message_id)
    ;
}
