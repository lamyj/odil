import unittest

import odil

class TestURL(unittest.TestCase):
    def test_parse(self):
        url = odil.webservices.URL.parse("http://foo.com/bar?plip=plop#here")
        self.assertEqual(url.scheme, "http")
        self.assertEqual(url.authority, "foo.com")
        self.assertEqual(url.path, "/bar")
        self.assertEqual(url.query, "plip=plop")
        self.assertEqual(url.fragment, "here")

    def test_default_arguments(self):
        url = odil.webservices.URL("http", "foo.com", "/bar", fragment="here")
        self.assertEqual(url.scheme, "http")
        self.assertEqual(url.authority, "foo.com")
        self.assertEqual(url.path, "/bar")
        self.assertEqual(url.query, "")
        self.assertEqual(url.fragment, "here")

    def test_serialize(self):
        url = odil.webservices.URL("http", "foo.com", "/bar", "plip=plop", "here")
        self.assertEqual(str(url), "http://foo.com/bar?plip=plop#here")

if __name__ == "__main__":
    unittest.main()
