import os
import sys
import unittest

import _odil

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from peer_fixture_base import PeerFixtureBase

class TestGetSCU(PeerFixtureBase):
    def setUp(self):
        get_pc = _odil.AssociationParameters.PresentationContext(
            1, _odil.registry.PatientRootQueryRetrieveInformationModelGET,
            [ _odil.registry.ImplicitVRLittleEndian ], True, False
        )
        raw_storage = _odil.AssociationParameters.PresentationContext(
            3, _odil.registry.RawDataStorage,
            [ _odil.registry.ImplicitVRLittleEndian ], False, True
        )
        presentation_contexts = _odil.AssociationParameters.VPresentationContext()
        presentation_contexts.append(get_pc)
        presentation_contexts.append(raw_storage)

        PeerFixtureBase.setUp(self, presentation_contexts)

        self.query = _odil.DataSet()
        self.query.add(_odil.registry.PatientName, _odil.Value.Strings(["Doe^John"]))
        self.query.add(_odil.registry.QueryRetrieveLevel, _odil.Value.Strings(["PATIENT"]))

    def test_without_callback(self):
        get = _odil.GetSCU(self.association)
        get.set_affected_sop_class(_odil.registry.PatientRootQueryRetrieveInformationModelGET)
        data_sets = get.get(self.query)

        self.assertEqual(len(data_sets), 1)
        self.assertEqual(
            [x for x in data_sets[0].as_string(_odil.registry.SOPInstanceUID)],
            ["2.25.95090344942250266709587559073467305647"])

    def test_with_callback(self):
        data_sets = []
        def callback(data_set):
            data_sets.append(data_set)

        get = _odil.GetSCU(self.association)
        get.set_affected_sop_class(_odil.registry.PatientRootQueryRetrieveInformationModelGET)
        get.get(self.query, callback)

        self.assertEqual(len(data_sets), 1)
        self.assertEqual(
            [x for x in data_sets[0].as_string(_odil.registry.SOPInstanceUID)],
            ["2.25.95090344942250266709587559073467305647"])

if __name__ == "__main__":
    unittest.main()
