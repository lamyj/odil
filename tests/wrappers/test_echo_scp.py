import multiprocessing
import subprocess
import sys
import time
import unittest

import odil

class TestEchoSCP(unittest.TestCase):
    def test_echo_scp_release(self):
        process = multiprocessing.Process(target=lambda: self.run_server(False))
        process.start()
        time.sleep(0.5)
        client_code = self.run_client(False)
        process.join(2)
        server_code = process.exitcode
        
        self.assertEqual(client_code, 0)
        self.assertEqual(server_code, 0)
    
    def test_echo_scp_abort(self):
        process = multiprocessing.Process(target=lambda: self.run_server(True))
        process.start()
        time.sleep(0.5)
        client_code = self.run_client(True)
        process.join(2)
        server_code = process.exitcode
        
        self.assertEqual(client_code, 0)
        self.assertEqual(server_code, 0)
    
    def run_client(self, use_abort):
        command = ["echoscu", "-q"]
        if use_abort:
            command.append("--abort")
        command.extend(["localhost", "11113"])
        
        return subprocess.call(command)

    def run_server(self, use_abort):
        called = [False]
        def echo_callback(message):
            called[0] = True
            return 0

        association = odil.Association()
        association.set_tcp_timeout(1)
        association.receive_association("v4", 11113)

        echo_scp = odil.EchoSCP(association)
        echo_scp.set_callback(echo_callback)

        message = association.receive_message()
        echo_scp(message)
        
        termination_ok = False

        try:
            association.receive_message()
        except odil.AssociationReleased:
            if not use_abort:
                termination_ok = True
        except odil.AssociationAborted:
            if use_abort:
                termination_ok = True
        
        if called[0] and termination_ok:
            sys.exit(0)
        else:
            sys.exit(1)

if __name__ == "__main__":
    unittest.main()
