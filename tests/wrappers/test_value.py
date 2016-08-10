import unittest

import odil

class TestValue(unittest.TestCase):
    def test_empty_constructor(self):
        value = odil.Value()
        self.assertEqual(value.type, odil.Value.Type.Empty)
        self.assertTrue(value.empty)
        
    def test_integers_constructor(self):
        items = [1, 2, 3]
        value = odil.Value(items)
        self.assertEqual(value.type, odil.Value.Type.Integers)
        self.assertSequenceEqual(value.as_integers(), items)
    
    def test_reals_constructor(self):
        items = [1.1, 2., 3.3]
        value = odil.Value(items)
        self.assertEqual(value.type, odil.Value.Type.Reals)
        self.assertSequenceEqual(value.as_reals(), items)
    
    def test_strings_constructor(self):
        items = ["foo", "bar"]
        value = odil.Value(items)
        self.assertEqual(value.type, odil.Value.Type.Strings)
        self.assertSequenceEqual(value.as_strings(), items)
    
    def test_data_sets_constructor(self):
        items = [odil.DataSet(), odil.DataSet()]
        value = odil.Value(items)
        self.assertEqual(value.type, odil.Value.Type.DataSets)
        self.assertSequenceEqual(value.as_data_sets(), items)
    
    def test_binary_constructor(self):
        items = [bytearray("\x01\x02\x03")]
        value = odil.Value(items)
        self.assertEqual(value.type, odil.Value.Type.Binary)
        self.assertSequenceEqual(
            [bytearray([x for x in item]) for item in value.as_binary()], 
            items)

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
        items = ["foo", "bar"]
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
        items = [odil.Value.BinaryItem("\x01\x02\x03")]
        data = odil.Value.Binary(items)
        self.assertEqual([x for x in data[0]], [x for x in items[0]])

    def test_buffer(self):
        item = odil.Value.BinaryItem("\x01\x02\x03")
        memory_view = item.get_memory_view()
        self.assertTrue(isinstance(memory_view, memoryview))


if __name__ == "__main__":
    unittest.main()
