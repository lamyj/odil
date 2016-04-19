/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>

#include <boost/python.hpp>

#include "odil/message/CFindRequest.h"
#include "odil/FindSCP.h"

#include "PythonDataSetGenerator.h"

namespace
{

void set_generator(
    odil::FindSCP & find_scp, boost::python::object const & python_generator)
{
    auto cpp_generator = 
        std::make_shared<PythonDataSetGenerator<odil::message::CFindRequest>>(
            python_generator);
    find_scp.set_generator(cpp_generator);
}

}

void wrap_FindSCP()
{
    boost::python::class_<odil::FindSCP>(
            "FindSCP", boost::python::init<odil::Association &>())
        .def("set_generator", &set_generator)
        .def("__call__", &odil::FindSCP::operator())
    ;
}
