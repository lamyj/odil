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

#include "odil/pdu/AAbort.h"
#include "odil/pdu/AAssociateAC.h"
#include "odil/pdu/AAssociateRJ.h"
#include "odil/pdu/AAssociateRQ.h"
#include "odil/pdu/AReleaseRP.h"
#include "odil/pdu/AReleaseRQ.h"
#include "odil/pdu/PDataTF.h"

namespace odil
{

namespace dul
{

enum class Signal
{
    // Transport-related signals
    TransportConnected,
    TransportClosed,
    TransportAccepted,
    TransportError,
    Accepted,
    // Signals emitted when a PDU is received
    AAssociateRQ,
    AAssociateAC,
    AAssociateRJ,
    PDataTF,
    AReleaseRQ,
    AReleaseRP,
    AAbort,
};

template<Signal S>
struct SignalTraits;

#define ODIL_SIGNAL_TRAITS(S, T) \
    template<> \
    struct SignalTraits<Signal::S> \
    { \
        typedef boost::signals2::signal<T> Type; \
    };

ODIL_SIGNAL_TRAITS(TransportConnected, void(boost::system::error_code));
ODIL_SIGNAL_TRAITS(TransportClosed, void(boost::system::error_code));
ODIL_SIGNAL_TRAITS(TransportAccepted, void(boost::system::error_code));
ODIL_SIGNAL_TRAITS(TransportError, void(boost::system::error_code));
ODIL_SIGNAL_TRAITS(Accepted, void());
ODIL_SIGNAL_TRAITS(AAssociateRQ, std::shared_ptr<pdu::Object>(std::shared_ptr<pdu::AAssociateRQ>));
ODIL_SIGNAL_TRAITS(AAssociateAC, void(std::shared_ptr<pdu::AAssociateAC>));
ODIL_SIGNAL_TRAITS(AAssociateRJ, void(std::shared_ptr<pdu::AAssociateRJ>));
ODIL_SIGNAL_TRAITS(PDataTF, void(std::shared_ptr<pdu::PDataTF>));
ODIL_SIGNAL_TRAITS(AReleaseRQ, void(std::shared_ptr<pdu::AReleaseRQ>));
ODIL_SIGNAL_TRAITS(AReleaseRP, void(std::shared_ptr<pdu::AReleaseRP>));
ODIL_SIGNAL_TRAITS(AAbort, void(std::shared_ptr<pdu::AAbort>));

#undef ODIL_SIGNAL_TRAITS

/**
 * @brief DICOM Upper Layer connection.
 *
 * This class asynchronously sends and receives PDUs.
 */
class Connection
{
public:
    boost::asio::io_context & io_context;
    boost::asio::ip::tcp::socket & socket;
    boost::posix_time::time_duration artim_timeout;

    Connection(
        boost::asio::io_context & io_context,
        boost::asio::ip::tcp::socket & socket,
        boost::posix_time::time_duration artim_timeout=boost::posix_time::seconds(30));

    ~Connection() = default;

    Connection(Connection const &) = delete;
    Connection(Connection &&) = delete;
    Connection & operator=(Connection const &) = delete;
    Connection & operator=(Connection &&) = delete;

    void async_send(
        boost::asio::ip::tcp::endpoint const & endpoint,
        std::shared_ptr<pdu::AAssociateRQ> pdu);
    void async_send(std::shared_ptr<pdu::AAssociateAC> pdu);
    void async_send(std::shared_ptr<pdu::AAssociateRJ> pdu);
    void async_send(std::shared_ptr<pdu::PDataTF> pdu);
    void async_send(std::shared_ptr<pdu::AReleaseRQ> pdu);
    void async_send(std::shared_ptr<pdu::AReleaseRP> pdu);
    void async_send(std::shared_ptr<pdu::AAbort> pdu);

    void async_receive();

    /// @brief Handler for the TCP Transport Connection Indication
    void tcp_accepted(boost::system::error_code const & error);

    /// @brief Connect a slot to one of the signals.
    template<Signal S>
    boost::signals2::connection connect(typename SignalTraits<S>::Type::slot_type slot);

private:
    enum class ReceiveStage
    {
        Type,
        Length,
        Data,
        Complete
    };

    std::atomic_int _state;
    std::string _incoming;
    boost::asio::deadline_timer _artim_timer;
    bool _is_requestor;

#define ODIL_SIGNAL(S) \
    typename SignalTraits<Signal::S>::Type _##S

    ODIL_SIGNAL(TransportConnected);
    ODIL_SIGNAL(TransportClosed);
    ODIL_SIGNAL(TransportAccepted);
    ODIL_SIGNAL(TransportError);
    ODIL_SIGNAL(Accepted);
    ODIL_SIGNAL(AAssociateRQ);
    ODIL_SIGNAL(AAssociateAC);
    ODIL_SIGNAL(AAssociateRJ);
    ODIL_SIGNAL(PDataTF);
    ODIL_SIGNAL(AReleaseRQ);
    ODIL_SIGNAL(AReleaseRP);
    ODIL_SIGNAL(AAbort);

#undef ODIL_SIGNAL

