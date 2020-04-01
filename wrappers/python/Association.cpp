/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <pybind11/pybind11.h>

#include "odil/Association.h"

#include "opaque_types.h"
#include "type_casters.h"

namespace
{

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

float get_tcp_timeout(odil::Association const& association)
{
    return association.get_tcp_timeout().total_microseconds()/1000000.f;
}

void set_tcp_timeout(odil::Association& association, float seconds)
{
    association.set_tcp_timeout(
        boost::posix_time::microseconds(int(seconds*1000000.f)));
}

}

void wrap_Association(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    auto association_scope = class_<Association>(m, "Association")
        .def(init<>())
        .def("get_peer_host", &Association::get_peer_host)
        .def("set_peer_host", &Association::set_peer_host)
        .def("get_peer_port", &Association::get_peer_port)
        .def("set_peer_port", &Association::set_peer_port)
        .def(
            "get_parameters", &Association::get_parameters,
            return_value_policy::reference_internal)
        .def("set_parameters", &Association::set_parameters)
        .def(
            "update_parameters", &Association::update_parameters,
            return_value_policy::reference_internal)
        .def(
            "get_negotiated_parameters", &Association::get_negotiated_parameters,
            return_value_policy::reference_internal)
        .def("get_tcp_timeout", &get_tcp_timeout)
        .def("set_tcp_timeout", &set_tcp_timeout)
        .def("is_associated", &Association::is_associated)
        .def("associate", &Association::associate)
        .def("receive_association", &receive_association)
        //.def("reject", &Association::reject)
        .def("release", &Association::release)
        .def("abort", &Association::abort)
        .def("receive_message", &Association::receive_message)
        .def("next_message_id", &Association::next_message_id)
        .def("send_message", &Association::send_message)
    ;

    enum_<Association::Result>(association_scope, "Result")
        .value("Accepted", Association::Accepted)
        .value("RejectedPermanent", Association::RejectedPermanent)
        .value("RejectedTransient", Association::RejectedTransient)
    ;

    register_exception<AssociationReleased>(
        m, "AssociationReleased", m.attr("Exception").ptr());
    register_exception<AssociationAborted>(
        m, "AssociationAborted", m.attr("Exception").ptr());
}
