Name: odil
Summary: C++11 library for the DICOM standard (libraries)
Version: 0.8.0
Release: 1%{?dist}
License: CeCILL-B
Source0: https://github.com/lamyj/odil/archive/v%{version}.tar.gz
URL: https://github.com/lamyj/odil

Patch1: odil-cli-import-path.patch

BuildRequires: cmake
BuildRequires: gcc-c++
BuildRequires: make
BuildRequires: pkgconfig

BuildRequires: boost-devel
#BuildRequires: dcmtk-devel
BuildRequires: pkgconfig(icu-uc)
BuildRequires: pkgconfig(jsoncpp)
BuildRequires: pkgconfig(log4cpp)
BuildRequires: pkgconfig(uuid)

BuildRequires: python2-devel
#BuildRequires: python-nose
# boost-python is only compiled for Python 2: skip Python 3-related packages

BuildRequires: doxygen
BuildRequires: help2man

%description
Odil leverages C++ constructs to provide a user-friendly API of the
different parts of the DICOM standard. Included in Odil are exception-based
error handling, generic access to datasets elements, standard JSON and XML
representation of datasets, and generic implementation of messages, clients
and servers for the various DICOM protocols.

This package contains the libraries.

#----------------------------------------------------------------------------

%package devel

Summary: C++11 library for the DICOM standard (development files)
Requires: %{name} = %{version}-%{release}

%description devel
Odil leverages C++ constructs to provide a user-friendly API of the
different parts of the DICOM standard. Included in Odil are exception-based
error handling, generic access to datasets elements, standard JSON and XML
representation of datasets, and generic implementation of messages, clients
and servers for the various DICOM protocols.

This package contains the development files.

#----------------------------------------------------------------------------

%package doc

Summary: C++11 library for the DICOM standard (documentation)
Requires: %{name} = %{version}-%{release}

%description doc
Odil leverages C++ constructs to provide a user-friendly API of the
different parts of the DICOM standard. Included in Odil are exception-based
error handling, generic access to datasets elements, standard JSON and XML
representation of datasets, and generic implementation of messages, clients
and servers for the various DICOM protocols.

This package contains the documentation.

#----------------------------------------------------------------------------

%package -n python2-%{name}

Summary: C++11 library for the DICOM standard (Python 2 wrappers)
Requires: %{name} = %{version}-%{release}, python

%description -n python2-%{name}
Odil leverages C++ constructs to provide a user-friendly API of the
different parts of the DICOM standard. Included in Odil are exception-based
error handling, generic access to datasets elements, standard JSON and XML
representation of datasets, and generic implementation of messages, clients
and servers for the various DICOM protocols.

This package contains the Python wrappers.

#----------------------------------------------------------------------------

%package cli

Summary: C++11 library for the DICOM standard (command-line application)
Requires: python2-%{name} = %{version}-%{release}
BuildArch: noarch

%description cli
Odil leverages C++ constructs to provide a user-friendly API of the
different parts of the DICOM standard. Included in Odil are exception-based
error handling, generic access to datasets elements, standard JSON and XML
representation of datasets, and generic implementation of messages, clients
and servers for the various DICOM protocols.

This package contains the command-line application.

#----------------------------------------------------------------------------

%prep
%autosetup -p1

%build
doxygen
sed -i 's/DESTINATION lib/DESTINATION %{_lib}/g' src/CMakeLists.txt
mkdir build
cd build
%cmake \
  -DBUILD_EXAMPLES=OFF \
  -DBUILD_TESTING=OFF \
  -DBUILD_WRAPPERS=ON \
  -DWITH_DCMTK=OFF \
  ..
%make_build
#../tests/run --no-network -e ".*"

%install
cd build
make install DESTDIR=%{buildroot}
cd ..
mkdir -p %{buildroot}%{_bindir} %{buildroot}/usr/share/%{name} %{buildroot}%{_mandir}/man1/
install -m 644 applications/*py %{buildroot}/usr/share/%{name}
install -m 755 applications/odil %{buildroot}%{_bindir}
LD_LIBRARY_PATH=%{buildroot}%{_libdir} \
  PYTHONPATH=%{buildroot}/usr/share/odil:%{buildroot}%{_libdir}/python2.7/site-packages/ \
  help2man -o %{buildroot}%{_mandir}/man1/odil.1 --version-string=%{version} %{buildroot}%{_bindir}/odil

%files
%{_libdir}/*.so.*
%doc README.md

%files devel
%{_includedir}/*
%{_libdir}/*.so
%doc README.md

%files doc
%doc doc/*
%doc README.md

%files -n python2-%{name}
%{_libdir}/python2.7/site-packages/*
%doc README.md

%files cli
%{_bindir}/*
/usr/share/%{name}
%doc README.md
%{_mandir}/man1/*

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%changelog
* Fri Apr 21 2017 Julien Lamy <lamy@unistra.fr> 0.8.0-1
- Initial release
