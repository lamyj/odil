/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
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

#include "dcmtkpp/Association.h"
#include "dcmtkpp/SCP.h"
#include "dcmtkpp/message/Message.h"

namespace dcmtkpp
{

/// @brief SCP for C-Move services.
class MoveSCP: public SCP
{
public:

    class DataSetGenerator: public SCP::DataSetGenerator
    {
    public:
        virtual unsigned int count() const =0;
        virtual std::pair<std::string, uint16_t> get_peer(
            std::string const & destination) const =0;
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

