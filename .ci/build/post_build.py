import glob
import os
import subprocess
import sys
import sysconfig
import time

workspace = os.environ["WORKSPACE"]
build_dir = os.environ.get("BUILD_DIR", os.path.join(workspace, "build"))
install_dir = os.environ.get("INSTALL_DIR", os.path.join(workspace, "install"))

bin_dir = os.path.join(install_dir, "bin")
lib_dir = os.path.join(install_dir, "lib")
python_lib_dir = os.path.join(
    install_dir,
    sysconfig.get_path(
        "purelib", {"posix":"posix_prefix", "nt":"nt"}[os.name], {"base": "."}))
python_tests_dir = os.path.join(workspace, "tests", "wrappers")

subprocess.check_call(
    ["dcmqridx", "./", "dataset.dcm"],
    cwd=os.path.join(workspace, "tests/data"))

server = subprocess.Popen(
    ["dcmqrscp", "-ll", "fatal", "-c", "dcmqrscp.config", "11112"],
    cwd=os.path.join(workspace, "tests/data"))
time.sleep(1)

# Set-up environment: C++ library, Python module and test data location.
for name in ["DYLD_LIBRARY_PATH", "LD_LIBRARY_PATH"]:
    os.environ[name] = os.pathsep.join([
        *os.environ.get(name, "").split(os.pathsep), lib_dir])
os.environ["PATH"] = os.pathsep.join([
    *os.environ.get("PATH", "").split(os.pathsep), bin_dir])
os.environ["PYTHONPATH"] = os.pathsep.join([
    *os.environ.get("PYTHONPATH", "").split(os.pathsep), python_lib_dir])

os.environ |= {
    "ODIL_OWN_AET": "LOCAL",
    "ODIL_PEER_HOST_NAME": "127.0.0.1",
    "ODIL_PEER_PORT": "11112",
    "ODIL_PEER_AET": "REMOTE"}
os.environ["PATH"] = os.pathsep.join([
    *os.environ["PATH"].split(os.pathsep),
    os.path.join(workspace, "tests/tools")])

# Run C++ and Python tests even if the former fails, return non-zero if any
# failed.
return_code = 0
return_code = max(
    return_code,
    subprocess.call(
        ["ctest", "--output-on-failure"],
        cwd=build_dir, stderr=subprocess.STDOUT))
return_code = max(
    return_code,
    subprocess.call(
        [sys.executable, "-m", "unittest", "discover", "-s", python_tests_dir], 
        cwd=build_dir, stderr=subprocess.STDOUT))

server.terminate()
os.remove(os.path.join(workspace, "tests/data", "index.dat"))
for path in glob.glob(os.path.join(workspace, "tests/data/RAW_*.dcm")):
    os.remove(path)

sys.exit(return_code)
