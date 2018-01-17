# Odil

Odil is a C++11 library for the [DICOM](http://dicom.nema.org/) standard.

Odil leverages C++ constructs to provide a user-friendly API of the different
parts of the DICOM standard. Included in Odil are:
- Reading and writing data sets with any transfer syntax
- Standard JSON and XML representation of datasets
- Clients and servers for the various DICOM protocols (C-FIND, C-GET, C-MOVE, C-STORE)
- Implementation of the DICOM web-services (WADO-RS, QIDO-RS, STOW-RS)
- Conversion to and from [DCMTK](http://dicom.offis.de/dcmtk.php.en) data structures.

Odil builds and run on:

- Linux (Debian 7, 8 and 9; Ubuntu 14.04, and 16.04). Official packages are available ([Debian](https://packages.debian.org/search?keywords=odil&searchon=sourcenames&suite=all&section=all), [Ubuntu](http://packages.ubuntu.com/search?keywords=odil&searchon=sourcenames&suite=all&section=all)), as well as [unofficial backports](https://github.com/lamyj/packages).
- macOS
- Windows

Installation and usage instructions are available on the [documentation website](http://odil.readthedocs.io/).

[![Build Status (Travis)](https://travis-ci.org/lamyj/odil.svg?branch=master)](https://travis-ci.org/lamyj/odil)
[![Build Status (Appveyor)](https://ci.appveyor.com/api/projects/status/github/lamyj/odil?svg=true)](https://ci.appveyor.com/project/lamyj/odil)
[![Coverage Status](https://coveralls.io/repos/lamyj/odil/badge.svg)](https://coveralls.io/r/lamyj/odil)
