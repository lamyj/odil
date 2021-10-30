import unittest

import odil

class TestRegistry(unittest.TestCase):
    def test_attribute(self):
        tag = odil.registry.PatientID
        self.assertEqual(tag.group, 0x0010)
        self.assertEqual(tag.element, 0x0020)

    def test_public_dictionary_tag(self):
        tag = odil.registry.PatientID
        self.assertTrue(tag in odil.registry.public_dictionary)
        entry = odil.registry.public_dictionary[tag]
        self.assertEqual(entry.name, "Patient ID")
        self.assertEqual(entry.keyword, "PatientID")
        self.assertEqual(entry.vr, "LO")
        self.assertEqual(entry.vm, "1")
    
    def test_public_dictionary_string(self):
        string = "60xx0010"
        self.assertTrue(string in odil.registry.public_dictionary)
        entry = odil.registry.public_dictionary[string]
        self.assertEqual(entry.name, "Overlay Rows")
        self.assertEqual(entry.keyword, "OverlayRows")
        self.assertEqual(entry.vr, "US")
        self.assertEqual(entry.vm, "1")

    def test_uids_dictionary(self):
        uid = "1.2.840.10008.1.2.1"
        self.assertTrue(uid in odil.registry.uids_dictionary)
        entry = odil.registry.uids_dictionary[uid]
        self.assertEqual(entry.name, "Explicit VR Little Endian")
        self.assertEqual(entry.keyword, "ExplicitVRLittleEndian")
        self.assertEqual(entry.type, "Transfer Syntax")

if __name__ == "__main__":
    unittest.main()
