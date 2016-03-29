/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/EchoSCU.h"

void wrap_EchoSCU()
{
    using namespace boost::python;
    using namespace odil;

    class_<EchoSCU>("EchoSCU", init<Association &>())
        .def(
            "get_affected_sop_class",
            &EchoSCU::get_affected_sop_class,
            return_value_policy<copy_const_reference>()
        )
        .def(
            "set_affected_sop_class",
            &EchoSCU::set_affected_sop_class
        )
        .def(
            "echo", 
            &EchoSCU::echo
        )
    ;
}
