/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <Python.h>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include <odil/UIDsDictionary.h>

void wrap_UIDsDictionary()
{
    using namespace boost::python;
    using namespace odil;

    class_<UIDsDictionaryEntry>(
        "UIDsDictionaryEntry",
        init<std::string, std::string, std::string>()
    )
        .def_readwrite("name", &UIDsDictionaryEntry::name)
        .def_readwrite("keyword", &UIDsDictionaryEntry::keyword)
        .def_readwrite("type", &UIDsDictionaryEntry::type)
    ;

    class_<UIDsDictionary>("UIDsDictionary")
        .def(map_indexing_suite<UIDsDictionary>())
    ;
}

