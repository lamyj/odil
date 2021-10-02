Installation
============

.. toctree::
  :hidden:
  :maxdepth: 2
  
  linux
  mac

The easiest way to install Odil is to use the pre-compiled packages, either from `Anaconda`_, or from `Debian`_/`Ubuntu`_. For Anaconda packages, simply run ``conda install -c conda-forge odil``. For Debian and Ubuntu packages, packages are available from the official repositories but are usually not the latest version; `unofficial packages`_ are also available: follow the linked instructions to set up the repository, then run ``apt-get install odil``.

To compile from source, you will need a C++ 11 compiler and `CMake`_, as well as several additional libraries: `Boost`_ ≥ 1.58 (`Asio`_, `Date Time`_, `Filesystem`_, `Fusion`_, `Log`_, `Preprocessor`_, `Property Tree`_, `Spirit`_, `Uuid`_), `ICU4C`_ ≥ 55.1, `JsonCpp`_ ≥ 1.7.2 and `pybind11`_ ≥ 2.2.4. Moreover, the DCMTK converter requires `DCMTK`_ ≥ 3.6.1, and unit tests require `Boost Test`_.

The build process consists in 

1. Get the code (cf. below).
2. Inside the directory containing the source code, create a ``build`` directory.
3. From the ``build`` directory, run ``cmake -D CMAKE_INSTALL_PREFIX="${INSTALL_DIR}" ..`` to configure the project (replacing ``${INSTALL_DIR}`` with the destination directory for the installed files).
4. Run ``cmake --build . --target install`` to build and install Odil.

Further sub-sections describe how to build and deploy Odil on different operating systems (:doc:`Linux <linux>`, :doc:`macOS <mac>`) in more details.

Getting the code
----------------

The system-specific instructions will detail how to install using pre-compiled packages or from source. Pre-compiled packages are the easiest to use, but may not contain the latest feeatures; building from source will require download the source code of Odil. Archives of stable releases are hosted on `Github`_. Fetch the latest one and decompress it:

.. code-block:: bash

  wget https://github.com/lamyj/odil/archive/v0.12.1.tar.gz
  tar -x -f v0.12.1.tar.gz
  cd odil-0.12.1

You can also clone the `Git repository`_. Note that the latest Git version may not always compile; should it happen, you can keep your clone but check out the latest tagged version:

.. code-block:: bash
  
  git clone https://github.com/lamyj/odil
  cd odil
  git checkout v0.12.1

Build options
-------------

Without additional options, the examples, the Python wrappers and the DCMTK converter are built. The following optional features are summarized in the table below and may passed to CMake with the ``-D`` flag (for example ``cmake -D BUILD_EXAMPLES=OFF ..``).

.. csv-table:: 
  :header: "Feature", "Option name", "Possible values"
  
  "Code examples", "``BUILD_EXAMPLES``", "``ON`` (default), ``OFF``"
  "Python wrappers", "``BUILD_PYTHON_WRAPPERS``", "``ON`` (default), ``OFF``"
  "Python interpreter", "``PYTHON_EXECUTABLE``", "Defaults to ``python``"
  "Python include directory", "``PYTHON_INCLUDE_DIR``", "Default depending on the interpreter"
  "Python library", "``PYTHON_LIBRARY``", Default depending on the interpreter
  "DCMTK converter", "``WITH_DCMTK``", "``ON`` (default), ``OFF``"

Note that the Python wrappers are required for the command-line application.

When building the Python wrappers, the Python interpreter and libraries default to whatever version is invoked when running ``python`` from a terminal. On a system that has multiple versions of Python and multiple versions of Boost.Python, the required versions should be explicitly specified to avoid version mismatch at link-time, which yield errors at run-time. The following CMake options control this behavior:

- ``PYTHON_EXECUTABLE``: the Python interpreter that will be used when calling the main command-line application, ``odil``
- ``PYTHON_INCLUDE_DIR``: the directory containing the development headers of Python
- ``PYTHON_LIBRARY``: path to the Python library, static or shared

.. _Anaconda: https://anaconda.org/conda-forge/odil/
.. _Asio: http://www.boost.org/doc/libs/release/libs/asio/
.. _Boost: http://www.boost.org/
.. _Boost.Python: http://www.boost.org/doc/libs/release/libs/python/
.. _Boost Test: http://www.boost.org/doc/libs/release/libs/test/
.. _CMake: https://cmake.org/
.. _Date Time: http://www.boost.org/doc/libs/release/libs/date_time/
.. _Debian: https://packages.debian.org/search?keywords=odil&searchon=sourcenames&suite=all&section=all
.. _DCMTK: http://dicom.offis.de/dcmtk.php.en
.. _Filesystem: http://www.boost.org/doc/libs/release/libs/filesystem/
.. _Fusion: http://www.boost.org/doc/libs/release/libs/fusion/doc/html/
.. _Github: https://github.com/lamyj/odil/releases
.. _Git repository: https://github.com/lamyj/odil
.. _ICU4C: https://ssl.icu-project.org/apiref/icu4c/
.. _JsonCpp: https://github.com/open-source-parsers/jsoncpp
.. _Log: http://www.boost.org/doc/libs/release/libs/log/
.. _Preprocessor: http://www.boost.org/doc/libs/release/libs/preprocessor/
.. _Property Tree: http://www.boost.org/doc/libs/release/libs/property_tree/
.. _pybind11: https://pybind11.readthedocs.io/en/stable/
.. _Spirit: http://www.boost.org/doc/libs/release/libs/spirit/
.. _Ubuntu: http://packages.ubuntu.com/search?keywords=odil&searchon=sourcenames&suite=all&section=all
.. _unofficial packages: https://github.com/lamyj/packages/
.. _Uuid: http://www.boost.org/doc/libs/release/libs/uuid/
