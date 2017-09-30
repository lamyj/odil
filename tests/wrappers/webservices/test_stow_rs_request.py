import email
import unittest

import odil


class TestSTOWRSRequest(unittest.TestCase):
    base_url_http = odil.webservices.URL("http", "example.com", "/dicom", "", "")
    full_url = odil.webservices.URL(
        "http", # scheme
        "example.com", # authority
        "/dicom/studies/1.2/instances", # path
        "", # query
        "" # fragment
    )

    selector = odil.webservices.Selector({"studies" : "1.2"})

    def setUp(self):
        data_set_1 = odil.DataSet()
        data_set_1.add("SOPClassUID", [odil.registry.RawDataStorage])
        data_set_1.add("SOPInstanceUID", ["1.2.3.4"])
        data_set_1.add("PatientID", ["DJ1234"])
        data_set_1.add("PixelSpacing", [1.5, 2.5])

        data_set_2 = odil.DataSet()
        data_set_2.add("SOPClassUID", [odil.registry.MRImageStorage])
        data_set_2.add("SOPInstanceUID", ["1.2.3.5"])
        data_set_2.add("PatientName", ["Doe^John"])
        data_set_2.add("PatientAge", ["042Y"])

        bin = odil.Value.BinaryItem()
        bin.append(0x01)
        bin.append(0x02)
        bin.append(0x03)
        bin.append(0x04)
        binary = odil.Value.Binary()
        binary.append(bin)
        # Fix Binary factory with BinaryItem
        data_set_2.add("Signature", [bytearray([0x01, 0x02, 0x03, 0x04])])

        self.data_sets = [data_set_1, data_set_2]

    def test_constructor_baseUrl(self):
        request = odil.webservices.STOWRSRequest(self.base_url_http)
        self.assertEqual(request.get_base_url(), self.base_url_http)

    def test_base_url(self):
        request = odil.webservices.STOWRSRequest(self.base_url_http)
        base_url_http2 = odil.webservices.URL("http", "second_example.com", "/dicom", "", "")
        request.set_base_url(base_url_http2)
        self.assertEqual(request.get_base_url(), base_url_http2)

    def test_constructor_http(self):
        http_request = odil.webservices.HTTPRequest("POST", self.full_url)
        http_request.set_header("Content-Type", "multipart/related;type=application/dicom")
        request = odil.webservices.STOWRSRequest(http_request)

        # Check for full_url
        self.assertEqual(request.get_url(), self.full_url)

        # Check for media type
        self.assertEqual(request.get_media_type(), "application/dicom")

        # Check for representation
        self.assertEqual(request.get_representation(), odil.webservices.Utils.Representation.DICOM)

        # Check for selector
        self.assertEqual(request.get_selector(), self.selector)

    def test_fail_request_datasets(self):
        request = odil.webservices.STOWRSRequest(self.base_url_http)
        invalid_selector = odil.webservices.Selector({"studies" : "1.2", "series" : "3.4"})
        with self.assertRaises(odil.Exception):
            request.request_dicom(self.data_sets, invalid_selector, odil.webservices.Utils.Representation.DICOM)

    def test_get_http_request(self):

        #DICOM+XML
        request = odil.webservices.STOWRSRequest(self.base_url_http)
        request.request_dicom(self.data_sets, self.selector, odil.webservices.Utils.Representation.DICOM_XML)
        http_request = request.get_http_request()
        # Check for http_request content
        self.assertTrue(http_request.has_header("Content-Type"))
        self.assertEqual(http_request.get_method(), "POST")
        self.assertEqual(http_request.get_http_version(), "HTTP/1.0")

        # Convert http response into string
        http_str = ""
        h = []
        for header in http_request.get_headers():
            h.append(header.key())
        for header in h:
            http_str += header + ": " + http_request.get_header(header)
            http_str += "\r\n" + http_request.get_body()


        msg = email.message_from_string(http_str)
        self.assertTrue(msg.is_multipart())

        i = 0
        for part in msg.walk():
            if part.get_param("type") != "application/dicom+xml":
                i = i+1
        self.assertEqual(i, 3) # 3 parts (One for each dataset and 1 for binary)
        self.assertEqual(request.get_base_url(), self.base_url_http)

        #DICOM
        request.request_dicom(self.data_sets, self.selector, odil.webservices.Utils.Representation.DICOM)
        http_request_dcm = request.get_http_request()
        # Convert http response into string
        http_str = ""
        h = []
        for header in http_request_dcm.get_headers():
            h.append(header.key())
        for header in h:
            http_str += header + ": " + http_request_dcm.get_header(header)
            http_str += "\r\n" + http_request_dcm.get_body()


        msg = email.message_from_string(http_str)
        self.assertTrue(msg.is_multipart())

        i = 0
        for part in msg.walk():
            if part.get_param("type") != "application/dicom":
                i = i+1
        self.assertEqual(i, 2) # 3 parts (One for each dataset and 1 for binary)

    def test_data_sets_equality(self):
        request = odil.webservices.STOWRSRequest(self.base_url_http)
        request.request_dicom([self.data_sets[1]], self.selector, odil.webservices.Utils.Representation.DICOM_JSON)
        http_request = request.get_http_request()
        self.assertEqual(request.get_data_sets(), [self.data_sets[1]])

    def test_equality(self):
        request = odil.webservices.STOWRSRequest(self.base_url_http)
        request.request_dicom(self.data_sets, self.selector, odil.webservices.Utils.Representation.DICOM)
        http_request = request.get_http_request()
        second_request = odil.webservices.STOWRSRequest(http_request)
        self.assertEqual(request, second_request)

    def test_equality_2 (self):
        request = odil.webservices.STOWRSRequest(self.base_url_http)
        request.request_dicom(self.data_sets, self.selector, odil.webservices.Utils.Representation.DICOM_XML)
        http_request = request.get_http_request()
        request_copy = odil.webservices.STOWRSRequest(http_request)
        self.assertEqual(request_copy, request)
        self.assertSequenceEqual(self.data_sets, request_copy.get_data_sets())

    def tearDown(self):
        self.data_sets = None

if __name__ == "__main__":
    unittest.main()
