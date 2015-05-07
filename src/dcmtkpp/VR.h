/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _998aa43a_9e90_4d39_a074_a7074ac5c9b8
#define _998aa43a_9e90_4d39_a074_a7074ac5c9b8

#include <string>

namespace dcmtkpp
{

/// @brief Value representations of DICOM.
enum class VR
{
    AE, AS, AT, CS, DA, DS, DT, FL, FD, IS, LO, LT, PN, OB, OF, OW, SH, SL,
    SQ, SS, ST, TM, UC, UI, UL, UN, UR, US, UT
};

/// @brief Convert a VR to its string representation.
std::string as_string(VR vr);

/**
 * @brief Convert a string to its VR.
 *
 * If the string does not represent a VR, a dcmtkpp::Exception is raised.
 */
VR as_vr(std::string const vr);


}

#endif // _998aa43a_9e90_4d39_a074_a7074ac5c9b8