    /// @addtogroup dul_handlers boost::asio handlers
    /// @{

    void _connect_handler(
        boost::system::error_code const & error,
        std::shared_ptr<pdu::AAssociateRQ> associate_rq);

    void _sent_handler(boost::system::error_code const & error);

    void _receive_handler(
            boost::system::error_code const & error=boost::system::error_code(),
            ReceiveStage stage=ReceiveStage::Type);

    /// @}

    /// @addtogroup dul_events DICOM Upper Layer events
    /// @{

    void _transport_connected(std::shared_ptr<pdu::AAssociateRQ> pdu);
    void _received(std::shared_ptr<pdu::AAssociateAC> pdu);
    void _received(std::shared_ptr<pdu::AAssociateRJ> pdu);
    void _received(std::shared_ptr<pdu::AAssociateRQ> pdu);
    void _received(std::shared_ptr<pdu::PDataTF> pdu);
    void _received(std::shared_ptr<pdu::AReleaseRQ> pdu);
    void _received(std::shared_ptr<pdu::AReleaseRP> pdu);
    void _received(std::shared_ptr<pdu::AAbort> pdu);
    void _transport_closed();
    void _artim_expired(boost::system::error_code const & error);
    void _invalid_pdu();

    /// @}

    /**
     * @addtogroup dul_actions DICOM Upper Layer actions
     * @warning indications are synchronous: they should be called through
     * boost::asio::post to avoid deadlock when holding the state mutex.
     * @{
     */

    void AE_1(
        boost::asio::ip::tcp::endpoint const & endpoint,
        std::shared_ptr<pdu::AAssociateRQ> pdu);
    void AE_2(std::shared_ptr<pdu::AAssociateRQ> pdu);
    void AE_3(std::shared_ptr<pdu::AAssociateAC> pdu);
    void AE_4(std::shared_ptr<pdu::AAssociateRJ> pdu);
    void AE_5();
    void AE_6(std::shared_ptr<pdu::AAssociateRQ> pdu);
    void AE_7(std::shared_ptr<pdu::AAssociateAC> pdu);
    void AE_8(std::shared_ptr<pdu::AAssociateRJ> pdu);

    void DT_1(std::shared_ptr<pdu::PDataTF> pdu);
    void DT_2(std::shared_ptr<pdu::PDataTF> pdu);

    void AR_1(std::shared_ptr<pdu::AReleaseRQ> pdu);
    void AR_2(std::shared_ptr<pdu::AReleaseRQ> pdu);
    void AR_3(std::shared_ptr<pdu::AReleaseRP> pdu);
    void AR_4(std::shared_ptr<pdu::AReleaseRP> pdu);
    void AR_5();
    void AR_6(std::shared_ptr<pdu::PDataTF> pdu);
    void AR_7(std::shared_ptr<pdu::PDataTF> pdu);
    void AR_8(std::shared_ptr<pdu::AReleaseRQ> pdu);
    void AR_9(std::shared_ptr<pdu::AReleaseRP> pdu);
    void AR_10(std::shared_ptr<pdu::AReleaseRP> pdu);

    void AA_1(std::shared_ptr<pdu::AAbort> pdu=std::make_shared<pdu::AAbort>(0, 0));
    void AA_2();
    void AA_3(std::shared_ptr<pdu::AAbort> pdu);
    void AA_4();
    void AA_5();
    void AA_6();
    void AA_7();
    void AA_8();

    /// @}

    void _async_send(std::shared_ptr<pdu::Object> pdu);

    void _start_artim_timer();
    void _stop_artim_timer();
};

#define ODIL_CONNECT(S) \
template<> \
boost::signals2::connection \
Connection \
::connect<Signal::S>(typename SignalTraits<Signal::S>::Type::slot_type slot)

ODIL_CONNECT(TransportConnected);
ODIL_CONNECT(TransportClosed);
ODIL_CONNECT(TransportAccepted);
ODIL_CONNECT(TransportError);
ODIL_CONNECT(Accepted);
ODIL_CONNECT(AAssociateRQ);
ODIL_CONNECT(AAssociateAC);
ODIL_CONNECT(AAssociateRJ);
ODIL_CONNECT(PDataTF);
ODIL_CONNECT(AReleaseRQ);
ODIL_CONNECT(AReleaseRP);
ODIL_CONNECT(AAbort);

#undef ODIL_CONNECT

}

}

#endif // _b252f437_dc81_4b9b_bd7d_7ba70a114e5a
