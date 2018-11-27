#include "ConnectionFixtureBase.h"

#include <cstdint>
#include <random>

#include <boost/asio.hpp>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/dimse.h>

std::random_device ConnectionFixtureBase::random_device{};

std::mt19937
ConnectionFixtureBase
::random_generator{ConnectionFixtureBase::random_device()};

std::uniform_int_distribution<uint16_t> 
ConnectionFixtureBase
::random_distribution{49152, 65535};

ConnectionFixtureBase
::ConnectionFixtureBase()
: service(), socket(service), 
    port(ConnectionFixtureBase::random_distribution(ConnectionFixtureBase::random_generator)), 
    endpoint(), acceptor(service)
{
    // Nothing else
}

void
ConnectionFixtureBase
::setup_odil_requestor()
{
    this->endpoint = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address_v4::from_string("127.0.0.1"), this->port);
}

void
ConnectionFixtureBase
::setup_odil_receiver()
{
    this->endpoint = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::tcp::v4(), this->port);
    this->acceptor = boost::asio::ip::tcp::acceptor(
        this->service, this->endpoint);
}

void
ConnectionFixtureBase
::dcmtk_acceptor(std::string const & action)
{
    OFCondition condition;

    T_ASC_Network * network;
    condition = ASC_initializeNetwork(NET_ACCEPTOR, this->port, 5, &network);
    if(!condition.good())
    {
        throw std::runtime_error("Could not initialize network");
    }

    T_ASC_Association * association;
    condition = ASC_receiveAssociation(network, &association, ASC_DEFAULTMAXPDU);
    if(!condition.good())
    {
        throw std::runtime_error(
            std::string("Could not receive association: ")+condition.text());
    }

    if(action == "accept")
    {
        T_ASC_PresentationContext context;
        ASC_getPresentationContext(association->params, 0, &context);
        
        ASC_acceptPresentationContext(
            association->params, 
            context.presentationContextID, context.proposedTransferSyntaxes[0]);
        ASC_acknowledgeAssociation(association);

        while(condition != DUL_PEERREQUESTEDRELEASE)
        {
            T_ASC_PresentationContextID context_id;
            T_DIMSE_Message message;
            DcmDataset * command_set;

            condition = DIMSE_receiveCommand(
                association, DIMSE_BLOCKING, 0, &context_id, &message, nullptr, 
                &command_set);
            if(condition.good())
            {
                this->dcmtk_messages.push_back(message);
                this->dcmtk_context_ids.push_back(context_id);

                DcmDataset * data_set=nullptr;
                Uint16 data_set_type;
                command_set->findAndGetUint16(
                    DCM_CommandDataSetType, data_set_type);
                if(data_set_type != DIMSE_DATASET_NULL)
                {
                    condition = DIMSE_receiveDataSetInMemory(
                        association, DIMSE_BLOCKING, 0, &context_id, &data_set, 
                        nullptr, nullptr);
                    this->dcmtk_data_sets.push_back(data_set);
                }
            }
        }

        condition = ASC_acknowledgeRelease(association);
    }
    else if(action == "reject")
    {
        T_ASC_RejectParameters rejection;
        rejection.result = ASC_RESULT_REJECTEDTRANSIENT;
        rejection.source = ASC_SOURCE_SERVICEUSER;
        rejection.reason = ASC_REASON_SU_CALLINGAETITLENOTRECOGNIZED;
        condition = ASC_rejectAssociation(association, &rejection);
    }
    else if(action == "abort")
    {
        condition = ASC_abortAssociation(association);
    }
    else
    {
        throw std::runtime_error("Unknown acceptor action: "+action);
    }

    if(!condition.good())
    {
        throw std::runtime_error(
            std::string("Error in handler: ")+condition.text());
    }

    ASC_dropNetwork(&network);
}

void 
ConnectionFixtureBase
::dcmtk_requestor(
    char const * abstract_syntax, char const * transfer_syntax, 
    bool requestor_abort,
    T_DIMSE_Message * message, DcmDataset * data_set)
{
    T_ASC_Network * network;
    ASC_initializeNetwork(NET_REQUESTOR, 0, 5, &network);

    T_ASC_Parameters * parameters;
    ASC_createAssociationParameters(&parameters, ASC_DEFAULTMAXPDU);
    ASC_setAPTitles(parameters, "calling", "called", nullptr);

    auto const peer_address = "localhost:"+std::to_string(this->port);
    ASC_setPresentationAddresses(parameters, "localhost", peer_address.c_str());

    // FIXME
    char const * transfer_syntaxes[] = { transfer_syntax };
    ASC_addPresentationContext(
        parameters, 1, abstract_syntax, transfer_syntaxes, 1);

    OFCondition condition;

    T_ASC_Association *association;
    condition = ASC_requestAssociation(network, parameters, &association);
    
    if(message != nullptr)
    {
        DIMSE_sendMessageUsingMemoryData(
            association, 1, message, nullptr, data_set, nullptr, nullptr);
    }

    if(!requestor_abort)
    {
        ASC_releaseAssociation(association);
    }
    else
    {
        ASC_abortAssociation(association);
    }

    ASC_destroyAssociation(&association);
    
    ASC_dropNetwork(&network);
}
