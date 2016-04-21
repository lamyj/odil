import logging

import odil

from print_ import find_max_name_length, print_data_set

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
    parser.add_argument(
        "--decode-uids", "-u", action="store_true",
        help="Print human-friendly name of known UIDs")
    parser.set_defaults(function=find)
    return parser

def find(host, port, calling_ae_title, called_ae_title, level, keys, decode_uids):
    query = odil.DataSet()
    for key in keys:
        if "=" in key:
            key, value = key.split("=", 1)
            value = value.split("\\")
        else:
            value = None
        
        tag = getattr(odil.registry, key)
        
        if value is not None:
            vr = odil.registry.public_dictionary[tag].vr
            if vr in ["DS", "FL", "FD"]:
                value = [float(x) for x in value]
            elif vr in ["IS", "SL", "SS", "UL", "US"]:
                value = [int(x) for x in value]
            
            query.add(tag, value)
        else:
            query.add(tag)
    
    sop_class = getattr(
        odil.registry,
        "{}RootQueryRetrieveInformationModelFIND".format(level.capitalize()))
    
    find_pc = odil.AssociationParameters.PresentationContext(
        1, sop_class,
        [
            odil.registry.ImplicitVRLittleEndian,
            odil.registry.ExplicitVRLittleEndian
        ], True, False
    )
    
    association = odil.Association()
    association.set_peer_host(host)
    association.set_peer_port(port)
    association.update_parameters()\
        .set_calling_ae_title(calling_ae_title)\
        .set_called_ae_title(called_ae_title) \
        .set_presentation_contexts([find_pc])
    association.associate()
    logging.info("Association established")
    
    find = odil.FindSCU(association)
    find.set_affected_sop_class(sop_class)
    data_sets = find.find(query)
    print "{} answer{}".format(len(data_sets), "s" if len(data_sets)>1 else "")

    max_length = 0
    for data_set in data_sets:
        max_length = max(max_length, find_max_name_length(data_set))

    for data_set in data_sets:
        print_data_set(data_set, decode_uids, "", max_length)
        print

    association.release()
    logging.info("Association released")
