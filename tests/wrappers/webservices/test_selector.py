import unittest

import odil

class TestSelector(unittest.TestCase):
    def test_default_constructor(self):
        selector = odil.webservices.Selector()
        self.assertFalse(selector.is_study_present())
        self.assertFalse(selector.is_series_present())
        self.assertFalse(selector.is_instance_present())
        self.assertEqual(list(selector.get_frames()), [])

    def test_full_constructor(self):
        selector = odil.webservices.Selector("1.2", "3.4", "5.6", [7,8])
        self.assertTrue(selector.is_study_present())
        self.assertEqual(selector.get_study(), "1.2")

        self.assertTrue(selector.is_series_present())
        self.assertEqual(selector.get_series(), "3.4")

        self.assertTrue(selector.is_instance_present())
        self.assertEqual(selector.get_instance(), "5.6")

        self.assertEqual(list(selector.get_frames()), [7,8])

    def test_get_path_no_frames(self):
        selector = odil.webservices.Selector(
            "1.2", "3.4", "5.6", [7,8])
        self.assertEqual(
            selector.get_path(False), "/studies/1.2/series/3.4/instances/5.6")

    def test_get_path_frames(self):
        selector = odil.webservices.Selector(
            "1.2", "3.4", "5.6", [7,8])
        self.assertEqual(
            selector.get_path(True),
            "/studies/1.2/series/3.4/instances/5.6/frames/7,8")

if __name__ == "__main__":
    unittest.main()
