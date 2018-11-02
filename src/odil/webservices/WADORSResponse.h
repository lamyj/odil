/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _91f4f1d4_f2ff_48a2_8918_ade8aa161233
#define _91f4f1d4_f2ff_48a2_8918_ade8aa161233

#include <string>
#include <vector>

#include "odil/DataSet.h"
#include "odil/Element.h"
#include "odil/odil.h"
#include "odil/Value.h"
#include "odil/webservices/BulkData.h"
#include "odil/webservices/HTTPResponse.h"
#include "odil/webservices/Utils.h"

namespace odil
{

namespace webservices
{

/// @brief WADO-RS response generator and parser.
class ODIL_API WADORSResponse
{
public:
    /// @brief Constructor.
    WADORSResponse();

    /// @brief Parse an HTTPResponse as a WADORSResponse.
    WADORSResponse(HTTPResponse const & response);

    WADORSResponse(WADORSResponse const &) =default;
    WADORSResponse(WADORSResponse &&) =default;
    ~WADORSResponse() =default;
    WADORSResponse & operator=(WADORSResponse &&) =default;

    /// @brief Equality operator.
    bool operator==(WADORSResponse const & other) const;
    //
    /// @brief Difference operator.
    bool operator!=(WADORSResponse const & other) const;

    /// @brief Get the response items.
    Value::DataSets const & get_data_sets() const;

    /// @brief Modify the response items.
    Value::DataSets & get_data_sets();

    /// @brief Set the response items.
    void set_data_sets(Value::DataSets const & data_sets);

    /// @brief Get the response items.
    std::vector<BulkData> const & get_bulk_data() const;

    /// @brief Modify the response items.
    std::vector<BulkData> & get_bulk_data();

    /// @brief Set the response items.
    void set_bulk_data(std::vector<BulkData> const & bulk_data);

    /// @brief Return whether the requested content is partially transferred.
    bool is_partial() const;
    
    /// @brief Set whether the requested content is partially transferred.
    void set_partial(bool partial);

    /// @brief Return the response type.
    Type get_type() const;

    /// @brief Return the representation.
    Representation const & get_representation() const;

    /**
     * @brief Prepare a DICOM response.
     *
     * With a DICOM representation, the transfer_syntax of each data set will
     * be used.
     */
    void respond_dicom(Representation representation);

    /// @brief Prepare a bulk data response.
    void respond_bulk_data();

    /// @brief Prepare a pixel data response.
    void respond_pixel_data(
        std::string const & media_type="application/octet-stream");

    /// @brief Generate the associated HTTP response
    HTTPResponse get_http_response() const;

private:
    Value::DataSets _data_sets;
    std::vector<BulkData> _bulk_data;
    bool _is_partial;
    Type _type;
    Representation _representation;
    std::string _media_type;
};

}

}

#endif //_91f4f1d4_f2ff_48a2_8918_ade8aa161233

