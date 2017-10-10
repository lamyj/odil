import unittest

from io import BytesIO

import odil

class TestWriter(unittest.TestCase):
    def test_constructor_1(self):
        stream = odil.iostream(BytesIO())
        writer = odil.Writer(stream, odil.ByteOrdering.LittleEndian, False)
        self.assertEqual(writer.byte_ordering, odil.ByteOrdering.LittleEndian)
        self.assertFalse(writer.explicit_vr)
        self.assertEqual(
            writer.item_encoding, odil.Writer.ItemEncoding.ExplicitLength)
        self.assertFalse(writer.use_group_length)

    def test_constructor_2(self):
        stream = odil.iostream(BytesIO())
        writer = odil.Writer(
            stream, odil.registry.ExplicitVRBigEndian_Retired)
        self.assertEqual(writer.byte_ordering, odil.ByteOrdering.BigEndian)
        self.assertTrue(writer.explicit_vr)
        self.assertEqual(
            writer.item_encoding, odil.Writer.ItemEncoding.ExplicitLength)
        self.assertFalse(writer.use_group_length)

    def test_write_data_set(self):
        data_set = odil.DataSet()
        data_set.add("PatientName", ["Foo^Bar"])
        data_set.add("PatientID", ["FOO"])

        string_io = BytesIO()
        stream = odil.iostream(string_io)
        writer = odil.Writer(stream, odil.registry.ExplicitVRLittleEndian)
        writer.write_data_set(data_set)

        self.assertEqual(
            string_io.getvalue(),
            b"\x10\x00\x10\x00" b"PN" b"\x08\x00" b"Foo^Bar "
            b"\x10\x00\x20\x00" b"LO" b"\x04\x00" b"FOO "
        )

    def test_write_tag(self):
        string_io = BytesIO()
        stream = odil.iostream(string_io)
        writer = odil.Writer(stream, odil.registry.ExplicitVRLittleEndian)
        writer.write_tag(odil.registry.PatientID)

        self.assertEqual(string_io.getvalue(), b"\x10\x00\x20\x00")

    def test_write_element(self):
        string_io = BytesIO()
        stream = odil.iostream(string_io)
        writer = odil.Writer(stream, odil.registry.ExplicitVRLittleEndian)
        writer.write_element(odil.Element(["Foo^Bar"], odil.VR.PN))
        self.assertEqual(string_io.getvalue(), b"PN\x08\x00Foo^Bar ")

    def test_write_file(self):
        data_set = odil.DataSet()
        data_set.add("SOPClassUID", ["1.2.3.4"])
        data_set.add("SOPInstanceUID", ["1.2.3.4.5"])
        data_set.add("PatientName", ["Foo^Bar"])

        string_io = BytesIO()
        stream = odil.iostream(string_io)

        odil.Writer.write_file(
            data_set, stream, odil.DataSet(),
            odil.registry.ExplicitVRLittleEndian)

        data = (
            128*b"\0"+b"DICM"+
            b"\x02\x00\x00\x00" b"UL" b"\x04\x00" b"\x80\x00\x00\x00"
            b"\x02\x00\x01\x00" b"OB" b"\x00\x00" b"\x02\x00\x00\x00" b"\x00\x01"
            b"\x02\x00\x02\x00" b"UI" b"\x08\x00" b"1.2.3.4\x00"
            b"\x02\x00\x03\x00" b"UI" b"\x0a\x00" b"1.2.3.4.5\x00"
            b"\x02\x00\x10\x00" b"UI" b"\x14\x00" b"1.2.840.10008.1.2.1\x00"
            b"\x02\x00\x12\x00" b"UI" b"\x1e\x00" b"1.2.826.0.1.3680043.9.55600.0\x00"
            b"\x02\x00\x13\x00" b"SH" b"\x06\x00" b"Odil 0"
            b"\x08\x00\x16\x00" b"UI" b"\x08\x00" b"1.2.3.4\x00"
            b"\x08\x00\x18\x00" b"UI" b"\x0a\x00" b"1.2.3.4.5\x00"
            b"\x10\x00\x10\x00" b"PN" b"\x08\x00" b"Foo^Bar ")

        self.assertEqual(string_io.getvalue(), data)

if __name__ == "__main__":
    unittest.main()
