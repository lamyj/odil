import email
import io
import json
import tempfile
import unittest

import odil

class WADORSResponse(unittest.TestCase):
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

        self.data_sets =  [data_set_1, data_set_2]

        bin = odil.Value.BinaryItem()
        bin.append(0x01)
        bin.append(0x02)
        bulk_data_1 = odil.webservices.BulkData(bin, "foo/bar", "here")

        bin = odil.Value.BinaryItem()
        bin.append(0x03)
        bin.append(0x04)
        bulk_data_2 = odil.webservices.BulkData(bin, "plip/plop", "not/here")

        self.bulk_data = [
            bulk_data_1, bulk_data_2
        ]

    def test_constructor(self):
        response = odil.webservices.WADORSResponse()
        self.assertEqual(len(response.get_data_sets()), 0)
        self.assertEqual(len(response.get_bulk_data()), 0)
        self.assertFalse(response.is_partial())
        self.assertEqual(response.get_type(), odil.webservices.Utils.Type.None)

    def test_data_sets(self):
        response = odil.webservices.WADORSResponse()
        response.set_data_sets(self.data_sets)
        self.assertSequenceEqual(response.get_data_sets(), self.data_sets)

    def test_bulk_data(self):
        response = odil.webservices.WADORSResponse()
        response.set_bulk_data(self.bulk_data)
        bulk = response.get_bulk_data()
        self.assertEqual(len(bulk), len(self.bulk_data))
        for i in range(len(bulk)):
            self.assertEqual(bulk[i].data.get_memory_view(), self.bulk_data[i].data.get_memory_view())
            self.assertEqual(bulk[i].type, self.bulk_data[i].type)
            self.assertEqual(bulk[i].location, self.bulk_data[i].location)

    def test_partial(self):
        response = odil.webservices.WADORSResponse()
        response.set_partial(True)
        self.assertTrue(response.is_partial())

    def test_respondFull(self):
        wado = odil.webservices.WADORSResponse()
        wado.set_data_sets(self.data_sets)
        wado.set_partial(False)
        wado.respond_dicom(odil.webservices.Utils.Representation.DICOM)
        http = wado.get_http_response()
        self.assertEqual(http.get_status(), 200)
        self.assertEqual(http.get_reason(), "OK")

    def test_respondPartial(self):
        wado = odil.webservices.WADORSResponse()
        wado.set_data_sets(self.data_sets)
        wado.set_partial(True)
        wado.respond_dicom(odil.webservices.Utils.Representation.DICOM)
        http = wado.get_http_response()
        self.assertEqual(http.get_status(), 206)
        self.assertEqual(http.get_reason(), "Partial Content")

    def test_respondDICOM(self):
        wado = odil.webservices.WADORSResponse()
        wado.set_data_sets(self.data_sets)
        wado.respond_dicom(odil.webservices.Utils.Representation.DICOM)
        self.assertEqual(wado.get_type(), odil.webservices.Utils.Type.DICOM)
        self.assertEqual(wado.get_representation(), odil.webservices.Utils.Representation.DICOM)
        http = wado.get_http_response()

        # Convert http response into string

        http_str = ""
        h = []
        for header in http.get_headers():
            h.append(header.key())
        for header in h:
            http_str += header + ": " + http.get_header(header)
        http_str += "\r\n" + http.get_body()


        msg = email.message_from_string(http_str)
        self.assertTrue(msg.is_multipart())

        i = 0
        for part in msg.walk():
            if part.get_content_type() == "application/dicom":
                file = tempfile.mkstemp()
                stream = io.FileIO(file[1], 'w')
                stream.write(part.get_payload())
                stream.close()
                with odil.open(file[1]) as stream:
                    ds = odil.Reader.read_file(stream)[1]
                self.assertEqual(self.data_sets[i], ds)
                i = i+1
        self.assertEqual(i, len(self.data_sets))

    def test_respondDICOMXML(self):
        wado = odil.webservices.WADORSResponse()
        wado.set_data_sets(self.data_sets)
        wado.respond_dicom(odil.webservices.Utils.Representation.DICOM_XML)
        self.assertEqual(wado.get_type(), odil.webservices.Utils.Type.DICOM)
        self.assertEqual(wado.get_representation(), odil.webservices.Utils.Representation.DICOM_XML)
        http = wado.get_http_response()

        # Convert http response into string
        http_str = ""
        h = []
        for header in http.get_headers():
            h.append(header.key())
        for header in h:
            http_str += header + ": " + http.get_header(header)
        http_str += "\r\n" + http.get_body()


        msg = email.message_from_string(http_str)
        self.assertTrue(msg.is_multipart())

        i = 0
        for part in msg.walk():
            if part.get_content_type() == "application/dicom+xml":
                self.assertEqual(odil.as_xml(self.data_sets[i], False), part.get_payload())
                i = i+1
        self.assertEqual(i, len(self.data_sets))

    def test_respondDICOMJSON(self):
        wado = odil.webservices.WADORSResponse()
        wado.set_data_sets(self.data_sets)
        wado.respond_dicom(odil.webservices.Utils.Representation.DICOM_JSON)
        self.assertEqual(wado.get_type(), odil.webservices.Utils.Type.DICOM)
        self.assertEqual(wado.get_representation(), odil.webservices.Utils.Representation.DICOM_JSON)
        http = wado.get_http_response()

        # Convert http response into string
        http_str = ""
        h = []
        for header in http.get_headers():
            h.append(header.key())
        for header in h:
            http_str += header + ": " + http.get_header(header)
        http_str += "\r\n" + http.get_body()

        msg = email.message_from_string(http_str)
        self.assertFalse(msg.is_multipart())
        self.assertTrue(msg.get_content_type(), "application/dicom+json")
        odil_json = [json.loads(odil.as_json(x)) for x in self.data_sets]
        http_json = json.loads(http.get_body())
        self.assertSequenceEqual(http_json, odil_json)

    def test_respondBulkData(self):
        wado = odil.webservices.WADORSResponse()
        wado.set_bulk_data(self.bulk_data)
        wado.respond_bulk_data()
        self.assertEqual(wado.get_type(), odil.webservices.Utils.Type.BulkData)
        http = wado.get_http_response()

        # Convert http response into string
        http_str = ""
        h = []
        for header in http.get_headers():
            h.append(header.key())
        for header in h:
            http_str += header + ": " + http.get_header(header)
            http_str += "\r\n" + http.get_body()


        msg = email.message_from_string(http_str)
        self.assertTrue(msg.is_multipart())

        i = 0
        for part in msg.walk():
            if part.get_param("type") != "application/octet-stream":
                self.assertEqual(part.get("Content-Location"), self.bulk_data[i].location)
                self.assertEqual(part.get_content_type(), self.bulk_data[i].type)
                self.assertEqual(
                    self.bulk_data[i].data.get_memory_view().tobytes(),
                    part.get_payload())
                i = i+1
        self.assertEqual(i, len(self.bulk_data))

    def test_respondPixelData(self):
        wado = odil.webservices.WADORSResponse()
        wado.set_bulk_data(self.bulk_data)
        wado.respond_pixel_data("image/jpeg")
        self.assertEqual(wado.get_type(), odil.webservices.Utils.Type.PixelData)
        http = wado.get_http_response();

        # Convert http response into string
        http_str = ""
        h = []
        for header in http.get_headers():
            h.append(header.key())
        for header in h:
            http_str += header + ": " + http.get_header(header)
            http_str += "\r\n" + http.get_body()


        msg = email.message_from_string(http_str)
        self.assertTrue(msg.is_multipart())

        i = 0
        for part in msg.walk():
            if part.get_param("type") != "image/jpeg":
                self.assertEqual(part.get("Content-Location"), self.bulk_data[i].location)
                self.assertEqual(part.get_content_type(), self.bulk_data[i].type)
                self.assertEqual(
                    self.bulk_data[i].data.get_memory_view().tobytes(),
                    part.get_payload())
                i = i+1
        self.assertEqual(i, len(self.bulk_data))


    def tearDown(self):
        self.data_sets = None
        self.bulk_data = None

if __name__ == "__main__":
    unittest.main()
