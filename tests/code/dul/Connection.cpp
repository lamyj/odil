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
#include "odil/registry.h"

#include <log4cpp/Category.hh>

struct OdilStatus
{
    std::shared_ptr<odil::dul::Object> pdu;

    OdilStatus()
    : pdu()
    {
        // Nothing else
    }
};

struct DCMTKStatus
{
    OFCondition request;
    OFCondition release;
    T_ASC_Parameters * parameters = nullptr;
};

struct Fixture
{
    static std::random_device random_device;
    static std::mt19937 random_generator;
    static std::uniform_int_distribution<> random_distribution;

    boost::asio::io_service service;
    boost::asio::ip::tcp::socket socket;
    odil::dul::Connection connection;
    boost::asio::ip::tcp::endpoint endpoint;
    std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor;
    odil::AssociationParameters association_parameters;
    OdilStatus odil_status;
    DCMTKStatus dcmtk_status;

    Fixture()
    : service(), socket(service), connection(socket), endpoint(),
        acceptor(), association_parameters(), odil_status(), dcmtk_status()
    {
        // Nothing else
    }

    void odil_request(
        int port,
        std::string const & calling_ae_title,
        std::string const & called_ae_title)
    {
        auto const pdu_received = [&](std::shared_ptr<odil::dul::PDU> pdu) {
            this->odil_status.pdu = pdu; };
        this->connection.connect<odil::dul::Signal::AAssociateAC>(pdu_received);
        this->connection.connect<odil::dul::Signal::AAssociateRJ>(pdu_received);
        this->connection.connect<odil::dul::Signal::AAbort>(pdu_received);

        this->endpoint = boost::asio::ip::tcp::endpoint(
            boost::asio::ip::make_address_v4("127.0.0.1"), port);

        this->association_parameters = odil::AssociationParameters()
            .set_calling_ae_title(calling_ae_title)
            .set_called_ae_title(called_ae_title)
            .set_presentation_contexts({
                {
                    1, odil::registry::VerificationSOPClass,
                    { odil::registry::ImplicitVRLittleEndian },
                    true, false
                }
            });

        this->connection.async_send(
            this->endpoint,
            std::make_shared<odil::dul::AAssociateRQ>(
                association_parameters.as_a_associate_rq()));
    }

    DCMTKStatus dcmtk_request(
        std::string const & calling_address, std::string const & called_address,
        std::string const & calling_ae_title,
        std::string const & called_ae_title)
    {
        DCMTKStatus status;

        T_ASC_Network * network;
        ASC_initializeNetwork(NET_REQUESTOR, 0, 5, &network);

        ASC_createAssociationParameters(&status.parameters, ASC_DEFAULTMAXPDU);
        ASC_setAPTitles(
            status.parameters, calling_ae_title.c_str(),
            called_ae_title.c_str(), NULL);

        ASC_setPresentationAddresses(
            status.parameters, calling_address.c_str(), called_address.c_str());

        char const * ts[] = { UID_LittleEndianImplicitTransferSyntax };
        ASC_addPresentationContext(
            status.parameters, 1, UID_VerificationSOPClass, ts, 1);

        OFCondition condition;

        T_ASC_Association *association;
        status.request = ASC_requestAssociation(
            network, status.parameters, &association);
        if(condition.good())
        {
            status.release = ASC_releaseAssociation(association);
            ASC_destroyAssociation(&association);
        }

        ASC_dropNetwork(&network);

        return status;
    }

    void odil_accept(int port)
    {
        this->endpoint = boost::asio::ip::tcp::endpoint(
            boost::asio::ip::tcp::v4(), port);

        this->acceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(
            this->service, this->endpoint);
        this->acceptor->async_accept(
            this->connection.socket,
            boost::bind(
                &odil::dul::Connection::tcp_accepted,
                &connection, boost::asio::placeholders::error));
    }

    void dcmtk_accept(
        int port,
        std::function<OFCondition(T_ASC_Association *association)> handler)
    {
        DCMTKStatus status;

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

        condition = handler(association);
        if(!condition.good())
        {
            throw std::runtime_error(
                std::string("Error in handler: ")+condition.text());
        }

        ASC_dropNetwork(&network);
    }
};

std::random_device Fixture::random_device{};
std::mt19937 Fixture::random_generator{Fixture::random_device()};
std::uniform_int_distribution<> Fixture::random_distribution{49152, 65535};

BOOST_FIXTURE_TEST_CASE(RequestorAccepted, Fixture)
{
    auto const port = Fixture::random_distribution(Fixture::random_generator);

    std::thread acceptor(
        [&](){
            this->dcmtk_accept(
                port,
                [](T_ASC_Association * association){
                    ASC_acceptPresentationContext(
                        association->params, 1,
                        UID_LittleEndianImplicitTransferSyntax);
                    ASC_acknowledgeAssociation(association);

                    T_ASC_PresentationContextID presID;
                    T_DIMSE_Message message;
                    DIMSE_receiveCommand(
                        association, DIMSE_BLOCKING, 0, &presID, &message,
                        NULL);
                    return ASC_acknowledgeRelease(association);
                });
        }
    );

    this->odil_request(port, "LOCAL", "REMOTE");
    this->connection.connect<odil::dul::Signal::AAssociateAC>(
        [&](std::shared_ptr<odil::dul::AAssociateAC>) {
            this->connection.async_send(std::make_shared<odil::dul::AReleaseRQ>());
        });
    this->service.run();

    acceptor.join();

    auto acception = std::dynamic_pointer_cast<odil::dul::AAssociateAC>(
        this->odil_status.pdu);
    BOOST_REQUIRE(acception);
}

