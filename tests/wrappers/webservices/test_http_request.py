import unittest

import odil

class TestHTTPRequest(unittest.TestCase):
    def test_default_constructor(self):
        request = odil.webservices.HTTPRequest()
        self.assertEqual(request.get_method(), "")
        self.assertEqual(request.get_target(), "")
        self.assertEqual(request.get_http_version(), "HTTP/1.0")
        self.assertEqual(request.get_headers(), {})
        self.assertEqual(request.get_body(), "")

    def test_constructor_method(self):
        request = odil.webservices.HTTPRequest(method="GET")
        self.assertEqual(request.get_method(), "GET")
        self.assertEqual(request.get_target(), "")
        self.assertEqual(request.get_http_version(), "HTTP/1.0")
        self.assertEqual(request.get_headers(), {})
        self.assertEqual(request.get_body(), "")

    def test_constructor_target(self):
        request = odil.webservices.HTTPRequest(
            target="http://example.com/foo?bar=quux")
        self.assertEqual(request.get_method(), "")
        self.assertEqual(
            request.get_target(), "http://example.com/foo?bar=quux")
        self.assertEqual(request.get_http_version(), "HTTP/1.0")
        self.assertEqual(request.get_headers(), {})
        self.assertEqual(request.get_body(), "")

    def test_constructor_http_version(self):
        request = odil.webservices.HTTPRequest(http_version="HTTP/1.1")
        self.assertEqual(request.get_method(), "")
        self.assertEqual(request.get_target(), "")
        self.assertEqual(request.get_http_version(), "HTTP/1.1")
        self.assertEqual(request.get_headers(), {})
        self.assertEqual(request.get_body(), "")

    def test_constructor_headers(self):
        request = odil.webservices.HTTPRequest(headers={"foo": "bar"})
        self.assertEqual(request.get_method(), "")
        self.assertEqual(request.get_target(), "")
        self.assertEqual(request.get_http_version(), "HTTP/1.0")
        self.assertEqual(request.get_headers(), {"foo": "bar"})
        self.assertEqual(request.get_body(), "")

    def test_constructor_body(self):
        request = odil.webservices.HTTPRequest(body="body")
        self.assertEqual(request.get_method(), "")
        self.assertEqual(request.get_target(), "")
        self.assertEqual(request.get_http_version(), "HTTP/1.0")
        self.assertEqual(request.get_headers(), {})
        self.assertEqual(request.get_body(), "body")

    def test_method(self):
        request = odil.webservices.HTTPRequest()
        request.set_method("POST")
        self.assertEqual(request.get_method(), "POST")

    def test_target(self):
        request = odil.webservices.HTTPRequest()
        request.set_target("http://example.com/foo?bar=quux")
        self.assertEqual(
            request.get_target(), "http://example.com/foo?bar=quux")

    def test_http_version(self):
        request = odil.webservices.HTTPRequest()
        request.set_http_version("HTTP/1.1")
        self.assertEqual(request.get_http_version(), "HTTP/1.1")

    def test_headers(self):
        request = odil.webservices.HTTPRequest()
        request.set_headers({"foo": "bar"})
        self.assertEqual(request.get_headers(), {"foo": "bar"})

    def test_body(self):
        request = odil.webservices.HTTPRequest()
        request.set_body("body")
        self.assertEqual(request.get_body(), "body")

if __name__ == "__main__":
    unittest.main()
