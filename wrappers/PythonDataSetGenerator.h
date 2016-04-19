/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f80d2c20_23e8_4751_bf31_37a031a201eb
#define _f80d2c20_23e8_4751_bf31_37a031a201eb

#include <boost/python.hpp>

#include "odil/DataSet.h"
#include "odil/message/Request.h"
#include "odil/SCP.h"

/// @brief Adapt a compatible Python class to a DataSetGenerator.
template<typename TRequest>
class PythonDataSetGenerator: public odil::SCP::DataSetGenerator
{
public:
    PythonDataSetGenerator(boost::python::object const & generator);
    
    virtual ~PythonDataSetGenerator();

    virtual void initialize(odil::message::Request const & request);

    virtual bool done() const;
    
    virtual void next();

    virtual odil::DataSet get() const;

private:
    boost::python::object _generator; 
};

#include "PythonDataSetGenerator.txx"

#endif // _f80d2c20_23e8_4751_bf31_37a031a201eb
