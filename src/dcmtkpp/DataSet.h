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

namespace dcmtkpp
{

/**
 * @brief DICOM Data set.
 */
class DataSet
{
public:
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

    /**
     * @brief Test whether an element of the data set contains integers.
     *
     * If the element is not in the data set, a dcmtkpp::Exception is raised.
     */
    bool is_int(Tag const & tag) const;

    /**
     * @brief Return the value of an element of the data set contains integers.
     *
     * If the element is not in the data set or does not contain integers,
     * a dcmtkpp::Exception is raised.
     */
    std::vector<int64_t> const & as_int(Tag const & tag) const;

    /**
     * @brief Return the value of an element of the data set contains integers.
     *
     * If the element is not in the data set or does not contain integers,
     * a dcmtkpp::Exception is raised.
     */
    std::vector<int64_t> & as_int(Tag const & tag);

    /**
     * @brief Test whether an element of the data set contains reals.
     *
     * If the element is not in the data set, a dcmtkpp::Exception is raised.
     */
    bool is_real(Tag const & tag) const;

    /**
     * @brief Return the value of an element of the data set contains reals.
     *
     * If the element is not in the data set or does not contain reals,
     * a dcmtkpp::Exception is raised.
     */
    std::vector<double> const & as_real(Tag const & tag) const;

    /**
     * @brief Return the value of an element of the data set contains reals.
     *
     * If the element is not in the data set or does not contain reals,
     * a dcmtkpp::Exception is raised.
     */
    std::vector<double> & as_real(Tag const & tag);

    /**
     * @brief Test whether an element of the data set contains strings.
     *
     * If the element is not in the data set, a dcmtkpp::Exception is raised.
     */
    bool is_string(Tag const & tag) const;

    /**
     * @brief Return the value of an element of the data set contains strings.
     *
     * If the element is not in the data set or does not contain strings,
     * a dcmtkpp::Exception is raised.
     */
    std::vector<std::string> const & as_string(Tag const & tag) const;

    /**
     * @brief Return the value of an element of the data set contains strings.
     *
     * If the element is not in the data set or does not contain strings,
     * a dcmtkpp::Exception is raised.
     */
    std::vector<std::string> & as_string(Tag const & tag);

    // FIXME: AT, PN, SQ, binary

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
