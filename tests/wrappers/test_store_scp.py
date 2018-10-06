import multiprocessing
import os
import shutil
import subprocess
import sys
import tempfile
import time
import unittest

import odil

class TestStoreSCP(unittest.TestCase):
    def __init__(self, *args, **kwargs):
        unittest.TestCase.__init__(self, *args, **kwargs)
        self.directory = None

    def setUp(self):
        self.directory = tempfile.mkdtemp()

        with open(os.path.join(self.directory, "data.txt"), "w") as fd:
            fd.write(
                """
                (0008,0016) UI =RawDataStorage
                (0008,0018) UI [2.25.95090344942250266709587559073467305647]
                (0010,0010) PN [Doe^John]
                (0010,0020) LO [DJ001]
                """)

        subprocess.check_call([
            "dump2dcm", "--write-xfer-little",
            os.path.join(self.directory, "data.txt"),
            os.path.join(self.directory, "data.dcm")
        ])

    def tearDown(self):
        shutil.rmtree(self.directory)

    def test_store_scp_release(self):
        process = multiprocessing.Process(target=lambda: self.run_server(False))
        process.start()
        time.sleep(0.5)
        client_code = self.run_client()
        process.join(2)
        server_code = process.exitcode

        self.assertEqual(client_code, 0)
        self.assertEqual(server_code, 0)

    def run_client(self):
        command = [
            "storescu", "-ll", "error", "localhost", "11113",
            os.path.join(self.directory, "data.dcm")]

        return subprocess.call(command)

    def run_server(self, use_abort):
        called = [False]
        def store_callback(message):
            called[0] = True
            return 0

        association = odil.Association()
        association.set_tcp_timeout(1)
        association.receive_association("v4", 11113)

        store_scp = odil.StoreSCP(association)
        store_scp.set_callback(store_callback)

        message = association.receive_message()
        store_scp(message)

        termination_ok = False

        try:
            association.receive_message()
        except odil.AssociationReleased:
            termination_ok = True

        if called[0] and termination_ok:
            sys.exit(0)
        else:
            sys.exit(1)

if __name__ == "__main__":
    unittest.main()
