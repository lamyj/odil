C++ API
=======

The primary programming language of Odil is C++11: other languages (as :doc:`Python <../python/index>` or :doc:`Javascript <../javascript/index>`) are wrappers of the C++ code and try to mimic the C++ API. All classes, functions and variables of Odil are declared in the ``odil`` namespace. The include files reflect the classes: the ``odil::DataSet`` class will be declared in the ``odil/DataSet.h``. 

Odil can be included in another project using e.g.:

::

  find_package(Odil 0.12.0 REQUIRED)
  include_directories(${ODIL_INCLUDE_DIRS})
  ...
  target_link_libraries(... libodil)
  
Odil_DIR might need to be passed as cmake argument if odil was built from source and was not installed to the default location (CMAKE_INSTALL_PREFIX). For example ``cmake -DOdil_DIR=/opt/odil/install/lib/CMake/Odil``.

The full Doxygen reference is also `available`_.

.. toctree::
  :maxdepth: 2
  
  data_sets
  io
  association
  services-scu
  services-scp
  webservices

.. _available: ../../_static/doxygen/index.html
