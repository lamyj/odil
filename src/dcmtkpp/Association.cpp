/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Association.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmnet/assoc.h>
#include <dcmtk/dcmnet/cond.h>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

Association
::Association()
: _own_ae_title(""),
  _peer_host_name(""), _peer_port(104), _peer_ae_title(""),
  _user_identity_type(UserIdentityType::None),
  _user_identity_primary_field(""), _user_identity_secondary_field(""),
  _association(NULL)
{
    // Nothing else
}

Association
::Association(Association const & other)
: _own_ae_title(other.get_own_ae_title()),
  _peer_host_name(other.get_peer_host_name()), _peer_port(other.get_peer_port()),
  _peer_ae_title(other.get_peer_ae_title()),
  _user_identity_type(other.get_user_identity_type()),
  _user_identity_primary_field(other.get_user_identity_primary_field()),
  _user_identity_secondary_field(other.get_user_identity_secondary_field()),
  _association(NULL)
{
}

Association
::~Association()
{
    if(this->is_associated())
    {
        this->release();
    }
}

Association &
Association
::operator=(Association const & other)
{
    if(this != &other)
    {
        this->set_own_ae_title(other.get_own_ae_title());
        this->set_peer_host_name(other.get_peer_host_name());
        this->set_peer_port(other.get_peer_port());
        this->set_peer_ae_title(other.get_peer_ae_title());
        this->set_user_identity_type(other.get_user_identity_type());
        this->set_user_identity_primary_field(other.get_user_identity_primary_field());
        this->set_user_identity_secondary_field(other.get_user_identity_secondary_field());
    }

    return *this;
}

std::string const &
Association
::get_own_ae_title() const
{
    return this->_own_ae_title;
}

void
Association
::set_own_ae_title(std::string const & ae_title)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_own_ae_title = ae_title;
}

std::string const &
Association
::get_peer_host_name() const
{
    return this->_peer_host_name;
}

void
Association
::set_peer_host_name(std::string const & host_name)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_peer_host_name = host_name;
}

uint16_t
Association
::get_peer_port() const
{
    return this->_peer_port;
}

void
Association
::set_peer_port(uint16_t port)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_peer_port = port;
}

std::string const &
Association
::get_peer_ae_title() const
{
    return this->_peer_ae_title;
}

void
Association
::set_peer_ae_title(std::string const & ae_title)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_peer_ae_title = ae_title;
}

void
Association
::add_presentation_context(std::string const & abstract_syntax,
    std::vector<std::string> const & transfer_syntaxes, T_ASC_SC_ROLE role)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_presentation_contexts.push_back(
        {abstract_syntax, transfer_syntaxes, role});
}

UserIdentityType
Association
::get_user_identity_type() const
{
    return this->_user_identity_type;
}

void
Association
::set_user_identity_type(UserIdentityType type)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_user_identity_type = type;
}

std::string const &
Association
::get_user_identity_primary_field() const
{
    return this->_user_identity_primary_field;
}

void
Association
::set_user_identity_primary_field(std::string const & value)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_user_identity_primary_field = value;
}

std::string const &
Association
::get_user_identity_secondary_field() const
{
    return this->_user_identity_secondary_field;
}

void
Association
::set_user_identity_secondary_field(std::string const & value)
{
    if(this->is_associated())
    {
        throw Exception("Cannot set member while associated");
    }

    this->_user_identity_secondary_field = value;
}

void
Association
::set_user_identity_to_none()
{
    this->set_user_identity_type(UserIdentityType::None);
    this->set_user_identity_primary_field("");
    this->set_user_identity_secondary_field("");
}

void
Association
::set_user_identity_to_username(std::string const & username)
{
    this->set_user_identity_type(UserIdentityType::Username);
    this->set_user_identity_primary_field(username);
    this->set_user_identity_secondary_field("");
}

void
Association
::set_user_identity_to_username_and_password(
    std::string const & username, std::string const & password)
{
    this->set_user_identity_type(UserIdentityType::UsernameAndPassword);
    this->set_user_identity_primary_field(username);
    this->set_user_identity_secondary_field(password);
}

void
Association
::set_user_identity_to_kerberos(std::string const & ticket)
{
    this->set_user_identity_type(UserIdentityType::Kerberos);
    this->set_user_identity_primary_field(ticket);
    this->set_user_identity_secondary_field("");
}

void
Association
::set_user_identity_to_saml(std::string const & assertion)
{
    this->set_user_identity_type(UserIdentityType::SAML);
    this->set_user_identity_primary_field(assertion);
    this->set_user_identity_secondary_field("");
}

bool
Association
::is_associated() const
{
    return (this->_association != NULL);
}

