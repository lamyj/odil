/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "odil/AssociationParameters.h"

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "odil/pdu/AAssociateAC.h"
#include "odil/pdu/AAssociateRQ.h"
#include "odil/Exception.h"
#include "odil/uid.h"
#include "odil/pdu/AsynchronousOperationsWindow.h"
#include "odil/pdu/ImplementationClassUID.h"
#include "odil/pdu/ImplementationVersionName.h"
#include "odil/pdu/PresentationContextAC.h"
#include "odil/pdu/PresentationContextRQ.h"
#include "odil/pdu/RoleSelection.h"
#include "odil/pdu/SOPClassExtendedNegotiation.h"
#include "odil/pdu/SOPClassCommonExtendedNegotiation.h"

namespace odil
{

AssociationParameters::PresentationContext
::PresentationContext(
    uint8_t id,
    std::string const & abstract_syntax,
    std::vector<std::string> const & transfer_syntaxes,
    bool scu_role_support, bool scp_role_support, Result result)
: id(id), abstract_syntax(abstract_syntax), transfer_syntaxes(transfer_syntaxes),
  scu_role_support(scu_role_support), scp_role_support(scp_role_support),
  result(result)
{
    // Nothing else.
}

bool 
AssociationParameters::PresentationContext
::operator==(PresentationContext const & other) const
{
    return (
        this->id == other.id && 
        this->abstract_syntax == other.abstract_syntax &&
        this->transfer_syntaxes == other.transfer_syntaxes &&
        this->scu_role_support == other.scu_role_support &&
        this->scp_role_support == other.scp_role_support &&
        this->result == other.result
    );
}

AssociationParameters::UserIdentity
::UserIdentity()
: type(UserIdentity::Type::None), primary_field(), secondary_field()
{
    // Nothing else.
}

AssociationParameters::UserIdentity
::UserIdentity(
    Type type, std::string const & primary_field,
    std::string const & secondary_field)
: type(type), primary_field(primary_field), secondary_field(secondary_field)
{
    // Nothing else.
}

bool 
AssociationParameters::UserIdentity
::operator==(UserIdentity const & other) const
{
    return (
        this->type == other.type &&
        (
            this->type == Type::None ||
            (
                this->type == Type::Username &&
                this->primary_field == other.primary_field
            ) ||
            (
                this->type == Type::UsernameAndPassword &&
                this->primary_field == other.primary_field &&
                this->secondary_field == other.secondary_field
            ) ||
            (
                this->type == Type::Kerberos &&
                this->primary_field == other.primary_field
            ) ||
            (
                this->type == Type::SAML &&
                this->primary_field == other.primary_field
            ) 
        )
    );
}

AssociationParameters
::AssociationParameters()
: _called_ae_title(""), _calling_ae_title(""), _presentation_contexts(),
  _user_identity({UserIdentity::Type::None, "", ""}), _maximum_length(16384),
  _maximum_number_operations_invoked(1), _maximum_number_operations_performed(1),
  _sop_class_extended_negotiation(), _sop_class_common_extended_negotiation()
{
    // Nothing else.
}

AssociationParameters
::AssociationParameters(pdu::AAssociateRQ const & pdu)
: _called_ae_title(""), _calling_ae_title(""), _presentation_contexts(),
  _user_identity({UserIdentity::Type::None, "", ""}), _maximum_length(16384),
  _maximum_number_operations_invoked(1), _maximum_number_operations_performed(1),
  _sop_class_extended_negotiation(), _sop_class_common_extended_negotiation()
{
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
        auto const it = roles_map.find(pc_pdu.get_abstract_syntax());
        pcs_parameters.emplace_back(
            pc_pdu.get_id(),
            pc_pdu.get_abstract_syntax(), pc_pdu.get_transfer_syntaxes(),
            (it!=roles_map.end())?it->second.first:true,
            (it!=roles_map.end())?it->second.second:false);
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

    // Maximum number of operations performed/invoked
    auto const asynchronous_operations_window =
        user_information.get_sub_items<pdu::AsynchronousOperationsWindow>();
    if(!asynchronous_operations_window.empty())
    {
        this->_maximum_number_operations_invoked =
            asynchronous_operations_window[0].get_maximum_number_operations_invoked();
        this->_maximum_number_operations_performed =
            asynchronous_operations_window[0].get_maximum_number_operations_performed();
    }
    
    this->_sop_class_common_extended_negotiation =
        user_information.get_sub_items<pdu::SOPClassCommonExtendedNegotiation>();
}

AssociationParameters
::AssociationParameters(
    pdu::AAssociateAC const & pdu, AssociationParameters const & request)
: _called_ae_title(""), _calling_ae_title(""), _presentation_contexts(),
  _user_identity({UserIdentity::Type::None, "", ""}), _maximum_length(16384),
  _maximum_number_operations_invoked(1), _maximum_number_operations_performed(1),
  _sop_class_extended_negotiation(), _sop_class_common_extended_negotiation()
{
    // Calling and Called AE titles are not meaningful in A-ASSOCIATE-AC
    this->set_called_ae_title(request.get_called_ae_title());
    this->set_calling_ae_title(request.get_calling_ae_title());

    auto const user_information = pdu.get_user_information();

    // Presentation contexts
    auto const & pcs_request = request.get_presentation_contexts();
    std::map<uint8_t, PresentationContext> pcs_request_map;
    for(auto const & pc: pcs_request)
    {
        pcs_request_map.insert({pc.id, pc});
    }

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
        auto const & pc_request = pcs_request_map.at(pc_pdu.get_id());
        auto const it = roles_map.find(pc_request.abstract_syntax);

        pcs_parameters.emplace_back(
            pc_pdu.get_id(),
            pc_request.abstract_syntax,
            std::vector<std::string>{ pc_pdu.get_transfer_syntax() },
            (it!=roles_map.end())?it->second.first:pc_request.scu_role_support,
            (it!=roles_map.end())?it->second.second:pc_request.scp_role_support,
            static_cast<PresentationContext::Result>(pc_pdu.get_result_reason()));
    }
    this->set_presentation_contexts(pcs_parameters);

