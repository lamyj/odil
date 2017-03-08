import unittest

import odil

class TestException(unittest.TestCase):
    def test_python_generic(self):
        with self.assertRaises(Exception):
            raise odil.Exception()
    
    def test_python_specific(self):
        with self.assertRaises(odil.Exception):
            raise odil.Exception()

    def test_cpp_generic(self):
        tag = odil.Tag(0xdead, 0xbeef)
        with self.assertRaises(Exception):
            tag.get_name()
    
    def test_cpp_specific(self):
        tag = odil.Tag(0xdead, 0xbeef)
        with self.assertRaises(odil.Exception):
            tag.get_name()

if __name__ == "__main__":
    unittest.main()
