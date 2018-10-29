#define BOOST_TEST_MODULE SCPDispatcher
#include <boost/test/unit_test.hpp>

#include <chrono>
#include <memory>
#include <thread>

#include "odil/Association.h"
#include "odil/EchoSCP.h"
#include "odil/Exception.h"
#include "odil/SCPDispatcher.h"
#include "odil/message/Message.h"
#include "odil/message/Response.h"

struct Status
{
    int client;
    std::string server;
    bool called;
};

void run_server(Status * status, bool with_echo)
{
    odil::Association association;
    association.set_tcp_timeout(boost::posix_time::seconds(1));

    try
    {
        association.receive_association(boost::asio::ip::tcp::v4(), 11113);

        auto echo_scp = std::make_shared<odil::EchoSCP>(association,
            [&status](std::shared_ptr<odil::message::CEchoRequest const>)
            {
                status->called = true;
                return odil::message::Response::Success;
            });

        odil::SCPDispatcher dispatcher(association);

        if(with_echo)
        {
            dispatcher.set_scp(
                odil::message::Message::Command::C_ECHO_RQ, echo_scp);
        }

        dispatcher.dispatch();

        // Should throw with peer closing connection
        association.receive_message();
    }
    catch(odil::AssociationAborted const &)
    {
        status->server = "abort";
    }
    catch(odil::AssociationReleased const &)
    {
        status->server = "release";
    }
    catch(odil::Exception const & e)
    {
        status->server = e.what();
    }
    catch(...)
    {
        status->server = "Other exception";
    }
}

void run_echo_client(Status * status)
{
    std::string command = "echoscu -ll error";
    command += " 127.0.0.1 11113";
    status->client = system(command.c_str());
}

BOOST_AUTO_TEST_CASE(Empty)
{
    odil::Association association;
    odil::SCPDispatcher dispatcher(association);
    BOOST_REQUIRE_EQUAL(
        dispatcher.has_scp(odil::message::Message::Command::C_ECHO_RQ),
        false);
    BOOST_REQUIRE_THROW(
        dispatcher.get_scp(odil::message::Message::Command::C_ECHO_RQ),
        odil::Exception);
}

BOOST_AUTO_TEST_CASE(SCP)
{
    odil::Association association;
    odil::SCPDispatcher dispatcher(association);

    auto scp = std::make_shared<odil::EchoSCP>(association);
    dispatcher.set_scp(
        odil::message::Message::Command::C_ECHO_RQ,
        scp);

    BOOST_REQUIRE_NO_THROW(
        dispatcher.get_scp(odil::message::Message::Command::C_ECHO_RQ));
}

BOOST_AUTO_TEST_CASE(DispatchWithEcho)
{
    Status status = { -1, "", false };

    std::thread server(run_server, &status, true);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread client(run_echo_client, &status);

    server.join();
    client.join();

    BOOST_REQUIRE_EQUAL(status.client, 0);
    BOOST_REQUIRE_EQUAL(status.server, "release");
    BOOST_REQUIRE_EQUAL(status.called, true);
}

BOOST_AUTO_TEST_CASE(DispatchWithoutEcho)
{
    Status status = { -1, "", false };

    std::thread server(run_server, &status, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread client(run_echo_client, &status);

    server.join();
    client.join();

    BOOST_REQUIRE_EQUAL(status.client, 0);
    BOOST_REQUIRE_EQUAL(status.server, "No provider for: 0030");
    BOOST_REQUIRE_EQUAL(status.called, false);
}
