#define BOOST_TEST_MODULE MessageReceiver
#include <boost/test/unit_test.hpp>

#include <thread>

#include <dcmtk/dcmdata/dctk.h>

#include "odil/AssociationParameters.h"
#include "odil/dul/AAssociateAC.h"
#include "odil/dul/PDU.h"
#include "odil/dul/Connection.h"
#include "odil/message/CEchoRequest.h"
#include "odil/message/CFindRequest.h"
#include "odil/message/Message.h"
#include "odil/MessageReceiver.h"
#include "odil/registry.h"

#include "../ConnectionFixtureBase.h"

class Fixture: public ConnectionFixtureBase
{
public:
    odil::dul::Connection connection;
    std::map<uint8_t, std::string> transfer_syntaxes_by_id;

    std::shared_ptr<odil::message::Message> message;
    odil::dul::PDU::Pointer error_pdu;
    boost::system::error_code error_code;
    
    Fixture();
    
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
    dcmtk_message.msg.CEchoRQ = T_DIMSE_C_EchoRQ{
        1, UID_VerificationSOPClass, DIMSE_DATASET_NULL};
    std::thread requestor(
        [&](){ 
            this->dcmtk_requestor(
                UID_VerificationSOPClass, 
                UID_LittleEndianImplicitTransferSyntax,
                false, &dcmtk_message, nullptr); });

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
    dcmtk_message.msg.CFindRQ = T_DIMSE_C_FindRQ{
        1, UID_FINDPatientRootQueryRetrieveInformationModel, 
        DIMSE_PRIORITY_MEDIUM, DIMSE_DATASET_PRESENT};
    DcmDataset data_set;
    data_set.putAndInsertString(DCM_QueryRetrieveLevel, "PATIENT");
    data_set.putAndInsertString(DCM_PatientID, "DJ*");
    
    std::thread requestor(
        [&](){ 
            this->dcmtk_requestor(
                UID_FINDPatientRootQueryRetrieveInformationModel, 
                UID_LittleEndianImplicitTransferSyntax,
                false, &dcmtk_message, &data_set); });
    
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
    dcmtk_message.msg.CFindRQ = T_DIMSE_C_FindRQ{
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
                UID_FINDPatientRootQueryRetrieveInformationModel, 
                UID_LittleEndianImplicitTransferSyntax,
                false, &dcmtk_message, &data_set); });
    
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

Fixture
::Fixture()
: ConnectionFixtureBase(), 
    connection(this->socket), transfer_syntaxes_by_id(),
    message(nullptr), error_pdu(nullptr), error_code()
{
    this->setup_odil_receiver();
    this->connection.acceptor = boost::bind(&Fixture::request_acceptor, this, _1);

    this->acceptor.async_accept(
        this->socket,
        [&](boost::system::error_code error) {
            connection.transport_connection.indication(error);
        }
    );
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
