/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _fdbf3f51_91f5_464a_b449_c3f994297210
#define _fdbf3f51_91f5_464a_b449_c3f994297210

#include <functional>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/message/CStoreRequest.h"
#include "dcmtkpp/message/Message.h"
#include "dcmtkpp/Network.h"
#include "dcmtkpp/SCP.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

/// @brief SCP for C-Store services.
class StoreSCP: public SCP
{
public:
    /// @brief Callback called when a request is received.
    typedef std::function<Value::Integer(message::CStoreRequest const &)> Callback;

    /// @brief Default constructor.
    StoreSCP();

    /// @brief Constructor with default callback.
    StoreSCP(Network * network, Association * association);

    /// @brief Constructor.
    StoreSCP(
        Network * network, Association * association,
        Callback const & callback);

    /// @brief Destructor.
    virtual ~StoreSCP();

    /// @brief Return the callback.
    Callback const & get_callback() const;

    /// @brief Set the callback.
    void set_callback(Callback const & callback);

    /// @brief Process a C-Store request.
    virtual void operator()(message::Message const & message);

private:
    Callback _callback;
};

}

#endif // _fdbf3f51_91f5_464a_b449_c3f994297210
