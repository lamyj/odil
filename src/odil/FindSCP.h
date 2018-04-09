/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d54d5d3d_791c_43e5_b13a_397954053963
#define _d54d5d3d_791c_43e5_b13a_397954053963

#include <memory>

#include "odil/Association.h"
#include "odil/odil.h"
#include "odil/SCP.h"
#include "odil/message/CFindRequest.h"
#include "odil/message/Message.h"

namespace odil
{

/// @brief SCP for C-Find services.
class ODIL_API FindSCP: public SCP
{
public:

    /// @brief Constructor.
    FindSCP(Association & association);

    /// @brief Constructor.
    FindSCP(
        Association & association,
        std::shared_ptr<DataSetGenerator> const & generator);

    /// @brief Return the generator.
    std::shared_ptr<DataSetGenerator const> get_generator() const;

    /// @brief Set the generator.
    void set_generator(std::shared_ptr<DataSetGenerator> const & generator);

    /// @brief Process a C-Find request.
    virtual void operator()(std::shared_ptr<message::Message> message);

private:
    std::shared_ptr<DataSetGenerator> _generator;

    void operator()(std::shared_ptr<message::CFindRequest const> request);
};

}

#endif // _d54d5d3d_791c_43e5_b13a_397954053963
