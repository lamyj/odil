import os
import sys
import unittest

import odil

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from peer_fixture_base import PeerFixtureBase

class TestGetSCU(PeerFixtureBase):
    def setUp(self):
        PeerFixtureBase.setUp(
            self, 
            [
                odil.AssociationParameters.PresentationContext(
                    1, odil.registry.PatientRootQueryRetrieveInformationModelGET,
                    [ odil.registry.ImplicitVRLittleEndian ], True, False
                ),
                odil.AssociationParameters.PresentationContext(
                    3, odil.registry.RawDataStorage,
                    [ odil.registry.ImplicitVRLittleEndian ], False, True
                )
            ])

        self.query = odil.DataSet()
        self.query.add("PatientName", ["Doe^John"])
        self.query.add("QueryRetrieveLevel", ["PATIENT"])

    def test_without_callback(self):
        get = odil.GetSCU(self.association)
        get.set_affected_sop_class(odil.registry.PatientRootQueryRetrieveInformationModelGET)
        data_sets = get.get(self.query)

        self.assertEqual(len(data_sets), 1)
        self.assertSequenceEqual(
            data_sets[0].as_string("SOPInstanceUID"),
            ["2.25.95090344942250266709587559073467305647"])

    def test_with_callback(self):
        data_sets = []
        def callback(data_set):
            data_sets.append(data_set)

        get = odil.GetSCU(self.association)
        get.set_affected_sop_class(odil.registry.PatientRootQueryRetrieveInformationModelGET)
        get.get(self.query, callback)

        self.assertEqual(len(data_sets), 1)
        self.assertSequenceEqual(
            data_sets[0].as_string("SOPInstanceUID"),
            ["2.25.95090344942250266709587559073467305647"])

if __name__ == "__main__":
    unittest.main()
