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
    odil::dul::PDU::Pointer received_pdu;
    DCMTKStatus dcmtk_status;

    Fixture()
    : service(), socket(service), connection(socket), endpoint(),
        acceptor(), association_parameters(), received_pdu(), dcmtk_status()
    {
        this->association_parameters = odil::AssociationParameters()
            .set_calling_ae_title("xxx").set_called_ae_title("yyy")
            .set_presentation_contexts({ { 1, "foo", { "bar" }, true, false } });
    }

    void odil_request(int port)
    {
        auto const on_pdu = [&](odil::dul::PDU::Pointer pdu) {
            this->received_pdu = pdu; };
        this->connection.a_associate.confirmation.connect(on_pdu);
        this->connection.a_abort.indication.connect(on_pdu);

        this->endpoint = boost::asio::ip::tcp::endpoint(
            boost::asio::ip::address_v4::from_string("127.0.0.1"), port);

        this->connection.async_send(
            this->endpoint,
            std::make_shared<odil::dul::AAssociateRQ>(
                this->association_parameters.as_a_associate_rq()));
    }

    DCMTKStatus dcmtk_request(int port)
    {
        DCMTKStatus status;

        T_ASC_Network * network;
        ASC_initializeNetwork(NET_REQUESTOR, 0, 5, &network);

        ASC_createAssociationParameters(&status.parameters, ASC_DEFAULTMAXPDU);
        ASC_setAPTitles(status.parameters, "xxx", "yyy", NULL);

        auto const peer_address = "localhost:"+std::to_string(port);
        ASC_setPresentationAddresses(
            status.parameters, "localhost", peer_address.c_str());

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
            [&](boost::system::error_code error) {
                this->connection.transport_connection.indication(error);
            }
        );
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

    this->odil_request(port);
    this->connection.a_associate.confirmation.connect(
        [&](odil::dul::PDU::Pointer) {
            this->connection.async_send(std::make_shared<odil::dul::AReleaseRQ>());
        });
    this->service.run();

    acceptor.join();

    auto acception = std::dynamic_pointer_cast<odil::dul::AAssociateAC>(
        this->received_pdu);
    BOOST_REQUIRE(acception);
}

BOOST_FIXTURE_TEST_CASE(RequestorAcceptedSync, Fixture)
{
    auto const port = Fixture::random_distribution(Fixture::random_generator);

    std::thread acceptor(
        [&](){
            this->dcmtk_accept(
                port,
                [](T_ASC_Association * association){
                    auto const pc_count = ASC_countPresentationContexts(
                        association->params);
                    for(int i=0; i<pc_count; ++i)
                    {
                        T_ASC_PresentationContext pc;
                        ASC_getPresentationContext(
                            association->params, i, &pc);
                        ASC_acceptPresentationContext(
                            association->params, pc.presentationContextID,
                            pc.proposedTransferSyntaxes[0]);
                    }
                    ASC_acknowledgeAssociation(association);

                    T_ASC_PresentationContextID presID;
                    T_DIMSE_Message message;
                    auto condition = DIMSE_receiveCommand(
                        association, DIMSE_BLOCKING, 0, &presID, &message,
                        NULL);
                    BOOST_REQUIRE(condition == DUL_PEERREQUESTEDRELEASE);
                    return ASC_acknowledgeRelease(association);
                });
        }
    );

    this->endpoint = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address_v4::from_string("127.0.0.1"), port);

    auto status = this->connection.send(
        this->endpoint,
        std::make_shared<odil::dul::AAssociateRQ>(
            this->association_parameters.as_a_associate_rq()));
    BOOST_REQUIRE(
        status.pdu
        && status.pdu->get_pdu_type() == odil::dul::AAssociateAC::type);
    BOOST_REQUIRE(!status.error_code);

    status = this->connection.send(std::make_shared<odil::dul::AReleaseRQ>());
    BOOST_REQUIRE(
        status.pdu
        && status.pdu->get_pdu_type() == odil::dul::AReleaseRP::type);
    BOOST_REQUIRE(!status.error_code);

    acceptor.join();
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

    this->odil_request(port);
    this->service.run();

    acceptor.join();

    auto rejection = std::dynamic_pointer_cast<odil::dul::AAssociateRJ>(
        this->received_pdu);
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

    this->odil_request(port);
    this->service.run();

    acceptor.join();

    auto rejection = std::dynamic_pointer_cast<odil::dul::AAbort>(
        this->received_pdu);
    BOOST_REQUIRE(rejection);
}

