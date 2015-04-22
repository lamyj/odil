/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _5ff4d940_4db7_4d85_9d3a_230b944b31fe
#define _5ff4d940_4db7_4d85_9d3a_230b944b31fe

#include <string>
#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcdatset.h>

#include "dcmtkpp/SCU.h"
#include "dcmtkpp/StoreSCP.h"

namespace dcmtkpp
{

/// @brief SCU for C-MOVE services.
class MoveSCU: public SCU
{
public:
    /// @brief Callback called when a response is received.
    typedef StoreSCP::Callback Callback;
    
    /// @brief Constructor.
    MoveSCU();
    
    /// @brief Destructor.
    virtual ~MoveSCU();
    
    /// @brief Return the AE title of the destination, defaults to "".
    std::string const & get_move_destination() const;
    /// @brief Set the AE title of the destination.
    void set_move_destination(std::string const & move_destination);

    /// @brief Perform the C-MOVE using a callback.
    void move(DcmDataset const & query, Callback callback) const;
    
    /**
     * @brief Return a list of datasets matching the query. The user is 
     * responsible for the de-allocation of the matches.
     */
    std::vector<DcmDataset *> move(DcmDataset const & query) const;

private:
    std::string _move_destination;
    
    bool _dispatch(Association & association, Callback callback) const;
    
    bool _handle_main_association() const;
    bool _handle_store_association(Association & association, Callback callback) const;
};

}

#endif // _5ff4d940_4db7_4d85_9d3a_230b944b31fe