void
Association
::associate(Network & network)
{
    if(!network.is_initialized())
    {
        throw Exception("Network is not initialized");
    }

    if(this->is_associated())
    {
        throw Exception("Already associated");
    }

    OFCondition condition;

    T_ASC_Parameters * params;
    condition = ASC_createAssociationParameters(&params, ASC_MAXIMUMPDUSIZE);
    if(condition.bad())
    {
        throw Exception(condition);
    }

    condition = ASC_setAPTitles(params,
        this->_own_ae_title.c_str(), this->_peer_ae_title.c_str(), NULL);
    if(condition.bad())
    {
        ASC_destroyAssociationParameters(&params);
        throw Exception(condition);
    }

    std::string localhost(128, '\0');
    gethostname(&localhost[0], localhost.size()-1);

    std::ostringstream peer;
    peer << this->_peer_host_name << ":" << this->_peer_port;

    condition = ASC_setPresentationAddresses(params,
        "localhost", peer.str().c_str());
    if(condition.bad())
    {
        ASC_destroyAssociationParameters(&params);
        throw Exception(condition);
    }

    unsigned int context_id = 1;
    for(auto const & context: this->_presentation_contexts)
    {
        char const ** transfer_syntaxes = new char const *[context.transfer_syntaxes.size()];
        for(std::size_t i = 0; i < context.transfer_syntaxes.size(); ++i)
        {
            transfer_syntaxes[i] = context.transfer_syntaxes[i].c_str();
        }

        condition = ASC_addPresentationContext(params,
            context_id, context.abstract_syntax.c_str(),
            transfer_syntaxes, context.transfer_syntaxes.size(), context.role);
        if(condition.bad())
        {
            ASC_destroyAssociationParameters(&params);
            throw Exception(condition);
        }

        context_id += 2;
    }

    if(this->_user_identity_type == UserIdentityType::None)
    {
        // Nothing to do.
    }
    else if(this->_user_identity_type == UserIdentityType::Username)
    {
        condition = ASC_setIdentRQUserOnly(params,
            this->_user_identity_primary_field.c_str());
    }
    else if(this->_user_identity_type == UserIdentityType::UsernameAndPassword)
    {
        condition = ASC_setIdentRQUserOnly(params,
            this->_user_identity_primary_field.c_str(),
            this->_user_identity_secondary_field.c_str());
    }
    else if(this->_user_identity_type == UserIdentityType::Kerberos)
    {
        condition = ASC_setIdentRQKerberos(params,
            this->_user_identity_primary_field.c_str(),
            this->_user_identity_primary_field.size());
    }
    else if(this->_user_identity_type == UserIdentityType::SAML)
    {
        condition = ASC_setIdentRQSaml(params,
            this->_user_identity_primary_field.c_str(),
            this->_user_identity_primary_field.size());
    }
    else
    {
        ASC_destroyAssociationParameters(&params);
        throw Exception("Unknown identity type");
    }

    if(condition.bad())
    {
        ASC_destroyAssociationParameters(&params);
        throw Exception(condition);
    }

    condition = ASC_requestAssociation(
        network.get_network(), params, &this->_association);
    if(condition.bad())
    {
        OFString empty;

        if(condition == DUL_ASSOCIATIONREJECTED)
        {
            T_ASC_RejectParameters rej;
            ASC_getRejectParameters(params, &rej);

            ASC_destroyAssociationParameters(&params);
            throw Exception(ASC_printRejectParameters(empty, &rej).c_str());
        }
        else
        {
            ASC_destroyAssociationParameters(&params);
            throw Exception(DimseCondition::dump(empty, condition).c_str());
        }
    }
}

void
Association
::receive(Network & network, bool accept_all)
{
    this->receive(
        network, [](Association const &) { return true; }, {"*"}, accept_all);
}

