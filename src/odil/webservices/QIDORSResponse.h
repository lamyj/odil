/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _14da8fe6_71a3_4c0b_91bf_9c518393a641
#define _14da8fe6_71a3_4c0b_91bf_9c518393a641

#include <string>
#include <vector>

#include "odil/DataSet.h"
#include "odil/webservices/HTTPResponse.h"
#include "odil/webservices/Utils.h"

namespace odil
{

namespace webservices
{

/// @brief QIDO-RS response generator and parser.
class QIDORSResponse
{
public:
    /// @brief Constructor.
    QIDORSResponse();

    /// @brief Parse an HTTPResponse as a WADORSResponse.
    QIDORSResponse(HTTPResponse const & response);

    QIDORSResponse(QIDORSResponse const &) = default;
    QIDORSResponse(QIDORSResponse &&) = default;
    QIDORSResponse & operator=(QIDORSResponse &&) = default;

    /// @brief Destructor.
    ~QIDORSResponse() = default;

    /// @brief Equality operator.
    bool operator==(QIDORSResponse const & other) const;

    /// @brief Difference operator.
    bool operator!=(QIDORSResponse const & other) const;

    /// @brief Get the response items
    std::vector<DataSet> const & get_data_sets() const;

    /// @brief Modify the response items
    std::vector<DataSet> & get_data_sets();

    /// @brief Set the response items
    void  set_data_sets(std::vector<DataSet> const& data_sets);

    /// @brief Return the representation
    odil::webservices::Representation const & get_representation() const;

    /// @brief Set the representation
    void set_representation(odil::webservices::Representation const & representation);

    /// @brief Return the media type
    std::string const & get_media_type() const;

    /// @brief Generate the associated HTTP response
    HTTPResponse get_http_response() const;

private:
    std::vector<DataSet> _data_sets;
    odil::webservices::Representation _representation;
    std::string _media_type;
};

}

}


#endif //_14da8fe6_71a3_4c0b_91bf_9c518393a641
