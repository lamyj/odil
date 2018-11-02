import unittest

import odil

class TestVR(unittest.TestCase):
    def test_bytes_constructor(self):
        vr = odil.VR(b"UT")
        self.assertEqual(vr, odil.VR.UT)

    def test_unicode_constructor(self):
        vr = odil.VR(u"UT")
        self.assertEqual(vr, odil.VR.UT)

    def test_invalid_bytes_constructor(self):
        with self.assertRaises(Exception):
            odil.VR(b"XX")

    def test_invalid_unicode_constructor(self):
        with self.assertRaises(Exception):
            odil.VR(u"XX")

    def test_string(self):
        vr = odil.VR.AE
        self.assertEqual(str(vr), "AE")

if __name__ == "__main__":
    unittest.main()

