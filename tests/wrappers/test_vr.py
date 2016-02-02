import unittest

import _odil

class TestVR(unittest.TestCase):
    def test_string(self):
        vr = _odil.VR.AE
        self.assertEqual(str(vr), "AE")

if __name__ == "__main__":
    unittest.main()

