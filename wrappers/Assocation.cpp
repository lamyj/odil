/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/Association.h"

void wrap_Association()
{
    using namespace boost::python;
    using namespace odil;

    scope association_scope = class_<Association>("Association", init<>())
        .def("get_peer_host", &Association::get_peer_host,
            return_value_policy<copy_const_reference>())
        .def("set_peer_host", &Association::set_peer_host)
        .def("get_peer_port", &Association::get_peer_port)
        .def("set_peer_port", &Association::set_peer_port)
        .def(
            "get_parameters", 
            &Association::get_parameters, 
            return_value_policy<reference_existing_object>()
        )
        .def(
            "set_parameters", 
            &Association::set_parameters, 
            return_value_policy<reference_existing_object>()
        )
        .def(
            "update_parameters", 
            &Association::update_parameters, 
            return_value_policy<reference_existing_object>()
        )
        // TCP timeout
        // Message timeout
        .def("is_associated", &Association::is_associated)
        .def("associate", &Association::associate)
        // Receive association
        //.def("reject", &Association::reject)
        .def("release", &Association::release)
        .def("abort", &Association::abort)
        // Receive message
        // Send message
        .def("next_message_id", &Association::next_message_id)
    ;

    enum_<Association::Result>("Result")
        .value("Accepted", Association::Accepted)
        .value("RejectedPermanent", Association::RejectedPermanent)
        .value("RejectedTransient", Association::RejectedTransient)
    ;
}

