Welcome to Odil's documentation!
================================

*Odil* is a `DICOM`_ library which provides a user-friendly C++11 and Python API for the different parts of the DICOM standard:

- Reading and writing data sets with any transfer syntax
- Standard JSON and XML representation of datasets
- Clients and servers for the various DICOM protocols (C-FIND, C-GET, C-MOVE, C-STORE)
- Implementation of the DICOM web-services (WADO-RS, QIDO-RS, STOW-RS)
- Conversion to and from `DCMTK`_ data structures.

Odil builds and run on Linux, macOS and Windows. `Anaconda`_ packages are available for those three platforms. Official packages are additionally available in `Debian`_ and `Ubuntu`_, as well as `unofficial backports`_.

Odil is free software: you can redistribute and/or modify it under the terms of the `CeCILL-B license`_.

Table of contents
-----------------

.. toctree::
  :includehidden:
  :maxdepth: 2
  
  installation/index
  user/index
  developer/index

.. _Anaconda: https://anaconda.org/conda-forge/odil
.. _CeCILL-B license: http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
.. _DCMTK: http://dicom.offis.de/dcmtk.php.en
.. _Debian: https://packages.debian.org/search?keywords=odil&searchon=sourcenames&suite=all&section=all
.. _DICOM: http://dicom.nema.org/
.. _Homebrew tap: https://github.com/lamyj/homebrew-odil
.. _Ubuntu: http://packages.ubuntu.com/search?keywords=odil&searchon=sourcenames&suite=all&section=all
.. _unofficial backports: https://github.com/lamyj/packages/