    // User identity
    auto const user_identity =
        user_information.get_sub_items<pdu::UserIdentityAC>();
    if(!user_identity.empty())
    {
        auto const type = request.get_user_identity().type;
        if(type == UserIdentity::Type::Kerberos)
        {
            this->set_user_identity_to_kerberos(
                user_identity[0].get_server_response());
        }
        else if(type == UserIdentity::Type::SAML)
        {
            this->set_user_identity_to_saml(
                user_identity[0].get_server_response());
        }
    }

    // Maximum length
    auto const maximum_length =
        user_information.get_sub_items<pdu::MaximumLength>();
    if(!maximum_length.empty())
    {
        this->set_maximum_length(maximum_length[0].get_maximum_length());
    }

    // Maximum number of operations performed/invoked
    auto const asynchronous_operations_window =
        user_information.get_sub_items<pdu::AsynchronousOperationsWindow>();
    if(!asynchronous_operations_window.empty())
    {
        this->_maximum_number_operations_invoked =
            asynchronous_operations_window[0].get_maximum_number_operations_invoked();
        this->_maximum_number_operations_performed =
            asynchronous_operations_window[0].get_maximum_number_operations_performed();
    }
    
    // No SOPClassCommonExtendedNegotiation in AC
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

uint16_t
AssociationParameters
::get_maximum_number_operations_invoked() const
{
    return this->_maximum_number_operations_invoked;
}

AssociationParameters &
AssociationParameters
::set_maximum_number_operations_invoked(uint16_t value)
{
    this->_maximum_number_operations_invoked = value;
    return *this;
}

uint16_t
AssociationParameters
::get_maximum_number_operations_performed() const
{
    return this->_maximum_number_operations_performed;
}

AssociationParameters &
AssociationParameters
::set_maximum_number_operations_performed(uint16_t value)
{
    this->_maximum_number_operations_performed = value;
    return *this;
}

std::vector<pdu::SOPClassExtendedNegotiation>
AssociationParameters
::get_sop_class_extended_negotiation() const
{
    return this->_sop_class_extended_negotiation;
}

void
AssociationParameters
::set_sop_class_extended_negotiation(
    std::vector<pdu::SOPClassExtendedNegotiation> const & value)
{
    this->_sop_class_extended_negotiation = value;
}

std::vector<pdu::SOPClassCommonExtendedNegotiation>
AssociationParameters
::get_sop_class_common_extended_negotiation() const
{
    return this->_sop_class_common_extended_negotiation;
}

void 
AssociationParameters
::set_sop_class_common_extended_negotiation(
    std::vector<pdu::SOPClassCommonExtendedNegotiation> const & value)
{
    this->_sop_class_common_extended_negotiation = value;
}

pdu::AAssociateRQ
AssociationParameters
::as_a_associate_rq() const
{
    pdu::AAssociateRQ pdu;
    pdu.set_protocol_version(1);
    pdu.set_application_context(std::string("1.2.840.10008.3.1.1.1"));
    pdu.set_called_ae_title(this->get_called_ae_title());
    pdu.set_calling_ae_title(this->get_calling_ae_title());

    // Presentation contexts
    {
        auto const & source = this->get_presentation_contexts();

        std::vector<pdu::PresentationContextRQ> destination;
        destination.reserve(source.size());

        for(auto const & source_pc: source)
        {
            pdu::PresentationContextRQ const pc(
                source_pc.id, source_pc.abstract_syntax,
                source_pc.transfer_syntaxes);
            destination.push_back(pc);
        }

        pdu.set_presentation_contexts(destination);
    }

    pdu::UserInformation user_information;

    user_information.set_sub_items<pdu::MaximumLength>(
        {this->get_maximum_length()});

    user_information.set_sub_items<pdu::ImplementationClassUID>(
        {implementation_class_uid});

    if(this->_maximum_number_operations_invoked != 1 ||
        this->_maximum_number_operations_performed != 1)
    {
        user_information.set_sub_items<pdu::AsynchronousOperationsWindow>({{
            this->_maximum_number_operations_invoked,
            this->_maximum_number_operations_performed
        }});
    }

    user_information.set_sub_items<pdu::SOPClassExtendedNegotiation>(
        this->_sop_class_extended_negotiation);
    
    user_information.set_sub_items<pdu::SOPClassCommonExtendedNegotiation>(
        this->_sop_class_common_extended_negotiation);

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

pdu::AAssociateAC
AssociationParameters
::as_a_associate_ac() const
{
    pdu::AAssociateAC pdu;
    pdu.set_protocol_version(1);
    pdu.set_application_context(std::string("1.2.840.10008.3.1.1.1"));
    pdu.set_called_ae_title(this->get_called_ae_title());
    pdu.set_calling_ae_title(this->get_calling_ae_title());

    // Presentation contexts
    {
        auto const & source = this->get_presentation_contexts();

        std::vector<pdu::PresentationContextAC> destination;
        destination.reserve(source.size());

        for(auto const & source_pc: source)
        {
            pdu::PresentationContextAC const pc(
                source_pc.id, source_pc.transfer_syntaxes[0],
                static_cast<uint8_t>(source_pc.result));
            destination.push_back(pc);
        }

        pdu.set_presentation_contexts(destination);
    }

    pdu::UserInformation user_information;

    user_information.set_sub_items<pdu::MaximumLength>(
        {this->get_maximum_length()});

    user_information.set_sub_items<pdu::ImplementationClassUID>(
        {implementation_class_uid});

    if(this->_maximum_number_operations_invoked != 1 ||
        this->_maximum_number_operations_performed != 1)
    {
        user_information.set_sub_items<pdu::AsynchronousOperationsWindow>({{
            this->_maximum_number_operations_invoked,
            this->_maximum_number_operations_performed
        }});
    }
    
    user_information.set_sub_items<pdu::SOPClassExtendedNegotiation>(
        this->_sop_class_extended_negotiation);

    // No SOPClassCommonExtendedNegotiation in AC

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

    pdu.set_user_information(user_information);

    return pdu;
}

bool 
AssociationParameters
::operator==(AssociationParameters const & other) const
{
    return (
        this->get_called_ae_title() == other.get_called_ae_title() &&
        this->get_calling_ae_title() == other.get_calling_ae_title() &&
        this->get_presentation_contexts() == other.get_presentation_contexts() &&
        this->get_user_identity() == other.get_user_identity() &&
        this->get_maximum_length() == other.get_maximum_length() &&
        this->get_maximum_number_operations_invoked() ==
            other.get_maximum_number_operations_invoked() &&
        this->get_maximum_number_operations_performed() ==
            other.get_maximum_number_operations_performed() && 
        this->get_sop_class_extended_negotiation() ==
            other.get_sop_class_extended_negotiation() &&
        this->get_sop_class_common_extended_negotiation() ==
            other.get_sop_class_common_extended_negotiation()
    );
}

AssociationParameters &
AssociationParameters
::_set_user_identity(UserIdentity const & value)
{
    this->_user_identity = value;
    return *this;
}

}
