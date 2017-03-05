import unittest

import odil

class TestSelector(unittest.TestCase):
    def test_default_constructor(self):
        selector = odil.webservices.WADORSRequest.Selector()
        self.assertEqual(selector.study, "")
        self.assertEqual(selector.series, "")
        self.assertEqual(selector.instance, "")
        self.assertEqual(list(selector.frames), [])

    def test_full_constructor(self):
        selector = odil.webservices.WADORSRequest.Selector(
            "1.2", "3.4", "5.6", [7,8])
        self.assertEqual(selector.study, "1.2")
        self.assertEqual(selector.series, "3.4")
        self.assertEqual(selector.instance, "5.6")
        self.assertEqual(list(selector.frames), [7,8])

    def test_get_path_no_frames(self):
        selector = odil.webservices.WADORSRequest.Selector(
            "1.2", "3.4", "5.6", [7,8])
        self.assertEqual(
            selector.get_path(False), "/studies/1.2/series/3.4/instances/5.6")

    def test_get_path_frames(self):
        selector = odil.webservices.WADORSRequest.Selector(
            "1.2", "3.4", "5.6", [7,8])
        self.assertEqual(
            selector.get_path(True),
            "/studies/1.2/series/3.4/instances/5.6/frames/7,8")

if __name__ == "__main__":
    unittest.main()