BOOST_FIXTURE_TEST_CASE(RequestorRejected, Fixture)
{
    auto const port = Fixture::random_distribution(Fixture::random_generator);

    std::thread acceptor(
        [&](){
            this->dcmtk_accept(
                port,
                [](T_ASC_Association * association){
                    T_ASC_RejectParameters rejection;
                    rejection.result = ASC_RESULT_REJECTEDTRANSIENT;
                    rejection.source = ASC_SOURCE_SERVICEUSER;
                    rejection.reason = ASC_REASON_SU_CALLINGAETITLENOTRECOGNIZED;
                    return ASC_rejectAssociation(association, &rejection);
                });
        }
    );

    this->odil_request(port, "LOCAL", "REMOTE");
    this->service.run();

    acceptor.join();

    auto rejection = std::dynamic_pointer_cast<odil::dul::AAssociateRJ>(
        this->odil_status.pdu);
    BOOST_REQUIRE(rejection);
}

BOOST_FIXTURE_TEST_CASE(RequestorAborted, Fixture)
{
    auto const port = Fixture::random_distribution(Fixture::random_generator);

    std::thread acceptor(
        [&](){
            this->dcmtk_accept(
                port,
                [](T_ASC_Association * association){
                    T_ASC_RejectParameters rejection;
                    rejection.result = ASC_RESULT_REJECTEDTRANSIENT;
                    rejection.source = ASC_SOURCE_SERVICEUSER;
                    rejection.reason = ASC_REASON_SU_CALLINGAETITLENOTRECOGNIZED;
                    return ASC_abortAssociation(association);
                });
        }
    );

    this->odil_request(port, "LOCAL", "REMOTE");
    this->service.run();

    acceptor.join();

    auto rejection = std::dynamic_pointer_cast<odil::dul::AAbort>(
        this->odil_status.pdu);
    BOOST_REQUIRE(rejection);
}

BOOST_FIXTURE_TEST_CASE(AcceptorAccept, Fixture)
{
    bool associate_request_received = false;
    this->connection.connect<odil::dul::Signal::AAssociateRQ>(
        [&](std::shared_ptr<odil::dul::AAssociateRQ> /* pdu */) {
            associate_request_received = true;

            auto const association_parameters = odil::AssociationParameters()
                .set_calling_ae_title("LOCAL")
                .set_called_ae_title("REMOTE")
                .set_presentation_contexts({
                    {
                        1, odil::registry::VerificationSOPClass,
                        { odil::registry::ImplicitVRLittleEndian },
                        true, false
                    }
                });
            return std::make_shared<odil::dul::AAssociateAC>(
                association_parameters.as_a_associate_ac());
        });

    bool release_request_received = false;
    this->connection.connect<odil::dul::Signal::AReleaseRQ>(
        [&](std::shared_ptr<odil::dul::AReleaseRQ> /* pdu */) {
            release_request_received = true;
        });

    auto const port = Fixture::random_distribution(Fixture::random_generator);

    this->odil_accept(port);

    std::thread requestor(
        [&]() {
            this->dcmtk_status = this->dcmtk_request(
                "localhost", "localhost:"+std::to_string(port),
                "LOCAL", "REMOTE");
        }
    );

    this->service.run();
    requestor.join();

    BOOST_REQUIRE(associate_request_received);
    BOOST_REQUIRE(release_request_received);
    BOOST_REQUIRE(this->dcmtk_status.request.good());
}

BOOST_FIXTURE_TEST_CASE(AcceptorReject, Fixture)
{
    bool associate_request_received = false;
    this->connection.connect<odil::dul::Signal::AAssociateRQ>(
        [&](std::shared_ptr<odil::dul::AAssociateRQ> /* pdu */) {
            associate_request_received = true;
            return std::make_shared<odil::dul::AAssociateRJ>(1, 3, 0);
        });

    auto const port = Fixture::random_distribution(Fixture::random_generator);

    this->odil_accept(port);

    std::thread requestor(
        [&]() {
            this->dcmtk_status = this->dcmtk_request(
                "localhost", "localhost:"+std::to_string(port),
                "LOCAL", "REMOTE");
        }
    );

    service.run();
    requestor.join();

    BOOST_REQUIRE(associate_request_received);

    BOOST_REQUIRE(this->dcmtk_status.request == DUL_ASSOCIATIONREJECTED);

    T_ASC_RejectParameters rejection;
    ASC_getRejectParameters(this->dcmtk_status.parameters, &rejection);
    BOOST_REQUIRE_EQUAL(rejection.result & 0xff, 1);
    BOOST_REQUIRE_EQUAL(rejection.source & 0xff, 3);
    BOOST_REQUIRE_EQUAL(rejection.reason & 0xff, 0);
}

BOOST_FIXTURE_TEST_CASE(AcceptorAbort, Fixture)
{
    bool associate_request_received = false;
    this->connection.connect<odil::dul::Signal::AAssociateRQ>(
        [&](std::shared_ptr<odil::dul::AAssociateRQ> /* pdu */) {
            associate_request_received = true;
            return std::make_shared<odil::dul::AAbort>(0, 0);
        });

    auto const port = Fixture::random_distribution(Fixture::random_generator);

    this->odil_accept(port);

    std::thread requestor(
        [&]() {
            this->dcmtk_status = this->dcmtk_request(
                "localhost", "localhost:"+std::to_string(port),
                "LOCAL", "REMOTE");
        }
    );

    service.run();
    requestor.join();

    BOOST_REQUIRE(associate_request_received);
    BOOST_REQUIRE(this->dcmtk_status.request == DUL_PEERABORTEDASSOCIATION);
}
