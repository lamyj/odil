/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b1c7d2fd_0e9b_4bcc_98f3_bbfa3cf724e0
#define _b1c7d2fd_0e9b_4bcc_98f3_bbfa3cf724e0

#include <functional>
#include <mutex>
#include <vector>

#include <boost/asio.hpp>
#include <boost/signals2.hpp>

#include "odil/dul/Connection.h"
#include "odil/dul/PDU.h"
#include "odil/odil.h"

namespace odil
{

/// @brief Receive an association and handle success/error notification.
class ODIL_API AssociationReceiver
{
public:
    /**
     * @brief The function to be called when the association has been 
     * negotiated. Defaults to an empty function.
     */
    std::function<void(dul::PDU::Pointer)> success_handler;

    /**
     * @brief The function to be called when an error (A-ABORT PDU received, 
     * transport error or transport closed) occurs. 
     * Defaults to an empty function.
     */
    std::function<void(dul::PDU::Pointer, boost::system::error_code)> error_handler;

    AssociationReceiver(
        boost::asio::io_service & service, dul::Connection & connection, 
        std::function<void(dul::PDU::Pointer)> success_handler={}, 
        std::function<void(dul::PDU::Pointer, boost::system::error_code)> error_handler={});

    void operator()(boost::asio::ip::tcp::endpoint & endpoint);

private:
    boost::asio::io_service & _service;
    dul::Connection & _connection;
    std::shared_ptr<boost::asio::ip::tcp::acceptor> _acceptor;

    std::vector<boost::signals2::connection> _connections;

    /**
     * @brief Ensure that only of the handlers is called simultaneously.
     */
    std::mutex _mutex;

    /// @brief Handler called when the association has been negotiated.
    void _on_negotiated(dul::PDU::Pointer pdu);

    /**
     * @brief Handler called when an error (A-ABORT, transport error 
     * or transport closed).
     */
    void _on_error(dul::PDU::Pointer pdu, boost::system::error_code error);

};

}

#endif // _b1c7d2fd_0e9b_4bcc_98f3_bbfa3cf724e0
