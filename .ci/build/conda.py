import os
import subprocess
import sys

conda = sys.argv[1] if len(sys.argv) >= 2 else os.environ.get("MAMBA_EXE", "conda")

subprocess.check_call([
    conda, "install", "--yes", "-c", "conda-forge",
    "boost", "cmake", "dcmtk", "icu", "jsoncpp", "ninja", "pkg-config",
    "pybind11", "zlib"])
