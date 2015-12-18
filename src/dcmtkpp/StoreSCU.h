/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1b2f876e_1ad2_464d_9423_28181320aed0
#define _1b2f876e_1ad2_464d_9423_28181320aed0

#include "SCU.h"

#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/DcmtkAssociation.h"

namespace dcmtkpp
{

/// @brief SCU for C-Store services.
class StoreSCU: public SCU
{
public:
    /// @brief Destructor.
    virtual ~StoreSCU();
    
    /// @brief Set the affected SOP class based on the dataset.
    void set_affected_sop_class(DataSet const & dataset);
    
    /// @brief Perform the C-STORE using an optional callback.
    void store(DataSet const & dataset,
               DcmtkAssociation::ProgressCallback callback=NULL,
               void * data=NULL) const;
};

}

#endif // _1b2f876e_1ad2_464d_9423_28181320aed0
