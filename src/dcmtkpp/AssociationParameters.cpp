/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "dcmtkpp/AssociationParameters.h"

#include <cstdint>
#include <string>
#include <vector>

#include "dcmtkpp/Exception.h"

namespace dcmtkpp
{

AssociationParameters
::AssociationParameters()
: _called_ae_title(""), _calling_ae_title(""), _presentation_contexts(),
  _user_identity({UserIdentity::Type::None, "", ""}), _maximum_length(16384)
{
    // Nothing else.
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

AssociationParameters &
AssociationParameters
::_set_user_identity(UserIdentity const & value)
{
    this->_user_identity = value;
    return *this;
}

}
