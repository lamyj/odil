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

/**
 * @brief DICOM Upper Layer connection.
 *
 * This class asynchronously sends and receives PDUs.
 */
class Connection
{
public:
    boost::posix_time::time_duration artim_timeout;

    Connection(
        boost::asio::io_context & io_context,
        boost::asio::ip::tcp::endpoint const & endpoint,
        boost::posix_time::time_duration artim_timeout=boost::posix_time::seconds(30));

    ~Connection() = default;

    Connection(Connection const &) = delete;
    Connection(Connection &&) = delete;
    Connection & operator=(Connection const &) = delete;
    Connection & operator=(Connection &&) = delete;

    boost::asio::ip::tcp::socket & get_socket();

    void async_send(std::shared_ptr<pdu::AAssociateRQ> pdu);
    void async_send(std::shared_ptr<pdu::AAssociateAC> pdu);
    void async_send(std::shared_ptr<pdu::AAssociateRJ> pdu);
    void async_send(std::shared_ptr<pdu::PDataTF> pdu);
    void async_send(std::shared_ptr<pdu::AReleaseRQ> pdu);
    void async_send(std::shared_ptr<pdu::AReleaseRP> pdu);
    void async_send(std::shared_ptr<pdu::AAbort> pdu);

    void async_receive();

    void tcp_accepted(boost::system::error_code const & error);

    /**
     * @addtogroup dul_indications DICOM Upper Layer indications
     * @{
     */

    // Transport-related indications
    boost::signals2::signal<void(boost::system::error_code)> transport_error;

    // Generic indications
    boost::signals2::signal<void()> accepted;

    // PDU-related indications
    boost::signals2::signal<void(std::shared_ptr<pdu::AAssociateAC>)> a_associate_ac;
    boost::signals2::signal<void(std::shared_ptr<pdu::AAssociateRJ>)> a_associate_rj;
    boost::signals2::signal<
            std::shared_ptr<pdu::Object>(std::shared_ptr<pdu::AAssociateRQ>)
        > a_associate_rq;
    boost::signals2::signal<void(std::shared_ptr<pdu::PDataTF>)> p_data;
    boost::signals2::signal<void(std::shared_ptr<pdu::AReleaseRQ>)> a_release_rq;
    boost::signals2::signal<void(std::shared_ptr<pdu::AReleaseRP>)> a_release_rp;
    boost::signals2::signal<void(std::shared_ptr<pdu::AAbort>)> a_abort;

    /// @}

private:
    enum class ReceiveStage
    {
        Type,
        Length,
        Data,
        Complete
    };

    boost::asio::io_context & _io_context;
    boost::asio::ip::tcp::endpoint _endpoint;
    boost::asio::ip::tcp::socket _socket;
    std::atomic_int _state;
    std::string _incoming;
    boost::asio::deadline_timer _artim_timer;

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

    void AE_1(std::shared_ptr<pdu::AAssociateRQ> pdu);
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

}

}

#endif // _b252f437_dc81_4b9b_bd7d_7ba70a114e5a
