#define BOOST_TEST_MODULE GetSCP
#include <boost/test/unit_test.hpp>

#include <chrono>
#include <cstdlib>
#include <memory>
#include <thread>
#include <vector>

#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/DataSet.h"
#include "dcmtkpp/GetSCP.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/SCP.h"
#include "dcmtkpp/uid.h"
#include "dcmtkpp/Reader.h"
#include "dcmtkpp/message/Response.h"

struct Status
{
    int client;
    std::string server;
    std::vector<dcmtkpp::DataSet> responses;
};

class Generator: public dcmtkpp::GetSCP::DataSetGenerator
{
public:
    Generator()
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
        data_set_1.add("SOPClassUID", {dcmtkpp::registry::RawDataStorage});
        data_set_1.add(
            "SOPInstanceUID",
            {"1.2.826.0.1.3680043.9.5560.3127449359877365688774406533090568532"});
        data_set_1.add("PatientName", {"Hello^World"});
        data_set_1.add("PatientID", {"1234"});
        this->_responses.push_back(data_set_1);

        dcmtkpp::DataSet data_set_2;
        data_set_2.add("SOPClassUID", {dcmtkpp::registry::RawDataStorage});
        data_set_2.add(
            "SOPInstanceUID",
            {"1.2.826.0.1.3680043.9.5560.3221615743193123463515381981101110692"});
        data_set_2.add("PatientName", {"Doe^John"});
        data_set_2.add("PatientID", {"5678"});
        this->_responses.push_back(data_set_2);

        this->_response_iterator = this->_responses.begin();
    }

    virtual bool done() const
    {
        return (this->_response_iterator == this->_responses.end());
    }

    virtual dcmtkpp::DataSet get() const
    {
        return *this->_response_iterator;
    }

    virtual void next()
    {
        ++this->_response_iterator;
    }

    virtual unsigned int count() const
    {
        return 2;
    }

private:
    std::vector<dcmtkpp::DataSet> _responses;
    std::vector<dcmtkpp::DataSet>::const_iterator _response_iterator;
};

void run_server(Status * status)
{
    dcmtkpp::Association association;
    association.set_tcp_timeout(boost::posix_time::seconds(1));

    try
    {
        association.receive_association(boost::asio::ip::tcp::v4(), 11113);

        dcmtkpp::GetSCP get_scp(association);
        auto const generator = std::make_shared<Generator>();
        get_scp.set_generator(generator);

        // Get echo message
        auto const message = association.receive_message();
        get_scp(message);
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
    std::string command = "getscu "
        "-P -k QueryRetrieveLevel=PATIENT "
        "-k PatientID=* -k PatientName "
        "+B "
        "127.0.0.1 11113";
    status->client = system(command.c_str());

    boost::filesystem::directory_iterator end;
    for(boost::filesystem::directory_iterator it("."); it != end; ++it )
    {
        if(!boost::filesystem::is_regular_file(it->status()))
        {
            continue;
        }
        auto const filename = it->path().stem().string();
        if(filename.substr(0, dcmtkpp::uid_prefix.size()) != dcmtkpp::uid_prefix)
        {
            continue;
        }

        std::ifstream stream(it->path().string());
        auto const data_set = dcmtkpp::Reader::read_file(stream).second;
        status->responses.push_back(data_set);

        boost::filesystem::remove(it->path());
    }
}

BOOST_AUTO_TEST_CASE(Release)
{
    Status status = { -1, "", {} };

    std::thread server(run_server, &status);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::thread client(run_client, &status);

    server.join();
    client.join();

    BOOST_REQUIRE_EQUAL(status.client, 0);
    BOOST_REQUIRE_EQUAL(status.server, "release");
    BOOST_REQUIRE_EQUAL(status.responses.size(), 2);

    BOOST_REQUIRE_EQUAL(status.responses[0].size(), 4);
    BOOST_REQUIRE_EQUAL(
        status.responses[0].as_string("SOPInstanceUID", 0),
        "1.2.826.0.1.3680043.9.5560.3127449359877365688774406533090568532");
    BOOST_REQUIRE_EQUAL(
        status.responses[0].as_string("SOPClassUID", 0),
        dcmtkpp::registry::RawDataStorage);
    BOOST_REQUIRE_EQUAL(status.responses[0].as_string("PatientName", 0), "Hello^World");
    BOOST_REQUIRE_EQUAL(status.responses[0].as_string("PatientID", 0), "1234");

    BOOST_REQUIRE_EQUAL(status.responses[1].size(), 4);
    BOOST_REQUIRE_EQUAL(
        status.responses[1].as_string("SOPInstanceUID", 0),
        "1.2.826.0.1.3680043.9.5560.3221615743193123463515381981101110692");
    BOOST_REQUIRE_EQUAL(
        status.responses[1].as_string("SOPClassUID", 0),
        dcmtkpp::registry::RawDataStorage);
    BOOST_REQUIRE_EQUAL(status.responses[1].as_string("PatientName", 0), "Doe^John");
    BOOST_REQUIRE_EQUAL(status.responses[1].as_string("PatientID", 0), "5678");
}
