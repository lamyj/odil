/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/NSetSCP.h"

#include <boost/python.hpp>

namespace
{

void
set_callback( odil::NSetSCP& scp, boost::python::object const& f)
{
    scp.set_callback(
        [f](odil::message::NSetRequest const& message)
        {
            return boost::python::call<odil::Value::Integer>(f.ptr(), message);
        }
        );
}
}

void wrap_NSetSCP()
{
    using namespace boost::python;
    using namespace odil;

    class_<NSetSCP >("NSetSCP", init<Association&>() )
    .def (init<Association&, NSetSCP::Callback&>())
    .def("set_callback", &set_callback)
    .def("__call__", &NSetSCP::operator())
    ;
}
