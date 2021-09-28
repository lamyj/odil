Installation on Linux
=====================

Unofficial packages are provided for stable Debian and Ubuntu versions. After following the `instructions to set up the unofficial repository`_, install the ``odil`` package with the usual tools provided by your distribution, for example ``sudo apt-get install odil``.

This will install the main command-line application as well as the C++ library and the Python wrappers.

If your distribution has no pre-compiled package available, you can compile it from source; refer to the :doc:`generic install instructions <index>` for minimum required versions.

Install dependencies
--------------------

For Debian and Ubuntu, the following package list will allow you to compile the whole library:
  
.. code-block:: bash
  
  sudo apt-get install \
    build-essential cmake ninja-build pkg-config python3 \
    libboost-dev libboost-date-time-dev libboost-exception-dev \
    libboost-log-dev libboost-filesystem-dev libboost-regex-dev \
    libdcmtk2-dev libicu-dev libjsoncpp-dev zlib1g-dev \
    pybind11-dev python3-pybind11 python3-dev \
    libboost-test-dev dcmtk

Build Odil
----------

First, choose where the compiled files will be installed: it can be for example ``$HOME/local``. From the source directory, create a ``build`` directory, configure and run the build:

.. code-block:: bash

  mkdir build
  cd build
  cmake -D CMAKE_INSTALL_PREFIX="${INSTALL_DIR}" ..
  cmake --build .

The ``${INSTALL_DIR}`` in the previous snippet must be replaced with the installation directory.

The compilation can take advantage of a multi-core CPU either by using `make`_ with the ``-jN`` flag (where ``N`` is the number of concurrent tasks, i.e. the number of cores) or by using `Ninja`_.

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

Install Odil
------------

If your install path is a standard system path (e.g. ``/usr`` or ``/usr/local``, being *root* may be required in these cases), no additional step need to be taken. In a user-dependent path or a non-standard system path, you may need to update two environment variables. Assuming your install prefix is ``/some/location``, add ``/some/location/bin`` to your ``PATH``, and ``/some/location/lib`` to your ``LD_LIBRARY_PATH``. With Python wrappers, you should also add ``/some/location/lib/python3.5/site-packages`` (update according to the Python version you built for) to your ``PYTHONPATH``.

.. _instructions to set up the unofficial repository: https://github.com/lamyj/packages
.. _make: https://www.gnu.org/software/make/
.. _Ninja: https://ninja-build.org/
