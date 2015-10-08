/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dca5b15b_b8df_4925_a446_d42efe06c923
#define _dca5b15b_b8df_4925_a446_d42efe06c923

#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

namespace dcmtkpp
{

class DataSet;

/**
 * @brief A value held in a DICOM element.
 */
class Value
{
public:
    /// @brief Possible types stored in the value.
    enum class Type
    {
        Empty,
        Integers,
        Reals,
        Strings,
        DataSets,
        Binary
    };

    typedef int64_t Integer;

    typedef double Real;

    typedef std::string String;

    /// @brief Integer container.
    typedef std::vector<Integer> Integers;

    /// @brief Real container.
    typedef std::vector<Real> Reals;

    /// @brief String container.
    typedef std::vector<String> Strings;

    /// @brief Data sets container.
    typedef std::vector<DataSet> DataSets;

    /// @brief Binary data container.
    typedef std::vector<uint8_t> Binary;

    /// @brief Build an empty value.
    Value();

    /// @brief Build a value from integers.
    Value(Integers const & integers);

    /// @brief Build a value from reals.
    Value(Reals const & reals);

    /// @brief Build a value from strings.
    Value(Strings const & strings);

    /// @brief Build a value from data sets.
    Value(DataSets const & datasets);

    /// @brief Build a value from binary data.
    Value(Binary const & binary);

    /// @brief Build a value from integers.
    Value(std::initializer_list<int> const & list);

    /// @brief Build a value from integers.
    Value(std::initializer_list<Integer> const & list);

    /// @brief Build a value from reals.
    Value(std::initializer_list<Real> const & list);

    /// @brief Build a value from strings.
    Value(std::initializer_list<String> const & list);

    /// @brief Build a value from data sets.
    Value(std::initializer_list<DataSet> const & list);

    /// @brief Return the type store in the value.
    Type get_type() const;

    /// @brief Test whether the value is empty.
    bool empty() const;

    /**
     * @brief Return the integers contained in the value.
     *
     * If the value does not contain integers, a dcmtkpp::Exception is raised.
     */
    Integers const & as_integers() const;

    /**
     * @brief Return the integers contained in the value.
     *
     * If the value does not contain integers, a dcmtkpp::Exception is raised.
     */
    Integers & as_integers();

    /**
     * @brief Return the reals contained in the value.
     *
     * If the value does not contain reals, a dcmtkpp::Exception is raised.
     */
    Reals const & as_reals() const;

    /**
     * @brief Return the reals contained in the value.
     *
     * If the value does not contain reals, a dcmtkpp::Exception is raised.
     */
    Reals & as_reals();

    /**
     * @brief Return the strings contained in the value.
     *
     * If the value does not contain strings, a dcmtkpp::Exception is raised.
     */
    Strings const & as_strings() const;

    /**
     * @brief Return the strings contained in the value.
     *
     * If the value does not contain strings, a dcmtkpp::Exception is raised.
     */
    Strings & as_strings();

    /**
     * @brief Return the data sets contained in the value.
     *
     * If the value does not contain data sets, a dcmtkpp::Exception is raised.
     */
    DataSets const & as_data_sets() const;

    /**
     * @brief Return the data sets contained in the value.
     *
     * If the value does not contain data sets, a dcmtkpp::Exception is raised.
     */
    DataSets & as_data_sets();

    /**
     * @brief Return the binary data contained in the value.
     *
     * If the value does not contain binary data, a dcmtkpp::Exception is raised.
     */
    Binary const & as_binary() const;

    /**
     * @brief Return the binary data contained in the value.
     *
     * If the value does not contain binary data, a dcmtkpp::Exception is raised.
     */
    Binary & as_binary();

    /// @brief Equality test.
    bool operator==(Value const & other) const;

    /// @brief Difference test.
    bool operator!=(Value const & other) const;

private:
    Integers _integers;
    Reals _reals;
    Strings _strings;
    DataSets _data_sets;
    Binary _binary;

    Type _type;
};

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

#include "dcmtkpp/Value.txx"

#endif // _dca5b15b_b8df_4925_a446_d42efe06c923
