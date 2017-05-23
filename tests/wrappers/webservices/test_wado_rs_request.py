import unittest

import odil

class TestWADORSRequest(unittest.TestCase):
    def test_default_constructor(self):
        request = odil.webservices.WADORSRequest()
        self.assertEqual(str(request.get_base_url()), "")
        self.assertEqual(request.get_transfer_syntax(), "")
        self.assertEqual(request.get_character_set(), "")
        self.assertFalse(request.get_include_media_type_in_query())
        self.assertFalse(request.get_include_character_set_in_query())

    def test_http_request_constructor(self):
        http_request = odil.webservices.HTTPRequest(
            "GET", odil.webservices.URL.parse("/foo/studies/1.2"),
            headers={"Accept": "multipart/related;type=application/dicom"})
        wado_rs_request = odil.webservices.WADORSRequest(http_request)

        self.assertEqual(str(wado_rs_request.get_base_url()), "/foo")
        self.assertEqual(
            wado_rs_request.get_transfer_syntax(),
            odil.registry.ExplicitVRLittleEndian)
        self.assertEqual(wado_rs_request.get_character_set(), "UTF-8")
        self.assertFalse(wado_rs_request.get_include_media_type_in_query())
        self.assertFalse(wado_rs_request.get_include_character_set_in_query())

        self.assertEqual(
            wado_rs_request.get_type(), odil.webservices.Utils.Type.DICOM)
        self.assertEqual(
            wado_rs_request.get_selector(),
            odil.webservices.Selector("1.2"))
        self.assertEqual(str(wado_rs_request.get_url()), "/foo/studies/1.2")
        self.assertEqual(wado_rs_request.get_media_type(), "application/dicom")
        self.assertEqual(
            wado_rs_request.get_representation(),
            odil.webservices.Utils.Representation.DICOM)

    def test_full_constructor(self):
        request = odil.webservices.WADORSRequest(
            base_url=odil.webservices.URL.parse("http://foo.com/bar"),
            transfer_syntax=odil.registry.ExplicitVRLittleEndian,
            character_set="utf-8", include_media_type_in_query=True,
            include_character_set_in_query=True)
        self.assertEqual(str(request.get_base_url()), "http://foo.com/bar")
        self.assertEqual(
            request.get_transfer_syntax(), odil.registry.ExplicitVRLittleEndian)
        self.assertEqual(request.get_character_set(), "utf-8")
        self.assertTrue(request.get_include_media_type_in_query())
        self.assertTrue(request.get_include_character_set_in_query())

if __name__ == "__main__":
    unittest.main()
