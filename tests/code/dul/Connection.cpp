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

using Port = unsigned short;

struct DCMTKStatus
{
    OFCondition request;
    OFCondition release;
    OFCondition abort;
    T_ASC_Parameters * parameters = nullptr;
};

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
    Acceptor acceptor;

    odil::AssociationParameters parameters;

    Fixture();

    void test_odil_acceptor_async(std::string const & acceptor_action, bool requestor_abort);
    void test_odil_acceptor_sync(std::string const & acceptor_action, bool requestor_abort);

    void test_odil_requestor_async(std::string const & acceptor_action);
    void test_odil_requestor_sync(std::string const & acceptor_action);

    void odil_acceptor_async(
        Port port, odil::dul::Connection & connection,
        odil::dul::Connection::Acceptor const & acceptor);

    odil::dul::Connection::SynchronousStatus
    odil_acceptor_sync(
        Port port, odil::dul::Connection & connection,
        odil::dul::Connection::Acceptor const & acceptor);

    void dcmtk_acceptor(Port port,std::string const & acceptor_action);

    void odil_requestor_async(
        Port port, odil::dul::Connection & connection,
        odil::dul::PDU::Pointer & received_pdu);

    DCMTKStatus dcmtk_requestor(Port port, bool requestor_abort);

private:
    odil::dul::PDU::Pointer
    _acceptor_handler(
        odil::dul::AAssociateRQ::Pointer request,
        std::string const & acceptor_action, bool & parameters_ok);

    void _check_dcmtk_status(
        DCMTKStatus const & dcmtk_status, std::string const & acceptor_action) const;
};

BOOST_FIXTURE_TEST_CASE(OdilAcceptorAsyncAcceptDCMTKRelease, Fixture)
{ this->test_odil_acceptor_async("accept", false); }

BOOST_FIXTURE_TEST_CASE(OdilAcceptorAsyncAcceptDCMTKAbort, Fixture)
{ this->test_odil_acceptor_async("accept", true); }

BOOST_FIXTURE_TEST_CASE(OdilAcceptorAsyncRejectDCMTKRelease, Fixture)
{ this->test_odil_acceptor_async("reject", false); }

BOOST_FIXTURE_TEST_CASE(OdilAcceptorAsyncRejectDCMTKAbort, Fixture)
{ this->test_odil_acceptor_async("reject", true); }

BOOST_FIXTURE_TEST_CASE(OdilAcceptorAsyncAbortDCMTKRelease, Fixture)
{ this->test_odil_acceptor_async("abort", false); }

// This one makes no sense:
// BOOST_FIXTURE_TEST_CASE(OdilRequestorAsyncAbortDCMTKAbort, Fixture)

BOOST_FIXTURE_TEST_CASE(OdilAcceptorSyncAcceptDCMTKRelease, Fixture)
{ this->test_odil_acceptor_sync("accept", false); }

BOOST_FIXTURE_TEST_CASE(OdilAcceptorSyncAcceptDCMTKAbort, Fixture)
{ this->test_odil_acceptor_sync("accept", true); }

BOOST_FIXTURE_TEST_CASE(OdilAcceptorSyncRejectDCMTKRelease, Fixture)
{ this->test_odil_acceptor_sync("reject", false); }

BOOST_FIXTURE_TEST_CASE(OdilAcceptorSyncRejectDCMTKAbort, Fixture)
{ this->test_odil_acceptor_sync("reject", true); }

BOOST_FIXTURE_TEST_CASE(OdilAcceptorSyncAbortDCMTKRelease, Fixture)
{ this->test_odil_acceptor_sync("abort", false); }

// This one makes no sense:
// BOOST_FIXTURE_TEST_CASE(OdilRequestorSyncAbortDCMTKAbort, Fixture)

BOOST_FIXTURE_TEST_CASE(OdilRequestorAsyncDCMTKAccept, Fixture)
{ this->test_odil_requestor_async("accept"); }

BOOST_FIXTURE_TEST_CASE(OdilRequestorAsyncDCMTKReject, Fixture)
{ this->test_odil_requestor_async("reject"); }

BOOST_FIXTURE_TEST_CASE(OdilRequestorAsyncDCMTKAbort, Fixture)
{ this->test_odil_requestor_async("abort"); }

BOOST_FIXTURE_TEST_CASE(OdilRequestorSyncDCMTKAccept, Fixture)
{ this->test_odil_requestor_sync("accept"); }

BOOST_FIXTURE_TEST_CASE(OdilRequestorSyncDCMTKReject, Fixture)
{ this->test_odil_requestor_sync("reject"); }

BOOST_FIXTURE_TEST_CASE(OdilRequestorSyncDCMTKAbort, Fixture)
{ this->test_odil_requestor_sync("abort"); }

std::random_device Fixture::random_device{};
std::mt19937 Fixture::random_generator{Fixture::random_device()};
std::uniform_int_distribution<Port> Fixture::random_distribution{49152, 65535};

