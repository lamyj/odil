import unittest

import odil

class TestElement(unittest.TestCase):
    def test_empty_constructor(self):
        element = odil.Element()
        self.assertTrue(element.empty())
        self.assertEqual(element.size(), 0)
        self.assertEqual(len(element), 0)
        self.assertEqual(element.vr, odil.VR.INVALID)

    def test_integers_constructor(self):
        items = [1, 2, 3]
        element = odil.Element(odil.Value.Integers(items), odil.VR.US)
        self.assertEqual([x for x in element.as_int()], items)
        self.assertEqual(element.vr, odil.VR.US)
        self.assertEqual(element.size(), 3)
        self.assertEqual(len(element), 3)

    def test_reals_constructor(self):
        items = [1.1, 2, 3.3]
        element = odil.Element(odil.Value.Reals(items), odil.VR.FL)
        self.assertEqual([x for x in element.as_real()], items)
        self.assertEqual(element.vr, odil.VR.FL)
        self.assertEqual(element.size(), 3)
        self.assertEqual(len(element), 3)

    def test_strings_constructor(self):
        items = ["foo", "bar"]
        element = odil.Element(odil.Value.Strings(items), odil.VR.CS)
        self.assertEqual([x for x in element.as_string()], items)
        self.assertEqual(element.vr, odil.VR.CS)
        self.assertEqual(element.size(), 2)
        self.assertEqual(len(element), 2)

    def test_data_sets_constructor(self):
        items = [odil.DataSet(), odil.DataSet()]
        element = odil.Element(odil.Value.DataSets(items), odil.VR.SQ)
        self.assertEqual([x for x in element.as_data_set()], items)
        self.assertEqual(element.vr, odil.VR.SQ)
        self.assertEqual(element.size(), 2)
        self.assertEqual(len(element), 2)

    def test_binary_constructor(self):
        items = [odil.Value.BinaryItem("\x01\x02\x03")]
        element = odil.Element(odil.Value.Binary(items), odil.VR.OB)
        self.assertEqual(
            [x for x in element.as_binary()[0]], [x for x in items[0]])
        self.assertEqual(element.vr, odil.VR.OB)
        self.assertEqual(element.size(), 1)
        self.assertEqual(len(element), 1)

if __name__ == "__main__":
    unittest.main()
