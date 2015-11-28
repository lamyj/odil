/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/dul/StateMachine.h"

#include <cstdint>
#include <map>
#include <sstream>
#include <utility>

#include "dcmtkpp/endian.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/dul/EventData.h"
#include "dcmtkpp/pdu/AAbort.h"
#include "dcmtkpp/pdu/AAssociate.h"
#include "dcmtkpp/pdu/AAssociateRJ.h"
#include "dcmtkpp/pdu/AReleaseRP.h"
#include "dcmtkpp/pdu/AReleaseRQ.h"
#include "dcmtkpp/pdu/PDataTF.h"

namespace dcmtkpp
{

namespace dul
{

StateMachine
::StateMachine()
: _state(State::Sta1)
{
    // Nothing else.
}

void
StateMachine
::transition(Event const & event, EventData & data)
{
    auto const iterator = StateMachine::_transitions.find(
        std::make_pair(this->_state, event));
    if(iterator == StateMachine::_transitions.end())
    {
        throw Exception("No such transition");
    }

    auto const & action = iterator->second.first;
    auto const & next_state = iterator->second.second;

    // Do action
#define dispatch_action(id, data) if(action == Action::id) { this->id(data); }
    if(action == Action::AE_1) { this->AE_1(data); }
    else if(action == Action::AE_2) { this->AE_2(data); }
    else if(action == Action::AE_3) { this->AE_3(data); }
    else if(action == Action::AE_4) { this->AE_4(data); }
    else if(action == Action::AE_5) { this->AE_5(data); }
    else if(action == Action::AE_6) { this->AE_6(data); }
    else if(action == Action::AE_7) { this->AE_7(data); }
    else if(action == Action::AE_8) { this->AE_8(data); }
    else if(action == Action::DT_1) { this->DT_1(data); }
    else if(action == Action::DT_2) { this->DT_2(data); }
//    dispatch_action(AR_1);
//    dispatch_action(AR_2);
//    dispatch_action(AR_3);
//    dispatch_action(AR_4);
//    dispatch_action(AR_5);
//    dispatch_action(AR_6);
//    dispatch_action(AR_7);
//    dispatch_action(AR_8);
//    dispatch_action(AR_9);
//    dispatch_action(AR_10);
//    dispatch_action(AA_1);
//    dispatch_action(AA_2);
//    dispatch_action(AA_3);
//    dispatch_action(AA_4);
//    dispatch_action(AA_5);
//    dispatch_action(AA_6);
//    dispatch_action(AA_7);
//    dispatch_action(AA_8);
    else
    {
        throw Exception("Unknown action");
    }

    this->_state = next_state;
}

StateMachine::State
StateMachine
::get_state() const
{
    return this->_state;
}

void
StateMachine
::send_pdu(EventData & data)
{
    if(data.transport == nullptr)
    {
        throw Exception("No transport");
    }
    if(data.pdu == nullptr)
    {
        throw Exception("No PDU");
    }
    auto const & item = data.pdu->get_item();
    auto const type = item.as_unsigned_int_8("PDU-type");

    if(type == 0x01)
    {
        this->transition(Event::AAssociateRQLocal, data);
        this->transition(Event::TransportConnectionConfirmation, data);
    }
    else if(type == 0x02)
    {
        this->transition(Event::AAssociateACLocal, data);
    }
    else if(type == 0x03)
    {
        this->transition(Event::AAssociateRJLocal, data);
    }
    else if(type == 0x04)
    {
        this->transition(Event::PDataTFLocal, data);
    }
    else if(type == 0x05)
    {
        this->transition(Event::AReleaseRQLocal, data);
    }
    else if(type == 0x06)
    {
        this->transition(Event::AReleaseRPLocal, data);
    }
    else if(type == 0x07)
    {
        this->transition(Event::AAbortLocal, data);
    }
    else
    {
        this->transition(Event::InvalidPDU, data);
    }
}

void
StateMachine
::receive_pdu(EventData & data)
{
    if(data.transport == nullptr)
    {
        throw Exception("No transport");
    }

    auto const header = data.transport->read(6);

    uint8_t const type = header[0];
    uint32_t const length = be32toh(
        *reinterpret_cast<uint32_t const *>(&header[0]+2));
    auto const pdu_data = data.transport->read(length);

    std::stringstream stream;
    stream.write(&header[0], header.size());
    stream.write(&pdu_data[0], pdu_data.size());

    data.pdu=nullptr;
    Event event = Event::None;
    if(type == 0x01)
    {
        data.pdu = std::make_shared<pdu::AAssociate>(stream);
        event = Event::AAssociateRQRemote;
    }
    else if(type == 0x02)
    {
        data.pdu = std::make_shared<pdu::AAssociate>(stream);
        event = Event::AAssociateACRemote;
    }
    else if(type == 0x03)
    {
        data.pdu = std::make_shared<pdu::AAssociateRJ>(stream);
        event = Event::AAssociateRJRemote;
    }
    else if(type == 0x04)
    {
        data.pdu = std::make_shared<pdu::PDataTF>(stream);
        event = Event::PDataTFRemote;
    }
    else if(type == 0x05)
    {
        data.pdu = std::make_shared<pdu::AReleaseRQ>(stream);
        event = Event::AReleaseRQRemote;
    }
    else if(type == 0x06)
    {
        data.pdu = std::make_shared<pdu::AReleaseRP>(stream);
        event = Event::AReleaseRPRemote;
    }
    else if(type == 0x07)
    {
        data.pdu = std::make_shared<pdu::AAbort>(stream);
        event = Event::AAbortRemote;
    }
    else
    {
        event = Event::InvalidPDU;
    }

    this->transition(event, data);

}

#define transition_full(start, event, action, end, guard) { \
        { StateMachine::State::start, StateMachine::Event::event }, \
        { StateMachine::Action::action, StateMachine::State::end } }

#define transition(start, event, action, end) { \
        { StateMachine::State::start, StateMachine::Event::event }, \
        { StateMachine::Action::action, StateMachine::State::end } }