Fixture
::Fixture()
: service(), socket(service), endpoint(), acceptor(service, endpoint),
  parameters()
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
::test_odil_acceptor_async(
    std::string const & acceptor_action, bool requestor_abort)
{
    auto const port = Fixture::random_distribution(Fixture::random_generator);

    odil::dul::Connection connection(this->socket);

    bool parameters_ok = false;
    auto acceptor = [&](odil::dul::AAssociateRQ::Pointer request) {
        return this->_acceptor_handler(request, acceptor_action, parameters_ok);
    };

    this->odil_acceptor_async(port, connection, acceptor);

    // WARNING: make sure the acceptor is running before starting the
    // requestor thread.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    DCMTKStatus dcmtk_status;
    std::thread requestor([&](){
        dcmtk_status = this->dcmtk_requestor(port, requestor_abort); });

    this->service.run();
    requestor.join();

    this->_check_dcmtk_status(dcmtk_status, acceptor_action);
    BOOST_REQUIRE(parameters_ok);
}

void
Fixture
::test_odil_acceptor_sync(
    std::string const & acceptor_action, bool requestor_abort)
{
    auto const port = Fixture::random_distribution(Fixture::random_generator);

    odil::dul::Connection connection(this->socket);

    this->endpoint = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address_v4::from_string("127.0.0.1"), port);

    bool parameters_ok = false;

    std::thread acceptor(
        [&]() {
            connection.acceptor = [&](odil::dul::AAssociateRQ::Pointer request){
                return this->_acceptor_handler(request, acceptor_action, parameters_ok);
            };

            connection.receive(this->endpoint);
            if(acceptor_action == "accept")
            {
                // Block until we get A-RELEASE-RQ or A-ABORT
                connection.receive();
            }
        });

    // WARNING: make sure the acceptor thread is running before starting the
    // requestor thread.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    DCMTKStatus dcmtk_status;
    std::thread requestor( [&]() { dcmtk_status = this->dcmtk_requestor(port, requestor_abort); } );

    requestor.join();
    acceptor.join();

    this->_check_dcmtk_status(dcmtk_status, acceptor_action);
    BOOST_REQUIRE(parameters_ok);
}

