import logging
import os

import odil

def add_subparser(subparsers):
    parser = subparsers.add_parser(
        "dicomdir",
        help="Create a DICOMDIR")
    parser.add_argument(
        "names", nargs="+", metavar="name", help="DICOM files or directories")
    parser.add_argument(
        "directory", help="Output directory for the DICOMDIR file")
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
    parser.set_defaults(function=create_dicomdir)
    return parser

def create_dicomdir(
        names, directory, patient_key, study_key, series_key, image_key):
    files = []
    for name in names:
        if os.path.isfile(name):
            files.append(os.path.abspath(name))
        elif os.path.isdir(name):
            for dirpath, _, filenames in os.walk(name):
                dirpath = os.path.abspath(dirpath)
                filenames = [os.path.join(dirpath, x) for x in filenames]
                dicom_files = []
                for filename in filenames:
                    try:
                        odil.Reader.read_file(
                            filename, halt_condition=lambda x: True)
                    except:
                        # Not a DICOM file
                        pass
                    else:
                        dicom_files.append(filename)
                files.extend(dicom_files)
    
    directory = os.path.abspath(directory)
    if not all(x.startswith(directory) for x in files):
        raise Exception("All files must be under {}".format(directory))
    
    files = [x[len(directory)+1:] for x in files]
    
    keys = {}
    for level in ["patient", "study", "series", "image"]:
        for entry in locals()["{}_key".format(level)]:
            if ":" in entry:
                tag, type_ = entry.split(":")
            else:
                tag, type_ = entry, "3"
            tag = getattr(odil.registry, tag)
            type_ = int(type_)
            keys.setdefault(level.upper(), []).append((tag, type_))
    
    creator = odil.BasicDirectoryCreator(directory, files, keys)
    creator()
