import logging

import _odil

def add_subparser(subparsers):
    parser = subparsers.add_parser(
        "print", help="Print the contents of data sets")
    parser.add_argument("inputs", nargs="+", metavar="FILE")
    parser.add_argument("--print-header", "-H", action="store_true")
    parser.add_argument("--decode-uids", "-u", action="store_true")
    parser.set_defaults(function=print_)

def print_(inputs, print_header, decode_uids):
    for input in inputs:
        logging.info("Printing {}".format(input))
        header, data_set = _odil.read(input)
        if print_header:
            print_data_set(header, decode_uids)
        print_data_set(data_set, decode_uids)

def print_data_set(data_set, decode_uids=False, padding=""):
    max_length = 0
    for tag in data_set.keys():
        if tag in _odil.registry.public_dictionary:
            entry = _odil.registry.public_dictionary[tag]
            max_length = max(max_length, len(entry.name))

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
            name, (max_length-len(name))*" ",
            tag.group, tag.element, element.vr,
            value)

        if element.is_data_set():
            sequence = element.as_data_set()
            if sequence:
                for item in sequence[:-1]:
                    print_data_set(item, decode_uids, padding+"  ")
                    print
                print_data_set(sequence[-1], padding+"  ")
