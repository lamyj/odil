import subprocess

data = subprocess.check_output(["brew", "ls", "--versions"]).decode()
versions = {}
for line in data.splitlines():
    if not line:
        continue
    items = [x for x in line.split(" ") if x]
    package = items[0].rsplit("@", 1)[0]
    versions.setdefault(package, []).extend(items[1:])

data = subprocess.check_output(["brew", "outdated"]).decode()
outdated = [x.split(" ")[0] for x in data.splitlines() if x]

install = []
upgrade = []
for package in ["boost", "cmake", "dcmtk", "icu4c", "jsoncpp", "pybind11"]:
    if package not in versions:
        install.append(package)
    elif package in outdated:
        upgrade.append(package)
    else:
        continue
    
subprocess.check_call(["brew", "upgrade", *upgrade])
subprocess.check_call(["brew", "install", *install])
