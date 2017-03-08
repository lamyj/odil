/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>

#include <boost/python.hpp>

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
    
    virtual ~DataSetGeneratorWrapperMove()
    {
        // Nothing to do.
    }
    
    virtual unsigned int count() const
    {
        return this->get_override("count")();
    }
    
    virtual odil::Association 
        get_association(odil::message::CMoveRequest const & request) const
    {
        return this->get_override("get_association")(request);
    }
};

void set_generator(
    odil::MoveSCP & move_scp, DataSetGeneratorWrapperMove generator)
{
    auto cpp_generator = 
        std::make_shared<DataSetGeneratorWrapperMove>(generator);
    move_scp.set_generator(cpp_generator);
}

}

void wrap_MoveSCP()
{
    using namespace boost::python;
    using namespace odil;
    
    scope move_scp_scope = class_<MoveSCP>("MoveSCP", init<Association &>())
        .def("set_generator", &set_generator)
        .def("__call__", &odil::MoveSCP::operator())
    ;
    
    class_<DataSetGeneratorWrapperMove, boost::noncopyable>(
        "DataSetGenerator", init<>());
}
