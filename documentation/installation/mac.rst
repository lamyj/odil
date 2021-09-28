Installation on macOS
=====================

An `unofficial Homebrew formula`_ is provided for macOS. To use it, add a new tap to Homebrew, and install ``odil``:

.. code-block:: bash
  
  brew tap lamyj/odil
  brew install odil

This will install the main command-line application as well as the C++ library and the Python wrappers.

Odil may also be compiled from source. This documentation uses `Homebrew`_ to install dependencies.

Install dependencies
--------------------

The following package list will allow you to compile the whole library:

.. code-block:: bash
  
  brew install boost cmake dcmtk icu4c jsoncpp ninja pkg-config pybind11

Note that if some dependencies are already installed, the previous command will fail; in that case, it can be run as ``brew upgrade`` instead of ``brew install``.

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

.. _Homebrew: https://brew.sh/
.. _make: https://www.gnu.org/software/make/
.. _Ninja: https://ninja-build.org/
.. _unofficial Homebrew formula: https://github.com/lamyj/homebrew-odil
