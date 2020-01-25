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
  
  brew install \
    cmake pkg-config \
    boost dcmtk icu4c jsoncpp pybind11 python
  pip install nose

Build Odil
----------

From the source directory, create a ``build`` directory, configure and run the build:

.. code-block:: bash

  mkdir build
  cd build
  
  export PKG_CONFIG_PATH=/usr/local/opt/icu4c/lib/pkgconfig

  cmake ..
  make

.. note::

	Add ``-D Boost_NO_BOOST_CMAKE=ON`` with brew and boost 1.71.0

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

Install Odil
------------

You can use the library and applications from the source directory, but it is more convenient to install it. Choose a destination directory on your system, either in your home directory or in a system location (e.g. ``/usr/local`` or ``/opt/odil``). The latter case will probably require you to become *root*. From the *build* directory, re-run CMake and ``make install``:

.. code-block:: bash

  cmake -D CMAKE_INSTALL_PREFIX=/some/location ..
  make install

The ``CMAKE_INSTALL_PREFIX`` option may be specified during the first call to CMake; it is presented in separate steps in this document for readability.

If your install path is a standard system path (e.g. ``/usr/local``), no additional step need to be taken. In a user-dependent path or a non-standard system path, you may need to update two environment variables. Assuming your install prefix is ``/some/location``, add ``/some/location/bin`` to your ``PATH``, and ``/some/location/lib`` to your ``LD_LIBRARY_PATH``. With Python wrappers, you should also add ``/some/location/lib/python2.7/site-packages`` (update according to the Python version you built for) to your ``PYTHONPATH``.

.. _Homebrew: https://brew.sh/
.. _make: https://www.gnu.org/software/make/
.. _Ninja: https://ninja-build.org/
.. _unofficial Homebrew formula: https://github.com/lamyj/homebrew-odil
