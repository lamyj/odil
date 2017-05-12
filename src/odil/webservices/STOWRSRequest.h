/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _920fb954_a579_47a3_8288_21ea1a01f81d
#define _920fb954_a579_47a3_8288_21ea1a01f81d

#include <vector>

#include "odil/DataSet.h"
#include "odil/webservices/BulkData.h"
#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/Selector.h"
#include "odil/webservices/Utils.h"
#include "odil/webservices/URL.h"

namespace odil
{

namespace webservices
{
/// @brief STOW-RS request generator and parser.
// TODO : Wrap me
class ODIL_API STOWRSRequest
{

public:
    /// @brief Constructor which takes an URL as argument.
    STOWRSRequest(URL const & base_url);

    /// @brief Constructor which takes an HTTPRequest as argument.
    STOWRSRequest(HTTPRequest const & request);

    /// @brief Equality operator.
    bool operator==(STOWRSRequest const & other) const;

    /// @brief Difference operator.
    bool operator!=(STOWRSRequest const & other) const;

    /// @brief Destructor.
    ~STOWRSRequest()=default;

    /// @brief Return base_url.
    URL const & get_base_url() const;

    /// @brief Set the base url.
    void set_base_url(URL const & url);

    /// @brief Return the media type.
    std::string const & get_media_type() const;

    /// @brief Return the representation.
    Representation const & get_representation() const;

    /// @brief Return the url.
    URL const & get_url() const;

    /// @brief Return the selector.
    Selector const & get_selector() const;

    /// @brief Get the response items.
    std::vector<DataSet> const & get_data_sets() const;

    /// @brief Modify the response items.
    std::vector<DataSet> & get_data_sets();

    /**
     * @brief Prepare a dicom request
     *
     * with a vector of datasets to store (each one will be used in a part of the request)
     * And a selector corresponding to the location where the instance will be stored
     */
    void request_dicom(std::vector<DataSet> const & data_sets, Selector const & selector);

    // TODO : Complete me when understanding the content of JSON or XML request
//    void request_dicom_xml(std::vector<DataSet>, std::vector<BulkData>);

//    void request_dicom_json(std::vector<DataSet>, std::vector<BulkData>);

    /// @brief Generate the associated HTTP request.
    HTTPRequest get_http_request() const;

private:
    URL _base_url;
    Selector _selector;
    URL _url;
    std::string _media_type;

    Representation _representation; // Available request representations : DICOM - DICOM_XML - DICOM_JSON
    std::vector<DataSet> _data_sets;
//    std::vector<BulkData> _bulk_data;

    /// @brief Return if the selector is valid or not
    static bool _is_selector_valid (Selector const & selector);

    /// @brief Split an url into a pair containing the base url, and the Selector
    static std::pair <URL, Selector> _split_full_url (const URL& url);
};

}

}

#endif // _920fb954_a579_47a3_8288_21ea1a01f81d
