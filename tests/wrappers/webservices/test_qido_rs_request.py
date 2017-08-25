import unittest

import odil

class TestQIDORSRequest(unittest.TestCase):
    base_url_http = odil.webservices.URL("http", "example.com", "/dicom", "", "")
    full_url = odil.webservices.URL(
        "http",
        "example.com",
        "/dicom/studies/1.2/instances",
        "PatientName=TOTO&"
        "SharedFunctionalGroupsSequence.EffectiveEchoTime=10.5&"
        "includefield=00200020&includefield=52009229.00200035",
        ""
    )

    def test_url_constructor(self):
        request = odil.webservices.QIDORSRequest(self.base_url_http)
        self.assertEqual(request.get_base_url(), self.base_url_http)
        self.assertEqual(request.get_media_type(), "")
        self.assertEqual(request.get_representation(), odil.webservices.Utils.Representation.DICOM_JSON)
        self.assertEqual(request.get_url(), odil.webservices.URL())
        self.assertEqual(request.get_selector(), odil.webservices.Selector())
        self.assertEqual(request.get_query_data_set(), odil.DataSet())
        self.assertFalse(request.get_fuzzymatching())
        self.assertEqual(request.get_limit(), -1)
        self.assertEqual(request.get_offset(), 0)

    def test_base_url(self):
        http_request = odil.webservices.HTTPRequest("GET", self.full_url)
        http_request.set_header("Accept", "application/dicom+json")
        request = odil.webservices.QIDORSRequest(http_request)
        self.assertEqual(request.get_base_url(), self.base_url_http)

    def test_set_base_url(self):
        request = odil.webservices.QIDORSRequest(odil.webservices.URL())

    def test_full_url(self):
        http_request = odil.webservices.HTTPRequest("GET", self.full_url)
        http_request.set_header("Accept", "application/dicom+json")
        request = odil.webservices.QIDORSRequest(http_request)
        full_url_alphabetic = odil.webservices.URL(
            "http",
            "example.com",
            "/dicom/studies/1.2/instances",
            "PatientName=TOTO&"
            "SharedFunctionalGroupsSequence.EffectiveEchoTime=10.5&"
            "includefield=PatientOrientation&"
            "includefield=SharedFunctionalGroupsSequence.ImageOrientation&"
            "fuzzymatching=false",
            ""
        )
        # Check for whole url
        self.assertEqual(request.get_url(), full_url_alphabetic)

    def test_selector(self):
        http_request = odil.webservices.HTTPRequest("GET", self.full_url)
        http_request.set_header("Accept", "application/dicom+json")
        request = odil.webservices.QIDORSRequest(http_request)
        # Check For Selector
        self.assertEqual(request.get_selector().get_path(False), "/studies/1.2/instances")

    def test_query_dataset(self):
        http_request = odil.webservices.HTTPRequest("GET", self.full_url)
        http_request.set_header("Accept", "application/dicom+json")
        request = odil.webservices.QIDORSRequest(http_request)
        # Check For DataSet
        dataset = odil.DataSet()
        dataset.add(odil.Tag("PatientName"),["TOTO"])
        dataset.add(odil.Tag("00200020"))
        shared = odil.DataSet()
        shared.add(odil.Tag("EffectiveEchoTime"), [10.5])
        shared.add(odil.Tag("00200035"))
        dataset.add(odil.Tag("SharedFunctionalGroupsSequence"), [shared])
        self.assertEqual(request.get_query_data_set(), dataset)

    def test_fuzzy_limit_offset(self):
        http_request = odil.webservices.HTTPRequest("GET", self.full_url)
        http_request.set_header("Accept", "application/dicom+json")
        request = odil.webservices.QIDORSRequest(http_request)
        # Check for fuzzymatching
        self.assertFalse(request.get_fuzzymatching())
        # Check for limit - offset
        self.assertEqual(request.get_limit(), -1)
        self.assertEqual(request.get_offset(), 0)

    def test_media_type_json(self):
        http_request = odil.webservices.HTTPRequest("GET", self.full_url)
        http_request.set_header("Accept", "application/dicom+json")
        request = odil.webservices.QIDORSRequest(http_request)
        self.assertEqual(request.get_representation(), odil.webservices.Utils.Representation.DICOM_JSON)

    def test_media_type_xml(self):
        http_request = odil.webservices.HTTPRequest("GET", self.full_url)
        http_request.set_header("Accept", "multipart/related;type=application/dicom+xml")
        request = odil.webservices.QIDORSRequest(http_request)
        self.assertEqual(request.get_representation(), odil.webservices.Utils.Representation.DICOM_XML)

    def test_media_type_unrecognized(self):
        http_request = odil.webservices.HTTPRequest("GET", self.full_url)
        http_request.set_header("Accept", "multipart/related;type=application/dicom+json")
        with self.assertRaises(odil.Exception):
            odil.webservices.QIDORSRequest(http_request)

    def test_request_data_set(self):
        # Selector
        selector = odil.webservices.Selector()
        selector.set_study("1.2").set_instance("")
        # DataSet
        dataset = odil.DataSet()
        dataset.add(odil.Tag("PatientName"),["TOTO"])
        dataset.add(odil.Tag("00200020"))
        shared = odil.DataSet()
        shared.add(odil.Tag("StudyDate"), [20130509])
        shared.add(odil.Tag("00200035"))
        dataset.add(odil.Tag("SharedFunctionalGroupsSequence"), [shared])

        request = odil.webservices.QIDORSRequest(self.base_url_http)
        request.request_datasets(
            odil.webservices.Utils.Representation.DICOM_XML,
            selector,
            dataset
        )

        full_url_alphabetic_tags = odil.webservices.URL(
            "http",
            "example.com",
            "/dicom/studies/1.2/instances",
            "PatientName=TOTO&"
            "SharedFunctionalGroupsSequence.StudyDate=20130509&"
            "includefield=PatientOrientation&"
            "includefield=SharedFunctionalGroupsSequence.ImageOrientation&"
            "fuzzymatching=false",
            ""
        )
        self.assertEqual(request.get_http_request().get_target(), full_url_alphabetic_tags)
        self.assertEqual(request.get_http_request().get_method(), "GET")

    def test_equality(self):
        full_url_cpy = odil.webservices.URL(
            "http",
            "example.com",
            "/dicom/studies/1.2/instances",
            "SharedFunctionalGroupsSequence.EffectiveEchoTime=10.5&"
            "includefield=00200020&"
            "includefield=52009229.00200035&"
            "PatientName=TOTO"
            ""
        )
        http_request_base = odil.webservices.HTTPRequest("GET", self.full_url)
        http_request_base.set_header("Accept", "application/dicom+json")
        request = odil.webservices.QIDORSRequest(http_request_base)
        http_request_cpy = odil.webservices.HTTPRequest("GET", full_url_cpy)
        http_request_cpy.set_header("Accept", "application/dicom+json")
        request_cpy = odil.webservices.QIDORSRequest(http_request_cpy)

        self.assertTrue(request == request_cpy)

    def test_difference(self):
        full_url_cpy = odil.webservices.URL(
            "http",
            "example.com",
            "/dicom/studies/1.2/instances",
            "SharedFunctionalGroupsSequence.EffectiveEchoTime=10.5&"
            "includefield=00200020&"
            "includefield=52009229.00200035&"
            "PatientName=TUTU"
            ""
        )
        http_request_base = odil.webservices.HTTPRequest("GET", self.full_url)
        http_request_base.set_header("Accept", "application/dicom+json")
        request = odil.webservices.QIDORSRequest(http_request_base)
        http_request_cpy = odil.webservices.HTTPRequest("GET", full_url_cpy)
        http_request_cpy.set_header("Accept", "application/dicom+json")
        request_cpy = odil.webservices.QIDORSRequest(http_request_cpy)

        self.assertIsNot(request, request_cpy)

if __name__ == "__main__":
    unittest.main()
