import _odil

association = _odil.Association()
association.set_peer_host("184.73.255.26")
association.set_peer_port(11112)

presentation_contexts = [
    _odil.AssociationParameters.PresentationContext(
        1, _odil.registry.StudyRootQueryRetrieveInformationModelFIND,
        [ _odil.registry.ExplicitVRLittleEndian ], True, False
    ),
    _odil.AssociationParameters.PresentationContext(
        3, _odil.registry.VerificationSOPClass,
        [ _odil.registry.ExplicitVRLittleEndian ], True, False
    )
]

association.update_parameters()\
    .set_calling_ae_title("myself")\
    .set_called_ae_title("AWSPIXELMEDPUB") \
    .set_presentation_contexts(presentation_contexts)
association.associate()

query = _odil.DataSet()
query.add(_odil.registry.PatientName, _odil.Value.Strings(["*"]))
query.add(_odil.registry.QueryRetrieveLevel, _odil.Value.Strings(["STUDY"]))
query.add(_odil.registry.StudyDescription)
query.add(_odil.registry.StudyDate)

find = _odil.FindSCU(association)
find.set_affected_sop_class(_odil.registry.StudyRootQueryRetrieveInformationModelFIND)

def callback(data_set):
    print data_set.as_string(_odil.registry.PatientName)[0]
find.find(query, callback)

data_sets = find.find(query)
print len(data_sets), "found"
for data_set in data_sets:
    print data_set.as_string(_odil.registry.PatientName)[0]
