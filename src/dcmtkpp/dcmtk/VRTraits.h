/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _4f556093_02e3_4659_9026_2b16bc2c8a51
#define _4f556093_02e3_4659_9026_2b16bc2c8a51

#include <vector>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcvr.h>

namespace dcmtkpp
{

namespace dcmtk
{

/**
 * @class dcmtkpp::VRTraits
 * @brief Information related to VR.
 *
 * The members are:
 * - ValueType: the DCMTK type of the VR
 */
template<DcmEVR VR>
struct VRTraits;

#define DECLARE_VR_TRAITS(vr, value_type) \
/** @brief Traits for generic data access to values of DcmElement. */ \
template<> \
struct VRTraits<vr> \
{ \
    /** @brief Type associated to the VR. */ \
    typedef value_type ValueType; \
};

DECLARE_VR_TRAITS(EVR_AE, std::string)
DECLARE_VR_TRAITS(EVR_AS, std::string)
//DECLARE_VR_TRAITS(EVR_AT
DECLARE_VR_TRAITS(EVR_CS, std::string)
DECLARE_VR_TRAITS(EVR_DA, std::string)
DECLARE_VR_TRAITS(EVR_DS, Float64)
DECLARE_VR_TRAITS(EVR_DT, std::string)
DECLARE_VR_TRAITS(EVR_FD, Float64)
DECLARE_VR_TRAITS(EVR_FL, Float32)
DECLARE_VR_TRAITS(EVR_IS, Sint32)
DECLARE_VR_TRAITS(EVR_LO, std::string)
DECLARE_VR_TRAITS(EVR_LT, std::string)
DECLARE_VR_TRAITS(EVR_OB, std::vector<unsigned char>)
DECLARE_VR_TRAITS(EVR_OF, std::vector<unsigned char>)
DECLARE_VR_TRAITS(EVR_OW, std::vector<unsigned char>)
DECLARE_VR_TRAITS(EVR_PN, std::string)
DECLARE_VR_TRAITS(EVR_SH, std::string)
DECLARE_VR_TRAITS(EVR_SL, Sint32)
//DECLARE_VR_TRAITS(EVR_SQ
DECLARE_VR_TRAITS(EVR_SS, Sint16)
DECLARE_VR_TRAITS(EVR_ST, std::string)
DECLARE_VR_TRAITS(EVR_TM, std::string)
DECLARE_VR_TRAITS(EVR_UI, std::string)
DECLARE_VR_TRAITS(EVR_UL, Uint32)
DECLARE_VR_TRAITS(EVR_UN, std::vector<unsigned char>)
DECLARE_VR_TRAITS(EVR_US, Uint16)
DECLARE_VR_TRAITS(EVR_UT, std::string)

#undef DECLARE_VR_TRAITS

}

}

#endif // _4f556093_02e3_4659_9026_2b16bc2c8a51
