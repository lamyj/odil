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

    auto scope = class_<ElementsDictionaryKey>(m, "ElementsDictionaryKey")
        .def(init<>())
        .def(init<Tag>())
        .def(init<std::string>())
        .def("get_type", &ElementsDictionaryKey::get_type)
        .def("get_tag", &ElementsDictionaryKey::get_tag)
        .def("get_string", &ElementsDictionaryKey::get_string)
        .def("get_string", &ElementsDictionaryKey::get_string)
        .def(
            "set", 
            static_cast<
                void (ElementsDictionaryKey::*)(Tag const)
            >(&ElementsDictionaryKey::set))
        .def(
            "set", 
            static_cast<
                void (ElementsDictionaryKey::*)(std::string const &)
            >(&ElementsDictionaryKey::set))
        .def(self < self)
        .def(self == self)
    ;
    
    enum_<ElementsDictionaryKey::Type>(scope, "Type")
        .value("Tag", ElementsDictionaryKey::Type::Tag)
        .value("String", ElementsDictionaryKey::Type::String)
        .value("None", ElementsDictionaryKey::Type::None)
    ;

    class_<ElementsDictionaryEntry>(m, "ElementsDictionaryEntry")
        .def(init<std::string, std::string, std::string, std::string>())
        .def_readwrite("name", &ElementsDictionaryEntry::name)
        .def_readwrite("keyword", &ElementsDictionaryEntry::keyword)
        .def_readwrite("vr", &ElementsDictionaryEntry::vr)
        .def_readwrite("vm", &ElementsDictionaryEntry::vm)
    ;
    
    auto ElementsDictionary_cl = bind_map<ElementsDictionary>(m, "ElementsDictionary")
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
        );
#if PYBIND11_VERSION_HEX >= 0x02080000    
    // WARNING: pybind11 2.8.0 adds a fallback to __contains__ when the type
    // of the searched item does not match the key type of the dictionary.
    // Remove *all* __contains__ overloads and rewrap
    delattr(ElementsDictionary_cl, "__contains__");
    ElementsDictionary_cl
        .def(
            "__contains__",
            [](ElementsDictionary & container, ElementsDictionaryKey const & key)
            {
                return container.find(key) != container.end();
            }
        )
#else
    ElementsDictionary_cl
#endif
        .def(
            "__contains__",
            [](ElementsDictionary & container, Tag const & key)
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
