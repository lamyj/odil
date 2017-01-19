/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
/*
#include <boost/python.hpp>

#include "odil/NSetSCU.h"

namespace
{

void 
set_callback(odil::NSetSCU & SCU, boost::python::object const & f)
{
    SCU.set_callback(
        [f](odil::message::NSetRequest const & message) 
        { 
            return boost::python::call<odil::Value::Integer>(f.ptr(), message);
        }
    );
}

}

void wrap_NSetSCU()
{
    using namespace boost::python;
    using namespace odil;

    class_<NSetSCU>("NSetSCU", init<Association &>())
        .def("set_callback", &set_callback)
        .def("__call__", &NSetSCU::operator())
    ;
}


*/
