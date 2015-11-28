/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _981c80db_b2ac_4f25_af6c_febf5563d178
#define _981c80db_b2ac_4f25_af6c_febf5563d178

#include <map>
#include <utility>

#include "dcmtkpp/dul/EventData.h"

namespace dcmtkpp
{

namespace dul
{

/// @brief State machine for the DICOM upper layer.
class StateMachine
{
public:

    /// @brief States of the state machine.
    enum class State
    {
        Sta1,
        Sta2, Sta3, Sta4, Sta5,
        Sta6,
        Sta7, Sta8, Sta9, Sta10, Sta11, Sta12,
        Sta13
    };

    /// @brief Event causing the transitions.
    enum class Event
    {
        None, // dummy event to allow easier initialization
        TransportConnectionIndication, TransportConnectionConfirmation,
            TransportConnectionClosedIndication,

        AAssociateRQLocal, AAssociateRQRemote,
        AAssociateACLocal, AAssociateACRemote,
        AAssociateRJLocal, AAssociateRJRemote,

        AReleaseRQLocal, AReleaseRQRemote,
        AReleaseRPLocal, AReleaseRPRemote,

        PDataTFLocal, PDataTFRemote,

        AAbortLocal, AAbortRemote,

        ARTIMTimerExpired, InvalidPDU,
    };

    /// @brief Constructor, initializing to Sta1.
    StateMachine();

    /**
     * @brief Perform the transition related to the event and current state.
     * Raise an exception if no such transition exists.
     */
    void transition(Event const & event, EventData & data);

    /// @brief Return the current state.
    State get_state() const;

    /// @brief Send a PDU to the transport, perform the corresponding transition.
    void send_pdu(EventData & data);

    /// @brief Receive a PDU on the transport, perform the corresponding transition.
    void receive_pdu(EventData & data);
private:

    enum class Action
    {
        AE_1, AE_2, AE_3, AE_4, AE_5, AE_6, AE_7, AE_8,
        DT_1, DT_2,
        AR_1, AR_2, AR_3, AR_4, AR_5, AR_6, AR_7, AR_8, AR_9, AR_10,
        AA_1, AA_2, AA_3, AA_4, AA_5, AA_6, AA_7, AA_8
    };

    typedef std::map<
        std::pair<State, Event>,
        std::pair<Action, State>> TransitionMap;
    static TransitionMap const _transitions;

    /// @brief Current state.
    State _state;

    /// @brief Check the PDU type in data and send it.
    void _send_pdu(EventData & data, uint8_t pdu_type);

    /// @brief Issue TRANSPORT CONNECT request primitive to local transport service.
    void AE_1(EventData & data);

    /// @brief Send A-ASSOCIATE-RQ-PDU.
    void AE_2(EventData & data);

    /// @brief Issue A-ASSOCIATE confirmation (accept) primitive.
    void AE_3(EventData & data);

    /// @brief Issue A-ASSOCIATE confirmation (reject) primitive and close transport connection.
    void AE_4(EventData & data);

    /// @brief Issue Transport connection response primitive; start ARTIM timer.
    void AE_5(EventData & data);

    /// @brief Stop ARTIM timer and accept or reject connection.
    void AE_6(EventData & data);

    /// @brief Send A-ASSOCIATE-AC PDU.
    void AE_7(EventData & data);

    /// @brief Send A-ASSOCIATE-RJ PDU and start ARTIM timer
    void AE_8(EventData & data);

    /// @brief Send P-DATA-TF PDU.
    void DT_1(EventData & data);

    /// @brief Send P-DATA indication primitive.
    void DT_2(EventData & data);
};

}

}

#endif // _981c80db_b2ac_4f25_af6c_febf5563d178
