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
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/Network.h"

namespace dcmtkpp
{

class ServiceRole
{
public:
    /// @brief Progress callback, following the semantics of DCMTK.
    typedef std::function<void(void *, unsigned long)> ProgressCallback;
    
    /// @brief Create a default Service Role with no network and no association.
    ServiceRole();
    
    /// @brief Copy the other service role.
    ServiceRole(ServiceRole const & other);
    
    /// @brief Copy the other service role.
    ServiceRole const & operator=(ServiceRole const & other);
    
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
    template<T_DIMSE_Command VCommand>
    struct Traits;
    
    struct ProgressCallbackData
    {
        ProgressCallback callback;
        void * data;
    };
    
    Network * _network;
    Association * _association;

    /// @brief Wrapper from ProgressCallback to DIMSE_ProgressCallback.
    static void _progress_callback_wrapper(void * data, unsigned long bytes_count);
    
    /// @brief Find an accepted presentation context.
    T_ASC_PresentationContextID _find_presentation_context(
        std::string const & abstract_syntax) const;
    
    /// @brief Send a DIMSE message.
    template<T_DIMSE_Command VCommand>
    void _send(
        typename Traits<VCommand>::Type const & command, 
        std::string const & abstract_syntax, DcmDataset* payload=NULL, 
        ProgressCallback callback=NULL, void* callback_data=NULL) const;
    
    /// @brief Receive a DIMSE command.
    std::pair<T_ASC_PresentationContextID, T_DIMSE_Message>
    _receive_command(T_DIMSE_BlockingMode block_mode) const;
    
    std::pair<T_ASC_PresentationContextID, DcmDataset *>
    _receive_dataset(
        T_DIMSE_BlockingMode block_mode,
        ProgressCallback callback=NULL, void* callback_data=NULL) const;

private:
    void _check_dimse_ready() const;
};

}

#include "ServiceRole.txx"

#endif // _fa7d372a_dd27_4a1e_9b29_be9d5fbe602a
