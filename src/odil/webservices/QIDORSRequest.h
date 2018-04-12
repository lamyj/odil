/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1cd2d27d_2d97_405b_b9d5_4104210e543a
#define _1cd2d27d_2d97_405b_b9d5_4104210e543a

#include <string>
#include <tuple>
#include <vector>
#include <set>

#include "odil/DataSet.h"
#include "odil/odil.h"
#include "odil/Tag.h"
#include "odil/webservices/HTTPRequest.h"
#include "odil/webservices/Utils.h"
#include "odil/webservices/Selector.h"
#include "odil/webservices/URL.h"

namespace odil
{

namespace webservices
{

/// @brief QIDO-RS request generator and parser
class ODIL_API QIDORSRequest
{
public:
    /// @brief Constructor.
    QIDORSRequest(URL const & base_url);

    /// @brief Constructor.
    QIDORSRequest(HTTPRequest const & request);

    /// @brief Equality operator.
    bool operator==(QIDORSRequest const & other) const;

    /// @brief Difference operator.
    bool operator!=(QIDORSRequest const & other) const;

    /// @brief Return base_url.
    URL const & get_base_url() const;

    /// @brief Set the base URL; the query and fragment must be empty
    void set_base_url(URL const & url);

    /// @brief Return the media type.
    std::string const & get_media_type() const;

    /// @brief Return the representation.
    Representation const & get_representation() const;

    /// @brief Return the url.
    URL const & get_url () const;

    /// brief Return the selector.
    Selector const & get_selector() const;

    /// @brief Return the dataSet containing the wanted attribute values.
    std::shared_ptr<DataSet const> get_query_data_set() const;

    /// @brief Return the wanted fields.
    std::set<std::vector<Tag>> const & get_includefields() const;

    /// @brief Return whether fuzzymatching is wanted or not.
    bool get_fuzzymatching() const;

    /// @brief Return the wanted limit.
    int get_limit() const;

    /// @brief Return the wanted offset.
    int get_offset() const;

    /// @brief Generate the associated HTTP request.
    HTTPRequest get_http_request() const;

    /// @brief Prepare a qido request
    void request_datasets(
        Representation representation, Selector const & selector,
        std::shared_ptr<DataSet> query, bool fuzzymatching=false,
        int limit=-1, int offset=0, bool numerical_tags=false);

private:
    URL _base_url;
    std::string _media_type;
    Representation _representation;
    URL _url;
    Selector _selector;
    std::shared_ptr<DataSet> _query_data_set;

    bool _fuzzymatching;
    /// @brief Maximum number of results the origin server shall return.
    int _limit;
    /**
     * @brief Number of results the origin server shall skip before the first
     * returned result.
     */
    int _offset;

    /// @brief Return if the selector is valid or not
    static bool _is_selector_valid (Selector const & selector);

    /// @brief Return the tag as a numerical string or as a "string"
    static std::string _tag_to_string(Tag const & tag, bool numerical_tag);

    /// @brief Split an URL into a tuple
    void _from_url(URL const & url);

    /// @brief Generate a generic URL from class information
    URL _generate_url(bool numerical_tags=false);

};

}

}


#endif // _1cd2d27d_2d97_405b_b9d5_4104210e543a
