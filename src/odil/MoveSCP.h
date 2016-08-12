/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7e899e10_2a21_45b8_a2d6_af1d13cbfd29
#define _7e899e10_2a21_45b8_a2d6_af1d13cbfd29

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include "odil/Association.h"
#include "odil/SCP.h"
#include "odil/message/CMoveRequest.h"
#include "odil/message/Message.h"

namespace odil
{

/// @brief SCP for C-Move services.
class MoveSCP: public SCP
{
public:

    /// @brief Generator of C-MOVE responses.
    class DataSetGenerator: public SCP::DataSetGenerator
    {
    public:
        /// @brief Return the number of responses.
        virtual unsigned int count() const =0;
        
        /**
         * @brief Return the sub-association to send responses on.
         *
         * If the move destination is unknown, an odil::Exception must be
         * thrown.
         */
        virtual Association get_association(message::CMoveRequest const &) const =0;
    };

    /// @brief Constructor.
    MoveSCP(Association & association);

    /// @brief Constructor.
    MoveSCP(
        Association & association,
        std::shared_ptr<DataSetGenerator> const & generator);

    /// @brief Destructor.
    virtual ~MoveSCP();

    /// @brief Return the generator.
    DataSetGenerator const & get_generator() const;

    /// @brief Set the generator.
    void set_generator(std::shared_ptr<DataSetGenerator> const & generator);

    /// @brief Process a C-Get request.
    virtual void operator()(message::Message const & message);

private:
    std::shared_ptr<DataSetGenerator> _generator;
};

}


#endif // _7e899e10_2a21_45b8_a2d6_af1d13cbfd29
