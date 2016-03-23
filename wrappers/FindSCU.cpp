/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "odil/FindSCU.h"

void wrap_FindSCU()
{
    using namespace boost::python;
    using namespace odil;

    class_<FindSCU>("FindSCU", init<Association &>())
        // Find with callback
        .def(
            "find", 
            static_cast<
                std::vector<DataSet> (FindSCU::*)(DataSet const &) const
            >(&FindSCU::find)
        )
        .def("set_affected_sop_class", &FindSCU::set_affected_sop_class)
    ;
}
