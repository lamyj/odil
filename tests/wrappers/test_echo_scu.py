import os
import sys
import unittest

import odil

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from peer_fixture_base import PeerFixtureBase

class TestEchoSCU(PeerFixtureBase):
    def setUp(self):
        PeerFixtureBase.setUp(
            self, 
            [
                odil.AssociationParameters.PresentationContext(
                    3, odil.registry.Verification,
                    [ odil.registry.ImplicitVRLittleEndian ], 
                    odil.AssociationParameters.PresentationContext.Role.SCU)
            ]
        )
    
    def test_echo(self):
        echo = odil.EchoSCU(self.association)
        echo.echo()

if __name__ == "__main__":
    unittest.main()
