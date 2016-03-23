import _odil

association = _odil.Association()
association.set_peer_host("184.73.255.26")
association.set_peer_port(11112)

find_pc = _odil.AssociationParameters.PresentationContext(
    1, _odil.registry.StudyRootQueryRetrieveInformationModelFIND,
    [ _odil.registry.ExplicitVRLittleEndian ], True, False
)

verification_pc =  _odil.AssociationParameters.PresentationContext(
    3, _odil.registry.VerificationSOPClass,
    [ _odil.registry.ExplicitVRLittleEndian ], True, False
)

presentation_contexts = _odil.AssociationParameters.VPresentationContext()
presentation_contexts.append(find_pc)
presentation_contexts.append(verification_pc)

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
data_sets = find.find(query)
print len(data_sets), "found"
for data_set in data_sets:
    print data_set.as_string(_odil.registry.PatientName)[0]
