import os
import sys
import unittest

import odil

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from peer_fixture_base import PeerFixtureBase

class TestMoveSCU(PeerFixtureBase):
    def setUp(self):
        PeerFixtureBase.setUp(
            self, 
            [
                odil.AssociationParameters.PresentationContext(
                    1, odil.registry.PatientRootQueryRetrieveInformationModelMOVE,
                    [ odil.registry.ImplicitVRLittleEndian ], True, False
                ),
                odil.AssociationParameters.PresentationContext(
                    3, odil.registry.RawDataStorage,
                    [ odil.registry.ImplicitVRLittleEndian ], False, True
                )
            ])

        self.query = odil.DataSet()
        self.query.add(odil.registry.PatientName, odil.Value.Strings(["Doe^John"]))
        self.query.add(odil.registry.QueryRetrieveLevel, odil.Value.Strings(["PATIENT"]))
    
    def test_default_constructor(self):
        move = odil.MoveSCU(self.association)
        self.assertEqual(move.get_move_destination(), "")
        
    def test_move_destination(self):
        move = odil.MoveSCU(self.association)
        move.set_move_destination("remote")
        self.assertEqual(move.get_move_destination(), "remote")

    def test_without_callback(self):
        move = odil.MoveSCU(self.association)
        move.set_affected_sop_class(odil.registry.PatientRootQueryRetrieveInformationModelMOVE)
        move.set_move_destination("LOCAL")
        data_sets = move.move(self.query)

        self.assertEqual(len(data_sets), 1)
        self.assertEqual(
            [x for x in data_sets[0].as_string(odil.registry.SOPInstanceUID)],
            ["2.25.95090344942250266709587559073467305647"])

    def test_with_callback(self):
        data_sets = []
        def callback(data_set):
            data_sets.append(data_set)

        move = odil.MoveSCU(self.association)
        move.set_affected_sop_class(odil.registry.PatientRootQueryRetrieveInformationModelMOVE)
        move.set_move_destination("LOCAL")
        move.move(self.query, callback)

        self.assertEqual(len(data_sets), 1)
        self.assertEqual(
            [x for x in data_sets[0].as_string(odil.registry.SOPInstanceUID)],
            ["2.25.95090344942250266709587559073467305647"])

if __name__ == "__main__":
    unittest.main()
