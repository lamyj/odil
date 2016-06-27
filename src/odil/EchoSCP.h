/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1a61d976_ba12_4dba_af34_67f064d38506
#define _1a61d976_ba12_4dba_af34_67f064d38506

#include <functional>

#include "odil/Association.h"
#include "odil/SCP.h"
#include "odil/Value.h"
#include "odil/message/CEchoRequest.h"
#include "odil/message/Message.h"

namespace odil
{

/// @brief SCP for C-Echo services.
class EchoSCP: public SCP
{
public:
    /**
     * @brief Callback called when a request is received, shall throw an
     * SCP::Exception on error.
     */
    typedef std::function<Value::Integer(message::CEchoRequest const &)> Callback;

    /// @brief Constructor.
    EchoSCP(Association & association);

    /// @brief Constructor.
    EchoSCP(Association & association, Callback const & callback);

    /// @brief Destructor.
    virtual ~EchoSCP();

    /// @brief Return the callback.
    Callback const & get_callback() const;

    /// @brief Set the callback.
    void set_callback(Callback const & callback);

    /// @brief Process a C-Echo request.
    virtual void operator()(message::Message const & message);

private:
    Callback _callback;
};

}

#endif // _1a61d976_ba12_4dba_af34_67f064d38506
