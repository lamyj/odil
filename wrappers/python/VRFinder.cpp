/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>

#include "odil/VRFinder.h"

namespace
{

odil::VR VRFinder_call(
    odil::VRFinder const & self,
    odil::Tag const & tag, std::shared_ptr<odil::DataSet> data_set,
    std::string const & transfer_syntax)
{
    return self(tag, data_set, transfer_syntax);
}

}

void wrap_VRFinder()
{
    using namespace boost::python;
    using namespace odil;
    
    class_<VRFinder>("VRFinder", init<>())
        .def("__call__", VRFinder_call)
    ;
}
