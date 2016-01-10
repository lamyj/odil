#define BOOST_TEST_MODULE AssociationParameters
#include <boost/test/unit_test.hpp>

#include "odil/AssociationParameters.h"
#include "odil/Exception.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    odil::AssociationParameters const parameters;
    BOOST_REQUIRE_EQUAL(parameters.get_called_ae_title(), "");
    BOOST_REQUIRE_EQUAL(parameters.get_calling_ae_title(), "");
    BOOST_REQUIRE(parameters.get_presentation_contexts().empty());

    BOOST_REQUIRE(
        parameters.get_user_identity().type ==
            odil::AssociationParameters::UserIdentity::Type::None);
    BOOST_REQUIRE(parameters.get_user_identity().primary_field.empty());
    BOOST_REQUIRE(parameters.get_user_identity().secondary_field.empty());

    BOOST_REQUIRE_EQUAL(parameters.get_maximum_length(), 16384);
}

BOOST_AUTO_TEST_CASE(CalledAETITLE)
{
    odil::AssociationParameters parameters;
    parameters.set_called_ae_title("foo");
    BOOST_REQUIRE_EQUAL(parameters.get_called_ae_title(), "foo");
}

BOOST_AUTO_TEST_CASE(CalledAETITLETooLong)
{
    odil::AssociationParameters parameters;
    BOOST_REQUIRE_THROW(
        parameters.set_called_ae_title("0123456789abcdefTOO_LONG"),
        odil::Exception);
}

BOOST_AUTO_TEST_CASE(CallingAETITLE)
{
    odil::AssociationParameters parameters;
    parameters.set_calling_ae_title("foo");
    BOOST_REQUIRE_EQUAL(parameters.get_calling_ae_title(), "foo");
}

BOOST_AUTO_TEST_CASE(CallingAETITLETooLong)
{
    odil::AssociationParameters parameters;
    BOOST_REQUIRE_THROW(
        parameters.set_calling_ae_title("0123456789abcdefTOO_LONG"),
        odil::Exception);
}

BOOST_AUTO_TEST_CASE(PresentationContexts)
{
    odil::AssociationParameters parameters;
    parameters.set_presentation_contexts({
        { 1, "abstract1", { "transfer1", "transfer2" }, true, false },
        { 3, "abstract2", { "transfer3" }, false, true }
    });

    BOOST_REQUIRE_EQUAL(parameters.get_presentation_contexts().size(), 2);

    BOOST_REQUIRE_EQUAL(parameters.get_presentation_contexts()[0].id, 1);
    BOOST_REQUIRE_EQUAL(
        parameters.get_presentation_contexts()[0].abstract_syntax, "abstract1");
    BOOST_REQUIRE_EQUAL(
        parameters.get_presentation_contexts()[0].transfer_syntaxes.size(), 2);
    BOOST_REQUIRE_EQUAL(
        parameters.get_presentation_contexts()[0].transfer_syntaxes[0],
        "transfer1");
    BOOST_REQUIRE_EQUAL(
        parameters.get_presentation_contexts()[0].transfer_syntaxes[1],
        "transfer2");
    BOOST_REQUIRE(parameters.get_presentation_contexts()[0].scu_role_support);
    BOOST_REQUIRE(!parameters.get_presentation_contexts()[0].scp_role_support);

    BOOST_REQUIRE_EQUAL(parameters.get_presentation_contexts()[1].id, 3);
    BOOST_REQUIRE_EQUAL(
        parameters.get_presentation_contexts()[1].abstract_syntax, "abstract2");
    BOOST_REQUIRE_EQUAL(
        parameters.get_presentation_contexts()[1].transfer_syntaxes.size(), 1);
    BOOST_REQUIRE_EQUAL(
        parameters.get_presentation_contexts()[1].transfer_syntaxes[0],
        "transfer3");
    BOOST_REQUIRE(!parameters.get_presentation_contexts()[1].scu_role_support);
    BOOST_REQUIRE(parameters.get_presentation_contexts()[1].scp_role_support);
}

