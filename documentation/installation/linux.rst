Installation on Linux
=====================

Unofficial packages are provided for stable Debian and Ubuntu versions. After following the `instructions to set up the unofficial repository`_, install the ``odil`` package with the usual tools provided by your distribution, for example ``sudo apt-get install odil``.

This will install the main command-line application as well as the C++ library and the Python wrappers.

If your distribution has no pre-compiled package available, you can either compile it from source (see below) or `ask for packaging`_.

Install dependencies
--------------------

For Debian and Ubuntu, the following package list will allow you to compile the whole library:
  
.. code-block:: bash
  
  sudo apt-get install \
    build-essential cmake pkg-config python-minimal \
    libboost-dev libboost-date-time-dev libboost-filesystem-dev \
    libdcmtk2-dev libicu-dev libjsoncpp-dev zlib1g-dev \
    libboost-python-dev python-dev \
    dcmtk libboost-test-dev python-nose

Build Odil
----------

From the source directory, create a ``build`` directory, configure and run the build:

.. code-block:: bash

  mkdir build
  cd build
  cmake ..
  make

The compilation can take advantage of a multi-core CPU either by using `make`_ with the ``-jN`` flag (where ``N`` is the number of concurrent tasks, i.e. the number of cores) or by using `Ninja`_.

Without additional options, this will build the examples, the Python wrappers and the DCMTK converter, but not the Javascript wrappers. The following optinal features are summarized in the table below and may passed to CMake with the ``-D`` flag (for example ``cmake -D BUILD_EXAMPLES=OFF ..``).

+---------------------+-------------------------------+---------------------------+
| Feature             | Option name                   | Possible values           |
+=====================+===============================+===========================+
| Code examples       | ``BUILD_EXAMPLES``            | ``ON`` (default), ``OFF`` |
+---------------------+-------------------------------+---------------------------+
| Python wrappers     | ``BUILD_PYTHON_WRAPPERS``     | ``ON`` (default), ``OFF`` |
+---------------------+-------------------------------+---------------------------+
| Javascript wrappers | ``BUILD_JAVASCRIPT_WRAPPERS`` | ``ON``, ``OFF`` (default) |
+---------------------+-------------------------------+---------------------------+
| DCMTK converter     | ``WITH_DCMTK``                | ``ON`` (default), ``OFF`` |
+---------------------+-------------------------------+---------------------------+

Note that the Python wrappers are required for the command-line application.

Choose the Python version
-------------------------

If you have multiple versions of Python installed, you may need to specify the following extra parameters to CMake to build the Python wrappers for a specific version:

- ``Python_ADDITIONAL_VERSIONS``: the requested Python version number, e.g. ``2.7`` or ``3.6``
- ``PYTHON_EXECUTABLE``: path to the Python interpreter, e.g. ``/usr/bin/python2.7`` or ``/usr/bin/python3.6``
- ``Boost_PYTHON_LIBRARY_DEBUG`` and ``Boost_PYTHON_LIBRARY_RELEASE``: the path to the Boost.Python library, e.g. ``/usr/lib/x86_64-linux-gnu/libboost_python-py27.so``.

Install Odil
------------

You can use the library and applications from the source directory, but it is more convenient to install it. Choose a destination directory on your system, either in your home directory or in a system location (e.g. ``/usr/local`` or ``/opt/odil``). The latter case will probably require you to become *root*. From the *build* directory, re-run CMake and ``make install``:

.. code-block:: bash

  cmake -D CMAKE_INSTALL_PREFIX=/some/location ..
  make install

The ``CMAKE_INSTALL_PREFIX`` option may be specified during the first call to CMake; it is presented in separate steps in this document for readability.

If your install path is a standard system path (e.g. ``/usr`` or ``/usr/local``), no additional step need to be taken. In a user-dependent path or a non-standard system path, you may need to update two environment variables. Assuming your install prefix is ``/some/location``, add ``/some/location/bin`` to your ``PATH``, and ``/some/location/lib`` to your ``LD_LIBRARY_PATH``. With Python wrappers, you should also add ``/some/location/lib/python2.7/site-packages`` (update according to the Python version you built for) to your ``PYTHONPATH``.

.. _ask for packaging: https://github.com/lamyj/odil/issues
.. _instructions to set up the unofficial repository: https://github.com/lamyj/packages
.. _make: https://www.gnu.org/software/make/
.. _Ninja: https://ninja-build.org/
