/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _fa7d372a_dd27_4a1e_9b29_be9d5fbe602a
#define _fa7d372a_dd27_4a1e_9b29_be9d5fbe602a

#include <functional>
#include <utility>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/assoc.h>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/message/Message.h"
#include "dcmtkpp/Network.h"

namespace dcmtkpp
{

/// @brief Base class for all Service Class Users and Providers.
class ServiceRole
{
public:
    /// @brief Progress callback, following the semantics of DCMTK.
    typedef std::function<void(void *, unsigned long)> ProgressCallback;
    
    /// @brief Create a default Service Role with no network and no association.
    ServiceRole();

    /// @brief Create a Service Role with network and association.
    ServiceRole(Network * network, Association * association);
    
    /// @brief Copy the other service role.
    ServiceRole(ServiceRole const & other);
    
    /// @brief Copy the other service role.
    ServiceRole & operator=(ServiceRole const & other);
    
    /// @brief Destructor, network and association are not modified.
    virtual ~ServiceRole();
    
    /// @brief Return the network used by the ServiceRole.
    Network * get_network() const;
    /// @brief Set the network used by the ServiceRole.
    void set_network(Network * network);
    
    /// @brief Return the association used by the ServiceRole.
    Association * get_association() const;
    /// @brief Set the association used by the ServiceRole.
    void set_association(Association * association);

protected:
    /// @brief Wrapper class for DMCTK progress callbacks.
    struct ProgressCallbackData
    {
        /// @brief Callback function.
        ProgressCallback callback;
        
        /// @brief Callback data.
        void * data;
    };
    
    /// @brief Network used by the ServiceRole.
    Network * _network;
    
    /// @brief Association used by the ServiceRole.
    Association * _association;

    /// @brief Wrapper from ProgressCallback to DIMSE_ProgressCallback.
    static void _progress_callback_wrapper(void * data, unsigned long bytes_count);
    
    /// @brief Find an accepted presentation context.
    T_ASC_PresentationContextID _find_presentation_context(
        std::string const & abstract_syntax) const;
    
    /// @brief Send a DIMSE message.
    void _send(
        message::Message const & message, std::string const & abstract_syntax,
        ProgressCallback callback=NULL, void* callback_data=NULL) const;
    
    /// @brief Receive a generic DIMSE message.
    message::Message _receive(
        ProgressCallback callback=NULL, void* callback_data=NULL) const;
    
    /**
     * @brief Receive a DIMSE message of specific type.
     *
     * Throw an exception if the received message is not of the requested type.
     */
    template<typename TMessage>
    TMessage _receive(ProgressCallback callback=NULL, void* callback_data=NULL) const;

private:
    void _send(
        DataSet const & obj, T_ASC_PresentationContextID presID,
        std::string const & transfer_syntax, DUL_DATAPDV pdvType,
        ProgressCallback callback, void *callbackContext) const;

    std::pair<DataSet, DUL_DATAPDV> _receive_dataset(
        ProgressCallback callback, void *callbackContext) const;
    
    DUL_PDV _read_next_pdv() const;

    void _check_dimse_ready() const;
};

}

#include "ServiceRole.txx"

#endif // _fa7d372a_dd27_4a1e_9b29_be9d5fbe602a
