/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/AssociationParameters.h"

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "dcmtkpp/pdu/AAssociate.h"
#include "dcmtkpp/Exception.h"
#include "dcmtkpp/uid.h"
#include "dcmtkpp/pdu/ImplementationClassUID.h"
#include "dcmtkpp/pdu/ImplementationVersionName.h"
#include "dcmtkpp/pdu/RoleSelection.h"

namespace dcmtkpp
{

AssociationParameters
::AssociationParameters()
: _called_ae_title(""), _calling_ae_title(""), _presentation_contexts(),
  _user_identity({UserIdentity::Type::None, "", ""}), _maximum_length(16384)
{
    // Nothing else.
}

AssociationParameters
::AssociationParameters(pdu::AAssociate const & pdu)
{
    if(pdu.get_type() != pdu::AAssociate::Type::RQ)
    {
        throw Exception("Expected an A-ASSOCIATE-RQ PDU");
    }
    AssociationParameters parameters;
    this->set_called_ae_title(pdu.get_called_ae_title());
    this->set_calling_ae_title(pdu.get_calling_ae_title());

    auto const user_information = pdu.get_user_information();

    // Presentation contexts
    auto const & pcs_pdu = pdu.get_presentation_contexts();

    std::map<std::string, std::pair<bool, bool>> roles_map;
    auto const roles = user_information.get_sub_items<pdu::RoleSelection>();
    for(auto const & role: roles)
    {
        roles_map[role.get_sop_class_uid()] =
            std::make_pair(
                role.get_scu_role_support(),
                role.get_scp_role_support());
    }

    std::vector<AssociationParameters::PresentationContext> pcs_parameters;
    pcs_parameters.reserve(pcs_pdu.size());
    for(auto const & pc_pdu: pcs_pdu)
    {
        AssociationParameters::PresentationContext pc_parameters;
        pc_parameters.abstract_syntax = pc_pdu.get_abstract_syntax();
        pc_parameters.transfer_syntaxes = pc_pdu.get_transfer_syntaxes();

        auto const it = roles_map.find(pc_pdu.get_abstract_syntax());
        pc_parameters.scu_role_support =
            (it!=roles_map.end())?it->second.first:true;
        pc_parameters.scp_role_support =
            (it!=roles_map.end())?it->second.second:false;

        pcs_parameters.push_back(pc_parameters);
    }
    this->set_presentation_contexts(pcs_parameters);

    // User identity
    auto const user_identity =
        user_information.get_sub_items<pdu::UserIdentityRQ>();
    if(!user_identity.empty())
    {
        if(user_identity[0].get_type() == 1)
        {
            this->set_user_identity_to_username(
                user_identity[0].get_primary_field());
        }
        else if(user_identity[0].get_type() == 2)
        {
            this->set_user_identity_to_username_and_password(
                user_identity[0].get_primary_field(),
                user_identity[0].get_secondary_field());
        }
        else if(user_identity[0].get_type() == 3)
        {
            this->set_user_identity_to_kerberos(
                user_identity[0].get_primary_field());
        }
        else if(user_identity[0].get_type() == 4)
        {
            this->set_user_identity_to_saml(
                user_identity[0].get_primary_field());
        }
    }

    // Maximum length
    auto const maximum_length =
        user_information.get_sub_items<pdu::MaximumLength>();
    if(!maximum_length.empty())
    {
        this->set_maximum_length(maximum_length[0].get_maximum_length());
    }
}

std::string const &
AssociationParameters
::get_called_ae_title() const
{
    return this->_called_ae_title;
}

AssociationParameters &
AssociationParameters
::set_called_ae_title(std::string const & value)
{
    if(value.size() > 16)
    {
        throw Exception("AE Title must be less than 16 characters");
    }

    this->_called_ae_title = value;
    return *this;
}

std::string const &
AssociationParameters
::get_calling_ae_title() const
{
    return this->_calling_ae_title;
}

AssociationParameters &
AssociationParameters
::set_calling_ae_title(std::string const & value)
{
    if(value.size() > 16)
    {
        throw Exception("AE Title must be less than 16 characters");
    }

    this->_calling_ae_title = value;
    return *this;
}

std::vector<AssociationParameters::PresentationContext> const &
AssociationParameters
::get_presentation_contexts() const
{
    return this->_presentation_contexts;
}

AssociationParameters &
AssociationParameters
::set_presentation_contexts(std::vector<PresentationContext> const & value)
{
    std::set<uint8_t> ids;
    for(auto const context: value)
    {
        auto const id = context.id;
        if(id%2 == 0)
        {
            throw Exception("Presentation Context ID must be odd");
        }
        ids.insert(id);
    }
    if(ids.size() != value.size())
    {
        throw Exception("All Presentation Context IDs must be unique");
    }

    this->_presentation_contexts = value;
    return *this;
}

AssociationParameters::UserIdentity const &
AssociationParameters
::get_user_identity() const
{
    return this->_user_identity;
}

AssociationParameters &
AssociationParameters
::set_user_identity_to_none()
{
    return this->_set_user_identity({UserIdentity::Type::None, "", ""});
}

AssociationParameters &
AssociationParameters
::set_user_identity_to_username(std::string const & username)
{
    return this->_set_user_identity(
        {UserIdentity::Type::Username, username, ""});
}

AssociationParameters &
AssociationParameters
::set_user_identity_to_username_and_password(
    std::string const & username, std::string const & password)
{
    return this->_set_user_identity(
        {UserIdentity::Type::UsernameAndPassword, username, password});
}

AssociationParameters &
AssociationParameters
::set_user_identity_to_kerberos(std::string const & ticket)
{
    return this->_set_user_identity({UserIdentity::Type::Kerberos, ticket, ""});
}

AssociationParameters &
AssociationParameters
::set_user_identity_to_saml(std::string const & assertion)
{
    return this->_set_user_identity({UserIdentity::Type::SAML, assertion, ""});
}

uint32_t
AssociationParameters
::get_maximum_length() const
{
    return this->_maximum_length;
}

AssociationParameters &
AssociationParameters
::set_maximum_length(uint32_t value)
{
    this->_maximum_length = value;
    return *this;
}

pdu::AAssociate
AssociationParameters
::as_pdu(pdu::AAssociate::Type type) const

{
    pdu::AAssociate pdu(type);
    pdu.set_protocol_version(1);
    pdu.set_application_context(std::string("1.2.840.10008.3.1.1.1"));
    pdu.set_called_ae_title(this->get_called_ae_title());
    pdu.set_calling_ae_title(this->get_calling_ae_title());

    // Presentation contexts
    {
        auto const & source = this->get_presentation_contexts();

        std::vector<pdu::PresentationContext> destination;
        destination.reserve(source.size());

        for(unsigned int i=0; i<source.size(); ++i)
        {
            pdu::PresentationContext pc(
                2*i+1, source[i].abstract_syntax, source[i].transfer_syntaxes);

            destination.push_back(pc);
        }

        pdu.set_presentation_contexts(destination);
    }

    pdu::UserInformation user_information;

    user_information.set_sub_items<pdu::MaximumLength>(
        {this->get_maximum_length()});

    user_information.set_sub_items<pdu::ImplementationClassUID>(
        {implementation_class_uid});
    user_information.set_sub_items<pdu::ImplementationVersionName>(
        {implementation_version_name});

    std::vector<pdu::RoleSelection> roles;
    for(auto const & presentation_context: this->get_presentation_contexts())
    {
        pdu::RoleSelection const role(
            presentation_context.abstract_syntax,
            presentation_context.scu_role_support,
            presentation_context.scp_role_support);
        roles.push_back(role);
    }
    user_information.set_sub_items(roles);

    auto const & user_identity = this->get_user_identity();
    if(user_identity.type != AssociationParameters::UserIdentity::Type::None)
    {
        pdu::UserIdentityRQ sub_item;
        sub_item.set_type(static_cast<int>(user_identity.type));
        sub_item.set_primary_field(user_identity.primary_field);
        sub_item.set_secondary_field(user_identity.secondary_field);

        // TODO
        sub_item.set_positive_response_requested(true);

        user_information.set_sub_items<pdu::UserIdentityRQ>({sub_item});
    }

    pdu.set_user_information(user_information);

    return pdu;
}

AssociationParameters &
AssociationParameters
::_set_user_identity(UserIdentity const & value)
{
    this->_user_identity = value;
    return *this;
}

}