BOOST_FIXTURE_TEST_CASE(AcceptorAccept, Fixture)
{
    bool associate_request_received = false;
    this->connection.acceptor = [&](odil::dul::AAssociateRQ::Pointer) {
        associate_request_received = true;

        return std::make_shared<odil::dul::AAssociateAC>(
            this->association_parameters.as_a_associate_ac());
    };

    bool release_request_received = false;
    this->connection.a_release.indication.connect(
        [&](odil::dul::AReleaseRQ::Pointer /* pdu */) {
            release_request_received = true;
        });

    auto const port = Fixture::random_distribution(Fixture::random_generator);

    this->odil_accept(port);

    std::thread requestor(
        [&]() { this->dcmtk_status = this->dcmtk_request(port); }
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
    this->connection.acceptor = [&](odil::dul::AAssociateRQ::Pointer) {
        associate_request_received = true;
        return std::make_shared<odil::dul::AAssociateRJ>(1, 3, 0);
    };

    auto const port = Fixture::random_distribution(Fixture::random_generator);

    this->odil_accept(port);

    std::thread requestor(
        [&]() { this->dcmtk_status = this->dcmtk_request(port); }
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
    this->connection.acceptor = [&](odil::dul::AAssociateRQ::Pointer) {
            associate_request_received = true;
            return std::make_shared<odil::dul::AAbort>(0, 0);
        };

    auto const port = Fixture::random_distribution(Fixture::random_generator);

    this->odil_accept(port);

    std::thread requestor(
        [&]() { this->dcmtk_status = this->dcmtk_request(port); }
    );

    service.run();
    requestor.join();

    BOOST_REQUIRE(associate_request_received);
    BOOST_REQUIRE(this->dcmtk_status.request == DUL_PEERABORTEDASSOCIATION);
}

BOOST_FIXTURE_TEST_CASE(AcceptorAcceptSync, Fixture)
{
    auto const port = Fixture::random_distribution(Fixture::random_generator);

    this->endpoint = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address_v4::from_string("127.0.0.1"), port);

    bool associate_request_received = false;
    bool release_request_received = false;

    std::thread acceptor(
        [&]() {
            this->connection.acceptor = [&](odil::dul::AAssociateRQ::Pointer){
                associate_request_received = true;
                return std::make_shared<odil::dul::AAssociateAC>(
                    this->association_parameters.as_a_associate_ac());
            };

            this->connection.receive(this->endpoint);

            auto status = this->connection.receive();
            if(std::dynamic_pointer_cast<odil::dul::AReleaseRQ>(status.pdu))
            {
                release_request_received = true;
            }
        });

    // WARNING: make sure the acceptor thread is running before starting the
    // requestor thread.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread requestor(
        [&]() { this->dcmtk_status = this->dcmtk_request(port); }
    );

    requestor.join();
    acceptor.join();

    BOOST_REQUIRE(associate_request_received);
    BOOST_REQUIRE(release_request_received);
    BOOST_REQUIRE(this->dcmtk_status.request.good());
}

BOOST_FIXTURE_TEST_CASE(AcceptorRejectSync, Fixture)
{
    auto const port = Fixture::random_distribution(Fixture::random_generator);

    this->endpoint = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address_v4::from_string("127.0.0.1"), port);

    bool associate_request_received = false;

    std::thread acceptor(
        [&]() {
            this->connection.acceptor = [&](odil::dul::AAssociateRQ::Pointer){
                associate_request_received = true;
                return std::make_shared<odil::dul::AAssociateRJ>(1, 3, 0);
            };

            this->connection.receive(this->endpoint);
        });

    // WARNING: make sure the acceptor thread is running before starting the
    // requestor thread.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread requestor(
        [&]() { this->dcmtk_status = this->dcmtk_request(port); }
    );

    requestor.join();
    acceptor.join();

    BOOST_REQUIRE(associate_request_received);

    BOOST_REQUIRE(this->dcmtk_status.request == DUL_ASSOCIATIONREJECTED);

    T_ASC_RejectParameters rejection;
    ASC_getRejectParameters(this->dcmtk_status.parameters, &rejection);
    BOOST_REQUIRE_EQUAL(rejection.result & 0xff, 1);
    BOOST_REQUIRE_EQUAL(rejection.source & 0xff, 3);
    BOOST_REQUIRE_EQUAL(rejection.reason & 0xff, 0);
}

BOOST_FIXTURE_TEST_CASE(AcceptorAbortSync, Fixture)
{
    auto const port = Fixture::random_distribution(Fixture::random_generator);

    this->endpoint = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address_v4::from_string("127.0.0.1"), port);

    bool associate_request_received = false;

    std::thread acceptor(
        [&]() {
            this->connection.acceptor = [&](odil::dul::AAssociateRQ::Pointer){
                associate_request_received = true;
                return std::make_shared<odil::dul::AAbort>(0, 0);
            };

            this->connection.receive(this->endpoint);
        });

    // WARNING: make sure the acceptor thread is running before starting the
    // requestor thread.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread requestor(
        [&]() { this->dcmtk_status = this->dcmtk_request(port); }
    );

    requestor.join();
    acceptor.join();

    BOOST_REQUIRE(associate_request_received);
    BOOST_REQUIRE(this->dcmtk_status.request == DUL_PEERABORTEDASSOCIATION);
}
