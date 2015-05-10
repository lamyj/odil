/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _8424446e_1153_4acc_9f57_e86faa7246e3
#define _8424446e_1153_4acc_9f57_e86faa7246e3

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "dcmtkpp/Element.h"
#include "dcmtkpp/Value.h"

namespace dcmtkpp
{

#define dcmtkppElementTypeMacro(name, Type) \
bool is_##name(Tag const & tag) const \
{ \
    auto const it = this->_find(tag); \
    if(it == this->_elements.end()) \
    { \
        throw Exception("No such element"); \
    } \
    return it->second.is_##name(); \
} \
Value::Type const & as_##name(Tag const & tag) const \
{ \
    auto const it = this->_find(tag); \
    if(it == this->_elements.end()) \
    { \
        throw Exception("No such element"); \
    } \
    return it->second.as_##name(); \
} \
Value::Type & as_##name(Tag const & tag) \
{ \
    auto const it = this->_find(tag); \
    if(it == this->_elements.end()) \
    { \
        throw Exception("No such element"); \
    } \
    return it->second.as_##name(); \
} 

/**
 * @brief DICOM Data set.
 */
class DataSet
{
public:
    /// @brief Create an empty data set.
    DataSet();

    /// @brief Add an empty element to the dataset.
    void add(Tag const & tag, VR const & vr);

    /**
     * @brief Add an empty element to the dataset, the VR is guessed.
     *
     * If the VR cannot be guessed (i.e. not in public data dictionary), a
     * dcmtkpp::Exception is raised.
     */
    void add(Tag const & tag);

    /**
     * @brief Remove an element from the data set.
     *
     * If the element is not in the data set, a dcmtkpp::Exception is raised.
     */
    void remove(Tag const & tag);

    /// @brief Test whether the data set is empty.
    bool empty() const;

    /// @brief Return the number of elements in the data set.
    std::size_t size() const;

    /// @brief Test whether an element is in the data set.
    bool has(Tag const & tag) const;

    /**
     * @brief Return the VR of an element in the data set.
     *
     * If the element is not in the data set, a dcmtkpp::Exception is raised.
     */
    VR get_vr(Tag const & tag) const;

    /**
     * @brief Test whether an element of the data set is empty.
     *
     * If the element is not in the data set, a dcmtkpp::Exception is raised.
     */
    bool empty(Tag const & tag) const;

    /**
     * @brief Return the number of values in an element of the data set.
     *
     * If the element is not in the data set, a dcmtkpp::Exception is raised.
     */
    std::size_t size(Tag const & tag) const;

    dcmtkppElementTypeMacro(int, Integers);
    dcmtkppElementTypeMacro(real, Reals);
    dcmtkppElementTypeMacro(string, Strings);
    dcmtkppElementTypeMacro(data_set, DataSets);

    typedef std::map<uint32_t, Element>::const_iterator const_iterator;
    const_iterator begin() const { return this->_elements.begin(); }
    const_iterator end() const { return this->_elements.end(); }

    // FIXME: AT, binary

private:
    typedef std::map<uint32_t, Element> ElementMap;

    ElementMap _elements;

    static uint32_t _as_numeric_tag(Tag const & tag);

    static bool _is_int_vr(VR vr);
    static bool _is_real_vr(VR vr);
    static bool _is_string_vr(VR vr);

    ElementMap::const_iterator _find(Tag const & tag) const;
    ElementMap::iterator _find(Tag const & tag);
};

}

#endif // _8424446e_1153_4acc_9f57_e86faa7246e3
