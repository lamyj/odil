/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _5ff4d940_4db7_4d85_9d3a_230b944b31fe
#define _5ff4d940_4db7_4d85_9d3a_230b944b31fe

#include <functional>
#include <string>
#include <vector>

#include "odil/Association.h"
#include "odil/DataSet.h"
#include "odil/message/CMoveResponse.h"
#include "odil/odil.h"
#include "odil/SCU.h"

namespace odil
{

/// @brief SCU for C-MOVE services.
class ODIL_API MoveSCU: public SCU
{
public:
    /// @brief Callback called when a C-STORE request is received.
    typedef std::function<void(DataSet const &)> StoreCallback;

    /**
     * @brief Typedef to keep compatibility with previous versions.
     * @deprecated The StoreCallback typedef should now be used.
     */
    typedef StoreCallback Callback;

    /// @brief Callback called when a C-MOVE response is received.
    typedef std::function<void(message::CMoveResponse const &)> MoveCallback;
    
    /// @brief Constructor.
    MoveSCU(Association & association);
    
    /// @brief Destructor.
    virtual ~MoveSCU();
    
    /// @brief Return the AE title of the destination, defaults to "".
    std::string const & get_move_destination() const;
    /// @brief Set the AE title of the destination.
    void set_move_destination(std::string const & move_destination);
    
    /// @brief Return the port for incoming associations, defaults to 0.
    uint16_t get_incoming_port() const;
    
    /// @brief Set the port for incoming associations, use 0 to disable.
    void set_incoming_port(uint16_t port);
    
    /// @brief Perform the C-MOVE using callbacks.
    void move(DataSet const & query, StoreCallback store_callback) const;
        
    /// @brief Perform the C-MOVE using callbacks.
    void move(DataSet const & query, MoveCallback move_callback) const;

    /// @brief Perform the C-MOVE using callbacks.
    void move(
        DataSet const & query, StoreCallback store_callback,
        MoveCallback move_callback) const;
    
    /**
     * @brief Return a list of datasets matching the query.
     */
    std::vector<DataSet> move(DataSet const & query) const;

private:
    std::string _move_destination;
    uint16_t _incoming_port;
    
    void _dispatch(
        Association & store_association, StoreCallback store_callback,
        MoveCallback move_callback) const;
    
    bool _handle_main_association(MoveCallback callback) const;
    bool _handle_store_association(
        Association & association, StoreCallback callback) const;
};

}

#endif // _5ff4d940_4db7_4d85_9d3a_230b944b31fe
