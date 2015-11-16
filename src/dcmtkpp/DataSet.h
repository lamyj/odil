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
#include <initializer_list>
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
    auto const it = this->_elements.find(tag); \
    if(it == this->_elements.end()) \
    { \
        throw Exception("No such element"); \
    } \
    return it->second.is_##name(); \
} \
Value::Type const & as_##name(Tag const & tag) const \
{ \
    auto const it = this->_elements.find(tag); \
    if(it == this->_elements.end()) \
    { \
        throw Exception("No such element"); \
    } \
    return it->second.as_##name(); \
} \
Value::Type::value_type const & as_##name(Tag const & tag, int position) const \
{ \
    auto const & data = this->as_##name(tag); \
    if(data.size() <= position) \
    { \
        throw Exception("No such element"); \
    } \
    return data[position]; \
} \
Value::Type & as_##name(Tag const & tag) \
{ \
    auto const it = this->_elements.find(tag); \
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

    /// @brief Add an element to the dataset.
    void add(Tag const & tag, Element const & element);

    /// @brief Add an empty element to the dataset.
    void add(Tag const & tag, VR vr=VR::UNKNOWN);

    /// @brief Add an element to the dataset.
    void add(
        Tag const & tag, Value::Integers const & value, VR vr=VR::UNKNOWN);

    /// @brief Add an element to the dataset.
    void add(
        Tag const & tag, Value::Reals const & value, VR vr=VR::UNKNOWN);

    /// @brief Add an element to the dataset.
    void add(
        Tag const & tag, Value::Strings const & value, VR vr=VR::UNKNOWN);

    /// @brief Add an element to the dataset.
    void add(
        Tag const & tag, Value::DataSets const & value, VR vr=VR::UNKNOWN);

    /// @brief Add an element to the dataset.
    void add(
        Tag const & tag, Value::Binary const & value, VR vr=VR::UNKNOWN);

    /// @brief Add an element to the dataset.
    void add(
        Tag const & tag, std::initializer_list<int> const & value,
        VR vr=VR::UNKNOWN);

    /// @brief Add an element to the dataset.
    void add(
        Tag const & tag, std::initializer_list<Value::Integer> const & value,
        VR vr=VR::UNKNOWN);

    /// @brief Add an element to the dataset.
    void add(
        Tag const & tag, std::initializer_list<Value::Real> const & value,
        VR vr=VR::UNKNOWN);

    /// @brief Add an element to the dataset.
    void add(
        Tag const & tag, std::initializer_list<Value::String> const & value,
        VR vr=VR::UNKNOWN);

    /// @brief Add an element to the dataset.
    void add(
        Tag const & tag, std::initializer_list<DataSet> const & value,
        VR vr=VR::UNKNOWN);

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

    /**
     * @brief Access the given element.
     *
     * If the element is not in the data set, a dcmtkpp::Exception is raised.
     */
    Element const & operator[](Tag const & tag) const;

    /**
     * @brief Access the given element.
     *
     * If the element is not in the data set, a dcmtkpp::Exception is raised.
     */
    Element & operator[](Tag const & tag);

    dcmtkppElementTypeMacro(int, Integers);
    dcmtkppElementTypeMacro(real, Reals);
    dcmtkppElementTypeMacro(string, Strings);
    dcmtkppElementTypeMacro(data_set, DataSets);
    dcmtkppElementTypeMacro(binary, Binary);

    typedef std::map<Tag, Element>::const_iterator const_iterator;
    const_iterator begin() const { return this->_elements.begin(); }
    const_iterator end() const { return this->_elements.end(); }

    /// @brief Equality test
    bool operator==(DataSet const & other) const;

    /// @brief Difference test
    bool operator!=(DataSet const & other) const;

private:
    typedef std::map<Tag, Element> ElementMap;

    ElementMap _elements;
};

}

#endif // _8424446e_1153_4acc_9f57_e86faa7246e3
