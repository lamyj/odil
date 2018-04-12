import contextlib
import warnings

from ._odil import *

_open = open

@contextlib.contextmanager
def open(path, mode="rb"):
    fd = _open(path, mode)
    stream = iostream(fd)
    yield stream
    fd.close()

def read(path, keep_group_length=False, halt_condition=None):
    warnings.warn("odil.read is deprecated. Use odil.open instead")
    with open(path) as stream:
        return Reader.read_file(stream, keep_group_length, halt_condition)

def write(
        data_set, path, meta_information=DataSet(),
        transfer_syntax=registry.ExplicitVRLittleEndian,
        item_encoding=Writer.ItemEncoding.ExplicitLength,
        use_group_length=False):
    warnings.warn("odil.write is deprecated. Use odil.open instead")
    with open(path, "wb") as stream:
        Writer.write_file(
            data_set, stream, meta_information, transfer_syntax, item_encoding,
            use_group_length)
