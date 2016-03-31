import os
import sys
import unittest

import _odil

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from peer_fixture_base import PeerFixtureBase

class TestStoreSCU(PeerFixtureBase):
    def setUp(self):
        PeerFixtureBase.setUp(
            self, 
            [
                _odil.AssociationParameters.PresentationContext(
                    1, _odil.registry.RawDataStorage,
                    [ _odil.registry.ImplicitVRLittleEndian ], True, False
                )
            ])

        self.data_set = _odil.DataSet()
        self.data_set.add(
            _odil.registry.ImageType, 
            _odil.Value.Strings(["ORIGINAL", "PRIMARY", "OTHER"]))
        self.data_set.add(
            _odil.registry.PatientID, _odil.Value.Strings(["1234"]))
        self.data_set.add(
            _odil.registry.StudyInstanceUID, 
            _odil.Value.Strings(["2.25.386726390606491051215227596277040710"]))
        self.data_set.add(
            _odil.registry.SeriesInstanceUID, 
            _odil.Value.Strings(["2.25.235367796740370588607388995952651763168"]))
        self.data_set.add(
            _odil.registry.SOPClassUID, 
            _odil.Value.Strings([_odil.registry.RawDataStorage]))
        self.data_set.add(
            _odil.registry.SOPInstanceUID, 
            _odil.Value.Strings(["2.25.294312554735929033890522327215919068328"]))
    
    def test_affected_sop_class_uid(self):
        store = _odil.StoreSCU(self.association)
        store.set_affected_sop_class(self.data_set)
        self.assertEqual(store.get_affected_sop_class(), _odil.registry.RawDataStorage)
    
    def test_store(self):
        store = _odil.StoreSCU(self.association)

        store.set_affected_sop_class(self.data_set)
        store.store(self.data_set)

if __name__ == "__main__":
    unittest.main()
