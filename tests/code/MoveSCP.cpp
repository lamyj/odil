#define BOOST_TEST_MODULE MoveSCP
#include <boost/test/unit_test.hpp>

#include <chrono>
#include <cstdlib>
#include <memory>
#include <thread>
#include <vector>

#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

#include "odil/Association.h"
#include "odil/AssociationParameters.h"
#include "odil/DataSet.h"
#include "odil/MoveSCP.h"
#include "odil/Exception.h"
#include "odil/SCP.h"
#include "odil/uid.h"
#include "odil/Reader.h"
#include "odil/registry.h"
#include "odil/message/Response.h"

struct Status
{
    int client;
    std::string server;
    std::vector<odil::DataSet> responses;
};

class Generator: public odil::MoveSCP::DataSetGenerator
{
public:
    Generator(odil::Association & association)
    : _association(association)
    {
        // Nothing else.
    }

    virtual ~Generator()
    {
        // Nothing to do.
    }

    virtual void initialize(odil::message::Request const & )
    {
        odil::DataSet data_set_1;
        data_set_1.add("SOPClassUID", {odil::registry::RawDataStorage});
        data_set_1.add(
            "SOPInstanceUID",
            {"1.2.826.0.1.3680043.9.5560.3127449359877365688774406533090568532"});
        data_set_1.add("PatientName", {"Hello^World"});
        data_set_1.add("PatientID", {"1234"});
        this->_responses.push_back(std::move(data_set_1));

        odil::DataSet data_set_2;
        data_set_2.add("SOPClassUID", {odil::registry::RawDataStorage});
        data_set_2.add(
            "SOPInstanceUID",
            {"1.2.826.0.1.3680043.9.5560.3221615743193123463515381981101110692"});
        data_set_2.add("PatientName", {"Doe^John"});
        data_set_2.add("PatientID", {"5678"});
        this->_responses.push_back(std::move(data_set_2));

        this->_response_iterator = this->_responses.begin();
    }

    virtual bool done() const
    {
        return (this->_response_iterator == this->_responses.end());
    }

    virtual odil::DataSet get() const
    {
        return *std::make_move_iterator(this->_response_iterator);
    }

    virtual void next()
    {
        ++this->_response_iterator;
    }

    virtual unsigned int count() const
    {
        return 2;
    }

    virtual odil::Association get_association(
        odil::message::CMoveRequest const & request) const
    {
        odil::Association move_association;
        move_association.set_peer_host(this->_association.get_peer_host());
        move_association.set_peer_port(11114);

        // FIXME: max length, user_identity
        std::vector<odil::AssociationParameters::PresentationContext>
            presentation_contexts;
        for(auto const & uid: odil::registry::uids_dictionary)
        {
            auto const & name = uid.second.name;
            if(name.substr(name.size()-7, std::string::npos) == "Storage")
            {
                odil::AssociationParameters::PresentationContext
                    presentation_context = {
                        uid.first,
                        { odil::registry::ImplicitVRLittleEndian },
                        true, false
                };
                presentation_contexts.push_back(presentation_context);
            }
        }
        move_association.update_parameters()
            .set_calling_ae_title(
                this->_association.get_negotiated_parameters().get_called_ae_title())
            .set_called_ae_title(request.get_move_destination())
            .set_presentation_contexts(presentation_contexts);

        return move_association;
    }

private:
    mutable std::vector<odil::DataSet> _responses;
    std::vector<odil::DataSet>::iterator _response_iterator;
    odil::Association & _association;
};

void run_server(Status * status)
{
    odil::Association association;
    association.set_tcp_timeout(boost::posix_time::seconds(1));

    try
    {
        association.receive_association(boost::asio::ip::tcp::v4(), 11113);

        odil::MoveSCP move_scp(association);
        auto const generator = std::make_shared<Generator>(association);
        move_scp.set_generator(generator);

        // Get move message
        auto message = association.receive_message();
        move_scp(std::move(message));
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

void run_client(Status * status)
{
    std::string command = "movescu "
        "-ll error "
        "-P -k QueryRetrieveLevel=PATIENT "
        "-k PatientID=* -k PatientName "
        "+P 11114 127.0.0.1 11113";
    status->client = system(command.c_str());

    boost::filesystem::directory_iterator end;
    for(boost::filesystem::directory_iterator it("."); it != end; ++it )
    {
        if(!boost::filesystem::is_regular_file(it->status()))
        {
            continue;
        }
        auto const filename = it->path().stem().string();
        if(filename.substr(0, 3) != "RAW")
        {
            continue;
        }

        std::ifstream stream(it->path().string());
        auto data_set = odil::Reader::read_file(stream).second;
        status->responses.push_back(std::move(data_set));

        boost::filesystem::remove(it->path());
    }

    std::sort(
        status->responses.begin(), status->responses.end(),
        [](odil::DataSet const & left, odil::DataSet const & right)
        {
            auto const & left_uid = left.as_string("SOPInstanceUID", 0);
            auto const & right_uid = right.as_string("SOPInstanceUID", 0);
            return (left_uid < right_uid);
        });
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
        odil::registry::RawDataStorage);
    BOOST_REQUIRE_EQUAL(status.responses[0].as_string("PatientName", 0), "Hello^World");
    BOOST_REQUIRE_EQUAL(status.responses[0].as_string("PatientID", 0), "1234");

    BOOST_REQUIRE_EQUAL(status.responses[1].size(), 4);
    BOOST_REQUIRE_EQUAL(
        status.responses[1].as_string("SOPInstanceUID", 0),
        "1.2.826.0.1.3680043.9.5560.3221615743193123463515381981101110692");
    BOOST_REQUIRE_EQUAL(
        status.responses[1].as_string("SOPClassUID", 0),
        odil::registry::RawDataStorage);
    BOOST_REQUIRE_EQUAL(status.responses[1].as_string("PatientName", 0), "Doe^John");
    BOOST_REQUIRE_EQUAL(status.responses[1].as_string("PatientID", 0), "5678");
}
