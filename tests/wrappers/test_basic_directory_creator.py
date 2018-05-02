import os
import shutil
import tempfile
import unittest

import odil

class TestBasicDirectoryCreator(unittest.TestCase):
    def setUp(self):
        self.root = tempfile.mkdtemp()

        data_set_1 = odil.DataSet()
        data_set_1.add("PatientID", ["DJ123"])
        data_set_1.add("StudyDate", ["19100110"])
        data_set_1.add("StudyTime", ["1234"])
        data_set_1.add("StudyDescription", ["Study"])
        data_set_1.add("StudyInstanceUID", ["1.2.3.4"])
        data_set_1.add("StudyID", ["FOO"])
        data_set_1.add("Modality", ["OT"])
        data_set_1.add("SeriesInstanceUID", ["1.2.3.4.1"])
        data_set_1.add("SeriesNumber", [1])
        data_set_1.add("SeriesDescription", ["Series"])
        data_set_1.add("InstanceNumber", [1])
        data_set_1.add("SOPInstanceUID", ["1.2.3.4.1.1"])
        data_set_1.add("SOPClassUID", [odil.registry.RawDataStorage])

        with open(os.path.join(self.root, "a.dcm"), "wb") as fd:
            stream_1 = odil.iostream(fd)
            odil.Writer.write_file(data_set_1, stream_1)

        data_set_2 = odil.DataSet()
        data_set_2.add("PatientID", ["DJ123"])
        data_set_2.add("StudyDate", ["19100110"])
        data_set_2.add("StudyTime", ["1234"])
        data_set_2.add("StudyDescription", ["Study"])
        data_set_2.add("StudyInstanceUID", ["1.2.3.4"])
        data_set_2.add("StudyID", ["FOO"])
        data_set_2.add("Modality", ["OT"])
        data_set_2.add("SeriesInstanceUID", ["1.2.3.4.1"])
        data_set_2.add("SeriesNumber", [1])
        data_set_2.add("SeriesDescription", ["Series"])
        data_set_2.add("InstanceNumber", [2])
        data_set_2.add("SOPInstanceUID", ["1.2.3.4.1.2"])
        data_set_2.add("SOPClassUID", [odil.registry.RawDataStorage])

        with open(os.path.join(self.root, "b.dcm"), "wb") as fd:
            stream_2 = odil.iostream(fd)
            odil.Writer.write_file(data_set_2, stream_2)

        self.files = ["a.dcm", "b.dcm"]

    def tearDown(self):
        shutil.rmtree(self.root)

    def test_default_record_keys(self):
        creator = odil.BasicDirectoryCreator(self.root, self.files)
        creator()
        with open(os.path.join(self.root, "DICOMDIR"), "rb") as fd:
            header, dicomdir = odil.Reader.read_file(odil.iostream(fd))

        records = dicomdir.as_data_set("DirectoryRecordSequence")

        self._test_default_records(records)

    def test_extra_record_keys(self):
        creator = odil.BasicDirectoryCreator(
            self.root, self.files,
            { "SERIES": [["SeriesDescription", 1]]})
        creator()
        with open(os.path.join(self.root, "DICOMDIR"), "rb") as fd:
            header, dicomdir = odil.Reader.read_file(odil.iostream(fd))

        records = dicomdir.as_data_set("DirectoryRecordSequence")

        self._test_default_records(records)
        self.assertSequenceEqual(
            records[2].as_string("SeriesDescription"), ["Series"])

    def _test_default_records(self, records):
        self.assertEqual(len(records), 5)

        self.assertSequenceEqual(
            records[0].as_string("DirectoryRecordType"), ["PATIENT"])
        self.assertSequenceEqual(
            records[0].as_string("PatientID"), ["DJ123"])

        self.assertSequenceEqual(
            records[1].as_string("DirectoryRecordType"), ["STUDY"])
        self.assertSequenceEqual(
            records[1].as_string("StudyInstanceUID"), ["1.2.3.4"])
        self.assertSequenceEqual(
            records[1].as_string("StudyDescription"), ["Study"])

        self.assertSequenceEqual(
            records[2].as_string("DirectoryRecordType"), ["SERIES"])
        self.assertSequenceEqual(
            records[2].as_string("SeriesInstanceUID"), ["1.2.3.4.1"])

        self.assertSequenceEqual(
            records[3].as_string("DirectoryRecordType"), ["IMAGE"])
        self.assertSequenceEqual(
            records[3].as_int("InstanceNumber"), [1])

        self.assertSequenceEqual(
            records[4].as_string("DirectoryRecordType") , ["IMAGE"])
        self.assertSequenceEqual(
            records[4].as_int("InstanceNumber"), [2])

if __name__ == "__main__":
    unittest.main()
