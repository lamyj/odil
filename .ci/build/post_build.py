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
    ["dcmqridx", ".", "dataset.dcm"],
    cwd=os.path.join(workspace, "tests", "data"))

server = subprocess.Popen(
    ["dcmqrscp", "-ll", "warn", "-c", "dcmqrscp.config", "11112"],
    cwd=os.path.join(workspace, "tests", "data"))
time.sleep(1)

# Set-up environment: test-related variables
def prepend_env_path(item, paths):
    return f"{item}{os.pathsep}{paths}" if paths else item
environment = os.environ.copy()
environment["ODIL_OWN_AET"] = "LOCAL"
environment["ODIL_PEER_HOST_NAME"] = "127.0.0.1"
environment["ODIL_PEER_PORT"] = "11112"
environment["ODIL_PEER_AET"] = "REMOTE"
environment["PATH"] = prepend_env_path(
    os.path.join(workspace, "tests", "tools"), environment.get("PATH"))

# Run C++ and Python tests even if the former fails, return non-zero if any
# failed.
return_code = 0

# No extra environment needed for C++ part except for Windows
if os.name == "nt":
    environment["PATH"] = prepend_env_path(bin_dir, environment.get("PATH"))
return_code = max(
    return_code,
    subprocess.call(
        ["ctest", "--output-on-failure"],
        cwd=build_dir, stderr=subprocess.STDOUT, env=environment))

# Python tests require lib configuration
for name in ["DYLD_LIBRARY_PATH", "LD_LIBRARY_PATH"]:
    environment[name] = prepend_env_path(lib_dir, environment.get(name))
environment["PYTHONPATH"] = prepend_env_path(
    python_lib_dir, environment.get("PYTHONPATH"))

return_code = max(
    return_code,
    subprocess.call(
        [sys.executable, "-m", "unittest", "discover", "-s", python_tests_dir], 
        cwd=build_dir, stderr=subprocess.STDOUT, env=environment))

server.terminate()
os.remove(os.path.join(workspace, "tests", "data", "index.dat"))
for path in glob.glob(os.path.join(workspace, "tests", "data", "RAW_*.dcm")):
    os.remove(path)
os.remove(os.path.join(workspace, "tests", "data", "dcmqrscp.config"))

sys.exit(return_code)
