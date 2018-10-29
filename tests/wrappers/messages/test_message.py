import unittest

import odil

class TestMessage(unittest.TestCase):
    def test_commands(self):
        self.assertEqual(odil.messages.Message.Command.C_FIND_RSP, 0x8020)

if __name__ == "__main__":
    unittest.main()
