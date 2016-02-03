import unittest

import _odil

class TestDataSet(unittest.TestCase):
    def test_empty_constructor(self):
        data_set = _odil.DataSet()
        self.assertTrue(data_set.empty())

if __name__ == "__main__":
    unittest.main()

