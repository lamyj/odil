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
#include "odil/SCU.h"

namespace odil
{

/// @brief SCU for C-MOVE services.
class MoveSCU: public SCU
{
public:
    /// @brief Callback called when a response is received.
    typedef std::function<void(DataSet const &)> Callback;
    
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

    /// @brief Perform the C-MOVE using a callback.
    void move(DataSet const & query, Callback callback) const;
    
    /**
     * @brief Return a list of datasets matching the query.
     */
    std::vector<DataSet> move(DataSet const & query) const;

private:
    std::string _move_destination;
    uint16_t _incoming_port;
    
    void _dispatch(Association & store_association, Callback callback) const;
    
    bool _handle_main_association() const;
    bool _handle_store_association(Association & association, Callback callback) const;
};

}

#endif // _5ff4d940_4db7_4d85_9d3a_230b944b31fe
