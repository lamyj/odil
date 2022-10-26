import os
import subprocess

os.environ["DEBIAN_FRONTEND"] = "noninteractive"
subprocess.check_call([
    "apt-get", "-y", "--no-install-recommends", "install",
    "cmake", "pkg-config", "g++", "make", "python3", "python3-requests",
    "libboost-dev", "libboost-date-time-dev", "libboost-exception-dev",
    "libboost-log-dev", "libboost-filesystem-dev", "libboost-regex-dev",
    "libdcmtk2-dev", "libicu-dev", "libjsoncpp-dev", "zlib1g-dev",
    "pybind11-dev", "python3-dev", "libboost-test-dev", "dcmtk"])
