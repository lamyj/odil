import unittest

import _odil

class TestRegistry(unittest.TestCase):
    def test_attribute(self):
        tag = _odil.registry.PatientID
        self.assertEqual(tag.group, 0x0010)
        self.assertEqual(tag.element, 0x0020)

    def test_public_dictionary(self):
        tag = _odil.registry.PatientID
        self.assertTrue(tag in _odil.registry.public_dictionary)
        entry = _odil.registry.public_dictionary[tag]
        self.assertEqual(entry.name, "Patient ID")
        self.assertEqual(entry.keyword, "PatientID")
        self.assertEqual(entry.vr, "LO")
        self.assertEqual(entry.vm, "1")

if __name__ == "__main__":
    unittest.main()
