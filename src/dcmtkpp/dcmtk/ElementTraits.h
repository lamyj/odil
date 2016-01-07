/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _3ae28d18_6f01_4e10_98e2_1c0d21fdcab7
#define _3ae28d18_6f01_4e10_98e2_1c0d21fdcab7

#include <functional>
#include <string>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcelem.h>
#include <dcmtk/dcmdata/dcvr.h>

namespace dcmtkpp
{

/**
 * @class dcmtkpp::ElementTraits
 * @brief Traits for generic data access to values of DcmElement.
 *
 * The members are:
 * - GetterType: the type of the getter function
 * - SetterType: the type of the setter function
 * - getter: the getter function (one of the get??? functions of DcmElement)
 * - setter: the setter function (one of the put??? functions of DcmElement)
 */
template<typename TValueType>
struct ElementTraits
{
    /** @brief Type of the getter function. */
    typedef std::function<OFCondition(DcmElement &, TValueType &, unsigned long const)> GetterType;
    /** @brief Getter function (one of the get??? functions of DcmElement). */
    static GetterType const getter;
    /** @brief Type of the setter function. */
    typedef std::function<OFCondition(DcmElement &, TValueType const, unsigned long const)> SetterType;
    /** @brief Setter function (one of the put??? functions of DcmElement). */
    static SetterType const setter;
};

}

#endif // _3ae28d18_6f01_4e10_98e2_1c0d21fdcab7
