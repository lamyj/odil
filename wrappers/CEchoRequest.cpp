/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/message/CEchoRequest.h"

void wrap_CEchoRequest()
{
    using namespace boost::python;
    using namespace odil::message;

    class_<CEchoRequest, bases<Request>>("CEchoRequest", no_init)
        .add_property(
            "affected_sop_class_uid", 
            make_function(
                &CEchoRequest::get_affected_sop_class_uid, 
                return_value_policy<copy_const_reference>()),
            &CEchoRequest::set_affected_sop_class_uid)
    ;
}
