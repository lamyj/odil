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
        "cmake",
        "-DPYTHON_EXECUTABLE={}".format(sys.executable),
        "-DCMAKE_BUILD_TYPE=Release",
        "-DCMAKE_INSTALL_PREFIX={}".format(install_dir), 
        *cmake_options,
        workspace],
    cwd=build_dir)

cmake_version = {}
with open(os.path.join(build_dir, "CMakeCache.txt")) as fd:
    for line in fd.readlines():
        match = re.match(r"CMAKE_CACHE_([^_]+)_VERSION:[^=]+=(\d+)", line)
        if match:
            cmake_version[match.group(1)] = int(match.group(2))
cmake_version = tuple(cmake_version[x] for x in ["MAJOR", "MINOR", "PATCH"])

if cmake_version >= (3, 12, 0):
    parallel = ["--parallel", str(multiprocessing.cpu_count())]
else:
    parallel = []
subprocess.check_call(
    [
        "cmake", "--build", ".", "--target", "install", "--config", "Release",
        *parallel],
    cwd=build_dir)
