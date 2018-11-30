#define BOOST_TEST_MODULE AssociationReceiver
#include <boost/test/unit_test.hpp>

#include <thread>

#include "odil/AssociationParameters.h"
#include "odil/AssociationReceiver.h"
#include "odil/dul/AAbort.h"
#include "odil/dul/Connection.h"
#include "odil/dul/PDU.h"
#include "odil/registry.h"

#include "../ConnectionFixtureBase.h"

struct Fixture: public ConnectionFixtureBase
{
    odil::dul::Connection connection;
    std::map<uint8_t, std::string> transfer_syntaxes_by_id;

    odil::dul::PDU::Pointer success_pdu;
    odil::dul::PDU::Pointer error_pdu;
    boost::system::error_code error_code;

    Fixture();

    odil::dul::PDU::Pointer request_acceptor(odil::dul::AAssociateRQ::Pointer request);
};

BOOST_FIXTURE_TEST_CASE(Success, Fixture)
{
    // WARNING: do not open this->acceptor
    this->endpoint = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::tcp::v4(), this->port);

    odil::AssociationReceiver receiver(
        this->service, this->connection,
        [&](odil::dul::PDU::Pointer p){ this->success_pdu = p; },
        [&](odil::dul::PDU::Pointer p, boost::system::error_code e) { 
            this->error_pdu = p;
            this->error_code = e; });

    receiver(this->endpoint);

    // WARNING: make sure the receiver is running before starting the
    // requestor thread.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::thread requestor(
        [&](){ 
            this->dcmtk_requestor(
                UID_VerificationSOPClass, 
                UID_LittleEndianImplicitTransferSyntax,
                true, nullptr, nullptr); });

    this->service.run();
    requestor.join();

    BOOST_REQUIRE_EQUAL(this->transfer_syntaxes_by_id.size(), 1);
    BOOST_REQUIRE_EQUAL(
        this->transfer_syntaxes_by_id.at(1), 
        odil::registry::ImplicitVRLittleEndian);
}

Fixture
::Fixture()
: ConnectionFixtureBase(), connection(this->socket), transfer_syntaxes_by_id()
{
    this->connection.acceptor = boost::bind(&Fixture::request_acceptor, this, _1);
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
