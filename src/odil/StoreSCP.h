/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _fdbf3f51_91f5_464a_b449_c3f994297210
#define _fdbf3f51_91f5_464a_b449_c3f994297210

#include <functional>

#include "odil/Association.h"
#include "odil/odil.h"
#include "odil/SCP.h"
#include "odil/Value.h"
#include "odil/message/CStoreRequest.h"
#include "odil/message/Message.h"

namespace odil
{

/// @brief SCP for C-Store services.
class ODIL_API StoreSCP: public SCP
{
public:
    /**
     * @brief Callback called when a request is received, shall throw an
     * SCP::Exception on error.
     */
    typedef std::function<
            Value::Integer(std::shared_ptr<message::CStoreRequest>)
        > Callback;

    /// @brief Constructor.
    StoreSCP(Association & association);

    /// @brief Constructor.
    StoreSCP(Association & association, Callback const & callback);

    /// @brief Return the callback.
    Callback const & get_callback() const;

    /// @brief Set the callback.
    void set_callback(Callback const & callback);

    /// @brief Process a C-Store request.
    void operator()(std::shared_ptr<message::CStoreRequest> request);

    /// @brief Process a C-Store request.
    virtual void operator()(std::shared_ptr<message::Message> message);
private:
    Callback _callback;
};

}

#endif // _fdbf3f51_91f5_464a_b449_c3f994297210
