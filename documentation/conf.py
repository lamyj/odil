import glob
import os
import re
import shutil
import subprocess

# Make sure Doxygen is up-to-date
if os.environ.get("READTHEDOCS", None) == "True":
    if not os.path.isdir(os.path.join("_build", "doxygen")):
        os.makedirs(os.path.join("_build", "doxygen"))
    subprocess.check_call(["doxygen", "Doxyfile"])
    
    if os.path.isdir(os.path.join("_build", "html", "_static", "doxygen")):
        shutil.rmtree(os.path.join("_build", "html", "_static", "doxygen"))
    os.makedirs(os.path.join("_build", "html", "_static", "doxygen"))
        
    for entry in glob.glob(os.path.join("_build", "doxygen", "html", "*")):
        shutil.move(entry, os.path.join("_build", "html", "_static", "doxygen"))

project = "Odil"
copyright = "2015-2024, Université de Strasbourg-CNRS"
author = "Julien Lamy"

# The short X.Y version
here = os.path.abspath(os.path.dirname(__file__))
with open(os.path.join(here, "..", "CMakeLists.txt")) as fd:
    version = re.search(r"""project\("Odil" VERSION (.+?)\)""", fd.read())
if not version:
    raise Exception("Could not get version from CMakeLists.txt")
version = version.group(1)
# The full version, including alpha/beta/rc tags
release = version

html_theme = "furo"
html_static_path = ["_static"]
html_css_files = ["css/style.css"]
html_title = project
