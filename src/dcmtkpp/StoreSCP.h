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

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmnet/dimse.h>

#include "dcmtkpp/SCP.h"

namespace dcmtkpp
{

class StoreSCP: public SCP
{
public:
    /// @brief Callback called when a response is received.
    typedef std::function<void(DcmDataset*)> Callback;
    
    /**
     * @brief Receive a store request and respond to it.
     * @param callback function called with the dataset to be stored.
     */
    bool store(Callback callback) const;
    
    /**
     * @brief Respond to a store request.
     * @param request
     * @param callback function called with the dataset to be stored.
     */
    void store(T_DIMSE_C_StoreRQ request, Callback callback) const;
};

}

#endif // _fdbf3f51_91f5_464a_b449_c3f994297210
