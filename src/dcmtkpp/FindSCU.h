/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _0106eb3a_4e02_4d7c_93bf_4d53dcafbb05
#define _0106eb3a_4e02_4d7c_93bf_4d53dcafbb05

#include "SCU.h"

#include <functional>
#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/Association.h"

namespace dcmtkpp
{

/// @brief SCU for C-FIND services.
class FindSCU: public SCU
{
public:
    /// @brief Full-featured callback, following the semantics of DCMTK.
    typedef std::function<void(void *, T_DIMSE_C_FindRQ *,
        int, T_DIMSE_C_FindRSP *, DcmDataset *)> FullCallback;
    
    /// @brief Simple callback, with access only to the response dataset.
    typedef std::function<void(DcmDataset*)> SimpleCallback;
    
    /// @brief Destructor.
    virtual ~FindSCU();
    
    /// @brief Perform the C-FIND using a full-featured callback.
    void find(DcmDataset const * query, FullCallback callback, void * data) const;
    
    /// @brief Perform the C-FIND using a simple callback.
    void find(DcmDataset const * query, SimpleCallback callback) const;
    
    /**
     * @brief Return a list of datasets matching the query. The user is 
     * responsible for the de-allocation of the matches.
     */
    std::vector<DcmDataset *> find(DcmDataset const * query) const;
    
private:
    struct FullCallbackData
    {
        FullCallback callback;
        void * data;
    };
    
    /// Wrapper to map C++ std::function to DCMTK void *
    static void _callback_wrapper(void * data, T_DIMSE_C_FindRQ * request, 
        int response_index, T_DIMSE_C_FindRSP * response, 
        DcmDataset * response_identifiers);
    
    /// Low-level find function
    void _find(DcmDataset const * query, 
        DIMSE_FindUserCallback callback, void * callback_data) const;
};

}

#endif // _0106eb3a_4e02_4d7c_93bf_4d53dcafbb05
