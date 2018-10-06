/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8971f17b_e958_4aa3_9d36_640aaa018f56
#define _8971f17b_e958_4aa3_9d36_640aaa018f56

#include <pybind11/pybind11.h>

#include "odil/DataSet.h"
#include "odil/message/Request.h"

template<typename TDataSetGenerator>
class DataSetGeneratorWrapper: public TDataSetGenerator
{
public:
    DataSetGeneratorWrapper()
    : TDataSetGenerator()
    {
        // Nothing else.
    }

    virtual ~DataSetGeneratorWrapper() override
    {
        // Nothing to do.
    }

    virtual void initialize(
        std::shared_ptr<odil::message::Request const> request) override
    {
        PYBIND11_OVERLOAD_PURE(void, TDataSetGenerator, initialize, request);
    }

    virtual bool done() const override
    {
        PYBIND11_OVERLOAD_PURE(bool, TDataSetGenerator, done, );
    }

    virtual void next() override
    {
        PYBIND11_OVERLOAD_PURE(void, TDataSetGenerator, next, );
    }

    virtual std::shared_ptr<odil::DataSet> get() const override
    {
        PYBIND11_OVERLOAD_PURE(
            std::shared_ptr<odil::DataSet>, TDataSetGenerator, get, );
    }
};

#endif // _8971f17b_e958_4aa3_9d36_640aaa018f56
