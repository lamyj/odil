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
    boost::asio::io_context & io_context, boost::asio::ip::tcp::socket & socket,
    boost::posix_time::time_duration artim_timeout)
: io_context(io_context), socket(socket), artim_timeout(artim_timeout),
     _state(1), _incoming(6, '\0'), _artim_timer(io_context),
    _is_requestor(false)
{
    this->connect<Signal::AReleaseRQ>(
        [this](std::shared_ptr<AReleaseRQ> /* pdu */) {
            this->async_send(std::make_shared<AReleaseRP>());
        }
    );
}

void
Connection
::async_send(
    boost::asio::ip::tcp::endpoint const & endpoint,
    std::shared_ptr<AAssociateRQ> pdu)
{
    ODIL_LOG(DEBUG, dul) << "Sending A-ASSOCIATE-RQ";

    if(this->_state == 1)
    {
        this->AE_1(endpoint, pdu);
    }
    else
    {
        throw Exception(
            "Cannot send AAssociateRQ in state "+std::to_string(this->_state));
    }
}

void
Connection
::async_send(std::shared_ptr<AAssociateAC> pdu)
{
    ODIL_LOG(DEBUG, dul) << "Sending A-ASSOCIATE-AC";

    if(this->_state == 3)
    {
        this->AE_7(pdu);
    }
    else
    {
        throw Exception(
            "Cannot send AAssociateAC in state "+std::to_string(this->_state));
    }
}

void
Connection
::async_send(std::shared_ptr<AAssociateRJ> pdu)
{
    ODIL_LOG(DEBUG, dul) << "Sending A-ASSOCIATE-RJ";

    if(this->_state == 3)
    {
        this->AE_8(pdu);
    }
    else
    {
        throw Exception(
            "Cannot send AAssociateRJ in state "+std::to_string(this->_state));
    }
}

void
Connection
::async_send(std::shared_ptr<PDataTF> pdu)
{
    ODIL_LOG(DEBUG, dul) << "Sending P-DATA-TF";

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
}

void
Connection
::async_send(std::shared_ptr<AReleaseRQ> pdu)
{
    ODIL_LOG(DEBUG, dul) << "Sending A-RELEASE-RQ";

    if(this->_state == 6)
    {
        this->AR_1(pdu);
    }
    else
    {
        throw Exception(
            "Cannot send AReleaseRQ in state "+std::to_string(this->_state));
    }
}

void
Connection
::async_send(std::shared_ptr<AReleaseRP> pdu)
{
    ODIL_LOG(DEBUG, dul) << "Sending A-RELEASE-RP";

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
}

void
Connection
::async_send(std::shared_ptr<AAbort> pdu)
{
    ODIL_LOG(DEBUG, dul) << "Sending A-ABORT";

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
}

void
Connection
::async_receive()
{
    this->_receive_handler();
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
        this->async_receive();
        this->AE_5();
    }
    else
    {
        throw Exception(
            "Connection cannot be accepted in state "
            +std::to_string(this->_state));
    }
}

#define ODIL_SIGNAL_CONNECT(S) \
template<> \
boost::signals2::connection \
Connection \
::connect<Signal::S>( \
    typename SignalTraits<Signal::S>::Type::slot_type slot) \
{ \
    return this->_##S.connect(slot); \
}

ODIL_SIGNAL_CONNECT(TransportConnected)
ODIL_SIGNAL_CONNECT(TransportClosed)
ODIL_SIGNAL_CONNECT(TransportAccepted)
ODIL_SIGNAL_CONNECT(TransportError)
ODIL_SIGNAL_CONNECT(Accepted)
ODIL_SIGNAL_CONNECT(AAssociateRQ)
ODIL_SIGNAL_CONNECT(AAssociateAC)
ODIL_SIGNAL_CONNECT(AAssociateRJ)
ODIL_SIGNAL_CONNECT(PDataTF)
ODIL_SIGNAL_CONNECT(AReleaseRQ)
ODIL_SIGNAL_CONNECT(AReleaseRP)
ODIL_SIGNAL_CONNECT(AAbort)

#undef ODIL_SIGNAL_CONNECT

void
Connection
::_connect_handler(
    boost::system::error_code const & error,
    std::shared_ptr<AAssociateRQ> associate_rq)
{
    if(error)
    {
        ODIL_LOG(DEBUG, dul) << "Transport error in _connect_handler";
        boost::asio::post(
            this->io_context, [=]() { this->_TransportError(error); });
    }
    else
    {
        this->_transport_connected(associate_rq);
    }
}

