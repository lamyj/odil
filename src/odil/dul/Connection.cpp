/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/dul/Connection.h"

#include <atomic>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/optional.hpp>
#include <boost/signals2.hpp>

#include "odil/endian.h"
#include "odil/logging.h"
#include "odil/dul/AAbort.h"
#include "odil/dul/AAssociateAC.h"
#include "odil/dul/AAssociateRJ.h"
#include "odil/dul/AAssociateRQ.h"
#include "odil/dul/AReleaseRP.h"
#include "odil/dul/AReleaseRQ.h"
#include "odil/dul/PDataTF.h"

namespace odil
{

namespace dul
{

Connection
::Connection(
    boost::asio::ip::tcp::socket & socket,
    boost::posix_time::time_duration artim_timeout)
: transport_connection(), transport_error(),transport_closed(),
    a_associate(), a_release(), a_abort(), a_p_abort(), p_data(),
    socket(socket), artim_timeout(artim_timeout), acceptor(),
    _state(1), _incoming(6, '\0'), _artim_timer(socket.get_io_service()),
    _is_requestor(false), _peer(), _association_request(nullptr)
{
    // Transport services
    this->transport_connection.request.connect([&]() {
        this->socket.async_connect(
            this->_peer,
            [&](boost::system::error_code const & error) {
                this->transport_connection.confirmation(error); });
    });
    this->transport_connection.confirmation.connect(
        [&](boost::system::error_code error) {
            if(error)
            {
                this->transport_error.indication(error);
            }
            else
            {
                ODIL_LOG(DEBUG, dul) << "Received transport connection confirmation";
                if(this->_state == 4)
                {
                    // Socket is opened, we can start receiving PDUs.
                    this->_receive_handler();
                    this->AE_2(this->_association_request);
                }
                else
                {
                    throw Exception(
                        "Cannot send AAssociateRQ in state "
                        +std::to_string(this->_state));
                }
            }
    });
    this->transport_closed.indication.connect([&]() {
        ODIL_LOG(DEBUG, dul) << "Transport connection closed";

        if(this->_state == 2) { this->AA_5(); }
        else if(this->_state >= 3 && this->_state <= 12) { this->AA_4(); }
        else if(this->_state == 13) { this->AR_5(); }
        else
        {
            throw Exception(
                "Transport closed indication cannot be received in state "
                +std::to_string(this->_state));
        }
    });

    // A-ASSOCIATE service
    this->a_associate.request.connect([&](AAssociateRQ::Pointer pdu) {
        ODIL_LOG(DEBUG, dul) << "Received A-ASSOCIATE request";

        if(this->_state == 1) { this->AE_1(pdu); }
        else
        {
            throw Exception(
                "Cannot send AAssociateRQ in state "+std::to_string(this->_state));
        }
    });
    this->a_associate.response.connect([&](PDU::Pointer pdu) {
        ODIL_LOG(DEBUG, dul) << "Received A-ASSOCIATE response";
        if(pdu->get_pdu_type() == AAssociateAC::type)
        {
            if(this->_state == 3)
            {
                this->AE_7(std::dynamic_pointer_cast<AAssociateAC>(pdu));
            }
            else
            {
                throw Exception(
                    "Cannot send AAssociateAC in state "+std::to_string(this->_state));
            }
        }
        else if(pdu->get_pdu_type() == AAssociateRJ::type)
        {
            if(this->_state == 3)
            {
                this->AE_8(std::dynamic_pointer_cast<AAssociateRJ>(pdu));
            }
            else
            {
                throw Exception(
                    "Cannot send AAssociateRJ in state "+std::to_string(this->_state));
            }
        }
        else
        {
            throw Exception(
                "A-ASSOCIATE response must be either "
                "A-ASSOCIATE-AC or A-ASSOCIATE-RJ");
        }
    });

    // A-RELEASE service
    this->a_release.request.connect([&](AReleaseRQ::Pointer pdu) {
        ODIL_LOG(DEBUG, dul) << "Received A-RELEASE request";
        if(this->_state == 6)
        {
            this->AR_1(pdu);
        }
        else
        {
            throw Exception(
                "Cannot send AReleaseRQ in state "+std::to_string(this->_state));
        }
    });
    this->a_release.indication.connect([&](AReleaseRQ::Pointer /* pdu */) {
        ODIL_LOG(DEBUG, dul) << "Received A-RELEASE indication";
        this->async_send(std::make_shared<AReleaseRP>());
    });
    this->a_release.response.connect([&](AReleaseRP::Pointer pdu) {
        ODIL_LOG(DEBUG, dul) << "Received A-RELEASE response";
        if(this->_state == 8)
        {
            this->AR_4(pdu);
        }
        else if(this->_state == 9)
        {
            this->AR_9(pdu);
        }
        else if(this->_state == 12)
        {
            this->AR_4(pdu);
        }
        else
        {
            throw Exception(
                "Cannot send AReleaseRP in state "+std::to_string(this->_state));
        }
    });

    // A-ABORT service
    this->a_abort.request.connect([&](AAbort::Pointer pdu) {
        ODIL_LOG(DEBUG, dul) << "Received A-ABORT request";
        if(this->_state == 3)
        {
            this->AA_1(pdu);
        }
        else if(this->_state == 4)
        {
            this->AA_2();
        }
        else if(this->_state >= 5 && this->_state <= 12)
        {
            this->AA_1(pdu);
        }
        else
        {
            throw Exception(
                "Cannot send AAssociateAC in state "+std::to_string(this->_state));
        }
    });

    // P-DATA service
    this->p_data.request.connect([&](PDataTF::Pointer pdu) {
        ODIL_LOG(DEBUG, dul) << "Received P-DATA request";
        if(this->_state == 6)
        {
            this->DT_1(pdu);
        }
        else if(this->_state == 8)
        {
            this->AR_7(pdu);
        }
        else
        {
            throw Exception(
                "Cannot send PDataTF in state "+std::to_string(this->_state));
        }
    });
}

void
Connection
::async_send(boost::asio::ip::tcp::endpoint peer, AAssociateRQ::Pointer pdu)
{
    // Save peer for later (transport_connection.request)
    this->_peer = peer;
    this->a_associate.request(pdu);
}

void
Connection
::async_send(PDU::Pointer pdu)
{
    if(pdu->get_pdu_type() == AAssociateAC::type)
    {
        this->a_associate.response(pdu);
    }
    else if(pdu->get_pdu_type() == AAssociateRJ::type)
    {
        this->a_associate.response(pdu);
    }
    else if(pdu->get_pdu_type() == AReleaseRQ::type)
    {
        this->a_release.request(std::dynamic_pointer_cast<AReleaseRQ>(pdu));
    }
    else if(pdu->get_pdu_type() == AReleaseRP::type)
    {
        this->a_release.response(std::dynamic_pointer_cast<AReleaseRP>(pdu));
    }
    else if(pdu->get_pdu_type() == AAbort::type)
    {
        this->a_abort.request(std::dynamic_pointer_cast<AAbort>(pdu));
    }
    // NOTE: there will never be an A-P-ABORT request here, since these will be
    // issued by the transport. cf. PS3.8, 7.4
    else if(pdu->get_pdu_type() == PDataTF::type)
    {
        this->p_data.request(std::dynamic_pointer_cast<PDataTF>(pdu));
    }
    else
    {
        throw Exception(
            "Invalid PDU type in async_send(peer): "
            +std::to_string(pdu->get_pdu_type()));
    }
}

Connection::SynchronousStatus
Connection
::send(
    boost::asio::ip::tcp::endpoint const & endpoint, AAssociateRQ::Pointer pdu)
{
    ODIL_LOG(DEBUG, dul) << "Sending A-ASSOCIATE-RQ synchronously";

    SynchronousStatus status;

    std::vector<boost::signals2::connection> connections;

    auto const on_pdu = [&](PDU::Pointer pdu) { status.pdu = pdu; };
    connections.emplace_back(this->a_associate.confirmation.connect(on_pdu));

    auto const on_error =
        [&](boost::system::error_code error=boost::system::error_code()) {
            status.error_code = error; };
    connections.emplace_back(
        this->transport_error.indication.connect(on_error));
    connections.emplace_back(
        this->transport_closed.indication.connect(on_error));

    this->async_send(endpoint, pdu);
    while(!status.pdu && !status.error_code)
    {
        this->socket.get_io_service().run_one();
    }

    for(auto const & connection: connections)
    {
        connection.disconnect();
    }

    return status;
}

Connection::SynchronousStatus
Connection
::send(AReleaseRQ::Pointer pdu)
{
    ODIL_LOG(DEBUG, dul) << "Sending A-RELEASE-RQ synchronously";

    SynchronousStatus status;

    std::vector<boost::signals2::connection> connections;

    auto const on_pdu = [&](PDU::Pointer pdu) { status.pdu = pdu; };
    connections.emplace_back(this->p_data.indication.connect(on_pdu));
    connections.emplace_back(this->a_release.indication.connect(on_pdu));
    connections.emplace_back(this->a_release.confirmation.connect(on_pdu));
    connections.emplace_back(this->a_abort.indication.connect(on_pdu));

    auto const on_error =
        [&](boost::system::error_code error=boost::system::error_code()) {
            status.error_code = error; };
    connections.emplace_back(
        this->transport_error.indication.connect(on_error));
    connections.emplace_back(
        this->transport_closed.indication.connect(on_error));

    this->async_send(pdu);
    while(!status.pdu && !status.error_code)
    {
        this->socket.get_io_service().run_one();
    }

    for(auto const & connection: connections)
    {
        connection.disconnect();
    }

    return status;
}

void
Connection
::tcp_accepted(boost::system::error_code const & error)
{
    ODIL_LOG(DEBUG, dul) << "Transport connection indication";

    if(error)
    {
        throw Exception("Error during accepting: "+error.message());
    }

    if(this->_state == 1)
    {
        // Socket is opened, we can start receiving PDUs.
        this->_receive_handler();
        this->AE_5();
    }
    else
    {
        throw Exception(
            "Connection cannot be accepted in state "
            +std::to_string(this->_state));
    }
}

void
Connection
::_sent_handler(boost::system::error_code const & error)
{
    if(error == boost::asio::error::eof)
    {
        this->socket.get_io_service().post(
            [=]() { this->transport_closed.indication(); });
    }
    else if(error)
    {
        this->socket.get_io_service().post(
            [=]() { this->transport_error.indication(error); });
    }
}

void
Connection
::_receive_handler(boost::system::error_code const & error, ReceiveStage stage)
{
    if(error == boost::asio::error::eof)
    {
        this->transport_closed.indication();
    }
    else if(error == boost::asio::error::bad_descriptor)
    {
        // ODIL_LOG(DEBUG, dul) << "Reading from a closed socket";
    }
    else if(error)
    {
        this->socket.get_io_service().post(
            [=]() { this->transport_error.indication(error); });
    }
    else if(stage == ReceiveStage::Type)
    {
        boost::asio::async_read(
            this->socket, boost::asio::buffer(&this->_incoming[0], 2),
            boost::bind(
                &Connection::_receive_handler, this,
                boost::asio::placeholders::error, ReceiveStage::Length));
    }
    else if(stage == ReceiveStage::Length)
    {
        boost::asio::async_read(
            this->socket, boost::asio::buffer(&this->_incoming[0]+2, 4),
            boost::bind(
                &Connection::_receive_handler, this,
                boost::asio::placeholders::error, ReceiveStage::Data));
    }
    else if(stage == ReceiveStage::Data)
    {
        uint32_t const length = big_endian_to_host(
            *reinterpret_cast<uint32_t*>(&this->_incoming[0]+2));
        this->_incoming.resize(6+length);
        boost::asio::async_read(
            this->socket, boost::asio::buffer(&this->_incoming[0]+6, length),
            boost::bind(
                &Connection::_receive_handler, this,
                boost::asio::placeholders::error, ReceiveStage::Complete));
    }
    else if(stage == ReceiveStage::Complete)
    {
        uint8_t const type = *reinterpret_cast<uint8_t*>(&this->_incoming[0]);
        std::istringstream stream(this->_incoming);

        if(type == AAssociateRQ::type)
        {
            this->_received(std::make_shared<AAssociateRQ>(stream));
        }
        else if(type == AAssociateAC::type)
        {
            this->_received(std::make_shared<AAssociateAC>(stream));
        }
        else if(type == AAssociateRJ::type)
        {
            this->_received(std::make_shared<AAssociateRJ>(stream));
        }
        else if(type == PDataTF::type)
        {
            this->_received(std::make_shared<PDataTF>(stream));
        }
        else if(type == AReleaseRQ::type)
        {
            this->_received(std::make_shared<AReleaseRQ>(stream));
        }
        else if(type == AReleaseRP::type)
        {
            this->_received(std::make_shared<AReleaseRP>(stream));
        }
        else if(type == AAbort::type)
        {
            this->_received(std::make_shared<AAbort>(stream));
        }
        else
        {
            throw Exception("Unknown PDU type: "+std::to_string(type));
        }
        this->_receive_handler();
    }
    else
    {
        throw Exception("Unknown stage");
    }
}

void
Connection
::_received(AAssociateAC::Pointer pdu)
{
    ODIL_LOG(DEBUG, dul) << "Received A-ASSOCIATE-AC";

    if(this->_state == 2) { this->AA_1(); }
    else if(this->_state == 3) { this->AA_8(); }
    else if(this->_state == 5)  { this->_is_requestor = true; this->AE_3(pdu); }
    else if(this->_state >= 6 && this->_state <= 12) { this->AA_8(); }
    else if(this->_state == 13) { this->AA_6(); }
    else
    {
        throw Exception(
            "AAssociateAC cannot be received in state "
            +std::to_string(this->_state));
    }
}

void
Connection
::_received(AAssociateRJ::Pointer pdu)
{
    ODIL_LOG(DEBUG, dul) << "Received A-ASSOCIATE-RJ";

    if(this->_state == 2) { this->AA_1(); }
    else if(this->_state == 3) { this->AA_8(); }
    else if(this->_state == 5) { this->AE_4(pdu); }
    else if(this->_state >= 6 && this->_state <= 12) { this->AA_8(); }
    else if(this->_state == 13) { this->AA_6(); }
    else
    {
        throw Exception(
            "AAssociateRJ cannot be received in state "
            +std::to_string(this->_state));
    }
}

void
Connection
::_received(AAssociateRQ::Pointer pdu)
{
    ODIL_LOG(DEBUG, dul) << "Received A-ASSOCIATE-RQ";
    if(this->_state == 2) { this->AE_6(pdu); }
    else if(this->_state == 3) { this->AA_8(); }
    else if(this->_state >= 5 && this->_state <= 12) { this->AA_8(); }
    else if(this->_state == 13) { this->AA_7(); }
    else
    {
        throw Exception(
            "AAssociateRQ cannot be received in state "
            +std::to_string(this->_state));
    }
}

void
Connection
::_received(PDataTF::Pointer pdu)
{
    ODIL_LOG(DEBUG, dul) << "Received P-DATA-TF";

    if(this->_state == 2) { this->AA_1(); }
    else if(this->_state == 3) { this->AA_8(); }
    else if(this->_state == 5) { this->AA_8(); }
    else if(this->_state == 6) { this->DT_2(pdu); }
    else if(this->_state == 7) { this->AR_6(pdu); }
    else if(this->_state >= 8 && this->_state <= 12) { this->AA_8(); }
    else if(this->_state == 13) { this->AA_6(); }
    else
    {
        throw Exception(
            "AAssociateRQ cannot be received in state "
            +std::to_string(this->_state));
    }
}

void
Connection
::_received(AReleaseRQ::Pointer pdu)
{
    ODIL_LOG(DEBUG, dul) << "Received A-RELEASE-RQ";

    if(this->_state == 2) { this->AA_1(); }
    else if(this->_state == 3) { this->AA_8(); }
    else if(this->_state == 5) { this->AA_8(); }
    else if(this->_state == 6) { this->AR_2(pdu); }
    else if(this->_state == 7) { this->AR_8(pdu); }
    else if(this->_state >= 8 && this->_state <= 12) { this->AA_8(); }
    else if(this->_state == 13) { this->AA_6(); }
    else
    {
        throw Exception(
            "AReleaseRQ cannot be received in state "
            +std::to_string(this->_state));
    }
}

void
Connection
::_received(AReleaseRP::Pointer pdu)
{
    ODIL_LOG(DEBUG, dul) << "Received A-RELEASE-RP";

    if(this->_state == 2) { this->AA_1(); }
    else if(this->_state == 3) { this->AA_8(); }
    else if(this->_state == 5 || this->_state == 6) { this->AA_8(); }
    else if(this->_state == 7) { this->AR_3(pdu); }
    else if(this->_state == 8 && this->_state == 9) { this->AA_8(); }
    else if(this->_state == 10) { this->AR_10(pdu); }
    else if(this->_state == 11) { this->AR_3(pdu); }
    else if(this->_state == 11) { this->AA_8(); }
    else if(this->_state == 13) { this->AA_6(); }
    else
    {
        throw Exception(
            "AReleaseRP cannot be received in state "
            +std::to_string(this->_state));
    }
}

void
Connection
::_received(AAbort::Pointer pdu)
{
    ODIL_LOG(DEBUG, dul) << "Received A-ABORT";

    if(this->_state == 2) { this->AA_2(); }
    else if(this->_state == 3) { this->AA_3(pdu); }
    else if(this->_state >= 5 && this->_state <= 12) { this->AA_3(pdu); }
    else if(this->_state == 13) { this->AA_2(); }
    else
    {
        throw Exception(
            "AAbort cannot be received in state "
            +std::to_string(this->_state));
    }
}

void
Connection
::_artim_expired(boost::system::error_code const & error)
{
    if(error && error == boost::system::errc::operation_canceled)
    {
        ODIL_LOG(DEBUG, dul) << "ARTIM timer canceled";
    }
    else if(error)
    {
        throw Exception("ARTIM expiration error: "+error.message());
    }
    else
    {
        ODIL_LOG(DEBUG, dul) << "ARTIM timer expired";

        if(this->_state == 2) { this->AA_2(); }
        else if(this->_state == 13) { this->AA_2(); }
        else
        {
            throw Exception(
                "ARTIM timer cannot expire in state "
                +std::to_string(this->_state));
        }
    }
}

void
Connection
::_invalid_pdu()
{
    ODIL_LOG(DEBUG, dul) << "Received unrecognized or invalid PDU";

    if(this->_state == 2) { this->AA_1(); }
    else if(this->_state == 3)  { this->AA_8(); }
    else if(this->_state >= 5 && this->_state <= 12)  { this->AA_8(); }
    else if(this->_state == 13)  { this->AA_7(); }
    else
    {
        throw Exception(
            "Invalid PDU cannot be received in state "
            +std::to_string(this->_state));
    }
}

void
Connection
::_async_send(PDU::Pointer pdu)
{
    ODIL_LOG(DEBUG, dul) << "Sending PDU of type " << std::to_string(pdu->get_pdu_type());
    std::ostringstream stream;
    stream << *pdu;
    boost::asio::async_write(
        this->socket, boost::asio::buffer(stream.str()),
        boost::bind(
            &Connection::_sent_handler, this, boost::asio::placeholders::error));
}

void
Connection
::_start_artim_timer()
{
    ODIL_LOG(DEBUG, dul) << "Starting ARTIM timer";
    this->_artim_timer.expires_from_now(this->artim_timeout);
    this->_artim_timer.async_wait(
        boost::bind(
            &Connection::_artim_expired, this,
            boost::asio::placeholders::error()));
}

void
Connection
::_stop_artim_timer()
{
    ODIL_LOG(DEBUG, dul) << "Stopping ARTIM timer";
    this->_artim_timer.expires_at(boost::posix_time::pos_infin);
}

}

}
