import os
import unittest

import _odil

class PeerFixtureBase(unittest.TestCase):
    def setUp(self, contexts):
        self.association = _odil.Association()
        self.association.set_peer_host(os.environ["ODIL_PEER_HOST_NAME"])
        self.association.set_peer_port(int(os.environ["ODIL_PEER_PORT"]))
        self.association.update_parameters()\
            .set_calling_ae_title(os.environ["ODIL_OWN_AET"])\
            .set_called_ae_title(os.environ["ODIL_PEER_AET"]) \
            .set_presentation_contexts(contexts)
        self.association.associate()

    def tearDown(self):
        self.association.release()
