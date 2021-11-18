/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dca5b15b_b8df_4925_a446_d42efe06c923
#define _dca5b15b_b8df_4925_a446_d42efe06c923

#include <cstdint>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include "odil/odil.h"

namespace odil
{

class DataSet;

/**
 * @brief A value held in a DICOM element.
 */
class ODIL_API Value
{
public:
    /// @brief Possible types stored in the value.
    enum class Type
    {
        Integers,
        Reals,
        Strings,
        DataSets,
        Binary
    };

    /// @brief Integer type.
    typedef int64_t Integer;

    /// @brief Real type.
    typedef double Real;

    /// @brief String type.
    typedef std::string String;

    /// @brief Integer container.
    typedef std::vector<Integer> Integers;

    /// @brief Real container.
    typedef std::vector<Real> Reals;

    /// @brief String container.
    typedef std::vector<String> Strings;

    /// @brief Data sets container.
    typedef std::vector<std::shared_ptr<DataSet>> DataSets;

    /// @brief Binary data container.
    typedef std::vector<std::vector<uint8_t>> Binary;

#define ODIL_VALUE_CONSTRUCTORS(type) \
    Value(type const & value); \
    Value(type && value); \
    Value(std::initializer_list<type::value_type> const & value);
    /*
     * No need for a rvalue reference version of std::initializer_list:
     * copying a std::initializer_list does not copy the underlying objects.
     */

    ODIL_VALUE_CONSTRUCTORS(Integers)
    ODIL_VALUE_CONSTRUCTORS(Reals)
    ODIL_VALUE_CONSTRUCTORS(Strings)
    ODIL_VALUE_CONSTRUCTORS(DataSets)
    ODIL_VALUE_CONSTRUCTORS(Binary)
#undef ODIL_VALUE_CONSTRUCTORS

    Value(std::initializer_list<int> const & value);

    Value(std::initializer_list<std::initializer_list<uint8_t>> const & value);

    /** @addtogroup default_operations Default class operations
     * @{
     */
    ~Value() =default;
    Value(Value const &) =default;
    Value(Value &&) =default;
    Value & operator=(Value const &) =default;
    Value & operator=(Value &&) =default;
    /// @}

    /// @brief Return the type store in the value.
    Type get_type() const;

    /// @brief Test whether the value is empty.
    bool empty() const;

    /// @brief Return the number of items.
    std::size_t size() const;

    /**
     * @brief Return the integers contained in the value.
     *
     * If the value does not contain integers, a odil::Exception is raised.
     */
    Integers const & as_integers() const;

    /**
     * @brief Return the integers contained in the value.
     *
     * If the value does not contain integers, a odil::Exception is raised.
     */
    Integers & as_integers();

    /**
     * @brief Return the reals contained in the value.
     *
     * If the value does not contain reals, a odil::Exception is raised.
     */
    Reals const & as_reals() const;

    /**
     * @brief Return the reals contained in the value.
     *
     * If the value does not contain reals, a odil::Exception is raised.
     */
    Reals & as_reals();

    /**
     * @brief Return the strings contained in the value.
     *
     * If the value does not contain strings, a odil::Exception is raised.
     */
    Strings const & as_strings() const;

    /**
     * @brief Return the strings contained in the value.
     *
     * If the value does not contain strings, a odil::Exception is raised.
     */
    Strings & as_strings();

    /**
     * @brief Return the data sets contained in the value.
     *
     * If the value does not contain data sets, a odil::Exception is raised.
     */
    DataSets const & as_data_sets() const;

    /**
     * @brief Return the data sets contained in the value.
     *
     * If the value does not contain data sets, a odil::Exception is raised.
     */
    DataSets & as_data_sets();

    /**
     * @brief Return the binary data contained in the value.
     *
     * If the value does not contain binary data, a odil::Exception is raised.
     */
    Binary const & as_binary() const;

    /**
     * @brief Return the binary data contained in the value.
     *
     * If the value does not contain binary data, a odil::Exception is raised.
     */
    Binary & as_binary();

    /// @brief Equality test.
    bool operator==(Value const & other) const;

    /// @brief Difference test.
    bool operator!=(Value const & other) const;

    /// @brief Clear the value (value.empty() will be true).
    void clear();

private:
    Integers _integers;
    Reals _reals;
    Strings _strings;
    // NOTE: can't use std::vector<DataSet> with forward-declaration of DataSet
    // cf. C++11, 17.6.4.8, last bullet of clause 2
    std::shared_ptr<DataSets> _data_sets;
    Binary _binary;

    Type _type;
};

/**
 * @brief Equality test.
 *
 * This will have priority over the standard operator of std::vector since the
 * latter is templated (cf. 23.3.6.1) and the former is not.
*/
bool ODIL_API operator==(Value::DataSets const & left, Value::DataSets const & right);

/// @brief Difference test.
bool ODIL_API operator!=(Value::DataSets const & left, Value::DataSets const & right);

/**
 * @brief Visitor of values.
 */
template<typename TVisitor>
typename TVisitor::result_type
apply_visitor(TVisitor const & visitor, Value const & value);

/**
 * @brief Visitor of values.
 */
template<typename TVisitor>
typename TVisitor::result_type
apply_visitor(TVisitor const & visitor, Value & value);

}

#include "odil/Value.txx"

#endif // _dca5b15b_b8df_4925_a446_d42efe06c923
