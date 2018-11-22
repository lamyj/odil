#define BOOST_TEST_MODULE MessageReceiver
#include <boost/test/unit_test.hpp>

#include <random>
#include <thread>

#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/dimse.h>

#include "odil/AssociationParameters.h"
#include "odil/dul/AAssociateAC.h"
#include "odil/dul/PDU.h"
#include "odil/dul/Connection.h"
#include "odil/message/CEchoRequest.h"
#include "odil/message/CFindRequest.h"
#include "odil/message/Message.h"
#include "odil/MessageReceiver.h"
#include "odil/registry.h"

using Port = unsigned short;

class Fixture
{
public:
    using Service = boost::asio::io_service;
    using Socket = boost::asio::ip::tcp::socket;
    using Endpoint = boost::asio::ip::tcp::endpoint;
    using Acceptor = boost::asio::ip::tcp::acceptor;

    static std::random_device random_device;
    static std::mt19937 random_generator;
    static std::uniform_int_distribution<Port> random_distribution;

    Service service;
    Socket socket;
    Endpoint endpoint;
    std::shared_ptr<Fixture::Acceptor> socket_acceptor;

    odil::dul::Connection connection;
    std::map<uint8_t, std::string> transfer_syntaxes_by_id;

    std::shared_ptr<odil::message::Message> message;
    odil::dul::PDU::Pointer error_pdu;
    boost::system::error_code error_code;
    

    Fixture();
    
    void dcmtk_requestor(
        Port port, char const * abstract_syntax, 
        T_DIMSE_Message * message, DcmDataset * data_set);

    odil::dul::PDU::Pointer request_acceptor(odil::dul::AAssociateRQ::Pointer request);

    void on_success(std::shared_ptr<odil::message::Message> message);
    void on_error(
        odil::dul::PDU::Pointer error_pdu, boost::system::error_code error_code);
};

BOOST_FIXTURE_TEST_CASE(CommandOnly, Fixture)
{
    odil::MessageReceiver receiver(
        connection, transfer_syntaxes_by_id, 
        boost::bind(&Fixture::on_success, this, _1),
        boost::bind(&Fixture::on_error, this, _1, _2));
    receiver();
    
    // WARNING: make sure the acceptor is running before starting the
    // requestor thread.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    T_DIMSE_Message dcmtk_message;
    dcmtk_message.CommandField = DIMSE_C_ECHO_RQ;
    dcmtk_message.msg.CEchoRQ = {1, UID_VerificationSOPClass, DIMSE_DATASET_NULL};
    std::thread requestor(
        [&](){ 
            this->dcmtk_requestor(
                this->endpoint.port(), 
                UID_VerificationSOPClass, 
                &dcmtk_message, nullptr); });

    this->service.run();
    requestor.join();    

    BOOST_REQUIRE(this->message);
    odil::message::CEchoRequest request(this->message);
    BOOST_REQUIRE_EQUAL(
        request.get_message_id(), dcmtk_message.msg.CEchoRQ.MessageID);
    BOOST_REQUIRE_EQUAL(
        request.get_affected_sop_class_uid(), 
        dcmtk_message.msg.CEchoRQ.AffectedSOPClassUID);
    BOOST_REQUIRE(!request.has_data_set());
}

BOOST_FIXTURE_TEST_CASE(CommandAndDataSet, Fixture)
{
    odil::MessageReceiver receiver(
        connection, transfer_syntaxes_by_id, 
        boost::bind(&Fixture::on_success, this, _1),
        boost::bind(&Fixture::on_error, this, _1, _2));
    receiver();
    
    // WARNING: make sure the acceptor is running before starting the
    // requestor thread.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    T_DIMSE_Message dcmtk_message;
    dcmtk_message.CommandField = DIMSE_C_FIND_RQ;
    dcmtk_message.msg.CFindRQ = {
        1, UID_FINDPatientRootQueryRetrieveInformationModel, 
        DIMSE_PRIORITY_MEDIUM, DIMSE_DATASET_PRESENT};
    DcmDataset data_set;
    data_set.putAndInsertString(DCM_QueryRetrieveLevel, "PATIENT");
    data_set.putAndInsertString(DCM_PatientID, "DJ*");
    
    std::thread requestor(
        [&](){ 
            this->dcmtk_requestor(
                this->endpoint.port(), 
                UID_FINDPatientRootQueryRetrieveInformationModel, 
                &dcmtk_message, &data_set); });
    
    this->service.run();
    requestor.join();    

    BOOST_REQUIRE(this->message);
    odil::message::CFindRequest request(this->message);
    BOOST_REQUIRE_EQUAL(
        request.get_message_id(), dcmtk_message.msg.CFindRQ.MessageID);
    BOOST_REQUIRE_EQUAL(
        request.get_priority(), dcmtk_message.msg.CFindRQ.Priority);
    BOOST_REQUIRE_EQUAL(
        request.get_affected_sop_class_uid(), 
        dcmtk_message.msg.CFindRQ.AffectedSOPClassUID);
    BOOST_REQUIRE(request.has_data_set());
    BOOST_REQUIRE(
        request.get_data_set()->as_string("QueryRetrieveLevel") 
            == odil::Value::Strings{"PATIENT"});
    BOOST_REQUIRE(
        request.get_data_set()->as_string("PatientID") 
            == odil::Value::Strings{"DJ*"});

    BOOST_REQUIRE(!this->error_pdu);
    BOOST_REQUIRE(!this->error_code);
}

