import glob
import multiprocessing
import os
import subprocess
import sys
import time
import unittest

import odil

class Generator(odil.FindSCP.DataSetGenerator):
    def __init__(self):
        odil.FindSCP.DataSetGenerator.__init__(self)
        self._responses = []
        self._response_index = None
        
    def initialize(self, message):
        data_set_1 = odil.DataSet()
        data_set_1.add("PatientName", ["Hello^World"])
        data_set_1.add("PatientID", ["1234"])
        self._responses.append(data_set_1)
        
        data_set_2 = odil.DataSet()
        data_set_2.add("PatientName", ["Doe^John"])
        data_set_2.add("PatientID", ["5678"])
        self._responses.append(data_set_2)
        
        self._response_index = 0
    
    def done(self):
        return (self._response_index == len(self._responses))
    
    def next(self):
        self._response_index += 1
    
    def get(self):
        return self._responses[self._response_index]

class TestFindSCP(unittest.TestCase):
    def test_find_scp_release(self):
        process = multiprocessing.Process(target=self.run_server)
        process.start()
        time.sleep(0.5)
        data_sets = self.run_client()
        process.join(2)
        server_code = process.exitcode
        
        self.assertEqual(server_code, 0)
        
        self.assertEqual(len(data_sets), 2)
        
        self.assertEqual(len(data_sets[0]), 2)
        
        self.assertSequenceEqual(
            data_sets[0].as_string("PatientName"), [b"Hello^World"])
        self.assertSequenceEqual(data_sets[0].as_string("PatientID"), [b"1234"])
        
        self.assertSequenceEqual(
            data_sets[1].as_string("PatientName"), [b"Doe^John"])
        self.assertSequenceEqual(data_sets[1].as_string("PatientID"), [b"5678"])
    
    def run_client(self):
        command = [
            "findscu",
            "-P", "-k", "QueryRetrieveLevel=PATIENT",
            "-k", "PatientID=*", "-k", "PatientName",
            "-q", "-X",
            "localhost", "11113"]
        
        retcode = subprocess.call(command)
        if retcode != 0:
            return []
        
        files = sorted(glob.glob("rsp*"))
        data_sets = []
        for file_ in files:
            with odil.open(file_, "rb") as fd:
                data_sets.append(odil.Reader.read_file(fd)[1])
        for file_ in files:
            os.remove(file_)
        
        return data_sets

    def run_server(self):
        association = odil.Association()
        association.set_tcp_timeout(1)
        association.receive_association("v4", 11113)

        find_scp = odil.FindSCP(association)
        generator = Generator()
        find_scp.set_generator(generator)

        message = association.receive_message()
        find_scp(message)
        
        termination_ok = False

        try:
            association.receive_message()
        except odil.AssociationReleased:
            termination_ok = True
        except odil.AssociationAborted:
            pass
        
        if termination_ok:
            sys.exit(0)
        else:
            sys.exit(1)

if __name__ == "__main__":
    unittest.main()
