import unittest

import odil

class TestAssociation(unittest.TestCase):
    def test_default_constructor(self):
        association = odil.Association()
        self.assertFalse(association.is_associated())

    def test_peer_host(self):
        association = odil.Association()
        association.set_peer_host("pacs.example.com")
        self.assertEqual(association.get_peer_host(), "pacs.example.com")

    def test_peer_port(self):
        association = odil.Association()
        association.set_peer_port(1234)
        self.assertEqual(association.get_peer_port(), 1234)

    def test_peer_port(self):
        association = odil.Association()
        association.set_peer_port(1234)
        self.assertEqual(association.get_peer_port(), 1234)

    def test_parameters(self):
        parameters = odil.AssociationParameters()
        parameters.set_called_ae_title("foo")

        association = odil.Association()
        association.set_parameters(parameters)
        self.assertEqual(
            association.get_parameters().get_called_ae_title(), "foo")

    def test_update_parameters(self):
        association = odil.Association()
        association.update_parameters().set_called_ae_title("foo")
        self.assertEqual(
            association.get_parameters().get_called_ae_title(), "foo")

    def test_next_message_id(self):
        association = odil.Association()
        id1 = association.next_message_id()
        id2 = association.next_message_id()
        self.assertNotEqual(id1, id2)

if __name__ == "__main__":
    unittest.main()

