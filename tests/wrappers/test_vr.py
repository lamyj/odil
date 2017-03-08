import unittest

import odil

class TestVR(unittest.TestCase):
    def test_string_constructor(self):
        data_set = odil.DataSet()
        data_set.add(odil.registry.PatientName, ["Doe^John"], "UT")
        self.assertEqual(data_set.get_vr(odil.registry.PatientName), odil.VR.UT)

    def test_unicode_constructor(self):
        data_set = odil.DataSet()
        data_set.add(odil.registry.PatientName, ["Doe^John"], u"UT")
        self.assertEqual(data_set.get_vr(odil.registry.PatientName), odil.VR.UT)

    def test_invalid_string_constructor(self):
        data_set = odil.DataSet()
        with self.assertRaises(Exception):
            data_set.add(odil.registry.PatientName, ["Doe^John"], "XX")

    def test_invalid_unicode_constructor(self):
        data_set = odil.DataSet()
        with self.assertRaises(Exception):
            data_set.add(odil.registry.PatientName, ["Doe^John"], u"XX")

    def test_string(self):
        vr = odil.VR.AE
        self.assertEqual(str(vr), "AE")

if __name__ == "__main__":
    unittest.main()

