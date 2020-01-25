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

    def test_without_callback(self):
        get = odil.GetSCU(self.association)
        get.set_affected_sop_class(odil.registry.PatientRootQueryRetrieveInformationModelGET)
        data_sets = get.get(self.query)

        self.assertEqual(len(data_sets), 1)
        self.assertSequenceEqual(
            data_sets[0].as_string("SOPInstanceUID"),
            [b"2.25.95090344942250266709587559073467305647"])

    def test_both_callbacks(self):
        data_sets = []
        messages = []
        def store_callback(data_set):
            data_sets.append(data_set)
        def get_callback(message):
            messages.append(message)

        get = odil.GetSCU(self.association)
        get.set_affected_sop_class(
            odil.registry.PatientRootQueryRetrieveInformationModelGET)
        get.get(self.query, store_callback, get_callback)

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

    def test_only_store_callback(self):
        data_sets = []
        def store_callback(data_set):
            data_sets.append(data_set)

        get = odil.GetSCU(self.association)
        get.set_affected_sop_class(
            odil.registry.PatientRootQueryRetrieveInformationModelGET)
        get.get(self.query, store_callback)

        self.assertEqual(len(data_sets), 1)
        self.assertSequenceEqual(
            data_sets[0].as_string("SOPInstanceUID"),
            [b"2.25.95090344942250266709587559073467305647"])

if __name__ == "__main__":
    unittest.main()
