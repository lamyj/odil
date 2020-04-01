import pickle
import unittest

import odil

class TestDataSet(unittest.TestCase):
    def test_empty_constructor(self):
        data_set = odil.DataSet()
        self.assertTrue(data_set.empty())
        self.assertEqual(data_set.size(), 0)
        self.assertEqual(len(data_set), 0)
        self.assertEqual(len(data_set.get_transfer_syntax()), 0)

    def test_transfer_syntax_constructor(self):
        data_set = odil.DataSet(odil.registry.ExplicitVRLittleEndian)
        self.assertEqual(
            data_set.get_transfer_syntax().encode(),
            odil.registry.ExplicitVRLittleEndian)
    
    def test_kwargs_constructor(self):
        data_set = odil.DataSet(
            PatientName=["Doe^John"], PatientWeight=[70],
             ReferencedStudySequence=[
                odil.DataSet(StudyInstanceUID=["1.2.3"])
            ])
        
        self.assertEqual(data_set.size(), 3)
        
        self._test_element_value(
            data_set, "PatientName", [b"Doe^John"], 
            odil.DataSet.is_string, odil.DataSet.as_string)
        self._test_element_value(
            data_set, "PatientWeight", [70], 
            odil.DataSet.is_int, odil.DataSet.as_int)
        self._test_element_value(
            data_set, "ReferencedStudySequence", [
               odil.DataSet(StudyInstanceUID=["1.2.3"])
            ], 
            odil.DataSet.is_data_set, odil.DataSet.as_data_set)
        
        with self.assertRaises(odil.Exception):
            odil.DataSet(FooBar=["foo"])
    
    def test_transfer_syntax(self):
        data_set = odil.DataSet()
        data_set.set_transfer_syntax(odil.registry.ExplicitVRLittleEndian)
        self.assertEqual(
            data_set.get_transfer_syntax().encode(),
            odil.registry.ExplicitVRLittleEndian)

    def test_empty_element_tag(self):
        tag = odil.registry.PatientName
        data_set = odil.DataSet()
        data_set.add(tag)

        self.assertFalse(data_set.empty())
        self.assertEqual(data_set.size(), 1)
        self.assertEqual(len(data_set), 1)

        self.assertEqual(data_set.get_vr(tag), odil.VR.PN)
        self.assertTrue(data_set.empty(tag))
        self.assertEqual(data_set.size(tag), 0)

    def _test_sequences(self, odil_contents, python_contents):
        if python_contents and isinstance(python_contents[0], bytearray):
            self.assertSequenceEqual(
                [bytearray([x for x in item]) for item in odil_contents], 
                python_contents)
        else:
            self.assertSequenceEqual(list(odil_contents), list(python_contents))

    def _test_element_value(
            self, data_set, tag, contents, type_check, accessor):
        self.assertTrue(data_set.has(tag))
        self.assertEqual(data_set.empty(tag), len(contents)==0)
        self.assertEqual(data_set.size(tag), len(contents))
        self.assertTrue(type_check(data_set, tag))
        self._test_sequences(accessor(data_set, tag), contents)

        if not data_set.is_int(tag):
            with self.assertRaises(odil.Exception):
                data_set.as_int(tag)
        if not data_set.is_real(tag):
            with self.assertRaises(odil.Exception):
                data_set.as_real(tag)
        if not data_set.is_string(tag):
            with self.assertRaises(odil.Exception):
                data_set.as_string(tag)
        if not data_set.is_data_set(tag):
            with self.assertRaises(odil.Exception):
                data_set.as_data_set(tag)
        if not data_set.is_binary(tag):
            with self.assertRaises(odil.Exception):
                data_set.as_binary(tag)

    def _test_implicit_container(
            self, tag, empty_content, type_check, accessor):

        # Implicit empty content
        data_set = odil.DataSet()
        data_set.add(tag)
        self._test_element_value(
            data_set, tag, empty_content, type_check, accessor)

        # Explicit empty content
        data_set = odil.DataSet()
        data_set.add(tag, empty_content)
        self._test_element_value(
            data_set, tag, empty_content, type_check, accessor)

    def _test_container_no_vr(self, tag, contents, type_check, accessor):
        data_set = odil.DataSet()
        data_set.add(tag, contents)
        self._test_element_value(data_set, tag, contents, type_check, accessor)

    def _test_container_vr(self, tag, contents, vr, type_check, accessor):
        data_set = odil.DataSet()
        data_set.add(tag, contents, vr)
        self._test_element_value(data_set, tag, contents, type_check, accessor)

    def _test_modify(self, tag, contents, accessor):
        data_set = odil.DataSet()
        data_set.add(tag, [contents[0]])
        if isinstance(contents[0], bytearray):
            accessor(data_set, tag).append(
                odil.Value.BinaryItem(contents[1]))
        else:
            accessor(data_set, tag).append(contents[1])
        self._test_sequences(accessor(data_set, tag), contents)

    def _test_clear(self, tag, contents, type_check):
        data_set = odil.DataSet()
        data_set.add(tag, contents)
        data_set.clear(tag)
        self.assertTrue(type_check(data_set, tag))
        self.assertTrue(data_set.empty(tag))

    def _test_item(self, tag, contents, type_check, accessor):
        data_set = odil.DataSet()
        data_set.add(tag, contents)

        self._test_sequences(accessor(data_set[tag]), contents)

        data_set[tag] = odil.Element(contents[:1], data_set.get_vr(tag))
        self._test_sequences(accessor(data_set[tag]), contents[:1])

    def _test_element(
            self, tag, empty_content, contents, vr,
            data_set_type_check, data_set_accessor,
            element_type_check, element_accessor):
        self._test_implicit_container(
            tag, empty_content, data_set_type_check, data_set_accessor)

        self._test_container_no_vr(
            tag, contents, data_set_type_check, data_set_accessor)
        self._test_container_vr(
            tag, contents, vr, data_set_type_check, data_set_accessor)

        self._test_modify(tag, contents, data_set_accessor)

        self._test_clear(tag, contents, data_set_type_check)

        self._test_item(tag, contents, element_type_check, element_accessor)

    def test_int(self):
        self._test_element(
            odil.registry.Rows, odil.Value.Integers(), [1234, 5678], odil.VR.US,
            odil.DataSet.is_int, odil.DataSet.as_int,
            odil.Element.is_int, odil.Element.as_int)

    def test_real(self):
        self._test_element(
            odil.registry.SpacingBetweenSlices, odil.Value.Reals(), 
            [12.34, 56.78], odil.VR.FL,
            odil.DataSet.is_real, odil.DataSet.as_real,
            odil.Element.is_real, odil.Element.as_real)
    
    def test_real_string(self):
        self._test_element(
            odil.registry.FieldOfViewOrigin, odil.Value.Reals(), 
            [12.34, 56.78], odil.VR.DS,
            odil.DataSet.is_real, odil.DataSet.as_real,
            odil.Element.is_real, odil.Element.as_real)

    def test_string(self):
        self._test_element(
            odil.registry.PatientID, odil.Value.Strings(), [b"foo", b"bar"],
            odil.VR.LT,
            odil.DataSet.is_string, odil.DataSet.as_string,
            odil.Element.is_string, odil.Element.as_string)

    def test_data_set(self):
        data_set_1 = odil.DataSet()
        data_set_1.add("PatientID", ["DJ1234"])
    
        data_set_2 = odil.DataSet()
        data_set_2.add("EchoTime", [100])

        self._test_element(
            odil.registry.ReferencedStudySequence, odil.Value.DataSets(), 
            [data_set_1, data_set_2], odil.VR.SQ,
            odil.DataSet.is_data_set, odil.DataSet.as_data_set,
            odil.Element.is_data_set, odil.Element.as_data_set)

    def test_binary(self):
        self._test_element(
            odil.registry.BadPixelImage, odil.Value.Binary(), 
            [bytearray([0x01, 0x02]), bytearray([0x03])], odil.VR.OB,
            odil.DataSet.is_binary, odil.DataSet.as_binary,
            odil.Element.is_binary, odil.Element.as_binary)

    def test_getitem(self):
        data_set = odil.DataSet()
        data_set.add("PatientName", ["Doe^John"])
        self.assertSequenceEqual(
            data_set["PatientName"].as_string(), [b"Doe^John"])
        self.assertRaises(Exception, lambda x: data_set["PatientID"])
    
    def test_delitem(self):
        data_set = odil.DataSet()
        data_set.add("PatientName", ["Doe^John"])
        del data_set[odil.registry.PatientName]
        self.assertTrue(data_set.empty())
        
        data_set = odil.DataSet()
        data_set.add("PatientName", ["Doe^John"])
        del data_set["PatientName"]
        self.assertTrue(data_set.empty())
    
    def test_contains(self):
        data_set = odil.DataSet()
        data_set.add("PatientName", ["Doe^John"])
        self.assertTrue("PatientName" in data_set)
        self.assertTrue(odil.registry.PatientName in data_set)
        self.assertTrue("PatientID" not in data_set)
        self.assertTrue(odil.registry.PatientID not in data_set)
    
    def test_get(self):
        data_set = odil.DataSet()
        data_set.add("PatientName", ["Doe^John"])
        
        self.assertSequenceEqual(
            data_set.get(odil.registry.PatientName).as_string(), [b"Doe^John"])
        self.assertSequenceEqual(
            data_set.get("PatientName").as_string(), [b"Doe^John"])
        
        self.assertEqual(data_set.get(odil.registry.PatientID), None)
        self.assertEqual(data_set.get("PatientID"), None)
        
        self.assertEqual(data_set.get(odil.registry.PatientID, 123), 123)
        self.assertEqual(data_set.get("PatientID", 123), 123)
        
    def test_iter(self):
        data_set = odil.DataSet()
        data_set.add("PatientName", ["Doe^John"])
        data_set.add("PatientID", ["DJ123"])
        self.assertEqual(
            [x.get_name() for x in data_set],
            ["PatientName", "PatientID"])

    def test_keys(self):
        data_set = odil.DataSet()
        data_set.add("PatientName", ["Doe^John"])
        data_set.add("PatientID", ["DJ123"])
        self.assertEqual(
            [x.get_name() for x in data_set.keys()],
            ["PatientName", "PatientID"])
        self.assertEqual(
            [x.get_name() for x in list(data_set)],
            ["PatientName", "PatientID"])
        self.assertEqual(
            [x.get_name() for x in data_set],
            ["PatientName", "PatientID"])

    def test_values(self):
        data_set = odil.DataSet()
        data_set.add("PatientName", ["Doe^John"])
        data_set.add("PatientID", ["DJ123"])
        self.assertEqual(
            [
                [item for item in element.as_string()]
                for element in data_set.values()],
            [[b"Doe^John"], [b"DJ123"]])

    def test_items(self):
        data_set = odil.DataSet()
        data_set.add("PatientName", ["Doe^John"])
        data_set.add("PatientID", ["DJ123"])
        self.assertSequenceEqual(
            [
                [tag.get_name(), [item for item in element.as_string()]]
                for tag, element in data_set.items()],
            [["PatientName", [b"Doe^John"]], ["PatientID", [b"DJ123"]]])
    
    def test_update(self):
        data_set = odil.DataSet()
        data_set.add("PatientName", ["Doe^John"])
        data_set.add("PatientSex", ["M"])
        
        other = odil.DataSet()
        data_set.add("PatientName", ["Bloggs^Joe"])
        other.add("PatientID", ["BJ123"])
        other.add("IssuerOfPatientID", ["Hospital"])
        
        data_set.update(other)
        
        self.assertSequenceEqual(
            [
                [tag.get_name(), [item for item in element.as_string()]]
                for tag, element in data_set.items()],
            [
                ["PatientName", [b"Bloggs^Joe"]], ["PatientID", [b"BJ123"]],
                ["IssuerOfPatientID", [b"Hospital"]], ["PatientSex", [b"M"]]])
    
    def test_pickle(self):
        data_set = odil.DataSet()
        data_set.add("PatientName", ["Doe^John"])
        data_set.add("PatientID", ["DJ123"])
        self.assertEqual(pickle.loads(pickle.dumps(data_set)), data_set)

if __name__ == "__main__":
    unittest.main()
