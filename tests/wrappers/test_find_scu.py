import os
import sys
import unittest

import _odil

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from peer_fixture_base import PeerFixtureBase

class TestFindSCU(PeerFixtureBase):
    def setUp(self):
        PeerFixtureBase.setUp(
            self, 
            [
                _odil.AssociationParameters.PresentationContext(
                1, _odil.registry.PatientRootQueryRetrieveInformationModelFIND,
                [ _odil.registry.ImplicitVRLittleEndian ], True, False)
            ]
        )

        self.query = _odil.DataSet()
        self.query.add(_odil.registry.PatientName, _odil.Value.Strings(["Doe^John"]))
        self.query.add(_odil.registry.QueryRetrieveLevel, _odil.Value.Strings(["PATIENT"]))
        self.query.add(_odil.registry.PatientID)

    def test_without_callback(self):
        find = _odil.FindSCU(self.association)
        find.set_affected_sop_class(_odil.registry.PatientRootQueryRetrieveInformationModelFIND)
        data_sets = find.find(self.query)

        self.assertEqual(len(data_sets), 1)
        self.assertEqual(
            [x for x in data_sets[0].as_string(_odil.registry.PatientID)],
            ["DJ001"])

    def test_with_callback(self):
        data_sets = []
        def callback(data_set):
            data_sets.append(data_set)

        find = _odil.FindSCU(self.association)
        find.set_affected_sop_class(_odil.registry.PatientRootQueryRetrieveInformationModelFIND)
        find.find(self.query, callback)

        self.assertEqual(len(data_sets), 1)
        self.assertEqual(
            [x for x in data_sets[0].as_string(_odil.registry.PatientID)],
            ["DJ001"])

if __name__ == "__main__":
    unittest.main()
