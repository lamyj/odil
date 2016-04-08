import unittest

import odil

class TestUIDsDictionaryEntry(unittest.TestCase):
    def test_constructor(self):
        entry = odil.UIDsDictionaryEntry(
            "MR Image Storage", "MRImageStorage",  "SOP Class")
        self.assertEqual(entry.name, "MR Image Storage")
        self.assertEqual(entry.keyword, "MRImageStorage")
        self.assertEqual(entry.type, "SOP Class")

class TestUIDsDictionary(unittest.TestCase):
    def test_get_item(self):
        entry = odil.registry.uids_dictionary["1.2.840.10008.5.1.4.1.1.4"]
        self.assertEqual(entry.name, "MR Image Storage")
        self.assertEqual(entry.keyword, "MRImageStorage")
        self.assertEqual(entry.type, "SOP Class")

if __name__ == "__main__":
    unittest.main()
