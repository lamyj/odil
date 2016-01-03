#define BOOST_TEST_MODULE EchoSCP
#include <boost/test/unit_test.hpp>

#include <cstdlib>
#include <memory>
#include <thread>

#include <boost/asio.hpp>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/EchoSCP.h"
#include "dcmtkpp/SCPDispatcher.h"
#include "dcmtkpp/message/CEchoRequest.h"
#include "dcmtkpp/message/Response.h"

dcmtkpp::Value::Integer echo(dcmtkpp::message::CEchoRequest const & request)
{
    return dcmtkpp::message::Response::Success;
}

void run_server()
{
    dcmtkpp::Association association;
    association.receive_association(boost::asio::ip::tcp::v4(), 11113);

    auto echo_scp = std::make_shared<dcmtkpp::EchoSCP>(association, echo);
    dcmtkpp::SCPDispatcher dispatcher(association);
    dispatcher.set_scp(dcmtkpp::message::Message::Command::C_ECHO_RQ, echo_scp);
    dispatcher.dispatch();
    try
    {
        dispatcher.dispatch();
    }
    catch(dcmtkpp::AssociationReleased const &)
    {
        // Do nothing
    }
}

void run_client()
{
    system("echoscu localhost 11113");
}

BOOST_AUTO_TEST_CASE(EchoSCP)
{
    std::thread server(run_server);
    usleep(100000);
    std::thread client(run_client);

    server.join();
    client.join();
}
