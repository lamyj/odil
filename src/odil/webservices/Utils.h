/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6df14dad_16fc_486d_b7e0_728127e7c579
#define _6df14dad_16fc_486d_b7e0_728127e7c579

namespace odil
{

namespace webservices
{

/**
 * @brief Type of the request or response (use for WADO & QIDO).
 *
 * DICOM means DICOM data, either in binary, XML or JSON format; bulk data
 * is large (application-defined) data in binary format; pixel data is
 * the pixel data stored in instances or frames, either in uncompressed or
 * compressed format.
 */
enum class Type
{
    None,
    DICOM,
    BulkData,
    PixelData,
};

/// @brief Data representation for DICOM requests and responses.
enum class Representation
{
    DICOM,
    DICOM_XML,
    DICOM_JSON,
};


}

}

#endif // _6df14dad_16fc_486d_b7e0_728127e7c579

