/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _9c3d8f32_0310_4e3a_b5d2_6d69f229a2cf
#define _9c3d8f32_0310_4e3a_b5d2_6d69f229a2cf

#include <cstddef>

#include "dcmtkpp/Tag.h"
#include "dcmtkpp/Value.h"
#include "dcmtkpp/VR.h"

namespace dcmtkpp
{

/**
 * @brief Element of a DICOM data set.
 */
class Element
{
public:

    /// @brief VR of the element.
    VR vr;

    /// @brief Default-initialize value and vr.
    Element();

    /// @brief Default-initialize vr.
    template<typename T>
    Element(T const & value);

    /// @brief Constructor.
    template<typename T>
    Element(T const & value, VR const & vr);

    /// @brief Test whether the element is empty.
    bool empty() const;

    /// @brief Return the number of items in the value.
    std::size_t size() const;

    /// @brief Test whether the value contains integers.
    bool is_int() const;

    /**
     * @brief Return the integers contained in the element.
     *
     * If the element does not contain integers, a dcmtkpp::Exception is raised.
     */
    Value::Integers const & as_int() const;

    /**
     * @brief Return the integers contained in the element.
     *
     * If the element does not contain integers, a dcmtkpp::Exception is raised.
     */
    Value::Integers & as_int();

    /// @brief Test whether the value contains reals.
    bool is_real() const;

    /**
     * @brief Return the reals contained in the element.
     *
     * If the element does not contain reals, a dcmtkpp::Exception is raised.
     */
    Value::Reals const & as_real() const;

    /**
     * @brief Return the reals contained in the element.
     *
     * If the element does not contain reals, a dcmtkpp::Exception is raised.
     */
    Value::Reals & as_real();

    /// @brief Test whether the value contains strings.
    bool is_string() const;

    /**
     * @brief Return the strings contained in the element.
     *
     * If the element does not contain strings, a dcmtkpp::Exception is raised.
     */
    Value::Strings const & as_string() const;

    /**
     * @brief Return the strings contained in the element.
     *
     * If the element does not contain strings, a dcmtkpp::Exception is raised.
     */
    Value::Strings & as_string();

    /// @brief Test whether the value contains data sets.
    bool is_data_set() const;

    /**
     * @brief Return the data sets contained in the element.
     *
     * If the element does not contain data sets, a dcmtkpp::Exception is raised.
     */
    Value::DataSets const & as_data_set() const;

    /**
     * @brief Return the data sets contained in the element.
     *
     * If the element does not contain data sets, a dcmtkpp::Exception is raised.
     */
    Value::DataSets & as_data_set();

private:
    struct Empty
    {
        typedef bool result_type;

        template<typename T>
        bool operator()(T const & container) const
        {
            return container.empty();
        }
    };

    struct Size
    {
        typedef std::size_t result_type;

        template<typename T>
        std::size_t operator()(T const & container) const
        {
            return container.size();
        }
    };


    Value _value;
};

}

#include "dcmtkpp/Element.txx"

#endif // _9c3d8f32_0310_4e3a_b5d2_6d69f229a2cf
