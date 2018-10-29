/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

#include <odil/ElementsDictionary.h>

#include "opaque_types.h"
#include "type_casters.h"

void wrap_ElementsDictionary(pybind11::module & m)
{
    using namespace pybind11;
    using namespace odil;

    class_<ElementsDictionaryKey>(m, "ElementsDictionaryKey")
        .def(init<>())
        .def(init<Tag>())
        .def(init<std::string>())
    ;

    class_<ElementsDictionaryEntry>(m, "ElementsDictionaryEntry")
        .def(init<std::string, std::string, std::string, std::string>())
        .def_readwrite("name", &ElementsDictionaryEntry::name)
        .def_readwrite("keyword", &ElementsDictionaryEntry::keyword)
        .def_readwrite("vr", &ElementsDictionaryEntry::vr)
        .def_readwrite("vm", &ElementsDictionaryEntry::vm)
    ;

    bind_map<ElementsDictionary>(m, "ElementsDictionary")
        .def("__getitem__",
            [](ElementsDictionary & container, Tag const & key)
            {
                ElementsDictionary::iterator iterator = container.find(key);
                if(iterator == container.end())
                {
                    throw key_error();
                }
                return iterator->second;
            }
        )
        .def("__getitem__",
            [](ElementsDictionary & container, std::string const & key)
            {
                ElementsDictionary::iterator iterator = container.find(key);
                if(iterator == container.end())
                {
                    throw key_error();
                }
                return iterator->second;
            }
        )
        .def(
            "__contains__",
            [](ElementsDictionary const & container, Tag const & key)
            {
                return container.find(key) != container.end();
            }
        )
        .def(
            "__contains__",
            [](ElementsDictionary const & container, std::string const & key)
            {
                return container.find(key) != container.end();
            }
        )
    ;
}
