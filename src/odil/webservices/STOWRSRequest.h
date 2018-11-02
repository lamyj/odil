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

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>

#include "odil/DataSet.h"
#include "odil/odil.h"
#include "odil/registry.h"
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

    /// @brief Return the transfer syntax.
    std::string const & get_transfer_syntax() const;

    /// @brief Set the transfer syntax.
    void set_transfer_syntax(std::string const & transfer_syntax);

    /// @brief Return the media type.
    std::string const & get_media_type() const;

    /// @brief Return the representation.
    Representation const & get_representation() const;

    /// @brief Return the url.
    URL const & get_url() const;

    /// @brief Return the selector.
    Selector const & get_selector() const;

    /// @brief Get the response items.
    Value::DataSets const & get_data_sets() const;

    /// @brief Modify the response items.
    Value::DataSets & get_data_sets();

    /**
     * @brief Prepare a dicom request
     *
     * with a vector of datasets to store (each one will be used in a part of the request)
     * A selector corresponding to the location where the instance will be stored
     * and a representation corresponding to the way the request will be encoded
     */
    void request_dicom(
        Value::DataSets const & data_sets, Selector const & selector,
        Representation const & representation,
        std::string const & transfer_syntax=registry::ExplicitVRLittleEndian);

    /// @brief Generate the associated HTTP request.
    HTTPRequest get_http_request() const;

private:
    /// @brief Map an UUID to its bulk content.
    typedef std::map<std::string, Value::Binary::value_type> BulkMap;

    URL _base_url;
    std::string _transfer_syntax;
    Selector _selector;
    URL _url;
    std::string _media_type;

    Representation _representation; // Available request representations : DICOM - DICOM_XML - DICOM_JSON
    Value::DataSets _data_sets;

    /// @brief Return if the selector is valid or not
    static bool _is_selector_valid (Selector const & selector);

    /// @brief Return the media-type deduced from the transfer-syntax of the dataSet
    static std::string _media_type_from_transfer_syntax(
        std::string const & transfer_syntax);

    /// @brief Function that extracts bulk data from a data_set and store them into the uuid_to_bulk vector
    static void _extract_bulk_data(
        std::shared_ptr<DataSet> data_set, std::vector<BulkData> & bulk_data);

    /**
     * @brief Function used to restore the dataSet to its initial state (With bulk data at the correct location)
     * In this function we also change the content of uuid_to_bulk map
     */
    static void _restore_data_set(
        std::shared_ptr<DataSet> data_set, BulkMap & bulk_map);
};

}

}

#endif // _920fb954_a579_47a3_8288_21ea1a01f81d
