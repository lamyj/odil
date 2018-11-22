#define BOOST_TEST_MODULE AssociationRequester
#include <boost/test/unit_test.hpp>

#include <cstdint>
#include <random>

#include <boost/asio.hpp>

#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/dimse.h>

#include "odil/AssociationRequester.h"
#include "odil/AssociationParameters.h"
#include "odil/dul/AAssociateAC.h"
#include "odil/dul/AReleaseRQ.h"
#include "odil/dul/Connection.h"
#include "odil/dul/PDU.h"
#include "odil/registry.h"

//FIXME: factorize with MessageSender, MessageReceiver, Connection
struct Fixture
{
    static std::random_device random_device;
    static std::mt19937 random_generator;
    static std::uniform_int_distribution<uint16_t> random_distribution;

    boost::asio::io_service service;
    boost::asio::ip::tcp::socket socket;
    uint16_t port;
    boost::asio::ip::tcp::endpoint endpoint;

    odil::dul::AAssociateRQ::Pointer request;

    odil::dul::Connection connection;

    odil::dul::AAssociateAC::Pointer acceptation;
    odil::dul::PDU::Pointer error_pdu;
    boost::system::error_code error_code;

    Fixture();

    void dcmtk_acceptor(uint16_t port, std::string const & action);

    void success_handler(odil::dul::AAssociateAC::Pointer pdu);
    void error_handler(
        odil::dul::PDU::Pointer pdu, boost::system::error_code code);
};

BOOST_FIXTURE_TEST_CASE(Accepted, Fixture)
{
    std::thread acceptor([&](){ this->dcmtk_acceptor(port, "accept"); });

    odil::AssociationRequester requester(
        this->service, this->connection,
        [&](odil::dul::AAssociateAC::Pointer acceptation) {
            this->success_handler(acceptation);
            this->connection.send(std::make_shared<odil::dul::AReleaseRQ>());
        },
        boost::bind(&Fixture::error_handler, this, _1, _2));
    
    requester(this->endpoint, this->request);

    this->service.run();
    acceptor.join();

    BOOST_REQUIRE(this->acceptation);
    BOOST_REQUIRE(!this->error_pdu);
    BOOST_REQUIRE(!this->error_code);
}

BOOST_FIXTURE_TEST_CASE(Rejected, Fixture)
{
    std::thread acceptor([&](){ this->dcmtk_acceptor(port, "reject"); });

    odil::AssociationRequester requester(
        this->service, this->connection,
        boost::bind(&Fixture::success_handler, this, _1),
        boost::bind(&Fixture::error_handler, this, _1, _2));
    
    requester(this->endpoint, this->request);

    this->service.run();
    acceptor.join();

    BOOST_REQUIRE(!this->acceptation);
    BOOST_REQUIRE(
        std::dynamic_pointer_cast<odil::dul::AAssociateRJ>(this->error_pdu));
    BOOST_REQUIRE(!this->error_code);
}

BOOST_FIXTURE_TEST_CASE(Aborted, Fixture)
{
    std::thread acceptor([&](){ this->dcmtk_acceptor(port, "abort"); });

    odil::AssociationRequester requester(
        this->service, this->connection,
        boost::bind(&Fixture::success_handler, this, _1),
        boost::bind(&Fixture::error_handler, this, _1, _2));
    
    requester(this->endpoint, this->request);

    this->service.run();
    acceptor.join();

    BOOST_REQUIRE(!this->acceptation);
    BOOST_REQUIRE(std::dynamic_pointer_cast<odil::dul::AAbort>(this->error_pdu));
    BOOST_REQUIRE(!this->error_code);
}

std::random_device Fixture::random_device{};
std::mt19937 Fixture::random_generator{Fixture::random_device()};
std::uniform_int_distribution<uint16_t> Fixture::random_distribution{49152, 65535};

Fixture
::Fixture()
: service(), socket(service), 
    port(Fixture::random_distribution(Fixture::random_generator)), 
    endpoint(boost::asio::ip::address_v4::from_string("127.0.0.1"), port),
    request(nullptr), connection(socket), acceptation(nullptr), 
    error_pdu(nullptr), error_code()
{
    odil::AssociationParameters parameters;
    parameters
        .set_calling_ae_title("calling").set_called_ae_title("called")
        .set_presentation_contexts({
            {
                1, odil::registry::RawDataStorage,
                { odil::registry::ImplicitVRLittleEndian }, true, false } });
    this->request = std::make_shared<odil::dul::AAssociateRQ>(
        parameters.as_a_associate_rq());
    
}

void
Fixture
::dcmtk_acceptor(uint16_t port, std::string const & action)
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

    if(action == "accept")
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
    else if(action == "reject")
    {
        T_ASC_RejectParameters rejection;
        rejection.result = ASC_RESULT_REJECTEDTRANSIENT;
        rejection.source = ASC_SOURCE_SERVICEUSER;
        rejection.reason = ASC_REASON_SU_CALLINGAETITLENOTRECOGNIZED;
        condition = ASC_rejectAssociation(association, &rejection);
    }
    else if(action == "abort")
    {
        condition = ASC_abortAssociation(association);
    }
    else
    {
        throw std::runtime_error("Unknown acceptor action: "+action);
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
::success_handler(odil::dul::AAssociateAC::Pointer pdu)
{
    this->acceptation = pdu;
}

void 
Fixture
::error_handler(
    odil::dul::PDU::Pointer pdu, boost::system::error_code code)
{
    this->error_pdu = pdu;
    this->error_code = code;
}
