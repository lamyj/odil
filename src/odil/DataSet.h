/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
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

#include "odil/Element.h"
#include "odil/Value.h"

namespace odil
{

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
     * If the element is not in the data set, a odil::Exception is raised.
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
     * If the element is not in the data set, a odil::Exception is raised.
     */
    VR get_vr(Tag const & tag) const;

    /**
     * @brief Test whether an element of the data set is empty.
     *
     * If the element is not in the data set, a odil::Exception is raised.
     */
    bool empty(Tag const & tag) const;

    /**
     * @brief Return the number of values in an element of the data set.
     *
     * If the element is not in the data set, a odil::Exception is raised.
     */
    std::size_t size(Tag const & tag) const;

    /**
     * @brief Access the given element.
     *
     * If the element is not in the data set, a odil::Exception is raised.
     */
    Element const & operator[](Tag const & tag) const;

    /**
     * @brief Access the given element.
     *
     * If the element is not in the data set, a odil::Exception is raised.
     */
    Element & operator[](Tag const & tag);

    /// @brief Test whether an existing element has integer type.
    bool is_int(Tag const & tag) const;
    
    /// @brief Return the integers contained in an existing element (read-only).
    Value::Integers const & as_int(Tag const & tag) const;
    
    /// @brief Return the integers contained in an existing element (read-write).
    Value::Integers & as_int(Tag const & tag);
    
    /// @brief Return an integer contained in an existing element (read-only).
    Value::Integer const & as_int(Tag const & tag, unsigned int position) const;
    
    /// @brief Test whether an existing element has real type.
    bool is_real(Tag const & tag) const;
    
    /// @brief Return the reals contained in an existing element (read-only).
    Value::Reals const & as_real(Tag const & tag) const;
    
    /// @brief Return the reals contained in an existing element (read-write).
    Value::Reals & as_real(Tag const & tag);
    
    /// @brief Return an real contained in an existing element (read-only).
    Value::Real const & as_real(Tag const & tag, unsigned int position) const;
    
    /// @brief Test whether an existing element has string type.
    bool is_string(Tag const & tag) const;
    
    /// @brief Return the strings contained in an existing element (read-only).
    Value::Strings const & as_string(Tag const & tag) const;
    
    /// @brief Return the strings contained in an existing element (read-write).
    Value::Strings & as_string(Tag const & tag);
    
    /// @brief Return a string contained in an existing element (read-only).
    Value::String const & as_string(Tag const & tag, unsigned int position) const;
    
    /// @brief Test whether an existing element has data set type.
    bool is_data_set(Tag const & tag) const;
    
    /// @brief Return the data sets contained in an existing element (read-only).
    Value::DataSets const & as_data_set(Tag const & tag) const;
    
    /// @brief Return the data sets contained in an existing element (read-write).
    Value::DataSets & as_data_set(Tag const & tag);
    
    /// @brief Return a data set contained in an existing element (read-only).
    DataSet const & as_data_set(Tag const & tag, unsigned int position) const;
    
    /// @brief Test whether an existing element has binary type.
    bool is_binary(Tag const & tag) const;
    
    /// @brief Return the binary items contained in an existing element (read-only).
    Value::Binary const & as_binary(Tag const & tag) const;
    
    /// @brief Return the binary items contained in an existing element (read-write).
    Value::Binary & as_binary(Tag const & tag);
    
    /// @brief Return a binary item contained in an existing element (read-only).
    Value::Binary::value_type const & 
    as_binary(Tag const & tag, unsigned int position) const;

    typedef std::map<Tag, Element>::const_iterator const_iterator;
    
    /// @brief Return an iterator to the start of the elements.
    const_iterator begin() const { return this->_elements.begin(); }
    
    /// @brief Return an iterator to the end of the elements.
    const_iterator end() const { return this->_elements.end(); }

    /// @brief Equality test.
    bool operator==(DataSet const & other) const;

    /// @brief Difference test.
    bool operator!=(DataSet const & other) const;

private:
    typedef std::map<Tag, Element> ElementMap;

    ElementMap _elements;
};

}

#endif // _8424446e_1153_4acc_9f57_e86faa7246e3
