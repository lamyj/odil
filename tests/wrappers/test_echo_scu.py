import os
import sys
import unittest

import _odil

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from peer_fixture_base import PeerFixtureBase

class TestEchoSCU(PeerFixtureBase):
    def setUp(self):
        PeerFixtureBase.setUp(
            self, 
            [
                _odil.AssociationParameters.PresentationContext(
                    3, _odil.registry.VerificationSOPClass,
                    [ _odil.registry.ImplicitVRLittleEndian ], True, False)
            ]
        )
    
    def test_echo(self):
        echo = _odil.EchoSCU(self.association)
        echo.echo()

if __name__ == "__main__":
    unittest.main()
