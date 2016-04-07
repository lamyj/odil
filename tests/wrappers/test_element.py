import unittest

import _odil

class TestElement(unittest.TestCase):
    def test_empty_constructor(self):
        element = _odil.Element()
        self.assertTrue(element.empty())
        self.assertEqual(element.size(), 0)
        self.assertEqual(len(element), 0)
        self.assertEqual(element.vr, _odil.VR.INVALID)

    def test_integers_constructor(self):
        items = [1, 2, 3]
        element = _odil.Element(_odil.Value.Integers(items), _odil.VR.US)
        self.assertEqual([x for x in element.as_int()], items)
        self.assertEqual(element.vr, _odil.VR.US)
        self.assertEqual(element.size(), 3)
        self.assertEqual(len(element), 3)

    def test_reals_constructor(self):
        items = [1.1, 2, 3.3]
        element = _odil.Element(_odil.Value.Reals(items), _odil.VR.FL)
        self.assertEqual([x for x in element.as_real()], items)
        self.assertEqual(element.vr, _odil.VR.FL)
        self.assertEqual(element.size(), 3)
        self.assertEqual(len(element), 3)

    def test_strings_constructor(self):
        items = ["foo", "bar"]
        element = _odil.Element(_odil.Value.Strings(items), _odil.VR.CS)
        self.assertEqual([x for x in element.as_string()], items)
        self.assertEqual(element.vr, _odil.VR.CS)
        self.assertEqual(element.size(), 2)
        self.assertEqual(len(element), 2)

    def test_data_sets_constructor(self):
        items = [_odil.DataSet(), _odil.DataSet()]
        element = _odil.Element(_odil.Value.DataSets(items), _odil.VR.SQ)
        self.assertEqual([x for x in element.as_data_set()], items)
        self.assertEqual(element.vr, _odil.VR.SQ)
        self.assertEqual(element.size(), 2)
        self.assertEqual(len(element), 2)

    def test_binary_constructor(self):
        items = [_odil.Value.BinaryItem("\x01\x02\x03")]
        element = _odil.Element(_odil.Value.Binary(items), _odil.VR.OB)
        self.assertEqual(
            [x for x in element.as_binary()[0]], [x for x in items[0]])
        self.assertEqual(element.vr, _odil.VR.OB)
        self.assertEqual(element.size(), 1)
        self.assertEqual(len(element), 1)

if __name__ == "__main__":
    unittest.main()
