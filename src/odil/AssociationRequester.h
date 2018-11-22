/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _db12d5bd_f1f9_4205_8c8f_f3477481a799
#define _db12d5bd_f1f9_4205_8c8f_f3477481a799

#include <functional>
#include <mutex>
#include <vector>

#include <boost/asio.hpp>
#include <boost/signals2.hpp>

#include "odil/dul/AAssociateAC.h"
#include "odil/dul/AAssociateRQ.h"
#include "odil/dul/Connection.h"
#include "odil/dul/PDU.h"
#include "odil/odil.h"

namespace odil
{

class ODIL_API AssociationRequester
{
public:
    /**
     * @brief The function to be called when the association has been 
     * established successfully. Defaults to an empty function.
     */
    std::function<void(dul::AAssociateAC::Pointer)> success_handler;
    
    /**
     * @brief The function to be called when an error (association rejected, 
     * A-ABORT PDU received, transport error or transport closed) occurs. 
     * Defaults to an empty function.
     */
    std::function<void(dul::PDU::Pointer, boost::system::error_code)> error_handler;

    AssociationRequester(
        boost::asio::io_service & service, dul::Connection & connection, 
        std::function<void(dul::AAssociateAC::Pointer)> success_handler={}, 
        std::function<void(dul::PDU::Pointer, boost::system::error_code)> error_handler={});
    
    void operator()(
        boost::asio::ip::tcp::endpoint & endpoint, 
        dul::AAssociateRQ::Pointer request);

private:
    boost::asio::io_service & _service;
    dul::Connection & _connection;

    std::vector<boost::signals2::connection> _connections;

    /**
     * @brief Ensure that only of the handlers is called simultaneously.
     */
    std::mutex _mutex;

    /// @brief Handler called when the association has been established.
    void _on_associated(dul::PDU::Pointer pdu);

    /**
     * @brief Handler called when an error (rejection, A-ABORT, transport error 
     * or transport closed).
     */
    void _on_error(dul::PDU::Pointer pdu, boost::system::error_code error);
};

}

#endif // _db12d5bd_f1f9_4205_8c8f_f3477481a799
