import os
import subprocess
import sys

print(f"Building with {sys.executable}")

workspace = os.environ["WORKSPACE"]
build_dir = os.environ.get("BUILD_DIR", os.path.join(workspace, "build"))
install_dir = os.environ.get("INSTALL_DIR", os.path.join(workspace, "install"))

for dir in [build_dir, install_dir]:
    if not os.path.isdir(dir):
        os.makedirs(dir)

subprocess.check_call(
    [
        "cmake", 
        # NOTE: if Ninja is used as a builder, compiler chain defaults to gcc on
        # Windows
        *(["-G", "Ninja"] if os.name != "nt" else []),
        "-DPython_EXECUTABLE={}".format(sys.executable),
        "-DCMAKE_INSTALL_PREFIX={}".format(install_dir), 
        *([os.environ["CMAKE_OPTIONS"]] if "CMAKE_OPTIONS" in os.environ else []),
        workspace],
    cwd=build_dir)

subprocess.check_call(
    [
        "cmake", "--build", ".", "--target", "install", "--config", "Release",
        "--parallel"],
    cwd=build_dir)
