#define BOOST_TEST_MODULE FindSCP
#include <boost/test/unit_test.hpp>

#include <chrono>
#include <cstdlib>
#include <memory>
#include <thread>

#include <boost/asio.hpp>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/FindSCP.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/message/Response.h"
#include "dcmtkpp/SCP.h"

struct Status
{
    int client;
    std::string server;
    int called;
};

class Generator: public dcmtkpp::SCP::DataSetGenerator
{
public:
    Generator(Status * status)
    : _status(status)
    {
        // Nothing else.
    }

    virtual ~Generator()
    {
        // Nothing to do.
    }

    virtual void initialize(dcmtkpp::message::Request const & )
    {
        dcmtkpp::DataSet data_set_1;
        data_set_1.add(dcmtkpp::registry::PatientName, {"Hello^World"});
        data_set_1.add(dcmtkpp::registry::PatientID, {"1234"});
        this->_responses.push_back(data_set_1);

        dcmtkpp::DataSet data_set_2;
        data_set_2.add(dcmtkpp::registry::PatientName, {"Doe^John"});
        data_set_2.add(dcmtkpp::registry::PatientID, {"5678"});
        this->_responses.push_back(data_set_2);

        this->_response_iterator = this->_responses.begin();
    }

    virtual bool done() const
    {
        return (this->_response_iterator == this->_responses.end());
    }

    virtual dcmtkpp::DataSet get() const
    {
        ++this->_status->called;
        return *this->_response_iterator;
    }

    virtual void next()
    {
        ++this->_response_iterator;
    }


private:
    Status * _status;
    std::vector<dcmtkpp::DataSet> _responses;
    std::vector<dcmtkpp::DataSet>::const_iterator _response_iterator;
};

void run_server(Status * status)
{
    dcmtkpp::Association association;

    association.receive_association(boost::asio::ip::tcp::v4(), 11113);

    dcmtkpp::FindSCP find_scp(association);
    auto const generator = std::make_shared<Generator>(status);
    find_scp.set_generator(generator);

    try
    {
        // Get echo message
        auto const message = association.receive_message();
        find_scp(message);
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

void run_client(Status * status)
{
    std::string command = "findscu "
        "-P -k QueryRetrieveLevel=PATIENT "
        "-k PatientID=* -k PatientName "
        "127.0.0.1 11113";
    status->client = system(command.c_str());
}

BOOST_AUTO_TEST_CASE(Release)
{
    Status status = { -1, "", 0 };

    std::thread server(run_server, &status);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread client(run_client, &status);

    server.join();
    client.join();

    BOOST_REQUIRE_EQUAL(status.client, 0);
    BOOST_REQUIRE_EQUAL(status.server, "release");
    BOOST_REQUIRE_EQUAL(status.called, 2);
}
