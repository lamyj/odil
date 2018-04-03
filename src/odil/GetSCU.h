/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f82a15e2_fd13_44b5_af7d_c6983494c9c6
#define _f82a15e2_fd13_44b5_af7d_c6983494c9c6

#include <functional>
#include <vector>

#include "odil/Association.h"
#include "odil/DataSet.h"
#include "odil/odil.h"
#include "odil/SCU.h"
#include "odil/message/CGetRequest.h"
#include "odil/message/CGetResponse.h"
#include "odil/message/CStoreRequest.h"

namespace odil
{

/// @brief SCU for C-GET services.
class ODIL_API GetSCU: public SCU
{
public:
    /// @brief Callback called when a C-STORE request is received.
    typedef std::function<void(std::shared_ptr<DataSet>)> StoreCallback;

    /**
     * @brief Typedef to keep compatibility with previous versions.
     * @deprecated The StoreCallback typedef should now be used.
     */
    typedef StoreCallback Callback;

    /// @brief Callback called when a C-GET response is received.
    typedef std::function<
            void(std::shared_ptr<message::CGetResponse>)
        > GetCallback;

    /// @brief Constructor.
    GetSCU(Association & association);

    /// @brief Perform the C-GET using callbacks.
    void get(
        std::shared_ptr<DataSet const> query, StoreCallback store_callback,
        GetCallback get_callback=GetCallback()) const;

    /**
     * @brief Return a list of datasets matching the query.
     */
    std::vector<std::shared_ptr<DataSet>> get(
        std::shared_ptr<DataSet const> query) const;

private:
    void _get(
        std::shared_ptr<message::CGetRequest const> request,
        StoreCallback store_callback, GetCallback get_callback) const;
    bool _handle_get_response(
        std::shared_ptr<message::CGetResponse> response,
        GetCallback callback) const;
    void _handle_store_request(
        std::shared_ptr<message::CStoreRequest> request,
        StoreCallback callback) const;
};

}

#endif // _f82a15e2_fd13_44b5_af7d_c6983494c9c6
