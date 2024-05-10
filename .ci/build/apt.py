import os
import subprocess

os.environ["DEBIAN_FRONTEND"] = "noninteractive"

subprocess.check_call(["apt-get", "update"])

subprocess.check_call([
    "apt-get", "-y", "--no-install-recommends", "install",
    "build-essential", "cmake", "ninja-build", "pkg-config", "python3",
    "libboost-dev", "libboost-date-time-dev", "libboost-exception-dev",
    "libboost-log-dev", "libboost-filesystem-dev", "libboost-regex-dev",
    "libdcmtk-dev", "libicu-dev", "libjsoncpp-dev", "libnsl-dev", "zlib1g-dev",
    "pybind11-dev", "python3-pybind11", "python3-dev",
    "libboost-test-dev", "dcmtk"])
