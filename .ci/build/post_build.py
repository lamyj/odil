import glob
import os
import subprocess
import sys
import time

import distutils.sysconfig

workspace = os.environ["WORKSPACE"]
build_dir = os.environ.get("BUILD_DIR", os.path.join(workspace, "build"))
install_dir = os.environ.get("BUILD_DIR", os.path.join(workspace, "install"))

test_data_dir = os.path.join(workspace, "tests", "data")

# Set-up environment
for name in ["DYLD_LIBRARY_PATH", "LD_LIBRARY_PATH"]:
    os.environ[name] = os.pathsep.join([
        *os.environ.get(name, "").split(os.pathsep),
        os.path.join(install_dir, "lib")])
os.environ["PATH"] = os.pathsep.join([
    *os.environ.get("PATH", "").split(os.pathsep),
    os.path.join(install_dir, "bin"), os.path.join(workspace, "tests", "tools")])
os.environ["PYTHONPATH"] = os.pathsep.join([
    *os.environ.get("PYTHONPATH", "").split(os.pathsep), 
    os.path.join(
        install_dir, distutils.sysconfig.get_python_lib(True, prefix=""))])
os.environ["ODIL_OWN_AET"] = "LOCAL"
os.environ["ODIL_PEER_HOST_NAME"] = "127.0.0.1"
os.environ["ODIL_PEER_PORT"] = "11112"
os.environ["ODIL_PEER_AET"] = "REMOTE"

# Start the Q/R SCP
subprocess.check_call(["dcmqridx", "./", "dataset.dcm"], cwd=test_data_dir)
dcmqrscp = subprocess.Popen(
    ["dcmqrscp", "-ll", "error", "-c", "dcmqrscp.config", "11112"],
    cwd=test_data_dir)
time.sleep(1.)

# Run C++ and Python tests even if the former fails
cpp_tests_return_code = subprocess.call(["ctest"], cwd=build_dir)
python_tests_return_code = subprocess.call(
    [
        sys.executable, "-m", "unittest", "discover",
        "-s", os.path.join(workspace, "tests", "wrappers")], 
    cwd=build_dir)

# Stop the Q/R SCP and clean up
dcmqrscp.terminate()
for path in [
        os.path.join(test_data_dir, "index.dat"),
        *glob.glob(os.path.join(test_data_dir, "RAW_*.dcm"))]:
    os.unlink(path)

# Return non-zero if either C++ or Python tests failed.
sys.exit(max(cpp_tests_return_code, python_tests_return_code))
