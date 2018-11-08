/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b252f437_dc81_4b9b_bd7d_7ba70a114e5a
#define _b252f437_dc81_4b9b_bd7d_7ba70a114e5a

#include <atomic>
#include <string>

#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <boost/system/error_code.hpp>

#include "odil/odil.h"
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

/// @brief Primitives associated with an OSI service.
template<typename Request, typename Indication>
class Service
{
public:
    boost::signals2::signal<Request> request;
    boost::signals2::signal<Indication> indication;
};

/// @brief Primitives associated with an OSI confirmed service.
template<
        typename Request, typename Indication,
        typename Response, typename Confirmation>
class ConfirmedService: public Service<Request, Indication>
{
public:
    boost::signals2::signal<Response> response;
    boost::signals2::signal<Confirmation> confirmation;
};

/**
 * @brief DICOM Upper Layer connection.
 *
 * This class asynchronously sends and receives PDUs.
 * 
 * @warning The io_context from the socket will be used to dispatch every action
 */
class ODIL_API Connection
{
public:
    /// @brief Acceptor function: its value is returned to the requestor.
    using Acceptor = std::function<PDU::Pointer(AAssociateRQ::Pointer)>;

    /**
     * @addtogroup dul_primitives DICOM Upper Layer service primitives
     * @warning Primitives should not be called directly by the user. However,
     *   in order to facilitate slot connection, these are kept public.
     * @{
     */

    /// @brief Connection of the underlying TCP transport.
    ConfirmedService<
            void(), void(boost::system::error_code),
            void(), void(boost::system::error_code)
        > transport_connection;

    /// @brief Error on the underlying TCP transport.
    Service<void(), void(boost::system::error_code)> transport_error;

    /// @brief Closing of the underlying TCP transport.
    Service<void(), void()> transport_closed;

    /// @brief A-ASSOCIATE service, PS 3.8, 7.1.
    ConfirmedService<
            void(AAssociateRQ::Pointer), void(AAssociateRQ::Pointer),
            void(PDU::Pointer), void(PDU::Pointer)
        > a_associate;

    /// @brief A-RELEASE service, PS 3.8, 7.2.
    ConfirmedService<
            void(AReleaseRQ::Pointer), void(AReleaseRQ::Pointer),
            void(AReleaseRP::Pointer), void(AReleaseRP::Pointer)
        > a_release;

    /// @brief A-ABORT service, PS 3.8, 7.3
    Service<void(AAbort::Pointer), void(AAbort::Pointer)> a_abort;

    /// @brief A-P-ABORT service, PS 3.8, 7.4
    Service<void(AAbort::Pointer), void(AAbort::Pointer)> a_p_abort;

    /// @brief P-DATA service, PS 3.8, 7.6
    Service<void(PDataTF::Pointer), void(PDataTF::Pointer)> p_data;

    /// @}

    /// @brief Network socket for the underlying TCP transport.
    boost::asio::ip::tcp::socket & socket;

    /// @brief Timeout for the ARTIM timer.
    boost::posix_time::time_duration artim_timeout;

    /// @brief Acceptor function, used when the connection is acceptor.
    Acceptor acceptor;

    Connection(
        boost::asio::ip::tcp::socket & socket,
        boost::posix_time::time_duration artim_timeout=boost::posix_time::seconds(30));

    ~Connection() = default;

    Connection(Connection const &) = delete;
    Connection(Connection &&) = delete;
    Connection & operator=(Connection const &) = delete;
    Connection & operator=(Connection &&) = delete;

    /// @brief Asynchronously send an A-ASSOCIATE-RQ PDU to the given peer.
    void send(boost::asio::ip::tcp::endpoint peer, AAssociateRQ::Pointer pdu);

    /// @brief Asynchronously send any non-A-ASSOCIATE-RQ PDU.
    void send(PDU::Pointer pdu);

    /// @brief Return the current state of the state machine.
    int get_state() const;

private:
    /// @brief Reception stage of a PDU
    enum class ReceiveStage
    {
        Type,
        Length,
        Data,
        Complete
    };

    /// @brief Current state of the state machine.
    std::atomic_int _state;

    /// @brief Buffer holding an incoming pdu
    std::string _incoming;

    /// @brief Association release or time-out timer.
    boost::asio::deadline_timer _artim_timer;

    /// @brief Whether the connection is currently a requestor or an acceptor.
    bool _is_requestor;

    /// @brief Peer to connect to, used when the connection is requestor.
    boost::asio::ip::tcp::endpoint _peer;

    /// @brief A-ASSOCIATE-RQ PDU from latest A-ASSOCIATE request primitive.
    AAssociateRQ::Pointer _association_request;

    /// @addtogroup dul_handlers boost::asio handlers
    /// @{

    void _sent_handler(boost::system::error_code const & error);

    void _receive_handler(
            boost::system::error_code const & error=boost::system::error_code(),
            ReceiveStage stage=ReceiveStage::Type);

    /// @}

    /// @addtogroup dul_events DICOM Upper Layer events
    /// @{

    void _received(AAssociateAC::Pointer pdu);
    void _received(AAssociateRJ::Pointer pdu);
    void _received(AAssociateRQ::Pointer pdu);
    void _received(PDataTF::Pointer pdu);
    void _received(AReleaseRQ::Pointer pdu);
    void _received(AReleaseRP::Pointer pdu);
    void _received(AAbort::Pointer pdu);
    void _artim_expired(boost::system::error_code const & error);
    void _invalid_pdu();

    /// @}

    /**
     * @addtogroup dul_actions DICOM Upper Layer actions
     * @{
     */

    void AE_1(AAssociateRQ::Pointer pdu);
    void AE_2(AAssociateRQ::Pointer pdu);
    void AE_3(AAssociateAC::Pointer pdu);
    void AE_4(AAssociateRJ::Pointer pdu);
    void AE_5();
    void AE_6(AAssociateRQ::Pointer pdu);
    void AE_7(AAssociateAC::Pointer pdu);
    void AE_8(AAssociateRJ::Pointer pdu);

    void DT_1(PDataTF::Pointer pdu);
    void DT_2(PDataTF::Pointer pdu);

    void AR_1(AReleaseRQ::Pointer pdu);
    void AR_2(AReleaseRQ::Pointer pdu);
    void AR_3(AReleaseRP::Pointer pdu);
    void AR_4(AReleaseRP::Pointer pdu);
    void AR_5();
    void AR_6(PDataTF::Pointer pdu);
    void AR_7(PDataTF::Pointer pdu);
    void AR_8(AReleaseRQ::Pointer pdu);
    void AR_9(AReleaseRP::Pointer pdu);
    void AR_10(AReleaseRP::Pointer pdu);

    void AA_1(AAbort::Pointer pdu=std::make_shared<AAbort>(0, 0));
    void AA_2();
    void AA_3(AAbort::Pointer pdu);
    void AA_4();
    void AA_5();
    void AA_6();
    void AA_7();
    void AA_8();

    /// @}

    /// @brief Send the PDU without checking state consistency.
    void _send(PDU::Pointer pdu);

    /// @brief Start or restart the ARTIM timer.
    void _start_artim_timer();

    /// @brief Stop the ARTIM timer.
    void _stop_artim_timer();
};

}

}

#endif // _b252f437_dc81_4b9b_bd7d_7ba70a114e5a
