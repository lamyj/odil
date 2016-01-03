/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d54d5d3d_791c_43e5_b13a_397954053963
#define _d54d5d3d_791c_43e5_b13a_397954053963

#include <memory>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/SCP.h"
#include "dcmtkpp/message/Message.h"

namespace dcmtkpp
{

/// @brief SCP for C-Find services.
class FindSCP: public SCP
{
public:

    /// @brief Constructor.
    FindSCP(Association & association);

    /// @brief Constructor.
    FindSCP(
        Association & association,
        std::shared_ptr<DataSetGenerator> const & generator);

    /// @brief Destructor.
    virtual ~FindSCP();

    /// @brief Return the generator.
    DataSetGenerator const & get_generator() const;

    /// @brief Set the generator.
    void set_generator(std::shared_ptr<DataSetGenerator> const & generator);

    /// @brief Process a C-Find request.
    virtual void operator()(message::Message const & message);

private:
    std::shared_ptr<DataSetGenerator> _generator;
};

}

#endif // _d54d5d3d_791c_43e5_b13a_397954053963
