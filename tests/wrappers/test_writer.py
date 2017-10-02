import unittest

try:
    from StringIO import StringIO
except ImportError:
    from io import StringIO

import odil

class TestWriter(unittest.TestCase):
    def test_constructor_1(self):
        stream = odil.iostream(StringIO())
        writer = odil.Writer(stream, odil.ByteOrdering.LittleEndian, False)
        self.assertEqual(writer.byte_ordering, odil.ByteOrdering.LittleEndian)
        self.assertFalse(writer.explicit_vr)
        self.assertEqual(
            writer.item_encoding, odil.Writer.ItemEncoding.ExplicitLength)
        self.assertFalse(writer.use_group_length)

    def test_constructor_2(self):
        stream = odil.iostream(StringIO())
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

        string_io = StringIO()
        stream = odil.iostream(string_io)
        writer = odil.Writer(stream, odil.registry.ExplicitVRLittleEndian)
        writer.write_data_set(data_set)

        self.assertEqual(
            string_io.getvalue(),
            "\x10\x00\x10\x00" "PN" "\x08\x00" "Foo^Bar "
            "\x10\x00\x20\x00" "LO" "\x04\x00" "FOO "
        )

    def test_write_tag(self):
        string_io = StringIO()
        stream = odil.iostream(string_io)
        writer = odil.Writer(stream, odil.registry.ExplicitVRLittleEndian)
        writer.write_tag(odil.registry.PatientID)

        self.assertEqual(string_io.getvalue(), "\x10\x00\x20\x00")

    def test_write_element(self):
        string_io = StringIO()
        stream = odil.iostream(string_io)
        writer = odil.Writer(stream, odil.registry.ExplicitVRLittleEndian)
        writer.write_element(odil.Element(["Foo^Bar"], odil.VR.PN))
        self.assertEqual(string_io.getvalue(), "PN\x08\x00Foo^Bar ")

    def test_write_file(self):
        data_set = odil.DataSet()
        data_set.add("SOPClassUID", ["1.2.3.4"])
        data_set.add("SOPInstanceUID", ["1.2.3.4.5"])
        data_set.add("PatientName", ["Foo^Bar"])

        string_io = StringIO()
        stream = odil.iostream(string_io)

        odil.Writer.write_file(
            data_set, stream, odil.DataSet(),
            odil.registry.ExplicitVRLittleEndian)

        data = (
            128*"\0"+"DICM"+
            "\x02\x00\x00\x00" "UL" "\x04\x00" "\x80\x00\x00\x00"
            "\x02\x00\x01\x00" "OB" "\x00\x00" "\x02\x00\x00\x00" "\x00\x01"
            "\x02\x00\x02\x00" "UI" "\x08\x00" "1.2.3.4\x00"
            "\x02\x00\x03\x00" "UI" "\x0a\x00" "1.2.3.4.5\x00"
            "\x02\x00\x10\x00" "UI" "\x14\x00" "1.2.840.10008.1.2.1\x00"
            "\x02\x00\x12\x00" "UI" "\x1e\x00" "1.2.826.0.1.3680043.9.55600.0\x00"
            "\x02\x00\x13\x00" "SH" "\x06\x00" "Odil 0"
            "\x08\x00\x16\x00" "UI" "\x08\x00" "1.2.3.4\x00"
            "\x08\x00\x18\x00" "UI" "\x0a\x00" "1.2.3.4.5\x00"
            "\x10\x00\x10\x00" "PN" "\x08\x00" "Foo^Bar ")

        self.assertEqual(string_io.getvalue(), data)

if __name__ == "__main__":
    unittest.main()
