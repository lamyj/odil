#define BOOST_TEST_MODULE NCreateSCP
#include <boost/test/unit_test.hpp>

#include <chrono>
#include <cstdlib>
#include <thread>

#include <boost/asio.hpp>

#include "odil/Association.h"
#include "odil/AssociationAborted.h"
#include "odil/AssociationReleased.h"
#include "odil/NCreateSCP.h"
#include "odil/Exception.h"
#include "odil/message/NCreateRequest.h"
#include "odil/message/Response.h"

struct Status
{
    int client;
    std::string server;
    bool called;
};

void run_server(Status * status)
{
    odil::Association association;
    // FIXME
    // association.set_tcp_timeout(boost::posix_time::seconds(1));

    try
    {
        association.receive_association(boost::asio::ip::tcp::v4(), 11113);

        odil::NCreateSCP NCreate_scp(association,
            [status](std::shared_ptr<odil::message::NCreateRequest const>)
            {
                status->called = true;
                return odil::message::Response::Success;
            });

        // Get NCreate message
        auto const message = association.receive_message();
        NCreate_scp(message);
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
    catch(odil::Exception const &)
    {
        status->server = "Other Odil exception";
    }
    catch(...)
    {
        status->server = "Other exception";
    }
}

// void run_client(Status * status, bool use_abort)
// {
//     std::string command = "NCreatescu -ll error";
//     if(use_abort)
//     {
//         command += " --abort";
//     }
//     command += " 127.0.0.1 11113";
//     status->client = system(command.c_str());
// }

BOOST_AUTO_TEST_CASE(Callback)
{
    odil::Association association;
    odil::NCreateSCP scp(association);

    bool called = false;
    auto const callback =
        [&called](std::shared_ptr<odil::message::NCreateRequest const>)
        {
            called = true;
            return odil::message::Response::Success;
        };

    scp.set_callback(callback);
    auto data_set = std::make_shared<odil::DataSet>();
    data_set->add("PatientName", {"Doe^John"});
    scp.get_callback()(
        std::make_shared<odil::message::NCreateRequest>(1, "", data_set));
    BOOST_REQUIRE_EQUAL(called, true);
}
