#define BOOST_TEST_MODULE AssociationRequester
#include <boost/test/unit_test.hpp>

#include <thread>

#include "odil/AssociationRequester.h"
#include "odil/AssociationParameters.h"
#include "odil/dul/AAssociateAC.h"
#include "odil/dul/AReleaseRQ.h"
#include "odil/dul/Connection.h"
#include "odil/dul/PDU.h"
#include "odil/registry.h"

#include "../ConnectionFixtureBase.h"

struct Fixture: public ConnectionFixtureBase
{
    odil::dul::AAssociateRQ::Pointer request;
    odil::dul::Connection connection;

    odil::dul::AAssociateAC::Pointer acceptation;
    odil::dul::PDU::Pointer error_pdu;
    boost::system::error_code error_code;

    Fixture();

    void success_handler(odil::dul::AAssociateAC::Pointer pdu);
    void error_handler(
        odil::dul::PDU::Pointer pdu, boost::system::error_code code);
};

BOOST_FIXTURE_TEST_CASE(Accepted, Fixture)
{
    this->setup_odil_requestor();

    std::thread acceptor([&](){ this->dcmtk_acceptor("accept"); });

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
    this->setup_odil_requestor();

    std::thread acceptor([&](){ this->dcmtk_acceptor("reject"); });

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
    this->setup_odil_requestor();
    
    std::thread acceptor_thread([&](){ this->dcmtk_acceptor("abort"); });

    odil::AssociationRequester requester(
        this->service, this->connection,
        boost::bind(&Fixture::success_handler, this, _1),
        boost::bind(&Fixture::error_handler, this, _1, _2));
    
    requester(this->endpoint, this->request);

    this->service.run();
    acceptor_thread.join();

    BOOST_REQUIRE(!this->acceptation);
    BOOST_REQUIRE(std::dynamic_pointer_cast<odil::dul::AAbort>(this->error_pdu));
    BOOST_REQUIRE(!this->error_code);
}

Fixture
::Fixture()
: ConnectionFixtureBase(),
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
