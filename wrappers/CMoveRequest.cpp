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
    using namespace odil::message;

    class_<CMoveRequest, bases<Request>>("CMoveRequest", no_init)
        .add_property(
            "affected_sop_class_uid", 
            make_function(
                &CMoveRequest::get_affected_sop_class_uid, 
                return_value_policy<copy_const_reference>()),
            &CMoveRequest::set_affected_sop_class_uid)
        .add_property(
            "priority", 
            make_function(
                &CMoveRequest::get_priority, 
                return_value_policy<copy_const_reference>()),
            &CMoveRequest::set_priority)
        .add_property(
            "move_destination", 
            make_function(
                &CMoveRequest::get_move_destination, 
                return_value_policy<copy_const_reference>()),
            &CMoveRequest::set_move_destination)
    ;
}
