# Odil

[![Build Status (Travis)](https://travis-ci.com/lamyj/odil.svg?branch=master)](https://travis-ci.com/lamyj/odil)
[![Build Status (Appveyor)](https://ci.appveyor.com/api/projects/status/github/lamyj/odil?svg=true)](https://ci.appveyor.com/project/lamyj/odil)
[![Conda Version](https://img.shields.io/conda/vn/conda-forge/odil.svg)](https://anaconda.org/conda-forge/odil)

Odil is a [DICOM][] library which provides a user-friendly C++11 and Python API for the different parts of the DICOM standard:
- Reading and writing data sets with any transfer syntax
- Standard JSON and XML representation of datasets
- Clients and servers for the various DICOM protocols (C-FIND, C-GET, C-MOVE, C-STORE)
- Implementation of the DICOM web-services (WADO-RS, QIDO-RS, STOW-RS)
- Conversion to and from [DCMTK][] data structures.

Packaged versions of Odil are available on [Anaconda][] for Linux, macOS and Windows. Official packages are available for [Debian][] and [Ubuntu][], as well as [unofficial backports][].

Installation and usage instructions are available on the [documentation website][].

[Anaconda]: https://anaconda.org/conda-forge/odil
[DCMTK]: http://dicom.offis.de/dcmtk.php.en
[Debian]: https://packages.debian.org/search?keywords=odil&searchon=sourcenames&suite=all&section=all
[DICOM]: http://dicom.nema.org/
[documentation website]: http://odil.readthedocs.io/
[Ubuntu]: http://packages.ubuntu.com/search?keywords=odil&searchon=sourcenames&suite=all&section=all
[unofficial backports]: https://github.com/lamyj/packages
