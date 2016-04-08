import unittest

import odil

class TestAssociationParameters(unittest.TestCase):
    def test_default_constructor(self):
        parameters = odil.AssociationParameters()
        self.assertEqual(parameters.get_called_ae_title(), "")
        self.assertEqual(parameters.get_calling_ae_title(), "")
        self.assertEqual(len(parameters.get_presentation_contexts()), 0)

        user_identity = parameters.get_user_identity()
        self.assertEqual(
            user_identity.type, 
            odil.AssociationParameters.UserIdentity.Type.None)

        self.assertEqual(parameters.get_maximum_length(), 16384)

    def test_called_ae_title(self):
        parameters = odil.AssociationParameters()
        parameters.set_called_ae_title("foo")
        self.assertEqual(parameters.get_called_ae_title(), "foo")

    def test_calling_ae_title(self):
        parameters = odil.AssociationParameters()
        parameters.set_calling_ae_title("foo")
        self.assertEqual(parameters.get_calling_ae_title(), "foo")

    def test_presentation_contexts(self):
        presentation_context = odil.AssociationParameters.PresentationContext()
        presentation_context.id = 1
        presentation_context.abstract_syntax = "foo"
        presentation_context.transfer_syntaxes.append("bar")

        parameters = odil.AssociationParameters()
        parameters.set_presentation_contexts([presentation_context])

        self.assertEqual(len(parameters.get_presentation_contexts()), 1)
        self.assertEqual(
            parameters.get_presentation_contexts()[0], presentation_context)

    def test_user_identity_username(self):
        parameters = odil.AssociationParameters()
        parameters.set_user_identity_to_username("foo")

        user_identity = parameters.get_user_identity()
        self.assertEqual(
            user_identity.type, 
            odil.AssociationParameters.UserIdentity.Type.Username)
        self.assertEqual(user_identity.primary_field, "foo")

    def test_user_identity_username_and_password(self):
        parameters = odil.AssociationParameters()
        parameters.set_user_identity_to_username_and_password("foo", "bar")

        user_identity = parameters.get_user_identity()
        self.assertEqual(
            user_identity.type, 
            odil.AssociationParameters.UserIdentity.Type.UsernameAndPassword)
        self.assertEqual(user_identity.primary_field, "foo")
        self.assertEqual(user_identity.secondary_field, "bar")

    def test_user_identity_kerberos(self):
        parameters = odil.AssociationParameters()
        parameters.set_user_identity_to_kerberos("foo")

        user_identity = parameters.get_user_identity()
        self.assertEqual(
            user_identity.type, 
            odil.AssociationParameters.UserIdentity.Type.Kerberos)
        self.assertEqual(user_identity.primary_field, "foo")

    def test_user_identity_saml(self):
        parameters = odil.AssociationParameters()
        parameters.set_user_identity_to_saml("foo")

        user_identity = parameters.get_user_identity()
        self.assertEqual(
            user_identity.type, 
            odil.AssociationParameters.UserIdentity.Type.SAML)
        self.assertEqual(user_identity.primary_field, "foo")

    def test_user_identity_none(self):
        parameters = odil.AssociationParameters()
        parameters.set_user_identity_to_saml("foo")
        parameters.set_user_identity_to_none()

        user_identity = parameters.get_user_identity()
        self.assertEqual(
            user_identity.type, 
            odil.AssociationParameters.UserIdentity.Type.None)

    def test_maximum_length(self):
        parameters = odil.AssociationParameters()
        parameters.set_maximum_length(12345)
        self.assertEqual(parameters.get_maximum_length(), 12345)

    def test_chaining(self):
        parameters = odil.AssociationParameters()
        parameters.set_called_ae_title("foo").set_calling_ae_title("bar")
        self.assertEqual(parameters.get_called_ae_title(), "foo")
        self.assertEqual(parameters.get_calling_ae_title(), "bar")
    
class TestPresentationContext(unittest.TestCase):
    def test_constructor(self):
        presentation_context = odil.AssociationParameters.PresentationContext(
            1, "foo", ["bar", "baz"], False, True)
        self.assertEqual(presentation_context.id, 1)
        self.assertEqual(presentation_context.abstract_syntax, "foo")
        self.assertEqual(
            [x for x in presentation_context.transfer_syntaxes], ["bar", "baz"])
        self.assertEqual(presentation_context.scu_role_support, False)
        self.assertEqual(presentation_context.scp_role_support, True)

if __name__ == "__main__":
    unittest.main()
