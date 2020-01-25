import os
import sys
import unittest

import odil

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from peer_fixture_base import PeerFixtureBase

class TestStoreSCU(PeerFixtureBase):
    def setUp(self):
        PeerFixtureBase.setUp(
            self, 
            [
                odil.AssociationParameters.PresentationContext(
                    1, odil.registry.RawDataStorage,
                    [ odil.registry.ImplicitVRLittleEndian ], 
                    odil.AssociationParameters.PresentationContext.Role.SCU
                )
            ])

        self.data_set = odil.DataSet()
        self.data_set.add("ImageType", ["ORIGINAL", "PRIMARY", "OTHER"])
        self.data_set.add("PatientID", ["1234"])
        self.data_set.add(
            "StudyInstanceUID",
            ["2.25.386726390606491051215227596277040710"])
        self.data_set.add(
            "SeriesInstanceUID",
            ["2.25.235367796740370588607388995952651763168"])
        self.data_set.add("SOPClassUID", [odil.registry.RawDataStorage])
        self.data_set.add(
            "SOPInstanceUID",
            ["2.25.294312554735929033890522327215919068328"])
    
    def test_affected_sop_class_uid(self):
        store = odil.StoreSCU(self.association)
        store.set_affected_sop_class(self.data_set)
        self.assertEqual(
            store.get_affected_sop_class().encode(),
            odil.registry.RawDataStorage)
    
    def test_store(self):
        store = odil.StoreSCU(self.association)

        store.set_affected_sop_class(self.data_set)
        store.store(self.data_set)

if __name__ == "__main__":
    unittest.main()
