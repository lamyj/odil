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
#include <cstdint>
#include <string>
#include <vector>

#include <boost/variant.hpp>

#include "dcmtkpp/Tag.h"
#include "dcmtkpp/VR.h"

namespace dcmtkpp
{

/**
 * @brief Element of a DICOM data set.
 */
class Element
{
public:
    /// @brief Value type.
    typedef boost::make_recursive_variant<
        std::vector<int64_t>, std::vector<double>, std::vector<std::string>,
        std::vector<boost::recursive_variant_>
    >::type Value;

    /// @brief Value of the element.
    Value value;

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
    std::vector<int64_t> const & as_int() const;

    /**
     * @brief Return the integers contained in the element.
     *
     * If the element does not contain integers, a dcmtkpp::Exception is raised.
     */
    std::vector<int64_t> & as_int();

    /// @brief Test whether the value contains reals.
    bool is_real() const;

    /**
     * @brief Return the reals contained in the element.
     *
     * If the element does not contain reals, a dcmtkpp::Exception is raised.
     */
    std::vector<double> const & as_real() const;

    /**
     * @brief Return the reals contained in the element.
     *
     * If the element does not contain reals, a dcmtkpp::Exception is raised.
     */
    std::vector<double> & as_real();

    /// @brief Test whether the value contains strings.
    bool is_string() const;

    /**
     * @brief Return the strings contained in the element.
     *
     * If the element does not contain strings, a dcmtkpp::Exception is raised.
     */
    std::vector<std::string> const & as_string() const;

    /**
     * @brief Return the strings contained in the element.
     *
     * If the element does not contain strings, a dcmtkpp::Exception is raised.
     */
    std::vector<std::string> & as_string();

private:
    struct Empty: public boost::static_visitor<bool>
    {
        template<typename T>
        bool operator()(T const & container) const
        {
            return container.empty();
        }
    };

    struct Size: public boost::static_visitor<std::size_t>
    {
        template<typename T>
        std::size_t operator()(T const & container) const
        {
            return container.size();
        }
    };

    template<typename TValue>
    std::vector<TValue> const & _as() const;

    template<typename TValue>
    std::vector<TValue> & _as();
};

}

#include "dcmtkpp/Element.txx"

#endif // _9c3d8f32_0310_4e3a_b5d2_6d69f229a2cf
