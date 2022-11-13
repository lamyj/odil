import subprocess

subprocess.check_call([
    "conda", "install", "--yes", "-c", "conda-forge",
    "boost", "cmake", "dcmtk", "icu", "jsoncpp", "libssh2", "pkg-config",
    "pybind11"])