BOOST_AUTO_TEST_CASE(UserIdentityNone)
{
    odil::AssociationParameters parameters;
    parameters.set_user_identity_to_username_and_password("foo", "bar");
    parameters.set_user_identity_to_none();

    BOOST_REQUIRE(
        parameters.get_user_identity().type ==
            odil::AssociationParameters::UserIdentity::Type::None);
    BOOST_REQUIRE(parameters.get_user_identity().primary_field.empty());
    BOOST_REQUIRE(parameters.get_user_identity().secondary_field.empty());
}

BOOST_AUTO_TEST_CASE(UserIdentityUsername)
{
    odil::AssociationParameters parameters;
    parameters.set_user_identity_to_username("foo");

    BOOST_REQUIRE(
        parameters.get_user_identity().type ==
            odil::AssociationParameters::UserIdentity::Type::Username);
    BOOST_REQUIRE_EQUAL(parameters.get_user_identity().primary_field, "foo");
    BOOST_REQUIRE(parameters.get_user_identity().secondary_field.empty());
}

BOOST_AUTO_TEST_CASE(UserIdentityUsernameAndPassword)
{
    odil::AssociationParameters parameters;
    parameters.set_user_identity_to_username_and_password("foo", "bar");

    BOOST_REQUIRE(
        parameters.get_user_identity().type ==
            odil::AssociationParameters::UserIdentity::Type::UsernameAndPassword);
    BOOST_REQUIRE_EQUAL(parameters.get_user_identity().primary_field, "foo");
    BOOST_REQUIRE_EQUAL(parameters.get_user_identity().secondary_field, "bar");
}

BOOST_AUTO_TEST_CASE(UserIdentityKerberos)
{
    odil::AssociationParameters parameters;
    parameters.set_user_identity_to_kerberos("foo");

    BOOST_REQUIRE(
        parameters.get_user_identity().type ==
            odil::AssociationParameters::UserIdentity::Type::Kerberos);
    BOOST_REQUIRE_EQUAL(parameters.get_user_identity().primary_field, "foo");
    BOOST_REQUIRE(parameters.get_user_identity().secondary_field.empty());
}

BOOST_AUTO_TEST_CASE(UserIdentitySAML)
{
    odil::AssociationParameters parameters;
    parameters.set_user_identity_to_saml("foo");

    BOOST_REQUIRE(
        parameters.get_user_identity().type ==
            odil::AssociationParameters::UserIdentity::Type::SAML);
    BOOST_REQUIRE_EQUAL(parameters.get_user_identity().primary_field, "foo");
    BOOST_REQUIRE(parameters.get_user_identity().secondary_field.empty());
}

BOOST_AUTO_TEST_CASE(MaximumLength)
{
    odil::AssociationParameters parameters;
    parameters.set_maximum_length(0x12345678);
    BOOST_REQUIRE_EQUAL(parameters.get_maximum_length(), 0x12345678);
}

BOOST_AUTO_TEST_CASE(ChainedSetters)
{
    odil::AssociationParameters parameters;
    parameters
        .set_called_ae_title("called")
        .set_calling_ae_title("calling")
        .set_presentation_contexts({ { 1, "abstract", { "transfer" }, true, true } })
        .set_user_identity_to_username_and_password("foo", "bar")
        .set_maximum_length(0x12345678);

    BOOST_REQUIRE_EQUAL(parameters.get_called_ae_title(), "called");
    BOOST_REQUIRE_EQUAL(parameters.get_calling_ae_title(), "calling");
    BOOST_REQUIRE_EQUAL(parameters.get_presentation_contexts().size(), 1);

    BOOST_REQUIRE(
        parameters.get_user_identity().type ==
            odil::AssociationParameters::UserIdentity::Type::UsernameAndPassword);
    BOOST_REQUIRE_EQUAL(parameters.get_user_identity().primary_field, "foo");
    BOOST_REQUIRE_EQUAL(parameters.get_user_identity().secondary_field, "bar");

    BOOST_REQUIRE_EQUAL(parameters.get_maximum_length(), 0x12345678);
}
