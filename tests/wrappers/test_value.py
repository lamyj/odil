#encoding: utf-8
import pickle
import unittest

import odil

class TestValue(unittest.TestCase):
    def _test_sequences(self, odil_contents, python_contents):
        self.assertEqual(len(odil_contents), len(python_contents))

        if python_contents and isinstance(python_contents[0], bytearray):
            self.assertSequenceEqual(
                [bytearray([x for x in item]) for item in odil_contents], 
                python_contents)

            # Access from start
            self.assertEqual(bytearray(odil_contents[0]), python_contents[0])

            # Access from end
            self.assertEqual(bytearray(odil_contents[-1]), python_contents[-1])

            # Slice
            self.assertSequenceEqual(
                [bytearray([x for x in item]) for item in odil_contents[0:-1]],
                python_contents[0:-1])
        else:
            self.assertSequenceEqual(list(odil_contents), list(python_contents))

            if python_contents:
                # Access from start
                self.assertEqual(odil_contents[0], python_contents[0])

                # Access from end
                self.assertEqual(odil_contents[-1], python_contents[-1])

                # Slice
                self.assertSequenceEqual(odil_contents[0:-1], python_contents[0:-1])
        
    def _test_contents(self, value, contents, type_, accessor):
        self.assertEqual(value.type, type_)
        self.assertEqual(value.empty(), len(contents) == 0)
        self.assertEqual(value.size(), len(contents))
        self.assertEqual(len(value), len(contents))
        self._test_sequences(accessor(value), contents)

        if type_ != odil.Value.Type.Integers:
            with self.assertRaises(odil.Exception):
                value.as_integers()
        if type_ != odil.Value.Type.Reals:
            with self.assertRaises(odil.Exception):
                value.as_reals()
        if type_ != odil.Value.Type.Strings:
            with self.assertRaises(odil.Exception):
                value.as_strings()
        if type_ != odil.Value.Type.DataSets:
            with self.assertRaises(odil.Exception):
                value.as_data_sets()
        if type_ != odil.Value.Type.Binary:
            with self.assertRaises(odil.Exception):
                value.as_binary()

    def _test_container(self, contents, type_, accessor):
        value = odil.Value(contents)
        self._test_contents(value, contents, type_, accessor)

    def _test_modify(self, contents, accessor):
        value = odil.Value([contents[0]])
        if isinstance(contents[0], bytearray):
            accessor(value).append(odil.Value.BinaryItem(contents[1]))
        else:
            accessor(value).append(contents[1])
        
        self._test_sequences(accessor(value), contents)

    def _test_clear(self, contents, type_):
        value = odil.Value(contents)
        value.clear()
        self.assertEqual(value.type, type_)
        self.assertTrue(value.empty())

    def _test_equality(self, contents_1, contents_2):
        value_1 = odil.Value(contents_1)
        value_2 = odil.Value(contents_1)
        value_3 = odil.Value(contents_2)
        value_4 = odil.Value(contents_2)

        self.assertTrue(value_1 == value_2)
        self.assertFalse(value_1 == value_3)
        self.assertFalse(value_1 == value_4)

        self.assertFalse(value_1 != value_2)
        self.assertTrue(value_1 != value_3)
        self.assertTrue(value_1 != value_4)
    
    def _test_iteration(self, contents, accessor):
        value = odil.Value(contents)
        if value.type == odil.Value.Type.Binary:
            self.assertSequenceEqual(
                [bytearray([x for x in item]) for item in value], contents)
        else:
            self.assertSequenceEqual([x for x in value], contents)
    
    def _test_pickle(self, contents, accessor):
        value = odil.Value(contents)
        self.assertSequenceEqual(
            accessor(pickle.loads(pickle.dumps(value))), accessor(value))
    
    def _test(self, empty_content, contents, other_contents, type_, accessor):
        self._test_container(empty_content, type_, accessor)
        self._test_container(contents, type_, accessor)
        self._test_modify(contents, accessor)
        self._test_clear(contents, type_)
        self._test_equality(contents, other_contents)
        self._test_iteration(contents, accessor)
        self._test_pickle(contents, accessor)

    def test_integers(self):
        self._test(
            odil.Value.Integers(), [1234, 5678], [9012, 3456], 
            odil.Value.Type.Integers, odil.Value.as_integers)
        
    def test_reals(self):
        self._test(
            odil.Value.Reals(), [12.34, 56.78], [1., 2.],
            odil.Value.Type.Reals, odil.Value.as_reals)

    def test_strings(self):
        self._test(
            odil.Value.Strings(), [b"foo", b"bar"], [b"plip", b"plop"],
            odil.Value.Type.Strings, odil.Value.as_strings)

    # FIXME: strings in DICOM are byte-string, with some VR requiring 
    # conversion based on Specific Character Set. In Boost.Python, some
    # explicit conversion are used (unicode <-> std::string in Python 3).

    def test_data_sets(self):
        data_set_1 = odil.DataSet()
        data_set_1.add("PatientID", ["DJ1234"])
    
        data_set_2 = odil.DataSet()
        data_set_2.add("EchoTime", [100])

        self._test(
            odil.Value.DataSets(), 
            [data_set_1, data_set_2], [data_set_2, data_set_1],
            odil.Value.Type.DataSets, odil.Value.as_data_sets)

    def test_binary(self):
        self._test(
            odil.Value.Binary(), 
            [bytearray([0x01, 0x02]), bytearray([0x03])],
            [bytearray([0x04]), bytearray([0x05, 0x06])],
            odil.Value.Type.Binary, odil.Value.as_binary)
        
    def test_unknown_constructor(self):
        class Foo(object): pass
        items = [Foo()]
        with self.assertRaises(odil.Exception):
            odil.Value(items)

class TestValueIntegers(unittest.TestCase):
    def test_empty_constructor(self):
        data = odil.Value.Integers()
        self.assertEqual([x for x in data], [])

    def test_sequence_constructor(self):
        items = [1, 2, 3]
        data = odil.Value.Integers(items)
        self.assertEqual([x for x in data], items)

class TestValueReals(unittest.TestCase):
    def test_empty_constructor(self):
        data = odil.Value.Reals()
        self.assertEqual([x for x in data], [])

    def test_sequence_constructor(self):
        items = [1.1, 2, 3.3]
        data = odil.Value.Reals(items)
        self.assertEqual([x for x in data], items)

class TestValueStrings(unittest.TestCase):
    def test_empty_constructor(self):
        data = odil.Value.Strings()
        self.assertEqual([x for x in data], [])

    def test_sequence_constructor(self):
        items = [b"foo", b"bar"]
        data = odil.Value.Strings(items)
        self.assertEqual([x for x in data], items)

class TestValueDataSets(unittest.TestCase):
    def test_empty_constructor(self):
        data = odil.Value.DataSets()
        self.assertEqual([x for x in data], [])

    def test_sequence_constructor(self):
        items = [odil.DataSet(), odil.DataSet()]
        data = odil.Value.DataSets(items)
        self.assertEqual([x for x in data], items)

class TestValueBinary(unittest.TestCase):
    def test_empty_constructor(self):
        data = odil.Value.Binary()
        self.assertEqual([x for x in data], [])

    def test_sequence_constructor(self):
        items = [odil.Value.BinaryItem([1, 2, 3])]
        data = odil.Value.Binary(items)
        self.assertEqual([x for x in data[0]], [x for x in items[0]])

    def test_buffer(self):
        item = odil.Value.BinaryItem([1, 2, 3])
        memory_view = item.get_memory_view()
        self.assertTrue(isinstance(memory_view, memoryview))


if __name__ == "__main__":
    unittest.main()
