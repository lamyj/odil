import contextlib

from ._odil import *

_open = open

@contextlib.contextmanager
def open(path, mode="r"):
    fd = _open(path, mode)
    stream = iostream(fd)
    yield stream
    fd.close()
