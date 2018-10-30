Installation
============

.. toctree::
  :hidden:
  :maxdepth: 2
  
  linux
  mac

This section describes how to build and deploy Odil on different operating systems (:doc:`Linux <linux>`, :doc:`macOS <mac>`)

The core of Odil depends on:

- C++ 11 (GCC >= 4.7, Clang)
- `CMake`_ (>= 2.8.9)
- `Boost`_ (>= 1.54, uses `Asio`_, `Date Time`_, `Filesystem`_, `Fusion`_, `Log`, `Preprocessor`_, `Property Tree`_, `Spirit`_, `Uuid`_)
- `ICU4C`_ (>= 4.8.1.1)
- `JsonCpp`_ (>= 0.6.0)

Earlier versions of these dependencies might work but are unsupported.

Optional features have additional dependencies:

- DCMTK converter: `DCMTK`_ (>= 3.6.0)
- Python wrappers: `Python`_ (>= 2.7 or >= 3.4) and `Boost.Python`_
- Javascript wrappers: `emscripten`_

Unit tests depend on:

- `DCMTK`_ (>= 3.6.0)
- `Boost Test`_
- `nose`_ (when compiling the Python wrappers)

Getting the code
----------------

The system-specific instructions will detail how to install using pre-compiled packages or from source. Pre-compiled packages are the easiest to use, but may not contain the latest feeatures; building from source will require download the source code of Odil. Archives of stable releases are hosted on `Github`_. Fetch the latest one and decompress it:

.. code-block:: bash

  wget https://github.com/lamyj/odil/archive/v0.10.0.tar.gz
  tar -x -f v0.10.0.tar.gz
  cd odil-0.10.0

You can also clone the `Git repository`_. Note that the latest Git version may not always compile; should it happen, you can keep your clone but check out the latest tagged version:

.. code-block:: bash
  
  git clone https://github.com/lamyj/odil
  cd odil
  git checkout v0.10.0

Building the Python wrappers
----------------------------

When building the Python wrappers, the Python interpreter and libraries default to whatever version is invoked when running ``python`` from a terminal. On a system that has multiple versions of Python and multiple versions of Boost.Python, the required versions should be explicitely specified to avoid version mismatch at link-time, which yield errors at run-time. The following CMake options control this behavior:

- ``PYTHON_EXECUTABLE``: the Python interpreter that will be used when calling the main command-line application, ``odil``
- ``PYTHON_INCLUDE_DIR``: the directory containing the development headers of Python
- ``PYTHON_LIBRARY``: path to the Python library, static or shared
- ``Boost_PYTHON_LIBRARY_DEBUG`` and ``Boost_PYTHON_LIBRARY_RELEASE``: path to the Boost.Python library

.. _Asio: http://www.boost.org/doc/libs/release/libs/asio/
.. _Boost: http://www.boost.org/
.. _Boost.Python: http://www.boost.org/doc/libs/release/libs/python/
.. _Boost Test: http://www.boost.org/doc/libs/release/libs/test/
.. _CMake: https://cmake.org/
.. _Date Time: http://www.boost.org/doc/libs/release/libs/date_time/
.. _DCMTK: http://dicom.offis.de/dcmtk.php.en
.. _emscripten: https://kripken.github.io/emscripten-site/
.. _Filesystem: http://www.boost.org/doc/libs/release/libs/filesystem/
.. _Fusion: http://www.boost.org/doc/libs/release/libs/fusion/doc/html/
.. _Github: https://github.com/lamyj/odil/releases
.. _Git repository: https://github.com/lamyj/odil
.. _ICU4C: https://ssl.icu-project.org/apiref/icu4c/
.. _JsonCpp: https://github.com/open-source-parsers/jsoncpp
.. _nose: https://nose.readthedocs.io/en/latest/testing.html
.. _Preprocessor: http://www.boost.org/doc/libs/release/libs/preprocessor/
.. _Property Tree: http://www.boost.org/doc/libs/release/libs/property_tree/
.. _Python: https://www.python.org/
.. _Spirit: http://www.boost.org/doc/libs/release/libs/spirit/
.. _Uuid: http://www.boost.org/doc/libs/release/libs/uuid/
