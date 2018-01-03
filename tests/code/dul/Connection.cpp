#define BOOST_TEST_MODULE dul::Connection
#include <boost/test/unit_test.hpp>

#include <cstdlib>
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
    bool accepted;
    bool rejected;
    std::shared_ptr<odil::pdu::Object> pdu;

    OdilStatus()
    : accepted(false), rejected(false), pdu()
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
    boost::asio::io_service service;
    boost::asio::ip::tcp::socket socket;
    odil::dul::Connection connection;
    boost::asio::ip::tcp::endpoint endpoint;
    std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor;
    odil::AssociationParameters association_parameters;
    OdilStatus odil_status;
    DCMTKStatus dcmtk_status;

    Fixture()
    : service(), socket(service), connection(service, socket), endpoint(),
        acceptor(), association_parameters(), odil_status(), dcmtk_status()
    {
        // Nothing else
    }

    void odil_request(
        std::string const & calling_ae_title,
        std::string const & called_ae_title)
    {
        this->connection.connect<odil::dul::Signal::AAssociateAC>(
            [&](std::shared_ptr<odil::pdu::AAssociateAC> pdu) {
                this->odil_status.accepted = true;
                this->odil_status.pdu = pdu;
                this->connection.async_send(
                    std::make_shared<odil::pdu::AReleaseRQ>());
            });
        this->connection.connect<odil::dul::Signal::AAssociateRJ>(
            [&](std::shared_ptr<odil::pdu::AAssociateRJ> pdu) {
                this->odil_status.rejected = true;
                this->odil_status.pdu = pdu;
            });

        this->endpoint = boost::asio::ip::tcp::endpoint(
            boost::asio::ip::make_address_v4("127.0.0.1"), 11112);

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
            std::make_shared<odil::pdu::AAssociateRQ>(
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

    void odil_accept()
    {
        this->endpoint = boost::asio::ip::tcp::endpoint(
            boost::asio::ip::tcp::v4(), 11112);

        this->acceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(
            this->service, this->endpoint);
        this->acceptor->async_accept(
            this->connection.socket,
            boost::bind(
                &odil::dul::Connection::tcp_accepted,
                &connection, boost::asio::placeholders::error));
    }

    void dcmtk_accept(
        std::function<OFCondition(T_ASC_Association *association)> handler)
    {
        DCMTKStatus status;

        OFCondition condition;

        T_ASC_Network * network;
        condition = ASC_initializeNetwork(NET_ACCEPTOR, 11112, 5, &network);
        if(!condition.good())
        {
            throw std::runtime_error("Could not initialize network");
        }

        T_ASC_Association *association;
        condition = ASC_receiveAssociation(
            network, &association, ASC_DEFAULTMAXPDU);
        if(!condition.good())
        {
            throw std::runtime_error("Could not receive association");
        }

        condition = handler(association);
        if(!condition.good())
        {
            std::cout << condition.text() << std::endl;
            throw std::runtime_error("Error in handler");
        }

        ASC_dropNetwork(&network);
    }
};

BOOST_FIXTURE_TEST_CASE(RequestorAccepted, Fixture)
{
    std::thread acceptor(
        [this](){
            this->dcmtk_accept(
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
                    DIMSE_receiveCommand(
                        association, DIMSE_BLOCKING, 0, &presID, &message,
                        NULL);
                    return ASC_acknowledgeRelease(association);
                });
        }
    );

    this->odil_request("LOCAL", "REMOTE");
    this->service.run();

    acceptor.join();

    BOOST_REQUIRE(this->odil_status.accepted);
    BOOST_REQUIRE(!this->odil_status.rejected);
    auto acception = std::dynamic_pointer_cast<odil::pdu::AAssociateAC>(
        this->odil_status.pdu);
    odil::AssociationParameters const acceptation_parameters(
        *acception, this->association_parameters);
    auto const & proposed_pcs =
        this->association_parameters.get_presentation_contexts();
    auto const & accepted_pcs =
        acceptation_parameters.get_presentation_contexts();

    BOOST_REQUIRE_EQUAL(accepted_pcs.size(), proposed_pcs.size());
    for(unsigned int i=0; i<accepted_pcs.size(); ++i)
    {
        BOOST_REQUIRE_EQUAL(accepted_pcs[i].id, proposed_pcs[i].id);
        BOOST_REQUIRE_EQUAL(
            accepted_pcs[i].abstract_syntax, proposed_pcs[i].abstract_syntax);
        BOOST_REQUIRE_EQUAL(
            accepted_pcs[i].transfer_syntaxes[0],
            proposed_pcs[i].transfer_syntaxes[0]);
    }
}

BOOST_FIXTURE_TEST_CASE(RequestorRejected, Fixture)
{
    std::thread acceptor(
        [this](){
            this->dcmtk_accept(
                [](T_ASC_Association * association){
                    T_ASC_RejectParameters rejection;
                    rejection.result = ASC_RESULT_REJECTEDTRANSIENT;
                    rejection.source = ASC_SOURCE_SERVICEUSER;
                    rejection.reason = ASC_REASON_SU_CALLINGAETITLENOTRECOGNIZED;
                    return ASC_rejectAssociation(association, &rejection);
                });
        }
    );

    this->odil_request("LOCAL", "REMOTE");
    this->service.run();

    acceptor.join();

    BOOST_REQUIRE(!this->odil_status.accepted);
    BOOST_REQUIRE(this->odil_status.rejected);
    auto rejection = std::dynamic_pointer_cast<odil::pdu::AAssociateRJ>(
        this->odil_status.pdu);
    BOOST_REQUIRE_EQUAL(rejection->get_result(), 2);
    BOOST_REQUIRE_EQUAL(rejection->get_source(), 1);
    BOOST_REQUIRE_EQUAL(rejection->get_reason(), 3);
}

BOOST_FIXTURE_TEST_CASE(AcceptorAccept, Fixture)
{
    bool associate_request_received = false;
    this->connection.connect<odil::dul::Signal::AAssociateRQ>(
        [&](std::shared_ptr<odil::pdu::AAssociateRQ> /* pdu */) {
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
            return std::make_shared<odil::pdu::AAssociateAC>(
                association_parameters.as_a_associate_ac());
        });

    bool release_request_received = false;
    this->connection.connect<odil::dul::Signal::AReleaseRQ>(
        [&](std::shared_ptr<odil::pdu::AReleaseRQ> /* pdu */) {
            release_request_received = true;
        });

    this->odil_accept();

    std::thread requestor(
        [&]() {
            this->dcmtk_status = this->dcmtk_request(
                "localhost", "localhost:11112", "LOCAL", "REMOTE");
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
        [&](std::shared_ptr<odil::pdu::AAssociateRQ> /* pdu */) {
            associate_request_received = true;
            return std::make_shared<odil::pdu::AAssociateRJ>(1, 3, 0);
        });

    this->odil_accept();

    std::thread requestor(
        [&]() {
            this->dcmtk_status = this->dcmtk_request(
                "localhost", "localhost:11112", "LOCAL", "REMOTE");
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