StateMachine::TransitionMap const
StateMachine
::_transitions = {
    transition(Sta1, AAssociateRQLocal, AE_1, Sta4),
    transition(Sta1, TransportConnectionIndication, AE_5, Sta2),

    transition(Sta2, AAssociateACRemote, AA_1, Sta13),
    transition(Sta2, AAssociateRJRemote, AA_1, Sta13),
    transition_full(Sta2, AAssociateRQRemote, AE_6, Sta3, is_association_request_acceptable),
    transition_full(Sta2, AAssociateRQRemote, AE_6, Sta13, !is_association_request_acceptable),
    transition(Sta2, PDataTFRemote, AA_1, Sta13),
    transition(Sta2, AReleaseRQRemote, AA_1, Sta13),
    transition(Sta2, AReleaseRPRemote, AA_1, Sta13),
    transition(Sta2, AAbortRemote, AA_2, Sta1),
    transition(Sta2, TransportConnectionClosedIndication, AA_5, Sta1),
    transition(Sta2, ARTIMTimerExpired, AA_2, Sta1),
    transition(Sta2, InvalidPDU, AA_1, Sta13),

    transition(Sta3, AAssociateACRemote, AA_8, Sta13),
    transition(Sta3, AAssociateRJRemote, AA_8, Sta13),
    transition(Sta3, AAssociateRQRemote, AA_8, Sta13),
    transition(Sta3, AAssociateACLocal, AE_7, Sta6),
    transition(Sta3, AAssociateRJLocal, AE_8, Sta13),
    transition(Sta3, PDataTFRemote, AA_8, Sta13),
    transition(Sta3, AReleaseRQRemote, AA_8, Sta13),
    transition(Sta3, AReleaseRPRemote, AA_8, Sta13),
    transition(Sta3, AAbortLocal, AA_1, Sta13),
    transition(Sta3, AAbortRemote, AA_3, Sta1),
    transition(Sta3, TransportConnectionClosedIndication, AA_4, Sta1),
    transition(Sta3, InvalidPDU, AA_8, Sta13),

    transition(Sta4, TransportConnectionConfirmation, AE_2, Sta5),
    transition(Sta4, AAbortLocal, AA_2, Sta1),
    transition(Sta4, TransportConnectionClosedIndication, AA_4, Sta1),

    transition(Sta5, AAssociateACRemote, AE_3, Sta6),
    transition(Sta5, AAssociateRJRemote, AE_4, Sta1),
    transition(Sta5, AAssociateRQRemote, AA_8, Sta13),
    transition(Sta5, PDataTFRemote, AA_8, Sta13),
    transition(Sta5, AReleaseRQRemote, AA_8, Sta13),
    transition(Sta5, AReleaseRPRemote, AA_8, Sta13),
    transition(Sta5, AAbortLocal, AA_1, Sta13),
    transition(Sta5, AAbortRemote, AA_3, Sta1),
    transition(Sta5, TransportConnectionClosedIndication, AA_4, Sta1),
    transition(Sta5, InvalidPDU, AA_8, Sta13),

    transition(Sta6, AAssociateACRemote, AA_8, Sta13),
    transition(Sta6, AAssociateRJRemote, AA_8, Sta13),
    transition(Sta6, AAssociateRQRemote, AA_8, Sta13),
    transition(Sta6, PDataTFLocal, DT_1, Sta6),
    transition(Sta6, PDataTFRemote, DT_2, Sta6),
    transition(Sta6, AReleaseRQLocal, AR_1, Sta7),
    transition(Sta6, AReleaseRQRemote, AR_2, Sta8),
    transition(Sta6, AReleaseRPRemote, AA_8, Sta13),
    transition(Sta6, AAbortLocal, AA_1, Sta13),
    transition(Sta6, AAbortRemote, AA_3, Sta1),
    transition(Sta6, TransportConnectionClosedIndication, AA_4, Sta1),
    transition(Sta6, InvalidPDU, AA_8, Sta13),

    transition(Sta7, AAssociateACRemote, AA_8, Sta13),
    transition(Sta7, AAssociateRJRemote, AA_8, Sta13),
    transition(Sta7, AAssociateRQRemote, AA_8, Sta13),
    transition(Sta7, PDataTFRemote, AR_6, Sta7),
    //transition(Sta7, AReleaseRQRemote, AR_8, Sta9Or10),
    transition(Sta7, AReleaseRPRemote, AR_3, Sta1),
    transition(Sta7, AAbortLocal, AA_1, Sta13),
    transition(Sta7, AAbortRemote, AA_3, Sta1),
    transition(Sta7, TransportConnectionClosedIndication, AA_4, Sta1),
    transition(Sta7, InvalidPDU, AA_8, Sta13),

    transition(Sta8, AAssociateACRemote, AA_8, Sta13),
    transition(Sta8, AAssociateRJRemote, AA_8, Sta13),
    transition(Sta8, AAssociateRQRemote, AA_8, Sta13),
    transition(Sta8, PDataTFLocal, AR_7, Sta8),
    transition(Sta8, PDataTFRemote, AA_8, Sta13),
    transition(Sta8, AReleaseRQRemote, AA_8, Sta13),
    transition(Sta8, AReleaseRPRemote, AA_8, Sta13),
    transition(Sta8, AReleaseRPLocal, AR_4, Sta13),
    transition(Sta8, AAbortLocal, AA_1, Sta13),
    transition(Sta8, AAbortRemote, AA_3, Sta1),
    transition(Sta8, TransportConnectionClosedIndication, AA_4, Sta1),
    transition(Sta8, InvalidPDU, AA_8, Sta13),

    transition(Sta9, AAssociateACRemote, AA_8, Sta13),
    transition(Sta9, AAssociateRJRemote, AA_8, Sta13),
    transition(Sta9, AAssociateRQRemote, AA_8, Sta13),
    transition(Sta9, PDataTFRemote, AA_8, Sta13),
    transition(Sta9, AReleaseRQRemote, AA_8, Sta13),
    transition(Sta9, AReleaseRPRemote, AA_8, Sta13),
    transition(Sta9, AReleaseRPLocal, AR_9, Sta11),
    transition(Sta9, AAbortLocal, AA_1, Sta13),
    transition(Sta9, AAbortRemote, AA_3, Sta1),
    transition(Sta9, TransportConnectionClosedIndication, AA_4, Sta1),
    transition(Sta9, InvalidPDU, AA_8, Sta13),

    transition(Sta10, AAssociateACRemote, AA_8, Sta13),
    transition(Sta10, AAssociateRJRemote, AA_8, Sta13),
    transition(Sta10, AAssociateRQRemote, AA_8, Sta13),
    transition(Sta10, PDataTFRemote, AA_8, Sta13),
    transition(Sta10, AReleaseRQRemote, AA_8, Sta13),
    transition(Sta10, AReleaseRPRemote, AR_10, Sta12),
    transition(Sta10, AAbortLocal, AA_1, Sta13),
    transition(Sta10, AAbortRemote, AA_3, Sta1),
    transition(Sta10, TransportConnectionClosedIndication, AA_4, Sta1),
    transition(Sta10, InvalidPDU, AA_8, Sta13),

    transition(Sta11, AAssociateACRemote, AA_8, Sta13),
    transition(Sta11, AAssociateRJRemote, AA_8, Sta13),
    transition(Sta11, AAssociateRQRemote, AA_8, Sta13),
    transition(Sta11, PDataTFRemote, AA_8, Sta13),
    transition(Sta11, AReleaseRQRemote, AA_8, Sta13),
    transition(Sta11, AReleaseRPRemote, AR_3, Sta1),
    transition(Sta11, AAbortLocal, AA_1, Sta13),
    transition(Sta11, AAbortRemote, AA_3, Sta1),
    transition(Sta11, TransportConnectionClosedIndication, AA_4, Sta1),
    transition(Sta11, InvalidPDU, AA_8, Sta13),

    transition(Sta12, AAssociateACRemote, AA_8, Sta13),
    transition(Sta12, AAssociateRJRemote, AA_8, Sta13),
    transition(Sta12, AAssociateRQRemote, AA_8, Sta13),
    transition(Sta12, PDataTFRemote, AA_8, Sta13),
    transition(Sta12, AReleaseRQRemote, AA_8, Sta13),
    transition(Sta12, AReleaseRPRemote, AA_8, Sta13),
    transition(Sta12, AReleaseRPLocal, AR_4, Sta13),
    transition(Sta12, AAbortLocal, AA_1, Sta13),
    transition(Sta12, AAbortRemote, AA_3, Sta1),
    transition(Sta12, TransportConnectionClosedIndication, AA_4, Sta1),
    transition(Sta12, InvalidPDU, AA_8, Sta13),

    transition(Sta13, AAssociateACRemote, AA_6, Sta13),
    transition(Sta13, AAssociateRJRemote, AA_6, Sta13),
    transition(Sta13, AAssociateRQRemote, AA_7, Sta13),
    transition(Sta13, PDataTFRemote, AA_6, Sta13),
    transition(Sta13, AReleaseRQRemote, AA_6, Sta13),
    transition(Sta13, AReleaseRPRemote, AA_6, Sta13),
    transition(Sta13, AAbortRemote, AA_2, Sta1),
    transition(Sta13, TransportConnectionClosedIndication, AR_5, Sta1),
    transition(Sta13, ARTIMTimerExpired, AA_2, Sta1),
    transition(Sta13, InvalidPDU, AA_7, Sta13),
};

