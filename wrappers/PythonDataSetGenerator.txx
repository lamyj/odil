/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "PythonDataSetGenerator.h"

#include <boost/python.hpp>

#include "odil/DataSet.h"
#include "odil/message/Request.h"
#include "odil/SCP.h"

template<typename TRequest>
PythonDataSetGenerator<TRequest>
::PythonDataSetGenerator(boost::python::object const & generator)
: _generator(generator)
{
    // Nothing else
}

template<typename TRequest>
PythonDataSetGenerator<TRequest>
::~PythonDataSetGenerator()
{
    // Nothing to do.
}

template<typename TRequest>
void
PythonDataSetGenerator<TRequest>
::initialize(odil::message::Request const & request)
{
    TRequest const concrete_request(request);
    this->_generator.attr("initialize")(concrete_request);
}

template<typename TRequest>
bool
PythonDataSetGenerator<TRequest>
::done() const
{
    bool const done = 
        boost::python::extract<bool>(this->_generator.attr("done")());
    return done;
}

template<typename TRequest>
void
PythonDataSetGenerator<TRequest>
::next()
{
    this->_generator.attr("next")();
}

template<typename TRequest>
odil::DataSet
PythonDataSetGenerator<TRequest>
::get() const
{
    odil::DataSet const data_set = 
        boost::python::extract<odil::DataSet>(this->_generator.attr("get")());
    return data_set;
}
