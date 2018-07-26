Name: odil
Summary: C++11 library for the DICOM standard (libraries)
Version: 0.9.2
Release: 1%{?dist}
License: CeCILL-B
Source0: https://github.com/lamyj/odil/archive/v%{version}.tar.gz
URL: https://github.com/lamyj/odil

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
BuildRequires: graphviz
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
%autosetup

%build
mkdir -p documentation/_build
cd documentation
doxygen
find _build -name "*.md5" -delete
cd ..
sed -i 's/DESTINATION lib/DESTINATION %{_lib}/g' src/CMakeLists.txt
mkdir build
cd build
%cmake \
  -DBUILD_EXAMPLES=OFF \
  -DBUILD_TESTING=OFF \
  -DBUILD_PYTHON_WRAPPERS=ON \
  -DBUILD_JAVASCRIPT_WRAPPERS=OFF \
  -DWITH_DCMTK=OFF \
  ..
%make_build
#../tests/run --no-network -e ".*"

%install
cd build
%make_install
cd ..
mkdir -p %{buildroot}%{_mandir}/man1/
LD_LIBRARY_PATH=%{buildroot}%{_libdir} \
  PYTHONPATH=%{buildroot}%{_libdir}/python2.7/site-packages/ \
  help2man -o %{buildroot}%{_mandir}/man1/odil.1 --version-string=%{version} %{buildroot}%{_bindir}/odil

%files
%{_libdir}/lib%{name}.so.*

%files devel
%{_includedir}/*
%{_libdir}/lib%{name}.so

%files doc
%doc documentation/_build/doxygen
%doc README.md

%files -n python2-%{name}
%{_libdir}/python%{python2_version}/site-packages/%{name}/_%{name}.so
%{_libdir}/python%{python2_version}/site-packages/%{name}/*.py
%{_libdir}/python%{python2_version}/site-packages/%{name}/*.py?

%files cli
%{_bindir}/*
%{_libdir}/python%{python2_version}/site-packages/%{name}/cli/*
%{_mandir}/man1/*

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%changelog
* Thu Jul 26 2018 Julien Lamy <lamy@unistra.fr> 0.9.2-1
- New upstream release
* Fri Apr 21 2017 Julien Lamy <lamy@unistra.fr> 0.8.0-1
- Initial release
