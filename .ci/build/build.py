import multiprocessing
import os
import re
import subprocess
import sys

cmake_options = sys.argv[1:]

workspace = os.environ["WORKSPACE"]
build_dir = os.environ.get("BUILD_DIR", os.path.join(workspace, "build"))
install_dir = os.environ.get("BUILD_DIR", os.path.join(workspace, "install"))

for dir in [build_dir, install_dir]:
    if not os.path.isdir(dir):
        os.makedirs(dir)

os.environ["CMAKE_PREFIX_PATH"] = os.pathsep.join([
    *os.environ.get("CMAKE_PREFIX_PATH", "").split(os.pathsep),
    os.path.join(os.path.expanduser("~"), "local")
])
subprocess.check_call(
    [
        "cmake", "-G", "Ninja",
        "-DPYTHON_EXECUTABLE={}".format(sys.executable),
        "-DCMAKE_BUILD_TYPE=Release",
        "-DCMAKE_INSTALL_PREFIX={}".format(install_dir), 
        *cmake_options,
        workspace],
    cwd=build_dir)
subprocess.check_call(["ninja", "install"], cwd=build_dir)
