/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>

#include <pybind11/pybind11.h>

#include "odil/message/CGetRequest.h"
#include "odil/GetSCP.h"

#include "opaque_types.h"
#include "type_casters.h"

#include "DataSetGeneratorWrapper.h"

namespace
{
    
class DataSetGeneratorWrapperGet: 
    public DataSetGeneratorWrapper<odil::GetSCP::DataSetGenerator>
{
public:
    DataSetGeneratorWrapperGet()
    : DataSetGeneratorWrapper<odil::GetSCP::DataSetGenerator>()
    {
        // Nothing else
    }
    
    virtual ~DataSetGeneratorWrapperGet() override
    {
        // Nothing to do.
    }
    
    virtual unsigned int count() const override
    {
        PYBIND11_OVERLOAD_PURE(unsigned int, odil::GetSCP::DataSetGenerator, count, );
    }
};

}

void wrap_GetSCP(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;
    
    auto get_scp_scope = class_<GetSCP>(m, "GetSCP")
        .def(init<Association &>())
        .def("set_generator", &GetSCP::set_generator)
        .def(
            "__call__",
            static_cast<
                void (GetSCP::*)(std::shared_ptr<message::Message>)
            >(&GetSCP::operator())
        )
    ;
    
    class_<
                GetSCP::DataSetGenerator,
                DataSetGeneratorWrapperGet, // trampoline
                std::shared_ptr<GetSCP::DataSetGenerator> // holder
            >(get_scp_scope, "DataSetGenerator")
        .def(init<>())
        .def("initialize", &GetSCP::DataSetGenerator::initialize)
        .def("done", &GetSCP::DataSetGenerator::done)
        .def("next", &GetSCP::DataSetGenerator::next)
        .def("get", &GetSCP::DataSetGenerator::get)
        .def("count", &GetSCP::DataSetGenerator::count)
    ;
}
