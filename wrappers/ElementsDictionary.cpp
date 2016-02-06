/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include <odil/ElementsDictionary.h>

void wrap_ElementsDictionary()
{
    using namespace boost::python;
    using namespace odil;

    class_<ElementsDictionaryEntry>(
        "ElementsDictionaryEntry",
        init<std::string, std::string, std::string, std::string>()
    )
        .def_readwrite("name", &ElementsDictionaryEntry::name)
        .def_readwrite("keyword", &ElementsDictionaryEntry::keyword)
        .def_readwrite("vr", &ElementsDictionaryEntry::vr)
        .def_readwrite("vm", &ElementsDictionaryEntry::vm)
    ;

    class_<ElementsDictionary>("ElementsDictionary")
        .def(map_indexing_suite<ElementsDictionary>())
    ;
}

