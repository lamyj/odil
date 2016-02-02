import unittest

import _odil

class TestElement(unittest.TestCase):
    def test_empty_constructor(self):
        element = _odil.Element()
        self.assertTrue(element.empty())
        self.assertEqual(element.vr, _odil.VR.INVALID)

    def test_integers_constructor(self):
        items = [1, 2, 3]
        element = _odil.Element(_odil.Value.Integers(items), _odil.VR.US)
        self.assertEqual([x for x in element.as_int()], items)
        self.assertEqual(element.vr, _odil.VR.US)

    def test_reals_constructor(self):
        items = [1.1, 2, 3.3]
        element = _odil.Element(_odil.Value.Reals(items), _odil.VR.FL)
        self.assertEqual([x for x in element.as_real()], items)
        self.assertEqual(element.vr, _odil.VR.FL)

    def test_strings_constructor(self):
        items = ["foo", "bar"]
        element = _odil.Element(_odil.Value.Strings(items), _odil.VR.CS)
        self.assertEqual([x for x in element.as_string()], items)
        self.assertEqual(element.vr, _odil.VR.CS)

    def test_data_sets_constructor(self):
        items = [_odil.DataSet(), _odil.DataSet()]
        element = _odil.Element(_odil.Value.DataSets(items), _odil.VR.SQ)
        self.assertEqual([x for x in element.as_data_set()], items)
        self.assertEqual(element.vr, _odil.VR.SQ)

    def test_binary_constructor(self):
        items = "\x01\x02\x03"
        element = _odil.Element(_odil.Value.Binary(items), _odil.VR.OB)
        self.assertEqual(
            [x for x in element.as_binary()], [ord(x) for x in items])
        self.assertEqual(element.vr, _odil.VR.OB)

if __name__ == "__main__":
    unittest.main()
