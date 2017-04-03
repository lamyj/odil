/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _32b5f072_8ebb_4df1_925d_abd5f0535eb6
#define _32b5f072_8ebb_4df1_925d_abd5f0535eb6

#include <string>
#include <vector>

#include "odil/odil.h"
#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/Selector.h"
#include "odil/webservices/URL.h"
#include "odil/webservices/Utils.h"

namespace odil
{

namespace webservices
{

/// @brief WADO-RS request generator and parser.
class ODIL_API WADORSRequest
{
public:
    /// @brief Constructor.
    WADORSRequest(
        URL const & base_url, std::string const & transfer_syntax="",
        std::string const & character_set="",
        bool include_media_type_in_query=false,
        bool include_character_set_in_query=false);

    /// @brief Constructor.
    WADORSRequest(HTTPRequest const & request);

    /// @brief Equality operator.
    bool operator==(WADORSRequest const & other) const;

    /// @brief Difference operator.
    bool operator!=(WADORSRequest const & other) const;

    /// @brief Return the base URL.
    URL const & get_base_url() const;

    /// @brief Set the base URL; the query and fragment must be empty.
    void set_base_url(URL const & url);

    /// @brief Return the transfer syntax.
    std::string const & get_transfer_syntax() const;

    /// @brief Set the transfer syntax.
    void set_transfer_syntax(std::string const & transfer_syntax);

    /// @brief Return the transfer syntax.
    std::string const & get_character_set() const;

    /// @brief Set the transfer syntax.
    void set_character_set(std::string const & character_set);

    /// @brief Return whether to include the media type in the URL query.
    bool get_include_media_type_in_query() const;

    /// @brief Set whether to include the media type in the URL query.
    void set_include_media_type_in_query(bool include_media_type_in_query);

    /// @brief Return whether to include the character set in the URL query.
    bool get_include_character_set_in_query() const;

    /// @brief Set whether to include the character_set in the URL query.
    void set_include_character_set_in_query(bool include_charcter_set_in_query);

    /// @brief Return the query type.
    Type get_type() const;

    /// @brief Return the selector.
    Selector const & get_selector() const;

    /// @brief Return if the given selector is valid or not
    bool is_selector_valid(Selector const & selector);

    /// @brief Return the URL.
    URL const & get_url() const;

    /// @brief Return the media type.
    std::string const & get_media_type() const;

    /// @brief Return the representation.
    Representation const & get_representation() const;

    /// @brief Prepare a DICOM request.
    void request_dicom(
        Representation representation, Selector const & selector);

    /// @brief Prepare a bulk data request.
    void request_bulk_data(Selector const & selector);

    /// @brief Prepare a bulk data request.
    void request_bulk_data(URL const & url);

    /// @brief Prepare a pixel data request.
    void request_pixel_data(
        Selector const & selector,
        std::string const & media_type="application/octet-stream");

    /// @brief Generate the associated HTTP request.
    HTTPRequest get_http_request() const;

private:
    URL _base_url;
    std::string _transfer_syntax;
    std::string _character_set;
    bool _include_media_type_in_query;
    bool _include_character_set_in_query;

    Selector _selector;
    URL _url;
    std::string _media_type;
    Representation _representation;
    Type _type;

    /// @brief Split an URL in a pair of base_url and request selector.
    static std::pair<URL, Selector> _split_full_url(URL const & url);
};

}

}

#endif // _32b5f072_8ebb_4df1_925d_abd5f0535eb6
