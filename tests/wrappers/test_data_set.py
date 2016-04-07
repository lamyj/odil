import unittest

import _odil

class TestDataSet(unittest.TestCase):
    def test_empty_constructor(self):
        data_set = _odil.DataSet()
        self.assertTrue(data_set.empty())
        self.assertEqual(data_set.size(), 0)
        self.assertEqual(len(data_set), 0)

    def test_empty_element(self):
        tag = _odil.registry.PatientName
        data_set = _odil.DataSet()
        data_set.add(tag, _odil.Element())

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)
        self.assertEqual(len(data_set), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.INVALID)
        self.assertTrue(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 0)

    def test_empty_element_tag(self):
        tag = _odil.registry.PatientName
        data_set = _odil.DataSet()
        data_set.add(tag)

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)
        self.assertEqual(len(data_set), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.PN)
        self.assertTrue(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 0)

    def test_int_element(self):
        tag = _odil.registry.SelectorUSValue
        value = [1, 2, 3]
        data_set = _odil.DataSet()
        data_set.add(tag, _odil.Value.Integers(value))

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)
        self.assertEqual(len(data_set), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.US)
        self.assertFalse(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 3)
        self.assertTrue(data_set.is_int(tag))
        self.assertEqual([x for x in data_set.as_int(tag)], value)

    def test_real_element(self):
        tag = _odil.registry.SelectorFLValue
        value = [1.1, 2, 3.3]
        data_set = _odil.DataSet()
        data_set.add(tag, _odil.Value.Reals(value))

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)
        self.assertEqual(len(data_set), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.FL)
        self.assertFalse(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 3)
        self.assertTrue(data_set.is_real(tag))
        self.assertEqual([x for x in data_set.as_real(tag)], value)

    def test_string_element(self):
        tag = _odil.registry.SelectorCSValue
        value = ["foo", "bar"]
        data_set = _odil.DataSet()
        data_set.add(tag, _odil.Value.Strings(value))

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)
        self.assertEqual(len(data_set), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.CS)
        self.assertFalse(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 2)
        self.assertTrue(data_set.is_string(tag))
        self.assertEqual([x for x in data_set.as_string(tag)], value)

    def test_data_set_element(self):
        tag = _odil.registry.SelectorCodeSequenceValue
        value = [_odil.DataSet(), _odil.DataSet()]
        data_set = _odil.DataSet()
        data_set.add(
            tag, _odil.Value.DataSets(value))

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)
        self.assertEqual(len(data_set), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.SQ)
        self.assertFalse(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 2)
        self.assertTrue(data_set.is_data_set(tag))
        self.assertEqual([x for x in data_set.as_data_set(tag)], value)

    def test_string_binary(self):
        tag = _odil.registry.RedPaletteColorLookupTableData
        value = [_odil.Value.BinaryItem("\x01\x02")]
        data_set = _odil.DataSet()
        data_set.add(tag, _odil.Value.Binary(value))

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)
        self.assertEqual(len(data_set), 1)

        self.assertEqual(data_set.get_vr(tag), _odil.VR.OW)
        self.assertFalse(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 1)
        self.assertTrue(data_set.is_binary(tag))
        self.assertEqual(
            [x for x in data_set.as_binary(tag)[0]], [x for x in value[0]])

    def test_getitem(self):
        data_set = _odil.DataSet()
        data_set.add(_odil.registry.PatientName, _odil.Value.Strings(["Doe^John"]))
        self.assertEqual(
            [x for x in data_set[_odil.registry.PatientName].as_string()],
            ["Doe^John"])
        self.assertRaises(Exception, lambda x: data_set[_odil.registry.PatientID])

    def test_iter(self):
        data_set = _odil.DataSet()
        data_set.add(_odil.registry.PatientName, _odil.Value.Strings(["Doe^John"]))
        data_set.add(_odil.registry.PatientID, _odil.Value.Strings(["DJ123"]))
        self.assertEqual(
            [x.get_name() for x in data_set],
            ["PatientName", "PatientID"])

    def test_keys(self):
        data_set = _odil.DataSet()
        data_set.add(_odil.registry.PatientName, _odil.Value.Strings(["Doe^John"]))
        data_set.add(_odil.registry.PatientID, _odil.Value.Strings(["DJ123"]))
        self.assertEqual(
            [x.get_name() for x in data_set.keys()],
            ["PatientName", "PatientID"])

    def test_values(self):
        data_set = _odil.DataSet()
        data_set.add(_odil.registry.PatientName, _odil.Value.Strings(["Doe^John"]))
        data_set.add(_odil.registry.PatientID, _odil.Value.Strings(["DJ123"]))
        self.assertEqual(
            [
                [item for item in element.as_string()] 
                for element in data_set.values()],
            [["Doe^John"], ["DJ123"]])

    def test_items(self):
        data_set = _odil.DataSet()
        data_set.add(_odil.registry.PatientName, _odil.Value.Strings(["Doe^John"]))
        data_set.add(_odil.registry.PatientID, _odil.Value.Strings(["DJ123"]))
        self.assertEqual(
            [
                [tag.get_name(), [item for item in element.as_string()]] 
                for tag, element in data_set.items()],
            [["PatientName", ["Doe^John"]], ["PatientID", ["DJ123"]]])

if __name__ == "__main__":
    unittest.main()

