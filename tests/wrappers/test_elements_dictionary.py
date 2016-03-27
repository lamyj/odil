import unittest

import _odil

class TestElementsDictionaryKey(unittest.TestCase):
    def test_empty_constructor(self):
        key = _odil.ElementsDictionaryKey()
    
    def test_tag_constructor(self):
        key = _odil.ElementsDictionaryKey(_odil.registry.PatientName)
    
    def test_string_constructor(self):
        key = _odil.ElementsDictionaryKey("60xx0010")

class TestElementsDictionaryEntry(unittest.TestCase):
    def test_constructor(self):
        entry = _odil.ElementsDictionaryEntry(
            "Patient's Name", "PatientName", "PN", "1")
        self.assertEqual(entry.name, "Patient's Name")
        self.assertEqual(entry.keyword, "PatientName")
        self.assertEqual(entry.vr, "PN")
        self.assertEqual(entry.vm, "1")

class TestElementsDictionary(unittest.TestCase):
    def test_contains(self):
        self.assertTrue(
            _odil.registry.PatientName in _odil.registry.public_dictionary)
        self.assertFalse(
            _odil.Tag(0x0001, 0x0001) in _odil.registry.public_dictionary)
        self.assertTrue("60xx0010" in _odil.registry.public_dictionary)
        self.assertFalse("foo" in _odil.registry.public_dictionary)
    
    def test_get_item_tag(self):
        entry = _odil.registry.public_dictionary[_odil.registry.PatientName]
        self.assertEqual(entry.name, "Patient's Name")
        self.assertEqual(entry.keyword, "PatientName")
        self.assertEqual(entry.vr, "PN")
        self.assertEqual(entry.vm, "1")
    
    def test_get_item_string(self):
        entry = _odil.registry.public_dictionary["60xx0010"]
        self.assertEqual(entry.name, "Overlay Rows")
        self.assertEqual(entry.keyword, "OverlayRows")
        self.assertEqual(entry.vr, "US")
        self.assertEqual(entry.vm, "1")

if __name__ == "__main__":
    unittest.main()
