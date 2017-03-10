/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dc5b12c8_04d2_11e7_88df_4303030ce2ae
#define _dc5b12c8_04d2_11e7_88df_4303030ce2ae

namespace odil
{

namespace webservices
{

namespace QIDORS
{

/// @brief Only DICOM is avaible as type (we will have either XML or JSON version)
enum class Representation
{
    DICOM_XML,
    DICOM_JSON,
};

}

}

}

#endif // _dc5b12c8_04d2_11e7_88df_4303030ce2ae
