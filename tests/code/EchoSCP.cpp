#define BOOST_TEST_MODULE EchoSCP
#include <boost/test/unit_test.hpp>

#include <chrono>
#include <cstdlib>
#include <thread>

#include <boost/asio.hpp>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/EchoSCP.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/message/CEchoRequest.h"
#include "dcmtkpp/message/Response.h"

struct Status
{
    int client;
    std::string server;
    bool called;
};

void run_server(Status * status)
{
    dcmtkpp::Association association;
    association.set_tcp_timeout(boost::posix_time::seconds(1));

    try
    {
        association.receive_association(boost::asio::ip::tcp::v4(), 11113);

        dcmtkpp::EchoSCP echo_scp(association,
            [status](dcmtkpp::message::CEchoRequest const &)
            {
                status->called = true;
                return dcmtkpp::message::Response::Success;
            });

        // Get echo message
        auto const message = association.receive_message();
        echo_scp(message);
        // Should throw with peer closing connection
        association.receive_message();
    }
    catch(dcmtkpp::AssociationAborted const &)
    {
        status->server = "abort";
    }
    catch(dcmtkpp::AssociationReleased const &)
    {
        status->server = "release";
    }
    catch(dcmtkpp::Exception const &)
    {
        status->server = "Other DCMTK++ exception";
    }
    catch(...)
    {
        status->server = "Other exception";
    }
}

void run_client(Status * status, bool use_abort)
{
    std::string command = "echoscu";
    if(use_abort)
    {
        command += " --abort";
    }
    command += " 127.0.0.1 11113";
    status->client = system(command.c_str());
}

BOOST_AUTO_TEST_CASE(Release)
{
    Status status = { -1, "", false };

    std::thread server(run_server, &status);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread client(run_client, &status, false);

    server.join();
    client.join();

    BOOST_REQUIRE_EQUAL(status.client, 0);
    BOOST_REQUIRE_EQUAL(status.server, "release");
    BOOST_REQUIRE_EQUAL(status.called, true);
}

BOOST_AUTO_TEST_CASE(Abort)
{
    Status status = { -1, "", false };

    std::thread server(run_server, &status);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread client(run_client, &status, true);

    server.join();
    client.join();

    BOOST_REQUIRE_EQUAL(status.client, 0);
    BOOST_REQUIRE_EQUAL(status.server, "abort");
    BOOST_REQUIRE_EQUAL(status.called, true);
}
