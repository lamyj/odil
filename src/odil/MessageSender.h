/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _9ae155cd_f353_4f9d_aac9_07c1d0796b17
#define _9ae155cd_f353_4f9d_aac9_07c1d0796b17

#include <cstdint>
#include <functional>
#include <mutex>
#include <set>
#include <string>
#include <vector>

#include <boost/signals2.hpp>

#include "odil/odil.h"
#include "odil/dul/Connection.h"
#include "odil/dul/PDataTF.h"
#include "odil/dul/PDU.h"
#include "odil/message/Message.h"

namespace odil
{

/// @brief Send a Message on an association and handle success/error notification.
class ODIL_API MessageSender
{
public:
    /**
     * @brief The function to be called when the message has been sent 
     * successfully. Defaults to an empty function.
     */
    std::function<void()> success_handler;
    
    /**
     * @brief The function to be called when an error (A-ABORT PDU received,
     * transport error or transport closed) occurs. Defaults to an empty 
     * function.
     */
    std::function<void(dul::PDU::Pointer, boost::system::error_code)> error_handler;

    /**
     * @brief Constructor
     * 
     * @warning The connection must not be destroyed before this object.
     */
    MessageSender(
        dul::Connection & connection, 
        std::function<void()> success_handler={},
        std::function<void(dul::PDU::Pointer, boost::system::error_code)> error_handler={});
    
    /**
     * @brief Send a message using the given transfer syntax and Presentation
     * Context ID. The message will be fragmented in PDUs according to 
     * maximum_length.
     */
    void operator()(
        std::shared_ptr<message::Message const> message,
        std::string const & transfer_syntax, uint8_t context_id, 
        uint32_t maximum_length);
private:
    dul::Connection & _connection;
    std::set<dul::PDataTF::Pointer> _to_send;

    std::vector<boost::signals2::connection> _connections;

    /**
     * @brief Ensure that both handlers (_pdu_sent and _on_error) are not called
     * simultaneously.
     */
    std::mutex _mutex;

    /// @brief Split the message in P-DATA-TF PDUs stored in _to_send.
    void _split_message(
        std::shared_ptr<message::Message const> message,
        std::string const & transfer_syntax, uint8_t context_id, 
        uint32_t maximum_length);

    /// @brief Handler called when a PDU has been successfully sent.
    void _pdu_sent(dul::PDU::Pointer pdu);

    /**
     * @brief Handler called when an error (A-ABORT, transport error or 
     * transport closed).
     */
    void _on_error(dul::PDU::Pointer pdu, boost::system::error_code error);
};

}

#endif // _9ae155cd_f353_4f9d_aac9_07c1d0796b17