BOOST_FIXTURE_TEST_CASE(MultiPDU, Fixture)
{
    odil::MessageReceiver receiver(
        connection, transfer_syntaxes_by_id, 
        boost::bind(&Fixture::on_success, this, _1),
        boost::bind(&Fixture::on_error, this, _1, _2));
    receiver();
    
    // WARNING: make sure the acceptor is running before starting the
    // requestor thread.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    T_DIMSE_Message dcmtk_message;
    dcmtk_message.CommandField = DIMSE_C_FIND_RQ;
    dcmtk_message.msg.CFindRQ = {
        1, UID_FINDPatientRootQueryRetrieveInformationModel, 
        DIMSE_PRIORITY_MEDIUM, DIMSE_DATASET_PRESENT};
    DcmDataset data_set;
    data_set.putAndInsertString(DCM_QueryRetrieveLevel, "PATIENT");
    // Since we already have QueryRetrieveLevel, this is sufficient to have
    // the data set split in several PDUs
    std::vector<uint8_t> data(ASC_DEFAULTMAXPDU);
    for(int i=0; i<data.size(); ++i)
    {
        data[i] = i;
    }
    data_set.putAndInsertUint8Array(DCM_PixelData, &data[0], data.size());
    
    std::thread requestor(
        [&](){ 
            this->dcmtk_requestor(
                this->endpoint.port(), 
                UID_FINDPatientRootQueryRetrieveInformationModel, 
                &dcmtk_message, &data_set); });
    
    this->service.run();
    requestor.join();    

    BOOST_REQUIRE(this->message);
    odil::message::CFindRequest request(this->message);
    BOOST_REQUIRE_EQUAL(
        request.get_message_id(), dcmtk_message.msg.CFindRQ.MessageID);
    BOOST_REQUIRE_EQUAL(
        request.get_priority(), dcmtk_message.msg.CFindRQ.Priority);
    BOOST_REQUIRE_EQUAL(
        request.get_affected_sop_class_uid(), 
        dcmtk_message.msg.CFindRQ.AffectedSOPClassUID);
    BOOST_REQUIRE(request.has_data_set());
    BOOST_REQUIRE(
        request.get_data_set()->as_string("QueryRetrieveLevel") 
            == odil::Value::Strings{"PATIENT"});
    BOOST_REQUIRE(
        request.get_data_set()->as_binary("PixelData") 
            == odil::Value::Binary{data} );

    BOOST_REQUIRE(!this->error_pdu);
    BOOST_REQUIRE(!this->error_code);
}

std::random_device Fixture::random_device{};
std::mt19937 Fixture::random_generator{Fixture::random_device()};
std::uniform_int_distribution<Port> Fixture::random_distribution{49152, 65535};

Fixture
::Fixture()
: service(), socket(service), endpoint(), socket_acceptor(nullptr),
    connection(this->socket), transfer_syntaxes_by_id(),
    message(nullptr), error_pdu(nullptr), error_code()
{
    this->connection.acceptor = boost::bind(&Fixture::request_acceptor, this, _1);

    auto const port = 11112; //Fixture::random_distribution(Fixture::random_generator);
    
    this->endpoint = Fixture::Endpoint(boost::asio::ip::tcp::v4(), port);
    this->socket_acceptor = std::make_shared<Fixture::Acceptor>(this->service, endpoint);
    this->socket_acceptor->async_accept(
        this->socket,
        [&](boost::system::error_code error) {
            connection.transport_connection.indication(error);
        }
    );
}

void
Fixture
::dcmtk_requestor(
    Port port, char const * abstract_syntax, 
    T_DIMSE_Message * message, DcmDataset * data_set)
{
    T_ASC_Network * network;
    ASC_initializeNetwork(NET_REQUESTOR, 0, 5, &network);

    T_ASC_Parameters * parameters;
    ASC_createAssociationParameters(&parameters, ASC_DEFAULTMAXPDU);
    ASC_setAPTitles(parameters, "calling", "called", nullptr);

    auto const peer_address = "localhost:"+std::to_string(port);
    ASC_setPresentationAddresses(parameters, "localhost", peer_address.c_str());

    char const * ts[] = { UID_LittleEndianExplicitTransferSyntax };
    ASC_addPresentationContext(parameters, 1, abstract_syntax, ts, 1);

    OFCondition condition;

    T_ASC_Association *association;
    condition = ASC_requestAssociation(network, parameters, &association);
    DIMSE_sendMessageUsingMemoryData(
        association, 1, message, nullptr, data_set, nullptr, nullptr);
    ASC_releaseAssociation(association);
    ASC_destroyAssociation(&association);
    
    ASC_dropNetwork(&network);
}

odil::dul::PDU::Pointer
Fixture
::request_acceptor(odil::dul::AAssociateRQ::Pointer request)
{
    odil::AssociationParameters input(*request);
    odil::AssociationParameters output;

    output.set_called_ae_title(input.get_called_ae_title());
    output.set_calling_ae_title(input.get_calling_ae_title());

    auto presentation_contexts = input.get_presentation_contexts();
    for(auto & presentation_context: presentation_contexts)
    {
        presentation_context.transfer_syntaxes =
            { presentation_context.transfer_syntaxes[0] };
        presentation_context.result =
            odil::AssociationParameters::PresentationContext::Result::Acceptance;
    }
    output.set_presentation_contexts(presentation_contexts);

    for(auto && pc: presentation_contexts)
    {
        this->transfer_syntaxes_by_id[pc.id] = pc.transfer_syntaxes[0];
    }

    output.set_maximum_length(input.get_maximum_length());
    return std::make_shared<odil::dul::AAssociateAC>(
        output.as_a_associate_ac());
}

void
Fixture
::on_success(std::shared_ptr<odil::message::Message> message)
{
    this->message = message;
}
    
void
Fixture
::on_error(
    odil::dul::PDU::Pointer error_pdu, boost::system::error_code error_code)
{
    this->error_pdu = error_pdu;
    this->error_code = error_code;
}
