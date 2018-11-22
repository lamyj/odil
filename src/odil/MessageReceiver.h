/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _56ff8a7c_7eea_4170_869a_c22b582ae797
#define _56ff8a7c_7eea_4170_869a_c22b582ae797

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include <boost/signals2.hpp>

#include "odil/DataSet.h"
#include "odil/dul/Connection.h"
#include "odil/dul/PDataTF.h"
#include "odil/message/Message.h"
#include "odil/odil.h"

namespace odil
{

/// @brief Assemble incoming P-DATA-TF PDUs to a message.
class ODIL_API MessageReceiver
{
public:
    /**
     * @brief The function to be called when the message has been received 
     * successfully. Defaults to an empty function.
     */
    std::function<void(std::shared_ptr<message::Message>)> success_handler;

    /**
     * @brief The function to be called when an error (A-ABORT PDU received,
     * transport error or transport closed) occurs. Defaults to an empty 
     * function.
     */
    std::function<void(dul::PDU::Pointer, boost::system::error_code)> error_handler;

    MessageReceiver(
        dul::Connection & connection,
        std::map<uint8_t, std::string> const & transfer_syntaxes_by_id, 
        std::function<void(std::shared_ptr<message::Message>)> success_handler={},
        std::function<void(dul::PDU::Pointer, boost::system::error_code)> error_handler={});

    /**
     * @brief Asynchronously receive P-DATA-TF PDUs, call success_handler if a
     * message is received, and error_handler if the connection is aborted or 
     * the transport closed.
     */
    void operator()();

private:
    dul::Connection & _connection;
    std::map<uint8_t, std::string> const & _transfer_syntaxes_by_id;

    std::vector<boost::signals2::connection> _connections;

    /**
     * @brief Ensure that both handlers (_pdu_sent and _on_error) are not called
     * simultaneously.
     */
    std::mutex _mutex;

    std::string _command_buffer;
    bool _command_received;
    std::shared_ptr<DataSet> _command;

    int _presentation_context_id;
    
    std::string _data_set_buffer;
    bool _data_set_received;
    std::shared_ptr<DataSet> _data_set;

    /// @brief Handler called when a PDU has been received.
    void _on_p_data_tf(dul::PDataTF::Pointer pdu);

    /**
     * @brief Handler called when an error (A-ABORT, transport error or 
     * transport closed).
     */
    void _on_error(dul::PDU::Pointer pdu, boost::system::error_code error);
};

}

#endif // _56ff8a7c_7eea_4170_869a_c22b582ae797
