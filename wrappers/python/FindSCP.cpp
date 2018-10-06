/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "odil/message/CFindRequest.h"
#include "odil/FindSCP.h"

#include "DataSetGeneratorWrapper.h"

void wrap_FindSCP(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    
    auto find_scp_scope = class_<FindSCP>(m, "FindSCP")
        .def(init<Association &>())
        .def("set_generator", &FindSCP::set_generator)
        .def(
            "__call__",
            static_cast<
                void (FindSCP::*)(std::shared_ptr<message::Message>)
            >(&FindSCP::operator()))
    ;
    
    class_<
                FindSCP::DataSetGenerator,
                DataSetGeneratorWrapper<FindSCP::DataSetGenerator>, // trampoline
                std::shared_ptr<FindSCP::DataSetGenerator> // holder
            >(find_scp_scope, "DataSetGenerator")
        .def(init<>())
        .def("initialize", &FindSCP::DataSetGenerator::initialize)
        .def("done", &FindSCP::DataSetGenerator::done)
        .def("next", &FindSCP::DataSetGenerator::next)
        .def("get", &FindSCP::DataSetGenerator::get)
    ;
}
