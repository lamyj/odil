from __future__ import print_function
import logging
import os

import odil

from print_ import find_max_name_length, print_data_set

def add_subparser(subparsers):
    parser = subparsers.add_parser(
        "get", help="DICOM retrieve (C-GET)")
    parser.add_argument("host", help="Remote host address")
    parser.add_argument("port", type=int, help="Remote host port")
    parser.add_argument(
        "calling_ae_title", help="AE title of the calling application")
    parser.add_argument(
        "called_ae_title", help="AE title of the called application")
    parser.add_argument(
        "level", choices=["patient", "study"], 
        help="Root object of the retrieval")
    parser.add_argument("keys", nargs="+", help="Retrieve keys")
    parser.add_argument(
        "--directory", "-d", default=os.getcwd(),
        help="Directory where the output files will be stored")
    parser.set_defaults(function=get)
    return parser

def get(host, port, calling_ae_title, called_ae_title, level, keys, directory):
    query = odil.DataSet()
    for key in keys:
        key, value = key.split("=", 1)
        value = value.split("\\")
        
        tag = getattr(odil.registry, key)
        
        vr = odil.registry.public_dictionary[tag].vr
        if vr in ["DS", "FL", "FD"]:
            value = [float(x) for x in value]
        elif vr in ["IS", "SL", "SS", "UL", "US"]:
            value = [int(x) for x in value]
        
        query.add(tag, value)
    
    get_syntax = getattr(
        odil.registry,
        "{}RootQueryRetrieveInformationModelGET".format(level.capitalize()))
    
    transfer_syntaxes = [
        odil.registry.ImplicitVRLittleEndian,
        odil.registry.ExplicitVRLittleEndian
    ]
    
    get_pc = odil.AssociationParameters.PresentationContext(
        1, get_syntax, transfer_syntaxes, True, False)
    
    # Negotiate ALL storage syntaxes. Is there a better way to do this?
    storage_uids = [
        entry.key() for entry in odil.registry.uids_dictionary
        if entry.data().name.endswith("Storage")
    ]
    if len(storage_uids) > 126:
        raise Exception("Too many storage syntaxes")
    storage_pcs = [
        odil.AssociationParameters.PresentationContext(
            2*(i+1)+1, uid, transfer_syntaxes, False, True)
        for i, uid in enumerate(storage_uids)
    ]
    
    association = odil.Association()
    association.set_peer_host(host)
    association.set_peer_port(port)
    association.update_parameters()\
        .set_calling_ae_title(calling_ae_title)\
        .set_called_ae_title(called_ae_title) \
        .set_presentation_contexts([get_pc]+storage_pcs)
    association.associate()
    logging.info("Association established")
    
    get = odil.GetSCU(association)
    get.set_affected_sop_class(get_syntax)
    
    class Callback(object):
        def __init__(self, directory):
            self.directory = directory
            self.completed = 0
            self.remaining = 0
            self.failed = 0
            self.warning = 0
        
        def store(self, data_set):
            uid = data_set.as_string("SOPInstanceUID")[0]
            odil.write(data_set, os.path.join(self.directory, uid))
        
        def get(self, message):
            for type_ in ["completed", "remaining", "failed", "warning"]:
                base = "number_of_{}_sub_operations".format(type_)
                if getattr(message, "has_{}".format(base))():
                    setattr(
                        self, type_, getattr(message, "get_{}".format(base))())
            logging.info(
                "Remaining: {}, completed: {}, failed: {}, warning: {}".format(
                    self.remaining, self.completed, self.failed, self.warning))
        
    if not os.path.isdir(directory):
        os.makedirs(directory)
        
    callback = Callback(directory)
    get.get(query, callback.store, callback.get)
    print(
        "Completed: {}, remaining: {}, failed: {}, warning: {}".format(
            callback.completed, callback.remaining, callback.failed, 
            callback.warning))
    
    association.release()
    logging.info("Association released")
