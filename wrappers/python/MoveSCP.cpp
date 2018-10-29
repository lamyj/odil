/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>

#include <pybind11/pybind11.h>

#include "odil/message/CMoveRequest.h"
#include "odil/MoveSCP.h"

#include "DataSetGeneratorWrapper.h"

namespace
{

class DataSetGeneratorWrapperMove: 
    public DataSetGeneratorWrapper<odil::MoveSCP::DataSetGenerator>
{
public:
    DataSetGeneratorWrapperMove()
    : DataSetGeneratorWrapper<odil::MoveSCP::DataSetGenerator>()
    {
        // Nothing else
    }
    
    virtual ~DataSetGeneratorWrapperMove() override
    {
        // Nothing to do.
    }
    
    virtual unsigned int count() const override
    {
        PYBIND11_OVERLOAD_PURE(unsigned int, odil::MoveSCP::DataSetGenerator, count, );
    }
    
    virtual odil::Association 
    get_association(std::shared_ptr<odil::message::CMoveRequest const> request) const override
    {
        PYBIND11_OVERLOAD_PURE(
            odil::Association, odil::MoveSCP::DataSetGenerator, get_association,
            request);
    }
};

}

void wrap_MoveSCP(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    
    auto move_scp_scope = class_<MoveSCP>(m, "MoveSCP")
        .def(init<Association &>())
        .def("set_generator", &MoveSCP::set_generator)
        .def(
            "__call__",
            static_cast<
                void (MoveSCP::*)(std::shared_ptr<message::Message>)
            >(&MoveSCP::operator())
        )
    ;
    
    class_<
                MoveSCP::DataSetGenerator,
                DataSetGeneratorWrapperMove, // trampoline
                std::shared_ptr<MoveSCP::DataSetGenerator> // holder
            >(move_scp_scope, "DataSetGenerator")
        .def(init<>())
        .def("initialize", &MoveSCP::DataSetGenerator::initialize)
        .def("done", &MoveSCP::DataSetGenerator::done)
        .def("next", &MoveSCP::DataSetGenerator::next)
        .def("get", &MoveSCP::DataSetGenerator::get)
        .def("count", &MoveSCP::DataSetGenerator::count)
        .def("get_association", &MoveSCP::DataSetGenerator::get_association)
    ;
}
