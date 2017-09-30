/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8971f17b_e958_4aa3_9d36_640aaa018f56
#define _8971f17b_e958_4aa3_9d36_640aaa018f56

#include <boost/python.hpp>
#include "odil/message/Request.h"

template<typename TDataSetGenerator>
class DataSetGeneratorWrapper:
    public TDataSetGenerator, public boost::python::wrapper<TDataSetGenerator>
{
public:
    DataSetGeneratorWrapper()
    : TDataSetGenerator(), boost::python::wrapper<TDataSetGenerator>()
    {
        // Nothing else.
    }

    virtual ~DataSetGeneratorWrapper()
    {
        // Nothing to do.
    }

    virtual void initialize(odil::message::Request const & request)
    {
        this->get_override("initialize")(request);
    }

    virtual bool done() const
    {
        return this->get_override("done")();
    }

    virtual void next()
    {
        this->get_override("next")();
    }

    virtual odil::DataSet get() const
    {
        return this->get_override("get")();
    }
};

#endif // _8971f17b_e958_4aa3_9d36_640aaa018f56
