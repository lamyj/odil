import unittest

import _odil

class TestUID(unittest.TestCase):
    def test_uid_prefix(self):
        self.assertEqual(_odil.uid_prefix, "1.2.826.0.1.3680043.9.5560")

    def test_uid_prefix(self):
        uid = _odil.generate_uid()
        self.assertEqual(uid[:len(_odil.uid_prefix)], _odil.uid_prefix)

if __name__ == "__main__":
    unittest.main()
