import email
import json
import unittest

import odil

class TestSTOWRSResponse(unittest.TestCase):
    def setUp(self):
        data_set_1 = odil.DataSet()
        data_set_1.add("RetrieveURL", ["http://example.com/dicom/studies/7.8.9"])
        data_set_1.add("FailedSOPSequence", [odil.DataSet()], odil.VR.SQ)
        referenceSOPSequence_item1 = odil.DataSet()
        referenceSOPSequence_item1.add("ReferencedSOPClassUID", [odil.registry.MRImageStorage])
        referenceSOPSequence_item1.add("ReferencedSOPInstanceUID", ["1.2.3.6.1"])
        referenceSOPSequence_item1.add("RetrieveURL",
            ["http://example.com/dicom/studies/7.8.9/series/4.5/instances/1.2.3.6.1"])

        referenceSOPSequence_item2 = odil.DataSet()
        referenceSOPSequence_item2.add("ReferencedSOPClassUID", [odil.registry.RawDataStorage])
        referenceSOPSequence_item2.add("ReferencedSOPInstanceUID", ["1.2.3.6.2"])
        referenceSOPSequence_item2.add("RetrieveURL",
        ["http://example.com/dicom/studies/7.8.9/series/4.5/instances/1.2.3.6.2"])

        data_set_1.add("ReferencedSOPSequence", [referenceSOPSequence_item1, referenceSOPSequence_item2])

        self.data_set = data_set_1

    def test_constructor(self):
        response = odil.webservices.STOWRSResponse()
        self.assertEqual(len(response.get_store_instance_responses()), 0)

    def test_respondDICOM_XML(self):
        response = odil.webservices.STOWRSResponse()
        response.set_representation(odil.webservices.Utils.Representation.DICOM_XML)
        response.set_store_instance_responses(self.data_set)
        self.assertEqual(response.get_media_type(), "application/dicom+xml")
        self.assertEqual(response.get_representation(), odil.webservices.Utils.Representation.DICOM_XML)
        http = response.get_http_response()

        msg = self._http_message_to_email_message(http)

        for part in msg.walk():
            if part.get_content_type() == "application/dicom+xml":
                self.assertEqual(odil.as_xml(self.data_set, False), part.get_payload())

    def test_respondDICOM_JSON(self):
        response = odil.webservices.STOWRSResponse()
        response.set_representation(odil.webservices.Utils.Representation.DICOM_JSON)
        response.set_store_instance_responses(self.data_set)
        self.assertEqual(response.get_media_type(), "application/dicom+json")
        self.assertEqual(response.get_representation(), odil.webservices.Utils.Representation.DICOM_JSON)
        http = response.get_http_response()

        msg = self._http_message_to_email_message(http)
        self.assertFalse(msg.is_multipart())
        self.assertTrue(msg.get_content_type(), "application/dicom+json")
        odil_json = [json.loads(odil.as_json(self.data_set))]
        http_json = json.loads(http.get_body())
        self.assertSequenceEqual(http_json, odil_json)

    def test_equality(self):
        http_response = odil.webservices.HTTPResponse()
        http_response.set_header("Content-Type", "application/dicom+xml")
        http_response.set_status(200)
        http_response.set_reason("OK")
        http_response.set_body(odil.as_xml(self.data_set, False))

        response = odil.webservices.STOWRSResponse(http_response)
        response_2 = odil.webservices.STOWRSResponse()
        response_2.set_representation(odil.webservices.Utils.Representation.DICOM_XML)
        response_2.set_store_instance_responses(self.data_set)
        response_2.set_warning(False)
        response_2.set_reason("OK")
        self.assertEqual(response, response_2)

    def test_difference(self):
        http_response = odil.webservices.HTTPResponse()
        http_response.set_header("Content-Type", "application/dicom+xml")
        http_response.set_status(200)
        http_response.set_reason("OK")
        http_response.set_body(odil.as_xml(self.data_set, False))
        response = odil.webservices.STOWRSResponse(http_response)

        http_response_2 = odil.webservices.HTTPResponse()
        http_response_2.set_header("Content-Type", "application/dicom+xml")
        http_response_2.set_status(400)
        http_response_2.set_reason("Bad Request")
        http_response_2.set_body(odil.as_xml(self.data_set, False))
        response_2 = odil.webservices.STOWRSResponse(http_response_2)

        self.assertTrue(response != response_2)

    def test_reason(self):
        response = odil.webservices.STOWRSResponse()
        response.set_reason("Unauthorized")
        self.assertEqual(response.get_reason(), "Unauthorized")

    def test_invalid_reason(self):
        response = odil.webservices.STOWRSResponse()
        with self.assertRaises(odil.Exception):
            self.assertRaises(response.set_reason("Unrecognize"))

    def test_failureCode(self):
        response = odil.webservices.STOWRSResponse()
        response.set_failure_code(503)
        self.assertEqual(response.get_failure_code(), 503)

    def test_Representation(self):
        response = odil.webservices.STOWRSResponse()
        response.set_representation(odil.webservices.Utils.Representation.DICOM_JSON)
        self.assertTrue(response.get_representation(), odil.webservices.Utils.Representation.DICOM_JSON)

    def tearDown(self):
        self.data_set = None

    def _http_message_to_email_message(self, http_message):
        message_bytes = [
            name.encode()+b": "+value.encode()
            for (name, value) in http_message.get_headers().items()]
        message_bytes.append(http_message.get_body())
        message_bytes = b"\r\n".join(message_bytes)

        email_message = email.message_from_bytes(message_bytes)
        return email_message

if __name__ == "__main__":
    unittest.main()
