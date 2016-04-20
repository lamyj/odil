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

namespace
{
    
class PythonDataSetGenerator_GET: public odil::GetSCP::DataSetGenerator
{
public:
    PythonDataSetGenerator_GET(boost::python::object const & generator)
    : _generator(generator)
    {
        // Nothing else
    }
    
    virtual ~PythonDataSetGenerator_GET()
    {
        // Nothing to do.
    }

    virtual void initialize(odil::message::Request const & request)
    {
        odil::message::CGetRequest const concrete_request(request);
        this->_generator.attr("initialize")(concrete_request);
    }

    virtual bool done() const
    {
        bool const done = 
            boost::python::extract<bool>(this->_generator.attr("done")());
        return done;
    }
    
    virtual void next()
    {
        this->_generator.attr("next")();
    }

    virtual odil::DataSet get() const
    {
        odil::DataSet const data_set = 
            boost::python::extract<odil::DataSet>(this->_generator.attr("get")());
        return data_set;
    }
    
    virtual unsigned int count() const
    {
        unsigned int const count = boost::python::extract<unsigned int>(
            this->_generator.attr("count")());
        return count;
    }

private:
    boost::python::object _generator; 
};

void set_generator(
    odil::GetSCP & get_scp, boost::python::object const & python_generator)
{
    auto cpp_generator = 
        std::make_shared<PythonDataSetGenerator_GET>(python_generator);
    get_scp.set_generator(cpp_generator);
}

}

void wrap_GetSCP()
{
    boost::python::class_<odil::GetSCP>(
            "GetSCP", boost::python::init<odil::Association &>())
        .def("set_generator", &set_generator)
        .def("__call__", &odil::GetSCP::operator())
    ;
}
