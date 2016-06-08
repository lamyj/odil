/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1b2f876e_1ad2_464d_9423_28181320aed0
#define _1b2f876e_1ad2_464d_9423_28181320aed0

#include "odil/Association.h"
#include "odil/DataSet.h"
#include "odil/SCU.h"

namespace odil
{

/// @brief SCU for C-Store services.
class StoreSCU: public SCU
{
public:
    /// @brief Constructor.
    StoreSCU(Association & association);

    /// @brief Destructor.
    virtual ~StoreSCU();
    
    /// @brief Set the affected SOP class based on the dataset.
    void set_affected_sop_class(DataSet const & dataset);

	using SCU::set_affected_sop_class;
    
    /// @brief Perform the C-STORE.
    void store(
        DataSet const & dataset,
        Value::String const & move_originator_ae_title = "",
        Value::Integer move_originator_message_id = -1) const;
};

}

#endif // _1b2f876e_1ad2_464d_9423_28181320aed0
