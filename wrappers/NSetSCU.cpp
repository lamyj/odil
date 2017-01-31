/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/NSetSCU.h"


void wrap_NSetSCU()
{
    using namespace boost::python;
    using namespace odil;

    class_<NSetSCU>("NSetSCU", init<Association &>())
        .def(
            "get_affected_sop_class",
            &NSetSCU::get_affected_sop_class,
            return_value_policy<copy_const_reference>()
        )
        .def(
            "set_affected_sop_class",
            static_cast<void(NSetSCU::*)(DataSet const &)>(&NSetSCU::set_affected_sop_class)
        )
        .def(
            "store",
            &NSetSCU::set
        )
    ;
}