void
Connection
::_sent_handler(boost::system::error_code const & error)
{
    if(error == boost::asio::error::eof)
    {
        this->_transport_closed();
    }
    else if(error)
    {
        ODIL_LOG(DEBUG, dul) << "Transport error in _sent_handler";
        boost::asio::post(
            this->io_context, [=]() { this->_TransportError(error); });
    }
}

void
Connection
::_receive_handler(boost::system::error_code const & error, ReceiveStage stage)
{
    if(error == boost::asio::error::eof)
    {
        this->_transport_closed();
    }
    else if(error == boost::asio::error::bad_descriptor)
    {
        // ODIL_LOG(DEBUG, dul) << "Reading from a closed socket";
    }
    else if(error)
    {
        boost::asio::post(
            this->io_context, [=]() { this->_TransportError(error); });
    }
    else if(stage == ReceiveStage::Type)
    {
        boost::asio::async_read(
            this->socket, boost::asio::buffer(this->_incoming, 2),
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
        this->async_receive();
    }
    else
    {
        throw Exception("Unknown stage");
    }
}

void
Connection
::_transport_connected(std::shared_ptr<AAssociateRQ> associate_rq)
{
    ODIL_LOG(DEBUG, dul) << "Transport connection confirmation";

    if(this->_state == 4)
    {
        // Socket is opened, we can start receiving PDUs.
        this->async_receive();
        this->AE_2(associate_rq);
    }
    else
    {
        throw Exception(
            "No connection must happen in state "+std::to_string(this->_state));
    }
}

void
Connection
::_received(std::shared_ptr<AAssociateAC> pdu)
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
::_received(std::shared_ptr<AAssociateRJ> pdu)
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
::_received(std::shared_ptr<AAssociateRQ> pdu)
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
::_received(std::shared_ptr<PDataTF> pdu)
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
::_received(std::shared_ptr<AReleaseRQ> pdu)
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
::_received(std::shared_ptr<AReleaseRP> pdu)
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
::_received(std::shared_ptr<AAbort> pdu)
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
::_transport_closed()
{
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
::AE_1(
    boost::asio::ip::tcp::endpoint const & endpoint,
    std::shared_ptr<AAssociateRQ> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AE-1";

    this->_state = 4;
    this->socket.async_connect(
        endpoint,
        boost::bind(
            &Connection::_connect_handler, this,
            boost::asio::placeholders::error, pdu));
}

void
Connection
::AE_2(std::shared_ptr<AAssociateRQ> associate_rq)
{
    ODIL_LOG(DEBUG, dul) << "AE-2";

    this->_state = 5;
    this->_async_send(associate_rq);
}

void
Connection
::AE_3(std::shared_ptr<AAssociateAC> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AE-3";

    this->_state = 6;
    boost::asio::post(this->io_context, [=]() { this->_AAssociateAC(pdu); });
}

void
Connection
::AE_4(std::shared_ptr<AAssociateRJ> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AE-4";

    this->_state = 1;
    boost::asio::post(this->io_context, [=]() { this->_AAssociateRJ(pdu); });
    this->socket.close();
}

void
Connection
::AE_5()
{
    ODIL_LOG(DEBUG, dul) << "AE-5";

    this->_state = 2;
    boost::asio::post(this->io_context, [=]() { this->_Accepted(); });
    this->_start_artim_timer();
}

void
Connection
::AE_6(std::shared_ptr<AAssociateRQ> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AE-6";

    this->_stop_artim_timer();

    boost::optional<std::shared_ptr<PDU>> signal_result = this->_AAssociateRQ(pdu);
    if(!signal_result || signal_result.get() == nullptr)
    {
        throw Exception("No response provided");
    }

    std::shared_ptr<PDU> response = signal_result.get();
    auto const type = response->get_pdu_type();
    if(type == AAssociateAC::type)
    {

        this->_state = 3;
        this->async_send(std::dynamic_pointer_cast<AAssociateAC>(response));
    }
    else if(type == AAssociateRJ::type)
    {
        // WARNING: standard says to send RJ and switch to state 13. However,
        // this is AE-8, which needs to happen in state 3.
        this->_state = 3;
        this->async_send(std::dynamic_pointer_cast<AAssociateRJ>(response));
    }
    else if(type == AAbort::type)
    {
        // WARNING: not sure this is correct
        this->_state = 3;
        this->async_send(std::dynamic_pointer_cast<AAbort>(response));
    }
    else
    {
        throw Exception(
            "Invalid association response type: "+std::to_string(type));
    }
}

void
Connection
::AE_7(std::shared_ptr<AAssociateAC> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AE-7";

    this->_state = 6;
    this->_async_send(pdu);
}

void
Connection
::AE_8(std::shared_ptr<AAssociateRJ> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AE-8";

    this->_state = 13;
    this->_async_send(pdu);
    this->_start_artim_timer();
}

void
Connection
::DT_1(std::shared_ptr<PDataTF> pdu)
{
    ODIL_LOG(DEBUG, dul) << "DT-1";

    this->_state = 6;
    this->_async_send(pdu);
}

void
Connection
::DT_2(std::shared_ptr<PDataTF> pdu)
{
    ODIL_LOG(DEBUG, dul) << "DT-2";

    this->_state = 6;
    boost::asio::post(this->io_context, [=]() { this->_PDataTF(pdu); });
}

void
Connection
::AR_1(std::shared_ptr<AReleaseRQ> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AR-1";

    this->_state = 7;
    this->_async_send(pdu);
}

void
Connection
::AR_2(std::shared_ptr<AReleaseRQ> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AR-2";

    this->_state = 8;
    boost::asio::post(this->io_context, [=]() { this->_AReleaseRQ(pdu); });
}

void
Connection
::AR_3(std::shared_ptr<AReleaseRP> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AR-3";

    this->_state = 1;
    boost::asio::post(this->io_context, [=]() { this->_AReleaseRP(pdu); });
    this->socket.close();
}

void
Connection
::AR_4(std::shared_ptr<AReleaseRP> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AR-4";

    this->_state = 13;
    this->_async_send(pdu);
    this->_start_artim_timer();
}

void
Connection
::AR_5()
{
    ODIL_LOG(DEBUG, dul) << "AR-5";

    this->_state = 1;
    this->_stop_artim_timer();
}

void
Connection
::AR_6(std::shared_ptr<PDataTF> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AR-6";

    this->_state = 7;
    boost::asio::post(this->io_context, [=]() { this->_PDataTF(pdu); });
}

void
Connection
::AR_7(std::shared_ptr<PDataTF> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AR-7";

    this->_state = 8;
    this->_async_send(pdu);
}

void
Connection
::AR_8(std::shared_ptr<AReleaseRQ> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AR-8";

    this->_state = this->_is_requestor ? 9 : 10;
    boost::asio::post(this->io_context, [=]() { this->_AReleaseRQ(pdu); });
}

void
Connection
::AR_9(std::shared_ptr<AReleaseRP> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AR-9";

    this->_state = 11;
    this->_async_send(pdu);
}

void
Connection
::AR_10(std::shared_ptr<AReleaseRP> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AR-10";

    this->_state = 12;
    boost::asio::post(this->io_context, [=]() { this->_AReleaseRP(pdu); });
}

void
Connection
::AA_1(std::shared_ptr<AAbort> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AA-1";

    this->_state = 13;
    this->_async_send(pdu);
    this->_start_artim_timer();
}

void
Connection
::AA_2()
{
    ODIL_LOG(DEBUG, dul) << "AA-2";

    this->_state = 1;
    this->_stop_artim_timer();
    this->socket.close();
}

void
Connection
::AA_3(std::shared_ptr<AAbort> pdu)
{
    ODIL_LOG(DEBUG, dul) << "AA-3";

    this->_state = 1;
    // a_abort is a generic handler (A-ABORT and A-P-ABORT)
    this->_AAbort(pdu);
    this->socket.close();
}

void
Connection
::AA_4()
{
    ODIL_LOG(DEBUG, dul) << "AA-4";

    this->_state = 1;
    boost::asio::post(
        this->io_context,
        [=]() { this->_AAbort(std::make_shared<AAbort>(2, 0)); });
}

void
Connection
::AA_5()
{
    ODIL_LOG(DEBUG, dul) << "AA-5";

    this->_state = 1;
    this->_stop_artim_timer();
}

void
Connection
::AA_6()
{
    ODIL_LOG(DEBUG, dul) << "AA-6";

    // Ignore PDU
    this->_state = 13;
}

void
Connection
::AA_7()
{
    ODIL_LOG(DEBUG, dul) << "AA-7";

    this->_state = 13;
    this->_async_send(std::make_shared<AAbort>(1, 0));
}

void
Connection
::AA_8()
{
    ODIL_LOG(DEBUG, dul) << "AA-8";

    this->_state = 13;
    auto pdu = std::make_shared<AAbort>(2, 2);
    this->_async_send(pdu);
    boost::asio::post(this->io_context, [=]() { this->_AAbort(pdu); });
    this->_start_artim_timer();
}

void
Connection
::_async_send(std::shared_ptr<PDU> pdu)
{
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
