from __future__ import print_function
import argparse
import logging
import os
import re

import odil

from print_ import find_max_name_length, print_data_set
from dicomdir import create_dicomdir

def add_subparser(subparsers):
    parser = subparsers.add_parser(
        "get", help="DICOM retrieve (C-GET)",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)
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
    parser.add_argument(
        "--iso-9660", "-I", action="store_true",
        help="Save file names using ISO-9660 compatible file names")
    parser.add_argument(
        "--layout", "-l", choices=["flat", "tree"], default="flat",
        help="Save files in the same directory (flat) or in a "
            "patient/study/series tree (hierarchical)")
    parser.add_argument(
        "--dicomdir", "-D", action="store_true",
        help="Create a DICOMDIR from the retrieved files")
    parser.add_argument(
        "--patient-key", "-p", default=[], action="append",
        help="User-defined keys for PATIENT-level records, "
            "expressed as KEYWORD[:TYPE]. TYPE defaults to 3.")
    parser.add_argument(
        "--study-key", "-S", default=[], action="append",
        help="User-defined keys for STUDY-level records")
    parser.add_argument(
        "--series-key", "-s", default=[], action="append", 
        help="User-defined keys for SERIES-level records")
    parser.add_argument(
        "--image-key", "-i", default=[], action="append",
        help="User-defined keys for IMAGE-level records")
    parser.set_defaults(function=get)
    return parser

def get(
        host, port, calling_ae_title, called_ae_title, level, keys, directory,
        iso_9660, layout, 
        dicomdir, patient_key, study_key, series_key, image_key):

    if dicomdir and not iso_9660:
        raise Exception("Cannot create a DICOMDIR without ISO-9660 filenames")

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
            self.stored = {}
            self.files = []
            self._study_ids = {}
            self._series_ids = {}
        
        def store(self, data_set):
            if layout == "flat":
                directory = ""
            elif layout == "tree":
                # Patient directory: <PatientName> or <PatientID>. 
                patient_directory = None
                if "PatientName" in data_set and data_set.as_string("PatientName"):
                    patient_directory = data_set.as_string("PatientName")[0]
                else:
                    
                    patient_directory = data_set.as_string("PatientID")[0]
                
                # Study directory: <StudyID>_<StudyDescription>, both parts are
                # optional. If both tags are missing or empty, default to a 
                # numeric index based on StudyInstanceUID.
                study_directory = []
                if "StudyID" in data_set and data_set.as_string("StudyID"):
                    study_directory.append(data_set.as_string("StudyID")[0])
                if ("StudyDescription" in data_set and
                        data_set.as_string("StudyDescription")):
                    study_directory.append(
                        data_set.as_string("StudyDescription")[0])
                
                if not study_directory:
                    study_instance_uid = data_set.as_string("StudyInstanceUID")[0]
                    study_directory.append(
                        self._study_ids.setdefault(
                            study_instance_uid, 1+len(self._study_ids)))
                    
                study_directory = "_".join(study_directory)

                # Study directory: <SeriesNumber>_<SeriesDescription>, both 
                # parts are optional. If both tags are missing or empty, default 
                # to a numeric index based on SeriesInstanceUID.
                series_directory = []
                if "SeriesNumber" in data_set and data_set.as_int("SeriesNumber"):
                    series_directory.append(str(data_set.as_int("SeriesNumber")[0]))
                if ("SeriesDescription" in data_set and
                        data_set.as_string("SeriesDescription")):
                    series_directory.append(
                        data_set.as_string("SeriesDescription")[0])
                
                if not series_directory:
                    series_instance_uid = data_set.as_string("series_instance_uid")[0]
                    series_directory.append(
                        self._series_ids.setdefault(
                            series_instance_uid, 1+len(self._series_ids)))
                
                series_directory = "_".join(series_directory)

                if iso_9660:
                    patient_directory = to_iso_9660(patient_directory)
                    study_directory = to_iso_9660(study_directory)
                    series_directory = to_iso_9660(series_directory)
                directory = os.path.join(
                    patient_directory, study_directory, series_directory)
                if not os.path.isdir(os.path.join(self.directory, directory)):
                    os.makedirs(os.path.join(self.directory, directory))
            else:
                raise NotImplementedError()

            self.stored.setdefault(directory, 0)

            if iso_9660:
                filename = "IM{:06d}".format(1+self.stored[directory])
            else:
                filename = data_set.as_string("SOPInstanceUID")[0]

            odil.write(
                data_set, os.path.join(self.directory, directory, filename))

            self.stored[directory] += 1
            self.files.append(os.path.join(directory, filename))
        
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
    if len(os.listdir(directory)):
        logging.warning("{} is not empty".format(directory))
        
    callback = Callback(directory)
    get.get(query, callback.store, callback.get)
    print(
        "Completed: {}, remaining: {}, failed: {}, warning: {}".format(
            callback.completed, callback.remaining, callback.failed, 
            callback.warning))
    
    association.release()
    logging.info("Association released")

    if dicomdir:
        logging.info("Creating DICOMDIR")
        create_dicomdir(
            [os.path.join(directory, x) for x in callback.files],
            directory, patient_key, study_key, series_key, image_key)

def to_iso_9660(value):
    value = value[:8].upper()
    value = re.sub(r"[^A-Z0-9_]", "_", value)
    return value
