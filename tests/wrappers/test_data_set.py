import unittest

import _odil

class TestDataSet(unittest.TestCase):
    def test_empty_constructor(self):
        data_set = _odil.DataSet()
        self.assertTrue(data_set.empty())
        self.assertEqual(data_set.size(), 0)

    def test_empty_element(self):
        tag = _odil.Tag("PatientName")
        data_set = _odil.DataSet()
        data_set.add(tag, _odil.Element())

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.INVALID)
        self.assertTrue(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 0)

    def test_empty_element_tag(self):
        tag = _odil.Tag("PatientName")
        data_set = _odil.DataSet()
        data_set.add(tag)

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.PN)
        self.assertTrue(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 0)

    def test_int_element(self):
        tag = _odil.Tag("SelectorUSValue")
        data_set = _odil.DataSet()
        data_set.add(tag, _odil.Value.Integers([1,2,3]))

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.US)
        self.assertFalse(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 3)

    def test_real_element(self):
        tag = _odil.Tag("SelectorFLValue")
        data_set = _odil.DataSet()
        data_set.add(tag, _odil.Value.Reals([1.1, 2, 3.3]))

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.FL)
        self.assertFalse(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 3)

    def test_string_element(self):
        tag = _odil.Tag("SelectorCSValue")
        data_set = _odil.DataSet()
        data_set.add(tag, _odil.Value.Strings(["foo", "bar"]))

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.CS)
        self.assertFalse(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 2)

    def test_data_set_element(self):
        tag = _odil.Tag("SelectorCodeSequenceValue")
        data_set = _odil.DataSet()
        data_set.add(
            tag, _odil.Value.DataSets([_odil.DataSet(), _odil.DataSet()]))

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.SQ)
        self.assertFalse(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 2)

    def test_string_binary(self):
        tag = _odil.Tag("RedPaletteColorLookupTableData")
        data_set = _odil.DataSet()
        data_set.add(tag, _odil.Value.Binary("\x01\x02"))

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.OW)
        self.assertFalse(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 2)

if __name__ == "__main__":
    unittest.main()

