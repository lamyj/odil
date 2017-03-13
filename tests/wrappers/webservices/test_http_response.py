import unittest

import odil

class TestHTTPResponse(unittest.TestCase):
    def test_default_constructor(self):
        response = odil.webservices.HTTPResponse()
        self.assertEqual(response.get_http_version(), "")
        self.assertEqual(response.get_status(), 0)
        self.assertEqual(response.get_reason(), "")
        self.assertEqual(dict(response.get_headers()), {})
        self.assertEqual(response.get_body(), "")

    def test_full_constructor(self):
        response = odil.webservices.HTTPResponse(
            http_version="HTTP/1.1", status=404, reason="not found",
            headers={"foo": "bar"}, body="body")
        self.assertEqual(response.get_http_version(), "HTTP/1.1")
        self.assertEqual(response.get_status(), 404)
        self.assertEqual(response.get_reason(), "not found")
        self.assertEqual(dict(response.get_headers()), {"foo":"bar"})
        self.assertEqual(response.get_body(), "body")

    def test_http_version(self):
        response = odil.webservices.HTTPResponse()
        response.set_http_version("HTTP/1.1")
        self.assertEqual(response.get_http_version(), "HTTP/1.1")

    def test_status(self):
        response = odil.webservices.HTTPResponse()
        response.set_status(200)
        self.assertEqual(response.get_status(), 200)

    def test_reason(self):
        response = odil.webservices.HTTPResponse()
        response.set_reason("OK")
        self.assertEqual(response.get_reason(), "OK")

    def test_headers(self):
        response = odil.webservices.HTTPResponse()
        response.set_headers({"foo": "bar"})
        self.assertEqual(dict(response.get_headers()), {"foo": "bar"})

    def test_body(self):
        response = odil.webservices.HTTPResponse()
        response.set_body("body")
        self.assertEqual(response.get_body(), "body")

if __name__ == "__main__":
    unittest.main()
