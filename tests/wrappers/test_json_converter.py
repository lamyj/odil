import re
import unittest

import odil

class TestJSONConverter(unittest.TestCase):
    def setUp(self):
        self.data_set = odil.DataSet()
        self.data_set.add("PatientName", ["Foo^Bar"])

        self.json = """{"00100010":{"Value":[{"Alphabetic":"Foo^Bar"}],"vr":"PN"}}"""

    def test_ugly_print(self):
        serialized = odil.as_json(self.data_set, False)
        self.assertEqual(re.sub(r"\s+", "", serialized), self.json)

    def test_pretty_print(self):
        serialized = odil.as_json(self.data_set, True)
        self.assertEqual(re.sub(r"\s+", "", serialized), self.json)

    def test_as_dataset(self):
        data_set = odil.from_json(self.json)
        self.assertTrue(data_set == self.data_set)

if __name__ == "__main__":
    unittest.main()
