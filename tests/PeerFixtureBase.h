#ifndef _b21e8d37_0125_4d64_84aa_f91d9d96612b
#define _b21e8d37_0125_4d64_84aa_f91d9d96612b

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>

#include <boost/lexical_cast.hpp>

#include "dcmtkpp/DcmtkAssociation.h"
#include "dcmtkpp/Network.h"

/// @brief Base class for fixtures of requiring a working association.
class PeerFixtureBase
{
public:
    dcmtkpp::Network network;
    dcmtkpp::DcmtkAssociation association;

    struct PresentationContext
    {
        std::string abstract_syntax;
        std::vector<std::string> transfer_syntaxes;
        T_ASC_SC_ROLE role;

        PresentationContext(std::string const & abstract_syntax, std::vector<std::string> const & transfer_syntaxes, T_ASC_SC_ROLE role=ASC_SC_ROLE_DEFAULT)
        : abstract_syntax(abstract_syntax),
          transfer_syntaxes(transfer_syntaxes), role(role)
        {
            // Nothing else
        }
    };

    PeerFixtureBase(T_ASC_NetworkRole role, int port, int timeout,
        std::vector<PresentationContext> const & presentation_contexts)
    : network(role, port, timeout), association()
    {
        this->network.initialize();

        this->association.set_own_ae_title(
            this->_get_environment_variable("DCMTKPP_OWN_AET"));
        this->association.set_peer_host_name(
            this->_get_environment_variable("DCMTKPP_PEER_HOST_NAME"));
        this->association.set_peer_port(
            this->_get_environment_variable<uint16_t>("DCMTKPP_PEER_PORT"));
        this->association.set_peer_ae_title(
            this->_get_environment_variable("DCMTKPP_PEER_AET"));

        std::vector<dcmtkpp::DcmtkAssociation::PresentationContext>
                pres_contexts;
        for(auto const & presentation_context: presentation_contexts)
        {
            pres_contexts.push_back(
                        dcmtkpp::DcmtkAssociation::PresentationContext(
                            presentation_context.abstract_syntax,
                            presentation_context.transfer_syntaxes,
                            presentation_context.role));
        }
        this->association.set_presentation_contexts(pres_contexts);

        this->association.associate(this->network);
    }

    ~PeerFixtureBase()
    {
        this->association.release();
        this->network.drop();
    }

private:

    std::string _get_environment_variable(std::string const & name) const
    {
        char* value = getenv(name.c_str());
        if(value == NULL)
        {
            BOOST_FAIL(name + " is not defined");
        }
        return value;
    }

    template<typename T>
    T _get_environment_variable(std::string const & name) const
    {
        return boost::lexical_cast<T>(this->_get_environment_variable(name));
    }
};

#endif // _b21e8d37_0125_4d64_84aa_f91d9d96612b
