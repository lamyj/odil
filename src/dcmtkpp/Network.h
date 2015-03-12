/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _fad49120_3f5c_447d_b0e9_72719087640c
#define _fad49120_3f5c_447d_b0e9_72719087640c

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/assoc.h>

namespace dcmtkpp
{

/**
 * @brief Wrapper around the T_ASC_Network class.
 * 
 * No member can be set while the network is initialized.
 */
class Network
{
public:
    /// @brief Create a default, un-initialized, network.
    Network();
    
    /// @brief Create an un-initialized network.
    Network(T_ASC_NetworkRole role, int port, int timeout, unsigned long options=0);
    
    /// @brief Create an un-initialized network.
    Network(Network const & other);
    
    /// @brief Destroy the network, dropping it if necessary.
    ~Network();
    
    /// @brief Assing an un-initialized network; it remains un-initialized.
    Network & operator=(Network const & other);
    
    /// @brief Return the role of the network, defaults to NET_REQUESTOR.
    T_ASC_NetworkRole get_role() const;
    
    /// @brief Set the role of the network.
    void set_role(T_ASC_NetworkRole role);
    
    /// @brief Return the port for acceptor role, defaults to 0.
    int get_port() const;
    
    /// @brief Set the port for acceptor role.
    void set_port(int port);
    
    /// @brief Return the timeout in seconds, defaults to 30.
    int get_timeout() const;
    
    /// @brief Set the timeout in seconds.
    void set_timeout(int timeout);
    
    /// @brief Return the options, defaults to 0.
    unsigned long get_options() const;
    
    /// @brief the set options.
    void set_options(unsigned long options);
    
    /// @brief Initialize the network.
    void initialize();
    
    /// @brief Return the underlying DCMTK object.
    T_ASC_Network * get_network();
    
    /// @brief Drop (i.e. un-initialize) the network.
    void drop();
    
    /// @brief Test whether the network is initialized.
    bool is_initialized() const;

private:
    T_ASC_NetworkRole _role;
    int _port;
    int _timeout;
    unsigned long _options;
    
    T_ASC_Network * _network;
};

}

#endif // _fad49120_3f5c_447d_b0e9_72719087640c
