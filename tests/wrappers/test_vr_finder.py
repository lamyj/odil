import unittest

import odil

class TestVRFinder(unittest.TestCase):
    def test_default_finder(self):
        finder = odil.VRFinder()
        data_set = odil.DataSet()
        data_set.add(odil.registry.BitsAllocated, [8])
        vr = finder(
            odil.Tag(0x7fe0, 0x0010), data_set,
            odil.registry.ExplicitVRLittleEndian)
        self.assertEqual(vr, odil.VR.OB)

if __name__ == "__main__":
    unittest.main()
