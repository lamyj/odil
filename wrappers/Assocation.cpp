/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "exception_factory.h"

#include "odil/Association.h"

#include <boost/asio.hpp>
#include <boost/python.hpp>

namespace
{

PyObject* wrapped_AssociationReleased;
PyObject* wrapped_AssociationAborted;

void receive_association(
    odil::Association& association, std::string protocol, unsigned short port)
{
    if(protocol == "v4")
    {
        association.receive_association(boost::asio::ip::tcp::v4(), port);
    }
    else if (protocol == "v6")
    {
        association.receive_association(boost::asio::ip::tcp::v6(), port);
    }
}

void released_translator(odil::AssociationReleased const& e)
{
    PyErr_SetString(wrapped_AssociationReleased, e.what());
}

void aborted_translator(odil::AssociationAborted const& e)
{
    PyErr_SetString(wrapped_AssociationAborted, e.what());
}

float get_tcp_timeout(odil::Association const& association)
{
    return association.get_tcp_timeout().total_microseconds()/1000000.;
}

void set_tcp_timeout(odil::Association& association, float seconds)
{
    association.set_tcp_timeout(
        boost::posix_time::microseconds(seconds*1000000.));
}

}

void wrap_Association()
{
    using namespace boost::python;
    using namespace odil;

    object wrapped_exception = scope().attr("Exception");

    wrapped_AssociationReleased = exception_factory(
        "AssociationReleased", wrapped_exception.ptr());
    register_exception_translator<AssociationReleased>(released_translator);

    wrapped_AssociationAborted = exception_factory(
        "AssociationAborted", wrapped_exception.ptr());
    register_exception_translator<AssociationAborted>(aborted_translator);

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
                              .def(
        "get_negotiated_parameters",
        &Association::get_negotiated_parameters,
        return_value_policy<reference_existing_object>()
        )
                              .def("get_tcp_timeout", &get_tcp_timeout)
                              .def("set_tcp_timeout", &set_tcp_timeout)
                              // Message timeout
                              .def("is_associated", &Association::is_associated)
                              .def("associate", &Association::associate)
                              // Receive association
                              .def("receive_association", &receive_association)
                              //.def("reject", &Association::reject)
                              .def("release", &Association::release)
                              .def("abort", &Association::abort)
                              // Receive message
                              .def("receive_message", &Association::receive_message)
                              // Send message
                              .def("next_message_id", &Association::next_message_id)
    ;

    enum_<Association::Result>("Result")
    .value("Accepted", Association::Accepted)
    .value("RejectedPermanent", Association::RejectedPermanent)
    .value("RejectedTransient", Association::RejectedTransient)
    ;
}
