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
                    [ odil.registry.ImplicitVRLittleEndian ], 
                    odil.AssociationParameters.PresentationContext.Role.SCU
                ),
                odil.AssociationParameters.PresentationContext(
                    3, odil.registry.RawDataStorage,
                    [ odil.registry.ImplicitVRLittleEndian ], 
                    odil.AssociationParameters.PresentationContext.Role.SCP
                )
            ])

        self.query = odil.DataSet()
        self.query.add("PatientName", ["Doe^John"])
        self.query.add("QueryRetrieveLevel", ["PATIENT"])

    def test_default_constructor(self):
        move = odil.MoveSCU(self.association)
        self.assertEqual(move.get_move_destination(), "")
        self.assertEqual(move.get_incoming_port(), 0)

    def test_move_destination(self):
        move = odil.MoveSCU(self.association)
        move.set_move_destination("remote")
        self.assertEqual(move.get_move_destination(), "remote")

    def test_incoming_port(self):
        move = odil.MoveSCU(self.association)
        move.set_incoming_port(11113)
        self.assertEqual(move.get_incoming_port(), 11113)

    def test_without_callback(self):
        move = odil.MoveSCU(self.association)
        move.set_affected_sop_class(odil.registry.PatientRootQueryRetrieveInformationModelMOVE)
        move.set_move_destination("LOCAL")
        move.set_incoming_port(11113)
        data_sets = move.move(self.query)

        self.assertEqual(len(data_sets), 1)
        self.assertSequenceEqual(
            data_sets[0].as_string("SOPInstanceUID"),
            [b"2.25.95090344942250266709587559073467305647"])

    def test_both_callback(self):
        data_sets = []
        messages = []
        def store_callback(data_set):
            data_sets.append(data_set)
        def move_callback(message):
            messages.append(message)

        move = odil.MoveSCU(self.association)
        move.set_affected_sop_class(odil.registry.PatientRootQueryRetrieveInformationModelMOVE)
        move.set_move_destination("LOCAL")
        move.set_incoming_port(11113)
        move.move(self.query, store_callback, move_callback)

        self.assertEqual(len(data_sets), 1)
        self.assertSequenceEqual(
            data_sets[0].as_string("SOPInstanceUID"),
            [b"2.25.95090344942250266709587559073467305647"])

        self.assertEqual(len(messages), 2)

        self.assertEqual(
            messages[0].get_number_of_remaining_sub_operations(), 0)
        self.assertEqual(
            messages[0].get_number_of_completed_sub_operations(), 1)
        self.assertEqual(messages[0].get_number_of_failed_sub_operations(), 0)
        self.assertEqual(messages[0].get_number_of_warning_sub_operations(), 0)

        self.assertFalse(messages[1].has_number_of_remaining_sub_operations())
        self.assertEqual(
            messages[1].has_number_of_completed_sub_operations(), 1)
        self.assertEqual(
            messages[1].get_number_of_failed_sub_operations(), 0)
        self.assertEqual(
            messages[1].get_number_of_warning_sub_operations(), 0)

    def test_store_only_callback(self):
        data_sets = []
        def store_callback(data_set):
            data_sets.append(data_set)

        move = odil.MoveSCU(self.association)
        move.set_affected_sop_class(odil.registry.PatientRootQueryRetrieveInformationModelMOVE)
        move.set_move_destination("LOCAL")
        move.set_incoming_port(11113)
        move.move(self.query, store_callback, None)

        self.assertEqual(len(data_sets), 1)
        self.assertSequenceEqual(
            data_sets[0].as_string("SOPInstanceUID"),
            [b"2.25.95090344942250266709587559073467305647"])

if __name__ == "__main__":
    unittest.main()
