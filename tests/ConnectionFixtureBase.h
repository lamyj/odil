#ifndef _239878f0_b6c8_4e03_af83_8e8b61525368
#define _239878f0_b6c8_4e03_af83_8e8b61525368

#include <cstdint>
#include <random>

#include <boost/asio.hpp>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/dimse.h>

struct DCMTKStatus
{
    OFCondition connection_end = DUL_PEERABORTEDASSOCIATION;
};

struct ConnectionFixtureBase
{
    static std::random_device random_device;
    static std::mt19937 random_generator;
    static std::uniform_int_distribution<uint16_t> random_distribution;

    boost::asio::io_service service;
    boost::asio::ip::tcp::socket socket;
    uint16_t port;
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::ip::tcp::acceptor acceptor;

    std::vector<T_DIMSE_Message> dcmtk_messages;
    std::vector<T_ASC_PresentationContextID> dcmtk_context_ids;
    std::vector<DcmDataset*> dcmtk_data_sets;

    ConnectionFixtureBase();

    void setup_odil_requestor();
    void setup_odil_receiver();

    void dcmtk_acceptor(std::string const & action);
    void dcmtk_requestor(
        char const * abstract_syntax, char const * transfer_syntax, 
        bool requestor_abort, T_DIMSE_Message * message=nullptr, 
        DcmDataset * data_set=nullptr);
};

#endif // _239878f0_b6c8_4e03_af83_8e8b61525368
