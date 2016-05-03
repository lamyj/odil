/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f4680d8c_18a8_4317_956d_3ae238cb39cc
#define _f4680d8c_18a8_4317_956d_3ae238cb39cc

#include "odil/Association.h"
#include "odil/DataSet.h"
#include "odil/message/Message.h"
#include "odil/message/Request.h"

namespace odil
{

/// @brief Base class for all Service Class Providers.
class SCP
{
public:
    /// @brief Abstract base class for SCP returning multiple data sets.
    class DataSetGenerator
    {
    public:
        /// @brief Destructor.
        virtual ~DataSetGenerator() =0;

        /// @brief Initialize the generator.
        virtual void initialize(message::Request const & request) =0;

        /// @brief Test whether all elements have been generated.
        virtual bool done() const =0;
        
        /// @brief Prepare the next element.
        virtual void next() =0;

        /// @brief Return the current element.
        virtual DataSet get() const =0;
    };

    /// @brief Create a Service Class Provider.
    SCP(Association & association);

    /// @brief Destructor
    virtual ~SCP();

    /// @brief Receive and process a message.
    void receive_and_process();

    /// @brief Process a message.
    virtual void operator()(message::Message const & message) =0;
protected:
    /// @brief Association with peer.
    Association & _association;
};

}

#endif // _f4680d8c_18a8_4317_956d_3ae238cb39cc
