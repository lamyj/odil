import re
import unittest

import odil

class TestXMLConverter(unittest.TestCase):
    def setUp(self):
        self.data_set = odil.DataSet()
        self.data_set.add("PatientName", ["Foo^Bar"])

        self.xml = (
            """<?xml version="1.0" encoding="utf-8"?>"""
              "<NativeDicomModel>"
                """<DicomAttribute vr="PN" tag="00100010" keyword="PatientName">"""
                  """<PersonName number="1">"""
                    "<Alphabetic>"
                      "<FamilyName>Foo</FamilyName>"
                      "<GivenName>Bar</GivenName>"
                    "</Alphabetic>"
                  "</PersonName>"
                "</DicomAttribute>"
              "</NativeDicomModel>"
            )

    def test_ugly_print(self):
        serialized = odil.as_xml(self.data_set, False)
        self.assertEqual(re.sub(r"\n+", "", serialized), self.xml)

    def test_pretty_print(self):
        serialized = odil.as_xml(self.data_set, True)
        serialized = re.sub(r"\n\s+", "\n", serialized, re.M)
        serialized = re.sub(r"\n", "", serialized)
        self.assertEqual(serialized, self.xml)

    def test_as_dataset(self):
        data_set = odil.from_xml(self.xml)
        self.assertTrue(data_set == self.data_set)

if __name__ == "__main__":
    unittest.main()
