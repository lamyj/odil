/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <memory>

#include <boost/python.hpp>

#include "odil/message/CFindRequest.h"
#include "odil/FindSCP.h"

#include "DataSetGeneratorWrapper.h"

namespace
{

void set_generator(
    odil::FindSCP & find_scp, 
    DataSetGeneratorWrapper<odil::FindSCP::DataSetGenerator> generator)
{
    auto cpp_generator = 
        std::make_shared<
            DataSetGeneratorWrapper<odil::FindSCP::DataSetGenerator>
        >(generator);
    find_scp.set_generator(cpp_generator);
}

}

void wrap_FindSCP()
{
    using namespace boost::python;
    using namespace odil;
    
    scope find_scp_scope = class_<FindSCP>("FindSCP", init<Association &>())
        .def("set_generator", &set_generator)
        .def(
            "__call__",
            static_cast<
                void (FindSCP::*)(std::shared_ptr<message::Message>)
            >(&FindSCP::operator())
        )
    ;
    
    class_<
        DataSetGeneratorWrapper<FindSCP::DataSetGenerator>, 
        boost::noncopyable
    >("DataSetGenerator", init<>());
}
