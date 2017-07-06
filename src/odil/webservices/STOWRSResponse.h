/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _0523d1f2_656d_47a9_b5e9_867dad172f31
#define _0523d1f2_656d_47a9_b5e9_867dad172f31

#include <string>
#include <vector>


#include "odil/DataSet.h"
#include "odil/webservices/HTTPResponse.h"
#include "odil/webservices/Utils.h"

namespace odil
{

namespace webservices
{
/// @brief STOW-RS request generator and parser.
class STOWRSResponse
{
public:
    /// @brief Constructor.
    STOWRSResponse();

    /// @brief Parse an HTTPResponse as a STOWRSResponse.
    STOWRSResponse(HTTPResponse const & response);

    /// @brief Destructor, does nothing
    ~STOWRSResponse() = default;

    /// @brief Equality operator
    bool operator==(STOWRSResponse const & other) const;

    /// @brief Difference operator
    bool operator!=(STOWRSResponse const & other) const;

    /// @brief Set store instance responses
    void set_store_instance_responses(DataSet const & responses);

    /// @brief Get store instance responses
    DataSet const & get_store_instance_responses() const;

    /// @brief Get the media type
    std::string const & get_media_type() const;

    /// @brief Set the representation
    void set_representation (odil::webservices::Representation const & representation);

    /// @brief Get the representation
    odil::webservices::Representation const & get_representation() const;

    /// @brief Set whether there is a warning in the response or not
    void set_warning(bool warn);

    /// @brief Return whether there is a warning in the response or not
    bool is_status_warning() const;

    /// @brief Set the failure code
    void set_failure_code(unsigned int failure_code);

    /// @brief Return the failure code
    unsigned int get_failure_code() const;

    /// @brief Set the reason
    void set_reason(std::string reason);

    /// @brief Get the reason
    std::string const & get_reason() const;

    /// @brief Generate the associated HTTP Response
    HTTPResponse get_http_response() const;


private:
    DataSet _store_instance_responses;
    odil::webservices::Representation _representation; // either DICOM+XML or DICOM+JSON
    std::string _reason;
    bool _warning;
    unsigned int _failure_code;
    std::string _media_type; // either DICOM+XML or DICOM+JSON

};

}

}

#endif // _0523d1f2_656d_47a9_b5e9_867dad172f31
