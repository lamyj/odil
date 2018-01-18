.. Odil documentation master file, created by
   sphinx-quickstart on Wed Jan 17 15:20:04 2018.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to Odil's documentation!
================================

*Odil* is a C++11 library for the `DICOM`_ standard.

Odil leverages C++ constructs to provide a user-friendly API of the different
parts of the DICOM standard. Included in Odil are:

- Reading and writing data sets with any transfer syntax
- Standard JSON and XML representation of datasets
- Clients and servers for the various DICOM protocols (C-FIND, C-GET, C-MOVE, C-STORE)
- Implementation of the DICOM web-services (WADO-RS, QIDO-RS, STOW-RS)
- Conversion to and from `DCMTK`_ data structures.

Odil builds and run on:

- Linux (Debian 7, 8 and 9; Ubuntu 14.04, and 16.04). Official packages are available in `Debian`_ and `Ubuntu`_, as well as `unofficial backports`_.
- macOS
- Windows

Odil is free software: you can redistribute and/or modify it under the terms of the `CeCILL-B license`_.

Table of contents
-----------------

.. toctree::
  :includehidden:
  :maxdepth: 2
  
  installation/index
  user/index
  developer/index

.. _CeCILL-B license: http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
.. _DCMTK: http://dicom.offis.de/dcmtk.php.en
.. _Debian: https://packages.debian.org/search?keywords=odil&searchon=sourcenames&suite=all&section=all
.. _DICOM: http://dicom.nema.org/
.. _Ubuntu: http://packages.ubuntu.com/search?keywords=odil&searchon=sourcenames&suite=all&section=all
.. _unofficial backports: https://github.com/lamyj/packages/
