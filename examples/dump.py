import argparse
import sys

import _odil

def main():
    parser = argparse.ArgumentParser(description="Print content of DICOM file")
    parser.add_argument("file")
    parser.add_argument("--header", "-H", action="store_true", help="Print header")
    arguments = parser.parse_args()

    header, data_set = _odil.read(arguments.file)
    if arguments.header:
        print_data_set(header)
        print
    print_data_set(data_set)

def print_data_set(data_set, padding=""):
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

        print "{}{}{} {:04x},{:04x} {} {}".format(
            padding,
            name, (max_length-len(name))*" ", 
            tag.group, tag.element, element.vr,
            value)

        if element.is_data_set():
            for item in element.as_data_set()[:-1]:
                print_data_set(item, padding+"  ")
                print
            print_data_set(element.as_data_set()[-1], padding+"  ")

if __name__ == "__main__":
    sys.exit(main())
