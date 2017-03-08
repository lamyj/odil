/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>

#include <boost/python.hpp>

#include "odil/message/CGetRequest.h"
#include "odil/GetSCP.h"

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
    
    virtual ~DataSetGeneratorWrapperGet()
    {
        // Nothing to do.
    }
    
    virtual unsigned int count() const
    {
        return this->get_override("count")();
    }
};

void set_generator(odil::GetSCP & get_scp, DataSetGeneratorWrapperGet generator)
{
    auto cpp_generator = 
        std::make_shared<DataSetGeneratorWrapperGet>(generator);
    get_scp.set_generator(cpp_generator);
}

}

void wrap_GetSCP()
{
    using namespace boost::python;
    using namespace odil;
    
    scope get_scp_scope = class_<GetSCP>("GetSCP", init<Association &>())
        .def("set_generator", &set_generator)
        .def("__call__", &odil::GetSCP::operator())
    ;
    
    class_<DataSetGeneratorWrapperGet, boost::noncopyable>(
        "DataSetGenerator", init<>());
}
