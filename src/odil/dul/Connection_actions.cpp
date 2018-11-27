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

void
Connection
::AE_1(AAssociateRQ::Pointer pdu)
{
    logging::trace() << "AE-1";

    // Save the PDU for later (AE-2).
    this->_association_request = pdu;

    this->_state = 4;
    this->socket.get_io_service().post(
        [=]() { this->transport_connection.request(); });
}

void
Connection
::AE_2(AAssociateRQ::Pointer associate_rq)
{
    logging::trace() << "AE-2";

    this->_state = 5;
    this->_send(associate_rq);
}

void
Connection
::AE_3(AAssociateAC::Pointer pdu)
{
    logging::trace() << "AE-3";

    this->_state = 6;
    this->socket.get_io_service().post(
        [=]() { this->a_associate.confirmation(pdu); });
}

void
Connection
::AE_4(AAssociateRJ::Pointer pdu)
{
    logging::trace() << "AE-4";

    this->_state = 1;
    this->socket.get_io_service().post(
        [=]() { this->a_associate.confirmation(pdu); });
    this->socket.close();
}

void
Connection
::AE_5()
{
    logging::trace() << "AE-5";

    this->_state = 2;
    this->socket.get_io_service().post(
        [=]() { this->transport_connection.response(); });
    this->_start_artim_timer();
}

void
Connection
::AE_6(AAssociateRQ::Pointer pdu)
{
    logging::trace() << "AE-6";

    this->_stop_artim_timer();

    auto const response = this->acceptor(pdu);
    if(response->get_pdu_type() == AAssociateAC::type)
    {
        logging::trace() << "Association request accepted";
        this->_state = 3;
        this->socket.get_io_service().post(
            [=]() { this->a_associate.response(response); });
    }
    else if(response->get_pdu_type() == AAssociateRJ::type)
    {
        logging::trace() << "Association request rejected";
        // WARNING: standard says to send RJ and switch to state 13. However,
        // this is AE-8, which needs to happen in state 3.
        this->_state = 3;
        this->socket.get_io_service().post(
            [=]() { this->a_associate.response(response); });
    }
    else if(response->get_pdu_type() == AAbort::type)
    {
        logging::trace() << "Association request aborted";
        this->_state = 3;
        this->socket.get_io_service().post(
            [=]() {
                this->a_abort.request(
                    std::dynamic_pointer_cast<AAbort>(response));
            });
    }
    else
    {
        throw Exception(
            "Invalid association response type: "
            +std::to_string(response->get_pdu_type()));
    }
}

void
Connection
::AE_7(AAssociateAC::Pointer pdu)
{
    logging::trace() << "AE-7";

    this->_state = 6;
    this->_send(pdu);
}

void
Connection
::AE_8(AAssociateRJ::Pointer pdu)
{
    logging::trace() << "AE-8";

    this->_state = 13;
    this->_send(pdu);
    this->_start_artim_timer();
}

void
Connection
::DT_1(PDataTF::Pointer pdu)
{
    logging::trace() << "DT-1";

    this->_state = 6;
    this->_send(pdu);
}

void
Connection
::DT_2(PDataTF::Pointer pdu)
{
    logging::trace() << "DT-2";

    this->_state = 6;
    this->socket.get_io_service().post([=]() { this->p_data.indication(pdu); });
}

void
Connection
::AR_1(AReleaseRQ::Pointer pdu)
{
    logging::trace() << "AR-1";

    this->_state = 7;
    this->_send(pdu);
}

void
Connection
::AR_2(AReleaseRQ::Pointer pdu)
{
    logging::trace() << "AR-2";

    this->_state = 8;
    this->socket.get_io_service().post(
        [=]() { this->a_release.indication(pdu); });
}

void
Connection
::AR_3(AReleaseRP::Pointer pdu)
{
    logging::trace() << "AR-3";

    this->_state = 1;
    this->socket.get_io_service().post(
        [=]() { this->a_release.confirmation(pdu); });
    this->socket.close();
}

void
Connection
::AR_4(AReleaseRP::Pointer pdu)
{
    logging::trace() << "AR-4";

    this->_state = 13;
    this->_send(pdu);
    this->_start_artim_timer();
}

void
Connection
::AR_5()
{
    logging::trace() << "AR-5";

    this->_state = 1;
    this->_stop_artim_timer();
}

void
Connection
::AR_6(PDataTF::Pointer pdu)
{
    logging::trace() << "AR-6";

    this->_state = 7;
    this->socket.get_io_service().post(
        [=]() { this->p_data.indication(pdu); });
}

void
Connection
::AR_7(PDataTF::Pointer pdu)
{
    logging::trace() << "AR-7";

    this->_state = 8;
    this->_send(pdu);
}

void
Connection
::AR_8(AReleaseRQ::Pointer pdu)
{
    logging::trace() << "AR-8";

    this->_state = this->_is_requestor ? 9 : 10;
    this->socket.get_io_service().post(
        [=]() { this->a_release.indication(pdu); });
}

void
Connection
::AR_9(AReleaseRP::Pointer pdu)
{
    logging::trace() << "AR-9";

    this->_state = 11;
    this->_send(pdu);
}

void
Connection
::AR_10(AReleaseRP::Pointer pdu)
{
    logging::trace() << "AR-10";

    this->_state = 12;
    this->socket.get_io_service().post(
        [=]() { this->a_release.confirmation(pdu); });
}

void
Connection
::AA_1(AAbort::Pointer pdu)
{
    logging::trace() << "AA-1";

    this->_state = 13;
    this->_send(pdu);
    this->_start_artim_timer();
}

void
Connection
::AA_2()
{
    logging::trace() << "AA-2";

    this->_state = 1;
    this->_stop_artim_timer();
    this->socket.close();
}

void
Connection
::AA_3(AAbort::Pointer pdu)
{
    logging::trace() << "AA-3";

    this->_state = 1;
    // a_abort is a generic handler (A-ABORT and A-P-ABORT)
    this->socket.get_io_service().post(
        [=]() { this->a_abort.indication(pdu); });
    this->socket.close();
}

void
Connection
::AA_4()
{
    logging::trace() << "AA-4";

    this->_state = 1;
    this->socket.get_io_service().post(
        [=]() { this->a_abort.indication(std::make_shared<AAbort>(2, 0)); });
}

void
Connection
::AA_5()
{
    logging::trace() << "AA-5";

    this->_state = 1;
    this->_stop_artim_timer();
}

void
Connection
::AA_6()
{
    logging::trace() << "AA-6";

    // Ignore PDU
    this->_state = 13;
}

void
Connection
::AA_7()
{
    logging::trace() << "AA-7";

    this->_state = 13;
    this->_send(std::make_shared<AAbort>(1, 0));
}

void
Connection
::AA_8()
{
    logging::trace() << "AA-8";

    this->_state = 13;
    auto pdu = std::make_shared<AAbort>(2, 2);
    this->_send(pdu);
    this->socket.get_io_service().post(
        [=]() { this->a_abort.indication(pdu); });
    this->_start_artim_timer();
}

}

}
