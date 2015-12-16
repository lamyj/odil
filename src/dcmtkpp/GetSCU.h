/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f82a15e2_fd13_44b5_af7d_c6983494c9c6
#define _f82a15e2_fd13_44b5_af7d_c6983494c9c6

#include <functional>
#include <vector>

#include "dcmtkpp/DcmtkAssociation.h"
#include "dcmtkpp/message/CGetResponse.h"
#include "dcmtkpp/message/CStoreRequest.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/Network.h"
#include "dcmtkpp/SCU.h"

namespace dcmtkpp
{

/// @brief SCU for C-GET services.
class GetSCU: public SCU
{
public:
    /// @brief Callback called when a response is received.
    typedef std::function<void(DataSet const &)> Callback;

    /// @brief Default constructor.
    GetSCU();

    /// @brief Constructor.
    GetSCU(Network * network, DcmtkAssociation * association);

    /// @brief Destructor.
    virtual ~GetSCU();
    
    /// @brief Perform the C-GET using an optional callback.
    void get(DataSet const & query, Callback callback) const;
    
    /**
     * @brief Return a list of datasets matching the query.
     */
    std::vector<DataSet> get(DataSet const & query) const;

private:
    bool _get_response(message::CGetResponse const & response) const;
    void _store_request(
        message::CStoreRequest const & request, Callback callback) const;
};

}

#endif // _f82a15e2_fd13_44b5_af7d_c6983494c9c6
