import odil

association = odil.Association()
association.set_peer_host("184.73.255.26")
association.set_peer_port(11112)

presentation_contexts = [
    odil.AssociationParameters.PresentationContext(
        1, odil.registry.StudyRootQueryRetrieveInformationModelFind,
        [ odil.registry.ExplicitVRLittleEndian ], True, False
    ),
    odil.AssociationParameters.PresentationContext(
        3, odil.registry.Verification,
        [ odil.registry.ExplicitVRLittleEndian ], True, False
    )
]

association.update_parameters()\
    .set_calling_ae_title("myself")\
    .set_called_ae_title("AWSPIXELMEDPUB") \
    .set_presentation_contexts(presentation_contexts)
association.associate()

query = odil.DataSet()
query.add(odil.registry.PatientName, odil.Value.Strings(["*"]))
query.add(odil.registry.QueryRetrieveLevel, odil.Value.Strings(["STUDY"]))
query.add(odil.registry.StudyDescription)
query.add(odil.registry.StudyDate)

find = odil.FindSCU(association)
find.set_affected_sop_class(odil.registry.StudyRootQueryRetrieveInformationModelFind)

def callback(data_set):
    print data_set.as_string(odil.registry.PatientName)[0]
find.find(query, callback)

data_sets = find.find(query)
print len(data_sets), "found"
for data_set in data_sets:
    print data_set.as_string(odil.registry.PatientName)[0]
