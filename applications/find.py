import logging

import _odil

from print_ import print_data_set

def add_subparser(subparsers):
    parser = subparsers.add_parser(
        "find", help="DICOM query (C-FIND)")
    parser.add_argument("host", help="Remote host address")
    parser.add_argument("port", type=int, help="Remote host port")
    parser.add_argument(
        "calling_ae_title", help="AE title of the calling application")
    parser.add_argument(
        "called_ae_title", help="AE title of the called application")
    parser.add_argument(
        "level", choices=["patient", "study"], help="Root object of the query")
    parser.add_argument("keys", nargs="+", help="Query keys")
    parser.set_defaults(function=find)
    return parser

def find(host, port, calling_ae_title, called_ae_title, level, keys):
    query = _odil.DataSet()
    for key in keys:
        if "=" in key:
            key, value = key.split("=", 1)
            value = value.split("\\")
        else:
            value = None
        
        tag = getattr(_odil.registry, key)
        
        if value is not None:
            vr = _odil.registry.public_dictionary[tag].vr
            if vr in ["DS", "FL", "FD"]:
                value = _odil.Value.Reals([float(x) for x in value])
            elif vr in ["IS", "SL", "SS", "UL", "US"]:
                value = _odil.Value.Integers([int(x) for x in value])
            else:
                value = _odil.Value.Strings(value)
                
            query.add(tag, value)
        else:
            query.add(tag)
    
    sop_class = getattr(
        _odil.registry, 
        "{}RootQueryRetrieveInformationModelFIND".format(level.capitalize()))
    
    find_pc = _odil.AssociationParameters.PresentationContext(
        1, sop_class,
        [ _odil.registry.ExplicitVRLittleEndian ], True, False
    )
    
    association = _odil.Association()
    association.set_peer_host(host)
    association.set_peer_port(port)
    association.update_parameters()\
        .set_calling_ae_title(calling_ae_title)\
        .set_called_ae_title(called_ae_title) \
        .set_presentation_contexts([find_pc])
    association.associate()
    logging.info("Association established")
    
    find = _odil.FindSCU(association)
    find.set_affected_sop_class(sop_class)
    data_sets = find.find(query)
    print "{} answer{}".format(len(data_sets), "s" if len(data_sets)>1 else "")
    for data_set in data_sets:
        print_data_set(data_set)
        print

    association.release()
    logging.info("Association released")