#undef transition

void
StateMachine
::_send_pdu(EventData & data, uint8_t pdu_type)
{
    if(data.transport == nullptr)
    {
        throw Exception("No transport");
    }
    if(data.pdu == nullptr)
    {
        throw Exception("No PDU");
    }
    auto const & item = data.pdu->get_item();

    if(item.as_unsigned_int_8("PDU-type") != pdu_type)
    {
        throw Exception("Invalid PDU");
    }

    std::ostringstream stream;
    stream << item;
    data.transport->write(stream.str());
}

void
StateMachine
::AE_1(EventData & data)
{
    data.transport->connect(data.peer_endpoint);
}

void
StateMachine
::AE_2(EventData & data)
{
    this->_send_pdu(data, 0x01);
}

void
StateMachine
::AE_3(EventData & data)
{
    // Do nothing ?

    //this->_notify("A-ASSOCIATE", "confirmation (accept)");
    //data.pdu = pdu::AAssociateAC(data.stream);
}

void
StateMachine
::AE_4(EventData & data)
{
    /*
    data.pdu = pdu::AAssociateRJ(data.stream);
    data.stream->close();
    */
}

void
StateMachine
::AE_5(EventData & data)
{
}

void
StateMachine
::AE_6(EventData & data)
{
}

void
StateMachine
::AE_7(EventData & data)
{
}

void
StateMachine
::AE_8(EventData & data)
{
}

void
StateMachine
::DT_1(EventData & data)
{
    this->_send_pdu(data, 0x04);
}

void
StateMachine
::DT_2(EventData & transport)
{
    /*
    // FIXME, replace the test with:
    // PDataPDU pdata(pdu);
    if(data.pdu->get_item().as_unsigned_int_8("PDU-type") != 0x04)
    {
        throw Exception("Invalid PDU type");
    }
    this->_notify("P-DATA", "indication", *data.pdu);
    */
}

/*
void
StateMachine
::_notify(std::string const & protocol, std::string const & type) const
{
    auto const iterator = this->_observers.find(std::make_pair(protocol, type));
    if(iterator != this->_observers.end())
    {
        for(auto const & observer: iterator->second)
        {
            observer.second();
        }
    }
}
*/

}

}
