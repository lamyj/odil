#define BOOST_TEST_MODULE MessageSender
#include <boost/test/unit_test.hpp>

#include <thread>

#include "odil/AssociationParameters.h"
#include "odil/dul/AAssociateAC.h"
#include "odil/dul/PDU.h"
#include "odil/dul/Connection.h"
#include "odil/logging.h"
#include "odil/message/CEchoRequest.h"
#include "odil/message/CFindRequest.h"
#include "odil/message/Message.h"
#include "odil/MessageSender.h"
#include "odil/registry.h"

#include "../ConnectionFixtureBase.h"

struct Fixture: public ConnectionFixtureBase
{
public:
    odil::AssociationParameters parameters;
    bool odil_success;
    odil::dul::PDU::Pointer error_pdu;
    boost::system::error_code error_code;

    Fixture();
    
    void success_handler();
    void error_handler(
        odil::dul::PDU::Pointer pdu, boost::system::error_code code);
};

BOOST_FIXTURE_TEST_CASE(CommandOnly, Fixture)
{
    this->setup_odil_requestor();

    std::thread acceptor([&](){ this->dcmtk_acceptor("accept"); });

    odil::dul::Connection connection(this->socket);
    
    odil::MessageSender message_sender(
        connection, [&]() { this->success_handler(); },
        [&](odil::dul::PDU::Pointer p, boost::system::error_code e) { 
            this->error_handler(p, e); });

    connection.a_associate.confirmation.connect([&](odil::dul::PDU::Pointer pdu) {
        odil::AssociationParameters const negotiated_parameters(
            *std::dynamic_pointer_cast<odil::dul::AAssociateAC>(pdu), 
            this->parameters);

        message_sender(
            std::make_shared<odil::message::CEchoRequest>(
                1, odil::registry::VerificationSOPClass),
            negotiated_parameters.get_presentation_contexts()[0].transfer_syntaxes[0],
            negotiated_parameters.get_presentation_contexts()[0].id,
            negotiated_parameters.get_maximum_length());
        
        connection.send(std::make_shared<odil::dul::AReleaseRQ>());
    });

    connection.send(
        this->endpoint,
        std::make_shared<odil::dul::AAssociateRQ>(
            this->parameters.as_a_associate_rq()));

    this->service.run();
    acceptor.join();

    BOOST_REQUIRE(this->odil_success);
    BOOST_REQUIRE_EQUAL(this->error_pdu, nullptr);
    BOOST_REQUIRE_EQUAL(this->error_code, boost::system::error_code());

    BOOST_REQUIRE_EQUAL(this->dcmtk_messages.size(), 1);
    BOOST_REQUIRE_EQUAL(this->dcmtk_messages[0].CommandField, DIMSE_C_ECHO_RQ);
    BOOST_REQUIRE_EQUAL(this->dcmtk_messages[0].msg.CEchoRQ.MessageID, 1);
    BOOST_REQUIRE_EQUAL(
        this->dcmtk_messages[0].msg.CEchoRQ.AffectedSOPClassUID, 
        odil::registry::VerificationSOPClass);
    BOOST_REQUIRE_EQUAL(
        this->dcmtk_messages[0].msg.CEchoRQ.DataSetType, DIMSE_DATASET_NULL);

    BOOST_REQUIRE_EQUAL(this->dcmtk_context_ids.size(), 1);
    BOOST_REQUIRE_EQUAL(
        this->dcmtk_context_ids[0], 
        this->parameters.get_presentation_contexts()[0].id);
    
    BOOST_REQUIRE(this->dcmtk_data_sets.empty());
}

BOOST_FIXTURE_TEST_CASE(CommandAndDataSet, Fixture)
{
    this->setup_odil_requestor();
    
    std::thread acceptor([&](){ this->dcmtk_acceptor("accept"); });

    odil::dul::Connection connection(this->socket);
    
    odil::MessageSender message_sender(
        connection, [&]() { this->success_handler(); },
        [&](odil::dul::PDU::Pointer p, boost::system::error_code e) { 
            this->error_handler(p, e); });

    connection.a_associate.confirmation.connect([&](odil::dul::PDU::Pointer pdu) {
        odil::AssociationParameters const negotiated_parameters(
            *std::dynamic_pointer_cast<odil::dul::AAssociateAC>(pdu), 
            this->parameters);

        auto query = std::make_shared<odil::DataSet>();
        query->add(odil::registry::QueryRetrieveLevel, {"PATIENT"});
        query->add(odil::registry::PatientName, {"Doe^John"});
        
        message_sender(
            std::make_shared<odil::message::CFindRequest>(
                1, odil::registry::PatientRootQueryRetrieveInformationModelFIND, 1,
                query),
            negotiated_parameters.get_presentation_contexts()[0].transfer_syntaxes[0],
            negotiated_parameters.get_presentation_contexts()[0].id,
            negotiated_parameters.get_maximum_length());
        
        connection.send(std::make_shared<odil::dul::AReleaseRQ>());
    });
    connection.transport_error.indication.connect(
        [&](boost::system::error_code e) { this->error_handler(nullptr, e); });
    connection.transport_closed.indication.connect(
        [&]() { this->error_handler(nullptr, boost::system::errc::make_error_code(boost::system::errc::connection_reset)); });

    connection.send(
        this->endpoint,
        std::make_shared<odil::dul::AAssociateRQ>(
            this->parameters.as_a_associate_rq()));

    this->service.run();
    acceptor.join();

    BOOST_REQUIRE(this->odil_success);
    BOOST_REQUIRE_EQUAL(this->error_pdu, nullptr);
    BOOST_REQUIRE_EQUAL(this->error_code, boost::system::error_code());

    BOOST_REQUIRE_EQUAL(this->dcmtk_messages.size(), 1);
    BOOST_REQUIRE_EQUAL(this->dcmtk_messages[0].CommandField, DIMSE_C_FIND_RQ);
    BOOST_REQUIRE_EQUAL(this->dcmtk_messages[0].msg.CEchoRQ.MessageID, 1);
    BOOST_REQUIRE_EQUAL(
        this->dcmtk_messages[0].msg.CFindRQ.AffectedSOPClassUID, 
        odil::registry::PatientRootQueryRetrieveInformationModelFIND);
    BOOST_REQUIRE_EQUAL(
        this->dcmtk_messages[0].msg.CFindRQ.DataSetType, DIMSE_DATASET_PRESENT);

    BOOST_REQUIRE_EQUAL(this->dcmtk_context_ids.size(), 1);
    BOOST_REQUIRE_EQUAL(
        this->dcmtk_context_ids[0], 
        this->parameters.get_presentation_contexts()[0].id);
    
    BOOST_REQUIRE_EQUAL(this->dcmtk_data_sets.size(), 1);
    BOOST_REQUIRE_NE(this->dcmtk_data_sets[0], nullptr);
}

Fixture
::Fixture()
: ConnectionFixtureBase(), parameters(), odil_success(false),
    error_pdu(nullptr), error_code()
{
    this->parameters
        .set_calling_ae_title("calling").set_called_ae_title("called")
        .set_presentation_contexts({
            {
                1, odil::registry::RawDataStorage,
                { odil::registry::ImplicitVRLittleEndian }, true, false } });
}

void
Fixture
::success_handler()
{
    this->odil_success = true;
}

void
Fixture
::error_handler(odil::dul::PDU::Pointer pdu, boost::system::error_code code)
{
    this->error_pdu = pdu;
    this->error_code = code;
}
