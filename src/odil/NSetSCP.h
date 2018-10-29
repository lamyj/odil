/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _cca2fb7a_c3b6_47f4_a619_44701b074cda
#define _cca2fb7a_c3b6_47f4_a619_44701b074cda

#include <functional>

#include "odil/Association.h"
#include "odil/odil.h"
#include "odil/SCP.h"
#include "odil/Value.h"
#include "odil/message/Message.h"
#include "odil/message/NSetRequest.h"

namespace odil
{

/// @brief SCP for N-Set services.
class ODIL_API NSetSCP: public SCP
{
public:
    /**
     * @brief Callback called when a request is received, shall throw an
     * SCP::Exception on error.
     */
    typedef std::function<
            Value::Integer(std::shared_ptr<message::NSetRequest const>)
        > Callback;

    /// @brief Constructor.
    NSetSCP(Association & association);

    /// @brief Constructor.
    NSetSCP(Association & association, Callback const & callback);

    /// @brief Return the callback.
    Callback const & get_callback() const;

    /// @brief Set the callback.
    void set_callback(Callback const & callback);

    /// @brief Process a N-Set request.
    virtual void operator()(std::shared_ptr<message::Message> message);
private:
    Callback _callback;
    void operator()(std::shared_ptr<message::NSetRequest const> message);
};

}

#endif // _cca2fb7a_c3b6_47f4_a619_44701b074cda
