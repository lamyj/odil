#ifndef _b21e8d37_0125_4d64_84aa_f91d9d96612b
#define _b21e8d37_0125_4d64_84aa_f91d9d96612b

#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

#include "dcmtkpp/Association.h"
#include "dcmtkpp/AssociationParameters.h"

/// @brief Base class for fixtures of requiring a working association.
class PeerFixtureBase
{
public:
    typedef
        dcmtkpp::AssociationParameters::PresentationContext PresentationContext;
    dcmtkpp::Association association;

    PeerFixtureBase(std::vector<PresentationContext> const & contexts)
    {
        this->association.set_peer_host(
            this->get_environment_variable("DCMTKPP_PEER_HOST_NAME"));
        this->association.set_peer_port(
            this->get_environment_variable<uint16_t>("DCMTKPP_PEER_PORT"));
        this->association.update_parameters()
            .set_calling_ae_title(
                this->get_environment_variable("DCMTKPP_OWN_AET"))
            .set_called_ae_title(
                this->get_environment_variable("DCMTKPP_PEER_AET"))
            .set_presentation_contexts(contexts);

        this->association.associate();
    }

    ~PeerFixtureBase()
    {
        this->association.release();
    }

    static std::string get_environment_variable(std::string const & name)
    {
        char* value = getenv(name.c_str());
        if(value == NULL)
        {
            BOOST_FAIL(name + " is not defined");
        }
        return value;
    }

    template<typename T>
    static T get_environment_variable(std::string const & name)
    {
        return boost::lexical_cast<T>(
            PeerFixtureBase::get_environment_variable(name));
    }
};

#endif // _b21e8d37_0125_4d64_84aa_f91d9d96612b
