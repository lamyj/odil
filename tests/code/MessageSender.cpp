#define BOOST_TEST_MODULE MessageSender
#include <boost/test/unit_test.hpp>

#include <random>
#include <thread>

#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/dimse.h>

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

using Port = unsigned short;

class Fixture
{
public:
    using Service = boost::asio::io_service;
    using Socket = boost::asio::ip::tcp::socket;
    using Endpoint = boost::asio::ip::tcp::endpoint;

    static std::random_device random_device;
    static std::mt19937 random_generator;
    static std::uniform_int_distribution<Port> random_distribution;

    Service service;
    Socket socket;
    Endpoint endpoint;

    odil::AssociationParameters parameters;
    bool odil_success;
    odil::dul::PDU::Pointer error_pdu;
    boost::system::error_code error_code;

    std::vector<T_DIMSE_Message> dcmtk_messages;
    std::vector<T_ASC_PresentationContextID> dcmtk_context_ids;
    std::vector<DcmDataset*> dcmtk_data_sets;

    Fixture();
    
    void dcmtk_acceptor(Port port, bool receive_data_set);

    void success_handler();
    void error_handler(
        odil::dul::PDU::Pointer pdu, boost::system::error_code code);
};

BOOST_FIXTURE_TEST_CASE(CommandOnly, Fixture)
{
    auto const port = Fixture::random_distribution(Fixture::random_generator);

    this->endpoint = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address_v4::from_string("127.0.0.1"), port);

    std::thread acceptor([&](){ this->dcmtk_acceptor(port, false); });

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
    auto const port = Fixture::random_distribution(Fixture::random_generator);

    this->endpoint = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address_v4::from_string("127.0.0.1"), port);

    std::thread acceptor([&](){ this->dcmtk_acceptor(port, true); });

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

std::random_device Fixture::random_device{};
std::mt19937 Fixture::random_generator{Fixture::random_device()};
std::uniform_int_distribution<Port> Fixture::random_distribution{49152, 65535};

Fixture
::Fixture()
: service(), socket(service), endpoint(), parameters(), odil_success(false),
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
::dcmtk_acceptor(Port port, bool receive_data_set)
{
    OFCondition condition;

    T_ASC_Network * network;
    condition = ASC_initializeNetwork(NET_ACCEPTOR, port, 5, &network);
    if(!condition.good())
    {
        throw std::runtime_error("Could not initialize network");
    }

    T_ASC_Association *association;
    condition = ASC_receiveAssociation(network, &association, ASC_DEFAULTMAXPDU);
    if(!condition.good())
    {
        throw std::runtime_error(
            std::string("Could not receive association: ")+condition.text());
    }

    ASC_acceptPresentationContext(
        association->params, 1, UID_LittleEndianImplicitTransferSyntax);
    ASC_acknowledgeAssociation(association);

    T_ASC_PresentationContextID context_id;
    T_DIMSE_Message message;
    
    while(condition != DUL_PEERREQUESTEDRELEASE)
    {
        condition = DIMSE_receiveCommand(
            association, DIMSE_BLOCKING, 0, &context_id, &message, nullptr);
        if(condition.good())
        {
            this->dcmtk_messages.push_back(message);
            this->dcmtk_context_ids.push_back(context_id);

            DcmDataset * data_set=nullptr;
            if(receive_data_set)
            {
                condition = DIMSE_receiveDataSetInMemory(
                    association, DIMSE_BLOCKING, 0, &context_id, &data_set, 
                    nullptr, nullptr);
                this->dcmtk_data_sets.push_back(data_set);
            }
        }
    }
    
    ASC_acknowledgeRelease(association);
    ASC_dropNetwork(&network);
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
