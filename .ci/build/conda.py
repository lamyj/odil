import subprocess

subprocess.check_call([
    "conda", "install", "--yes", "-c", "conda-forge",
    "boost", "cmake", "dcmtk", "icu", "jsoncpp", "libssh2", "ninja",
    "pkg-config", "pybind11"])