void
Fixture
::test_odil_requestor_async(std::string const & acceptor_action)
{
    auto const port = Fixture::random_distribution(Fixture::random_generator);

    std::thread acceptor([&](){ this->dcmtk_acceptor(port, acceptor_action); });

    odil::dul::Connection connection(this->socket);
    odil::dul::PDU::Pointer received_pdu;
    this->odil_requestor_async(port, connection, received_pdu);
    if(acceptor_action == "accept")
    {
        connection.a_associate.confirmation.connect(
            [&](odil::dul::PDU::Pointer) {
                connection.async_send(std::make_shared<odil::dul::AReleaseRQ>());
            });
    }

    this->service.run();
    acceptor.join();

    if(acceptor_action == "accept")
    {
        auto acception = std::dynamic_pointer_cast<odil::dul::AAssociateAC>(
            received_pdu);
        BOOST_REQUIRE(acception);
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
::test_odil_requestor_sync(std::string const & acceptor_action)
{
    auto const port = Fixture::random_distribution(Fixture::random_generator);

    std::thread acceptor([&](){ this->dcmtk_acceptor(port, acceptor_action); });

    this->endpoint = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address_v4::from_string("127.0.0.1"), port);

    odil::dul::Connection connection(this->socket);
    auto status = connection.send(
        this->endpoint,
        std::make_shared<odil::dul::AAssociateRQ>(
            this->parameters.as_a_associate_rq()));
    if(acceptor_action == "accept")
    {
        connection.send(std::make_shared<odil::dul::AReleaseRQ>());
    }

    acceptor.join();

    BOOST_REQUIRE(status.pdu);
    BOOST_REQUIRE(!status.error_code);

    if(acceptor_action == "accept")
    {
        auto acception = std::dynamic_pointer_cast<odil::dul::AAssociateAC>(
            status.pdu);
        BOOST_REQUIRE(acception);
    }
    else if(acceptor_action == "reject")
    {
        auto rejection = std::dynamic_pointer_cast<odil::dul::AAssociateRJ>(
            status.pdu);
        BOOST_REQUIRE(rejection);
    }
    else if(acceptor_action == "abort")
    {
        auto rejection = std::dynamic_pointer_cast<odil::dul::AAbort>(
            status.pdu);
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
::odil_acceptor_async(
    Port port, odil::dul::Connection & connection,
    odil::dul::Connection::Acceptor const & acceptor)
{
    connection.acceptor = acceptor;

    this->endpoint = Fixture::Endpoint(boost::asio::ip::tcp::v4(), port);
    this->acceptor = Fixture::Acceptor(this->service, this->endpoint);
    this->acceptor.async_accept(
        this->socket,
        [&](boost::system::error_code error) {
            connection.transport_connection.indication(error);
        }
    );
}

odil::dul::Connection::SynchronousStatus
Fixture
::odil_acceptor_sync(
    Port port, odil::dul::Connection & connection,
    odil::dul::Connection::Acceptor const & acceptor)
{
    connection.acceptor = acceptor;

    this->endpoint = Fixture::Endpoint(boost::asio::ip::tcp::v4(), port);
    this->acceptor = Fixture::Acceptor(this->service, this->endpoint);

    return connection.receive(this->endpoint);
}

void
Fixture
::dcmtk_acceptor(Port port, std::string const & acceptor_action)
{
    OFCondition condition;

    T_ASC_Network * network;
    condition = ASC_initializeNetwork(NET_ACCEPTOR, port, 5, &network);
    if(!condition.good())
    {
        throw std::runtime_error("Could not initialize network");
    }

    T_ASC_Association *association;
    condition = ASC_receiveAssociation(
        network, &association, ASC_DEFAULTMAXPDU);
    if(!condition.good())
    {
        throw std::runtime_error(
            std::string("Could not receive association: ")+
            condition.text());
    }

    if(acceptor_action == "accept")
    {
        ASC_acceptPresentationContext(
            association->params, 1,
            UID_LittleEndianImplicitTransferSyntax);
        ASC_acknowledgeAssociation(association);

        T_ASC_PresentationContextID presID;
        T_DIMSE_Message message;
        DIMSE_receiveCommand(
            association, DIMSE_BLOCKING, 0, &presID, &message, nullptr);
        condition = ASC_acknowledgeRelease(association);
    }
    else if(acceptor_action == "reject")
    {
        T_ASC_RejectParameters rejection;
        rejection.result = ASC_RESULT_REJECTEDTRANSIENT;
        rejection.source = ASC_SOURCE_SERVICEUSER;
        rejection.reason = ASC_REASON_SU_CALLINGAETITLENOTRECOGNIZED;
        condition = ASC_rejectAssociation(association, &rejection);
    }
    else if(acceptor_action == "abort")
    {
        condition = ASC_abortAssociation(association);
    }
    else
    {
        throw std::runtime_error(
            "Unknown acceptor action: "+acceptor_action);
    }

    if(!condition.good())
    {
        throw std::runtime_error(
            std::string("Error in handler: ")+condition.text());
    }

    ASC_dropNetwork(&network);
}

void
Fixture
::odil_requestor_async(
    Port port, odil::dul::Connection & connection,
    odil::dul::PDU::Pointer & received_pdu)
{
    auto const on_pdu = [&](odil::dul::PDU::Pointer pdu) { received_pdu = pdu; };
    connection.a_associate.confirmation.connect(on_pdu);
    connection.a_abort.indication.connect(on_pdu);

    this->endpoint = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address_v4::from_string("127.0.0.1"), port);

    connection.async_send(
        this->endpoint,
        std::make_shared<odil::dul::AAssociateRQ>(
            this->parameters.as_a_associate_rq()));
}

DCMTKStatus
Fixture
::dcmtk_requestor(Port port, bool requestor_abort)
{
    DCMTKStatus status;

    T_ASC_Network * network;
    ASC_initializeNetwork(NET_REQUESTOR, 0, 5, &network);

    ASC_createAssociationParameters(&status.parameters, ASC_DEFAULTMAXPDU);
    ASC_setAPTitles(status.parameters, "calling", "called", nullptr);

    auto const peer_address = "localhost:"+std::to_string(port);
    ASC_setPresentationAddresses(
        status.parameters, "localhost", peer_address.c_str());

    char const * ts[] = { UID_LittleEndianImplicitTransferSyntax };
    ASC_addPresentationContext(
        status.parameters, 1, UID_RawDataStorage, ts, 1);

    OFCondition condition;

    T_ASC_Association *association;
    status.request = ASC_requestAssociation(
        network, status.parameters, &association);
    if(condition.good())
    {
        if(!requestor_abort)
        {
            status.release = ASC_releaseAssociation(association);
        }
        else
        {
            status.abort = ASC_abortAssociation(association);
        }
        ASC_destroyAssociation(&association);
    }
    else
    {
        ASC_dropNetwork(&network);
        throw std::runtime_error(
            std::string("DCMTK could not request association: ")
            + condition.text());
    }

    ASC_dropNetwork(&network);

    return status;
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

void
Fixture
::_check_dcmtk_status(
    DCMTKStatus const & dcmtk_status, std::string const & acceptor_action) const
{
    if(acceptor_action == "accept")
    {
        BOOST_REQUIRE(dcmtk_status.request.good());
    }
    else if(acceptor_action == "reject")
    {
        BOOST_REQUIRE(dcmtk_status.request == DUL_ASSOCIATIONREJECTED);
        T_ASC_RejectParameters rejection;
        ASC_getRejectParameters(dcmtk_status.parameters, &rejection);
        BOOST_REQUIRE_EQUAL(rejection.result & 0xff, 1);
        BOOST_REQUIRE_EQUAL(rejection.source & 0xff, 3);
        BOOST_REQUIRE_EQUAL(rejection.reason & 0xff, 0);
    }
    else if(acceptor_action == "abort")
    {
        BOOST_REQUIRE(dcmtk_status.request == DUL_PEERABORTEDASSOCIATION);
    }
    else
    {
        throw std::runtime_error("Unknown acceptor_action: "+acceptor_action);
    }
}

