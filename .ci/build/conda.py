import subprocess

subprocess.check_call([
    "conda", "install", "--yes", "-c", "conda-forge", "-c", "bioconda",
    "boost", "cmake", "dcmtk=3.6.7", "icu", "jsoncpp", "libssh2", "pkg-config",
    "pybind11"])
