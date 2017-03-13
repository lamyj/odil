/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7c67d064_123c_48a2_9bb5_b3329b795023
#define _7c67d064_123c_48a2_9bb5_b3329b795023

namespace odil
{

namespace webservices
{

namespace WADORS
{

/**
 * @brief Type of the WADO-RS request or response.
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

}

#endif // _7c67d064_123c_48a2_9bb5_b3329b795023

