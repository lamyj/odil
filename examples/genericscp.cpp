#include <boost/asio.hpp>

#include "odil/Association.h"
#include "odil/DataSet.h"
#include "odil/EchoSCP.h"
#include "odil/FindSCP.h"
#include "odil/StoreSCP.h"
#include "odil/registry.h"
#include "odil/SCPDispatcher.h"
#include "odil/SCP.h"

#include "odil/message/CEchoRequest.h"
#include "odil/message/CFindRequest.h"
#include "odil/message/CFindResponse.h"
#include "odil/message/CStoreRequest.h"

class FindGenerator: public odil::SCP::DataSetGenerator
{
public:
    FindGenerator()
    {
        // Nothing to do
    }

    virtual ~FindGenerator()
    {
        // Nothing to do.
    }

    virtual void initialize(odil::message::Request const & )
    {
        odil::DataSet data_set_1;
        data_set_1.add(odil::registry::PatientName, {"Hello^World"});
        data_set_1.add(odil::registry::PatientID, {"1234"});
        this->_responses.push_back(data_set_1);

        odil::DataSet data_set_2;
        data_set_2.add(odil::registry::PatientName, {"Doe^John"});
        data_set_2.add(odil::registry::PatientID, {"5678"});
        this->_responses.push_back(data_set_2);

        this->_response_iterator = this->_responses.begin();
    }

    virtual bool done() const
    {
        return (this->_response_iterator == this->_responses.end());
    }

    virtual odil::DataSet get() const
    {
        return *this->_response_iterator;
    }

    virtual void next()
    {
        ++this->_response_iterator;
    }


private:
    std::vector<odil::DataSet> _responses;
    std::vector<odil::DataSet>::const_iterator _response_iterator;
};

odil::Value::Integer echo(odil::message::CEchoRequest const & request)
{
    std::cout << "Received echo\n";
    std::cout << "  ID: " << request.get_message_id() << "\n";
    std::cout << "  Affected SOP Class UID: " << request.get_affected_sop_class_uid() << "\n";
    return odil::message::Response::Success;
}

odil::Value::Integer store(odil::message::CStoreRequest const & request)
{
    auto const patient_name =
        request.get_data_set().as_string(odil::registry::PatientName)[0];
    std::cout << "Storing " << patient_name << "\n";
    return odil::message::Response::Success;
}

int main()
{
    odil::Association association;
    association.receive_association(boost::asio::ip::tcp::v4(), 11112);

    std::cout
        << "Received association from "
        << association.get_peer_host() << ":" << association.get_peer_port()
        << "\n";

    auto const & contexts =
        association.get_negotiated_parameters().get_presentation_contexts();
    std::cout << "Presentation contexts (" << contexts.size() << ")\n";
    for(auto const & context: contexts)
    {
        std::cout
            << "    "
            << odil::registry::uids_dictionary.at(context.abstract_syntax).name
            << ": "
            << odil::registry::uids_dictionary.at(context.transfer_syntaxes[0]).name
            << ", "
            << (context.scu_role_support?"SCU":"")
            << ((context.scu_role_support & context.scp_role_support)?"/":"")
            << (context.scp_role_support?"SCP":"")
            << std::endl;
    }

    auto echo_scp = std::make_shared<odil::EchoSCP>(association, echo);
    auto find_scp = std::make_shared<odil::FindSCP>(
        association, std::make_shared<FindGenerator>());
    auto store_scp = std::make_shared<odil::StoreSCP>(association, store);

    odil::SCPDispatcher dispatcher(association);
    dispatcher.set_scp(odil::message::Message::Command::C_ECHO_RQ, echo_scp);
    dispatcher.set_scp(odil::message::Message::Command::C_FIND_RQ, find_scp);
    dispatcher.set_scp(
        odil::message::Message::Command::C_STORE_RQ, store_scp);

    bool done = false;
    while(!done)
    {
        try
        {
            dispatcher.dispatch();
        }
        catch(odil::AssociationReleased const &)
        {
            std::cout << "Peer released association" << std::endl;
            done = true;
        }
        catch(odil::AssociationAborted const & e)
        {
            std::cout
                << "Peer aborted association, "
                << "source: " << int(e.source) << ", "
                << "reason: " << int(e.reason)
                << std::endl;
            done = true;
        }
    }
}
