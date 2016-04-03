import logging

import _odil

def add_subparser(subparsers):
    parser = subparsers.add_parser(
        "print", help="Print the contents of data sets")
    parser.add_argument("inputs", nargs="+", metavar="FILE", help="Input files")
    parser.add_argument(
        "--print-header", "-H", action="store_true",
        help="Print the header as well as the data set")
    parser.add_argument(
        "--decode-uids", "-u", action="store_true",
        help="Print human-friendly name of known UIDs")
    parser.set_defaults(function=print_)
    return parser

def print_(inputs, print_header, decode_uids):
    for input in inputs:
        logging.info("Printing {}".format(input))
        header, data_set = _odil.read(input)
        if print_header:
            print_data_set(header, decode_uids)
        print_data_set(data_set, decode_uids)

def print_data_set(data_set, decode_uids=False, padding="", max_length=None):
    if max_length is None:
        max_length = find_max_name_length(data_set)

    for tag, element in data_set.items():
        name = "{:04x},{:04x}".format(tag.group, tag.element)
        if tag in _odil.registry.public_dictionary:
            entry = _odil.registry.public_dictionary[tag]
            name = entry.name

        if element.is_data_set():
            value = ""
        elif element.is_binary():
            length = len(element.as_binary())
            value = "(binary, {} byte{})".format(length, "s" if length>1 else "")
        else:
            getter = None
            if element.is_int():
                getter = element.as_int
            elif element.is_real():
                getter = element.as_real
            elif element.is_string():
                getter = element.as_string
            value = [x for x in getter()]

            if decode_uids and element.vr == _odil.VR.UI:
                value = [
                    _odil.registry.uids_dictionary[uid].name
                        if uid in _odil.registry.uids_dictionary else uid
                    for uid in value
                ]

        print "{}{}{} {:04x},{:04x} {} {}".format(
            padding,
            name, (max_length-len(name)-len(padding))*" ",
            tag.group, tag.element, element.vr,
            value)

        if element.is_data_set():
            sequence = element.as_data_set()
            if sequence:
                for item in sequence[:-1]:
                    print_data_set(item, decode_uids, padding+"  ", max_length)
                    print
                print_data_set(sequence[-1], decode_uids, padding+"  ", max_length)

def find_max_name_length(data_set, max_length=0, padding_length=0):
    for tag, element in data_set.items():
        if tag in _odil.registry.public_dictionary:
            entry = _odil.registry.public_dictionary[tag]
            length = len(entry.name)
        else:
            length = 9 # xxxx,yyyy
        max_length = max(max_length, padding_length+length)
        if element.is_data_set():
            sequence = element.as_data_set()
            for item in sequence:
                max_length = max(
                    max_length,
                    find_max_name_length(item, max_length, 2+padding_length))
    return max_length
