/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _918ce553_d774_44c0_9cbf_56f32584a1ab
#define _918ce553_d774_44c0_9cbf_56f32584a1ab

#include <functional>

#include "odil/Association.h"
#include "odil/odil.h"
#include "odil/SCP.h"
#include "odil/Value.h"
#include "odil/message/NCreateRequest.h"
#include "odil/message/Message.h"

namespace odil
{

/// @brief SCP for N-Create services.
class ODIL_API NCreateSCP: public SCP
{
public:
    /**
     * @brief Callback called when a request is received, shall throw an
     * SCP::Exception on error.
     */
    typedef std::function<
            Value::Integer(std::shared_ptr<message::NCreateRequest const>)
        > Callback;

    /// @brief Constructor.
    NCreateSCP(Association & association);

    /// @brief Constructor.
    NCreateSCP(Association & association, Callback const & callback);

    /// @brief Return the callback.
    Callback const & get_callback() const;

    /// @brief Set the callback.
    void set_callback(Callback const & callback);

    /// @brief Process a N-Create request.
    virtual void operator()(std::shared_ptr<message::Message> message);
private:
    Callback _callback;
    void operator()(std::shared_ptr<message::NCreateRequest const> message);
};

}

#endif // _918ce553_d774_44c0_9cbf_56f32584a1ab
