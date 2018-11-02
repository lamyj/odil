/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <algorithm>
#include <memory>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "odil/AssociationParameters.h"

namespace
{

odil::AssociationParameters::PresentationContext
presentation_context_constructor(
    uint8_t id, std::string const & abstract_syntax,
    pybind11::sequence transfer_syntaxes,
    bool scu_role_support, bool scp_role_support)
{

    std::vector<std::string> transfer_syntaxes_cpp(
        pybind11::len(transfer_syntaxes));
    std::transform(
        transfer_syntaxes.begin(), transfer_syntaxes.end(),
        transfer_syntaxes_cpp.begin(),
        [](pybind11::handle const & item) {
            return item.cast<std::string>();
        });
    return odil::AssociationParameters::PresentationContext(
        id, abstract_syntax, transfer_syntaxes_cpp,
        scu_role_support, scp_role_support);
}

odil::AssociationParameters::PresentationContext
presentation_context_simplified_constructor(
    std::string const & abstract_syntax,
    pybind11::sequence transfer_syntaxes,
    bool scu_role_support, bool scp_role_support)
{

    std::vector<std::string> transfer_syntaxes_cpp(len(transfer_syntaxes));
    std::transform(
        transfer_syntaxes.begin(), transfer_syntaxes.end(),
        transfer_syntaxes_cpp.begin(),
        [](pybind11::handle const & item) {
            return item.cast<std::string>();
        });
    return odil::AssociationParameters::PresentationContext(
        abstract_syntax, transfer_syntaxes_cpp,
        scu_role_support, scp_role_support);
}

pybind11::list
get_presentation_contexts(odil::AssociationParameters const & parameters)
{
    pybind11::list presentation_contexts_python;
    for(auto const & presentation_context: parameters.get_presentation_contexts())
    {
        presentation_contexts_python.append(presentation_context);
    }

    return presentation_contexts_python;
}

odil::AssociationParameters &
set_presentation_contexts(
    odil::AssociationParameters & parameters,
    pybind11::sequence const & presentation_contexts)
{
    std::vector<odil::AssociationParameters::PresentationContext> 
        presentation_contexts_cpp;
    presentation_contexts_cpp.reserve(pybind11::len(presentation_contexts));
    for(pybind11::handle const & item: presentation_contexts)
    {
        presentation_contexts_cpp.push_back(
            item.cast<odil::AssociationParameters::PresentationContext>());
    }
    parameters.set_presentation_contexts(presentation_contexts_cpp);
    
    return parameters;
}

}

void wrap_AssociationParameters(pybind11::module & m)
{
    using namespace pybind11;
    using namespace pybind11::literals;
    using namespace odil;

    auto association_parameters_scope =
        class_<AssociationParameters>(m, "AssociationParameters")
        .def(init<>())
        // TODO Construct from PDU
        .def(
            "get_called_ae_title",
            &AssociationParameters::get_called_ae_title,
            return_value_policy::copy)
        .def(
            "set_called_ae_title",
            &AssociationParameters::set_called_ae_title,
            return_value_policy::copy)
        .def(
            "get_calling_ae_title",
            &AssociationParameters::get_calling_ae_title,
            return_value_policy::copy)
        .def(
            "set_calling_ae_title",
            &AssociationParameters::set_calling_ae_title,
            return_value_policy::reference_internal)
        .def("get_presentation_contexts", &get_presentation_contexts)
        .def(
            "set_presentation_contexts", &set_presentation_contexts,
            return_value_policy::reference_internal)
        .def(
            "get_user_identity", &AssociationParameters::get_user_identity,
            return_value_policy::reference_internal)
        .def(
            "set_user_identity_to_none",
            &AssociationParameters::set_user_identity_to_none,
            return_value_policy::reference_internal)
        .def(
            "set_user_identity_to_username",
            &AssociationParameters::set_user_identity_to_username,
            return_value_policy::reference_internal)
        .def(
            "set_user_identity_to_username_and_password",
            &AssociationParameters::set_user_identity_to_username_and_password,
            return_value_policy::reference_internal)
        .def(
            "set_user_identity_to_kerberos",
            &AssociationParameters::set_user_identity_to_kerberos,
            return_value_policy::reference_internal)
        .def(
            "set_user_identity_to_saml",
            &AssociationParameters::set_user_identity_to_saml,
            return_value_policy::reference_internal)
        .def("get_maximum_length", &AssociationParameters::get_maximum_length)
        .def(
            "set_maximum_length",
            &AssociationParameters::set_maximum_length,
            return_value_policy::reference_internal)
    ;

    {
        auto presentation_context_scope =
            class_<AssociationParameters::PresentationContext>(
                association_parameters_scope, "PresentationContext");

        enum_<AssociationParameters::PresentationContext::Result>(
                presentation_context_scope, "Result")
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

        // WARNING using STL conversion
        // (https://pybind11.readthedocs.io/en/stable/advanced/cast/stl.html)
        // conflicts with opaque types required to avoid copying data set values
        presentation_context_scope
            .def(init(&presentation_context_constructor))
            .def(init(&presentation_context_simplified_constructor))
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


    }

    {
        auto user_identity_scope =
            class_<AssociationParameters::UserIdentity>(
                association_parameters_scope, "UserIdentity")
            .def(init<>())
            .def_readwrite(
                "type", &AssociationParameters::UserIdentity::type
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

        enum_<AssociationParameters::UserIdentity::Type>(user_identity_scope, "Type")
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
