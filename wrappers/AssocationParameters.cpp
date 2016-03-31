/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "odil/AssociationParameters.h"

namespace
{

std::shared_ptr<odil::AssociationParameters::PresentationContext>
presentation_context_constructor(
    uint8_t id, std::string const & abstract_syntax,
    boost::python::list const & transfer_syntaxes,
    bool scu_role_support, bool scp_role_support)
{
    std::vector<std::string> transfer_syntaxes_cpp(boost::python::len(transfer_syntaxes));
    for(int i = 0; i<boost::python::len(transfer_syntaxes); ++i)
    {
        transfer_syntaxes_cpp[i] = boost::python::extract<std::string>(transfer_syntaxes[i]);
    }
    odil::AssociationParameters::PresentationContext presentation_context = {
        id, abstract_syntax, transfer_syntaxes_cpp,
        scu_role_support, scp_role_support
    };
    return std::make_shared<odil::AssociationParameters::PresentationContext>(presentation_context);
}

boost::python::list
get_presentation_contexts(odil::AssociationParameters const & parameters)
{
    boost::python::list presentation_contexts_python;
    for(auto const & presentation_context: parameters.get_presentation_contexts())
    {
        presentation_contexts_python.append(presentation_context);
    }

    return presentation_contexts_python;
}

odil::AssociationParameters &
set_presentation_contexts(
    odil::AssociationParameters & parameters,
    boost::python::list const & presentation_contexts)
{
    std::vector<odil::AssociationParameters::PresentationContext> 
        presentation_contexts_cpp(boost::python::len(presentation_contexts));
    for(int i = 0; i<boost::python::len(presentation_contexts); ++i)
    {
        presentation_contexts_cpp[i] = 
            boost::python::extract<
                odil::AssociationParameters::PresentationContext
            >(presentation_contexts[i]);
    }
    parameters.set_presentation_contexts(presentation_contexts_cpp);
    
    return parameters;
}

}

void wrap_AssociationParameters()
{
    using namespace boost::python;
    using namespace odil;

    scope association_parameters_scope =
        class_<AssociationParameters>("AssociationParameters", init<>())
        // Construct from PDU
        .def(
            "get_called_ae_title",
            &AssociationParameters::get_called_ae_title,
            return_value_policy<copy_const_reference>()
        )
        .def(
            "set_called_ae_title",
            &AssociationParameters::set_called_ae_title,
            return_value_policy<reference_existing_object>()
        )
        .def(
            "get_calling_ae_title",
            &AssociationParameters::get_calling_ae_title,
            return_value_policy<copy_const_reference>()
        )
        .def(
            "set_calling_ae_title",
            &AssociationParameters::set_calling_ae_title,
            return_value_policy<reference_existing_object>()
        )
        .def(
            "get_presentation_contexts",
            &get_presentation_contexts
        )
        .def(
            "set_presentation_contexts",
            &set_presentation_contexts,
            return_value_policy<reference_existing_object>()
        )
        .def(
            "get_user_identity", &AssociationParameters::get_user_identity,
            return_value_policy<reference_existing_object>()
        )
        .def(
            "set_user_identity_to_none",
            &AssociationParameters::set_user_identity_to_none,
            return_value_policy<reference_existing_object>()
        )
        .def(
            "set_user_identity_to_username",
            &AssociationParameters::set_user_identity_to_username,
            return_value_policy<reference_existing_object>()
        )
        .def(
            "set_user_identity_to_username_and_password",
            &AssociationParameters::set_user_identity_to_username_and_password,
            return_value_policy<reference_existing_object>()
        )
        .def(
            "set_user_identity_to_kerberos",
            &AssociationParameters::set_user_identity_to_kerberos,
            return_value_policy<reference_existing_object>()
        )
        .def(
            "set_user_identity_to_saml",
            &AssociationParameters::set_user_identity_to_saml,
            return_value_policy<reference_existing_object>()
        )
        .def(
            "get_maximum_length",
            &AssociationParameters::get_maximum_length
        )
        .def(
            "set_maximum_length",
            &AssociationParameters::set_maximum_length,
            return_value_policy<reference_existing_object>()
        )
    ;

    {
        scope presentation_context_scope =
            class_<AssociationParameters::PresentationContext>("PresentationContext")
            .def(
                "__init__", 
                make_constructor(&presentation_context_constructor))
            .def_readwrite(
                "id",
                &AssociationParameters::PresentationContext::id
            )
            .def_readwrite(
                "abstract_syntax",
                &AssociationParameters::PresentationContext::abstract_syntax
            )
            .def_readwrite(
                "transfer_syntaxes",
                &AssociationParameters::PresentationContext::transfer_syntaxes
            )
            .def_readwrite(
                "scu_role_support",
                &AssociationParameters::PresentationContext::scu_role_support
            )
            .def_readwrite(
                "scp_role_support",
                &AssociationParameters::PresentationContext::scp_role_support
            )
            .def_readwrite(
                "result",
                &AssociationParameters::PresentationContext::result
            )
            .def(self == self)
        ;

        enum_<AssociationParameters::PresentationContext::Result>("Result")
            .value(
                "Acceptance", 
                AssociationParameters::PresentationContext::Result::Acceptance
            )
            .value(
                "UserRejection", 
                AssociationParameters::PresentationContext::Result::UserRejection
            )
            .value(
                "NoReason", 
                AssociationParameters::PresentationContext::Result::NoReason
            )
            .value(
                "AbstractSyntaxNotSupported", 
                AssociationParameters::PresentationContext::Result::AbstractSyntaxNotSupported
            )
            .value(
                "TransferSyntaxesNotSupported", 
                AssociationParameters::PresentationContext::Result::TransferSyntaxesNotSupported
            )
        ;
    }

    {
        scope user_identity_scope = 
            class_<AssociationParameters::UserIdentity>("UserIdentity")
            .def_readwrite(
                "type", 
                &AssociationParameters::UserIdentity::type
            )
            .def_readwrite(
                "primary_field", 
                &AssociationParameters::UserIdentity::primary_field
            )
            .def_readwrite(
                "secondary_field", 
                &AssociationParameters::UserIdentity::secondary_field
            )
            .def(self == self)
        ;

        enum_<AssociationParameters::UserIdentity::Type>("Type")
            .value("None", AssociationParameters::UserIdentity::Type::None)
            .value(
                "Username", AssociationParameters::UserIdentity::Type::Username
            )
            .value(
                "UsernameAndPassword", 
                AssociationParameters::UserIdentity::Type::UsernameAndPassword
            )
            .value(
                "Kerberos", AssociationParameters::UserIdentity::Type::Kerberos)
            .value("SAML", AssociationParameters::UserIdentity::Type::SAML)
        ;
    }
}
