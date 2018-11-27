#define BOOST_TEST_MODULE dul::Connection
#include <boost/test/unit_test.hpp>

#include <cstdlib>
#include <random>
#include <thread>

#include <boost/asio.hpp>

#include "dcmtk/dcmnet/assoc.h"
#include "dcmtk/dcmnet/dimse.h"

#include "odil/AssociationParameters.h"
#include "odil/dul/Connection.h"
#include "odil/logging.h"
#include "odil/registry.h"

#include "../../ConnectionFixtureBase.h"

struct Fixture: public ConnectionFixtureBase
{
public:
    odil::AssociationParameters parameters;

    Fixture();

    void test_odil_acceptor(std::string const & acceptor_action, bool requestor_abort);
    
    void test_odil_requestor(std::string const & acceptor_action);
    
    void odil_acceptor(
        odil::dul::Connection & connection,
        odil::dul::Connection::Acceptor const & acceptor);

    void odil_requestor(
        odil::dul::Connection & connection,
        odil::dul::PDU::Pointer & received_pdu);

private:
    odil::dul::PDU::Pointer
    _acceptor_handler(
        odil::dul::AAssociateRQ::Pointer request,
        std::string const & acceptor_action, bool & parameters_ok);
};

BOOST_FIXTURE_TEST_CASE(OdilAcceptorAcceptDCMTKRelease, Fixture)
{ this->test_odil_acceptor("accept", false); }

BOOST_FIXTURE_TEST_CASE(OdilAcceptorAcceptDCMTKAbort, Fixture)
{ this->test_odil_acceptor("accept", true); }

BOOST_FIXTURE_TEST_CASE(OdilAcceptorRejectDCMTKRelease, Fixture)
{ this->test_odil_acceptor("reject", false); }

BOOST_FIXTURE_TEST_CASE(OdilAcceptorRejectDCMTKAbort, Fixture)
{ this->test_odil_acceptor("reject", true); }

BOOST_FIXTURE_TEST_CASE(OdilAcceptorAbortDCMTKRelease, Fixture)
{ this->test_odil_acceptor("abort", false); }

// This one makes no sense: OdilRequestorAbortDCMTKAbort

BOOST_FIXTURE_TEST_CASE(OdilRequestorDCMTKAccept, Fixture)
{ this->test_odil_requestor("accept"); }

BOOST_FIXTURE_TEST_CASE(OdilRequestorDCMTKReject, Fixture)
{ this->test_odil_requestor("reject"); }

BOOST_FIXTURE_TEST_CASE(OdilRequestorDCMTKAbort, Fixture)
{ this->test_odil_requestor("abort"); }

Fixture
::Fixture()
: ConnectionFixtureBase(), parameters()
{
    this->parameters
        .set_calling_ae_title("calling").set_called_ae_title("called")
        .set_presentation_contexts({
            {
                1, odil::registry::RawDataStorage,
                { odil::registry::ExplicitVRLittleEndian }, true, false } });
}

void
Fixture
::test_odil_acceptor(
    std::string const & acceptor_action, bool requestor_abort)
{
    this->setup_odil_receiver();

    odil::dul::Connection connection(this->socket);

    bool parameters_ok = false;
    auto acceptor = [&](odil::dul::AAssociateRQ::Pointer request) {
        return this->_acceptor_handler(request, acceptor_action, parameters_ok);
    };

    this->odil_acceptor(connection, acceptor);

    // WARNING: make sure the acceptor is running before starting the
    // requestor thread.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::thread requestor(
        [&](){ this->dcmtk_requestor(
            this->parameters.get_presentation_contexts()[0].abstract_syntax.c_str(),
            this->parameters.get_presentation_contexts()[0].transfer_syntaxes[0].c_str(),
            requestor_abort); });

    this->service.run();
    requestor.join();

    BOOST_REQUIRE(parameters_ok);
}

void
Fixture
::test_odil_requestor(std::string const & acceptor_action)
{
    this->setup_odil_requestor();

    std::thread acceptor([&](){ this->dcmtk_acceptor(acceptor_action); });

    odil::dul::Connection connection(this->socket);
    odil::dul::PDU::Pointer received_pdu;
    this->odil_requestor(connection, received_pdu);
    if(acceptor_action == "accept")
    {
        connection.a_associate.confirmation.connect(
            [&](odil::dul::PDU::Pointer) {
                connection.send(std::make_shared<odil::dul::AReleaseRQ>());
            });
    }

    this->service.run();
    acceptor.join();

    if(acceptor_action == "accept")
    {
        auto acceptation = std::dynamic_pointer_cast<odil::dul::AAssociateAC>(
            received_pdu);
        BOOST_REQUIRE(acceptation);
    }
    else if(acceptor_action == "reject")
    {
        auto rejection = std::dynamic_pointer_cast<odil::dul::AAssociateRJ>(
            received_pdu);
        BOOST_REQUIRE(rejection);
    }
    else if(acceptor_action == "abort")
    {
        auto rejection = std::dynamic_pointer_cast<odil::dul::AAbort>(
            received_pdu);
        BOOST_REQUIRE(rejection);
    }
    else
    {
        throw std::runtime_error(
            "Unknown acceptor action: "+acceptor_action);
    }
}

void
Fixture
::odil_acceptor(
    odil::dul::Connection & connection,
    odil::dul::Connection::Acceptor const & acceptor)
{
    connection.acceptor = acceptor;

    this->acceptor.async_accept(
        this->socket,
        [&](boost::system::error_code error) {
            connection.transport_connection.indication(error);
        }
    );
}

void
Fixture
::odil_requestor(
    odil::dul::Connection & connection, odil::dul::PDU::Pointer & received_pdu)
{
    auto const on_pdu = [&](odil::dul::PDU::Pointer pdu) { received_pdu = pdu; };
    connection.a_associate.confirmation.connect(on_pdu);
    connection.a_abort.indication.connect(on_pdu);

    connection.send(
        this->endpoint,
        std::make_shared<odil::dul::AAssociateRQ>(
            this->parameters.as_a_associate_rq()));
}

odil::dul::PDU::Pointer
Fixture
::_acceptor_handler(
    odil::dul::AAssociateRQ::Pointer request,
    std::string const & acceptor_action, bool & parameters_ok)
{
    odil::AssociationParameters const request_parameters(*request);
    parameters_ok = (request_parameters == this->parameters);

    odil::dul::PDU::Pointer result;

    if(acceptor_action == "accept")
    {
        result = std::make_shared<odil::dul::AAssociateAC>(
            this->parameters.as_a_associate_ac());
    }
    else if(acceptor_action == "reject")
    {
        result = std::make_shared<odil::dul::AAssociateRJ>(1, 3, 0);
    }
    else if(acceptor_action == "abort")
    {
        result = std::make_shared<odil::dul::AAbort>(0, 0);
    }
    else
    {
        throw std::runtime_error("Unknown acceptor_action: "+acceptor_action);
    }
    return result;
}
