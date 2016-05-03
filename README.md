Odil
=======

Odil is a C++11 library for the [DICOM](http://dicom.nema.org/) standard.

Odil leverages C++ constructs to provide a user-friendly API of the different
parts of the DICOM standard. Included in Odil are exception-based error
handling, generic access to datasets elements, standard JSON and XML
representation of datasets, and generic implementation of messages,
clients and servers for the various DICOM protocols.

Odil also provides conversion to and from
[DCMTK](http://dicom.offis.de/dcmtk.php.en) data structures.

Odil builds and run on:
* Linux (Debian 7 and 8, Ubuntu 12.04, 14.04, and 16.04, all 32 and 64 bits).
  Official packages are available ([Debian](https://packages.debian.org/search?keywords=odil&searchon=sourcenames&suite=all&section=all), [Ubuntu](http://packages.ubuntu.com/search?keywords=odil&searchon=sourcenames&suite=all&section=all)),
  as well as [unofficial backports](https://github.com/lamyj/packages).
    
* OS X

[![Build Status](https://travis-ci.org/lamyj/odil.svg?branch=master)](https://travis-ci.org/lamyj/odil)
[![Coverage Status](https://coveralls.io/repos/lamyj/odil/badge.svg)](https://coveralls.io/r/lamyj/odil)
