import email
import json
import unittest

import odil

class TestQIDORSResponse(unittest.TestCase):
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

    data_sets =  [data_set_1, data_set_2]

    def test_constructor(self):
        response = odil.webservices.QIDORSResponse()
        self.assertEqual(len(response.get_data_sets()), 0)

    def test_data_sets(self):
        response = odil.webservices.QIDORSResponse()
        response.set_data_sets(self.data_sets)
        self.assertSequenceEqual(response.get_data_sets(), self.data_sets)

    def test_Response_DicomJson(self):
        response = odil.webservices.QIDORSResponse()
        response.set_representation(odil.webservices.Utils.Representation.DICOM_JSON)
        response.set_data_sets(self.data_sets)
        self.assertEqual(response.get_media_type(), "application/dicom+json")
        self.assertEqual(response.get_representation(), odil.webservices.Utils.Representation.DICOM_JSON)
        http = response.get_http_response()
        content_type = http.get_header("Content-Type")
        self.assertEqual(content_type, "application/dicom+json")
        json_http = json.loads(http.get_body().decode())
        json_ds = [ json.loads(odil.as_json(x)) for x in self.data_sets ]
        self.assertEqual(json_ds, json_http)

    def test_Response_DicomXML(self):
        response = odil.webservices.QIDORSResponse()
        response.set_representation(odil.webservices.Utils.Representation.DICOM_XML)
        response.set_data_sets(self.data_sets)
        self.assertEqual(response.get_media_type(), "application/dicom+xml")
        self.assertEqual(response.get_representation(), odil.webservices.Utils.Representation.DICOM_XML)
        http = response.get_http_response()

        message_bytes = [
            name.encode()+b": "+value.encode()
            for (name, value) in http.get_headers().items()]
        message_bytes.append(http.get_body())
        message_bytes = b"\r\n".join(message_bytes)
        msg = email.message_from_bytes(message_bytes)
        self.assertTrue(msg.is_multipart())

        i = 0
        for part in msg.walk():
            if part.get_content_type() == "application/dicom+xml":
                self.assertEqual(odil.as_xml(self.data_sets[i], False), part.get_payload())
                i = i+1
        self.assertEqual(i, len(self.data_sets))

    def test_empty_response(self):
        response = odil.webservices.QIDORSResponse()
        http = response.get_http_response()
        self.assertEqual(http.get_status(), 204)
        self.assertEqual(http.get_reason(), "No Content")


if __name__ == "__main__":
    unittest.main()
