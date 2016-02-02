import unittest

import _odil

class TestTag(unittest.TestCase):
    def test_two_ints_constructor(self):
        tag = _odil.Tag(0x1234, 0x5678)
        self.assertEqual(tag.group, 0x1234)
        self.assertEqual(tag.element, 0x5678)

    def test_one_int_constructor(self):
        tag = _odil.Tag(0x12345678)
        self.assertEqual(tag.group, 0x1234)
        self.assertEqual(tag.element, 0x5678)

    def test_string_constructor(self):
        tag = _odil.Tag("PatientID")
        self.assertEqual(tag.group, 0x0010)
        self.assertEqual(tag.element, 0x0020)

    def test_group(self):
        tag = _odil.Tag(0x1234, 0x5678)
        tag.group = 0x4321
        self.assertEqual(tag.group, 0x4321)
        self.assertEqual(tag.element, 0x5678)

    def test_element(self):
        tag = _odil.Tag(0x1234, 0x5678)
        tag.element = 0x8765
        self.assertEqual(tag.group, 0x1234)
        self.assertEqual(tag.element, 0x8765)

    def test_is_private(self):
        public = _odil.Tag(0x1234, 0x5678)
        self.assertTrue(not public.is_private())

        private = _odil.Tag(0x1235, 0x5678)
        self.assertTrue(private.is_private())

    def test_get_name(self):
        tag = _odil.Tag(0x0010, 0x0020)
        self.assertEqual(tag.get_name(), "PatientID")

    def test_equality(self):
        tag1 = _odil.Tag(0x1234, 0x5678)
        tag2 = _odil.Tag(0x4321, 0x8765)
        self.assertTrue(tag1 == tag1)
        self.assertFalse(tag1 == tag2)

    def test_inequality(self):
        tag1 = _odil.Tag(0x1234, 0x5678)
        tag2 = _odil.Tag(0x4321, 0x8765)
        self.assertFalse(tag1 != tag1)
        self.assertTrue(tag1 != tag2)

    def test_less(self):
        tag1 = _odil.Tag(0x1234, 0x5678)
        tag2 = _odil.Tag(0x4321, 0x8765)
        self.assertTrue(tag1 < tag2)
        self.assertFalse(tag2 < tag1)

    def test_greater(self):
        tag1 = _odil.Tag(0x1234, 0x5678)
        tag2 = _odil.Tag(0x4321, 0x8765)
        self.assertFalse(tag1 > tag2)
        self.assertTrue(tag2 > tag1)

    def test_less_or_equal(self):
        tag1 = _odil.Tag(0x1234, 0x5678)
        tag2 = _odil.Tag(0x4321, 0x8765)
        self.assertTrue(tag1 <= tag2)
        self.assertTrue(tag1 <= tag1)
        self.assertFalse(tag2 <= tag1)

    def test_greater_or_equal(self):
        tag1 = _odil.Tag(0x1234, 0x5678)
        tag2 = _odil.Tag(0x4321, 0x8765)
        self.assertFalse(tag1 >= tag2)
        self.assertTrue(tag1 >= tag1)
        self.assertTrue(tag2 >= tag1)

    def test_str(self):
        tag = _odil.Tag(0x1234, 0x5678)
        self.assertEqual(str(tag), "12345678")

if __name__ == "__main__":
    unittest.main()
