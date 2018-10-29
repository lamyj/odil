import unittest

import odil

class TestMessage(unittest.TestCase):
    def test_default_constructor(self):
        message = odil.webservices.Message()
        self.assertEqual(dict(message.get_headers()), {})
        self.assertEqual(message.get_body(), b"")

    def test_full_constructor(self):
        message = odil.webservices.Message(headers={"foo": "bar"}, body="body")
        self.assertEqual(dict(message.get_headers()), {"foo": "bar"})
        self.assertEqual(message.get_body(), b"body")

    def test_existing_header(self):
        message = odil.webservices.Message({"foo": "bar", "plip": "plop"})
        self.assertTrue(message.has_header("foo"))
        self.assertEqual(message.get_header("foo"), "bar")

    def test_missing_header(self):
        message = odil.webservices.Message({"foo": "bar", "plip": "plop"})
        self.assertFalse(message.has_header("none"))
        with self.assertRaises(odil.Exception):
            message.get_header("none")

    def test_set_headers(self):
        message = odil.webservices.Message()
        message.set_headers({"foo": "bar", "plip": "plop"})
        self.assertEqual(
            dict(message.get_headers()), {"foo": "bar", "plip": "plop"})

    def test_modify_header(self):
        message = odil.webservices.Message({"foo": "bar", "plip": "plop"})
        message.set_header("foo", "baz")
        self.assertEqual(message.get_header("foo"), "baz")

    def test_add_header(self):
        message = odil.webservices.Message()
        message.set_header("foo", "baz")
        self.assertEqual(message.get_header("foo"), "baz")

    def test_body(self):
        message = odil.webservices.Message()
        message.set_body("body")
        self.assertEqual(message.get_body(), b"body")

if __name__ == "__main__":
    unittest.main()
