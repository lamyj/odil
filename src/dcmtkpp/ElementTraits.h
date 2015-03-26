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
 * - ValueType: the C++ type of the VR
 * - GetterType: the type of the getter function
 * - SetterType: the type of the setter function
 * - getter: the getter function (one of the get??? functions of DcmElement)
 * - setter: the setter function (one of the put??? functions of DcmElement)
 */
template<DcmEVR VR>
struct ElementTraits;

#define DECLARE_ELEMENT_TRAITS(vr, value_type, dcmtk_value_type) \
/** @brief Traits for generic data access to values of DcmElement. */ \
template<> \
struct ElementTraits<vr> \
{ \
    /** @brief C++ type of the VR. */ \
    typedef value_type ValueType; \
    /** @brief Type of the getter function. */ \
    typedef std::function<OFCondition(DcmElement &, dcmtk_value_type &, unsigned long const)> GetterType; \
    /** @brief Getter function (one of the get??? functions of DcmElement). */ \
    static GetterType const getter; \
    /** @brief Type of the setter function. */ \
    typedef std::function<OFCondition(DcmElement &, dcmtk_value_type const, unsigned long const)> SetterType; \
    /** @brief Setter function (one of the put??? functions of DcmElement). */ \
    static SetterType const setter; \
};

DECLARE_ELEMENT_TRAITS(EVR_AE, std::string, OFString)
DECLARE_ELEMENT_TRAITS(EVR_AS, std::string, OFString)
//DECLARE_ELEMENT_TRAITS(EVR_AT
DECLARE_ELEMENT_TRAITS(EVR_CS, std::string, OFString)
DECLARE_ELEMENT_TRAITS(EVR_DA, std::string, OFString)
DECLARE_ELEMENT_TRAITS(EVR_DS, Float64, Float64)
DECLARE_ELEMENT_TRAITS(EVR_DT, std::string, OFString)
DECLARE_ELEMENT_TRAITS(EVR_FD, Float64, Float64)
DECLARE_ELEMENT_TRAITS(EVR_FL, Float32, Float32)
DECLARE_ELEMENT_TRAITS(EVR_IS, Sint32, Sint32)
DECLARE_ELEMENT_TRAITS(EVR_LO, std::string, OFString)
DECLARE_ELEMENT_TRAITS(EVR_LT, std::string, OFString)
//DECLARE_ELEMENT_TRAITS(EVR_OB
//DECLARE_ELEMENT_TRAITS(EVR_OF
//DECLARE_ELEMENT_TRAITS(EVR_OW
DECLARE_ELEMENT_TRAITS(EVR_PN, std::string, OFString)
DECLARE_ELEMENT_TRAITS(EVR_SH, std::string, OFString)
DECLARE_ELEMENT_TRAITS(EVR_SL, Sint32, Sint32)
//DECLARE_ELEMENT_TRAITS(EVR_SQ
DECLARE_ELEMENT_TRAITS(EVR_SS, Sint16, Sint16)
DECLARE_ELEMENT_TRAITS(EVR_ST, std::string, OFString)
DECLARE_ELEMENT_TRAITS(EVR_TM, std::string, OFString)
DECLARE_ELEMENT_TRAITS(EVR_UI, std::string, OFString)
DECLARE_ELEMENT_TRAITS(EVR_UL, Uint32, Uint32)
//DECLARE_ELEMENT_TRAITS(EVR_UN
DECLARE_ELEMENT_TRAITS(EVR_US, Uint16, Uint16)
DECLARE_ELEMENT_TRAITS(EVR_UT, std::string, OFString)

#undef DECLARE_ELEMENT_TRAITS

}

#endif // _3ae28d18_6f01_4e10_98e2_1c0d21fdcab7