void
Association
::receive(Network &network,
          std::function<bool (const Association &)> authenticator,
          std::vector<std::string> const & aetitles,
          bool accept_all)
{
    if(!network.is_initialized())
    {
        throw Exception("Network is not initialized");
    }

    if(this->is_associated())
    {
        throw Exception("Already associated");
    }

    OFCondition condition;

    condition = ASC_receiveAssociation(
        network.get_network(), &this->_association, ASC_DEFAULTMAXPDU);
    if(condition.bad())
    {
        throw Exception(condition);
    }

    T_ASC_Parameters * const params = this->_association->params;
    DUL_ASSOCIATESERVICEPARAMETERS const dul = params->DULparams;
    // No peer port should be defined when receiving
    this->_peer_host_name = dul.callingPresentationAddress;
    this->_peer_port = 0;
    this->_peer_ae_title = dul.callingAPTitle;

    // check Peer ae title
    // '*' => everybody allowed
    if (std::find(aetitles.begin(), aetitles.end(), "*") == aetitles.end() &&
        std::find(aetitles.begin(), aetitles.end(),
                  this->_peer_ae_title.c_str()) == aetitles.end())
    {
        this->reject(RejectedPermanent, ULServiceUser,
                     CallingAETitleNotRecognized);
        this->drop();
        throw Exception("Bad AE Title");
    }

    // Check Application Context Name
    char buf[BUFSIZ];
    condition = ASC_getApplicationContextName(params, buf);
    if (condition.bad() || std::string(buf) != DICOM_STDAPPLICATIONCONTEXT)
    {
        // reject: application context name not supported
        this->reject(RejectedPermanent, ULServiceUser,
                     ApplicationContextNameNotSupported);
        this->drop();
        throw Exception("Bad Application context name");
    }

    if(accept_all)
    {
        unsigned int const pc_count = ASC_countPresentationContexts(params);
        for(unsigned int pc_index=0; pc_index<pc_count; ++pc_index)
        {
            T_ASC_PresentationContext pc;
            memset(&pc, 0, sizeof(pc));
            ASC_getPresentationContext(params, pc_index, &pc);

            for(unsigned int ts_index=0; ts_index<pc.transferSyntaxCount; ++ts_index)
            {
                std::string const abstract_syntax = pc.abstractSyntax;
                char const * abstract_syntax_data = abstract_syntax.c_str();

                condition = ASC_acceptContextsWithTransferSyntax(
                    this->_association->params,
                    pc.proposedTransferSyntaxes[ts_index],
                    1, &abstract_syntax_data);
                if(condition.bad())
                {
                    this->reject(RejectedPermanent, ULServiceUser, NoReasonGiven);
                    this->drop();
                    throw Exception(condition);
                }
            }
        }
    }
    else
    {
        for(auto const & context: this->_presentation_contexts)
        {
            for(std::size_t i = 0; i < context.transfer_syntaxes.size(); ++i)
            {
                char const * abstract_syntax = context.abstract_syntax.c_str();
                char const * transfer_syntax = context.transfer_syntaxes[i].c_str();
                condition = ASC_acceptContextsWithTransferSyntax(
                    this->_association->params, transfer_syntax,
                    1, &abstract_syntax);
                if(condition.bad())
                {
                    this->reject(RejectedPermanent, ULServiceUser, NoReasonGiven);
                    this->drop();
                    throw Exception(condition);
                }
            }
        }
    }

    // Get user identity information
    UserIdentityNegotiationSubItemRQ* identity =
            this->_association->params->DULparams.reqUserIdentNeg;

    this->_user_identity_primary_field = "";
    this->_user_identity_secondary_field = "";
    if (identity == NULL ||
        identity->getIdentityType() == ASC_USER_IDENTITY_NONE)
    {
        this->_user_identity_type = UserIdentityType::None;
    }
    else if (identity->getIdentityType() != ASC_USER_IDENTITY_UNKNOWN)
    {
        this->_user_identity_type =
                    (UserIdentityType)identity->getIdentityType();

        // Get primary field
        char * primary_field;
        Uint16 primary_field_length;
        identity->getPrimField(primary_field, primary_field_length);
        // user is not NULL-terminated
        this->_user_identity_primary_field = std::string(primary_field,
                                                         primary_field_length);

        if (identity->getIdentityType() == ASC_USER_IDENTITY_USER_PASSWORD)
        {
            // Get secondary field
            char * secondary_field;
            Uint16 secondary_field_length;
            identity->getSecField(secondary_field, secondary_field_length);
            // password is not NULL-terminated
            this->_user_identity_primary_field =
                    std::string(secondary_field, secondary_field_length);
        }
    }
    else
    {
        throw Exception("Unknown user identity type");
    }

    // Authentication
    if(authenticator(*this))
    {
        condition = ASC_acknowledgeAssociation(this->_association);
        if(condition.bad())
        {
            throw Exception(condition);
        }
    }
    else
    {
        this->reject(RejectedPermanent, ULServiceUser, NoReasonGiven);
        this->drop();
        throw Exception("Bad Authentication");
    }
}

void
Association
::reject(Result result, ResultSource result_source, Diagnostic diagnostic)
{
    T_ASC_RejectParameters reject_parameters;
    reject_parameters.result = T_ASC_RejectParametersResult(result);
    reject_parameters.source = T_ASC_RejectParametersSource(result_source);
    reject_parameters.reason = T_ASC_RejectParametersReason(diagnostic);

    OFCondition const condition = ASC_rejectAssociation(
        this->_association, &reject_parameters);
    if(condition.bad())
    {
        throw Exception(condition);
    }
}

T_ASC_Association *
Association
::get_association()
{
    return this->_association;
}

void
Association
::release()
{
    if(!this->is_associated())
    {
        throw Exception("Not associated");
    }

    ASC_releaseAssociation(this->_association);
    ASC_destroyAssociation(&this->_association);
    this->_association = NULL;
}

void
Association
::abort()
{
    if(!this->is_associated())
    {
        throw Exception("Not associated");
    }

    ASC_abortAssociation(this->_association);
    ASC_destroyAssociation(&this->_association);
    this->_association = NULL;
}

void
Association
::drop()
{
    if(!this->is_associated())
    {
        throw Exception("Not associated");
    }

    ASC_acknowledgeRelease(this->_association);
    ASC_dropSCPAssociation(this->_association);
    ASC_destroyAssociation(&this->_association);
    this->_association = NULL;
}

}
