import os
import sys
import unittest

import odil

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from peer_fixture_base import PeerFixtureBase

class TestFindSCU(PeerFixtureBase):
    def setUp(self):
        PeerFixtureBase.setUp(
            self, 
            [
                odil.AssociationParameters.PresentationContext(
                1, odil.registry.PatientRootQueryRetrieveInformationModelFIND,
                [ odil.registry.ImplicitVRLittleEndian ], True, False)
            ]
        )

        self.query = odil.DataSet()
        self.query.add("PatientName", ["Doe^John"])
        self.query.add("QueryRetrieveLevel", ["PATIENT"])
        self.query.add("PatientID")

    def test_without_callback(self):
        find = odil.FindSCU(self.association)
        find.set_affected_sop_class(odil.registry.PatientRootQueryRetrieveInformationModelFIND)
        data_sets = find.find(self.query)

        self.assertEqual(len(data_sets), 1)
        self.assertSequenceEqual(
            data_sets[0].as_string("PatientID"), ["DJ001"])

    def test_with_callback(self):
        data_sets = []
        def callback(data_set):
            data_sets.append(data_set)

        find = odil.FindSCU(self.association)
        find.set_affected_sop_class(odil.registry.PatientRootQueryRetrieveInformationModelFIND)
        find.find(self.query, callback)

        self.assertEqual(len(data_sets), 1)
        self.assertSequenceEqual(
            data_sets[0].as_string("PatientID"), ["DJ001"])

if __name__ == "__main__":
    unittest.main()
