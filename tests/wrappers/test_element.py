import re
import unittest

import odil

class TestElement(unittest.TestCase):
    def _test_sequences(self, odil_contents, python_contents):
        if python_contents and isinstance(python_contents[0], bytearray):
            self.assertSequenceEqual(
                [bytearray([x for x in item]) for item in odil_contents], 
                python_contents)
        else:
            self.assertSequenceEqual(list(odil_contents), list(python_contents))

    def _test_value(self, element, vr, contents, type_check, accessor):
        self.assertTrue(type_check(element))
        self.assertEqual(element.empty(), len(contents)==0)
        self.assertEqual(element.size(), len(contents))
        self.assertEqual(len(element), len(contents))
        self._test_sequences(accessor(element), contents)
        self.assertEqual(element.vr, vr)

        if not element.is_int():
            with self.assertRaises(odil.Exception):
                element.as_int()
        if not element.is_real():
            with self.assertRaises(odil.Exception):
                element.as_real()
        if not element.is_string():
            with self.assertRaises(odil.Exception):
                element.as_string()
        if not element.is_data_set():
            with self.assertRaises(odil.Exception):
                element.as_data_set()
        if not element.is_binary():
            with self.assertRaises(odil.Exception):
                element.as_binary()

    def _test_implicit_container(self, empty_content, vr, type_check, accessor):
        element = odil.Element(vr)
        self._test_value(element, vr, empty_content, type_check, accessor)

    def _test_container(self, contents, vr, type_check, accessor):
        element = odil.Element(contents, vr)
        self._test_value(element, vr, contents, type_check, accessor)
    
    def _test_modify(self, contents, vr, accessor):
        value = odil.Element([contents[0]], vr)
        if isinstance(contents[0], bytearray):
            accessor(value).append(odil.Value.BinaryItem("".join(chr(x) for x in contents[1])))
        else:
            accessor(value).append(contents[1])
        
        self._test_sequences(accessor(value), contents)

    def _test_clear(self, contents, vr, type_check):
        element = odil.Element(contents, vr)
        element.clear()
        self.assertTrue(type_check(element))
        self.assertTrue(element.empty())

    def _test_equality(self, contents_1, contents_2, vr_1, vr_2):
        element_1 = odil.Element(contents_1, vr_1)
        element_2 = odil.Element(contents_1, vr_1)
        element_3 = odil.Element(contents_1, vr_2)
        element_4 = odil.Element(contents_2, vr_1)

        self.assertTrue(element_1 == element_2)
        self.assertFalse(element_1 == element_3)
        self.assertFalse(element_1 == element_4)

        self.assertFalse(element_1 != element_2)
        self.assertTrue(element_1 != element_3)
        self.assertTrue(element_1 != element_4)

    def _test(
            self, 
            empty_content, contents, other_contents, vr, other_vr, 
            type_check, accessor):
        self._test_implicit_container(empty_content, vr, type_check, accessor)
        self._test_container(contents, vr, type_check, accessor)

        self._test_modify(contents, vr, accessor)

        self._test_clear(contents, vr, type_check)

        self._test_equality(contents, other_contents, vr, other_vr)

    def test_implicit_type(self):
        for vr in dir(odil.VR):
            if re.match(r"^[A-Z]{2}$", vr) is None:
                continue

            vr = getattr(odil.VR, vr)
            if odil.is_int(vr):
                self._test_implicit_container(
                    odil.Value.Integers(), vr, 
                    odil.Element.is_int, odil.Element.as_int)
            elif odil.is_real(vr):
                self._test_implicit_container(
                    odil.Value.Reals(), vr, 
                    odil.Element.is_real, odil.Element.as_real)
            elif odil.is_string(vr):
                self._test_implicit_container(
                    odil.Value.Strings(), vr, 
                    odil.Element.is_string, odil.Element.as_string)
            elif vr == odil.VR.SQ:
                self._test_implicit_container(
                    odil.Value.DataSets(), vr, 
                    odil.Element.is_data_set, odil.Element.as_data_set)
            elif odil.is_binary(vr):
                self._test_implicit_container(
                    odil.Value.Binary(), vr, 
                    odil.Element.is_binary, odil.Element.as_binary)

    def test_integers(self):
        self._test(
            odil.Value.Integers(), [1234, 5678], [9012, 3456],
            odil.VR.US, odil.VR.UL,
            odil.Element.is_int, odil.Element.as_int)

    def test_reals(self):
        self._test(
            odil.Value.Reals(), [12.34, 56.78], [1., 2.],
            odil.VR.FD, odil.VR.DS,
            odil.Element.is_real, odil.Element.as_real)

    def test_strings(self):
        self._test(
            odil.Value.Strings(), [b"foo", b"bar"], [b"plip", b"plop"],
            odil.VR.CS, odil.VR.UT,
            odil.Element.is_string, odil.Element.as_string)
        
    def test_data_sets(self):
        data_set_1 = odil.DataSet()
        data_set_1.add("PatientID", ["DJ1234"])
    
        data_set_2 = odil.DataSet()
        data_set_2.add("EchoTime", [100])

        self._test(
            odil.Value.DataSets(), 
            [data_set_1, data_set_2], [data_set_2, data_set_1],
            odil.VR.SQ, odil.VR.UN,
            odil.Element.is_data_set, odil.Element.as_data_set)

    def test_binary(self):
        self._test(
            odil.Value.Binary(), 
            [bytearray([0x01, 0x02]), bytearray([0x03])],
            [bytearray([0x04]), bytearray([0x05, 0x06])],
            odil.VR.OB, odil.VR.OW,
            odil.Element.is_binary, odil.Element.as_binary)

if __name__ == "__main__":
    unittest.main()
